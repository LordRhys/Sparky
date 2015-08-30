#pragma once

#include <vector>

#ifdef SPARKY_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else
	#include <GL/glew.h>
#endif // SPARKY_EMSCRIPTEN

#include "buffer.h"

namespace sparky {
	namespace graphics {

		class VertexArray
		{
		private:
			GLuint m_ArrayID;
			std::vector<Buffer*> m_Buffers;
		public:
			VertexArray();
			~VertexArray();

			void addBuffers(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;

		};

} }