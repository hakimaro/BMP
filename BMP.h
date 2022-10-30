#pragma once
struct pixel {
	unsigned char rgb[3] = { 0, 0, 0 };
};

#pragma pack(push, 1)
struct BMP_h {
	short type;
	unsigned int size;
	int reserved;
	int off_set_bits;
};
#pragma pack(pop)

struct BMP_i {
	unsigned int size;
	unsigned int width;
	unsigned int height;
	short planes;
	short bit_count;
	int compression;
	int size_image;
	int xpels_per_meter;
	int ypels_per_meter;
	int color_used;
	int colors_important;
};

class BMP {
private:
	BMP_h header;
	BMP_i info;
	pixel** px;
public:
	BMP() = default;
	BMP(const char* filename);
	inline BMP operator=(BMP bmp);
	inline BMP_h get_header() { return header; }
	inline BMP_i get_info() { return info; }
	inline pixel** get_pixels() { return px; }
	void set_pixels(pixel** px);
	void set_header(BMP_h header);
	void set_info(BMP_i info);
	void set(BMP_h header, BMP_i info, pixel** px);
	static void load_bmp(const char* filename, BMP_h header, BMP_i info, pixel** px);
	static void load_bmp(const char* filename, BMP bmp) { 
		load_bmp(filename, bmp.get_header(), bmp.get_info(), bmp.get_pixels());
	}
};



