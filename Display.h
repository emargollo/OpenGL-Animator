#ifndef DISPLAY_H
#define DISPLAY_H

#include<SDL\SDL.h>
#include <SDL\SDL_events.h>
#include <SDL\SDL_keyboard.h>
#include <GL\glew.h>
#include <stdio.h>
#include <iostream>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	~Display();

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();

private:
	SDL_Window * _window = NULL;
	SDL_GLContext _glContext;
	SDL_Surface* _screenSurface = NULL;
};

#endif