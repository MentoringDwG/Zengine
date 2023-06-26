#include "Character.h"

void Character::MoveLeft()
{
	cout <<Character::inputHandler.GetName() <<" Move Left" << endl;
}

void Character::MoveRight()
{
	cout << Character::inputHandler.GetName() << " Move Right" << endl;
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
	const sf::Texture texture = GetTextureAsset().TextureSFML;
	character.setSize(sf::Vector2f(32.0f, 64.0f));
	character.setTexture(&texture);
	
	characterRenderObject = new RenderObject();
	characterRenderObject->drawable = &character;
	characterRenderObject->zOrder = 1000;
	characterRenderObject->layerId = 1;

	renderStack->renderQueue.push_back(characterRenderObject);
}