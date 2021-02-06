#ifndef __SHOOTING_H__

#define __SHOOTING_H__

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <string>

#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

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
			void DrawChara(SDL_Texture* texture,SDL_Renderer* renderer,SDL_Surface* image,int x,int y,int width,int height,SDL_RendererFlip flip);

		private:

			typedef struct{
				int x,y;
				bool isUsed;
			}Egg;
			typedef struct{
				int hp;
				int x,y;
				
				Egg egg;
			}Eagle;
			typedef struct{
				int hp;
				int x,y;

				Egg egg;
			}Enemy;

			Eagle eagle;
			Enemy enemy;

			std::string title;
			int windowWidth,windowHeight;
			
			SDL_Window* window;
			SDL_Renderer* renderer;
			SDL_Texture* imageTexture,*eggTexture;
			SDL_Texture* tekiTexture;

			Mix_Chunk* shotWave = nullptr;
			Mix_Chunk* dieWave = nullptr;


			SDL_Event sdlEvent;
	};
};

#endif
