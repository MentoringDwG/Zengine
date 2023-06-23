#include "Character.h"

void Character::MoveLeft()
{
	cout <<inputHandler.GetName() <<" Move Left" << endl;
}

void Character::MoveRight()
{
	cout << inputHandler.GetName() << " Move Right" << endl;
}

CharacterInputHandler Character::GetInputHandler()
{
	return inputHandler;
}

void Character::SetTextureAsset(string Path, string Name)
{
	texcureAsset = new TextureAsset(Path, Name);
}

TextureAsset Character::GetTextureAsset()
{
	return *texcureAsset;
}