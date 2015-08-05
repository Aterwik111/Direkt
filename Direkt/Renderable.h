#pragma once
#include "stdafx.h"
class Renderable
{
protected:
	std::list<Renderable*>::iterator it;
public:
	bool bActive;
	virtual void Render() = 0;
	Renderable();
	void SetActive();
	void SetInactive();
	virtual ~Renderable();
};

