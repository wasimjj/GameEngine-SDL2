#pragma once
#include "TankBodyComponent.h"

class BulletComponent;
class TextureComponent;
class Player2InputComponent : public EntityComponent
{

public:
	Player2InputComponent(Entity* Owner);
	Player2InputComponent();

	virtual EntityComponent* Clone() const override { return new Player2InputComponent(*this); }

	virtual void Initialize() override;
	virtual void BeginStart() override;
	virtual void Update(float DeltaTime) override;
	virtual void LoadFromConfig(nlohmann::json Config) override;

	void UpdateDirection(DirectionType Direction);
	void Fire();
private:
	BulletComponent* m_BulletComponent;
	TankBodyComponent* m_TankBodyComponent;
	TextureComponent* m_TextureComponent;
	struct SDL_Rect* m_Rectangle;
	DirectionType m_Direction;
	int m_PlyerId;

};