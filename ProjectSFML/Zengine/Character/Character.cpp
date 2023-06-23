#include "Character.h"

void Character::MoveLeft()
{
	cout <<Character::inputHandler.name <<" Move Left" << endl;
}

void Character::MoveRight()
{
	cout << Character::inputHandler.name << " Move Right" << endl;
}

CharacterInputHandler Character::GetInputHandler()
{
	return Character::inputHandler;
}