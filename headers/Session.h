#pragma once
#include "Image.h"
#include "Commands.h"

class Session
{
public:
	Session() = default;
	Session(Image* image);

	Session* clone() const;

	void addImage(Image* image);
	void addCommand(Commands* command);

	Vector<Polymorphic_Ptr<Image>>& getImages();	

	void undo();
	void executeAllCommands();

	MyString getSessionInfo();

private:
	Vector<Polymorphic_Ptr<Image>> images;
	Vector<Polymorphic_Ptr<Commands>> commands;
};