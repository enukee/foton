#pragma once
#pragma once

using namespace std;
#include "imgmatrix.h"

#define ALING4(x) ((((x)-1)/4+1)*4) //Макрос - дополнение величины до ближайшей кратной 4

class ImgBmp {
private:
	BITMAPFILEHEADER  File;       //Структура заголовока файла
	BITMAPINFOHEADER  Head;       //Структура параметров растра
	HFILE hFile;

public:
	ImageMatrix Bitmap;

	ImgBmp(char* way, ImageMatrix Bitmap_1) {
		Bitmap = Bitmap_1;
		unsigned int Height = Bitmap.get_height();
		unsigned int Width = Bitmap.get_width();

		//Заполнение структуры нулевыми значениями
		ZeroMemory(&Head, sizeof(Head));

		//Заполнение необходимых полей параметров растра
		Head.biSize = 40;
		Head.biHeight = Height;
		Head.biWidth = Width;
		Head.biSizeImage = Height + Width * 3;
		Head.biPlanes = 1;
		Head.biBitCount = 24;

		//Заполнение структуры заголовка файла
		File.bfOffBits = sizeof(Head) + sizeof(File);
		File.bfSize = sizeof(File) + sizeof(Head) + Height * Width * 3;
		File.bfType = 'B' + (int)'M' * 256;

		char b[4] = {0};
		int w = 0;
		hFile = _lcreat(way, 0);
		if (hFile != HFILE_ERROR)
		{
			Pixel<byte> pixel;
			_lwrite(hFile, (const char*)&File, sizeof(File));
			_lwrite(hFile, (const char*)&Head, sizeof(Head));
			for (unsigned int i = 0; i < Height; i++) {
				for (unsigned int j = 0; j < Width; j++) {
					pixel = Bitmap.get_pixel(Height - i - 1, j);
					_lwrite(hFile, (const char*)&pixel.canal_B, 1);
					_lwrite(hFile, (const char*)&pixel.canal_G, 1);
					_lwrite(hFile, (const char*)&pixel.canal_R, 1);
				}



				w = ALING4(Width * 3) - Width * 3;
				_lwrite(hFile, b, w);
				//for (unsigned int k = 0; k < w; k++) {
				//	_lwrite(hFile, 0, 1);
				//}
			}

			_lclose(hFile);
			
		}
		
		else MessageBox(0, L"Ошибка создания файла BMP", L"Ошибка", MB_OK);
	}

	ImgBmp(char* way) {
		hFile = _lopen(way, OF_READ);
		if (hFile != HFILE_ERROR) //Если файл открылся нормально
		{
			_lread(hFile, (char*)&File, sizeof(File));
			_lread(hFile, (char*)&Head, sizeof(Head));

			unsigned int Height = Head.biHeight;
			unsigned int Width = Head.biWidth;

			//ImageMatrix Bitmap(Height, Width);
			Bitmap = ImageMatrix (Height, Width);

			Pixel<BYTE> bytes;
			Pixel<BYTE>* matrix = new Pixel<BYTE> [Width];

			for (unsigned int i = 0; i < Height; i++) {
				for (unsigned int j = 0; j < Width; j++) {
					_lread(hFile, (char*)&bytes.canal_B, 1);
					_lread(hFile, (char*)&bytes.canal_G, 1);
					_lread(hFile, (char*)&bytes.canal_R, 1);

					Bitmap.set_pixel(bytes, Bitmap.get_height() - i - 1, j);
				}

				for (unsigned int k = 0; k < ALING4(Bitmap.get_width() * 3) - Bitmap.get_width() * 3; k++) {
					_lread(hFile, (char*)&bytes, 1);
				}
			}

			delete[] matrix;
		}
		else MessageBox(0, L"Ошибка открытия файла изображения", L"Ошибка", MB_OK);
	}
};