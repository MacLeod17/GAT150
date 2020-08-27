
#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"

gk::Engine engine;
gk::Scene scene;

int main(int, char**)
{
	engine.Startup();

	gk::ObjectFactory::Instance().Initialize();
	gk::ObjectFactory::Instance().Register("PlayerComponent", new gk::Creator<gk::PlayerComponent, gk::Object>);

	rapidjson::Document document;
	gk::json::Load("scene.txt", document);

	scene.Create(&engine);
	scene.Read(document);

	for (size_t i = 0; i < 10; i++)
	{
		gk::GameObject* gameObject = gk::ObjectFactory::Instance().Create<gk::GameObject>("ProtoCoin");
		gameObject->m_transform.position = { gk::Random(0, 800), gk::Random(200, 400) };
		//gameObject->m_transform.angle = gk::Random(0, 360);

		scene.AddGameObject(gameObject);
	}

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
