
#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Core/Json.h"
#include "Core/Factory.h"

gk::Engine engine;
gk::Factory<gk::Object, std::string> objectFactory;

int main(int, char**)
{
	/*
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
	*/

	engine.Startup();

	objectFactory.Register("GameObject", gk::Object::Instantiate<gk::GameObject>);
	objectFactory.Register("PhysicsComponent", gk::Object::Instantiate<gk::PhysicsComponent>);
	objectFactory.Register("SpriteComponent", gk::Object::Instantiate<gk::SpriteComponent>);
	objectFactory.Register("PlayerComponent", gk::Object::Instantiate<gk::PlayerComponent>);

	gk::GameObject* player = objectFactory.Create<gk::GameObject>("GameObject");

	rapidjson::Document document;

	player->Create(&engine);
	gk::json::Load("player.txt", document);
	player->Read(document);

	{
		gk::Component* component = objectFactory.Create<gk::Component>("PhysicsComponent");
		player->AddComponent(component);
		component->Create();

		component = objectFactory.Create<gk::Component>("SpriteComponent");
		player->AddComponent(component);
		gk::json::Load("sprite.txt", document);
		component->Read(document);
		component->Create();

		component = objectFactory.Create<gk::Component>("PlayerComponent");
		player->AddComponent(component);
		component->Create();
	}
	
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
		player->Update();

		if (engine.GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == gk::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		//Draw
		engine.GetSystem<gk::Renderer>()->BeginFrame();

		background->Draw({ 0, 0 }, { 1, 1 }, 0);
		
		player->Draw();

		engine.GetSystem<gk::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}
