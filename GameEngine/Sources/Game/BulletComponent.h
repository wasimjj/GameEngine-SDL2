#pragma once
#include <vector>
#include "EntityComponent.h"
#include "TextureComponent.h"
#include "TankBodyComponent.h"
class BulletComponent : public EntityComponent
{

public:
	BulletComponent(Entity* Owner);
	BulletComponent();
   ~BulletComponent();
	virtual BulletComponent* Clone() const override { return new BulletComponent(*this); }
	virtual void Initialize() override;
	virtual void BeginStart() override;
	virtual void Update(float DeltaTime) override;
	void OnCollisionEnter(TextureComponent* TextureComponent);
	void SetActive(const bool Status) { m_TextureComponent->SetActive(Status); }
	void SetPosition(const int x, const int y) { m_TextureComponent->SetPosition(x,y); }
	void SetDirection( DirectionType Direction)  { m_Direction = Direction; }
	int GetWidth() const { return m_Rectangle->w; }
	int GetHeight() const { return m_Rectangle->h; }
private:
	DirectionType m_Direction;
	TextureComponent* m_TextureComponent;
	SDL_Rect* m_Rectangle ;
	std::list<TextureComponent*> ListOfTextureComponent;
	int m_Speed = 3;
	float LifeSpam = -1.0f;
};
