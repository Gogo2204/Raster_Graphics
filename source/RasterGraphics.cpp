#include <iostream>
#include <fstream>
#include <exception>
#include "SessionManager.h"
#include "ImageCreator.h"
#include "CommandCreator.h"

Vector<MyString> separateWords(const MyString& str)
{
	Vector<MyString> words;
	char temp[Utility::BUFFER];

	int i = 0;
	int j = 0;
	
	while (i <= str.getSize())
	{
		if (str[i] != ' ')
		{
			temp[j] = str[i];
			j++;
		}
		else
		{
			temp[j] = '\0';			
			MyString word(temp);
			words.push_back(word);
			j = 0;
			temp[0] = '\0';
		}
		i++;
	}

	if (j > 0)
	{
		temp[j] = '\0';
		MyString word(temp);
		words.push_back(word);
	}
	
	return words;
}

void readLine(const MyString& line, bool& wantToExit, bool& isSessionStarted)
{
	Vector<MyString> wordsInLine = separateWords(line);

	if (!std::strcmp(wordsInLine[0].c_str(), "load"))
	{
		Image* newImage = ImageCreator::readImageFile(wordsInLine[1]);
		Session* newSession = new Session(newImage);
		SessionManager::getInstance().addSession(newSession);

		isSessionStarted = true;

		std::cout << "\nSession with ID: " << SessionManager::getInstance().getSessionId() + 1 << " started" << std::endl;
		std::cout << "\nImage '" << wordsInLine[1] << "' added\n" << std::endl;

		for (size_t i = 2; i < wordsInLine.getSize(); i++)
		{
			newSession->addImage(ImageCreator::readImageFile(wordsInLine[i]));
			std::cout << "\nImage '" << wordsInLine[i] << "' added\n" << std::endl;
		}
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "add"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		for (size_t i = 1; i < wordsInLine.getSize(); i++)
		{
			 SessionManager::getInstance().getCurrentSession()->addImage(ImageCreator::readImageFile(wordsInLine[i]));
			 std::cout << "\nImage '" << wordsInLine[i] << "' added\n" << std::endl;
		}
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "save"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
		SessionManager::getInstance().getCurrentSession()->executeAllCommands();

		unsigned currentSessionId = SessionManager::getInstance().getSessionId() + 1;
		std::cout << "\nYou saved a session with ID: " << currentSessionId << "!" << std::endl;
		SessionManager::getInstance().closeSession();
		if (currentSessionId == 1)
			isSessionStarted = false;
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "saveas"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0], wordsInLine[1]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
		SessionManager::getInstance().getCurrentSession()->executeAllCommands();

		unsigned currentSessionId = SessionManager::getInstance().getSessionId() + 1;
		std::cout << "\nYou saved a session with ID: " << currentSessionId << "!" << std::endl;
		SessionManager::getInstance().closeSession();
		if (currentSessionId == 1)
			isSessionStarted = false;
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "close"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		unsigned currentSessionId = SessionManager::getInstance().getSessionId() + 1; // because it starts from zero
		SessionManager::getInstance().closeSession();
		std::cout << "\nYou closed a session with ID: " << currentSessionId << "!" << std::endl;
		if (currentSessionId == 1)
			isSessionStarted = false;
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "exit"))
	{
		wantToExit = true;
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "grayscale"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "monochrome"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "negative"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "rotate"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		if (!std::strcmp(wordsInLine[1].c_str(), "left"))
		{
			Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0]+ wordsInLine[1]);
			SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
		}
		else if (!std::strcmp(wordsInLine[1].c_str(), "right"))
		{
			Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0] + wordsInLine[1]);
			SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
		}
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "sessioninfo"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		std::cout << SessionManager::getInstance().getCurrentSession()->getSessionInfo();
		std::cout << std::endl;
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "undo"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		SessionManager::getInstance().getCurrentSession()->undo();
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "switch"))
	{
		if (!isSessionStarted)
			throw std::logic_error("\nThere is no session started!");

		unsigned index = Utility::convertToNum(wordsInLine[1][0]);
		SessionManager::getInstance().switchSession(index - 1);
		std::cout << "\nYou switched to session with ID: " << index << "!" << std::endl;
	}
	else
	{
		throw std::exception("\nThere is no such command!");
	}
}

int main()
{    
	bool wantToExit = false;
	bool isSessionStarted = false;
	while (!wantToExit)
	{
		std::cout << "> ";

		char temp[Utility::BUFFER];
		std::cin.getline(temp, Utility::BUFFER);
		MyString line(temp);

		try
		{
			readLine(line, wantToExit, isSessionStarted);
		}
		catch (std::exception exc)
		{
			std::cout << exc.what() << std::endl;
		}
	}

	return 0;
}