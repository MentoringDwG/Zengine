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
	texcureAsset = new TextureAsset(Path, Name);
}

TextureAsset Character::GetTextureAsset()
{
	return *texcureAsset;
}

void Character::DrawCharacter(RenderingStack* renderStack)
{
	const sf::Texture texcure = GetTextureAsset().TextureSFML;
	character.setSize(sf::Vector2f(32.0f, 64.0f));
	character.setTexture(&texcure);
	
	characterRenderObject.drawable = &character;
	characterRenderObject.zOrder = 1000;
	characterRenderObject.layerId = 1;

	renderStack->renderQueue.push_back(&characterRenderObject);

	//windowIn.draw(character);
}