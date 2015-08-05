#pragma once
#include "stdafx.h"
class SyncLock
{
public:
	SyncLock(std::mutex &m);
	operator bool() const;
	void setUnlock();
	~SyncLock();
private:
	std::mutex &m_mutex;
	bool m_locked;
};

