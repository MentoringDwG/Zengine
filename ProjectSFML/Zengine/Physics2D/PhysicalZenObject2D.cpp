#include "PhysicalZenObject2D.h"
#pragma optimize("", off)

enum PhysicalZenObject2D::ForceDirection
{
	left = -1,
	right = 1
};

PhysicalZenObject2D::PhysicalZenObject2D(int IDIn, string NameIn, string enemySpritePath, sf::Vector2f startPosition) :ZenObject(IDIn, NameIn)
{
	velocity.push_back(0);
	transposition.push_back(0.1);
	acceleration.push_back(0);

	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(enemySpritePath);

	rectangleShape = new sf::RectangleShape;
	rectangleShape->setPosition(startPosition);
	rectangleShape->setSize(sf::Vector2f(32.0f, 32.0f));
	rectangleShape->setTexture(texture);
}

void PhysicalZenObject2D::CalculatePhysics()
{
	transposition[0] = velocity[0] - (slowdownPercentage * velocity[0] / 100);

	if (forceDirection==left && transposition[0] > -0.5)
	{
		transposition[0] = 0;
		slowdownPercentage = 1;
		return;
	}

	if (forceDirection == right && transposition[0] < 0.5)
	{
		transposition[0] = 0;
		slowdownPercentage = 1;
		return;
	}

	rectangleShape->move(sf::Vector2f(transposition[0], 0.0f));
	velocity[0]= velocity[0] - (slowdownPercentage * velocity[0] / 100);
	slowdownPercentage = slowdownPercentage + 0.1;
}

//direction: -1 - left, 1 -right
void PhysicalZenObject2D::AddForce(float massIn, float forceIN, float time, int direction)
{
	if (direction == -1) forceDirection = left;
	if (direction == 1) forceDirection = right;

	mass = massIn;
	force = forceIN*direction;

	acceleration[0] = force / mass;

	float s = (acceleration[0] * time * time) / 2;

	velocity[0] = s / time;
}

void PhysicalZenObject2D::Draw(RenderingStack* renderStack)
{
	physicalRenderObject = new RenderObject();
	physicalRenderObject->drawable = rectangleShape;
	physicalRenderObject->zOrder = 1000;
	physicalRenderObject->layerId = 1;

	renderStack->renderQueue.push_back(physicalRenderObject);
}

float PhysicalZenObject2D::GetTransposition()
{
	return transposition[0];
}

#pragma optimize("", on)