#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cJSON.h>

int openWindow() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	SDL_Window* window = SDL_CreateWindow(u8"qwqqwq", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event event;

	SDL_Point pos_cursor = { 0, 0 };
	bool is_quit = false;
	while (!is_quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				is_quit = true;
			}
		}
	}
}

template <typename T>
class Base {
public:
	static T qwq;

	static void printqwq() {
		std::cout << qwq << std::endl;
	}
};

class Sub1 : public Base<int> {

};

class Sub2 : public Base<int> {

};

class Sub3 : public Base<double> {

};

int Sub1::qwq = 1;
double Sub3::qwq = 3.0;


int main() {
	Sub2::qwq = 2;
	Sub1::printqwq();
	Sub2::printqwq();
	Sub3::printqwq();

	return 0;
}