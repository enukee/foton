#include <iostream>
#include "windows.h"

#define ALING4(x) ((((x)-1)/4+1)*4) //������ - ���������� �������� �� ��������� ������� 4

using namespace std;

float avg(BYTE *Bitmap, unsigned int size) { // ������� ������ �������� �������� ������� �������� size
	float avg = 0;

	for (unsigned int i = 0; i < size; i++) {
		avg += (int)Bitmap[i];
	}
	avg /= size;

	return avg;
}

double sd(BYTE* Bitmap, unsigned int size) {// ������� ������ c������������������� ���������� ������� �������� size
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

	HFILE hFile = _lopen("C:\\Users\\vi\\Desktop\\�����\\prog_1\\image\\file_4.bmp", OF_READ);
	if (hFile != HFILE_ERROR) //���� ���� �������� ���������
	{
		BITMAPFILEHEADER  File;       //��������� ���������� �����
		BITMAPINFOHEADER  Head;   //��������� ���������� ������

		_lread(hFile, (char*)&File, sizeof(File));
		_lread(hFile, (char*)&Head, sizeof(Head));

		if (Head.biBitCount == 24) {
			unsigned int img_Height = Head.biHeight;    // ������ �����������
			unsigned int img_biWidth = Head.biWidth;    // ������ �����������
			unsigned int size = img_Height * img_biWidth;   // ������ �����������

			BYTE** Bitmap = new BYTE * [3];       //������� ����������� 
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

			cout << "������� �������� ������� ������ R: " << avg(Bitmap[0], size) << endl;
			cout << "������� �������� ������� ������ G: " << avg(Bitmap[1], size) << endl;
			cout << "������� �������� ������� ������ B: " << avg(Bitmap[2], size) << endl;

			cout << "�������������������� ���������� ������ R: " << sd(Bitmap[0], size) << endl;
			cout << "�������������������� ���������� ������ G: " << sd(Bitmap[1], size) << endl;
			cout << "�������������������� ���������� ������ B: " << sd(Bitmap[2], size) << endl;

			for (int i = 0; i < 3; i++) {
				delete[] Bitmap[i];  // ������� ������
			}
			delete[] Bitmap;
		}
	}
	else MessageBox(0, L"������ �������� ����� �����������", L"������", MB_OK);

	return 0;
}