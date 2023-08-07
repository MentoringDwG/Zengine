#include "Character.h"
#include <functional>

Character::Character(std::string name, string Path, float playerMoveSpeed)
{
	inputHandler.SetName(name);
	inputHandler.SetOwningCharacter(this);
	inputHandler.Start();

	SetTextureAsset(Path, name);

	moveSpeed = playerMoveSpeed;

	physicalZenObject2D = new PhysicalZenObject2D(0, name, Path, sf::Vector2f(200.0f, 384.0f), sf::Vector2f(32, 64));
	physicalZenObject2D->zenShape = new ZenShape(0, name, sf::Vector2f(32, 64));
	physicalZenObject2D->zenShape->SetPosition(sf::Vector2f(200.0f, 384.0f));
	physicalZenObject2D->zenShape->SetSize(sf::Vector2f(32, 64));

	SetCollider(new Vector2(physicalZenObject2D->zenShape->GetPosition().x, physicalZenObject2D->zenShape->GetPosition().y), 35);
	physicalZenObject2D->SetGravity(5);

	ZenPhysics2D::Get()->RegisterPhysicalObject(physicalZenObject2D);
}

//MOVEMENT
void Character::MoveLeft()
{
	physicalZenObject2D->zenShape->SetScale(sf::Vector2f(-1, 1));
	physicalZenObject2D->zenShape->SetOrigin(sf::Vector2f(physicalZenObject2D->zenShape->GetGlobalBounds().width, 0));
	physicalZenObject2D->zenShape->SetTexture(texture);

	physicalZenObject2D->zenShape->MoveObject(sf::Vector2f(-1.0f * moveSpeed, 0.0f));
}

void Character::MoveRight()
{
	physicalZenObject2D->zenShape->SetScale(sf::Vector2f(1, 1));
	physicalZenObject2D->zenShape->SetOrigin(sf::Vector2f(0, 0));
	physicalZenObject2D->zenShape->MoveObject(sf::Vector2f(1.0f * moveSpeed, 0.0f));
}

void Character::MoveUp()
{
	if (isGrounded)
	{
		isJump = true;
		physicalZenObject2D->AddForce(1.0f, Vector2(0, -3.0f), 3.0f);
	}
}

void Character::MoveDown()
{
	if (!isGrounded)
	{
		physicalZenObject2D->zenShape->MoveObject(sf::Vector2f(0.0f, 1.0f * physicalZenObject2D->GetGravity()));
	}
}

void Character::UpdateCharacter()
{
	collider2D->SetPosition(physicalZenObject2D->zenShape->GetPosition());
}


CharacterInputHandler Character::GetInputHandler()
{
	return Character::inputHandler;
}

void Character::SetTextureAsset(string Path, string Name)
{
	textureAsset = new TextureAsset(Path, Name);
}

TextureAsset Character::GetTextureAsset()
{
	return *textureAsset;
}

void Character::Draw(RenderingStack* renderStack)
{
	texture = textureAsset->GetTexture();
	physicalZenObject2D->zenShape->SetTexture(texture);

	characterRenderObject = new RenderObject(physicalZenObject2D->zenShape->Draw(), 1000, 1);
	renderStack->renderQueue.push_back(characterRenderObject);
}

void Character::SetCollider(Vector2* position, float radius)
{
	collider2D = new CircleCollider2D(position, radius, physicalZenObject2D->zenShape);
	collider2D->OnCollisionStart = std::bind(&Character::HandleCollisionStart, this, std::placeholders::_1);
	collider2D->OnCollisionEnd = std::bind(&Character::HandleCollisionEnd, this, std::placeholders::_1);
	ZenPhysics2D::Get()->RegisterCollider(collider2D);
}

void Character::HandleCollisionStart(Collider* other)
{
	if (other->GetOwner()->Name == "Ground")
	{
		isGrounded = true;
	}
}

void Character::HandleCollisionEnd(Collider* other)
{
	if (other->GetOwner()->Name == "Ground")
	{
		isGrounded = false;
	}
}