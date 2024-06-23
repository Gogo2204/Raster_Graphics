#include "SessionManager.h"

SessionManager& SessionManager::getInstance()
{
	static SessionManager instance;
	return instance;
}

void SessionManager::addSession(Session* newSession)
{
	sessions.push_back(newSession);
	currentSession = sessions.getSize() - 1;
}

void SessionManager::switchSession(unsigned index)
{
	if (index >= sessions.getSize())
		return;
	currentSession = index;
}

void SessionManager::closeSession()
{
	//sessions.erase(currentSession);
}

Session* SessionManager::getCurrentSession()
{
	return sessions[currentSession].get();
}

unsigned SessionManager::getSessionId() const
{
	return currentSession;
}