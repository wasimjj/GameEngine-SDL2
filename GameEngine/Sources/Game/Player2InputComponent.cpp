#include "Player2InputComponent.h"
#include "TextureComponent.h"
#include "Bullet2Component.h"
#include "BulletComponent.h"
#include <algorithm>
#include "Entity.h"
#include "Engine.h"
#include "Scene.h"

Player2InputComponent::Player2InputComponent(Entity* Owner)
	: EntityComponent(Owner)
	, m_TextureComponent(nullptr)
{
}

Player2InputComponent::Player2InputComponent()
	: Player2InputComponent(nullptr)
{
}

void Player2InputComponent::Initialize()
{


}

void Player2InputComponent::BeginStart()
{
	m_TextureComponent = GetOwner()->GetComponent<TextureComponent>();
	m_TankBodyComponent = GetOwner()->GetComponent<TankBodyComponent>();

	m_Rectangle = &m_TextureComponent->GetRectangle();
	m_BulletComponent = Engine::Get()->GetActiveScene()->FindComponent<BulletComponent>();
	m_BulletComponent = m_BulletComponent->GetOwner()->Clone()->GetComponent<BulletComponent>();
}

void Player2InputComponent::Update(float DeltaTime)
{
	const int Speed = 300;
	auto& Events = Engine::Get()->GetEvents();
	for (const SDL_Event& Event : Events)
	{
		switch (Event.type)
		{
		case SDL_KEYDOWN:
		{
			switch (Event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
				
					m_Rectangle->y -= Speed / 30;
					m_Direction = DirectionType::UP;
					UpdateDirection(m_Direction);
				break;
		
			case SDL_SCANCODE_A:
					m_Rectangle->x -= Speed / 30;
					m_Direction = DirectionType::LEFT;
					UpdateDirection(m_Direction);
				break;
			
			case SDL_SCANCODE_S:
					m_Rectangle->y += Speed / 30;
					m_Direction = DirectionType::DOWN;
					UpdateDirection(m_Direction);
				
				break;
			
			case SDL_SCANCODE_D:
					m_Rectangle->x += Speed / 30;
					m_Direction = DirectionType::RIGHT;
					UpdateDirection(m_Direction);
				break;
			
			case SDL_SCANCODE_F:
				
					if (m_BulletComponent != nullptr)
					{
						Fire();
					}
				break;
			default:
				break;
			}

		}
		}
	}

	int MaxWidth = 0, MaxHeight = 0;
	SDL_GetWindowSize(Engine::Get()->GetWindow(), &MaxWidth, &MaxHeight);

	if (m_Rectangle->x + m_Rectangle->w > MaxWidth)
	{
		m_Rectangle->x = MaxWidth - m_Rectangle->w;
	}

	if (m_Rectangle->x < 0)
	{
		m_Rectangle->x = 0;
	}

	if (m_Rectangle->y + m_Rectangle->h > MaxHeight)
	{
		m_Rectangle->y = MaxHeight - m_Rectangle->h;
	}

	if (m_Rectangle->y < 0)
	{
		m_Rectangle->y = 0;
	}
}

void Player2InputComponent::LoadFromConfig(nlohmann::json Config)
{
	m_PlyerId = Config.value("Id", 0);
}

void Player2InputComponent::UpdateDirection(DirectionType Direction)
{
	m_TankBodyComponent->UpdateTexture(Direction);
	m_BulletComponent->SetDirection(Direction);
}

void Player2InputComponent::Fire()
{
	int x;
	int y;
	switch (m_Direction)
	{
	case DirectionType::UP:
		x = m_Rectangle->x + m_Rectangle->h / 2;
		y = m_Rectangle->y - m_BulletComponent->GetHeight();
		break;
	case DirectionType::DOWN:
		x = m_Rectangle->x + m_Rectangle->h / 2;
		y = m_Rectangle->y + m_Rectangle->h;
		break;
	case DirectionType::LEFT:
		x = m_Rectangle->x - m_Rectangle->w / 2;
		y = m_Rectangle->y + m_Rectangle->h / 2;
		break;
	case DirectionType::RIGHT:
		x = m_Rectangle->x + m_Rectangle->w;
		y = m_Rectangle->y + m_Rectangle->h / 2;
		break;
	default:
		break;
	}

	auto Bullet = m_BulletComponent->GetOwner()->Clone();
	BulletComponent* bulletComponent = Bullet->GetComponent<BulletComponent>();
	if (bulletComponent != nullptr)
	{
		bulletComponent->SetPosition(x, y);
		bulletComponent->SetActive(true);
	}


}
