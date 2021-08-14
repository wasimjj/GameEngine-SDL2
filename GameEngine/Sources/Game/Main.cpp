#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Engine.h"
#include "ResourceManager.h"
#include "BulletComponent.h"
#include "Bullet2Component.h"
#include "TextureComponent.h"
#include "TankBodyComponent.h"
#include "PlayerInputComponent.h"
#include "Player2InputComponent.h"
int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Engine::Get()->Initialize();

	ResourceManager* ResourceManagerPtr = Engine::Get()->GetResourceManager();
	ResourceManagerPtr->RegisterComponent("PlayerInputComponent", new PlayerInputComponent());
	ResourceManagerPtr->RegisterComponent("Player2InputComponent", new Player2InputComponent());

	ResourceManagerPtr->RegisterComponent("TextureComponent", new TextureComponent());
	ResourceManagerPtr->RegisterComponent("BulletComponent", new BulletComponent());
	ResourceManagerPtr->RegisterComponent("Bullet2Component", new Bullet2Component());
	ResourceManagerPtr->RegisterComponent("TankBodyComponent", new TankBodyComponent());

	Engine::Get()->CreateActiveSceneFromTemplate("MainScene");

	Engine::Get()->MainLoop();
	Engine::Get()->ShutDown();
	free(ResourceManagerPtr);

	return 0;
}