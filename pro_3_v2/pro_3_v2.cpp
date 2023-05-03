#include <iostream>
#include "BmpFile.h"
#include "correlation.h"

using namespace std;


// метод поиска пересечения 2х изображений (поиск img_2 в img_1)
coordinates finding_intersection(BmpFile* img_1, BmpFile* img_2, coordinates coord_img) {
	// Создаём матрицу части изображения img_1
	ImageMatrix Bitmap(coord_img.height, coord_img.width);
	// Записыаем в неё нужный фрагмент
	Bitmap.cut_out(img_1, coord_img.y, coord_img.x);

	BmpFile m(&Bitmap);
	m.bmp_writer((char*)"D:\\GitHub_rep\\foton_prog\\pro_3_v2\\image\\п_4\\444444444444rf.bmp");

	coordinates coordinates;
	Pixel<double> kof_kor;

	unsigned int Height = Bitmap.get_height();
	unsigned int Width = Bitmap.get_width();

	unsigned int search_area_h = img_2->get_height() - Height + 1;
	unsigned int search_area_w = img_2->get_width() - Width + 1;

	Pixel<BYTE>* Bitmap_im_1 = new Pixel<BYTE>[Width];
	Pixel<BYTE>* Bitmap_im_2 = new Pixel<BYTE>[Width];

	// флаг не совпадения фрагментов
	boolean similar;

	for (unsigned int i = 0; i < search_area_h; i++) {
		for (unsigned int j = 0; j < search_area_w; j++) {

			similar = 1;
			for (unsigned int t = 0; t < Height; t++) {

				img_2->get_row_matrix(Bitmap_im_2, i, j, Width);
				Bitmap.get_row_matrix(Bitmap_im_1, t);
				kof_kor = kcor(Bitmap_im_1, Bitmap_im_2, Width);
				if (!((kof_kor.canal_R > 0.99) &&
					(kof_kor.canal_G > 0.99) &&
					(kof_kor.canal_B > 0.99)))
					similar = 0;
					break;
			}
			if (similar) {
				coordinates.set_coord(j, i);
			}

		}
	}
	delete[] Bitmap_im_1;
	delete[] Bitmap_im_2;

	return coordinates;
}

//метод объединения изображений
void combining(BmpFile* img_1, BmpFile* img_2, coordinates coord_img_1, coordinates coord_img_2) {
	unsigned int img_1_height = img_1->get_height();
	unsigned int img_1_width = img_1->get_width();

	unsigned int img_2_height = img_2->get_height();
	unsigned int img_2_width = img_2->get_width();

	unsigned int Height;
	unsigned int Width;

	coordinates coord_general_image_1;
	coordinates coord_general_image_2;

	if (coord_img_1.x <= coord_img_2.x) {
		coord_general_image_1.x = coord_img_2.x - coord_img_1.x;
		coord_general_image_2.x = 0;
		Width = img_1->get_width() + coord_general_image_1.x;
	}

	if (coord_img_1.x > coord_img_2.x) {
		coord_general_image_1.x = 0; 
		coord_general_image_2.x = coord_img_1.x - coord_img_2.x;
		Width = img_2->get_width() + coord_general_image_2.x;
	}

	if (coord_img_1.y <= coord_img_2.y) {
		coord_general_image_1.y = coord_img_2.y - coord_img_1.y;
		coord_general_image_2.y = 0;
		Height = img_1->get_height() + coord_general_image_1.y;
	}

	if (coord_img_1.y > coord_img_2.y) {
		coord_general_image_1.y = 0;
		coord_general_image_2.y = coord_img_1.y - coord_img_2.y;
		Height = img_2->get_height() + coord_general_image_2.y;
	}

	ImageMatrix Bitmap(Height, Width);

	Bitmap.recording(img_2, coord_general_image_2.y, coord_general_image_2.x);
	Bitmap.recording(img_1, coord_general_image_1.y, coord_general_image_1.x);

	BmpFile img(&Bitmap);
	img.bmp_writer((char*)"D:\\GitHub_rep\\foton_prog\\pro_3_v2\\image\\п_4\\1&2.bmp");
}

Pixel<BYTE> color_correction(Pixel<double> pixel, Pixel<double>sco, Pixel<double>mo) {
	Pixel<double> value;
	value = pixel * sco + mo;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

	Pixel<BYTE> pixel_1;
	pixel_1 = value.to_BYTE();

	return pixel_1;
}

// метод корректирования яркости
void brightness_correction(BmpFile* img_1, BmpFile* img_2, coordinates coord_img_1, coordinates coord_img_2) {

	// создание матрицы части пересечеия первого изображения
	ImageMatrix Bitmap_1(coord_img_1.height, coord_img_1.width);

	// заполнения первой матрицы 
	Bitmap_1.cut_out(img_1, coord_img_1.y, coord_img_1.x);

	// создание матрицы части пересечеия второго изображения
	ImageMatrix Bitmap_2(coord_img_2.height, coord_img_2.width);

	// заполнения второй матрицы 
	Bitmap_2.cut_out(img_2, coord_img_2.y, coord_img_2.x);

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

	//cout << "корректируемое изображение" << endl;
	//cout << "CKO_1: " << sco_1.canal_R << "  " << sco_1.canal_G << "  " << sco_1.canal_B << endl;
	//cout << "MO_1: " << mo_1.canal_R << "  " << mo_1.canal_G << "  " << mo_1.canal_B << endl << endl;
	//cout << "эталонное изображение" << endl;
	//cout << "CKO_2: " << sco_2.canal_R << "  " << sco_2.canal_G << "  " << sco_2.canal_B << endl;
	//cout << "MO_2: " << mo_2.canal_R << "  " << mo_2.canal_G << "  " << mo_2.canal_B << endl << endl;
	//cout << "CKO_1 /  CKO_2: " << sco.canal_R << "  " << sco.canal_G << "  " << sco.canal_B << endl;
	//cout << "MO_1 - MO_2: " << mo.canal_R << "  " << mo.canal_G << "  " << mo.canal_B << endl << endl;

	Pixel<BYTE> byte;
	unsigned int height = img_2->get_height();
	unsigned int width = img_2->get_width();
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			byte = img_2->get_pixel(i, j);
			byte = color_correction(byte.to_double(), sco, mo);
			img_2->set_pixel(byte, i, j);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");

	BmpFile img_1((char*)"D:\\GitHub_rep\\foton_prog\\pro_3_v2\\image\\п_4\\file_1.bmp");
	BmpFile img_2((char*)"D:\\GitHub_rep\\foton_prog\\pro_3_v2\\image\\п_4\\file_2.bmp");

	coordinates coord_img_1; // координаты заданного фрагмента внутри img_1

	//п_2
	/*coord_img_1.x = 218;
	coord_img_1.y = 189;
	coord_img_1.width = 50;
	coord_img_1.height = 50;*/

	//п_4
	coord_img_1.x = 1; //100;
	coord_img_1.y = 88; //3;
	coord_img_1.width = 50;
	coord_img_1.height = 25;

	coordinates coord_img_2; // координаты заданного фрагмента внутри img_2
	coord_img_2 = finding_intersection(&img_1, &img_2, coord_img_1);
	cout << coord_img_2.x << endl;
	cout << coord_img_2.y << endl;
	coord_img_2.height = coord_img_1.height;
	coord_img_2.width = coord_img_1.width;

	brightness_correction(&img_1, &img_2, coord_img_1, coord_img_2);

	combining(&img_1, &img_2, coord_img_1, coord_img_2);
}