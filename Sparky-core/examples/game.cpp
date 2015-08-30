#include "../src/sparky.h"

using namespace sparky;
using namespace graphics;

class Game : public Sparky
{
private:
	Window* window;
	Layer* layer;
	Label* fps;
	Label* ups;
	Sprite* sprite;
	Shader* shader;
public:
	Game()
	{

	}

	~Game()
	{

	}

	void init() override
	{
		window = createWindow("Test Game", 960, 540);
		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);
#ifdef SPARKY_EMSCRIPTEN
		shader = new Shader("res/shaders/basic.es3.vert", "res/shaders/basic.es3.frag");
#else
		shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
#endif
		layer = new Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
#ifdef SPARKY_EMSCRIPTEN
    sprite = new Sprite(0.0f, 0.0f, 4, 4, new Texture("Tex", "res/test1.png"));
#else
		sprite = new Sprite(0.0f, 0.0f, 4, 4, new Texture("Tex", "test1.png"));
#endif
		layer->add(sprite);

		fps = new Label("", -15.5, 7.5, 0xffffffff);
		ups = new Label("", -15.5, 4.5, 0xffffffff);

		layer->add(fps);
		layer->add(ups);

    //audio::SoundManager::add(new audio::Sound("Angel", "Angel's Breath.ogg"))->play();
    
	}

	void tick() override
	{
		fps->text = std::to_string(getFPS()) + " fps";
		//ups->text = std::to_string(getUPS()) + " ups";
    SPARKY_INFO(getUPS(), "ups, ", getFPS(), " fps");
	}

	void update() override
	{
		float speed = 0.5f;
		if (window->isKeyPressed(GLFW_KEY_UP))
			sprite->position.y += speed;
		else if (window->isKeyPressed(GLFW_KEY_DOWN))
			sprite->position.y -= speed;
		if (window->isKeyPressed(GLFW_KEY_LEFT))
			sprite->position.x -= speed;
		else if (window->isKeyPressed(GLFW_KEY_RIGHT))
			sprite->position.x += speed;

		maths::vec2 mouse = window->getMousePosition();
		shader->setUniform2f("light_pos", maths::vec2((float)(mouse.x * 32.0f / window->getWidth() - 16.0f), (float)(9.0f - mouse.y * 18.0f / window->getHeight())));
	}

	void render() override
	{
		layer->render();
	}

};

int main()
{
	Game game;
	game.start();
	return 0;
}