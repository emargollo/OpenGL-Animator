#include "Display.h"
#include "AnimatedModel\Mesh.h"
#include "AnimatedModel\Shader.h"
#include "AnimatedModel\Texture.h"
#include "Animation\Transform.h"
#include "Camera\Camera.h"
#include <string>
#include "nlohmann\json.hpp"
#include <iostream>

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv) {
	
	//nlohmann::json j = nlohmann::json::parse("{\"json\": \"string\"}");
	//std::cout << j << std::endl;

	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Animator");

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(-0.5, 0.5, 0.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(0.5, 0.5, 0.0), glm::vec2(1.0, 1.0)) };
	unsigned int indices[] = { 0, 1, 2, 3, 2, 1 };
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	
	Mesh cube(".\\res\\monkey3.obj");
	
	Shader shader(".\\res\\basicShader");
	//Texture texture(".\\res\\bricks.jpg");
	Texture texture(".\\res\\c0003_t01_cat102.png");
	Camera camera(glm::vec3(0.0, 1.0, -3), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	Transform transform;

	float counter = 0.0f;

	SDL_Event event;
	while (true) {
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return 0;
				break;
			}

		}

		transform.GetPos().z = sinf(counter);
		transform.GetRot() = glm::quat(glm::vec3(0.0f, counter, 0.0f));

		display.Clear(0.0, 0.0, 0.0, 1.0);
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		cube.Draw();
		mesh.Draw();

		display.SwapBuffers();
		counter += 0.01f;
	}
	return 0;
}