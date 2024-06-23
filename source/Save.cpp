#include "Save.h"

Save::Save(Vector<Polymorphic_Ptr<Image>>& images) : Commands(images) {}

Save::Save(Vector<Polymorphic_Ptr<Image>>& images, const MyString& newFileName) : Commands(images)
{
	this->newFileName = newFileName;
}

void Save::execute()
{
	if (newFileName.getSize() == 0)
		SaveAll();
	else
		SaveAs();
}

Commands* Save::clone() const
{
	return new Save(*this);
}

void Save::SaveAll()
{
	for (size_t i = 0; i < images.getSize(); i++)
	{
		images[i]->save(images[i].get()->getFileName());
	}
}

void Save::SaveAs()
{
	images[0]->save(newFileName);
}