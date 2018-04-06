#include "Render\Display.h"
#include "AnimatedModel\Mesh.h"
#include "Render\Shader.h"
#include "AnimatedModel\Texture.h"
#include "Animator\Transform.h"
#include "Render\Camera.h"
#include <string>
#include "nlohmann\json.hpp"
#include <iostream>
#include "AnimatedModel\Model.h"
#include <fstream>

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv) {
	
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Animator");

	Model model;
	model.LoadModel(".\\res\\model.json");

	Camera camera(glm::vec3(0.0, -15.0, 5.0), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	Transform transform;

	float counter = 0.0f;

	SDL_Event event;

	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	double deltaTime = 0;

	model.getAnimator()->startAnimation("");

	while (true)
	{
		last = now;
		now = SDL_GetPerformanceCounter();

		deltaTime = (double)((now - last) / (double) SDL_GetPerformanceFrequency());
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return 0;
				break;
			}
		}

		display.Clear(0.0, 0.0, 0.0, 1.0);
		model.Update(deltaTime);
		model.Draw(transform, camera);

		display.SwapBuffers();
		counter += 0.01f;

	}

	return 0;
}