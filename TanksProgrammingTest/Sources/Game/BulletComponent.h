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
	virtual EntityComponent* Clone() const override { return new BulletComponent(*this); }
	virtual void Initialize() override;
	virtual void BeginStart() override;
	virtual void Update(float DeltaTime) override;
	void OnCollisionEnter(TextureComponent* TextureComponent);

private:
	TextureComponent* m_TextureComponent;
	SDL_Rect* MyRectangle ;
	std::list<TextureComponent*> ListOfTextureComponent;
};
