#pragma once
#include "Commands.h"
#include "Grayscale.h"
#include "Monochrome.h"
#include "Negative.h"
#include "Rotate.h"
#include "Save.h"

class CommandCreator
{
public:
	static Commands* createCommand(Vector<Polymorphic_Ptr<Image>>& images, MyString command);
	static Commands* createCommand(Vector<Polymorphic_Ptr<Image>>& images, MyString command, MyString& fileName);
};