#pragma once

#include "ImageMatrix.h"
#include "MyForm.h"

class BmpFile : public ImageMatrix{
private:
	BITMAPFILEHEADER  File;       //Структура заголовока файла
	BITMAPINFOHEADER  Head;       //Структура параметров растра
	HFILE hFile;

	void pixel_matrix_in_bmp(unsigned int i, BYTE* strok);
	void bmp_into_pixel_matrix(unsigned int i, BYTE* strok);

public:

	BmpFile(char* way, prog3v3::MyForm^ mb);
	BmpFile(ImageMatrix* Bitmap);

	void bmp_writer(char* way);	
};
