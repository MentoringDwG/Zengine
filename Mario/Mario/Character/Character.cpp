#include "Character.h"
#include <functional>
#include <Zengine/Structs/Vector2.h>
#include <Zengine/World/TextureAsset.h>
#include <Zengine/Renderer/Renderer.h>
#include <Zengine/Colliders/BoxCollider2D.h>
#include <Zengine/Physics2D/ZenPhysics2D.h>
#include <Zengine/Physics2D/PhysicalZenObject2D.h>
#include <Zengine/Animation/Animator.h>
#include <Zengine/Animation/Animation.h>
#include <Zengine/Animation/AnimationDefinitionManager.h>
#include <Zengine/Audio/AudioSystem.h>

Character::Character(std::string name, string Path, float playerMoveSpeed, class AudioSystem* audioSystem)
{
	this->audioSystem = audioSystem;

	inputHandler.SetName(name);
	inputHandler.SetOwningCharacter(this);

	SetTextureAsset(Path, name);

	moveSpeed = playerMoveSpeed;

	physicalZenObject2D = new PhysicalZenObject2D(0, name, Path, sf::Vector2f(200.0f, 0.0f), sf::Vector2f(32, 64));
	physicalZenObject2D->zenShape = new ZenShape(0, name, sf::Vector2f(32, 64));
	physicalZenObject2D->zenShape->SetPosition(sf::Vector2f(200.0f, 0.0f));
	physicalZenObject2D->zenShape->SetSize(sf::Vector2f(32, 64));

	SetCollider(Vector2(physicalZenObject2D->zenShape->GetPosition().x, physicalZenObject2D->zenShape->GetPosition().y), Vector2(32, 64));
	physicalZenObject2D->SetGravity(0.5);

	physicalZenObject2D->SetCollider(collider2D);
	ZenPhysics2D::Get()->RegisterPhysicalObject(physicalZenObject2D);

	animator = new Animator(physicalZenObject2D->zenShape);

	AnimationDefinitionManager::Get()->AddAnimationDefinition("Json/Animations/marioWalk.json", "MarioWalk");
	walkAnimation = new Animation(AnimationDefinitionManager::Get()->GetAnimationDefinition("MarioWalk"));
	walkAnimationId = animator->AddAnimation(walkAnimation);

	AnimationDefinitionManager::Get()->AddAnimationDefinition("Json/Animations/marioIdle.json", "MarioIdle");
	idleAnimation = new Animation(AnimationDefinitionManager::Get()->GetAnimationDefinition("MarioIdle"));
	idleAnimationId = animator->AddAnimation(idleAnimation);

	AnimationDefinitionManager::Get()->AddAnimationDefinition("Json/Animations/marioJump.json", "MarioJump");
	jumpAnimation = new Animation(AnimationDefinitionManager::Get()->GetAnimationDefinition("MarioJump"));
	jumpAnimationId = animator->AddAnimation(jumpAnimation);

	animator->SetCurrentAnimation(idleAnimationId);

	idleTexture = new sf::Texture;
	idleTexture->loadFromFile("Graphics/Mario/Mario.png");

	jumpTexture = new sf::Texture;
	jumpTexture->loadFromFile("Graphics/Mario/MarioJump.png");
}

Character::~Character()
{
	delete textureAsset;
	delete characterRenderObject;
	delete texture;
	ZenPhysics2D::Get()->RemovingObjectFromPhysics(physicalZenObject2D);
	delete physicalZenObject2D;
	collisionColliders.clear();
}

//MOVEMENT
void Character::MoveLeft()
{
	inputHandler.movingStates = CharacterInputHandler::MovingStates::movingLeft;

	physicalZenObject2D->zenShape->SetScale(sf::Vector2f(-1, 1));
	physicalZenObject2D->zenShape->SetOrigin(sf::Vector2f(physicalZenObject2D->zenShape->GetGlobalBounds().width, 0));

	if (physicalZenObject2D->clollisionNormalVector.x != -1)
	physicalZenObject2D->zenShape->MoveObject(sf::Vector2f(-1.0f * moveSpeed, 0.0f));

	if (physicalZenObject2D->clollisionNormalVector.x == 1)
	{
		physicalZenObject2D->clollisionNormalVector.x = 0;
	}
}

