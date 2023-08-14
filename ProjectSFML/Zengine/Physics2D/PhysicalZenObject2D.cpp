#include "PhysicalZenObject2D.h"
#include "../Colliders/Collider.h"

PhysicalZenObject2D::PhysicalZenObject2D(int inID, string inName, string enemySpritePath, sf::Vector2f startPosition, sf::Vector2f inSize) :ZenObject(inID, inName, inSize)
{
	velocity = new Vector2(0, 0);
	transposition = new Vector2(0.1, 0);
	acceleration = new Vector2(0, 0);
	force = new Vector2(0, 0);

	zenShape = new ZenShape(3, "zenShape", sf::Vector2f(32, 32));
	zenShape->SetTexture(enemySpritePath);
	zenShape->SetPosition(startPosition);
	zenShape->SetSize(inSize);
}

void PhysicalZenObject2D::SetCollider(class Collider* collider)
{
	this->collider = collider;
	collider->OnCollisionStart.AddListener(&PhysicalZenObject2D::HandleCollisionStart, this);
	collider->OnCollisionEnd.AddListener(&PhysicalZenObject2D::HandleCollisionEnd, this);
}

void PhysicalZenObject2D::HandleCollisionStart(Collider* other)
{
	if (other->GetOwner()->Name == "Ground")
	{
		canUseGravity = false;
	}
}

void PhysicalZenObject2D::HandleCollisionEnd(Collider* other)
{
	if (other->GetOwner()->Name == "Ground")
	{
		canUseGravity = true;
	}
}

void PhysicalZenObject2D::CalculatePhysics()
{
	transposition->x = velocity->x;
	transposition->y = velocity->y;

	if (velocity->x<0 && transposition->x > -0.5)
	{
		ResettingVariables();
		return;
	}

	if (velocity->y<0 && transposition->y > -0.5)
	{
		ResettingVariables();
		return;
	}

	if (velocity->x>0 && transposition->x < 0.5)
	{
		ResettingVariables();
		return;
	}

	if (velocity->y > 0 && transposition->y < 0.5)
	{
		ResettingVariables();
		return;
	}

	zenShape->MoveObject(sf::Vector2f(transposition->x, 0));

	if (collider != nullptr)
	{
		if (canUseGravity || collider->GetOwner()->isJump)
		{
			zenShape->MoveObject(sf::Vector2f(0, transposition->y));
		}
	}

	velocity->x = (1.0 - fakeDrag) * velocity->x;

	velocity->y = (1.0 - fakeDrag) * velocity->y + gravity;
}

void PhysicalZenObject2D::ResettingVariables()
{
	transposition->SetVector2(0, 0);
	velocity->y = 0;
}

void PhysicalZenObject2D::AddForce(float massIn, Vector2 forceIN, float time)
{
	mass = massIn;
	force = &forceIN;

	acceleration->x = force->x / mass;
	acceleration->y = force->y / mass;

	float sx = (acceleration->x * time * time) / 2;
	float sy = (acceleration->y * time * time) / 2;

	velocity->x = sx / time;
	velocity->y = sy / time;
}

Vector2* PhysicalZenObject2D::GetTransposition()
{
	return transposition;
}

Vector2* PhysicalZenObject2D::GetVelocity()
{
	return velocity;
}

void  PhysicalZenObject2D::SetGravity(float gravity)
{
	this->gravity = gravity;
}

float PhysicalZenObject2D::GetGravity()
{
	return gravity;
}