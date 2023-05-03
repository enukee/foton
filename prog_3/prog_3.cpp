#include <iostream>
#include "pixel.h"
#include "ImgBmp.h"

#define ALING4(x) ((((x)-1)/4+1)*4) //Макрос - дополнение величины до ближайшей кратной 4

using namespace std;

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

// метод поика одного изображения внутри другого
coordinates finding(ImgBmp img_1, ImageMatrix Bitmap) {
	coordinates coordinates;
	Pixel<double> kof_kor;

	unsigned int Height = Bitmap.get_height();
	unsigned int Width = Bitmap.get_width();

	unsigned int h = img_1.Bitmap.get_height() - Height + 1;
	unsigned int w = img_1.Bitmap.get_width() - Width + 1;

	Pixel<BYTE>*Bitmap_im_1 = new Pixel<BYTE>[Width];
	
	for (unsigned int i = 0; i < h; i++) {
		for (unsigned int j = 0; j < w; j++) {

			for (unsigned int k = 0; k < Width; k++) {
				Bitmap_im_1[k] = img_1.Bitmap.get_pixel(i, j + k);
			}

			kof_kor = kcor(Bitmap_im_1, Bitmap.get_row_matrix(0), Width);

			if ((kof_kor.canal_R > 0.99) &&
				(kof_kor.canal_G > 0.99) &&
				(kof_kor.canal_B > 0.99)) {

				for (unsigned int t = 1; t < Height; t++) {
					for (unsigned int k = 0; k < Width; k++) {
						Bitmap_im_1[k] = img_1.Bitmap.get_pixel(t, j + k);
					}

					kof_kor = kcor(Bitmap_im_1, Bitmap.get_row_matrix(t), Width);
					if (!((kof_kor.canal_R > 0.99) &&
						(kof_kor.canal_G > 0.99) &&
						(kof_kor.canal_B > 0.99)))
						break;
				}
			coordinates.x = j;
			coordinates.y = i;
			}

		}
	}

	delete[] Bitmap_im_1;

	return coordinates;
}

// метод поиска пересечения 2х изображений
coordinates finding_intersection(ImgBmp img_1, ImgBmp img_2, unsigned int x, unsigned int y, unsigned int size_x, unsigned int size_y) {
	// Создаём матрицу части изображения img_1
	ImageMatrix Bitmap(size_y, size_x);
	// Записыаем в неё нужный фрагмент
	Bitmap.cut_out(img_1.Bitmap, x, y);

	return finding(img_2, Bitmap);
}

//метод объединения изображений
void combining(ImgBmp img_1, ImgBmp img_2, coordinates coord_img_1, coordinates coord_img_2) {
	unsigned int img_1_height = img_1.Bitmap.get_height();
	unsigned int img_1_width = img_1.Bitmap.get_width();

	unsigned int img_2_height = img_2.Bitmap.get_height();
	unsigned int img_2_width = img_2.Bitmap.get_width();

	unsigned int Height = img_2.Bitmap.get_height() + coord_img_1.y - coord_img_2.y;
	unsigned int Width = img_2.Bitmap.get_width() + coord_img_1.x - coord_img_2.x;

	//cout << endl << Height << "   " << Width;

	ImageMatrix Bitmap(Height, Width);

	Pixel<BYTE> byte;
	for (unsigned int i = 0; i < img_1_height; i++) {
		for (unsigned int j = 0; j < img_1_width; j++) {
			byte = img_1.Bitmap.get_pixel(i, j);
			Bitmap.set_pixel(byte, i, j);
		}
	}

	unsigned int x_img, y_img;
	for (unsigned int i = 0; i < img_2_height; i++) {
		for (unsigned int j = 0; j < img_2_width; j++) {
			y_img = i + coord_img_1.y - coord_img_2.y;
			x_img = j + coord_img_1.x - coord_img_2.x;
			if ((y_img >= img_1_height) || (x_img >= img_1_width)) {
				byte = img_2.Bitmap.get_pixel(i, j);
				Bitmap.set_pixel(byte, y_img, x_img);
			}
		}
	}

	ImgBmp img((char*)"D:\\GitHub_rep\\foton_prog\\prog_3\\image\\п_2\\1&2.bmp", Bitmap);
}

Pixel<BYTE> color_correction(Pixel<double> pixel, Pixel<double>sco, Pixel<double>mo) {
	Pixel<double> value;
	value.canal_R = (pixel.canal_R * sco.canal_R) + (mo.canal_R);
	value.canal_G = (pixel.canal_G * sco.canal_G) + (mo.canal_G);
	value.canal_B = (pixel.canal_B * sco.canal_B) + (mo.canal_B);

	//cout << "pixel: " << value.canal_R << "  " << value.canal_G << "  " << value.canal_B << endl << endl;

	Pixel<BYTE> pixel_1;
	pixel_1 = value.to_BYTE();

	return pixel_1;
}

