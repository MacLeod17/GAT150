
#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"

gk::ResourceManager resourcemanager;
gk::Renderer renderer;

int main(int, char**)
{
	renderer.Startup();
	renderer.Create("Kilpack");

	gk::Texture* texture1 = resourcemanager.Get<gk::Texture>("sf2.png", &renderer);
	gk::Texture* texture2 = resourcemanager.Get<gk::Texture>("sf2.png", &renderer);
	float angle{ 0 };

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
		angle += 0.1f;
		texture1->Draw({ 500, 100 }, { 1, 1 }, angle);
		texture2->Draw({ 200, 400 }, { 1, 1 }, angle);

		renderer.EndFrame();
	}

	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
