#pragma once
#include "Commands.h"

class Rotate : public Commands
{
public:
	Rotate() = default;
	Rotate(Vector<Polymorphic_Ptr<Image>>& images, bool direction);

	void execute() override;
	Commands* clone() const override;

private:
	bool direction;
};