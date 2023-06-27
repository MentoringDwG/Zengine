#include "Character.h"

//MOVEMENT
void Character::MoveLeft()
{
	cout <<Character::inputHandler.GetName() <<" Move Left" << endl;

	character.move(sf::Vector2f(-1.0f * moveSpeed, 0.0f));

}

void Character::MoveRight()
{
	cout << Character::inputHandler.GetName() << " Move Right" << endl;

	character.move(sf::Vector2f(1.0f * moveSpeed, 0.0f));
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
	texture = new sf::Texture();
	*texture = GetTextureAsset().TextureSFML;
	character.setSize(sf::Vector2f(32.0f, 64.0f));
	character.setPosition(sf::Vector2f(10.0f, 416.0f));
	
	characterRenderObject = new RenderObject();
	characterRenderObject->drawable = &character;
	characterRenderObject->texcure = texture;
	characterRenderObject->zOrder = 1000;
	characterRenderObject->layerId = 1;

	renderStack->renderQueue.push_back(characterRenderObject);
}