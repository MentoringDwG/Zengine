#include "PhysicalZenObject2D.h"

void PhysicalZenObject2D::CalculatePhysics()
{
	//You have to think about it
}

void PhysicalZenObject2D::Draw(RenderingStack* renderStack)
{
	physicalRenderObject = new RenderObject();
	physicalRenderObject->drawable = rectangleShape;
	physicalRenderObject->zOrder = 1000;
	physicalRenderObject->layerId = 1;

	renderStack->renderQueue.push_back(physicalRenderObject);
}