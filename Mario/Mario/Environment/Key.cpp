#include "Key.h"
#include <Zengine/Physics2D/ZenPhysics2D.h>
#include <Zengine/Colliders/CircleCollider2D.h>
#include <Zengine/Colliders/Collider.h>
#include <Zengine/Structs/Vector2.h>
#include <Zengine/Animation/Animator.h>
#include <Zengine/Animation/Animation.h>
#include <Zengine/Animation/AnimationDefinitionManager.h>

#include "../UIinGame/KeyPanel.h"


Key::Key(int IDIn, string NameIn, string CoinPath, sf::Vector2f position, class KeyPanel* keyPanel)
{
	this->keyPanel = keyPanel;

	zenShape = new ZenShape(IDIn, NameIn, sf::Vector2f(32, 32));
	zenShape->SetTexture(CoinPath);
	zenShape->SetPosition(position);
	zenShape->SetSize(sf::Vector2f(32, 32));

	SetCollider(Vector2(position.x, position.y), 20);

	animator = new Animator(zenShape);
	animation = new Animation(AnimationDefinitionManager::Get()->GetAnimationDefinition("Key"));
	animationId = animator->AddAnimation(animation);
	animator->SetCurrentAnimation(animationId);
	animator->Play();
}

Key::~Key()
{
	renderStack->RemoveFromRenderLayers(keyRenderObject);
	delete keyRenderObject;
	ZenPhysics2D::Get()->UnregisterCollider(collider);
	delete collider;
	animator->~Animator();
}

void Key::Draw(RenderingStack* renderStack)
{
	ZenPhysics2D::Get()->RegisterCollider(collider);
	this->renderStack = renderStack;
	keyRenderObject = new RenderObject(zenShape->Draw(), 100, 1);
	renderStack->renderQueue.push_back(keyRenderObject);
}

void Key::SetCollider(Vector2 position, float radius)
{
	collider = new CircleCollider2D(position, radius, zenShape, Collider::ColliderTags::COIN);
	listenerIndexStart = collider->OnCollisionStart.AddListener(&Key::HandleCollisionStart, this);
	ZenPhysics2D::Get()->RegisterCollider(collider);
}

void Key::HandleCollisionStart(Collider* other)
{
	if (other->GetOwner()->name == "Mario")
	{
		renderStack->RemoveFromRenderLayers(keyRenderObject);
		ZenPhysics2D::Get()->UnregisterCollider(collider);

		keyPanel->UpdateKeysState();
	}
}