// Copyright Z.Z. Zengine (c)

#include "PhysicalZenObject2D.h"
#include "../Structs/Vector2.h"

PhysicalZenObject2D::PhysicalZenObject2D(int inID, string inName, string enemySpritePath, sf::Vector2f startPosition, sf::Vector2f inSize) :ZenObject(inID, inName, inSize)
{
	zenShape = new ZenShape(3, "zenShape", sf::Vector2f(32, 32));
	zenShape->SetTexture(enemySpritePath);
	zenShape->SetPosition(startPosition);
	zenShape->SetSize(inSize);
}

PhysicalZenObject2D::~PhysicalZenObject2D()
{
	delete zenShape;
	delete collider;
}

void PhysicalZenObject2D::SetCollider(class Collider* collider)
{
	this->collider = collider;
	handleCollisionStartId = collider->OnCollisionStart.AddListener(&PhysicalZenObject2D::HandleCollisionStart, this);
	handleCollisionEndId = collider->OnCollisionEnd.AddListener(&PhysicalZenObject2D::HandleCollisionEnd, this);
}

void PhysicalZenObject2D::HandleCollisionStart(Collider* other)
{
	CalculationColliderPush();

	for (auto itr = collisionColliders[other->tag].begin(); itr != collisionColliders[other->tag].end(); itr++)
	{
		if (*itr == other)
		{
			return;
		}
	}
	collisionColliders[other->tag].push_back(other);
}

void PhysicalZenObject2D::HandleCollisionEnd(Collider* other)
{
	for (auto itr = collisionColliders[other->tag].begin(); itr != collisionColliders[other->tag].end(); itr++)
	{
		if (*itr == other)
		{
			collisionColliders[other->tag].erase(itr);
			return;
		}
	}
	
	if (collisionColliders[Collider::ColliderTags::GROUND].size() == 0)
	{
		canUseGravity = true;
	}
}

void PhysicalZenObject2D::CalculatePhysics()
{
	//CalculationColliderPush();

	transposition.x = velocity.x;
	transposition.y = velocity.y;

	if (velocity.x < 0 && transposition.x > -0.5)
	{
		ResettingVariables();
		return;
	}

	if (velocity.y < 0 && transposition.y > -0.5)
	{
		ResettingVariables();
		return;
	}

	if (velocity.x > 0 && transposition.x < 0.5)
	{
		ResettingVariables();
		return;
	}

	if (velocity.y > 0 && transposition.y < 0.5)
	{
		ResettingVariables();
		return;
	}

	zenShape->MoveObject(sf::Vector2f(transposition.x, 0));

	if (collider != nullptr)
	{
		if (canUseGravity || collider->GetOwner()->isJump)
		{
			zenShape->MoveObject(sf::Vector2f(0, transposition.y));
		}
	}

	velocity.x = (float)((1.0 - fakeDrag) * velocity.x);

	velocity.y = (float)((1.0 - fakeDrag) * velocity.y + gravity);
}

void PhysicalZenObject2D::ResettingVariables()
{
	transposition.SetVector2(0, 0);
	velocity.y = 0;
}

void PhysicalZenObject2D::AddForce(float massIn, Vector2 forceIN, float time)
{
	mass = massIn;
	force = forceIN;

	acceleration.x = force.x / mass;
	acceleration.y = force.y / mass;

	float sx = (acceleration.x * time * time) / 2;
	float sy = (acceleration.y * time * time) / 2;

	velocity.x = sx / time;
	velocity.y = sy / time;
}

