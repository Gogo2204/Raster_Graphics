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
		throw std::logic_error("There is no such session with ID");
	currentSession = index;
}

void SessionManager::closeSession()
{
	sessions.erase(currentSession);
	if(currentSession != 0)
		currentSession--;

	if (currentSession == 0)
		sessions.clear();
}

Session* SessionManager::getCurrentSession()
{
	return sessions[currentSession].get();
}

unsigned SessionManager::getSessionId() const
{
	return currentSession;
}