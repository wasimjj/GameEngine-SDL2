#pragma once

#include "EntityComponent.h"
class BulletComponent;
class TextureComponent;

class PlayerInputComponent : public EntityComponent
{

public:
	PlayerInputComponent(Entity* Owner);
	PlayerInputComponent();

	virtual EntityComponent* Clone() const override { return new PlayerInputComponent(*this); }

	virtual void Initialize() override;
	virtual void BeginStart() override;
	virtual void Update(float DeltaTime) override;

private:
	BulletComponent* m_BulletComponent;
	TextureComponent* m_TextureComponent;
	struct SDL_Rect* Rectangle;
};