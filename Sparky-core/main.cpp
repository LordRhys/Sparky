#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/timer.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2D.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"

#include "src/graphics/layers/tilelayer.h"

#include "src/graphics/layers/group.h"

#include "src/graphics/texture.h"


#include <time.h>


#if 1
int main()
{
	using namespace sparky;
	using namespace graphics;
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
			//layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4((rand() % 1000 / 1000.0f), (rand() % 1000 / 1000.0f), (rand() % 1000 / 1000.0f), 1)));
			int v = rand() % 3;
			layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[v])); //textures[rand() % 3]));
		}
	}
	
	
	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	shader.setUniformMat4f("pr_matrix",maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
	
	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{		
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		//shader.enable();
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
	for (int i = 0; i < 3; i++)
	{
		delete textures[i];
	}
	return 0;
}
#endif

#if 0
int main()
{
	const char* filename = "test.png";
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unknown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plug-in has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	unsigned int bitsPerPixel = FreeImage_GetBPP(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	for (int i = 0; i < width * height * 3; i+=3)
	{
		
		int hex = bits[i] | bits[i + 1] << 8 | bits[i + 2] << 16 ;
		printf("%d  %x\n", i,hex);
	}


	return 0;
}

#endif


