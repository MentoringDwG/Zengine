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
	Character::texcureAsset = new TextureAsset(Path, Name);
}

TextureAsset Character::GetTextureAsset()
{
	return *Character::texcureAsset;
}