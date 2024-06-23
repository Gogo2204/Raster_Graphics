#pragma once
#include "Commands.h"

class Save : public Commands
{
public:
	Save() = default;
	Save(Vector<Polymorphic_Ptr<Image>>& images);
	Save(Vector<Polymorphic_Ptr<Image>>& images, const MyString& newFileName);

	void execute() override;
	Commands* clone() const override;

private:
	MyString newFileName;

	void SaveAll();
	void SaveAs();
};