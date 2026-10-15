#pragma once

#include "MeshBuffer.h"
#include "Transform.h"
#include "Material.h"

namespace SPEngine::Graphics
{
	class RenderObject
	{
	public:
		void Terminate();

		MeshBuffer meshBuffer; // shape, vertices, indices...
		Transform transform; // location/orientation
		Material material; // light data
	};
}