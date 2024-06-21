#pragma once
#include "Commands.h"
#include "GrayMap.h"

class Grayscale : public Commands
{
public:
	Grayscale() = default;
	Grayscale(Vector<Polymorphic_Ptr<Image>>& images);

	void execute() override;

	Commands* clone() const override;

private:
	GrayMap* turnToGrayMap(size_t index);
};