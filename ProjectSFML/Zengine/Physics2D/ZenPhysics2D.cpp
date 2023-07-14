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

int ZenPhysics2D::GetPhysicsTimeStep()
{
	return physicsTimeStep;
}