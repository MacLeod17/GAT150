
#include "pch.h"
#include "Core/Timer.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Input/InputSystem.h"
#include "Resources/ResourceManager.h"

gk::InputSystem inputSystem;
gk::ResourceManager resourcemanager;
gk::Renderer renderer;

gk::FrameTimer timer;

int main(int, char**)
{
	/*
	gk::Timer timer;
	for (size_t i = 0; i < 10000; i++) { std::sqrt(rand() % 100); }
	std::cout << timer.ElapsedSeconds() << std::endl;
	*/
	
	renderer.Startup();
	renderer.Create("Kilpack");
	resourcemanager.Startup();
	inputSystem.Startup();

	gk::Texture* car = resourcemanager.Get<gk::Texture>("cars.png", &renderer);
	gk::Texture* background = resourcemanager.Get<gk::Texture>("background.png", &renderer);

	float angle{ 0 };
	gk::Vector2 position{ 400, 300 };

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
		timer.Tick();
		inputSystem.Update();

		if (inputSystem.GetButtonState(SDL_SCANCODE_ESCAPE) == gk::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT)	== gk::InputSystem::eButtonState::HELD || 
			inputSystem.GetButtonState(SDL_SCANCODE_A)		== gk::InputSystem::eButtonState::HELD)
		{
			position.x -= 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT)	== gk::InputSystem::eButtonState::HELD || 
			inputSystem.GetButtonState(SDL_SCANCODE_D)		== gk::InputSystem::eButtonState::HELD)
		{
			position.x += 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_UP)		== gk::InputSystem::eButtonState::HELD || 
			inputSystem.GetButtonState(SDL_SCANCODE_W)		== gk::InputSystem::eButtonState::HELD)
		{
			position.y -= 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_DOWN)	== gk::InputSystem::eButtonState::HELD || 
			inputSystem.GetButtonState(SDL_SCANCODE_S)		== gk::InputSystem::eButtonState::HELD)
		{
			position.y += 200.0f * timer.DeltaTime();
		}

		//Draw
		renderer.BeginFrame();

		angle += 180 * timer.DeltaTime();
		background->Draw({ 0, 0 }, { 1, 1 }, 0);
		car->Draw({ 0, 16, 64, 144 }, position, { 1, 1 }, 0);

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
