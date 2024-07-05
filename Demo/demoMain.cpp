#define SDL_MAIN_HANDLED

#include <iostream>
#include <vector>
#include <memory>

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

int main() {
	std::vector<std::weak_ptr<int> > m_vecTempObservers;

	std::shared_ptr<int> a = std::make_shared<int>(10);
	std::shared_ptr<int> b = std::make_shared<int>(20);
	std::shared_ptr<int> c = std::make_shared<int>(30);
	std::shared_ptr<int> d = std::make_shared<int>(40);

	m_vecTempObservers.push_back(a);
	m_vecTempObservers.push_back(b);
	m_vecTempObservers.push_back(c);

	std::weak_ptr<int> qwq = d;

	/*
	auto it = std::find_if(
		m_vecTempObservers.begin(), m_vecTempObservers.end(),
		[&qwq](const std::weak_ptr<int>& wp) { return !wp.owner_before(qwq) && !qwq.owner_before(wp); }
	);
	*/

	if (d.owner_before(qwq) || qwq.owner_before(d)) {
		std::cout << "qwq" << std::endl;
	}

	return 0;
}