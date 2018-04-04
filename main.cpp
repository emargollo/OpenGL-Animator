#include "Display.h"
#include "AnimatedModel\Mesh.h"
#include "AnimatedModel\Shader.h"
#include "AnimatedModel\Texture.h"
#include "Animation\Transform.h"
#include "Camera\Camera.h"
#include <string>
#include "nlohmann\json.hpp"
#include <iostream>
#include "Utils\JSONLoader.h"
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
	while (true)
	{
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
		model.Draw(transform, camera);

		display.SwapBuffers();
		counter += 0.01f;
	}

	return 0;
}