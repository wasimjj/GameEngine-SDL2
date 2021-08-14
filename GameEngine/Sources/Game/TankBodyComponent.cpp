#include "TankBodyComponent.h"
#include "Engine.h"
#include "TextureComponent.h"

TankBodyComponent::TankBodyComponent(Entity* Owner):
	EntityComponent(Owner)
{
}

TankBodyComponent::TankBodyComponent() :
	TankBodyComponent(nullptr)
{
}

TankBodyComponent::~TankBodyComponent()
{
}

void TankBodyComponent::LoadFromConfig(nlohmann::json Config)
{
	std::string TextureName = Config.value("Texture1", "");
	SetTextureFromAssetName(TextureName);
	TextureName  = Config.value("Texture2", "");
	SetTextureFromAssetName(TextureName);
	TextureName = Config.value("Texture3", "");
	SetTextureFromAssetName(TextureName);
	TextureName = Config.value("Texture4", "");
	SetTextureFromAssetName(TextureName);


}

void TankBodyComponent::Initialize()
{
}

void TankBodyComponent::BeginStart()
{
	m_TextureComponent = GetOwner()->GetComponent<TextureComponent>();
}

void TankBodyComponent::UpdateTexture(const DirectionType& directionType)
{
	m_TextureComponent->SetTexture(m_TankTextureMap[directionType]);
}

void TankBodyComponent::SetTextureFromAssetName(std::string& TextureName)
{
	std::string path = "Resources/Images/" + TextureName;
	if (strstr(TextureName.c_str(), "Front"))
	{
		m_TankTextureMap[DirectionType::UP] = path;
	}
	else if (strstr(TextureName.c_str(), "Down"))
	{
		m_TankTextureMap[DirectionType::DOWN] = path;
	}
	else if(strstr(TextureName.c_str(), "left"))
	{
		m_TankTextureMap[DirectionType::LEFT] = path;
	}
	else if (strstr(TextureName.c_str(), "Right"))
	{
		m_TankTextureMap[DirectionType::RIGHT] = path;
	}
}
