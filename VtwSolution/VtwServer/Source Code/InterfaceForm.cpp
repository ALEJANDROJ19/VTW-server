#include "../InterfaceForm.h"

using namespace System;
using namespace System::Windows::Forms;


void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	VtwServer::InterfaceForm form;
	Application::Run(%form);
}
