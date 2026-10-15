#include "Precompiled.h"
#include "RenderObject.h"

using namespace SPEngine;
using namespace SPEngine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();
}