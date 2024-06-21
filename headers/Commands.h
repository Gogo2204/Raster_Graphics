#pragma once
#include "Image.h"
#include "Polymorfic_Ptr.hpp"

class Commands
{
public:
	Commands(Vector< Polymorphic_Ptr<Image> >& images) : images(images) {}

	virtual void execute() = 0;

	virtual Commands* clone() const = 0;
	virtual ~Commands() = default;

protected:
	Vector< Polymorphic_Ptr<Image> >& images;
};