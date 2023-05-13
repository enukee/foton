#pragma once
#include "pixel.h" 

namespace prog3v3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private: char* way_1;
	private: char* way_2; 
	private: int x_1;
	private: int y_1;
	private: int x_1_other;
	private: int y_1_other;
	private: int w_1;
	private: int h_1;

	private: int x_2;
	private: int y_2;
	private: int w_2;
	private: int h_2;

	private: Image^ image_1;
	private: Bitmap^ bitmap_1;

	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::TabPage^ tabPage4;

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label_h;
	private: System::Windows::Forms::Label^ label_w;
	private: System::Windows::Forms::Label^ label_y;
	private: System::Windows::Forms::Label^ label_x;

	private: System::Windows::Forms::TextBox^ textBox_x_1;
	private: System::Windows::Forms::TextBox^ textBox_y_1;
	private: System::Windows::Forms::TextBox^ textBox_w_1;
	private: System::Windows::Forms::TextBox^ textBox_h_1;

	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button_processing;
	private: System::Windows::Forms::Button^ button_open_file_2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button_open_file_1;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;

	private: System::Windows::Forms::TextBox^ textBox_h_2;
	private: System::Windows::Forms::TextBox^ textBox_w_2;
	private: System::Windows::Forms::TextBox^ textBox_y_2;
	private: System::Windows::Forms::TextBox^ textBox_x_2;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	

	private: System::Windows::Forms::MessageBox^ messageBox_error;


	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}





	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;

	private: System::Windows::Forms::TabControl^ tabControl1;

	private: System::Windows::Forms::TabPage^ tabPage2;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button_processing = (gcnew System::Windows::Forms::Button());
			this->button_open_file_2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button_open_file_1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label_x = (gcnew System::Windows::Forms::Label());
			this->textBox_x_1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_y_1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_w_1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_h_1 = (gcnew System::Windows::Forms::TextBox());
			this->label_y = (gcnew System::Windows::Forms::Label());
			this->label_w = (gcnew System::Windows::Forms::Label());
			this->label_h = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox_x_2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox_y_2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox_w_2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox_h_2 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1126, 598);
			this->tabControl1->TabIndex = 5;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::White;
			this->tabPage1->Controls->Add(this->progressBar1);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->textBox3);
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->button_processing);
			this->tabPage1->Controls->Add(this->button_open_file_2);
			this->tabPage1->Controls->Add(this->textBox2);
			this->tabPage1->Controls->Add(this->button_open_file_1);
			this->tabPage1->Controls->Add(this->panel1);
			this->tabPage1->Controls->Add(this->panel2);
			this->tabPage1->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1118, 569);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Параметры";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(643, 364);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(362, 23);
			this->progressBar1->TabIndex = 26;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(49, 158);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(108, 16);
			this->label6->TabIndex = 23;
			this->label6->Text = L"Изображение 2";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(49, 26);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(108, 16);
			this->label5->TabIndex = 22;
			this->label5->Text = L"Изображение 1";
			// 
			// textBox3
			// 
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox3->Location = System::Drawing::Point(35, 285);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(285, 245);
			this->textBox3->TabIndex = 13;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(160, 50);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(419, 22);
			this->textBox1->TabIndex = 3;
			// 
			// button_processing
			// 
			this->button_processing->Location = System::Drawing::Point(643, 301);
			this->button_processing->Name = L"button_processing";
			this->button_processing->Size = System::Drawing::Size(135, 33);
			this->button_processing->TabIndex = 0;
			this->button_processing->Text = L"Объединить";
			this->button_processing->UseVisualStyleBackColor = true;
			this->button_processing->Click += gcnew System::EventHandler(this, &MyForm::button_processing_Click);
			// 
			// button_open_file_2
			// 
			this->button_open_file_2->Location = System::Drawing::Point(52, 177);
			this->button_open_file_2->Name = L"button_open_file_2";
			this->button_open_file_2->Size = System::Drawing::Size(75, 31);
			this->button_open_file_2->TabIndex = 2;
			this->button_open_file_2->Text = L"Открыть";
			this->button_open_file_2->UseVisualStyleBackColor = true;
			this->button_open_file_2->Click += gcnew System::EventHandler(this, &MyForm::button_open_file_2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(160, 181);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(419, 22);
			this->textBox2->TabIndex = 4;
			// 
			// button_open_file_1
			// 
			this->button_open_file_1->Location = System::Drawing::Point(52, 45);
			this->button_open_file_1->Name = L"button_open_file_1";
			this->button_open_file_1->Size = System::Drawing::Size(75, 32);
			this->button_open_file_1->TabIndex = 1;
			this->button_open_file_1->Text = L"Открыть";
			this->button_open_file_1->UseVisualStyleBackColor = true;
			this->button_open_file_1->Click += gcnew System::EventHandler(this, &MyForm::button_open_file_1_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::White;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->label_x);
			this->panel1->Controls->Add(this->textBox_x_1);
			this->panel1->Controls->Add(this->textBox_y_1);
			this->panel1->Controls->Add(this->textBox_w_1);
			this->panel1->Controls->Add(this->textBox_h_1);
			this->panel1->Controls->Add(this->label_y);
			this->panel1->Controls->Add(this->label_w);
			this->panel1->Controls->Add(this->label_h);
			this->panel1->Location = System::Drawing::Point(35, 16);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1040, 120);
			this->panel1->TabIndex = 24;
			// 
			// label_x
			// 
			this->label_x->AutoSize = true;
			this->label_x->Location = System::Drawing::Point(605, 34);
			this->label_x->Name = L"label_x";
			this->label_x->Size = System::Drawing::Size(98, 16);
			this->label_x->TabIndex = 9;
			this->label_x->Text = L"Коррдината x:";
			// 
			// textBox_x_1
			// 
			this->textBox_x_1->Location = System::Drawing::Point(709, 28);
			this->textBox_x_1->Name = L"textBox_x_1";
			this->textBox_x_1->Size = System::Drawing::Size(84, 22);
			this->textBox_x_1->TabIndex = 5;
			this->textBox_x_1->Text = L"367";
			this->textBox_x_1->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::textBox_x_1_Validating);
			// 
			// textBox_y_1
			// 
			this->textBox_y_1->Location = System::Drawing::Point(709, 83);
			this->textBox_y_1->Name = L"textBox_y_1";
			this->textBox_y_1->Size = System::Drawing::Size(84, 22);
			this->textBox_y_1->TabIndex = 6;
			this->textBox_y_1->Text = L"241";
			this->textBox_y_1->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::textBox_y_1_Validating);
			// 
			// textBox_w_1
			// 
			this->textBox_w_1->Location = System::Drawing::Point(915, 28);
			this->textBox_w_1->Name = L"textBox_w_1";
			this->textBox_w_1->Size = System::Drawing::Size(84, 22);
			this->textBox_w_1->TabIndex = 7;
			this->textBox_w_1->Text = L"118";
			this->textBox_w_1->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::textBox_w_1_Validating);
			// 
			// textBox_h_1
			// 
			this->textBox_h_1->Location = System::Drawing::Point(915, 83);
			this->textBox_h_1->Name = L"textBox_h_1";
			this->textBox_h_1->Size = System::Drawing::Size(84, 22);
			this->textBox_h_1->TabIndex = 8;
			this->textBox_h_1->Text = L"62";
			this->textBox_h_1->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::textBox_h_1_Validating);
			// 
			// label_y
			// 
			this->label_y->AutoSize = true;
			this->label_y->Location = System::Drawing::Point(604, 84);
			this->label_y->Name = L"label_y";
			this->label_y->Size = System::Drawing::Size(99, 16);
			this->label_y->TabIndex = 10;
			this->label_y->Text = L"Коррдината y:";
			// 
			// label_w
			// 
			this->label_w->AutoSize = true;
			this->label_w->Location = System::Drawing::Point(859, 31);
			this->label_w->Name = L"label_w";
			this->label_w->Size = System::Drawing::Size(50, 16);
			this->label_w->TabIndex = 11;
			this->label_w->Text = L"Ширна";
			// 
			// label_h
			// 
			this->label_h->AutoSize = true;
			this->label_h->Location = System::Drawing::Point(854, 84);
			this->label_h->Name = L"label_h";
			this->label_h->Size = System::Drawing::Size(55, 16);
			this->label_h->TabIndex = 12;
			this->label_h->Text = L"Высота";
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::White;
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->label4);
			this->panel2->Controls->Add(this->textBox_x_2);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Controls->Add(this->textBox_y_2);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->textBox_w_2);
			this->panel2->Controls->Add(this->label3);
			this->panel2->Controls->Add(this->textBox_h_2);
			this->panel2->Location = System::Drawing::Point(35, 144);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1040, 120);
			this->panel2->TabIndex = 25;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(605, 37);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(98, 16);
			this->label4->TabIndex = 18;
			this->label4->Text = L"Коррдината x:";
			// 
			// textBox_x_2
			// 
			this->textBox_x_2->Location = System::Drawing::Point(709, 31);
			this->textBox_x_2->Name = L"textBox_x_2";
			this->textBox_x_2->Size = System::Drawing::Size(84, 22);
			this->textBox_x_2->TabIndex = 14;
			this->textBox_x_2->Text = L"0";
			this->textBox_x_2->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::textBox_x_2_Validating);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(854, 87);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(55, 16);
			this->label1->TabIndex = 21;
			this->label1->Text = L"Высота";
			// 
			// textBox_y_2
			// 
			this->textBox_y_2->Location = System::Drawing::Point(709, 86);
			this->textBox_y_2->Name = L"textBox_y_2";
			this->textBox_y_2->Size = System::Drawing::Size(84, 22);
			this->textBox_y_2->TabIndex = 15;
			this->textBox_y_2->Text = L"0";
			this->textBox_y_2->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::textBox_y_2_Validating);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(859, 34);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(50, 16);
			this->label2->TabIndex = 20;
			this->label2->Text = L"Ширна";
			// 
			// textBox_w_2
			// 
			this->textBox_w_2->Location = System::Drawing::Point(915, 31);
			this->textBox_w_2->Name = L"textBox_w_2";
			this->textBox_w_2->Size = System::Drawing::Size(84, 22);
			this->textBox_w_2->TabIndex = 16;
			this->textBox_w_2->Text = L"0";
			this->textBox_w_2->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::textBox_w_2_Validating);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(604, 87);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(99, 16);
			this->label3->TabIndex = 19;
			this->label3->Text = L"Коррдината y:";
			// 
			// textBox_h_2
			// 
			this->textBox_h_2->Location = System::Drawing::Point(915, 86);
			this->textBox_h_2->Name = L"textBox_h_2";
			this->textBox_h_2->Size = System::Drawing::Size(84, 22);
			this->textBox_h_2->TabIndex = 17;
			this->textBox_h_2->Text = L"0";
			this->textBox_h_2->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::textBox_h_2_Validating);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->pictureBox1);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1118, 569);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Cross;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1118, 569);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->pictureBox2);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(1118, 569);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"tabPage3";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(0, 0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(1118, 569);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->pictureBox3);
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(1118, 569);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"tabPage4";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(0, 0);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(1118, 569);
			this->pictureBox3->TabIndex = 3;
			this->pictureBox3->TabStop = false;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1126, 600);
			this->Controls->Add(this->tabControl1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->tabPage4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button_processing_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void button_open_file_1_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_open_file_2_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	private: System::Void textBox_x_1_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void textBox_y_1_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void textBox_w_1_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void textBox_h_1_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void textBox_x_2_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void textBox_y_2_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void textBox_w_2_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void textBox_h_2_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);

	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);

	public: System::Void set_value(int value);

	public: System::Void increasing_value(int value);

	public: System::Void setProgressBarValue(int value) {
		this->progressBar1->Value = value;
	}

	public: System::Void increasingProgressBarValue(int value) {
		this->progressBar1->Value += value;
	}

	public: int getProgressBarValue() {
		return this->progressBar1->Value ;
	}

	public: System::Void dataUpdate(System::String^ data) {
		this->textBox3->Text = data;
	}

	public: System::Void setImage(Drawing::Bitmap^ bitmap) {
		this->pictureBox3->Image = bitmap;
		this->pictureBox3->Refresh();
	}
};
}
