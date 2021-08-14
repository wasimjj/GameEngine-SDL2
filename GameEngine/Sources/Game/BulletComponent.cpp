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
	,m_Rectangle(nullptr)
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
	m_Rectangle = &m_TextureComponent->GetRectangle();
	m_TextureComponent->SetColliderEnable(true);
	
}

void BulletComponent::BeginStart()
{
	m_TextureComponent->SetActive(false);
	m_TextureComponent->OnCollisionEnterCallback = OnCollisionEnterDelegate::from_method<BulletComponent, &BulletComponent::OnCollisionEnter>(this);
}

void BulletComponent::Update(float DeltaTime)
{
	if (!(LifeSpam <= -1))
	{
		LifeSpam -= DeltaTime;
		if (LifeSpam <= 0)
		{
			Destroy();
		}
	}
	
	if (!m_TextureComponent->GetActive())
		return;
	switch (m_Direction)
	{
	case DirectionType::UP:
		m_Rectangle->y -= m_Speed ;

		break;
	case DirectionType::DOWN:
		m_Rectangle->y += m_Speed;

		break;
	case DirectionType::LEFT:
		m_Rectangle->x -= m_Speed;

		break;
	case DirectionType::RIGHT:
		m_Rectangle->x += m_Speed;

		break;
	default:
		break;
	}
}

void BulletComponent::OnCollisionEnter(TextureComponent* TextureComponent)
{
	
	TextureComponent->Destroy();
}
