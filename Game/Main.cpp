
#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Input/InputSystem.h"
#include "Resources/ResourceManager.h"

gk::InputSystem inputSystem;
gk::ResourceManager resourcemanager;
gk::Renderer renderer;

int main(int, char**)
{
	renderer.Startup();
	renderer.Create("Kilpack");
	inputSystem.Startup();

	gk::Texture* texture1 = resourcemanager.Get<gk::Texture>("sf2.png", &renderer);
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
		
		renderer.BeginFrame();

		//Draw
		angle += 1.0f;
		texture1->Draw(position, { 1, 1 }, angle);

		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == gk::InputSystem::eButtonState::HELD)
		{
			position.x -= 5.0f;
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == gk::InputSystem::eButtonState::HELD)
		{
			position.x += 5.0f;
		}
		inputSystem.Update();

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
