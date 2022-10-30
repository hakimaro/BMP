#include <iostream>
#include "BMP.h"

int main()
{
	const char* name1 = "name1.bmp";
	const char* newn1 = "new_name1.bmp";
	const char* name2 = "name2.bmp";
	const char* newn2 = "new_name2.bmp";

	BMP bmp;
	BMP bmp1(name2);
	bmp.set(bmp1.get_header(), bmp1.get_info(), bmp1.get_pixels());
	BMP::load_bmp(newn1, bmp.get_header(), bmp.get_info(), bmp.get_pixels());
	BMP bmp2 = bmp;
	BMP::load_bmp(newn2, bmp2);
}