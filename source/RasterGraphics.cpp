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

void readLine(const MyString& line, bool& wantToExit)
{
	Vector<MyString> wordsInLine = separateWords(line);

	if (!std::strcmp(wordsInLine[0].c_str(), "load"))
	{
		Image* newImage = ImageCreator::readImageFile(wordsInLine[1]);
		Session* ses = new Session(newImage);
		SessionManager::getInstance().addSession(ses);

		std::cout << "\nSession with ID: " << SessionManager::getInstance().getSessionId() + 1 << " started" << std::endl;
		std::cout << "Image '" << wordsInLine[1] << "' added\n" << std::endl;

		for (size_t i = 2; i < wordsInLine.getSize(); i++)
		{
			ses->addImage(ImageCreator::readImageFile(wordsInLine[i]));
			std::cout << "Image '" << wordsInLine[i] << "' added\n" << std::endl;
		}
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "add"))
	{
		for (size_t i = 1; i < wordsInLine.getSize(); i++)
		{
			 SessionManager::getInstance().getCurrentSession()->addImage(ImageCreator::readImageFile(wordsInLine[i]));
			 std::cout << "Image '" << wordsInLine[i] << "' added\n" << std::endl;
		}
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "save"))
	{
		Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
		SessionManager::getInstance().getCurrentSession()->executeAllCommands();
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "saveas"))
	{
		Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0], wordsInLine[1]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
		SessionManager::getInstance().getCurrentSession()->executeAllCommands();
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "close"))
	{
		SessionManager::getInstance().getCurrentSession()->executeAllCommands();
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "exit"))
	{
		SessionManager::getInstance().getCurrentSession()->executeAllCommands();
		wantToExit = true;
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "grayscale"))
	{
		Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "monochrome"))
	{
		Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "negative"))
	{
		Commands* newCommand = CommandCreator::createCommand(SessionManager::getInstance().getCurrentSession()->getImages(), wordsInLine[0]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "rotate"))
	{
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
		std::cout << SessionManager::getInstance().getCurrentSession()->getSessionInfo();
		std::cout << std::endl;
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "undo"))
	{
		SessionManager::getInstance().getCurrentSession()->undo();
	}
	else if (!std::strcmp(wordsInLine[0].c_str(), "switch"))
	{
		unsigned index = Utility::convertToNum(wordsInLine[1][0]);
		SessionManager::getInstance().switchSession(index);
		std::cout << "You switched to session with ID: " << index << "!" << std::endl;
	}
	else
	{
		throw std::exception("There is no such command!");
	}
}

int main()
{    
	bool wantToExit = false;
	while (!wantToExit)
	{
		std::cout << "> ";

		char temp[Utility::BUFFER];
		std::cin.getline(temp, Utility::BUFFER);
		MyString line(temp);

		try
		{
			readLine(line, wantToExit);
		}
		catch (std::exception exc)
		{
			std::cout << exc.what() << std::endl;
		}
	}

	return 0;
}