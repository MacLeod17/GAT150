
#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Core/Json.h"

gk::Engine engine;
gk::GameObject player;

int main(int, char**)
{
	rapidjson::Document document;
	gk::json::Load("json.txt", document);

	std::string str;
	gk::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	gk::json::Get(document, "bool", b);
	std::cout << b << std::endl;

	int i1;
	gk::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	gk::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	gk::json::Get(document, "float", f);
	std::cout << f << std::endl;

	gk::Vector2 v2;
	gk::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	gk::Color color;
	gk::json::Get(document, "color", color);
	std::cout << color << std::endl;

	return 0;

	engine.Startup();

	player.Create(&engine);
	player.m_transform.position = { 400, 300 };
	player.m_transform.angle = 90;
	gk::Component* component = new gk::PhysicsComponent;
	player.AddComponent(component);
	component->Create();

	component = new gk::SpriteComponent;
	player.AddComponent(component);
	component->Create();
	
	gk::Texture* background = engine.GetSystem<gk::ResourceManager>()->Get<gk::Texture>("background.png", engine.GetSystem<gk::Renderer>());

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
		player.Update();

		if (engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == gk::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		//Player Controls
		if (engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT)	== gk::InputSystem::eButtonState::HELD ||
			engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_A)		== gk::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle -= 120.0f * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT)	== gk::InputSystem::eButtonState::HELD ||
			engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_D)		== gk::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle += 120.0f * engine.GetTimer().DeltaTime();
		}

		//Physics
		gk::Vector2 force{ 0,0 };

		if (engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_UP)		== gk::InputSystem::eButtonState::HELD ||
			engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_W)		== gk::InputSystem::eButtonState::HELD)
		{
			force = gk::Vector2::forward * 1000;
		}
		if (engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_DOWN)	== gk::InputSystem::eButtonState::HELD ||
			engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_S)		== gk::InputSystem::eButtonState::HELD)
		{
			force = -(gk::Vector2::forward * 1000);
		}
		
		force = gk::Vector2::Rotate(force, gk::DegreesToRadians(player.m_transform.angle));

		//Draw
		engine.GetSystem<gk::Renderer>()->BeginFrame();

		background->Draw({ 0, 0 }, { 1, 1 }, 0);
		
		player.Draw();

		engine.GetSystem<gk::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}
