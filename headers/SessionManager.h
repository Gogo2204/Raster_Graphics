#pragma once
#include "Session.h"

class SessionManager
{
public:
	SessionManager(const SessionManager& other) = delete;
	SessionManager& operator=(const SessionManager& other) = delete;

	static SessionManager& getInstance();

	void addSession(Session* newSession);
	void switchSession(unsigned index);
	void closeSession();

	Session* getCurrentSession();
	unsigned getSessionId() const;

private:
	SessionManager() = default;
	~SessionManager() = default;

	unsigned currentSession = 0;
	Vector<Polymorphic_Ptr<Session>> sessions;
};