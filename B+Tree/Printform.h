#pragma once
#include "Backend.h"

BPTree* bPTreeprint;

namespace BTree {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Printform
	/// </summary>
	public ref class Printform : public System::Windows::Forms::Form
	{
	public:
		Printform(void)
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
		~Printform()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:







	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ Resulttext;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Printform::typeid));
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->Resulttext = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label4->Font = (gcnew System::Drawing::Font(L"MV Boli", 36, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label4->Location = System::Drawing::Point(719, 37);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(130, 63);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Tree";
			// 
			// Resulttext
			// 
			this->Resulttext->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Resulttext->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Resulttext->ForeColor = System::Drawing::Color::Chartreuse;
			this->Resulttext->Location = System::Drawing::Point(52, 120);
			this->Resulttext->Name = L"Resulttext";
			this->Resulttext->Size = System::Drawing::Size(1489, 703);
			this->Resulttext->TabIndex = 14;
			this->Resulttext->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Printform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1584, 861);
			this->Controls->Add(this->Resulttext);
			this->Controls->Add(this->label4);
			this->Name = L"Printform";
			this->Text = L"Print";
			this->Shown += gcnew System::EventHandler(this, &Printform::Printform_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Printform_Shown(System::Object^ sender, System::EventArgs^ e) {
		string ans= bPTreeprint->display(bPTreeprint->getRoot());
		this->Resulttext->Text = gcnew String(ans.c_str());
	}
	};
}
