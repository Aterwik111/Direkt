#include "stdafx.h"
#include "Renderable.h"


Renderable::Renderable()
{
}
void Renderable::SetActive(){
	if (!bActive){
		Graphic->thingsToRender.push_back(this);
		it = Graphic->thingsToRender.end();
		it--;
		bActive = true;
	}
}
void Renderable::SetInactive(){
	if (bActive){
		Graphic->thingsToRender.erase(it);
		bActive = false;
	}
}
void Renderable::Render(){
	DirectStuff->m_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}
Renderable::~Renderable()
{
	SetInactive();
}
