#include "UIButton.h"

UIButton::UIButton(Vector2 positionIn, Vector2 sizeIn): Widget(positionIn, sizeIn)
{
	background = new sf::Texture();
	highlight = new sf::Texture();
}

void UIButton::OnMouseHover()
{
	if (state != Widget::MouseHover)
	{
		state = Widget::MouseHover;
		OnMouseHoverEvent.Invoke();

		if (isHighlightSet)
		{
			zenShape->SetTexture(highlight);
		}
	}
}

void UIButton::OnMouseUnHover()
{
	if (state != Widget::UnHover)
	{
		state = Widget::UnHover;
		OnMouseUnHoverEvent.Invoke();

		if (isHighlightSet)
		{
			zenShape->SetTexture(background);
		}
	}
}

void UIButton::OnMousePressed()
{
	OnMouseDownEvent.Invoke();
}

void UIButton::OnMouseUnPressed()
{
	OnMouseUpEvent.Invoke();
}

void UIButton::Draw(RenderingStack* renderStack, string texturePath, int rendererObjectId, string rendererObjectName)
{
	zenShape = new ZenShape(12, rendererObjectName, sf::Vector2f(GetSize().x, GetSize().y));
	zenShape->SetSize(sf::Vector2f(GetSize().x, GetSize().y));

	background->loadFromFile(texturePath);

	zenShape->SetTexture(background);
	zenShape->SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y));

	renderobject = new RenderObject(zenShape->Draw(), 1, 2);
	
	renderStack->renderQueue.push_back(renderobject);
}

void UIButton::SetHighlight(string texturePath)
{
	isHighlightSet = true;
	highlight->loadFromFile(texturePath);
}