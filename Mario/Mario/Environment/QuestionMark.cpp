#include "QuestionMark.h"
#include <Zengine/Physics2D/ZenPhysics2D.h>
#include <Zengine/Colliders/BoxCollider2D.h>
#include <Zengine/Colliders/Collider.h>
#include <Zengine/Structs/Vector2.h>
#include <Zengine/Animation/Animator.h>
#include <Zengine/Animation/Animation.h>
#include <Zengine/Animation/AnimationDefinitionManager.h>

QuestionMark::QuestionMark(int IDIn, string NameIn, string CoinPath, sf::Vector2f position)
{
	zenShape = new ZenShape(IDIn, NameIn, sf::Vector2f(32, 32));
	zenShape->SetTexture(CoinPath);
	zenShape->SetPosition(position);
	zenShape->SetSize(sf::Vector2f(32, 32));

	SetCollider(Vector2(position.x, position.y));

	animator = new Animator(zenShape);
	animation = new Animation(AnimationDefinitionManager::Get()->GetAnimationDefinition("QuestionMark"));
	animationId = animator->AddAnimation(animation);
	animator->SetCurrentAnimation(animationId);
	animator->Play();
}

QuestionMark::~QuestionMark()
{
	renderStack->RemoveFromRenderLayers(questionMarkRenderObject);
	delete questionMarkRenderObject;
	ZenPhysics2D::Get()->UnregisterCollider(boxCollider);
	delete boxCollider;
	animator->~Animator();
}

void QuestionMark::Draw(RenderingStack* renderStack)
{
	ZenPhysics2D::Get()->RegisterCollider(boxCollider);
	this->renderStack = renderStack;
	questionMarkRenderObject = new RenderObject(zenShape->Draw(), 100, 1);
	renderStack->renderQueue.push_back(questionMarkRenderObject);
}

void QuestionMark::SetCollider(Vector2 position)
{
	boxCollider = new BoxCollider2D(position, Vector2(32,32), zenShape, Collider::ColliderTags::QUESTION_MARK);
	listenerIndexStart = boxCollider->OnCollisionStart.AddListener(&QuestionMark::HandleCollisionStart, this);
	ZenPhysics2D::Get()->RegisterCollider(boxCollider);
}

void QuestionMark::HandleCollisionStart(Collider* other)
{
	if (other->GetOwner()->name == "Mario")
	{
		renderStack->RemoveFromRenderLayers(questionMarkRenderObject);
		ZenPhysics2D::Get()->UnregisterCollider(boxCollider);
	}
}