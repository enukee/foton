#pragma once

#include "pixel.h"

class ImageMatrix {
protected:
	unsigned int img_Height = 0;                    // Высота изображения
	unsigned int img_Width = 0;                     // Ширина изображения

	Pixel<BYTE>** matrix;       //Матрица изображения 

	ImageMatrix();

public:
	ImageMatrix(unsigned int height, unsigned int width);

	~ImageMatrix();

	
	void set_pixel(Pixel<BYTE> value, unsigned int i, unsigned int j);
	void set_pixel(BYTE canal_R, BYTE canal_G, BYTE canal_B, unsigned int i, unsigned int j);

	Pixel<BYTE> get_pixel(unsigned int i, unsigned int j);
	void get_row_matrix(Pixel<BYTE>* matr, unsigned int i);
	void get_row_matrix(Pixel<BYTE>* matr, unsigned int i, unsigned int y, unsigned int x);

	// геттер высоты изображения
	unsigned int get_height();
	// геттер ширины изображения
	unsigned int get_width();

	//void copy(ImageMatrix Bitmap);
	void recording(ImageMatrix* Bitmap, unsigned int y, unsigned int x);
	void cut_out(ImageMatrix* Bitmap, unsigned int y, unsigned int x);
	Pixel<double> avg();
	Pixel<double>sd();
};
