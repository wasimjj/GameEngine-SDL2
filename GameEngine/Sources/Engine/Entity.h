#pragma once

#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>
class EntityComponent;

class Entity
{

public:
	void LoadFromConfig(nlohmann::json Config);
	void Initialize();
	void BeginStart();
	void Update(float DeltaTime);
	void Draw();
	void UnInitialize();
	void Destroy();
	void AddComponent(EntityComponent* Component);
	void RemoveComponent(EntityComponent* Component);
	Entity* Clone() const;
	~Entity() { printf("my name is %s\n" , m_Name); }

	template <typename ComponentType>
	ComponentType* GetComponent()
	{
		for (EntityComponent* Component : m_Components)
		{
			if (ComponentType* TypedComponent = dynamic_cast<ComponentType*>(Component))
			{
				return TypedComponent;
			}
		}
		return nullptr;
	}
	
private:
	std::vector<EntityComponent*> m_Components;
	std::string m_Name;
};