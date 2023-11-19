// Copyright Z.Z. Zengine (c)

#include "PhysicalZenObject2D.h"
#include "../Structs/Vector2.h"

PhysicalZenObject2D::PhysicalZenObject2D(int inID, string inName, string enemySpritePath, sf::Vector2f startPosition, sf::Vector2f inSize) :ZenObject(inID, inName, inSize)
{
	zenShape = new ZenShape(3, "zenShape", sf::Vector2f(32, 32));
	zenShape->SetTexture(enemySpritePath);
	zenShape->SetPosition(startPosition);
	zenShape->SetSize(inSize);

	int radius = 2;
	collisionPoint1.setRadius(radius);
	collisionPoint1.setOrigin(radius, radius);
	collisionPoint1.setFillColor(sf::Color::Red);

	collisionPoint2.setRadius(radius);
	collisionPoint2.setOrigin(radius, radius);
	collisionPoint2.setFillColor(sf::Color::Red);
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
	CalculationColliderPush();

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
		CalculationCollisionPoints(collider);

		bounds = zenShape->GetGlobalBounds();

		switch (colliderPushState)
		{
			case ColliderPushState::Top:
			{
				PushTop(collider);
				break;
			}
			case ColliderPushState::Bottom:
			{
				PushBottom(collider);
				break;
			}
			case ColliderPushState::Left:
			{
				PushLeft(collider);
				break;
			}
			case ColliderPushState::Right:
			{
				PushRight(collider);
				break;
			}
			case ColliderPushState::TopLeft:
			{
				if (collisionPoint1.getPosition().y - collisionPoint2.getPosition().y > collider->size.y / 8)
				{
					PushLeft(collider);
					break;
				}
				else
				{
					PushTop(collider);
					break;
				}
			}
			case ColliderPushState::TopRight:
			{
				if (collisionPoint2.getPosition().y - collisionPoint1.getPosition().y > collider->size.y / 8)
				{
					PushRight(collider);
					break;
				}
				else
				{
					PushTop(collider);
					break;
				}
			}
			case ColliderPushState::BottomLeft:
			{
				if (collisionPoint2.getPosition().y - collisionPoint1.getPosition().y > collider->size.y / 8)
				{
					PushLeft(collider);
					break;
				}
				else
				{
					PushBottom(collider);
					break;
				}
			}
			case ColliderPushState::BottomRight:
			{
				if (collisionPoint1.getPosition().y - collisionPoint2.getPosition().y > collider->size.y / 8)
				{
					PushRight(collider);
					break;
				}
				else
				{
					PushBottom(collider);
					break;
				}
			}
		}
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

void PhysicalZenObject2D::CalculationCollisionPoints(Collider* collider)
{
	sf::FloatRect bounds = zenShape->GetGlobalBounds();

	bounds = zenShape->GetGlobalBounds();

	//top left corner
	if (collider->GetPosition()->y > zenShape->position.y
		&& collider->GetPosition()->y + collider->size.y > zenShape->position.y + zenShape->size.y
		&& zenShape->position.x < collider->GetPosition()->x
		&& zenShape->position.x + zenShape->size.x > collider->GetPosition()->x)
	{
		positionPoint1 = sf::Vector2f(collider->GetPosition()->x, zenShape->position.y + zenShape->size.y);
		positionPoint2 = sf::Vector2f(zenShape->position.x + zenShape->size.x, collider->GetPosition()->y);

		colliderPushState = ColliderPushState::TopLeft;
	}
	//top right corner
	else if (collider->GetPosition()->y > zenShape->position.y
		&& collider->GetPosition()->y + collider->size.y > zenShape->position.y + zenShape->size.y
		&& zenShape->position.x < collider->GetPosition()->x + collider->size.x
		&& zenShape->position.x + zenShape->size.x > collider->GetPosition()->x + collider->size.x)
	{
		positionPoint1 = sf::Vector2f(zenShape->position.x, collider->GetPosition()->y);
		positionPoint2 = sf::Vector2f(collider->GetPosition()->x + collider->size.x, zenShape->position.y + zenShape->size.y);

		colliderPushState = ColliderPushState::TopRight;
	}
	//bottom left corner
	else if (zenShape->position.y > collider->GetPosition()->y
		&& zenShape->position.y + zenShape->size.y > collider->GetPosition()->y + collider->size.y
		&& zenShape->position.x < collider->GetPosition()->x
		&& zenShape->position.x + zenShape->size.x > collider->GetPosition()->x)
	{
		positionPoint1 = sf::Vector2f(collider->GetPosition()->x, zenShape->position.y);
		positionPoint2 = sf::Vector2f(zenShape->position.x + zenShape->size.x, collider->GetPosition()->y + collider->size.y);

		colliderPushState = ColliderPushState::BottomLeft;
	}
	//bottom right corner
	else if (zenShape->position.y > collider->GetPosition()->y
		&& zenShape->position.y + zenShape->size.y > collider->GetPosition()->y + collider->size.y
		&& zenShape->position.x > collider->GetPosition()->x
		&& zenShape->position.x + zenShape->size.x > collider->GetPosition()->x + collider->size.x)
	{
		positionPoint1 = sf::Vector2f(zenShape->position.x, collider->GetPosition()->y + collider->size.y);
		positionPoint2 = sf::Vector2f(collider->GetPosition()->x + collider->size.x, zenShape->position.y);

		colliderPushState = ColliderPushState::BottomRight;
	}
	//top
	else if (collider->GetPosition()->y > zenShape->position.y
		&& zenShape->position.y + zenShape->size.y < collider->GetPosition()->y + collider->size.y)
	{
		if (bounds.left < collider->GetPosition()->x)
		{
			positionPoint1 = sf::Vector2f(bounds.left + bounds.width, collider->GetPosition()->y);
			positionPoint2 = sf::Vector2f(bounds.left + bounds.width, collider->GetPosition()->y);
		}
		else if (bounds.left + bounds.width > collider->GetPosition()->x + collider->size.x)
		{
			positionPoint1 = sf::Vector2f(bounds.left, collider->GetPosition()->y);
			positionPoint2 = sf::Vector2f(bounds.left, collider->GetPosition()->y);
		}
		else
		{
			positionPoint1 = sf::Vector2f(bounds.left + bounds.width, collider->GetPosition()->y);
			positionPoint2 = sf::Vector2f(bounds.left, collider->GetPosition()->y);
		}

		colliderPushState = ColliderPushState::Top;
	}
	//bottom
	else if (collider->GetPosition()->y < zenShape->GetPosition().y
		&& collider->GetPosition()->y + collider->size.y < zenShape->GetPosition().y + zenShape->GetSize().y)
	{
		if (bounds.left < collider->GetPosition()->x)
		{
			positionPoint1 = sf::Vector2f(bounds.left + bounds.width, collider->GetPosition()->y + collider->size.y);
			positionPoint2 = sf::Vector2f(bounds.left + bounds.width, collider->GetPosition()->y + collider->size.y);
		}
		else if (bounds.left + bounds.width > collider->GetPosition()->x + collider->size.x)
		{
			positionPoint1 = sf::Vector2f(bounds.left, collider->GetPosition()->y + collider->size.y);
			positionPoint2 = sf::Vector2f(bounds.left, collider->GetPosition()->y + collider->size.y);
		}
		else
		{
			positionPoint1 = sf::Vector2f(bounds.left + bounds.width, collider->GetPosition()->y + collider->size.y);
			positionPoint2 = sf::Vector2f(bounds.left, collider->GetPosition()->y + collider->size.y);
		}

		colliderPushState = ColliderPushState::Bottom;
	}
	//left
	else if (bounds.left < collider->GetPosition()->x
		&& bounds.left + bounds.width < collider->GetPosition()->x + collider->size.x)
	{
		if (collider->GetPosition()->y < bounds.top)
		{
			positionPoint1 = sf::Vector2f(bounds.left + bounds.width, bounds.top);
			positionPoint2 = sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);
		}
		else
		{
			positionPoint1 = sf::Vector2f(bounds.left + bounds.width, collider->GetPosition()->y);
			positionPoint2 = sf::Vector2f(bounds.left + bounds.width, collider->GetPosition()->y + collider->size.y);
		}

		colliderPushState = ColliderPushState::Left;
	}
	//right
	else if (bounds.left > collider->GetPosition()->x
		&& bounds.left + bounds.width > collider->GetPosition()->x + collider->size.x)
	{
		if (collider->GetPosition()->y < bounds.top)
		{
			positionPoint1 = sf::Vector2f(bounds.left, bounds.top);
			positionPoint2 = sf::Vector2f(bounds.left, bounds.top + bounds.height);
		}
		else
		{
			positionPoint1 = sf::Vector2f(bounds.left, collider->GetPosition()->y);
			positionPoint2 = sf::Vector2f(bounds.left, collider->GetPosition()->y + collider->size.y);
		}

		colliderPushState = ColliderPushState::Right;
	}

	collisionPoint1.setPosition(positionPoint1);
	collisionPoint2.setPosition(positionPoint2);
	
}

