#include "ZenPhysics2D.h"

void ZenPhysics2D::RegisterPhysicalObject(PhysicalZenObject2D* physicalObject)
{
	PhysicalObjects.push_back(physicalObject);
}


void ZenPhysics2D::RemovingObjectFromPhysics(PhysicalZenObject2D* physicalObjectToRemove)
{
	for (auto itr = PhysicalObjects.begin(); itr != PhysicalObjects.end(); itr++)
	{
		if (*itr == physicalObjectToRemove)
		{
			PhysicalObjects.erase(itr);
			return;
		}
	}
}

void ZenPhysics2D::CalculatePhysics()
{
	for (PhysicalZenObject2D* physicalObject : PhysicalObjects)
	{
		physicalObject->CalculatePhysics();
	}
}

void ZenPhysics2D::Draw(RenderingStack* renderStack)
{
	for (PhysicalZenObject2D* physicalObject : PhysicalObjects)
	{
		RenderObject* physicalRenderObject = new RenderObject(physicalObject->zenShape->Draw(), 1000, 1);
		renderStack->renderQueue.push_back(physicalRenderObject);
	}
}

void ZenPhysics2D::RegisterCollider(CircleCollider2D* collider)
{
	colliders.push_back(collider);
}

void ZenPhysics2D::RemovingCollider(CircleCollider2D* collider)
{
	for (auto itr = colliders.begin(); itr != colliders.end(); itr++)
	{
		if (*itr == collider)
		{
			colliders.erase(itr);
			return;
		}
	}
}

void ZenPhysics2D::CalculateCollision()
{
	for (int i = 0; i < colliders.size(); i++)
	{
		CircleCollider2D* collider = colliders[i];
		for (int j = i + 1; j < colliders.size(); j++)
		{
			CircleCollider2D* otherCollider = colliders[j];
			collider->CheckCollision(otherCollider);
		}
	}
}

void ZenPhysics2D::DrawColliders(sf::RenderWindow* window)
{
	for (CircleCollider2D* collider : colliders)
	{
		window->draw(collider->circle);
	}
}

int ZenPhysics2D::GetPhysicsTimeStep()
{
	return physicsTimeStep;
}