void Character::MoveRight()
{
	inputHandler.movingStates = CharacterInputHandler::MovingStates::movingRight;

	physicalZenObject2D->zenShape->SetScale(sf::Vector2f(1, 1));
	physicalZenObject2D->zenShape->SetOrigin(sf::Vector2f(0, 0));

	if (physicalZenObject2D->clollisionNormalVector.x != 1)
	physicalZenObject2D->zenShape->MoveObject(sf::Vector2f(1.0f * moveSpeed, 0.0f));
	
	if (physicalZenObject2D->clollisionNormalVector.x == -1)
	{
		physicalZenObject2D->clollisionNormalVector.x = 0;
	}
}

void Character::MoveUp()
{
	if (isGrounded && IsCollisionWithOneGround())
	{
		inputHandler.movingStates = CharacterInputHandler::MovingStates::movingUp;

		audioSystem->PlaySingleShot("jump");
		physicalZenObject2D->AddForce(1.0f, Vector2(0, -8.0f), 4.0f);
		collider2D->GetOwner()->isJump = true;
	}
}

void Character::MoveDown()
{
	inputHandler.movingStates = CharacterInputHandler::MovingStates::movingDown;
}

bool Character::IsCollisionWithOneGround()
{
	return collisionColliders[Collider::ColliderTags::GROUND].size() == 1;
}

void Character::UpdateCharacter()
{
	collider2D->SetPosition(physicalZenObject2D->zenShape->GetPosition());

	if (isStanding == true)
	{
		inputHandler.movingStates = CharacterInputHandler::MovingStates::standing;
	}
	
	if (isGrounded==false)
	{
		if (animator->GetCurrentAnimation() != jumpAnimationId)
			animator->SetCurrentAnimation(jumpAnimationId);
	}
	else if (inputHandler.movingStates == CharacterInputHandler::MovingStates::standing)
	{
		if (animator->GetCurrentAnimation() != idleAnimationId)
			animator->SetCurrentAnimation(idleAnimationId);
	}
	else
	{
		if(animator->GetCurrentAnimation()!=walkAnimationId)
		animator->SetCurrentAnimation(walkAnimationId);
	}
}

CharacterInputHandler* Character::GetInputHandler()
{
	return &inputHandler;
}

void Character::SetTextureAsset(string Path, string Name)
{
	textureAsset = new TextureAsset(Path, Name);
}

TextureAsset Character::GetTextureAsset()
{
	return *textureAsset;
}

bool Character::IsCharacterGrounded()
{
	return isGrounded;
}

void Character::Draw(RenderingStack* renderStack)
{
	animator->Play();

	texture = textureAsset->GetTexture();
	physicalZenObject2D->zenShape->SetTexture(texture);

	characterRenderObject = new RenderObject(physicalZenObject2D->zenShape->Draw(), 1000, 1);
	renderStack->renderQueue.push_back(characterRenderObject);
}

void Character::SetCollider(Vector2 position, Vector2 size)
{
	collider2D = new BoxCollider2D(position, size, physicalZenObject2D->zenShape, Collider::ColliderTags::CHARACTER);
	listenerIndexStart = collider2D->OnCollisionStart.AddListener(&Character::HandleCollisionStart, this);
	listenerIndexEnd = collider2D->OnCollisionEnd.AddListener(&Character::HandleCollisionEnd, this);
	ZenPhysics2D::Get()->RegisterCollider(collider2D);
}

void  Character::ClearCollisionColliders()
{
	collisionColliders.clear();
	isGrounded = false;
	physicalZenObject2D->ClearCollisionColliders();
}

void Character::HandleCollisionStart(Collider* other)
{
	for (auto itr = collisionColliders[other->tag].begin(); itr != collisionColliders[other->tag].end(); itr++)
	{
		if (*itr == other)
		{
			return;
		}
	}
	collisionColliders[other->tag].push_back(other);

	if (collisionColliders[Collider::ColliderTags::GROUND].size() > 0)
	{
		isGrounded = true;
		collider2D->GetOwner()->isJump = false;
	}
}

void Character::HandleCollisionEnd(Collider* other)
{
	for (auto itr = collisionColliders[other->tag].begin(); itr != collisionColliders[other->tag].end(); itr++)
	{
		if (*itr == other)
		{
			collisionColliders[other->tag].erase(itr);
			return;
		}
	}

	if (collisionColliders[Collider::ColliderTags::GROUND].size() == 0)
	{
		isGrounded = false;
	}
}