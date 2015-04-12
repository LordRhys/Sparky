#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2D.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/utils/timer.h"

#include "src/graphics/layers/tilelayer.h"

#include <time.h>

#define BATCH_RENDERER 1

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky",960,540);
	//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);	
	
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");	
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);
	layer.add(new Sprite(0, 0, 2, 2, 0xF252CA));
	

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{		
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		layer.render();

		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}		
	}
		
	return 0;
}


