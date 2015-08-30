#if 0
#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/timer.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/batchrenderer2D.h"

#include "src/graphics/sprite.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/layers/group.h"

#include "src/graphics/font_manager.h"
#include "src/graphics/label.h"
#include "src/graphics/texture.h"

#include "src/audio/sound_manager.h"

#include "tilelayer.h"

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace audio;
	using namespace maths;

	Window window("Sparky",960,540);
	//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);	
	
	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	
	srand(time(NULL));

	TileLayer layer(&shader);

	Texture* textures[] =
	{
		new Texture("test.png"),
		new Texture("tb.png"),
		new Texture("tc.png")
	};

	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x ++)
		{
			int r = rand() % 256;

			int col = 0xffff00 << 8 | r;
			if (rand() % 4 == 0)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, col));
			else
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3])); 
		}
	}
	
	FontManager::add(new Font("SourceSansPro", "SourceSansPro-Light.ttf", 50));

	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.8f, 7.0f, 0.0f)));
	Label* fps = new Label("", 0.4f, 0.4f, "SourceSansPro", 0xffffffff);
	g->add(new Sprite(0, 0, 5, 1.5f, 0xDD888888));
	g->add(fps);

	layer.add(g);	
	
	shader.enable();
	shader.setUniformMat4f("pr_matrix",maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	SoundManager::add(new Sound("Cherno", "Cherno.ogg"));
	SoundManager::add(new Sound("Angel's Breath", "Angel's Breath.ogg"));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float gain = 0.5f;
	SoundManager::get("Angel's Breath")->setGain(gain);
	while (!window.closed())
	{		
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));		
		layer.render();
		
		if (window.isKeyTyped(GLFW_KEY_P))
			SoundManager::get("Angel's Breath")->play();
		if (window.isKeyTyped(GLFW_KEY_L))
			SoundManager::get("Angel's Breath")->loop();
		if (window.isKeyTyped(GLFW_KEY_X))
			SoundManager::get("Angel's Breath")->pause();
		if (window.isKeyTyped(GLFW_KEY_S))
			SoundManager::get("Angel's Breath")->stop();
		if (window.isKeyTyped(GLFW_KEY_UP))
		{
			gain += 0.1f;
			SoundManager::get("Angel's Breath")->setGain(gain);
		}
		if (window.isKeyTyped(GLFW_KEY_DOWN))
		{
			gain -= 0.1f;
			SoundManager::get("Angel's Breath")->setGain(gain);
		}
		

		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			printf("%d fps\n", frames);
			frames = 0;
		}
	}
	for (int i = 0; i < 3; i++)
		delete textures[i];

	return 0;
}
#endif

