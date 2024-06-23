#include "Rotate.h"

Rotate::Rotate(Vector<Polymorphic_Ptr<Image>>& images, bool direction) : Commands(images)
{
	this->direction = direction;
}

void Rotate::execute()
{
	for (size_t i = 0; i < images.getSize(); i++)
	{
		images[i].get()->rotate(direction);
	}
}

Commands* Rotate::clone() const
{
	return new Rotate(*this);
}