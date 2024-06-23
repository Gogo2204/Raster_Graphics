#include <iostream>
#include <exception>
#include "Utility.h"
#include "Vector.hpp"
#include "MyString.h"
#include "Bitset.h"
#include "Image.h"
#include "ImageCreator.h"

int main()
{    
	MyString file("test.pbm");
	MyString file1("test1.pbm");
	try
	{
		Image* img = ImageCreator::readImageFile(file1);
		img->rotate(Utility::LEFT);
		img->save(file1);
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

