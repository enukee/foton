#include <iostream>
#include "windows.h"

#define ALING4(x) ((((x)-1)/4+1)*4) //Макрос - дополнение величины до ближайшей кратной 4

using namespace std;

float avg(BYTE *Bitmap, unsigned int size) { // Функция поиска среднего значения массива размером size
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

int main() {
	setlocale(LC_ALL, "Russian");

	HFILE hFile = _lopen("C:\\Users\\vi\\Desktop\\фотон\\prog_1\\image\\file_4.bmp", OF_READ);
	if (hFile != HFILE_ERROR) //Если файл открылся нормально
	{
		BITMAPFILEHEADER  File;       //Структура заголовока файла
		BITMAPINFOHEADER  Head;   //Структура параметров растра

		_lread(hFile, (char*)&File, sizeof(File));
		_lread(hFile, (char*)&Head, sizeof(Head));

		if (Head.biBitCount == 24) {
			unsigned int img_Height = Head.biHeight;    // Высота изображения
			unsigned int img_biWidth = Head.biWidth;    // Ширина изображения
			unsigned int size = img_Height * img_biWidth;   // Размер изображения

			BYTE** Bitmap = new BYTE * [3];       //Матрица изображения 
			for (unsigned int i = 0; i < 3; i++) {
				Bitmap[i] = new BYTE[img_Height * img_biWidth];
			}

			BYTE bytes;
			for (unsigned int i = 0; i < img_Height; i++) {
				for (unsigned int j = 0; j < img_biWidth; j++) {
					_lread(hFile, (char*)&bytes, 1);
					Bitmap[2][i * img_biWidth + j] = bytes;
					_lread(hFile, (char*)&bytes, 1);
					Bitmap[1][i * img_biWidth + j] = bytes;
					_lread(hFile, (char*)&bytes, 1);
					Bitmap[0][i * img_biWidth + j] = bytes;
				}

				for (unsigned int k = 0; k < ALING4(img_biWidth * 3) - img_biWidth * 3; k++) {
					_lread(hFile, (char*)&bytes, 1);
				}
			}
			_lclose(hFile);

			cout << "Среднее значение яркости канала R: " << avg(Bitmap[0], size) << endl;
			cout << "Среднее значение яркости канала G: " << avg(Bitmap[1], size) << endl;
			cout << "Среднее значение яркости канала B: " << avg(Bitmap[2], size) << endl;

			cout << "Среднеквадратическое отклонение канала R: " << sd(Bitmap[0], size) << endl;
			cout << "Среднеквадратическое отклонение канала G: " << sd(Bitmap[1], size) << endl;
			cout << "Среднеквадратическое отклонение канала B: " << sd(Bitmap[2], size) << endl;

			for (int i = 0; i < 3; i++) {
				delete[] Bitmap[i];  // удаляем массив
			}
			delete[] Bitmap;
		}
	}
	else MessageBox(0, L"Ошибка открытия файла изображения", L"Ошибка", MB_OK);

	return 0;
}