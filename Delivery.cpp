#include "Delivery.h"
#include "Produkt.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // 1. Сначала создаём форму склада
    Laba14::Produkt^ warehouseForm = gcnew Laba14::Produkt();

    // 2. Передаём её в конструктор Delivery
    Laba14::Delivery^ deliveryForm = gcnew Laba14::Delivery();

    Application::Run(deliveryForm);
    return 0;
}