#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Engine.h"
#include "BulletComponent.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "PlayerInputComponent.h"
int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Engine::Get()->Initialize();

	ResourceManager* ResourceManagerPtr = Engine::Get()->GetResourceManager();
	ResourceManagerPtr->RegisterComponent("PlayerInputComponent", new PlayerInputComponent());
	ResourceManagerPtr->RegisterComponent("TextureComponent", new TextureComponent());
	ResourceManagerPtr->RegisterComponent("BulletComponent", new BulletComponent());


	Engine::Get()->CreateActiveSceneFromTemplate("MainScene");

	Engine::Get()->MainLoop();
	Engine::Get()->ShutDown();
	free(ResourceManagerPtr);

	return 0;
}