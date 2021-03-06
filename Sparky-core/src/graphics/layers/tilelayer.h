#pragma once

#include "layer.h"
#include "..\batchrenderer2D.h"

namespace sparky{
	namespace graphics{

		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			virtual ~TileLayer();			
		};

	}
}