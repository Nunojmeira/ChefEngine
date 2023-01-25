#include "Precompiled.h"
#include "RenderObject.h"

using namespace ChefEngine;
using namespace ChefEngine::Graphics;

void RenderObject::Terminate()
{
	diffuseMapId = 0;
	meshBuffer.Terminate();
}