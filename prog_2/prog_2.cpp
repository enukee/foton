#include <iostream>
#include "windows.h"

#define ALING4(x) ((((x)-1)/4+1)*4) //Макрос - дополнение величины до ближайшей кратной 4

using namespace std;

float avg(BYTE* Bitmap, unsigned int size) { // Функция поиска среднего значения массива размером size
	float avg = 0;

	for (unsigned int i = 0; i < size; i++) {
		avg += (int)Bitmap[i];
	}
	avg /= size;

	return avg;
}

double sd(BYTE* Bitmap, unsigned int size) {// Функция поиска cреднеквадратическое отклонение массива размером size
	double sd = 0;
	float _avg = avg(Bitmap, size);

	for (unsigned int i = 0; i < size; i++) {
		sd += pow((Bitmap[i] - _avg), 2);
	}
	sd /= size;
	sd = sqrt(sd);

	return sd;
}

float kcor(BYTE* Bitmap_1, BYTE* Bitmap_2, unsigned int size) {
	float avg_1 = avg(Bitmap_1, size);
	float avg_2 = avg(Bitmap_2, size);

	int* Bitmap_1_2 = new int[size];

	double kof_kor;

	float avg_1_2 = 0;
	for (unsigned int i = 0; i < size; i++) {

		avg_1_2 += Bitmap_1[i]* Bitmap_2[i];
	}
	avg_1_2 /= size;

	double sd_1 = sd(Bitmap_1, size);
	double sd_2 = sd(Bitmap_2, size);

	kof_kor = (avg_1_2 - avg_1 * avg_2) / (sd_1 * sd_2);

	return kof_kor;
}

class Imgbmp {
public:
	BITMAPFILEHEADER  File;       //Структура заголовока файла
	BITMAPINFOHEADER  Head;       //Структура параметров растра

	BYTE*** Bitmap = new BYTE * *[3];       //Матрица изображения 

	unsigned int img_Height = Head.biHeight;    // Высота изображения
	unsigned int img_Width = Head.biWidth;    // Ширина изображения
	unsigned int size = img_Height * img_Width;   // Размер изображения

	Imgbmp(char* way) {
		HFILE hFile = _lopen(way, OF_READ);

		if (hFile != HFILE_ERROR) //Если файл открылся нормально
		{
			_lread(hFile, (char*)&File, sizeof(File));
			_lread(hFile, (char*)&Head, sizeof(Head));

			img_Height = Head.biHeight;    // Высота изображения
			img_Width = Head.biWidth;    // Ширина изображения
			size = img_Height * img_Width;   // Размер изображения

			for (unsigned int i = 0; i < 3; i++) {
				Bitmap[i] = new BYTE * [img_Height];
				for (unsigned int j = 0; j < img_Height; j++) {
					Bitmap[i][j] = new BYTE[img_Width];
				}
			}

			BYTE bytes;
			for (unsigned int i = 0; i < img_Height; i++) {
				for (unsigned int j = 0; j < img_Width; j++) {
					_lread(hFile, (char*)&bytes, 1);
					Bitmap[2][img_Height - i - 1][j] = bytes;
					_lread(hFile, (char*)&bytes, 1);
					Bitmap[1][img_Height - i - 1][j] = bytes;
					_lread(hFile, (char*)&bytes, 1);
					Bitmap[0][img_Height - i - 1][j] = bytes;
				}

				for (unsigned int k = 0; k < ALING4(img_Width * 3) - img_Width * 3; k++) {
					_lread(hFile, (char*)&bytes, 1);
				}
			}
		}
		else MessageBox(0, L"Ошибка открытия файла изображения", L"Ошибка", MB_OK);
	}

private:


};

int main()
{
	Imgbmp img_1((char*)"C:\\Users\\vi\\Desktop\\фотон\\prog_2\\image\\foto_1.bmp");
	Imgbmp img_2((char*)"C:\\Users\\vi\\Desktop\\фотон\\prog_2\\image\\foto_2.bmp");

	BYTE** Bitmap_im_1 = new BYTE* [3];
	for (unsigned int i = 0; i < 3; i++) {
		Bitmap_im_1[i] = new BYTE[img_2.img_Width];
	}

	for (unsigned int i = 0; i < img_1.img_Height - img_2.img_Height + 1; i++) {
		for (unsigned int j = 0; j < img_1.img_Width - img_2.img_Width + 1; j++) {

			for (unsigned int k = 0; k < img_2.img_Width ; k++) {
				Bitmap_im_1[0][k] = img_1.Bitmap[0][i][j + k];
				Bitmap_im_1[1][k] = img_1.Bitmap[1][i][j + k];
				Bitmap_im_1[2][k] = img_1.Bitmap[2][i][j + k];
			}

			if ((kcor(Bitmap_im_1[0], img_2.Bitmap[0][0], img_2.img_Width) > 0.99) &&
				(kcor(Bitmap_im_1[1], img_2.Bitmap[1][0], img_2.img_Width) > 0.99) &&
				(kcor(Bitmap_im_1[2], img_2.Bitmap[2][0], img_2.img_Width) > 0.99)){
				
				for (unsigned int t = 1; t < img_2.img_Height; t++) {
					for (unsigned int k = 0; k < img_2.img_Width; k++) {
						Bitmap_im_1[0][k] = img_1.Bitmap[0][t][j + k];
					}

					if (!((kcor(Bitmap_im_1[0], img_2.Bitmap[0][t], img_2.img_Width) == 1) &&
						(kcor(Bitmap_im_1[1], img_2.Bitmap[1][t], img_2.img_Width) == 1) &&
						(kcor(Bitmap_im_1[2], img_2.Bitmap[2][t], img_2.img_Width) == 1)))
						break;
				}
				cout << "x: " << j << "  " << "y: " << i << endl;

			}
			
		}
	}
}