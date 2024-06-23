#pragma once
#include "Commands.h"

class Negative : public Commands
{
public:
	Negative() = default;
	Negative(Vector<Polymorphic_Ptr<Image>>& images);

	void execute() override;
	MyString message() const override;

	Commands* clone() const override;

private:
	BitMap* negativeToBitMap(unsigned index);
	GrayMap* negativeToGrayMap(unsigned index);
	PixMap* negativeToPixMap(unsigned index);
};