#pragma once

#include "EntityComponent.h"
#include "Engine.h"
#include <vector>
#include "delegate/delegate.hpp"


typedef srutil::delegate1<void, class TextureComponent*> OnCollisionEnterDelegate;


class TextureComponent : public EntityComponent
{

public:

	TextureComponent(Entity* Owner);
	TextureComponent();
	~TextureComponent();
	virtual EntityComponent* Clone() const override { return new TextureComponent(*this); }

	virtual void LoadFromConfig(nlohmann::json Config) override;
	virtual void Initialize() override;
	virtual void BeginStart() override;
	virtual void UnInitialize() override;
	virtual void Update(float DeltaTime) override;
	virtual void Draw() override;
	void CheckCollisionEnter();
	void SetTextureFromAssetName(std::string Name);
	void SetColliderEnable(const bool Status) { IsColliderEnable = Status; };
	void SetActive(const bool Status) { IsActive = Status; };
	bool GetActive()const { return IsActive; };
	void SetPosition(int x, int y);
	void SetScale(int w, int h);
	SDL_Rect& GetRectangle() { return m_Rectangle; }
	OnCollisionEnterDelegate OnCollisionEnterCallback;

private:
	bool IsColliderEnable;
	bool IsActive;
	std::string TexturePath;
	SDL_Rect m_Rectangle;
	std::list<TextureComponent*> ListOfTextureComponents;
	
};