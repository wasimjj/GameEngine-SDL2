#include "Scene.h"
#include "Entity.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include <fstream>

void Scene::LoadFromConfig(nlohmann::json Config)
{
	m_Name = Config.value("Name", "");

	if (Config.find("Entities") != Config.end())
	{
		auto ResourceManagerPtr = Engine::Get()->GetResourceManager();
		for (auto Item : Config["Entities"].items())
		{
			auto NewEntity = new Entity();

			nlohmann::json EntityConfig = Item.value();
			std::string TypeName = EntityConfig.value("Type", "");
			if (!TypeName.empty())
			{
				nlohmann::json EntityTemplateConfig = ResourceManagerPtr->GetJsonConfig(TypeName, ResourceType::Entity);
				NewEntity->LoadFromConfig(EntityTemplateConfig);
				//NewEntity->setname
			}
			else
			{
				NewEntity->LoadFromConfig(Item.value());
			}

			AddEntity(NewEntity);
		}
		 
	}

	nlohmann::json::const_iterator SecenLayoutIt = Config.find("SceneLayout");
	if (SecenLayoutIt != Config.end())
	{
		LoadSceneFromLayout((*SecenLayoutIt)["Content"], (*SecenLayoutIt)["Legend"]);
	}
}

void Scene::Initialize()
{
	for (auto Entity : m_Entities)
	{
		Entity->Initialize();
	}
}

void Scene::Update(float DeltaTime)
{
	for (auto Entity : m_Entities)
	{
		Entity->Update(DeltaTime);
	}
}

void Scene::Draw()
{
	for (auto Entity : m_Entities)
	{
		Entity->Draw();
	}
}

void Scene::UnInitialize()
{
	for (auto Entity : m_Entities)
	{
		Entity->UnInitialize();
	}
}

void Scene::Startgame()
{
	for (Entity* Entity : m_Entities)
	{
		Entity->BeginStart();
	}
}

void Scene::AddEntity(Entity* Entity)
{
	m_Entities.push_back(Entity);

}

void Scene::RemoveEntity(Entity* Entity)
{
	auto RetIt = std::remove(m_Entities.begin(), m_Entities.end(), Entity);
}


void Scene::LoadSceneFromLayout(nlohmann::json Content, nlohmann::json Legend)
{
	int Row = 0;
	auto ResourceManagerPtr = Engine::Get()->GetResourceManager();
	for (auto Item : Content.items())
	{
		int Column = 0;
		const std::string& Line = Item.value();
		for (char Character : Line)
		{
			if (Character != ' ')
			{
				const char Key[] = { Character, '\0' };
				nlohmann::json EntitySpecs = Legend[Key];

				auto NewEntity = ResourceManagerPtr->CreateEntityFromDataTemplate(EntitySpecs["Type"]);
				auto TextureComponentPtr = NewEntity->GetComponent<TextureComponent>();
				int Width = EntitySpecs["Width"];
				int Height = EntitySpecs["Height"];
				TextureComponentPtr->SetPosition(Column * Width, Row * Height);
				TextureComponentPtr->SetScale(Width, Height);
				AddEntity(NewEntity);
			}
			++Column;
		}
		++Row;
	}
}
