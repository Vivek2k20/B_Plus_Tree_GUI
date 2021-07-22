#pragma once
#define _HAS_STD_BYTE 0
#include <msclr\marshal_cppstd.h>
#include "Success.h"
#include "Backend.h"

BPTree* bPTreeinsert;

namespace BTree {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for Insertform
	/// </summary>
	public ref class Insertform : public System::Windows::Forms::Form
	{
	public:
		Insertform(void)
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
		~Insertform()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::ComboBox^ vaccinelist;
	private: System::Windows::Forms::NumericUpDown^ rno;



	private: System::Windows::Forms::TextBox^ name;

	private: System::Windows::Forms::TextBox^ mobile;


	private: System::Windows::Forms::Button^ submit;
	private: System::Windows::Forms::Button^ C;
	private: System::Windows::Forms::TextBox^ dosenotext;












	private: System::ComponentModel::IContainer^ components;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Insertform::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->vaccinelist = (gcnew System::Windows::Forms::ComboBox());
			this->rno = (gcnew System::Windows::Forms::NumericUpDown());
			this->name = (gcnew System::Windows::Forms::TextBox());
			this->mobile = (gcnew System::Windows::Forms::TextBox());
			this->submit = (gcnew System::Windows::Forms::Button());
			this->C = (gcnew System::Windows::Forms::Button());
			this->dosenotext = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rno))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->Font = (gcnew System::Drawing::Font(L"MV Boli", 24, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(371, 41);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Enter record details :";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label2->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label2->Location = System::Drawing::Point(52, 91);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(165, 31);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Record No :";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label3->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label3->Location = System::Drawing::Point(52, 141);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(105, 31);
			this->label3->TabIndex = 11;
			this->label3->Text = L"Name :";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label4->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label4->Location = System::Drawing::Point(52, 194);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(162, 31);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Mobile No :";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label5->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label5->Location = System::Drawing::Point(52, 252);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(204, 31);
			this->label5->TabIndex = 13;
			this->label5->Text = L"Vaccine Name :";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label6->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label6->Location = System::Drawing::Point(52, 314);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(140, 31);
			this->label6->TabIndex = 14;
			this->label6->Text = L"Dose No :";
			// 
			// vaccinelist
			// 
			this->vaccinelist->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->vaccinelist->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->vaccinelist->Font = (gcnew System::Drawing::Font(L"MV Boli", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->vaccinelist->ForeColor = System::Drawing::SystemColors::ControlText;
			this->vaccinelist->FormattingEnabled = true;
			this->vaccinelist->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Covishield", L"Covaxin" });
			this->vaccinelist->Location = System::Drawing::Point(262, 254);
			this->vaccinelist->Name = L"vaccinelist";
			this->vaccinelist->Size = System::Drawing::Size(153, 29);
			this->vaccinelist->TabIndex = 15;
			// 
			// rno
			// 
			this->rno->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->rno->Font = (gcnew System::Drawing::Font(L"MV Boli", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rno->Location = System::Drawing::Point(223, 93);
			this->rno->Name = L"rno";
			this->rno->Size = System::Drawing::Size(80, 29);
			this->rno->TabIndex = 17;
			this->rno->ValueChanged += gcnew System::EventHandler(this, &Insertform::rno_ValueChanged);
			// 
			// name
			// 
			this->name->Font = (gcnew System::Drawing::Font(L"MV Boli", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->name->Location = System::Drawing::Point(163, 139);
			this->name->Name = L"name";
			this->name->Size = System::Drawing::Size(161, 33);
			this->name->TabIndex = 18;
			// 
			// mobile
			// 
			this->mobile->Font = (gcnew System::Drawing::Font(L"MV Boli", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mobile->Location = System::Drawing::Point(223, 192);
			this->mobile->MaxLength = 10;
			this->mobile->Name = L"mobile";
			this->mobile->Size = System::Drawing::Size(161, 33);
			this->mobile->TabIndex = 19;
			this->mobile->TextChanged += gcnew System::EventHandler(this, &Insertform::textBox2_TextChanged);
			this->mobile->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Insertform::mobile_KeyPress);
			// 
			// submit
			// 
			this->submit->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->submit->Font = (gcnew System::Drawing::Font(L"Times New Roman", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->submit->ForeColor = System::Drawing::SystemColors::ControlText;
			this->submit->Location = System::Drawing::Point(117, 386);
			this->submit->Name = L"submit";
			this->submit->Size = System::Drawing::Size(100, 35);
			this->submit->TabIndex = 21;
			this->submit->Text = L"Submit";
			this->submit->UseVisualStyleBackColor = false;
			this->submit->Click += gcnew System::EventHandler(this, &Insertform::submit_Click);
			// 
			// C
			// 
			this->C->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->C->Font = (gcnew System::Drawing::Font(L"Times New Roman", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->C->ForeColor = System::Drawing::SystemColors::ControlText;
			this->C->Location = System::Drawing::Point(375, 386);
			this->C->Name = L"C";
			this->C->Size = System::Drawing::Size(100, 35);
			this->C->TabIndex = 22;
			this->C->Text = L"Clear";
			this->C->UseVisualStyleBackColor = false;
			this->C->Click += gcnew System::EventHandler(this, &Insertform::C_Click);
			// 
			// dosenotext
			// 
			this->dosenotext->Font = (gcnew System::Drawing::Font(L"MV Boli", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dosenotext->Location = System::Drawing::Point(198, 314);
			this->dosenotext->MaxLength = 1;
			this->dosenotext->Name = L"dosenotext";
			this->dosenotext->Size = System::Drawing::Size(83, 33);
			this->dosenotext->TabIndex = 23;
			this->dosenotext->Text = L"1";
			// 
			// Insertform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(584, 461);
			this->Controls->Add(this->dosenotext);
			this->Controls->Add(this->C);
			this->Controls->Add(this->submit);
			this->Controls->Add(this->mobile);
			this->Controls->Add(this->name);
			this->Controls->Add(this->rno);
			this->Controls->Add(this->vaccinelist);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"Insertform";
			this->Text = L"Insert";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rno))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void mobile_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	char ch = e->KeyChar;
	if (!isdigit(ch) && ch != 8 && ch != 46)
		e->Handled = true;
}
private: System::Void rno_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void C_Click(System::Object^ sender, System::EventArgs^ e) {
	this->name->Text = gcnew String("");
	this->mobile->Text = gcnew String("");
	this->vaccinelist->Text = gcnew String("");
	this->rno->Value = NULL;
	this->dosenotext->Text = gcnew String("1");
}
private: System::Void bindingNavigator1_RefreshItems(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void submit_Click(System::Object^ sender, System::EventArgs^ e) {
	std::string names, mobiles, vaccine;
	int rnos,dose;
	names = msclr::interop::marshal_as<std::string>(name->Text);
	mobiles = msclr::interop::marshal_as<std::string>(mobile->Text);
	vaccine = msclr::interop::marshal_as<std::string>(vaccinelist->Text);
	rnos =(int)(rno->Value);
	dose = stoi(msclr::interop::marshal_as<std::string>(dosenotext->Text));
	std::string result;
	//result = std::to_string(rnos) +" "+ names +" "+ mobiles +" " + vaccine + " " + std::to_string(dose);
	Success^ messageform = gcnew Success();
	result=insertionMethod(&bPTreeinsert,rnos,names,vaccine,mobiles,dose);
	msg = result;
	messageform->ShowDialog();
}
private: System::Void doseno_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	char ch = e->KeyChar;
	if (ch!=49 && ch!=50 && ch != 8 && ch != 46)
		e->Handled = true;
}
};
}
