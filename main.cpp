#include "core.h"
#include "Draw.h"
#include "camera.h"
#include "pipeline.h"
#include "mesh.h"
int width = 600;
const int height = 400;
using namespace glm;

int main(int argc, char* argv[]) {
	//initial
	auto camera = new maincamera(
		vec3(0.0f, 0.0f, 3.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		glm::radians(45.0f),
		static_cast<float>(width) / static_cast<float>(height),
		0.1f,
		100.0f
	);
	SDL_Window* window;
	SDL_Renderer* renderer;
	auto pipeline = new Pipeline(width,height);
	window = SDL_CreateWindow("Soft Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	pipeline->initialize(camera);

	//Mesh push in
	glm::vec3 v1(-0.5f, -0.5f, 0.0f);
	glm::vec3 v2(0.5f, -0.5f, 0.0f);
	glm::vec3 v3(0.0f, 0.5f, 0.0f);

    Mesh *msh=new Mesh();
    msh->triangle(v1,v2,v3);
	//pipeline push in
	msh->triangle(v1,v2,v3);
    pipeline->setVertexBuffer(msh->vertices);
    pipeline->setIndexBuffer(msh->index);
		

	SDL_Event sdlEvent;
    bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT) {
				quit = true;
			}
		}
		//pipeline cycle
		pipeline->clearBuffer(glm::vec4(0,0,0,1.0f),false,renderer);
        pipeline->drawIndex(Pipeline::Fill,camera,renderer);

		//CAMERA Update
		camera->updateCamera();

	}

	return 0;
}