#pragma once

#include "MeshTypes.h"

namespace SPEngine::Graphics
{
	class MeshBuilder
	{
	public:
		// cube
		static MeshPC CreateVertexCubePC(float size, const Color& color);
	};
}