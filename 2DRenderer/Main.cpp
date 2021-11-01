#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcess.h"
#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	unsigned char randColor1;
	unsigned char randColor2;
	unsigned char randColor3;
	unsigned char randColor4;
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);
	
	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		randColor1 = rand() % 256;
		randColor2 = rand() % 256;
		randColor3 = rand() % 256;
		randColor4 = rand() % 256;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear(color_t{0, 0, 0, 0});

		framebuffer->Update();
		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();

		/*int clamp(int v, int min, int max)
		{
			int result = (v < min) ? min : ((v > max) ? max : v);
			return result;
		}*/
	}

	SDL_Quit();

	return 0;
}
