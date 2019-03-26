#include <iostream>
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.h"
#include "Particle.h"
#include "Swarm.h"

#undef main

int main()
{
	srand(time(NULL));
	Screen screen;

	if (screen.init() == false)
	{
		std::cout << "Error initialising SDL" << std::endl;
	}

	Swarm swarm;
	const double widthDevision = Screen::SCREEN_WIDTH / 2;
	const double heightDevision = Screen::SCREEN_HEIGHT / 2;
	while (true)
	{
		//Draw particles

		int elapsed = SDL_GetTicks();

		
		swarm.update(elapsed);

		unsigned char green = (unsigned char)((1 + sin(elapsed * .0001)) * 128);
		unsigned char red = (unsigned char)((1 + sin(elapsed * .0002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * .0003)) * 128);

		const Particle * const pParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::NPARTICLES; i++)
		{
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * (widthDevision);
			int y = particle.m_y * (widthDevision) + heightDevision;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

		//Draw the screen
		screen.update();

		//Check for messages/events
		if (screen.processEvents() == false)
		{
			break;
		}
	}
	
	screen.close();
	return 0;
}