void PhysicalZenObject2D::CalculationColliderPush()
{
	std::vector<Collider*> colliders = collisionColliders[Collider::ColliderTags::GROUND];
	std::vector<Collider*> confiners = collisionColliders[Collider::ColliderTags::CONFINER];

	Collider* collider = colliders[0];
	Collider* confiner = confiners[0];
	sf::FloatRect bounds = zenShape->GetGlobalBounds();

	for (int i = 0; i < colliders.size(); i++)
	{
		collider = colliders[i];
		bounds = zenShape->GetGlobalBounds();

		sf::Vector2f pushPosition = sf::Vector2f(zenShape->position.x, zenShape->position.y);

		//top
		if (collider->GetPosition()->y > zenShape->position.y
			&& collider->GetPosition()->y < zenShape->position.y + zenShape->size.y
			&& collider->GetPosition()->x < zenShape->position.x + zenShape->size.x
			&& collider->GetPosition()->x + collider->size.x > zenShape->position.x)
		{
			pushPosition.y = collider->GetPosition()->y - zenShape->GetSize().y;
			zenShape->SetPosition(pushPosition);
			clollisionNormalVector = Vector2(0, -1);
			canUseGravity = false;
			return;
		}

		//bottom
		if (collider->GetPosition()->y + collider->size.y + COLLIDER_PUSH_2 > zenShape->previousPosition.y
			&& collider->GetPosition()->y + collider->size.y + COLLIDER_PUSH_X < zenShape->position.y + COLLIDER_PUSH_Y)
		{
			velocity.y = 0;
			pushPosition.y = collider->GetPosition()->y + collider->size.y + COLLIDER_PUSH_2;
			zenShape->SetPosition(pushPosition);
			clollisionNormalVector = Vector2(0, 1);
			return;
		}

		//left
		if (bounds.left < collider->GetPosition()->x
			&& bounds.left + bounds.width < collider->GetPosition()->x + collider->size.x
			&& collider->GetPosition()->y < bounds.top + bounds.height
			&& collider->GetPosition()->y+collider->size.y >= bounds.top
			)
		{
			velocity.x = 0.0f;
			pushPosition.x = collider->GetPosition()->x - bounds.width - COLLIDER_PUSH_2;
			clollisionNormalVector = Vector2(1, 0);
		}

		//right
		if (bounds.left > collider->GetPosition()->x
			&& bounds.left + bounds.width > collider->GetPosition()->x + collider->size.x
			&& collider->GetPosition()->y < bounds.top + bounds.height
			&& collider->GetPosition()->y + collider->size.y >= bounds.top
			)
		{
			velocity.x = 0.0f;
			pushPosition.x = collider->GetPosition()->x + collider->size.x + COLLIDER_PUSH_2;
			clollisionNormalVector = Vector2(-1, 0);
		}

		zenShape->SetPosition(pushPosition);
		
	}

	for (int i = 0; i < confiners.size(); i++)
	{
		confiner = confiners[i];
		bounds = zenShape->GetGlobalBounds();

		if (bounds.left < confiner->GetPosition()->x
			&& bounds.left + bounds.width < confiner->GetPosition()->x + confiner->size.x
			&& bounds.top < confiner->GetPosition()->y + confiner->size.y
			&& bounds.top + bounds.height > confiner->GetPosition()->y
			)
		{
			velocity.x = 0.0f;
			zenShape->SetPosition(sf::Vector2f(confiner->GetPosition()->x - bounds.width - COLLIDER_PUSH_2, bounds.top));
			clollisionNormalVector = Vector2(1, 0);
		}

		if (bounds.left > confiner->GetPosition()->x
			&& bounds.left + bounds.width > confiner->GetPosition()->x + confiner->size.x
			&& bounds.top < confiner->GetPosition()->y + confiner->size.y
			&& bounds.top + bounds.height > confiner->GetPosition()->y
			)
		{
			velocity.x = 0.0f;
			zenShape->SetPosition(sf::Vector2f(confiner->GetPosition()->x + confiner->size.x + COLLIDER_PUSH_2, bounds.top));
			clollisionNormalVector = Vector2(-1, 0);
		}
	}
}

Vector2* PhysicalZenObject2D::GetTransposition()
{
	return &transposition;
}

Vector2* PhysicalZenObject2D::GetVelocity()
{
	return &velocity;
}

void  PhysicalZenObject2D::SetGravity(float gravity)
{
	this->gravity = gravity;
}

float PhysicalZenObject2D::GetGravity()
{
	return gravity;
}

void PhysicalZenObject2D::ClearCollisionColliders()
{
	collisionColliders.clear();
	canUseGravity = true;
}