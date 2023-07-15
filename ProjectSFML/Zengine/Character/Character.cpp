#include "Character.h"
#include <functional>


Character::Character(std::string name, string Path, float playerMoveSpeed)
{
	inputHandler.SetName(name);
	inputHandler.SetOwningCharacter(this);

	SetTextureAsset(Path, name);

	moveSpeed = playerMoveSpeed;

	zenShape = new ZenShape(0, name);
	zenShape->SetPosition(sf::Vector2f(200.0f, 416.0f));
	zenShape->SetOrigin(sf::Vector2f(zenShape->GetSize().x / 2, zenShape->GetSize().y / 2));
}

//MOVEMENT
void Character::MoveLeft()
{
	zenShape->SetScale(sf::Vector2f(-1.0f, 1.0f));
	zenShape->MoveObject(sf::Vector2f(-1.0f * moveSpeed, 0.0f));
}

void Character::MoveRight()
{
	zenShape->SetScale(sf::Vector2f(1.0f, 1.0f));
	zenShape->MoveObject(sf::Vector2f(1.0f * moveSpeed, 0.0f));
}

void Character::MoveUp()
{
	zenShape->MoveObject(sf::Vector2f(0.0f, -1.0f * moveSpeed));
}

void Character::MoveDown()
{
	zenShape->MoveObject(sf::Vector2f(0.0f, 1.0f * moveSpeed));
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
	sf::Texture* texture = nullptr;
	texture = textureAsset->GetTexture();

	zenShape->SetSize(sf::Vector2f(32.0f, 64.0f));
	zenShape->SetTexture(texture);

	characterRenderObject = new RenderObject(zenShape->Draw(), 1000, 1);
	renderStack->renderQueue.push_back(characterRenderObject);
}

void Character::SetCollider(Vector2* position, float radius)
{
	collider2D = new CircleCollider2D(position, radius, zenShape);
	collider2D->OnCollisionStart = std::bind(&Character::HandleCollisionStart, this, std::placeholders::_1);
}
	
void Character::HandleCollisionStart(const CircleCollider2D* other)
{
	cout << "Characetr hier";
}

