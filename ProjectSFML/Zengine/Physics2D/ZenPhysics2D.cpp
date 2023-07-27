#include "ZenPhysics2D.h"

ZenPhysics2D ZenPhysics2D::instance;

void ZenPhysics2D::RegisterPhysicalObject(PhysicalZenObject2D* physicalObject)
{
	physicalObjects.push_back(physicalObject);
}

void ZenPhysics2D::RemovingObjectFromPhysics(PhysicalZenObject2D* physicalObjectToRemove)
{
	for (auto itr = physicalObjects.begin(); itr != physicalObjects.end(); itr++)
	{
		if (*itr == physicalObjectToRemove)
		{
			physicalObjects.erase(itr);
			return;
		}
	}
}

void ZenPhysics2D::CalculatePhysics()
{
	for (PhysicalZenObject2D* physicalObject : physicalObjects)
	{
		physicalObject->CalculatePhysics();
	}
}

void ZenPhysics2D::Draw(RenderingStack* renderStack)
{
	for (PhysicalZenObject2D* physicalObject : physicalObjects)
	{
		RenderObject* physicalRenderObject = new RenderObject(physicalObject->zenShape->Draw(), 1000, 1);
		renderStack->renderQueue.push_back(physicalRenderObject);
	}
}

void ZenPhysics2D::RegisterCollider(CircleCollider2D* collider)
{
	circleColliders.push_back(collider);
}

void ZenPhysics2D::RegisterCollider(BoxCollider2D* collider)
{
	boxColliders.push_back(collider);
}

void ZenPhysics2D::UnregisterCollider(CircleCollider2D* collider)
{
	for (auto itr = circleColliders.begin(); itr != circleColliders.end(); itr++)
	{
		if (*itr == collider)
		{
			circleColliders.erase(itr);
			return;
		}
	}
}

void ZenPhysics2D::UnregisterCollider(BoxCollider2D* collider)
{
	for (auto itr = boxColliders.begin(); itr != boxColliders.end(); itr++)
	{
		if (*itr == collider)
		{
			boxColliders.erase(itr);
			return;
		}
	}
}

void ZenPhysics2D::CalculateCollision()
{
	for (int i = 0; i < circleColliders.size(); i++)
	{
		CircleCollider2D* collider = circleColliders[i];
		for (int j = 0; j < circleColliders.size(); j++)
		{
			CircleCollider2D* otherCollider = circleColliders[j];
			collider->CheckCircleCollision(otherCollider);
		}
	}

	for (int i = 0; i < boxColliders.size(); i++)
	{
		BoxCollider2D* collider = boxColliders[i];
		for (int j = 0; j < boxColliders.size(); j++)
		{
			BoxCollider2D* otherCollider = boxColliders[j];
			collider->CheckBoxCollision(otherCollider);
		}
	}

	for (int i = 0; i < circleColliders.size(); i++)
	{
		CircleCollider2D* collider = circleColliders[i];
		for (int j = 0; j < boxColliders.size(); j++)
		{
			BoxCollider2D* otherCollider = boxColliders[j];
			collider->CheckBoxCollision(otherCollider);
		}
	}
}

void ZenPhysics2D::DrawColliders(sf::RenderWindow* window)
{
	for (CircleCollider2D* collider : circleColliders)
	{
		window->draw(collider->debugCircle);
	}

	for (BoxCollider2D* collider : boxColliders)
	{
		window->draw(collider->debugRectangleShape);
	}
}

int ZenPhysics2D::GetPhysicsTimeStep()
{
	return physicsTimeStep;
}
