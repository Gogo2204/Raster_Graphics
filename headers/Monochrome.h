#pragma once
#include "Commands.h"

class Monochrome : public Commands
{
public:
	Monochrome() = default;
	Monochrome(Vector<Polymorphic_Ptr<Image>>& images);

	void execute() override;
	MyString message() const override;

	Commands* clone() const override;

private:
	BitMap* fromGrayToBitMap(size_t index);
	BitMap* fromPixToBitMap(size_t index);
};