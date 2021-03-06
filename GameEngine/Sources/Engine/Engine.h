#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <vector>
#include <string>
#include <list>

class Scene;
class ResourceManager;

class Engine
{

public:
	static Engine* Get();

	void Initialize();
	void MainLoop();
	void Draw();
	void ShutDown();

	SDL_Renderer* GetRenderer() { return m_Renderer; }
	SDL_Window* GetWindow() { return m_Window; }
	ResourceManager* GetResourceManager() { return m_ResourceManager; }
	const std::list<SDL_Event>& GetEvents() { return m_Events; }
	void SetActiveScene(Scene* Scene) { m_ActiveScene = Scene; }
	Scene* GetActiveScene() const { return m_ActiveScene; }
	void CreateActiveSceneFromTemplate(std::string Name);

private:
	Engine();
	~Engine();
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	Scene* m_ActiveScene;
	ResourceManager* m_ResourceManager;
	
	unsigned int FramesPerSecond;
	unsigned int TimePerFrameInMs;
	float TimePerFramInSceonds;

	std::list<SDL_Event> m_Events;
};