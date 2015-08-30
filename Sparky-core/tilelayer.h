#pragma once

#include "src\graphics\layers\layer.h"
#include "src\graphics\batchrenderer2D.h"

	class TileLayer : public sparky::graphics::Layer
	{
	public:
		TileLayer(sparky::graphics::Shader* shader);
		virtual ~TileLayer();			
	};

	