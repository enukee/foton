#include "windows.h"
#include <iostream>

const int img_Height = 384;
const int img_biWidth = 512;

int create_8bit_img() {

    BITMAPFILEHEADER  File;       //Структура заголовока файла
    BITMAPINFOHEADER  Head;   //Структура параметров растра
    RGBQUAD bmiData[256];          //Таблица цветов
    BYTE Bitmap[img_Height][img_biWidth];       //Матрица изображения

    HFILE hFile = _lopen("C:\\Users\\vi\\Desktop\\фотон\\img_1.jpg", OF_READ);

    if (hFile != HFILE_ERROR) //Если файл открылся нормально
    {
        _lread(hFile, Bitmap, img_Height * img_biWidth); //Читаем матрицу изображения
        _lclose(hFile);     //закрываем файл

        //Заполнение структуры нулевыми значениями
        ZeroMemory(&Head, sizeof(Head));
        //Заполнение необходимых полей параметров растра
        Head.biSize = 40;
        Head.biHeight = img_Height;
        Head.biWidth = img_biWidth;
        Head.biPlanes = 1;
        Head.biBitCount = 8;

        //Заполнение структуры заголовка файла
        File.bfOffBits = sizeof(Head) + sizeof(File);
        File.bfSize = sizeof(File) + sizeof(Head) + sizeof(bmiData) + img_Height * img_biWidth; //Размер файла
        File.bfType = 'B' + (int)'M' * 256;

        //Заполнение структуры нулевыми значениями
        ZeroMemory(&bmiData, sizeof(bmiData));
        bmiData[1].rgbRed = 0;
        bmiData[1].rgbGreen = 0;
        bmiData[1].rgbBlue = 0;

        bmiData[2].rgbRed = 0;
        bmiData[2].rgbGreen = 0;
        bmiData[2].rgbBlue = 0;

        hFile = _lcreat("C:\\Users\\vi\\Desktop\\фотон\\file_8bit_1.bmp", 0);
        if (hFile != HFILE_ERROR)
        {
            _lwrite(hFile, (const char*)&File, sizeof(File));     //Сохранение заголовка файла
            _lwrite(hFile, (const char*)&Head, sizeof(Head)); //Сохранение параметров растра
            _lwrite(hFile, (const char*)bmiData, sizeof(bmiData)); //Сохранение параметров растра
            _lwrite(hFile, (const char*)Bitmap, img_Height * img_biWidth);   //Сохранение матрицы изображения
            _lclose(hFile);             //Закрытие файла
        }
        else MessageBox(0, L"Ошибка создания файла BMP", L"Ошибка", MB_OK);
    }
    else MessageBox(0, L"Ошибка открытия файла изображения", L"Ошибка", MB_OK);
    return 0;
}

int create_24bit_img() {
    BITMAPFILEHEADER  File;
    BITMAPINFOHEADER  Head;

    BYTE Bitmap[img_Height][img_biWidth][3];
    HFILE hFile = _lopen("C:\\Users\\vi\\Desktop\\фотон\\img_1.jpg", OF_READ);

    if (hFile != HFILE_ERROR) //Если файл открылся нормально
    {
        _lread(hFile, Bitmap, img_Height * img_biWidth*3); //Читаем матрицу изображения
        _lclose(hFile);     //закрываем файл
        //Заполнение структуры нулевыми значениями
        ZeroMemory(&Head, sizeof(Head));

        //Заполнение необходимых полей параметров растра
        Head.biSize = 40;
        Head.biHeight = img_Height;
        Head.biWidth = img_biWidth;
        Head.biPlanes = 1;
        Head.biBitCount = 24;

        //Заполнение структуры заголовка файла
        File.bfOffBits = sizeof(Head) + sizeof(File);
        File.bfSize = sizeof(File) + sizeof(Head) + img_Height * img_biWidth * 3;
        File.bfType = 'B' + (int)'M' * 256;


        /*ZeroMemory(&Bitmap, sizeof(Bitmap));
        for (int i = 0; i < img_Height; i++) {
            for (int j = 0; j < img_biWidth; j++) {
                Bitmap[i][j][2] = 255;
                Bitmap[i][j][0] = 1;
            }
        }*/

        HFILE hFile = _lcreat("C:\\Users\\vi\\Desktop\\фотон\\file_24bit_1.bmp", 0);
        if (hFile != HFILE_ERROR)
        {
            _lwrite(hFile, (const char*)&File, sizeof(File));
            _lwrite(hFile, (const char*)&Head, sizeof(Head));
            _lwrite(hFile, (const char*)&Bitmap, img_Height * img_biWidth * 3);
            _lclose(hFile);
        }
        else MessageBox(0, L"Ошибка создания файла BMP", L"Ошибка", MB_OK);
    }
    else MessageBox(0, L"Ошибка открытия файла изображения", L"Ошибка", MB_OK);

    return 0;
}

int main() {

    // создание 8битного bmp файла
    create_8bit_img();

    // создание 24битного bmp файла
    create_24bit_img();

    return 0;
}