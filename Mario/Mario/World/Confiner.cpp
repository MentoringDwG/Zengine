#include "Confiner.h"
#include <Zengine/Colliders/BoxCollider2D.h>
#include <Zengine/ZenObject/ZenObject.h>
#include <Zengine/Physics2D/ZenPhysics2D.h>
#include <Zengine/StateMachine/StateMachine.h>

Confiner::Confiner(Vector2 size, Vector2 positionLeftCollider, Vector2 positionRightCollider)
{
	leftConfiner = new ZenObject(21, "LeftConfiner", sf::Vector2f(size.x, size.y));
	boxColliderLeft = new BoxCollider2D(positionLeftCollider, size, leftConfiner, Collider::ColliderTags::CONFINER);
	ZenPhysics2D::Get()->RegisterCollider(boxColliderLeft);

	rightConfiner = new ZenObject(21, "RightConfiner", sf::Vector2f(size.x, size.y));
	boxColliderRight = new BoxCollider2D(positionRightCollider, size, rightConfiner, Collider::ColliderTags::CONFINER);
	ZenPhysics2D::Get()->RegisterCollider(boxColliderRight);
}