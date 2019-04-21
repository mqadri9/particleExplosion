/*
 * Screen.h
 *
 *  Created on: Apr 20, 2019
 *      Author: mqadri
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL2/SDL.h>

namespace sdlscreen {

class Screen {
public:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer1;
	Uint32 *m_buffer2;

public:
	Screen();
	bool init();
	bool processEvents();
	void update();
	void clear();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void close();
	void boxBlur();
};

}
#endif /* SCREEN_H_ */
