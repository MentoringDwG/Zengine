// Copyright Z.Z. Zengine (c)

#pragma once

#include "Widget.h"
#include "../Renderer/Renderer.h"
#include "../ZenObject/ZenShape.h"

class UIButton: public Widget
{
public:
	UIButton(Vector2 positionIn, Vector2 sizeIn);
	~UIButton();

	virtual void OnMouseHover() override;
	virtual void OnMouseUnHover() override;
	virtual void OnMousePressed() override;
	virtual void OnMouseUnPressed() override;

	void Draw(RenderingStack* renderStack, string texturePath, sf::IntRect TextureRect, int rendererObjectId, string rendererObjectName);
	void SetHighlight(string texturePath);
	void SetIntRect(sf::IntRect TextureRect);
	sf::IntRect GetIntRect();

private:
	sf::Texture* background = nullptr;
	sf::Texture* highlight = nullptr;
	ZenShape* zenShape = nullptr;
	RenderObject* renderobject = nullptr;

	bool isHighlightSet = false;
};

