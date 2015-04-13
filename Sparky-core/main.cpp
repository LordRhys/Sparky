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
#define TEST_50K_SPRITES 0

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky",960,540);
	//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);	
	
	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	Shader& shader2 = *s2;
	shader.enable();
	shader2.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader2.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	srand(time(NULL));

	TileLayer layer(&shader);

#if TEST_50K_SPRITES
	for (float y = -9.0f; y < 9.0f; y+= 0.1f)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1f)
		{
			
			int r = (int)((rand() % 1000 / 1000.0f) *255.0f);
			int g = (int)((rand() % 1000 / 1000.0f) *255.0f);
			int b = (int)((rand() % 1000 / 1000.0f) *255.0f);
			int a = 1 * 255;

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			layer.add(new Sprite(x, y, 0.09f, 0.09f, c));
		}
	}
#else
	/*for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{

			int r = (int)((rand() % 1000 / 1000.0f) *255.0f);
			int g = (int)((rand() % 1000 / 1000.0f) *255.0f);
			int b = (int)((rand() % 1000 / 1000.0f) *255.0f);
			int a = 1 * 255;

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			layer.add(new Sprite(x, y, 0.9f, 0.9f, c));
		}
	}*/

	Sprite* button = new Sprite(-15.0f, 5.0f, 6, 3, 0xffffffff);
	layer.add(button);
	layer.push(maths::mat4(button->getPosition()));
	layer.add(new Sprite(0.5, 0.5f, 5.0f, 2.0f, 0xffff00ff));
	layer.pop(maths::mat4(button->getPosition()));

#endif

	TileLayer layer2(&shader2);
	layer2.add(new Sprite(-2, -2, 4, 4, 0x00ffffff));		

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{		
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
		//shader2.enable();
		//shader2.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		layer.render();
		//layer2.render();

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


