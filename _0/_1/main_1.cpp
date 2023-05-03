//#include "windows.h"
//
//const int img_Height = 500;
//const int img_biWidth = 500;
//
//int create_8bit_img() {
//
//    BITMAPFILEHEADER  File;       //��������� ���������� �����
//    BITMAPINFOHEADER  Head;   //��������� ���������� ������
//    RGBQUAD bmiData[256];          //������� ������
//    BYTE Bitmap[img_Height][img_biWidth];       //������� �����������
//
//    //���������� ��������� �������� ����������
//    ZeroMemory(&Head, sizeof(Head));
//    //���������� ����������� ����� ���������� ������
//    Head.biSize = 40;
//    Head.biHeight = img_Height;
//    Head.biWidth = img_biWidth;
//    Head.biPlanes = 1;
//    Head.biBitCount = 8;
//
//    //���������� ��������� ��������� �����
//    File.bfOffBits = sizeof(Head) + sizeof(File);
//    File.bfSize = sizeof(File) + sizeof(Head) + sizeof(bmiData) + img_Height * img_biWidth; //������ �����
//    File.bfType = 'B' + (int)'M' * 256;
//
//    //���������� ��������� �������� ����������
//    ZeroMemory(&bmiData, sizeof(bmiData));
//    bmiData[1].rgbRed = 30;
//    bmiData[1].rgbGreen = 30;
//    bmiData[1].rgbBlue = 30;
//
//    bmiData[2].rgbRed = 40;
//    bmiData[2].rgbGreen = 40;
//    bmiData[2].rgbBlue = 40;
//
//    for (int i = 0; i < img_Height; i++) {
//        for (int j = 0; j < img_biWidth; j++) {
//            if (i < j) Bitmap[i][j] = 1;
//            else Bitmap[i][j] = 2;
//        }
//    }
//
//    HFILE hFile = _lcreat("C:\\Users\\vi\\Desktop\\�����\\file_8bit_1.bmp", 0);
//    if (hFile != HFILE_ERROR)
//    {
//        _lwrite(hFile, (const char*)&File, sizeof(File));     //���������� ��������� �����
//        _lwrite(hFile, (const char*)&Head, sizeof(Head)); //���������� ���������� ������
//        _lwrite(hFile, (const char*)bmiData, sizeof(bmiData)); //���������� ���������� ������
//        _lwrite(hFile, (const char*)Bitmap, img_Height * img_biWidth);   //���������� ������� �����������
//        _lclose(hFile);             //�������� �����
//    }
//    else MessageBox(0, L"������ �������� ����� BMP", L"������", MB_OK);
//
//    return 0;
//}
//
//int create_24bit_img() {
//    BITMAPFILEHEADER  File;
//    BITMAPINFOHEADER  Head;
//
//    BYTE Bitmap[img_Height][img_biWidth][3];
//
//    //���������� ��������� �������� ����������
//    ZeroMemory(&Head, sizeof(Head));
//
//    //���������� ����������� ����� ���������� ������
//    Head.biSize = 40;
//    Head.biHeight = img_Height;
//    Head.biWidth = img_biWidth;
//    Head.biPlanes = 1;
//    Head.biBitCount = 24;
//
//    //���������� ��������� ��������� �����
//    File.bfOffBits = sizeof(Head) + sizeof(File);
//    File.bfSize = sizeof(File) + sizeof(Head) + img_Height * img_biWidth * 3;
//    File.bfType = 'B' + (int)'M' * 256;
//
//
//    ZeroMemory(&Bitmap, sizeof(Bitmap));
//    for (int i = 0; i < img_Height; i++) {
//        for (int j = 0; j < img_biWidth; j++) {
//            Bitmap[i][j][2] = 255;
//            Bitmap[i][j][0] = 1;
//        }
//    }
//
//    HFILE hFile = _lcreat("C:\\Users\\vi\\Desktop\\�����\\file_24bit_1.bmp", 0);
//    if (hFile != HFILE_ERROR)
//    {
//        _lwrite(hFile, (const char*)&File, sizeof(File));
//        _lwrite(hFile, (const char*)&Head, sizeof(Head));
//        _lwrite(hFile, (const char*)&Bitmap, img_Height * img_biWidth * 3);
//        _lclose(hFile);
//    }
//    else MessageBox(0, L"������ �������� ����� BMP", L"������", MB_OK);
//
//    return 0;
//}
//
//int main() {
//
//    // �������� 8������� bmp �����
//    create_8bit_img();
//
//    // �������� 24������� bmp �����
//    create_24bit_img();
//
//    return 0;
//}