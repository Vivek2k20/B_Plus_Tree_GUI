#pragma once
#define _HAS_STD_BYTE 0
#include<bits/stdc++.h>

std::string msg;



namespace BTree {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Success
	/// </summary>
	public ref class Success : public System::Windows::Forms::Form
	{
	public:
		Success(void)
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
		~Success()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ result;
	protected:
	private: System::Windows::Forms::Button^ button1;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Success::typeid));
			this->result = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// result
			// 
			this->result->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->result->Location = System::Drawing::Point(32, 31);
			this->result->Margin = System::Windows::Forms::Padding(8, 0, 8, 0);
			this->result->Name = L"result";
			this->result->Size = System::Drawing::Size(305, 190);
			this->result->TabIndex = 0;
			this->result->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->button1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button1->Location = System::Drawing::Point(154, 250);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Ok";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Success::button1_Click);
			// 
			// Success
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(15, 31);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(376, 285);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->result);
			this->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->Margin = System::Windows::Forms::Padding(8, 7, 8, 7);
			this->Name = L"Success";
			this->Text = L"Message";
			this->Shown += gcnew System::EventHandler(this, &Success::Success_Shown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		delete this;
	}
	private: System::Void Success_Shown(System::Object^ sender, System::EventArgs^ e) {
		this->result->Text = gcnew String(msg.c_str());
	}
	};
}
