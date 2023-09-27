#include "UIButton.h"

UIButton::UIButton(Vector2 positionIn, Vector2 sizeIn): Widget(positionIn, sizeIn)
{
	background = new sf::Texture();
	highlight = new sf::Texture();
}

UIButton::~UIButton()
{
	delete background;
	delete highlight;
	delete zenShape;
	delete renderobject;
}

void UIButton::OnMouseHover()
{
	if (state != Widget::State::MouseHover)
	{
		state = Widget::State::MouseHover;
		OnMouseHoverEvent.Invoke();

		if (isHighlightSet)
		{
			zenShape->SetTexture(highlight);
		}
	}
}

void UIButton::OnMouseUnHover()
{
	if (state != Widget::State::UnHover)
	{
		state = Widget::State::UnHover;
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

void UIButton::Draw(RenderingStack* renderStack, string texturePath, sf::IntRect TextureRect, int rendererObjectId, string rendererObjectName)
{
	zenShape = new ZenShape(12, rendererObjectName, sf::Vector2f(GetSize().x, GetSize().y));
	zenShape->SetSize(sf::Vector2f(GetSize().x, GetSize().y));

	background->loadFromFile(texturePath);

	zenShape->SetTexture(background);
	zenShape->Draw()->setTextureRect(TextureRect);
	zenShape->SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y));

	renderobject = new RenderObject(zenShape->Draw(), 1, 2);
	
	renderStack->renderQueueUI.push_back(renderobject);
}

void UIButton::SetHighlight(string texturePath)
{
	isHighlightSet = true;
	highlight->loadFromFile(texturePath);
}

void UIButton::SetIntRect(sf::IntRect TextureRect)
{
	zenShape->Draw()->setTextureRect(TextureRect);
}

sf::IntRect UIButton::GetIntRect()
{
	return zenShape->Draw()->getTextureRect();
}