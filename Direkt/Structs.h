#pragma once
#include "stdafx.h"


struct positionI{
	int x, y;
};
struct positionD{
	double x, y;
	void operator=(const positionI& posI){
		this->x = posI.x;
		this->y = posI.y;
	}
};
struct AABB{
	double left, top, right, bottom;
};
struct BlockArea{
	int left, top, right, bottom;
	void CreateFromAABB(AABB aabb){

		this->left = static_cast<int> (aabb.left);
		if (signbit(aabb.left)){ //aabb.left < 0
			this->left--;
		}

		this->right = static_cast<int> (aabb.right) + 1;
		if (signbit(aabb.right)){ //aabb.right < 0
			this->right--;
		}

		if (signbit(aabb.bottom)){ //aabb.bottom < 0
			this->bottom = 0;
		}
		else if(aabb.bottom <= WORLD_HEIGHT){ //0 <= aabb.bottom <= WORLD_HEIGHT
			this->bottom = static_cast<int> (aabb.bottom);
		}
		else{ // aabb.bottom > WORLD_HEIGHT
			this->bottom = WORLD_HEIGHT;
		}

		if (signbit(aabb.top)){ //aabb.top < 0
			this->top = 0;
		}
		else if (aabb.top <= WORLD_HEIGHT){ //0 <= aabb.top <= WORLD_HEIGHT
			this->bottom = static_cast<int> (aabb.bottom)+1;
		}
		else{ // aabb.top > WORLD_HEIGHT
			this->top = WORLD_HEIGHT;
		}
	}
};
struct Chunk{
	std::array <int,CHUNK_WIDTH*WORLD_HEIGHT> blockTypes;
	int iNumber;

	int GetBlockTypeAtRelativePos(int x, int y){
		return blockTypes[y*CHUNK_WIDTH + x];
	}
	int GetBlockTypeAtRelativePos(positionI pos){
		return blockTypes[pos.y*CHUNK_WIDTH + pos.x];
	}
	void SetBlockTypeAtRelativePos(int x, int y, int iType){
		blockTypes[y*CHUNK_WIDTH + x] = iType;
	}
	void SetBlockTypeAtRelativePos(positionI pos, int iType){
		blockTypes[pos.y*CHUNK_WIDTH + pos.x] = iType;
	}
};
union value{
	int i;
	char bytes[sizeof(int)];
};
struct Fd{
	float fPixelsPerMeter = 16;
	AABB camAABB;
	positionD camPos;
};