void PhysicalZenObject2D::PushTop(Collider* collider)
{
	zenShape->SetPosition(sf::Vector2f(zenShape->GetPosition().x, collider->GetPosition()->y - zenShape->GetSize().y));
	clollisionNormalVector.y = 1;
	canUseGravity = false;
}

void PhysicalZenObject2D::PushBottom(Collider* collider)
{
	velocity.y = 0.0f;
	zenShape->SetPosition(sf::Vector2f(zenShape->GetPosition().x, collider->GetPosition()->y + collider->size.y + COLLIDER_PUSH_2));
	clollisionNormalVector.y = -1;
}

void PhysicalZenObject2D::PushRight(Collider* collider)
{
	velocity.x = 0.0f;
	zenShape->SetPosition(sf::Vector2f(collider->GetPosition()->x + collider->size.x + COLLIDER_PUSH_2, zenShape->GetPosition().y));
	clollisionNormalVector = Vector2(-1, 0);
}

void PhysicalZenObject2D::PushLeft(Collider* collider)
{
	velocity.x = 0.0f;
	zenShape->SetPosition(sf::Vector2f(collider->GetPosition()->x - zenShape->GetSize().x - COLLIDER_PUSH_2, zenShape->GetPosition().y));
	clollisionNormalVector = Vector2(1, 0);
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