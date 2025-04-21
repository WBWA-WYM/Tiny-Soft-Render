#include "core.h"
#include "Draw.h"
#include "camera.h"
#include "pipeline.h"
#include "mesh.h"


const int   FPS_CAP     = 60;                       // 最大帧率
const Uint32 FRAME_DELAY = 1000u / FPS_CAP;         // 每帧的毫秒目标

// helper: 将一个 Mesh 的顶点/索引追加到场景缓冲，并且加上偏移，使得每个mesh互相索引不会冲突
void appendMeshToScene(
    const Mesh& mesh,
    std::vector<Vertex>& sceneVerts,
    std::vector<unsigned int>& sceneIdx
) {
    unsigned int base = (unsigned int)sceneVerts.size();
    // append verts
    sceneVerts.insert(sceneVerts.end(), mesh.vertices.begin(), mesh.vertices.end());
    // append indices (with offset)
    for (auto i : mesh.index) {
        sceneIdx.push_back(base + i);
    }
}


int width = 600;
const int height = 400;
using namespace glm;



int main(int argc, char* argv[]) {
//initial
//pos gol up fov asp near far
	auto camera = new maincamera(
		vec3(0.0f, 10.0f, 18.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		glm::radians(45.0f),
		static_cast<float>(width) / static_cast<float>(height),
		0.1f,
		100.0f
	);

// 准备一个大的场景顶点/索引缓冲
	std::vector<Vertex> sceneVertices;
	std::vector<unsigned int> sceneIndices;

// 1) 地面：10×10 平面，center 在 (0,0,0)
{
    Mesh ground;
    ground.plane(10.0f, 10.0f, /*textureID*/0, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
    appendMeshToScene(ground, sceneVertices, sceneIndices);
}

// 2) 多个立方体：边长 1，排列成 3×3 网格，间距 2
{
    float cubeSize = 1.0f;
    float spacing  = 2.0f;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            float x = (col - 1) * spacing;
            float z = (row - 1) * spacing;
            Mesh cube;
// 偏移位置 (x, 高度 = cubeSize/2, z)，让立方体底面正好接触地面
            cube.cube(cubeSize, /*textureID*/0, glm::vec4(x, cubeSize*0.5f, z, 0.0f));
            appendMeshToScene(cube, sceneVertices, sceneIndices);
        }
    }
}

	SDL_Window* window;
	SDL_Renderer* renderer;
	auto pipeline = new Pipeline(width,height);
	window = SDL_CreateWindow("Soft Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	pipeline->initialize(camera);

	// 3) 送入管线
	pipeline->setVertexBuffer(sceneVertices);
	pipeline->setIndexBuffer(sceneIndices);
		
	SDL_Event sdlEvent;
    bool quit = false;
	Uint32 frameStart;  
	int    frameTime;

	while (!quit) {
//记录帧开始时间
		frameStart = SDL_GetTicks();           
//处理事件
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT) {
				quit = true;
			}
		}
//pipeline cycle
		pipeline->clearBuffer(glm::vec4(0,0,0,1.0f),false,renderer);
        pipeline->drawIndex(Pipeline::Fill,camera,renderer);
		SDL_RenderPresent(renderer);
//camera update
		camera->updateCamera();

//计算本帧耗时，并根据目标帧时延做延迟
		frameTime = SDL_GetTicks() - frameStart;
		if (FRAME_DELAY > static_cast<Uint32>(frameTime)) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}



	return 0;
}