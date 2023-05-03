#include "MyForm.h"
#include "processing.h"

using namespace prog3v3;
using namespace System::Runtime::InteropServices;

boolean is_bmp_file(char* way) {
	int last_symbol = strlen(way) - 1;
	boolean is_bmp = (way[last_symbol] == 'p');
	is_bmp &= (way[last_symbol - 1] == 'm');
	is_bmp &= (way[last_symbol - 2] == 'b');
	is_bmp &= (way[last_symbol - 3] == '.');
	return is_bmp;
}

// Открытие bmp файла 1
System::Void MyForm::button_open_file_1_Click(System::Object^ sender, System::EventArgs^ e) {
	this->openFileDialog1->ShowDialog();
	this->textBox1->Text = this->openFileDialog1->FileName;
	way_1 = (char*)(void*)Marshal::StringToHGlobalAnsi(this->openFileDialog1->FileName);
	if (is_bmp_file(way_1)) {
		this->pictureBox1->ImageLocation = this->openFileDialog1->FileName;
		image_1 = Image::FromFile(this->openFileDialog1->FileName);
		bitmap_1 = gcnew Bitmap(image_1);
	}
	else {
		this->messageBox_error->Show("Данный файл не является bmp", "Ошибка");
	}

}

// Открытие bmp файла 2
System::Void MyForm::button_open_file_2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->openFileDialog2->ShowDialog(); 
	this->textBox2->Text = this->openFileDialog2->FileName;
	way_2 = (char*)(void*)Marshal::StringToHGlobalAnsi(this->openFileDialog2->FileName); 
	if (is_bmp_file(way_2)) {
		this->pictureBox2->ImageLocation = this->openFileDialog2->FileName;
		this->pictureBox2->Image = gcnew Bitmap(this->pictureBox2->ImageLocation);
		w_2 = this->pictureBox2->Image->Width;
		h_2 = this->pictureBox2->Image->Height;
		this->textBox_w_2->Text = System::Convert::ToString(w_2);
		this->textBox_h_2->Text = System::Convert::ToString(h_2);
	}
	else {
		this->messageBox_error->Show("Данный файл не является bmp", "Ошибка");
	}
}

// Ввод координаты x для изображения 1
System::Void MyForm::textBox_x_1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	string str;
	try {
		x_1 = Int32::Parse(this->textBox_x_1->Text);
	}
	catch (FormatException^) {
		this->messageBox_error->Show("Недопустимый символ", "Ошибка");
	}
}

// Ввод координаты y для изображения 1
System::Void MyForm::textBox_y_1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	try {
		y_1 = Int32::Parse(this->textBox_y_1->Text);
	}
	catch (FormatException^) {
		this->messageBox_error->Show("Недопустимый символ", "Ошибка");
	}

}

// Ввод ширины для изображения 1
System::Void MyForm::textBox_w_1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	try {
		w_1 = Int32::Parse(this->textBox_w_1->Text);
	}
	catch (FormatException^) {
		this->messageBox_error->Show("Недопустимый символ", "Ошибка");
	}
}

// Ввод высоты для изображения 1
System::Void MyForm::textBox_h_1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	try {
		h_1 = Int32::Parse(this->textBox_h_1->Text);
	}
	catch (FormatException^) {
		this->messageBox_error->Show("Недопустимый символ","Ошибка");
	}
}

// Ввод координаты x для изображения 2
System::Void MyForm::textBox_x_2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	try {
		x_2 = Int32::Parse(this->textBox_w_2->Text);
	}
	catch (FormatException^) {
		this->messageBox_error->Show("Недопустимый символ", "Ошибка");
	}
}

// Ввод координаты y для изображения 2
System::Void MyForm::textBox_y_2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	try {
		y_2 = Int32::Parse(this->textBox_w_2->Text);
	}
	catch (FormatException^) {
		this->messageBox_error->Show("Недопустимый символ", "Ошибка");
	}
}

// Ввод ширины для изображения 2
System::Void MyForm::textBox_w_2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	try {
		w_2 = Int32::Parse(this->textBox_w_2->Text);
	}
	catch (FormatException^) {
		this->messageBox_error->Show("Недопустимый символ", "Ошибка");
	}
}

