#pragma once

#include "pixel.h"

class ImageMatrix {
private:
	unsigned int img_Height = 0;                    // Высота изображения
	unsigned int img_Width = 0;                     // Ширина изображения

	Pixel<BYTE>** matrix;       //Матрица изображения 

public:

	ImageMatrix() {}

	ImageMatrix(unsigned int height, unsigned int width) {
		img_Height = height;
		img_Width = width;

		matrix = new Pixel<BYTE> *[img_Height];
		for (unsigned int i = 0; i < img_Height; i++) {
			matrix[i] = new Pixel<BYTE>[img_Width];
		}
	}

	//~ImageMatrix() {
	//	for (unsigned int i = 0; i < img_Height; i++)
	//	{
	//		delete[] matrix[i];
	//	}
	//	delete[] matrix;
	//	//matrix = NULL;
	//}

	// записывает матрицу Bitmap в матрицу matrix (начиная с позиции matrix[x][y])
	void recording(ImageMatrix Bitmap, unsigned int x, unsigned int y) {
		for (unsigned int i = 0; i < Bitmap.get_height(); i++) {
			for (unsigned int j = 0; j < Bitmap.get_width(); j++) {
				matrix[i + y][j + x] = Bitmap.matrix[i][j];
			}
		}
	}

	// заполнние матрицы mdtrix значениями матрицы Bitmap (начиная с позиции Bitmap[x][y])
	void cut_out(ImageMatrix Bitmap, unsigned int x, unsigned int y) {
		for (unsigned int i = 0; i < img_Height; i++) {
			for (unsigned int j = 0; j < img_Width; j++) {
				matrix[i][j] = Bitmap.matrix[i + y][j + x];
			}
		}
	}

	Pixel<double> avg() { // Функция поиска среднего значения массива 
		Pixel<double> avg;

		for (unsigned int i = 0; i < img_Height; i++) {
			for (unsigned int j = 0; j < img_Width; j++) {
				avg += matrix[i][j].to_double();
			}
		}
		avg /= img_Height;
		avg /= img_Width;

		return avg;
	}

	Pixel<double> sd() {// Функция поиска cреднеквадратическое отклонение массива 
		Pixel<double> sd;
		Pixel<double> _avg = avg();

		for (unsigned int i = 0; i < img_Height; i++) {
			for (unsigned int j = 0; j < img_Width; j++) {
				sd += ((matrix[i][j].to_double() - _avg) * (matrix[i][j].to_double() - _avg));
			}
		}
		sd /= img_Height;
		sd /= img_Width;
		sd = pixel_sqrt(sd);

		return sd;
	}

	void set_pixel(Pixel<BYTE> value, unsigned int i, unsigned int j) {
		matrix[i][j] = value;
	}

	void set_pixel(BYTE canal_R, BYTE canal_G, BYTE canal_B, unsigned int i, unsigned int j) {
		matrix[i][j].canal_R = canal_R;
		matrix[i][j].canal_G = canal_G;
		matrix[i][j].canal_B = canal_B;
	}

	Pixel<BYTE> get_pixel(unsigned int i, unsigned int j) {
		return matrix[i][j];
	}

	Pixel<BYTE>* get_row_matrix(unsigned int i) {
		return matrix[i];
	}

	/*Pixel<BYTE>* set_row_matrix(Pixel<BYTE>* matr, unsigned int i) {
		for (unsigned int j = 0; j < img_Width; j++) {
			matrix[i][j] = matr[j];
		}
		return matrix[i];
	}*/

	// геттер высоты изображения
	unsigned int get_height() {
		return img_Height;
	}

	// геттер ширины изображения
	unsigned int get_width() {
		return img_Width;
	}
};