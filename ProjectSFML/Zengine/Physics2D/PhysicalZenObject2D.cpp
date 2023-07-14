#include "PhysicalZenObject2D.h"

enum PhysicalZenObject2D::ForceDirection
{
	left = -1,
	right = 1
};

PhysicalZenObject2D::PhysicalZenObject2D(int IDIn, string NameIn, string enemySpritePath, sf::Vector2f startPosition) :ZenObject(IDIn, NameIn)
{
	velocity = new Vector2(0, 0);
	transposition = new Vector2(0.1, 0);
	acceleration = new Vector2(0, 0);

	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(enemySpritePath);

	rectangleShape = new sf::RectangleShape;
	rectangleShape->setPosition(startPosition);
	rectangleShape->setSize(sf::Vector2f(32.0f, 32.0f));
	rectangleShape->setTexture(texture);
}

void PhysicalZenObject2D::CalculatePhysics()
{
	transposition->x = velocity->x - (slowdownPercentage * velocity->x / 100);

	if (forceDirection==left && transposition->x > -0.5)
	{
		ResettingVariables();
		return;
	}

	if (forceDirection == right && transposition->x < 0.5)
	{
		ResettingVariables();
		return;
	}

	rectangleShape->move(sf::Vector2f(transposition->x, 0.0f));
	velocity->x= velocity->x - (slowdownPercentage * velocity->x / 100);
	slowdownPercentage = slowdownPercentage + 0.1;
}

void PhysicalZenObject2D::ResettingVariables()
{
	transposition->SetVector2(0, 0);
	slowdownPercentage = 1;
}

//direction: -1 - left, 1 -right
void PhysicalZenObject2D::AddForce(float massIn, float forceIN, float time, int direction)
{
	if (direction == -1) forceDirection = left;
	if (direction == 1) forceDirection = right;

	mass = massIn;
	force = forceIN*direction;

	acceleration->x = force / mass;

	float s = (acceleration->x * time * time) / 2;

	velocity->x = s / time;
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
	return transposition->x;
}