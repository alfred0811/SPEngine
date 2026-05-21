#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace SPEngine;
using namespace SPEngine::Graphics;

MeshPC MeshBuilder::CreateVertexCubePC(float size, const Color& color)
{
	MeshPC mesh;
	const float hs = size * 0.5f;

	mesh.vertices.push_back({ {-hs, -hs, -hs }, { color } });
	mesh.vertices.push_back({ { hs,  hs, -hs }, { color } });
	mesh.vertices.push_back({ { hs, -hs, -hs }, { color } });

	mesh.vertices.push_back({ {-hs, -hs, -hs }, { color } });
	mesh.vertices.push_back({ {-hs,  hs, -hs }, { color } });
	mesh.vertices.push_back({ { hs,  hs, -hs }, { color } });	

	return mesh;
}