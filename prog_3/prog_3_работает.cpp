#include <iostream>
#include "windows.h"

#include "bmpimg.h"

#define ALING4(x) ((((x)-1)/4+1)*4) //Макрос - дополнение величины до ближайшей кратной 4

using namespace std;

struct coordinates {
	int x = 0;
	int y = 0;
};

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

		avg_1_2 += Bitmap_1[i] * Bitmap_2[i];
	}
	avg_1_2 /= size;

	double sd_1 = sd(Bitmap_1, size);
	double sd_2 = sd(Bitmap_2, size);

	kof_kor = (avg_1_2 - avg_1 * avg_2) / (sd_1 * sd_2);

	return kof_kor;
}

// метод поика одного изображения внутри другого
coordinates finding(Imgbmp img_1, BYTE*** Bitmap, unsigned int Width, unsigned int Height) {
	coordinates coordinates;
	float kcor_0 = 0;
	float kcor_1 = 0;
	float kcor_2 = 0;

	BYTE** Bitmap_im_1 = new BYTE * [3];
	for (unsigned int i = 0; i < 3; i++) {
		Bitmap_im_1[i] = new BYTE[Width];
	}

	for (unsigned int i = 0; i < img_1.img_Height - Height + 1; i++) {
		for (unsigned int j = 0; j < img_1.img_Width - Width + 1; j++) {

			for (unsigned int k = 0; k < Width; k++) {
				Bitmap_im_1[0][k] = img_1.Bitmap[0][i][j + k];
				Bitmap_im_1[1][k] = img_1.Bitmap[1][i][j + k];
				Bitmap_im_1[2][k] = img_1.Bitmap[2][i][j + k];
			}

			float kcor_0 = kcor(Bitmap_im_1[0], Bitmap[0][0], Width);
			float kcor_1 = kcor(Bitmap_im_1[1], Bitmap[1][0], Width);
			float kcor_2 = kcor(Bitmap_im_1[2], Bitmap[2][0], Width);
			//cout << kcor_0 << "  " << kcor_1 << "  " << kcor_2 << endl;
			if ((kcor_0 > 0.99) &&
				(kcor_1 > 0.99) &&
				(kcor_2 > 0.99)) {

				for (unsigned int t = 1; t < Height; t++) {
					for (unsigned int k = 0; k < Width; k++) {
						Bitmap_im_1[0][k] = img_1.Bitmap[0][t][j + k];
					}

					if (!((kcor(Bitmap_im_1[0], Bitmap[0][t], Width) == 1) &&
						(kcor(Bitmap_im_1[1], Bitmap[1][t], Width) == 1) &&
						(kcor(Bitmap_im_1[2], Bitmap[2][t], Width) == 1)))
						break;
				}
				coordinates.x = j;
				coordinates.y = i;
			}

		}
	}

	return coordinates;
}

// метод поиска пересечения 2х изображений
coordinates finding_intersection(Imgbmp img_1, Imgbmp img_2, unsigned int x, unsigned int y, unsigned int size_x, unsigned int size_y) {
	// Создаём матрицу части тзображения img_1
	BYTE*** Bitmap_1 = new BYTE **[3];
	for (unsigned int i = 0; i < 3; i++) {
		Bitmap_1[i] = new BYTE * [size_y];
		for (unsigned int j = 0; j < size_y; j++) {
			Bitmap_1[i][j] = new BYTE[size_x];
		}
	}
	// Записыаем в неё нужный фрагмент
	for (unsigned int i = 0; i < size_y; i++) {
		for (unsigned int j = 0; j < size_x; j++) {
			Bitmap_1[0][i][j] = img_1.Bitmap[0][i + y][j + x];
			Bitmap_1[1][i][j] = img_1.Bitmap[1][i + y][j + x];
			Bitmap_1[2][i][j] = img_1.Bitmap[2][i + y][j + x];
		}
	}

	return finding(img_2, Bitmap_1, size_x, size_y);
}

