#include "PhysicalZenObject2D.h"

PhysicalZenObject2D::PhysicalZenObject2D(int IDIn, string NameIn, string enemySpritePath, sf::Vector2f startPosition) :ZenObject(IDIn, NameIn)
{
	velocity = new Vector2(0, 0);
	transposition = new Vector2(0.1, 0);
	acceleration = new Vector2(0, 0);

	zenShape = new ZenShape(3, "zenShape");
	zenShape->SetTexture(enemySpritePath);
	zenShape->SetPosition(startPosition);
	zenShape->SetSize(sf::Vector2f(32.0f, 32.0f));
}

void PhysicalZenObject2D::CalculatePhysics()
{
	transposition->x = velocity->x - (fakeDrag * velocity->x / 100);

	if (velocity->x<0 && transposition->x > -0.5)
	{
		ResettingVariables();
		return;
	}

	if (velocity->x>0 && transposition->x < 0.5)
	{
		ResettingVariables();
		return;
	}

	zenShape->MoveObject(sf::Vector2f(transposition->x, 0.0f));
	velocity->x= velocity->x - (fakeDrag * velocity->x / 100);
	fakeDrag = fakeDrag + 0.1;
}

void PhysicalZenObject2D::ResettingVariables()
{
	transposition->SetVector2(0, 0);
	fakeDrag = 1;
}

//direction: -1 - left, 1 -right
void PhysicalZenObject2D::ApplyForceToPhysicsObject(float massIn, float forceIN, float time)
{
	mass = massIn;
	force = forceIN;

	acceleration->x = force / mass;

	float s = (acceleration->x * time * time) / 2;

	velocity->x = s / time;
}

float PhysicalZenObject2D::GetTransposition()
{
	return transposition->x;
}

float PhysicalZenObject2D::GetVelocityX()
{
	return velocity->x;
}