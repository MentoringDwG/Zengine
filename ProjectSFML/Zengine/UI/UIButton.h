#pragma once

#include "Widget.h"
#include "../Renderer/Renderer.h"
#include "../ZenObject/ZenShape.h"

class UIButton: public Widget
{
public:
	UIButton(Vector2 positionIn, Vector2 sizeIn);

	virtual void OnMouseHover() override;
	virtual void OnMouseUnHover() override;
	virtual void OnMousePressed() override;
	virtual void OnMouseUnPressed() override;

	void Draw(RenderingStack* renderStack, string texturePath, int rendererObjectId, string rendererObjectName);
	void SetHighlight(string texturePath);

private:
	sf::Texture* background;
	sf::Texture* highlight;
	sf::Color color;
	ZenShape* zenShape = nullptr;
	RenderObject* renderobject = nullptr;
};

