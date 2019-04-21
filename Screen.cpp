/*
 * Screen.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: mqadri
 */

#include "Screen.h"

namespace sdlscreen {

Screen::Screen():
		m_window(NULL), m_renderer(NULL), m_texture(NULL),
		m_buffer1(new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]),
		m_buffer2(new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]) {

}

bool Screen::init() {
	const char* TITLE = "Particle fire explosion";

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}
	m_window = SDL_CreateWindow(TITLE,
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	// SDL_CreateWindow returns null on failure
	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == NULL) {
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	// SDL_PIXELFORMAT_RGBA8888: 32 bits per pixel, each byte represent once color in RGBA

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_texture == NULL) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));


	return true;
}

void Screen::clear() {
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
}

void Screen::update() {
	// pitch aka The number of bytes in a row of pixel data is numberSCREEN_WIDTH*sizeof(Uint32)
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	if (x < 0 or x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	m_buffer1[(y*SCREEN_WIDTH + x)] = color;
}

bool Screen::processEvents() {
	// if there is an event in the queue, SDL_PollEvent will process the event and fill in info in the variable event

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

void Screen::boxBlur() {
	// Swap the buffers, so pixel is in m_buffer2 and we are drawing to m_buffer1
	Uint32 *temp = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = temp;
	for(int y=0; y<SCREEN_HEIGHT; y++){
		for(int x=0; x< SCREEN_WIDTH; x++) {

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;
			for(int row=-1; row <= 1; row++) {
				for(int col=-1; col <= 1; col++){
					int currentX = x + col;
					int currentY = y + row;
					if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >=0 && currentY < SCREEN_HEIGHT) {
						Uint32 color = m_buffer2[currentY*SCREEN_WIDTH + currentX];
						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;
						redTotal+=red;
						blueTotal+=blue;
						greenTotal+=green;
					}
				}
			}
			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			setPixel(x, y, red, green, blue);
		}
	}

}

void Screen::close() {
	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
}
