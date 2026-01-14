#pragma once

#include "Produkt.h" 
namespace Laba14 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class Delivery : public System::Windows::Forms::Form
	{
	private:
		// УДАЛЕНО: Produkt^ warehouseForm; ← больше не нужно!

		System::Windows::Forms::Button^ Добавить;
		System::Windows::Forms::CheckBox^ checkBox;
		System::Windows::Forms::TextBox^ textBox;
		System::Windows::Forms::Label^ label;
		System::Windows::Forms::Label^ labelAddress;
		System::Windows::Forms::Label^ labelResult;
		System::Windows::Forms::TextBox^ textBoxName;
		System::Windows::Forms::Label^ labelName;
		System::Windows::Forms::ComboBox^ comboBoxDelivery;
		System::Windows::Forms::Label^ labelDeliveryType;
		System::Windows::Forms::ListBox^ ОкноСЗаказами;
		System::Windows::Forms::Button^ button1;

		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::Button^ button2;
		System::Windows::Forms::TextBox^ textBox1;
		System::Windows::Forms::ListBox^ ОкноДляПродуктов;
		System::Windows::Forms::Button^ buttonOpenWarehouse;
		System::ComponentModel::Container^ components;
		System::Windows::Forms::ComboBox^ comboBox1;

		// ========== ДАННЫЕ ЗАКАЗА ==========
		List<String^>^ orders;
		List<String^>^ selectedProducts;   
		List<int>^ productQuantities;      
		List<double>^ productPrices;       

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Delivery::typeid));
			this->Добавить = (gcnew System::Windows::Forms::Button());
			this->checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->textBox = (gcnew System::Windows::Forms::TextBox());
			this->label = (gcnew System::Windows::Forms::Label());
			this->labelAddress = (gcnew System::Windows::Forms::Label());
			this->labelResult = (gcnew System::Windows::Forms::Label());
			this->textBoxName = (gcnew System::Windows::Forms::TextBox());
			this->labelName = (gcnew System::Windows::Forms::Label());
			this->comboBoxDelivery = (gcnew System::Windows::Forms::ComboBox());
			this->labelDeliveryType = (gcnew System::Windows::Forms::Label());
			this->ОкноСЗаказами = (gcnew System::Windows::Forms::ListBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->ОкноДляПродуктов = (gcnew System::Windows::Forms::ListBox());
			this->buttonOpenWarehouse = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// Добавить
			// 
			this->Добавить->BackColor = System::Drawing::SystemColors::Info;
			this->Добавить->Cursor = System::Windows::Forms::Cursors::Default;
			this->Добавить->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Добавить->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Добавить->Location = System::Drawing::Point(66, 297);
			this->Добавить->Name = L"Добавить";
			this->Добавить->Size = System::Drawing::Size(284, 37);
			this->Добавить->TabIndex = 0;
			this->Добавить->Text = L"Создать Заказ";
			this->Добавить->UseVisualStyleBackColor = false;
			this->Добавить->Click += gcnew System::EventHandler(this, &Delivery::Добавить_Click);
			// 
			// checkBox
			// 
			this->checkBox->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->checkBox->CheckAlign = System::Drawing::ContentAlignment::TopLeft;
			this->checkBox->Location = System::Drawing::Point(169, 133);
			this->checkBox->Name = L"checkBox";
			this->checkBox->Size = System::Drawing::Size(150, 20);
			this->checkBox->TabIndex = 3;
			this->checkBox->Text = L"Самовывоз";
			this->checkBox->UseVisualStyleBackColor = false;
			this->checkBox->CheckedChanged += gcnew System::EventHandler(this, &Delivery::checkBox_CheckedChanged);
			// 
			// textBox
			// 
			this->textBox->Location = System::Drawing::Point(66, 108);
			this->textBox->Multiline = true;
			this->textBox->Name = L"textBox";
			this->textBox->Size = System::Drawing::Size(253, 22);
			this->textBox->TabIndex = 2;
			// 
			// label
			// 
			this->label->AutoSize = true;
			this->label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label->Location = System::Drawing::Point(112, 9);
			this->label->Name = L"label";
			this->label->Size = System::Drawing::Size(227, 25);
			this->label->TabIndex = 4;
			this->label->Text = L"Оформление Заказа";
			// 
			// labelAddress
			// 
			this->labelAddress->AutoSize = true;
			this->labelAddress->Location = System::Drawing::Point(63, 89);
			this->labelAddress->Name = L"labelAddress";
			this->labelAddress->Size = System::Drawing::Size(114, 16);
			this->labelAddress->TabIndex = 5;
			this->labelAddress->Text = L"Адрес доставки:";
			// 
			// labelResult
			// 
			this->labelResult->AutoSize = true;
			this->labelResult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelResult->Location = System::Drawing::Point(12, 337);
			this->labelResult->Name = L"labelResult";
			this->labelResult->Size = System::Drawing::Size(84, 18);
			this->labelResult->TabIndex = 6;
			this->labelResult->Text = L"Результат:";
			// 
			// textBoxName
			// 
			this->textBoxName->Location = System::Drawing::Point(66, 60);
			this->textBoxName->Multiline = true;
			this->textBoxName->Name = L"textBoxName";
			this->textBoxName->Size = System::Drawing::Size(253, 22);
			this->textBoxName->TabIndex = 1;
			// 
			// labelName
			// 
			this->labelName->AutoSize = true;
			this->labelName->Location = System::Drawing::Point(63, 41);
			this->labelName->Name = L"labelName";
			this->labelName->Size = System::Drawing::Size(114, 16);
			this->labelName->TabIndex = 7;
			this->labelName->Text = L"ФИО заказчика:";
			// 
			// comboBoxDelivery
			// 
			this->comboBoxDelivery->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxDelivery->FormattingEnabled = true;
			this->comboBoxDelivery->Location = System::Drawing::Point(66, 170);
			this->comboBoxDelivery->Name = L"comboBoxDelivery";
			this->comboBoxDelivery->Size = System::Drawing::Size(253, 24);
			this->comboBoxDelivery->TabIndex = 8;
			this->comboBoxDelivery->SelectedIndexChanged += gcnew System::EventHandler(this, &Delivery::comboBoxDelivery_SelectedIndexChanged);
			// 
			// labelDeliveryType
			// 
			this->labelDeliveryType->AutoSize = true;
			this->labelDeliveryType->Location = System::Drawing::Point(63, 151);
			this->labelDeliveryType->Name = L"labelDeliveryType";
			this->labelDeliveryType->Size = System::Drawing::Size(99, 16);
			this->labelDeliveryType->TabIndex = 9;
			this->labelDeliveryType->Text = L"Тип доставки:";
			// 
			// ОкноСЗаказами
			// 
			this->ОкноСЗаказами->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->ОкноСЗаказами->FormattingEnabled = true;
			this->ОкноСЗаказами->ItemHeight = 16;
			this->ОкноСЗаказами->Location = System::Drawing::Point(355, 41);
			this->ОкноСЗаказами->Name = L"ОкноСЗаказами";
			this->ОкноСЗаказами->Size = System::Drawing::Size(609, 148);
			this->ОкноСЗаказами->TabIndex = 10;
			this->ОкноСЗаказами->SelectedIndexChanged += gcnew System::EventHandler(this, &Delivery::listBoxOrders_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->button1->Location = System::Drawing::Point(613, 337);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(151, 67);
			this->button1->TabIndex = 11;
			this->button1->Text = L"Обновить товары";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Delivery::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(72, 197);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(115, 16);
			this->label1->TabIndex = 13;
			this->label1->Text = L"Товар со склада";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(231, 197);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(88, 16);
			this->label2->TabIndex = 14;
			this->label2->Text = L"Количество:";
			// 
			// button2
			// 
			this->button2->Cursor = System::Windows::Forms::Cursors::Default;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->ForeColor = System::Drawing::Color::Black;
			this->button2->Location = System::Drawing::Point(114, 260);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(181, 31);
			this->button2->TabIndex = 16;
			this->button2->Text = L"Добавить в Заказ";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Delivery::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(277, 221);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(42, 22);
			this->textBox1->TabIndex = 17;
			// 
			// ОкноДляПродуктов
			// 
			this->ОкноДляПродуктов->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->ОкноДляПродуктов->FormattingEnabled = true;
			this->ОкноДляПродуктов->ItemHeight = 16;
			this->ОкноДляПродуктов->Location = System::Drawing::Point(355, 197);
			this->ОкноДляПродуктов->Name = L"ОкноДляПродуктов";
			this->ОкноДляПродуктов->Size = System::Drawing::Size(609, 132);
			this->ОкноДляПродуктов->TabIndex = 18;
			// 
			// buttonOpenWarehouse
			// 
			this->buttonOpenWarehouse->BackColor = System::Drawing::Color::LightSkyBlue;
			this->buttonOpenWarehouse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->buttonOpenWarehouse->ForeColor = System::Drawing::SystemColors::ControlText;
			this->buttonOpenWarehouse->Location = System::Drawing::Point(770, 337);
			this->buttonOpenWarehouse->Name = L"buttonOpenWarehouse";
			this->buttonOpenWarehouse->Size = System::Drawing::Size(151, 67);
			this->buttonOpenWarehouse->TabIndex = 19;
			this->buttonOpenWarehouse->Text = L"Открыть склад";
			this->buttonOpenWarehouse->UseVisualStyleBackColor = false;
			this->buttonOpenWarehouse->Click += gcnew System::EventHandler(this, &Delivery::buttonOpenWarehouse_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(66, 221);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(176, 24);
			this->comboBox1->TabIndex = 20;
			// 
			// Delivery
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->ClientSize = System::Drawing::Size(976, 433);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->buttonOpenWarehouse);
			this->Controls->Add(this->ОкноДляПродуктов);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->ОкноСЗаказами);
			this->Controls->Add(this->labelDeliveryType);
			this->Controls->Add(this->comboBoxDelivery);
			this->Controls->Add(this->labelName);
			this->Controls->Add(this->textBoxName);
			this->Controls->Add(this->labelResult);
			this->Controls->Add(this->labelAddress);
			this->Controls->Add(this->label);
			this->Controls->Add(this->checkBox);
			this->Controls->Add(this->textBox);
			this->Controls->Add(this->Добавить);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Delivery";
			this->Text = L"Система доставки";
			this->Load += gcnew System::EventHandler(this, &Delivery::Delivery_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
		
		Delivery()
		{
			InitializeComponent();
			InitializeOrderData();
			UpdateAddressField();
			this->textBoxName->KeyPress += gcnew KeyPressEventHandler(this, &Delivery::textBoxName_KeyPress);
		}

	protected:
		~Delivery()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		void InitializeOrderData()
		{
			orders = gcnew List<String^>();
			selectedProducts = gcnew List<String^>();
			productQuantities = gcnew List<int>();
			productPrices = gcnew List<double>();
			// Инициализация типов доставки
			comboBoxDelivery->Items->Add("Стандартная доставка");
			comboBoxDelivery->Items->Add("Экспресс доставка");
			comboBoxDelivery->SelectedIndex = 0;
			// Загрузка товаров при старте
			LoadProductsFromWarehouse();
		}

		// Загружает список доступных товаров из НОВОГО экземпляра склада
		void LoadProductsFromWarehouse()
		{
			try
			{
				// Создаём ВРЕМЕННЫЙ экземпляр склада только для чтения данных
				Produkt^ tempWarehouse = gcnew Produkt();
				comboBox1->DataSource = nullptr;
				comboBox1->Items->Clear();
				List<String^>^ products = tempWarehouse->GetAvailableProductsWithQuantity();
				comboBox1->DataSource = products;
				if (products->Count > 0)
				{
					comboBox1->SelectedIndex = 0;
					textBox1->Text = "1";
				}
				else
				{
					textBox1->Text = "";
					labelResult->Text = "Склад пуст";
				}
				delete tempWarehouse; // ← важно!
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка загрузки склада: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				labelResult->Text = "Ошибка загрузки";
			}
		}

		String^ ExtractProductName(String^ productString)
		{
			int bracketIndex = productString->IndexOf('(');
			if (bracketIndex > 0)
			{
				return productString->Substring(0, bracketIndex)->Trim();
			}
			return productString;
		}

		double ExtractProductPrice(String^ productString)
		{
			try
			{
				int openBracket = productString->IndexOf('(');
				int closeBracket = productString->IndexOf(')');
				if (openBracket > 0 && closeBracket > openBracket)
				{
					String^ pricePart = productString->Substring(openBracket + 1, closeBracket - openBracket - 1);
					pricePart = pricePart->Replace("руб", "")->Trim();
					return Convert::ToDouble(pricePart);
				}
			}
			catch (Exception^) { 
			}
			return 0.0;
		}

		int ExtractProductQuantity(String^ productString)
		{
			try
			{
				int dashIndex = productString->LastIndexOf('-');
				if (dashIndex > 0)
				{
					String^ qtyPart = productString->Substring(dashIndex + 1);
					qtyPart = qtyPart->Replace("шт.", "")->Replace("шт", "")->Trim();
					return Convert::ToInt32(qtyPart);
				}
			}
			catch (Exception^) { 
			}
			return 0;
		}

		void UpdateAddressField()
		{
			if (checkBox->Checked)
			{
				textBox->Enabled = false;
				textBox->Text = "Самовывоз";
				textBox->BackColor = Color::LightGray;
				comboBoxDelivery->Enabled = false;
				comboBoxDelivery->SelectedIndex = -1;
				comboBoxDelivery->Text = "Самовывоз";
			}
			else
			{
				textBox->Enabled = true;
				textBox->Text = "";
				textBox->BackColor = Color::White;
				comboBoxDelivery->Enabled = true;
				comboBoxDelivery->SelectedIndex = 0;
			}
		}

		bool ValidateName(String^ name)
		{
			if (String::IsNullOrWhiteSpace(name)) return false;
			for each (Char c in name)
			{
				if (!(Char::IsLetter(c) || c == ' ' || c == '-')) return false;
			}
			return name->Trim()->Length >= 2;
		}

		String^ FormatName(String^ name)
		{
			if (String::IsNullOrWhiteSpace(name)) return name;
			array<Char>^ seps = { ' ' };
			array<String^>^ parts = name->Split(seps, StringSplitOptions::RemoveEmptyEntries);
			for (int i = 0; i < parts->Length; i++)
			{
				if (parts[i]->Length > 0)
				{
					parts[i] = Char::ToUpper(parts[i][0]) + parts[i]->Substring(1)->ToLower();
				}
			}
			return String::Join(" ", parts);
		}

		double CalculateCost(bool isPickup, String^ deliveryType, String^ address)
		{
			if (isPickup) return 0.0;
			std::string addr = msclr::interop::marshal_as<std::string>(address);
			if (deliveryType == "Стандартная доставка") return 200.0 + (addr.length() * 0.1);
			if (deliveryType == "Экспресс доставка") return 500.0 + (addr.length() * 0.2);
			return 0.0;
		}

		int CalculateDays(bool isPickup, String^ deliveryType, String^ address)
		{
			if (isPickup) return 0;
			std::string addr = msclr::interop::marshal_as<std::string>(address);
			if (deliveryType == "Стандартная доставка") return 3 + (addr.length() / 50);
			if (deliveryType == "Экспресс доставка") return 1 + (addr.length() / 100);
			return 0;
		}

		String^ GetDeliveryDescription(bool isPickup, String^ deliveryType)
		{
			if (isPickup) return "Самовывоз из пункта выдачи. Бесплатно. Доступно сразу после оформления.";
			if (deliveryType == "Стандартная доставка") return "Доставка курьером в течение 3-7 дней";
			if (deliveryType == "Экспресс доставка") return "Срочная доставка курьером в течение 1-2 дней";
			return "";
		}

		double CalculateTotalProductsCost()
		{
			double total = 0.0;
			for (int i = 0; i < selectedProducts->Count; i++)
			{
				total += productPrices[i] * productQuantities[i];
			}
			return total;
		}

		// ========== ОБРАБОТЧИКИ СОБЫТИЙ ==========

	private:
		System::Void Delivery_Load(System::Object^ sender, System::EventArgs^ e)
		{
			LoadProductsFromWarehouse();
		}

		System::Void Добавить_Click(System::Object^ sender, System::EventArgs^ e)
		{
		
			if (String::IsNullOrWhiteSpace(textBoxName->Text))
			{
				MessageBox::Show("Введите ФИО", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			String^ customerName = FormatName(textBoxName->Text->Trim());
			if (!ValidateName(customerName))
			{
				MessageBox::Show("Некорректное ФИО", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			if (!checkBox->Checked && String::IsNullOrEmpty(textBox->Text))
			{
				MessageBox::Show("Введите адрес", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			if (selectedProducts->Count == 0)
			{
				MessageBox::Show("Добавьте товары", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			String^ address = checkBox->Checked ? "Самовывоз" : textBox->Text;
			String^ deliveryType = comboBoxDelivery->Text;
			bool isPickup = checkBox->Checked;
			double deliveryCost = CalculateCost(isPickup, deliveryType, address);
			double productsCost = CalculateTotalProductsCost();
			double totalCost = deliveryCost + productsCost;
			int days = CalculateDays(isPickup, deliveryType, address);
			String^ description = GetDeliveryDescription(isPickup, deliveryType);

			// === ГЛАВНОЕ: ОБНОВЛЕНИЕ СКЛАДА ===
			bool allUpdated = true;
			
			// Создаём ВРЕМЕННЫЙ экземпляр склада для обновления
			Produkt^ tempWarehouse = gcnew Produkt();
			for (int i = 0; i < selectedProducts->Count; i++)
			{
				String^ productName = selectedProducts[i];
				int qty = productQuantities[i];
				if (!tempWarehouse->DecreaseProductQuantity(productName, qty))
				{
					allUpdated = false;
					break;
				}
			}
			delete tempWarehouse; // ← важно!

			if (!allUpdated)
			{
				MessageBox::Show("Не удалось оформить заказ. Проверьте наличие товаров.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// Формирование и сохранение заказа
			String^ orderInfo = String::Format("========== ЗАКАЗ №{0} ==========\r\nДата: {1}\r\nКлиент: {2}\r\nТип: {3}\r\nАдрес: {4}\r\n",
				orders->Count + 1, DateTime::Now.ToString("dd.MM.yyyy HH:mm"), customerName, deliveryType, address);
			orderInfo += "--------------------------------\r\n";
			for (int i = 0; i < selectedProducts->Count; i++)
			{
				orderInfo += String::Format("{0} x {1} шт. = {2:F2} руб\r\n",
					selectedProducts[i], productQuantities[i], productPrices[i] * productQuantities[i]);
			}
			orderInfo += "--------------------------------\r\n";
			orderInfo += String::Format("Товары: {0:F2} руб\r\nДоставка: {1:F2} руб\r\nИТОГО: {2:F2} руб\r\nСрок: {3} дн.\r\nПримечание: {4}\r\n================================\r\n",
				productsCost, deliveryCost, totalCost, days, description);

			orders->Add(orderInfo);
			ОкноСЗаказами->Items->Add(String::Format("Заказ #{0}: {1} - {2:F2} руб", orders->Count, customerName, totalCost));
			labelResult->Text = String::Format("Заказ оформлен! Сумма: {0:F2} руб", totalCost);

			// Очистка
			selectedProducts->Clear();
			productQuantities->Clear();
			productPrices->Clear();
			ОкноДляПродуктов->Items->Clear();
			LoadProductsFromWarehouse(); 
			textBoxName->Clear();
			textBox->Clear();
			checkBox->Checked = false;
			UpdateAddressField();
			SaveToFile(orderInfo);
		}

		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (comboBox1->SelectedIndex == -1)
			{
				MessageBox::Show("Выберите товар", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			int qty;
			if (!Int32::TryParse(textBox1->Text, qty) || qty <= 0)
			{
				MessageBox::Show("Некорректное количество", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			String^ fullProductStr = comboBox1->SelectedItem->ToString();
			String^ productName = ExtractProductName(fullProductStr);
			
			// Получаем актуальное количество из склада
			Produkt^ tempWarehouse = gcnew Produkt();
			int availableQty = tempWarehouse->GetProductQuantity(productName);
			delete tempWarehouse;

			if (qty > availableQty)
			{
				MessageBox::Show(String::Format("Недостаточно товара. Доступно: {0}", availableQty), "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			// Добавляем в заказ
			selectedProducts->Add(productName);
			productQuantities->Add(qty);
			productPrices->Add(ExtractProductPrice(fullProductStr));
			ОкноДляПродуктов->Items->Add(String::Format("{0} x {1} шт. = {2:F2} руб", productName, qty, qty * ExtractProductPrice(fullProductStr)));
			labelResult->Text = "Товар добавлен в заказ";
			textBox1->Text = "1";
		}

		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
		{
			LoadProductsFromWarehouse();
			MessageBox::Show("Список товаров обновлён!", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		// ✅ КНОПКА "ОТКРЫТЬ СКЛАД" 
		System::Void buttonOpenWarehouse_Click(System::Object^ sender, System::EventArgs^ e)
		{
			(gcnew Produkt())->Show(); 
		}

		System::Void comboBoxDelivery_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
		{
			// Можно оставить пустым
		}

		System::Void textBoxName_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
		{
			Char c = e->KeyChar;
			e->Handled = !(Char::IsControl(c) || Char::IsLetter(c) || c == ' ' || c == '-');
		}

		System::Void checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			UpdateAddressField();
		}

		System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (comboBox1->SelectedIndex != -1)
			{
				String^ productName = ExtractProductName(comboBox1->SelectedItem->ToString());
				Produkt^ tempWarehouse = gcnew Produkt();
				int qty = tempWarehouse->GetProductQuantity(productName);
				delete tempWarehouse;
				labelResult->Text = String::Format("Доступно: {0} шт.", qty);
				textBox1->Text = "1";
			}
		}

		System::Void listBoxOrders_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
		{
			// Можно реализовать просмотр деталей заказа при необходимости
		}

		System::Void SaveToFile(String^ orderInfo)
		{
			try
			{
				System::IO::File::AppendAllText("orders.txt", orderInfo + "\r\n");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка сохранения заказа: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};
}