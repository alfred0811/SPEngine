#include "Precompiled.h"
#include "RenderObject.h"

using namespace SPEngine;
using namespace SPEngine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();

	TextureManager* tm = TextureManager::Get();
	tm->ReleaseTexture(diffuseMapId);
	tm->ReleaseTexture(specMapId);
	tm->ReleaseTexture(normMapId);
	tm->ReleaseTexture(bumpMapId);
}