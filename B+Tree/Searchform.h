#pragma once
#include<bits/stdc++.h>
#include "Backend.h"
#include "Success.h"

BPTree* bPTreesearch;


namespace BTree {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Searchform
	/// </summary>
	public ref class Searchform : public System::Windows::Forms::Form
	{
	public:
		Searchform(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Searchform()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ Result;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ Resulttext;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Searchform::typeid));
			this->Result = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->Resulttext = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// Result
			// 
			this->Result->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Result->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Result->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->Result->Location = System::Drawing::Point(361, 134);
			this->Result->Name = L"Result";
			this->Result->Size = System::Drawing::Size(172, 31);
			this->Result->TabIndex = 0;
			this->Result->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Result->Click += gcnew System::EventHandler(this, &Searchform::Result_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->button1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button1->Location = System::Drawing::Point(109, 263);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 27);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Search";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Searchform::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->Font = (gcnew System::Drawing::Font(L"MV Boli", 36, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label1->Location = System::Drawing::Point(71, 43);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(175, 63);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Search";
			this->label1->Click += gcnew System::EventHandler(this, &Searchform::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label2->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label2->Location = System::Drawing::Point(12, 134);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(278, 31);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Enter the Record No :";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numericUpDown1->Location = System::Drawing::Point(104, 190);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(80, 26);
			this->numericUpDown1->TabIndex = 5;
			// 
			// label3
			// 
			this->label3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label3->Location = System::Drawing::Point(300, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(2, 500);
			this->label3->TabIndex = 6;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label4->Font = (gcnew System::Drawing::Font(L"MV Boli", 36, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label4->Location = System::Drawing::Point(356, 43);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(174, 63);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Result";
			// 
			// Resulttext
			// 
			this->Resulttext->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Resulttext->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Resulttext->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->Resulttext->Location = System::Drawing::Point(308, 190);
			this->Resulttext->Name = L"Resulttext";
			this->Resulttext->Size = System::Drawing::Size(274, 124);
			this->Resulttext->TabIndex = 8;
			this->Resulttext->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Resulttext->Click += gcnew System::EventHandler(this, &Searchform::Resulttext_Click);
			// 
			// Searchform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(584, 461);
			this->Controls->Add(this->Resulttext);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->Result);
			this->Name = L"Searchform";
			this->Text = L"Search";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		int rnos = (int)(numericUpDown1->Value);
		string result= searchMethod(bPTreesearch,rnos);
		string tocompare = "Record not found!\n";
		if (result.compare(tocompare) == 0)
		{
			this->Result->Text = gcnew String("");
			this->Resulttext->Text = gcnew String(result.c_str());
		}
		else
		{
			string tmp = "Record found!\n";
			this->Result->Text = gcnew String(tmp.c_str());
			this->Resulttext->Text = gcnew String(result.c_str());
		};
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void Resulttext_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Result_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
