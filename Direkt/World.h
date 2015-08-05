#pragma once
#include "Structs.h"
class CWorld
{
public:
	std::mutex fileMutex, dataMutex;
	std::wstring folderName;	
	HANDLE hDataFile, hChunksFile;
	std::vector <Chunk> loadedChunks;
	bool Load(std::wstring folderName); 
	void Unload(); //
	bool Create(std::wstring folderName); 
	void GenerateChunk(int iNumber);
	bool LoadChunk(int iNumber);
	Chunk& GetChunk(int iNumber);
	bool isChunkLoaded(int iNumber);
	int GetBlockTypeAt(positionI pos);
	void SetBlockTypeAt(positionI pos, int iType);
	//void UnloadChunk(int iNumber);
	CWorld();
	~CWorld();
};
int InWhichChunk(int iBlockNum);
int InWhichChunk(positionI pos);
int InWhichChunk(positionD pos);

extern CWorld* World;