#include "Session.h"

Session::Session(Image* image)
{
	images.push_back(image);
}

Session* Session::clone() const
{
	return new Session(*this);
}

void Session::addImage(Image* image)
{
	Polymorphic_Ptr<Image> newImage(image);
	images.push_back(newImage);
}

void Session::addCommand(Commands* command)
{ 
	Polymorphic_Ptr<Commands> newCommand(command);
	commands.push_back(newCommand);	
}

Vector<Polymorphic_Ptr<Image>>& Session::getImages()
{
	return images;
}

void Session::undo()
{
	if (commands.getSize() == 0)
		return;
	commands.pop_back();
}

void Session::executeAllCommands()
{
	for (size_t i = 0; i < commands.getSize(); i++)
	{
		commands[i].get()->execute();
	}
}

MyString Session::getSessionInfo()
{
	MyString result("Name of images in the session: ");

	for (size_t i = 0; i < images.getSize(); i++)
	{
		result += images[i].get()->getFileName() + " ";
	}

	result += MyString("\nPending transformations: ");

	for (size_t j = 0; j < commands.getSize(); j++)
	{
		result += commands[j].get()->message() + " ";
	}

	return result;
}