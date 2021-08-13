#pragma once

#include <vector>
#include <string>
#include "Entity.h"
#include "TextureComponent.h"
#include <nlohmann/json.hpp>

class Scene
{

public:
	Scene() {};
	void LoadFromConfig(nlohmann::json Config);
	void Initialize();
	void Update(float DeltaTime);
	void Draw();
	void UnInitialize();
	void Startgame();
	void AddEntity(Entity* Entity);
	void RemoveEntity(Entity* Entity);

	template<typename componentType>
	std::list<componentType*> GetComponents() // Will used for collision and other stuff needed
	{
		std::list<componentType*> list;

		for (Entity* entity : m_Entities)
		{
			if (componentType* typedComponent = entity->GetComponent<componentType>())
			{
				list.push_back(typedComponent);
			}
		}
		return list;
	}
	template<typename componentType>
	componentType* FindComponent()
	{

		for (Entity* entity : m_Entities)
		{
			if (componentType* typedComponent = entity->GetComponent<componentType>())
			{
				return typedComponent;
			}
		}
		return nullptr;
	}
	static Entity* Instantiate(const Entity* entity);
private:
	void LoadSceneFromLayout(nlohmann::json Content, nlohmann::json Legend);

	std::list<Entity*> m_Entities;
	std::string m_Name;
};