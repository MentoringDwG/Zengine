#include "ZenPhysics2D.h"

void ZenPhysics2D::RegisterPhysicalObject(PhysicalZenObject2D* physicalObject)
{
	PhysicalObjects.push_back(physicalObject);
}

void ZenPhysics2D::CalculatePhysics()
{
	for (PhysicalZenObject2D* physicalObject : PhysicalObjects)
	{
		physicalObject->CalculatePhysics();
	}
}

std::chrono::nanoseconds ZenPhysics2D::GetPhysicsTimeStep()
{
	return physicsTimeStep;
}