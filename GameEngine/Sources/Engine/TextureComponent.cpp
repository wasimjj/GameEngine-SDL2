#include "TextureComponent.h"
#include "Engine.h"
#include "Scene.h"
#include <iostream>

TextureComponent::TextureComponent(Entity* Owner)
	: EntityComponent(Owner)
	, m_Rectangle{0,0,0,0}
{
}

TextureComponent::TextureComponent()
	: TextureComponent(nullptr)
{
}

TextureComponent::~TextureComponent()
{
	free((void*)TexturePath.c_str());
	std::cout<< "Texture Component Deleted..." << std::endl;
}

void TextureComponent::LoadFromConfig(nlohmann::json Config)
{
	std::string TextureName = Config.value("Texture", "");
	if (!TextureName.empty())
	{
		SetTextureFromAssetName(TextureName);
	}

	m_Rectangle.w = Config.value("Width", 10);
	m_Rectangle.h = Config.value("Height", 10);
	m_Rectangle.x = Config.value("PositionX", 0);
	m_Rectangle.y = Config.value("PositionY", 0);
}

void TextureComponent::Initialize()
{
}

void TextureComponent::BeginStart()
{
	IsActive = true;
	ListOfTextureComponents = Engine::Get()->GetActiveScene()->GetComponents<TextureComponent>();
}

void TextureComponent::UnInitialize()
{
}

void TextureComponent::Update(float DeltaTime)
{
	if (!IsActive)
		return;
	if (IsColliderEnable)
	{
		CheckCollisionEnter();
	}
}

void TextureComponent::Draw()
{
	if (!IsActive)
		return;
	auto Surface = IMG_Load(TexturePath.c_str());
	auto Texture = SDL_CreateTextureFromSurface(Engine::Get()->GetRenderer(), Surface);
	SDL_FreeSurface(Surface);

	SDL_RenderCopy(Engine::Get()->GetRenderer(), Texture, nullptr, &m_Rectangle);
}

void TextureComponent::CheckCollisionEnter()
{
	ListOfTextureComponents = Engine::Get()->GetActiveScene()->GetComponents<TextureComponent>();

	if (IsColliderEnable)
	{
		for (TextureComponent* textureComponent : ListOfTextureComponents)
		{
			if ( this != textureComponent &&  SDL_HasIntersection(&m_Rectangle, &textureComponent->m_Rectangle))
			{
				if (OnCollisionEnterCallback)
				{
					OnCollisionEnterCallback(textureComponent);

				}
			}
		}
	}
}

void TextureComponent::SetTextureFromAssetName(std::string Name)
{
	TexturePath = "Resources/Images/" + Name;
}

void TextureComponent::SetPosition(int x, int y)
{
	m_Rectangle.x = x;
	m_Rectangle.y = y;
}

void TextureComponent::SetScale(int w, int h)
{
	m_Rectangle.w = w;
	m_Rectangle.h = h;
}

