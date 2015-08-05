#include "stdafx.h"
#include "Synchronization.h"


SyncLock::SyncLock(std::mutex &m) : m_mutex(m), m_locked(true)
{
	m_mutex.lock();
}

SyncLock::~SyncLock()
{
	m_mutex.unlock();
}
void SyncLock::setUnlock()
{
	m_locked = false;
}
SyncLock::operator bool() const
{
	return m_locked;
}

