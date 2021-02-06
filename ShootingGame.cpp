#include "ShootingGame.h"

nori::ShootingTutorial::ShootingTutorial()
{
	nori::ShootingTutorial("STG");
}

nori::ShootingTutorial::ShootingTutorial(std::string title, int width, int height)
{

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	this->title = title;

	this->windowWidth = width;
	this->windowHeight = height;

	this->eagle.hp = 1; // 一回でもあたったらアウト
	this->eagle.x = 0;

	this->eagle.y = DEFAULT_WINDOW_HEIGHT / 2;
	this->eagle.egg.isUsed = false;

	this->eagle.egg.x = 0;
	this->eagle.egg.y = 0;

	this->shotWave = Mix_LoadWAV("sounds/shot.wav");
	this->dieWave = Mix_LoadWAV("sounds/die.wav");
}

void nori::ShootingTutorial::start()
{

	this->window = SDL_CreateWindow(
		this->title.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		this->windowWidth,
		this->windowHeight,
		SDL_WINDOW_OPENGL);

	if (this->window == nullptr)
	{
		std::cerr << "ウィンドウの生成に失敗しました" << std::endl;
		SDL_Quit();
		exit(0);
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	SDL_SetRenderDrawColor(this->renderer, 200, 200, 200, 255);
	SDL_RenderClear(this->renderer);
	SDL_RenderPresent(this->renderer);

	//自機の画像を読み込む

	SDL_Surface *image = IMG_Load("images/jiki.png");
	SDL_Surface *egg = IMG_Load("images/egg.png");
	SDL_Surface *teki = IMG_Load("images/teki.png");

	this->tekiTexture = SDL_CreateTextureFromSurface(renderer, teki);
	this->imageTexture = SDL_CreateTextureFromSurface(renderer, image);
	this->eggTexture = SDL_CreateTextureFromSurface(renderer, egg);

	bool isKeyDown;
	bool isUpKeyDown;
	bool isDownKeyDown;
	bool isReturnKeyDown;
	bool isGameExit;

	std::mt19937 randEngine;
	std::uniform_int_distribution<> enemyHP(1, 15);
	std::uniform_int_distribution<> enemyShowPercent(0, 100);
	std::uniform_int_distribution<> enemyRandomY(0, 480);

	bool isEnemyShow = false;

	double hLen[2];
	double xLen[2];
	double yLen[2];

	bool isJikiDie = false;

	while (true)
	{
		SDL_PollEvent(&(this->sdlEvent));
		if (isJikiDie)
		{
			Mix_PlayChannel(-1,dieWave,0);
			this->eagle.x = -100;
			SDL_Delay(5000);
			break;
		}
		else
		{
			isKeyDown = this->sdlEvent.type == SDL_KEYDOWN;

			isUpKeyDown = isKeyDown && this->sdlEvent.key.keysym.sym == SDLK_UP;
			isDownKeyDown = isKeyDown && this->sdlEvent.key.keysym.sym == SDLK_DOWN;
			isReturnKeyDown = isKeyDown && this->sdlEvent.key.keysym.sym == SDLK_SPACE;
			isGameExit = isKeyDown && this->sdlEvent.key.keysym.sym == SDLK_ESCAPE;

			if (isUpKeyDown)
				this->eagle.y -= 3;
			else if (isDownKeyDown)
				this->eagle.y += 3;

			if (this->eagle.y <= 0)
				this->eagle.y = 0;
			else if (this->eagle.y >= 480 - 64)
				this->eagle.y = 480 - 64;

			if (isReturnKeyDown && this->eagle.egg.isUsed == false)
			{
				Mix_PlayChannel(-1, this->shotWave, 0);
				this->eagle.egg.isUsed = true;
				this->eagle.egg.x = 0;
				this->eagle.egg.y = this->eagle.y;
			}

			if (this->eagle.egg.isUsed)
			{
				this->eagle.egg.x += 6;
				this->DrawChara(this->eggTexture, this->renderer, egg, this->eagle.egg.x, this->eagle.egg.y, 32, 32, SDL_FLIP_HORIZONTAL);
				if (this->eagle.egg.x >= DEFAULT_WINDOW_WIDTH + 64)
					this->eagle.egg.isUsed = false;
			}

			if (enemyShowPercent(randEngine) < 5 && isEnemyShow == false)
			{
				this->enemy.hp = enemyHP(randEngine);
				this->enemy.y = enemyRandomY(randEngine);
				this->enemy.x = DEFAULT_WINDOW_WIDTH - 64;
				this->DrawChara(this->tekiTexture, this->renderer, teki, this->enemy.x, this->enemy.y, 64, 64, SDL_FLIP_NONE);
				isEnemyShow = true;
			}

			if (this->enemy.x <= -64)
				isEnemyShow = false;
			else
				this->enemy.x -= 1;
			if (isGameExit)
				break;

			this->DrawChara(this->tekiTexture, this->renderer, teki, this->enemy.x, this->enemy.y, 64, 64, SDL_FLIP_NONE);
			this->DrawChara(this->imageTexture, this->renderer, image, this->eagle.x, this->eagle.y, 64, 64, SDL_FLIP_HORIZONTAL);

			hLen[0] = 32 + 32; //自機と敵の中心座標を足す
			xLen[0] = this->eagle.x - this->enemy.x;
			yLen[0] = this->eagle.y - this->enemy.y;

			hLen[1] = 16 + 32;
			xLen[1] = this->eagle.egg.x - this->enemy.x;
			yLen[1] = this->eagle.egg.y - this->enemy.y;

			isJikiDie = hLen[0] * hLen[0] >= xLen[0] * xLen[0] + yLen[0] * yLen[0];

			if (hLen[1] * hLen[1] >= xLen[1] * xLen[1] + yLen[1] * yLen[1])
			{
				this->eagle.egg.x = -100;
				this->enemy.x = -100;
			}
			SDL_RenderPresent(this->renderer);
			SDL_RenderClear(this->renderer);
			SDL_Delay(1);
		}
	}
	Mix_FreeChunk(this->shotWave);
	Mix_FreeChunk(this->dieWave);
}

void nori::ShootingTutorial::DrawChara(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Surface *image, int x, int y, int width, int height, SDL_RendererFlip flip)
{

	int imageWidth, imageHeight;
	SDL_QueryTexture(texture, nullptr, nullptr, &imageWidth, &imageHeight);

	SDL_Rect imageRect = (SDL_Rect){0, 0, imageWidth, imageHeight};
	SDL_Rect drawRect = (SDL_Rect){x, y, width, height};

	SDL_RenderCopyEx(
		renderer,
		imageTexture,
		&imageRect,
		&drawRect,
		0.0,
		nullptr,
		flip);
}
nori::ShootingTutorial::~ShootingTutorial()
{
	SDL_DestroyWindow(window);
	
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
}
