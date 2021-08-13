#pragma once
#include <vector>
#include "EntityComponent.h"
#include "TextureComponent.h"
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

private:

	TextureComponent* m_TextureComponent;
	SDL_Rect* MyRectangle ;
	std::list<TextureComponent*> ListOfTextureComponent;
};
