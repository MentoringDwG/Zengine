#include "Character.h"
#include <functional>

Character::Character(std::string name, string Path, float playerMoveSpeed)
{
	inputHandler.SetName(name);
	inputHandler.SetOwningCharacter(this);

	SetTextureAsset(Path, name);

	moveSpeed = playerMoveSpeed;

	zenShape = new ZenShape(0, name, sf::Vector2f(32, 64));
	zenShape->SetPosition(sf::Vector2f(200.0f, 384.0f));
	zenShape->SetSize(sf::Vector2f(32.0f, 64.0f));

	boxCollider = new BoxCollider2D(new Vector2(zenShape->GetPosition().x, zenShape->GetPosition().y), new Vector2(zenShape->GetSize().x, zenShape->GetSize().y), zenShape);
	boxCollider->OnBoxCollisionStart = std::bind(&Character::HandleBoxCollisionStart, this, std::placeholders::_1);
	ZenPhysics2D::Get()->RegisterCollider(boxCollider);
	//SetCollider(new Vector2(zenShape->GetPosition().x, zenShape->GetPosition().y), 35);
}

//MOVEMENT
void Character::MoveLeft()
{
	zenShape->SetScale(sf::Vector2f(-1, 1));
	zenShape->SetOrigin(sf::Vector2f(zenShape->GetGlobalBounds().width, 0));
	zenShape->SetTexture(texture);

	zenShape->MoveObject(sf::Vector2f(-1.0f * moveSpeed, 0.0f));
	boxCollider->SetPosition(zenShape->GetPosition());
	//collider2D->SetPosition(zenShape->GetPosition());
}

void Character::MoveRight()
{
	zenShape->SetScale(sf::Vector2f(1, 1));
	zenShape->SetOrigin(sf::Vector2f(0, 0));
	zenShape->MoveObject(sf::Vector2f(1.0f * moveSpeed, 0.0f));
	boxCollider->SetPosition(zenShape->GetPosition());
	//collider2D->SetPosition(zenShape->GetPosition());
}

void Character::MoveUp()
{
	zenShape->MoveObject(sf::Vector2f(0.0f, -1.0f * moveSpeed));
	boxCollider->SetPosition(zenShape->GetPosition());
	//collider2D->SetPosition(zenShape->GetPosition());
}

void Character::MoveDown()
{
	zenShape->MoveObject(sf::Vector2f(0.0f, 1.0f * moveSpeed));
	boxCollider->SetPosition(zenShape->GetPosition());
	//collider2D->SetPosition(zenShape->GetPosition());
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
	zenShape->SetTexture(texture);

	characterRenderObject = new RenderObject(zenShape->Draw(), 1000, 1);
	renderStack->renderQueue.push_back(characterRenderObject);
}

void Character::SetCollider(Vector2* position, float radius)
{
	collider2D = new CircleCollider2D(position, radius, zenShape);
	collider2D->OnCollisionStart = std::bind(&Character::HandleCollisionStart, this, std::placeholders::_1);
	//ZenPhysics2D::Get()->RegisterCollider(collider2D);
	ZenPhysics2D::Get()->RegisterCollider(boxCollider);
}
	
void Character::HandleCollisionStart(CircleCollider2D* other)
{

}

void Character::HandleBoxCollisionStart(BoxCollider2D* other)
{
	if (other->GetOwner()->Name == "Ground")
	{
		cout << "Collision" << endl;
	}
}
