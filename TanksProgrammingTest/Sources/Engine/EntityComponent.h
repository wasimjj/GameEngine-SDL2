#pragma once

#include <nlohmann/json.hpp>

class Entity;

class EntityComponent
{

public:
	EntityComponent() = delete;
	EntityComponent(Entity* Owner);
	
	virtual EntityComponent* Clone() const = 0;

	virtual void LoadFromConfig(nlohmann::json Config);
	virtual void Initialize();
	virtual void BeginStart();
	virtual void Update(float DeltaTime);
	virtual void Draw();
	virtual void UnInitialize();
	virtual void Destroy();
	void SetOwner(Entity* Owner) { m_Owner = Owner; }
	Entity* GetOwner() { return m_Owner; }

private:
	Entity* m_Owner;
};