// метод объединения изображений
void combining(Imgbmp img_1, Imgbmp img_2, coordinates coord_img_1, coordinates coord_img_2) {
	int Height = img_2.img_Height + coord_img_1.y - coord_img_2.y;
	int Width = img_2.img_Width + coord_img_1.x - coord_img_2.x;

	//cout << endl << Height << "   " << Width;

	BYTE*** Bitmap = new BYTE **[3];
	for (unsigned int i = 0; i < 3; i++) {
		Bitmap[i] = new BYTE * [Height];
		for (unsigned int j = 0; j < Height; j++) {
			Bitmap[i][j] = new BYTE[Width];
		}
	}

	for (unsigned int i = 0; i < img_1.img_Height; i++) {
		for (unsigned int j = 0; j < img_1.img_Width; j++) {
			Bitmap[0][i][j] = img_1.Bitmap[0][i][j];
			Bitmap[1][i][j] = img_1.Bitmap[1][i][j];
			Bitmap[2][i][j] = img_1.Bitmap[2][i][j];
		}
	}

	unsigned int x_img, y_img;
	for (unsigned int i = 0; i < img_2.img_Height; i++) {
		for (unsigned int j = 0; j < img_2.img_Width; j++) {
			y_img = i + coord_img_1.y - coord_img_2.y;
			x_img = j + coord_img_1.x - coord_img_2.x;
			if ((y_img >= img_1.img_Height) || (x_img >= img_1.img_Width)) {
				Bitmap[0][y_img][x_img] = img_2.Bitmap[0][i][j];
				Bitmap[1][y_img][x_img] = img_2.Bitmap[1][i][j];
				Bitmap[2][y_img][x_img] = img_2.Bitmap[2][i][j];
			}
		}
	}

	BITMAPFILEHEADER  File;
	BITMAPINFOHEADER  Head;

	//Заполнение структуры нулевыми значениями
	ZeroMemory(&Head, sizeof(Head));

	//Заполнение необходимых полей параметров растра
	Head.biSize = 40;
	Head.biHeight = Height;
	Head.biWidth = Width;
	Head.biPlanes = 1;
	Head.biBitCount = 24;

	//Заполнение структуры заголовка файла
	File.bfOffBits = sizeof(Head) + sizeof(File);
	File.bfSize = sizeof(File) + sizeof(Head) + Height * Width * 3;
	File.bfType = 'B' + (int)'M' * 256;

	//ZeroMemory(&Bitmap, sizeof(Bitmap));

	int b = 0;
	HFILE hFile = _lcreat("C:\\Users\\vi\\Desktop\\фотон\\prog_3\\image\\п_1\\file_005&6.bmp", 0);
	if (hFile != HFILE_ERROR)
	{
		_lwrite(hFile, (const char*)&File, sizeof(File));
		_lwrite(hFile, (const char*)&Head, sizeof(Head));
		for (unsigned int i = 0; i < Height; i++) {
			for (unsigned int j = 0; j < Width; j++) {
				_lwrite(hFile, (const char*)&Bitmap[2][Height - i - 1][j], 1);
				_lwrite(hFile, (const char*)&Bitmap[1][Height - i - 1][j], 1);
				_lwrite(hFile, (const char*)&Bitmap[0][Height - i - 1][j], 1);
			}

			for (unsigned int k = 0; k < ALING4(Width * 3) - Width * 3; k++) {
				_lwrite(hFile, (const char*)&b, 1);
			}
		}
		_lclose(hFile);
	}
	else MessageBox(0, L"Ошибка создания файла BMP", L"Ошибка", MB_OK);
}

int main()
{
	Imgbmp img_1((char*)"C:\\Users\\vi\\Desktop\\фотон\\prog_3\\image\\п_1\\file_1.bmp");
	Imgbmp img_2((char*)"C:\\Users\\vi\\Desktop\\фотон\\prog_3\\image\\п_1\\file_2.bmp");

	coordinates coord_img_1; //координаты заданного фрагмента внутри img_1
	coord_img_1.x = 280;
	coord_img_1.y = 160;

	coordinates coord_img_2; //координаты заданного фрагмента внутри img_2
	coord_img_2 = finding_intersection(img_1, img_2, coord_img_1.x, coord_img_1.y, 30, 30);
	cout << coord_img_1.x << "   " << coord_img_1.y << endl;
	cout << coord_img_2.x << "   " << coord_img_2.y << endl;

	combining(img_1, img_2, coord_img_1, coord_img_2);
}

