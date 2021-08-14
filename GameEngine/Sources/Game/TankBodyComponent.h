#pragma once
#include "TextureComponent.h"
#include <iostream>
#include "EntityComponent.h"
#include "Entity.h"

enum class DirectionType
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class TankBodyComponent : public EntityComponent 
{

public:
	TankBodyComponent(Entity* Owner);
	TankBodyComponent();
	~TankBodyComponent();
	virtual TankBodyComponent* Clone() const override { return new TankBodyComponent(*this); }
	virtual void LoadFromConfig(nlohmann::json Config) override;
	virtual void Initialize() override;
	virtual void BeginStart() override;
	void UpdateTexture(const DirectionType& directionType);
	void SetTextureFromAssetName(std::string& TextureName);


private:
	std::string FrontTexturePath;
	TextureComponent* m_TextureComponent;;
	std::map<DirectionType, std::string> m_TankTextureMap;

};