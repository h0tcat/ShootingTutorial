#ifndef __SHOOTING_H__

#define __SHOOTING_H__

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <string>

#include <SDL2/SDL.h>
#include <iostream>

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

namespace nori{
	class ShootingTutorial{
		public:
			ShootingTutorial();
			ShootingTutorial(std::string title,int width=DEFAULT_WINDOW_WIDTH,int height=DEFAULT_WINDOW_HEIGHT);

			void start();

			~ShootingTutorial();

		protected:
			void DrawChara(SDL_Renderer* renderer,SDL_Surface* image,int x,int y);

		private:
			std::string title;
			int windowWidth,windowHeight;
			
			SDL_Window* window;
			SDL_Renderer* renderer;

			SDL_Event sdlEvent;
	};
};

#endif
