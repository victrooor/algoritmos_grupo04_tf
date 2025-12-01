#include "MyForm.h"
using namespace JuegoFinal;
void main() {
	Application::EnableVisualStyles;
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew JuegoFinal::MyForm());
}
