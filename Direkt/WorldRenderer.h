#pragma once
#include "Renderable.h"
#include "World.h"
class WorldRenderer :
	public Renderable
{
public:
	void Render();
	WorldRenderer();
	~WorldRenderer();
};

