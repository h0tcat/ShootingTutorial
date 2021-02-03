#include "ShootingGame.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

nori::ShootingTutorial::ShootingTutorial(){
	nori::ShootingTutorial("STG");
}

nori::ShootingTutorial::ShootingTutorial(std::string title,int width,int height){
	
	SDL_Init(SDL_INIT_VIDEO);
	this->title=title;
	
	this->windowWidth=width;
	this->windowHeight=height;
}

void nori::ShootingTutorial::start(){

	this->window = SDL_CreateWindow(
			this->title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			this->windowWidth,
			this->windowHeight,
			SDL_WINDOW_OPENGL
			);

	if(this->window==nullptr){
		std::cerr << "ウィンドウの生成に失敗しました" << std::endl;
		SDL_Quit();
		exit(0);
	}


	this->renderer = SDL_CreateRenderer(this->window,-1,0);
	SDL_SetRenderDrawColor(this->renderer,255,255,255,255);
	SDL_RenderClear(this->renderer);
	SDL_RenderPresent(this->renderer);
	
	//自機の画像を読み込む
	
	SDL_Surface* image = IMG_Load("images/jiki.png");
	
	while(SDL_PollEvent(&(this->sdlEvent))){
		if(this->sdlEvent.type == SDL_QUIT)
			break;

		this->DrawChara(this->renderer,image,500,500);

	}
}

void nori::ShootingTutorial::DrawChara(SDL_Renderer* renderer,SDL_Surface* image,int x,int y){
	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer,image);
	int imageWidth,imageHeight;
	SDL_QueryTexture(imageTexture,nullptr,nullptr,&imageWidth,&imageHeight);

	SDL_Rect imageRect = {0,0,imageWidth,imageHeight};
	SDL_Rect drawRect = {0,0,imageWidth,imageHeight};
	
	SDL_RenderCopy(renderer,imageTexture,&imageRect,&drawRect);
	SDL_RenderPresent(renderer);
}
nori::ShootingTutorial::~ShootingTutorial(){
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}
