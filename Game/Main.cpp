
#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"
#include "Core/Json.h"
#include "TileMap.h"

gk::Engine engine;
gk::Scene scene;

int main(int, char**)
{
	engine.Startup();

	gk::ObjectFactory::Instance().Initialize();
	gk::ObjectFactory::Instance().Register("PlayerComponent", new gk::Creator<gk::PlayerComponent, gk::Object>);
	gk::ObjectFactory::Instance().Register("EnemyComponent", new gk::Creator<gk::EnemyComponent, gk::Object>);

	rapidjson::Document document;
	gk::json::Load("scene.txt", document);

	scene.Create(&engine);
	scene.Read(document);

	gk::TileMap tilemap;
	gk::json::Load("tileMap.txt", document);
	tilemap.Read(document);
	tilemap.Create(&scene);

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		
		//Update
		engine.Update();
		scene.Update();

		if (engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == gk::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		//Draw
		engine.GetSystem<gk::Renderer>()->BeginFrame();

		scene.Draw();

		engine.GetSystem<gk::Renderer>()->EndFrame();
	}

	scene.Destroy();
	engine.Shutdown();

	return 0;
}
