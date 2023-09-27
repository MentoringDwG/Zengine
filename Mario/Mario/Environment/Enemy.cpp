#include "Enemy.h"
#include "../UIinGame/HeartsPanel.h"
#include "Zengine/Colliders/CircleCollider2D.h"
#include "Zengine/Colliders/Collider.h"
#include "Zengine/Physics2D/ZenPhysics2D.h"

Enemy::Enemy(int inID, string inName, string enemySpritePath, sf::Vector2f startPosition, sf::Vector2f inSize, HeartsPanel* heartsPanelIn)
{
	heartsPanel = heartsPanelIn;
	physicalZenObject = new PhysicalZenObject2D(inID, inName, enemySpritePath, startPosition, inSize);
	ZenPhysics2D::Get()->RegisterPhysicalObject(physicalZenObject);

	Vector2 position(startPosition.x, startPosition.y);
	circleCollider = new CircleCollider2D(position, 20, physicalZenObject->zenShape, Collider::ColliderTags::ENEMY);
	circleCollider->OnCollisionStart.AddListener(&Enemy::HandleCollisionStart, this);
	circleCollider->OnCollisionEnd.AddListener(&Enemy::HandleCollisionEnd, this);
	ZenPhysics2D::Get()->RegisterCollider(circleCollider);
}

Enemy::~Enemy()
{
	delete heartsPanel;
	delete physicalZenObject;
	delete circleCollider;
}

void Enemy::Update()
{
	colliderPosition = physicalZenObject->zenShape->GetPosition();

	circleCollider->SetPosition(colliderPosition);
}

void Enemy::HandleCollisionStart(Collider* other)
{
	if (other->GetOwner()->name == "Mario")
	{
		if (isCollisionWithCharacter == false)
		{
			heartsPanel->UpdateHeartsState();
			isCollisionWithCharacter = true;
		}
	}
}

void Enemy::HandleCollisionEnd(Collider* other)
{
	if (other->GetOwner()->name == "Mario")
	{
		isCollisionWithCharacter = false;
	}
}

void Enemy::AddForce(float mass, Vector2 force, float time)
{
	physicalZenObject->AddForce(mass, force, time);
}

Vector2* Enemy::GetTransposition()
{
	return physicalZenObject->GetTransposition();
}

Vector2* Enemy::GetVelocity()
{
	return physicalZenObject->GetVelocity();
}