// Ввод высоты для изображения 2
System::Void MyForm::textBox_h_2_TextChanged(System::Object^ sender, System::EventArgs^ e){
	try {
		h_2 = Int32::Parse(this->textBox_h_2->Text);
	}
	catch (FormatException^) {
		this->messageBox_error->Show("Недопустимый символ", "Ошибка");
	}
}

System::Void MyForm::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	Point* mouseLocation = new Point(e->X, e->Y);

	x_1 = mouseLocation->X;
	y_1 = mouseLocation->Y;

	x_1_other = x_1;
	y_1_other = y_1;

	bitmap_1 = gcnew Bitmap(image_1);
}



System::Void MyForm::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		Point* mouseLocation = new Point(e->X, e->Y);

		w_1 = abs(mouseLocation->X - x_1);
		h_1 = abs(mouseLocation->Y - y_1);

		if (x_1 > mouseLocation->X) {
			x_1_other = mouseLocation->X;
		}

		if (y_1 > mouseLocation->Y) {
			y_1_other = mouseLocation->Y;
		}

		Graphics^ g = Graphics::FromImage(bitmap_1);
		//g = this->pictureBox1->CreateGraphics();
		Pen^ pp = gcnew Pen(Brushes::Red, 2);
		g->DrawRectangle(pp, x_1_other, y_1_other, w_1, h_1);
		g->DrawImage(bitmap_1, 0, 0);
		this->pictureBox1->Image = bitmap_1;
		this->pictureBox1->Refresh();
		bitmap_1 = gcnew Bitmap(image_1);

	}
}

System::Void MyForm::pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	Point* mouseLocation = new Point(e->X, e->Y);

	w_1 = abs(mouseLocation->X - x_1);
	h_1 = abs(mouseLocation->Y - y_1);

	if (x_1 > mouseLocation->X) {
		x_1_other = mouseLocation->X;
	}

	if (y_1 > mouseLocation->Y) {
		y_1_other = mouseLocation->Y;
	}

	this->textBox_x_1->Text = System::Convert::ToString(x_1);
	this->textBox_y_1->Text = System::Convert::ToString(y_1);
	this->textBox_w_1->Text = System::Convert::ToString(w_1);
	this->textBox_h_1->Text = System::Convert::ToString(h_1);

	Graphics^ g = Graphics::FromImage(bitmap_1);
	//g = this->pictureBox1->CreateGraphics();
	Pen^ pp = gcnew Pen(Brushes::Red, 2);
	g->DrawRectangle(pp, x_1_other, y_1_other, w_1, h_1);
	g->DrawImage(bitmap_1, 0, 0);
	this->pictureBox1->Image = bitmap_1;
	this->pictureBox1->Refresh();
	

}

System::Void MyForm::button_processing_Click(System::Object^ sender, System::EventArgs^ e) {

	this->progressBar1->Value = 0;

	BmpFile img_1(way_1, this);
	this->progressBar1->Value = 20;
	BmpFile img_2(way_2, this);
	this->progressBar1->Value = 40;

	coordinates coord_img_1;

	coord_img_1.x = Int32::Parse(this->textBox_x_1->Text);
	coord_img_1.y = Int32::Parse(this->textBox_y_1->Text);
	coord_img_1.width = Int32::Parse(this->textBox_w_1->Text);
	coord_img_1.height = Int32::Parse(this->textBox_h_1->Text);

	coordinates coord_img_2; // координаты заданного фрагмента внутри img_2
	coord_img_2.x = Int32::Parse(this->textBox_x_2->Text);
	coord_img_2.y = Int32::Parse(this->textBox_y_2->Text);
	coord_img_2.width = Int32::Parse(this->textBox_w_2->Text);
	coord_img_2.height = Int32::Parse(this->textBox_h_2->Text);

	boolean is_found = finding_intersection(&img_1, &img_2, &coord_img_1, &coord_img_2, this);
	this->progressBar1->Value = 60;
	coord_img_2.height = coord_img_1.height;
	coord_img_2.width = coord_img_1.width;

	if (is_found){
		this->textBox3->Text = brightness_correction(&img_1, &img_2, coord_img_1, coord_img_2, this);
		this->progressBar1->Value = 80;

		combining(&img_1, &img_2, coord_img_1, coord_img_2, this);
		this->progressBar1->Value = 100;
	}
	else {
		this->messageBox_error->Show("Пересечение не найдено", "Ошибка");
	}
}
