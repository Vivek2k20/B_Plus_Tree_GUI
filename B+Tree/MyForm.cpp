#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(cli::array<String^>^ args) {
	//BPTree* bPTree = new BPTree(4, 4);
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	BTree::MyForm form;
	Application::Run(% form);
}

