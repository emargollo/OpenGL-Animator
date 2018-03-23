#include "Display.h"
#include "AnimatedModel\Mesh.h"
#include "AnimatedModel\Shader.h"
#include "AnimatedModel\Texture.h"
#include "Animation\Transform.h"
#include <string>

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv) {

	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Animator");

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(-0.5, 0.5, 0.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(0.5, 0.5, 0.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(-0.5, 0.5, 0.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0.0)) };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader(".\\res\\basicShader");
	Texture texture(".\\res\\bricks.jpg");
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

		transform.GetPos().y = sinf(counter);

		display.Clear(0.0, 0.0, 0.0, 1.0);
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform);
		mesh.Draw();

		display.SwapBuffers();
		counter += 0.01f;
	}
	return 0;
}