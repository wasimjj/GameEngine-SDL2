#include "EntityComponent.h"
#include "Scene.h"
#include "Engine.h"
EntityComponent::EntityComponent(Entity* Owner)
	: m_Owner(Owner)
{
}

void EntityComponent::LoadFromConfig(nlohmann::json Config)
{
}

void EntityComponent::Initialize()
{
}

void EntityComponent::BeginStart()
{
}

void EntityComponent::Update(float DeltaTime)
{
}

void EntityComponent::Draw()
{
}

void EntityComponent::UnInitialize()
{
}

void EntityComponent::Destroy()
{
	m_Owner->Destroy();
}
