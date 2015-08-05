#include "stdafx.h"
#include "World.h"


CWorld::CWorld()
{
}
bool CWorld::Create(std::wstring folderName){
	bool ret = true;
	std::wstring tmpFilePath = L"Worlds\\" + folderName;
	synchronized(fileMutex){
		if (CreateDirectory(tmpFilePath.c_str(),NULL)){
			tmpFilePath = L"Worlds\\" + folderName + L"\\chunks.chd";
			hChunksFile = CreateFile(tmpFilePath.c_str(), GENERIC_ALL, 0, NULL, CREATE_NEW, 0, NULL);
			if (hChunksFile != INVALID_HANDLE_VALUE){
				tmpFilePath = L"Worlds\\" + folderName + L"\\data.wdd";
				hDataFile = CreateFile(tmpFilePath.c_str(), GENERIC_ALL, 0, NULL, CREATE_NEW, 0, NULL);
				if (hDataFile != INVALID_HANDLE_VALUE){
					synchronized(dataMutex){
						this->folderName = folderName;
					}
				}
				else{
					ret = false;
				}
			}
			else{
				ret = false;
			}
		}
		else{
			ret = false;
		}
		if (!ret){
			SafeCloseHandle(hChunksFile);
			SafeCloseHandle(hDataFile);
		}
	}
	return ret;
}
/*bool CWorld::Load(std::wstring folderName){
	std::wstring tmpFilePath = L"Worlds\\" + folderName + L"\\chunks.chd";
	int tmpKey, tmpValue;
	value Buffer[4];
	DWORD dwNumRead;
	bool ret = true;

	synchronized(fileMutex){
		hChunksFile = CreateFile(tmpFilePath.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (hChunksFile != INVALID_HANDLE_VALUE){
			tmpFilePath = L"Worlds\\" + folderName + L"\\data.wdd";
			hDataFile = CreateFile(tmpFilePath.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL);
			if (hDataFile != INVALID_HANDLE_VALUE){
				DWORD dwSize = GetFileSize(hChunksFile, NULL);
				for (DWORD d = 0; d < dwSize; d += 4){
					if (ReadFile(hChunksFile, Buffer->bytes, 4, &dwNumRead, NULL)){
						tmpKey = Buffer->i;
						if (ReadFile(hChunksFile, Buffer->bytes, 4, &dwNumRead, NULL)){
							tmpValue = Buffer->i;
							synchronized(dataMutex){
								chunkMappng[tmpKey] = tmpValue;
							}
						}
						else{
							ret = false;
							break;
						}
						synchronized(dataMutex){
							this->folderName = folderName;
						}
					}
					else{
						ret = false;
					}
				}
			}
			else{
				ret = false;
			}
		}
		else{
			ret = false;
		}
		if (!ret){
			SafeCloseHandle(hChunksFile);
			SafeCloseHandle(hDataFile);
		}
	}
	return ret;
}*/
void CWorld::Unload(){
	synchronized(fileMutex){
		SafeCloseHandle(hChunksFile);
		SafeCloseHandle(hDataFile);
	}
	synchronized(dataMutex){
		loadedChunks.clear();
		folderName = L"";
	}
}

void CWorld::GenerateChunk(int iNumber){
	Chunk tmpChunk;
	tmpChunk.iNumber = iNumber;
	for (int i = 0; i < CHUNK_WIDTH*128; i++){
		tmpChunk.blockTypes[i] = 1;
	}
	for (int i = CHUNK_WIDTH * 128; i < CHUNK_WIDTH * WORLD_HEIGHT; i++){
		tmpChunk.blockTypes[i] = 0;
	}
	loadedChunks.push_back(tmpChunk);
}
Chunk& CWorld::GetChunk(int iNumber){
	bool bFound = false;
	size_t s;
	for (s = 0; s < loadedChunks.size(); s++){
		if (loadedChunks[s].iNumber == iNumber){
			bFound = true;
			break;
		}
	}
	if (!bFound){
		GenerateChunk(iNumber);
		return loadedChunks.back();
	}
	return loadedChunks[s];
}
int CWorld::GetBlockTypeAt(positionI pos){
	int iChunkNumber = InWhichChunk(pos.x);
	positionI relativePos;
	if (pos.x >= 0){ relativePos.x = pos.x % CHUNK_WIDTH; }
	else{
		relativePos.x = (((pos.x % CHUNK_WIDTH) + 4) % 4);
	}
	relativePos.y = pos.y;
	return GetChunk(iChunkNumber).GetBlockTypeAtRelativePos(relativePos);
}
void CWorld::SetBlockTypeAt(positionI pos, int iType){
	int iChunkNumber = InWhichChunk(pos.x);
	positionI relativePos;
	if (pos.x >= 0){ relativePos.x = pos.x % CHUNK_WIDTH; }
	else{
		relativePos.x = (((pos.x % CHUNK_WIDTH) + 4) % 4);
	}
	relativePos.y = pos.y;
	GetChunk(iChunkNumber).SetBlockTypeAtRelativePos(relativePos, iType);
}
bool CWorld::isChunkLoaded(int iNumber){
	for (size_t s = 0; s < loadedChunks.size(); s++){
		if (loadedChunks[s].iNumber == iNumber){
			return true;
		}
	}
	return false;
}
bool CWorld::LoadChunk(int iNumber){
	//TODO do zrobienia
	return false;
}



int InWhichChunk(int iBlockNum){
	if (iBlockNum >= 0){
		return (iBlockNum / CHUNK_WIDTH);
	}
	return ((iBlockNum + 1 / CHUNK_WIDTH) - 1);
}
int InWhichChunk(positionI pos){
	if (pos.x >= 0){
		return (pos.x / CHUNK_WIDTH);
	}
	return ((pos.x + 1 / CHUNK_WIDTH) - 1);
}
int InWhichChunk(positionD pos){
	if (pos.x >= 0){
		return (static_cast<int>(floor(pos.x)) / CHUNK_WIDTH);
	}
	return ((static_cast<int>(floor(pos.x)) + 1 / CHUNK_WIDTH) - 1);
}


CWorld::~CWorld()
{
}
