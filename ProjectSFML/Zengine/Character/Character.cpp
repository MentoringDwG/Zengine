#include "Character.h"

Character::Character(std::string name, string Path, float playerMoveSpeed)
{
	inputHandler.SetName(name);
	inputHandler.SetOwningCharacter(this);
	SetTextureAsset(Path, name);

	moveSpeed = playerMoveSpeed;

	character.setPosition(sf::Vector2f(200.0f, 416.0f));
	character.setOrigin(sf::Vector2f(character.getSize().x / 2, character.getSize().y / 2));
}

//MOVEMENT
void Character::MoveLeft()
{
	character.setScale(sf::Vector2f(-1.0f, 1.0f));
	character.move(sf::Vector2f(-1.0f * moveSpeed, 0.0f));
}

void Character::MoveRight()
{
	character.setScale(sf::Vector2f(1.0f, 1.0f));
	character.move(sf::Vector2f(1.0f * moveSpeed, 0.0f));
}

void Character::MoveUp()
{
	character.move(sf::Vector2f(0.0f, -1.0f * moveSpeed));
}

void Character::MoveDown()
{
	character.move(sf::Vector2f(0.0f, 1.0f * moveSpeed));
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

void Character::DrawCharacter(RenderingStack* renderStack)
{
	sf::Texture* texture = nullptr;
	texture = textureAsset->GetTexture();

	character.setSize(sf::Vector2f(32.0f, 64.0f));
	character.setTexture(texture);

	characterRenderObject->drawable = &character;
	characterRenderObject->zOrder = 1000;
	characterRenderObject->layerId = 1;

	renderStack->renderQueue.push_back(characterRenderObject);
}