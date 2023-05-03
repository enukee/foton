#pragma once

#include "pixel.h"

Pixel<double> avg(Pixel<BYTE>* Bitmap, unsigned int size) { // Функция поиска среднего значения массива размером size
	Pixel<double> avg;

	for (unsigned int i = 0; i < size; i++) {
		avg += Bitmap[i].to_double();
	}
	avg /= size;

	return avg;
}

Pixel<double>  sd(Pixel<BYTE>* Bitmap, unsigned int size) {// Функция поиска cреднеквадратическое отклонение массива размером size
	Pixel<double>  sd;
	Pixel<double>  _avg = avg(Bitmap, size);

	for (unsigned int i = 0; i < size; i++) {
		sd += pixel_pow((Bitmap[i].to_double() - _avg), 2);
	}
	sd /= size;
	sd = pixel_sqrt(sd);

	return sd;
}

Pixel<double> kcor(Pixel<BYTE>* Bitmap_1, Pixel<BYTE>* Bitmap_2, unsigned int size) {
	Pixel<double> avg_1 = avg(Bitmap_1, size);
	Pixel<double> avg_2 = avg(Bitmap_2, size);

	Pixel<double> kof_kor;

	Pixel<double> avg_1_2;
	for (unsigned int i = 0; i < size; i++) {

		avg_1_2 += Bitmap_1[i].to_double() * Bitmap_2[i].to_double();
	}
	avg_1_2 /= size;

	Pixel<double> sd_1 = sd(Bitmap_1, size);

	Pixel<double> sd_2 = sd(Bitmap_2, size);

	kof_kor = (avg_1_2 - avg_1 * avg_2) / (sd_1 * sd_2);

	return kof_kor;
}