#include "Castle.h"
#include "Zengine/Colliders/BoxCollider2D.h"
#include "Zengine/ZenObject/ZenObject.h"
#include "Zengine/Physics2D/ZenPhysics2D.h"
#include "Zengine/StateMachine/StateMachine.h"

Castle::Castle(Vector2 size, Vector2 position, StateMachine* stateMachineIn) :ZenObject(20, "Castle", sf::Vector2f(size.x, size.y))
{
	stateMachine = stateMachineIn;

	boxCollider = new BoxCollider2D(position, size, this, Collider::ColliderTags::CASTLE);
	boxCollider->OnCollisionStart.AddListener(&Castle::HandleCollisionStart, this);
	boxCollider->OnCollisionEnd.AddListener(&Castle::HandleCollisionEnd, this);
	ZenPhysics2D::Get()->RegisterCollider(boxCollider);
}

void Castle::HandleCollisionStart(Collider* other)
{
	if (other->GetOwner()->name == MARIO && !isCollisionWithMario)
	{
		isCollisionWithMario = true;
		
		stateMachine->TransitionTo(State::WinState);
	}
}

void Castle::HandleCollisionEnd(Collider* other)
{
	if (other->GetOwner()->name == MARIO)
	{
		isCollisionWithMario = false;
	}
}