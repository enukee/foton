#include "MyForm.h"
#include "processing.h"

using namespace prog3v3;
using namespace System::Runtime::InteropServices;

void checking_the_value(System::Object^ sender, int max) {
	int value = Int32::Parse((safe_cast<TextBox^>(sender))->Text);
	if (value < 0) {
		(safe_cast<TextBox^>(sender))->Text = "0";
	}
	if (value >= max) {
		(safe_cast<TextBox^>(sender))->Text = System::Convert::ToString(max);
	}
}

// Открытие bmp файла 1
System::Void MyForm::button_open_file_1_Click(System::Object^ sender, System::EventArgs^ e) {
	this->openFileDialog1->ShowDialog();
	this->textBox1->Text = this->openFileDialog1->FileName;
	way_1 = (char*)(void*)Marshal::StringToHGlobalAnsi(this->openFileDialog1->FileName);
	if (is_bmp_file(way_1)) {
		this->pictureBox1->Image = gcnew Bitmap(this->openFileDialog1->FileName);
		image_1 = Image::FromFile(this->openFileDialog1->FileName);
		bitmap_1 = gcnew Bitmap(image_1);
	}
	else {
		this->messageBox_error->Show("Данный файл не является bmp", "Ошибка");
	}

}

// Открытие bmp файла 2
System::Void MyForm::button_open_file_2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->openFileDialog1->ShowDialog(); 
	this->textBox2->Text = this->openFileDialog1->FileName;
	way_2 = (char*)(void*)Marshal::StringToHGlobalAnsi(this->openFileDialog1->FileName); 
	if (is_bmp_file(way_2)) {
		this->pictureBox2->Image = gcnew Bitmap(this->openFileDialog1->FileName);
		w_2 = this->pictureBox2->Image->Width;
		h_2 = this->pictureBox2->Image->Height;
		this->textBox_w_2->Text = System::Convert::ToString(w_2);
		this->textBox_h_2->Text = System::Convert::ToString(h_2);
	}
	else {
		this->messageBox_error->Show("Данный файл не является bmp", "Ошибка");
	}
}

System::Void MyForm::textBox_x_1_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	try {
		checking_the_value(sender, this->pictureBox1->Image->Width);
	}
	catch (...) {
		this->messageBox_error->Show("Откройте файл", "Ошибка");
	}
}

System::Void MyForm::textBox_y_1_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	checking_the_value(sender, this->pictureBox1->Image->Height);
}

System::Void MyForm::textBox_w_1_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	checking_the_value(sender, this->pictureBox1->Image->Width - Int32::Parse(this->textBox_x_1->Text));
}

System::Void MyForm::textBox_h_1_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	checking_the_value(sender, this->pictureBox1->Image->Height - Int32::Parse(this->textBox_y_1->Text));
}

System::Void MyForm::textBox_x_2_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	checking_the_value(sender, this->pictureBox2->Image->Width);
}

System::Void MyForm::textBox_y_2_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	checking_the_value(sender, this->pictureBox2->Image->Height);
}

System::Void MyForm::textBox_w_2_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	checking_the_value(sender, this->pictureBox2->Image->Width - Int32::Parse(this->textBox_x_2->Text));
}

System::Void MyForm::textBox_h_2_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	checking_the_value(sender, this->pictureBox2->Image->Height - Int32::Parse(this->textBox_y_2->Text));
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
	Pen^ pp = gcnew Pen(Brushes::Red, 2);
	g->DrawRectangle(pp, x_1_other, y_1_other, w_1, h_1);
	g->DrawImage(bitmap_1, 0, 0);
	this->pictureBox1->Image = bitmap_1;
	this->pictureBox1->Refresh();
}

System::Void MyForm::button_processing_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->backgroundWorker1->IsBusy != true) {
		this->backgroundWorker1->RunWorkerAsync();
	}
}

System::Void MyForm::backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	this->set_value(0);

	BmpFile img_1(way_1, this);
	BmpFile img_2(way_2, this);

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
	coord_img_2.height = coord_img_1.height;
	coord_img_2.width = coord_img_1.width;

	if (is_found){
		System::String^ data = brightness_correction(&img_1, &img_2, coord_img_1, coord_img_2, this);
		this->textBox3->Invoke(gcnew Action<System::String^>(this, &MyForm::dataUpdate), data);
		
		System::Drawing::Bitmap^  img = combining(&img_1, &img_2, coord_img_1, coord_img_2, this);
		this->pictureBox3->Invoke(gcnew Action<System::Drawing::Bitmap^>(this, &MyForm::setImage), img);

		this->set_value(100);
	}
	else {
		this->messageBox_error->Show("Пересечение не найдено", "Ошибка");
	}
}

System::Void MyForm::set_value(int value) {
	this->progressBar1->Invoke(gcnew Action<int>(this, &MyForm::setProgressBarValue), value);
}

System::Void MyForm::increasing_value(int value) {
	this->progressBar1->Invoke(gcnew Action<int>(this, &MyForm::increasingProgressBarValue), value);
}
