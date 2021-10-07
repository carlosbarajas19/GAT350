#include "Renderer.h"
#include "Framebuffer.h"
#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);
	
	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear(color_t{0, 0, 0, 0});
		for (int i = 0; i < 100; i++)
		{
			framebuffer->DrawPoint(rand() % framebuffer->width, rand() % framebuffer->height, color_t{ 255,255,255,255 });
		}
		framebuffer->DrawRect(100, 100, 300, 400, color_t{ 155,255,0, 100 });
		framebuffer->Update();
		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}