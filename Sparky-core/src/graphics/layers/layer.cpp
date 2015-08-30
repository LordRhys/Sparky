#include "layer.h"

namespace sparky { namespace graphics {

		Layer::Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix)
			: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
		{
			m_Shader->enable();
			m_Shader->setUniformMat4f("pr_matrix", m_ProjectionMatrix);

#ifdef SPARKY_EMSCRIPTEN
			m_Shader->setUniform1i("textures_0",   0);
			m_Shader->setUniform1i("textures_1",   1);
			m_Shader->setUniform1i("textures_2",   2);
			m_Shader->setUniform1i("textures_3",   3);
			m_Shader->setUniform1i("textures_4",   4);
			m_Shader->setUniform1i("textures_5",   5);
			m_Shader->setUniform1i("textures_6",   6);
			m_Shader->setUniform1i("textures_7",   7);
			m_Shader->setUniform1i("textures_8",   8);
			m_Shader->setUniform1i("textures_9",   9);
			m_Shader->setUniform1i("textures_10", 10);
			m_Shader->setUniform1i("textures_11", 11);
			m_Shader->setUniform1i("textures_12", 12);
			m_Shader->setUniform1i("textures_13", 13);
			m_Shader->setUniform1i("textures_14", 14);
			m_Shader->setUniform1i("textures_15", 15);
			m_Shader->setUniform1i("textures_16", 16);
			m_Shader->setUniform1i("textures_17", 17);
			m_Shader->setUniform1i("textures_18", 18);
			m_Shader->setUniform1i("textures_19", 19);
			m_Shader->setUniform1i("textures_20", 20);
			m_Shader->setUniform1i("textures_21", 21);
			m_Shader->setUniform1i("textures_22", 22);
			m_Shader->setUniform1i("textures_23", 23);
			m_Shader->setUniform1i("textures_24", 24);
			m_Shader->setUniform1i("textures_25", 25);
			m_Shader->setUniform1i("textures_26", 26);
			m_Shader->setUniform1i("textures_27", 27);
			m_Shader->setUniform1i("textures_28", 28);
			m_Shader->setUniform1i("textures_29", 29);
			m_Shader->setUniform1i("textures_30", 30);
			m_Shader->setUniform1i("textures_31", 31);
#else
			GLint texIDs[] =
			{
				 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};

			m_Shader->setUniform1iv("textures", texIDs, 32);
#endif // SPARKY_EMSCRIPTEN			
			m_Shader->disable();
		}

		Layer::~Layer()
		{
			delete m_Shader;
			delete m_Renderer;

			for (int i = 0; i < m_Renderables.size(); i++)
			{
				delete m_Renderables[i];
			}
		}

		void Layer::add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Layer::render()
		{
			m_Shader->enable();
			m_Renderer->begin();
	
			for (const Renderable2D* renderable : m_Renderables)
				renderable->submit(m_Renderer);
	
			m_Renderer->end();
			m_Renderer->flush();			
		}

} }