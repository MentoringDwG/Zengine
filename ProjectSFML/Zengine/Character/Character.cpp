#include "Character.h"
#include <functional>


Character::Character(std::string name, string PathR, string PathL, float playerMoveSpeed)
{
	inputHandler.SetName(name);
	inputHandler.SetOwningCharacter(this);

	SetTextureAsset(PathR, name);
	this->PathR = PathR;
	this->PathL = PathL;

	moveSpeed = playerMoveSpeed;

	zenShape = new ZenShape(0, name);
	zenShape->SetPosition(sf::Vector2f(200.0f, 416.0f));
	zenShape->SetOrigin(sf::Vector2f(zenShape->GetSize().x / 2, zenShape->GetSize().y / 2));
}

//MOVEMENT
void Character::MoveLeft()
{
	SetGraphicsForMovement(PathL);
	zenShape->MoveObject(sf::Vector2f(-1.0f * moveSpeed, 0.0f));
	collider2D->SetPosition(zenShape->GetPosition());
}

void Character::MoveRight()
{
	SetGraphicsForMovement(PathR);
	zenShape->MoveObject(sf::Vector2f(1.0f * moveSpeed, 0.0f));
	collider2D->SetPosition(zenShape->GetPosition());
}

void Character::MoveUp()
{
	zenShape->MoveObject(sf::Vector2f(0.0f, -1.0f * moveSpeed));
	collider2D->SetPosition(zenShape->GetPosition());
}

void Character::MoveDown()
{
	zenShape->MoveObject(sf::Vector2f(0.0f, 1.0f * moveSpeed));
	collider2D->SetPosition(zenShape->GetPosition());
}


CharacterInputHandler Character::GetInputHandler()
{
	return Character::inputHandler;
}

void  Character::SetGraphicsForMovement(string Path)
{
	textureAsset->SetPath(Path);
	texture = textureAsset->GetTexture();
	zenShape->SetTexture(texture);
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

	zenShape->SetSize(sf::Vector2f(32.0f, 64.0f));
	zenShape->SetTexture(texture);

	characterRenderObject = new RenderObject(zenShape->Draw(), 1000, 1);
	renderStack->renderQueue.push_back(characterRenderObject);
}

void Character::SetCollider(Vector2* position, float radius, ZenPhysics2D* zenPhysics2D)
{
	collider2D = new CircleCollider2D(position, radius, zenShape);
	collider2D->OnCollisionStart = std::bind(&Character::HandleCollisionStart, this, std::placeholders::_1);
	zenPhysics2D->RegisterCollider(collider2D);
}
	
void Character::HandleCollisionStart(const CircleCollider2D* other)
{
	cout << "Characetr hier";
}

