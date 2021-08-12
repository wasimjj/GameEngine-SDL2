#include "BulletComponent.h"
#include "TextureComponent.h"
#include "EntityComponent.h"
#include "Entity.h"
#include "Engine.h"
#include "iostream"
#include "Scene.h"
#include "delegate/delegate.hpp"

BulletComponent::BulletComponent(Entity* Owner):
	EntityComponent(Owner)
	,m_TextureComponent(nullptr)
	,MyRectangle(nullptr)
{
}
BulletComponent::BulletComponent()
	: BulletComponent(nullptr)
{
}
BulletComponent::~BulletComponent()
{
}

void BulletComponent::Initialize()
{
	m_TextureComponent = GetOwner()->GetComponent<TextureComponent>();
	MyRectangle = &m_TextureComponent->GetRectangle();
	m_TextureComponent->SetColliderEnable(true);
}

void BulletComponent::BeginStart()
{
	m_TextureComponent->OnCollisionEnterCallback = OnCollisionEnterDelegate::from_method<BulletComponent, &BulletComponent::OnCollisionEnter>(this);
}

void BulletComponent::Update(float DeltaTime)
{
	MyRectangle->y -= 1 * DeltaTime;
}

void BulletComponent::OnCollisionEnter(TextureComponent* TextureComponent)
{
	printf("OnCollisionEnter..");
}