// метод корректирования яркости
ImgBmp brightness_correction(ImgBmp img_1, ImgBmp img_2, coordinates coord_img_1, coordinates coord_img_2) {

	// создание матрицы части пересечеия первого изображения
	ImageMatrix Bitmap_1(coord_img_1.height, coord_img_1.width);

	// заполнения первой матрицы 
	Bitmap_1.cut_out(img_1.Bitmap, coord_img_1.x, coord_img_1.y);

	// создание матрицы части пересечеия второго изображения
	ImageMatrix Bitmap_2(coord_img_2.height, coord_img_2.width);

	// заполнения второй матрицы 
	Bitmap_2.cut_out(img_2.Bitmap, coord_img_2.x, coord_img_2.y);

	Pixel<double> sco_1 = Bitmap_1.sd();
	Pixel<double> sco_2 = Bitmap_2.sd();
	Pixel<double> mo_1 = Bitmap_1.avg();
	Pixel<double> mo_2 = Bitmap_2.avg();

	Pixel<double> sco;
	Pixel<double> mo;

	if (((sco_1.canal_R > -0.5) and (sco_1.canal_R < 0.5)) or ((sco_2.canal_R > -0.5) and (sco_2.canal_R < 0.5))) {
		sco.canal_R = 1;
	}
	else {
		sco.canal_R = sco_1.canal_R / sco_2.canal_R;
	}

	if (((sco_1.canal_G > -0.5) and (sco_1.canal_G < 0.5)) or ((sco_2.canal_G > -0.5) and (sco_2.canal_G < 0.5))) {
		sco.canal_G = 1;
	}
	else {
		sco.canal_G = sco_1.canal_G / sco_2.canal_G;
	}

	if (((sco_1.canal_B > -0.5) and (sco_1.canal_B < 0.5)) or ((sco_2.canal_B > -0.5) and (sco_2.canal_B < 0.5))) {
		sco.canal_B = 1;
	}
	else {
		sco.canal_B = sco_1.canal_B / sco_2.canal_B;
	}

	mo = mo_1 - (mo_2 * sco);

	cout << "корректируемое изображение" << endl;
	cout << "CKO_1: " << sco_1.canal_R << "  " << sco_1.canal_G << "  " << sco_1.canal_B << endl;
	cout << "MO_1: " << mo_1.canal_R << "  " << mo_1.canal_G << "  " << mo_1.canal_B << endl << endl;
	cout << "эталонное изображение" << endl;
	cout << "CKO_2: " << sco_2.canal_R << "  " << sco_2.canal_G << "  " << sco_2.canal_B << endl;
	cout << "MO_2: " << mo_2.canal_R << "  " << mo_2.canal_G << "  " << mo_2.canal_B << endl << endl;
	cout << "CKO_1 /  CKO_2: " << sco.canal_R << "  " << sco.canal_G << "  " << sco.canal_B << endl;
	cout << "MO_1 - MO_2: " << mo.canal_R << "  " << mo.canal_G << "  " << mo.canal_B << endl << endl;

	Pixel<BYTE> byte;
	unsigned int height = img_2.Bitmap.get_height();
	unsigned int width = img_2.Bitmap.get_width();
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			byte = img_2.Bitmap.get_pixel(i, j);
			byte = color_correction(byte.to_double(), sco, mo);
			img_2.Bitmap.set_pixel(byte, i, j);
		}
	}

	return img_2;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	ImgBmp img_1((char*)"D:\\GitHub_rep\\foton_prog\\prog_3\\image\\п_2\\file_1.bmp");
	ImgBmp img_2((char*)"D:\\GitHub_rep\\foton_prog\\prog_3\\image\\п_2\\file_2.bmp");

	coordinates coord_img_1; // координаты заданного фрагмента внутри img_1
	//п_1
	/*coord_img_1.x = 287;
	coord_img_1.y = 168;
	coord_img_1.width = 30;
	coord_img_1.height = 30;*/

	//п_2
	coord_img_1.x = 218;
	coord_img_1.y = 189;
	coord_img_1.width = 50;
	coord_img_1.height = 50;

	//п_3
	/*coord_img_1.x = 481;
	coord_img_1.y = 287;
	coord_img_1.width = 30;
	coord_img_1.height = 30;*/

	coordinates coord_img_2; // координаты заданного фрагмента внутри img_2
	coord_img_2 = finding_intersection(img_1, img_2, coord_img_1.x, coord_img_1.y, coord_img_1.width, coord_img_1.height);
	cout << coord_img_2.x << endl;
	cout << coord_img_2.y << endl;
	coord_img_2.height = coord_img_1.height;
	coord_img_2.width = coord_img_1.width;

	// коррекция яркости
	img_2 = brightness_correction(img_1, img_2, coord_img_1, coord_img_2);

	// комплексирование изображений
	combining(img_1, img_2, coord_img_1, coord_img_2);
}

