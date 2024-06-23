#pragma once
#include "Commands.h"

class Grayscale : public Commands
{
public:
	Grayscale() = default;
	Grayscale(Vector<Polymorphic_Ptr<Image>>& images);

	void execute() override;
	MyString message() const override;

	Commands* clone() const override;

private:
	GrayMap* turnToGrayMap(size_t index);
};