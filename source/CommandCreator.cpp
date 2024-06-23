#include "CommandCreator.h"

Commands* CommandCreator::createCommand(Vector<Polymorphic_Ptr<Image>>& images, MyString command)
{
	
	if (!std::strcmp(command.c_str(), "grayscale"))
	{
		return new Grayscale(images);
	}
	else if (!std::strcmp(command.c_str(), "monochrome"))
	{
		return new Monochrome(images);
	}
	else if (!std::strcmp(command.c_str(), "negative"))
	{
		return new Negative(images);
	}
	else if (!std::strcmp(command.c_str(), "rotateleft"))
	{
		return new Rotate(images, Utility::LEFT);
	}
	else if (!std::strcmp(command.c_str(), "rotateright"))
	{
		return new Rotate(images, Utility::RIGHT);
	}
	else if (!std::strcmp(command.c_str(), "save"))
	{
		return new Save(images);
	}
}

Commands* CommandCreator::createCommand(Vector<Polymorphic_Ptr<Image>>& images, MyString command, MyString& fileName)
{
	if (!std::strcmp(command.c_str(), "saveas"))
	{
		return new Save(images, fileName);
	}
}