#include "BMP.h"
#include <fstream>
#include <iostream>

BMP::BMP(const char* filename) {
	std::ifstream file(filename, std::ios::binary | std::ios::in);
	if (file) {
		file.read((char*)&header, sizeof(header));
		file.read((char*)&info, sizeof(info));
		file.seekg(header.off_set_bits, std::ios::beg);
		px = new pixel * [info.height];
		for (size_t i = 0; i < info.height; i++) {
			px[i] = new pixel[info.width];
			for (size_t j = 0; j < info.width; j++) {
				file.read((char*)&px[i][j], sizeof(px[i][j]));
			}
			if ((4 - (info.width*3)) % 4 != 0) {
				file.seekg((4 - (info.width * 3)) % 4, std::ios::cur);
			}
		}
		file.close();
	}
}

BMP BMP::operator=(BMP bmp) {
	BMP clone;
	memcpy(&clone.header, &bmp.header, sizeof(bmp.header));
	memcpy(&clone.info, &bmp.header, sizeof(bmp.info));
	memcpy(&clone.px, &bmp.px, sizeof(bmp.px));
	return clone;
}

void BMP::set_pixels(pixel** px)
{
	memcpy(&this->px, &px, sizeof(px));
}

void BMP::set_header(BMP_h header) {
	memcpy(&this->header, &header, sizeof(header));
}

void BMP::set_info(BMP_i info) {
	memcpy(&this->info, &info, sizeof(info));
}

void BMP::set(BMP_h header, BMP_i info, pixel** px)
{
	set_header(header);
	set_info(info);
	set_pixels(px);
}

void BMP::load_bmp(const char* filename, BMP_h header, BMP_i info, pixel** px) {
	std::ofstream file(filename, std::ios::out | std::ios::binary);
	if (file) {
 		file.write((char*)&header, sizeof(header));
		file.write((char*)&info, sizeof(info));
		for (int i = 0; i < info.height; i++) {
			for (int j = 0; j < info.width; j++) {
				file.write((char*)&px[i][j], sizeof(px[i][j]));
			}
			if ((4 - (info.width*3)) % 4 != 0) {
				char zero = 0;
				file.write(&zero, 3);
			}
		}
		file.close();
	}
}
