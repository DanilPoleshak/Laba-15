#pragma once

#include <msclr/marshal_cppstd.h>
#include <vector>
#include <string>
#include "sqlite3.h"

namespace Laba14 {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;
    using namespace System::IO;
    using namespace System::Text;

    public ref class Produkt : public Form
    {
    public:
        Produkt(void)
        {
            InitializeComponent();
            InitializeDatabase();
            LoadProduktDataFromDB();
            this->FormClosed += gcnew FormClosedEventHandler(this, &Produkt::OnFormClosed);
        }

        // ========== ПУБЛИЧНЫЕ МЕТОДЫ ДЛЯ Delivery ==========
        List<String^>^ GetAvailableProductsWithQuantity()
        {
            List<String^>^ products = gcnew List<String^>();
            for each (ProductData ^ product in productList)
            {
                if (product->Quantity > 0)
                {
                    products->Add(String::Format("{0} ({1:F2} руб) - {2} шт.",
                        product->Name, product->Price, product->Quantity));
                }
            }
            return products;
        }

        bool DecreaseProductQuantity(String^ productName, int quantity)
        {
            if (String::IsNullOrWhiteSpace(productName) || quantity <= 0)
                return false;

            try
            {
                int currentQty = GetProductQuantity(productName);
                if (currentQty < quantity)
                    return false;

                UpdateProductQuantity(productName, -quantity);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        int GetProductQuantity(String^ productName)
        {
            if (String::IsNullOrWhiteSpace(productName))
                return 0;

            for each (ProductData ^ product in productList)
            {
                if (product->Name->Equals(productName, StringComparison::OrdinalIgnoreCase))
                {
                    return product->Quantity;
                }
            }
            return 0;
        }

        void UpdateProductQuantity(String^ productName, int quantityChange)
        {
            try {
                for each (ProductData ^ product in productList)
                {
                    if (product->Name == productName)
                    {
                        product->Quantity += quantityChange;
                        if (product->Quantity < 0) product->Quantity = 0;
                        product->Total = product->Quantity * product->Price;
                        DisplayAllProducts();
                        UpdateSummary();
                        SaveProductToDB(product->Id, product->Name, product->Quantity, product->Price);
                        return;
                    }
                }
                if (quantityChange > 0) {
                    int newId = GetNextProductId();
                    AddInventoryItem(newId, productName, quantityChange, 0.0);
                    MessageBox::Show(String::Format(
                        "Товар '{0}' не найден и добавлен с количеством {1} шт.\nЦена = 0. Отредактируйте на складе!",
                        productName, quantityChange), "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                }
                else {
                    throw gcnew Exception("Товар '" + productName + "' не найден");
                }
            }
            catch (Exception^ ex) {
                throw gcnew Exception("Ошибка при обновлении товара '" + productName + "': " + ex->Message);
            }
        }

    protected:
        ~Produkt()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        // === Компоненты ===
        DataGridView^ dataGridViewInventory;
        Label^ labelTitle;
        Button^ buttonClose;
        Label^ labelTotalItems;
        Label^ labelTotalValue;
        GroupBox^ groupBoxAddProduct;
        Label^ labelProductName;
        TextBox^ textBoxProductName;
        Label^ labelQuantity;
        TextBox^ textBoxQuantity;
        Label^ labelPrice;
        TextBox^ textBoxPrice;
        Button^ buttonAddProduct;
        Button^ buttonEditProduct;
        Button^ buttonCancelEdit;
        Button^ buttonImportCSV;
        ToolTip^ toolTip;

        // === Структура товара ===
        ref struct ProductData
        {
            int Id;
            String^ Name;
            int Quantity;
            double Price;
            double Total;
            ProductData(int id, String^ name, int quantity, double price)
            {
                Id = id;
                Name = name;
                Quantity = quantity;
                Price = price;
                Total = quantity * price;
            }
        };

        // === Поля ===
        List<ProductData^>^ productList;
        int nextProductId = 1;
        bool isEditing = false;
        int editingProductId = -1;
        IContainer^ components;

        // === Вспомогательный метод: путь к БД на рабочем столе ===
        String^ GetDatabasePath()
        {
            return System::IO::Path::Combine(
                Environment::GetFolderPath(Environment::SpecialFolder::Desktop),
                "warehouse.db"
            );
        }

        // === Получение следующего ID ===
        int GetNextProductId()
        {
            sqlite3* db;
            String^ dbPath = GetDatabasePath();
            pin_ptr<const wchar_t> wpath = PtrToStringChars(dbPath);
            int rc = sqlite3_open16(wpath, &db);
            if (rc) return 1;

            const char* sql = "SELECT MAX(Id) FROM Products;";
            sqlite3_stmt* stmt;
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
            int maxId = 0;
            if (rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
                maxId = sqlite3_column_int(stmt, 0);
            }
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return maxId + 1;
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            this->labelTitle = gcnew Label();
            this->dataGridViewInventory = gcnew DataGridView();
            this->labelTotalItems = gcnew Label();
            this->labelTotalValue = gcnew Label();
            this->buttonClose = gcnew Button();
            this->groupBoxAddProduct = gcnew GroupBox();
            this->labelProductName = gcnew Label();
            this->textBoxProductName = gcnew TextBox();
            this->labelQuantity = gcnew Label();
            this->textBoxQuantity = gcnew TextBox();
            this->labelPrice = gcnew Label();
            this->textBoxPrice = gcnew TextBox();
            this->buttonAddProduct = gcnew Button();
            this->buttonEditProduct = gcnew Button();
            this->buttonCancelEdit = gcnew Button();
            this->buttonImportCSV = gcnew Button();
            this->toolTip = gcnew ToolTip(this->components);

            // === Настройка labelTitle ===
            this->labelTitle->Text = "Склад товаров";
            this->labelTitle->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 14, FontStyle::Bold);
            this->labelTitle->AutoSize = true;
            this->labelTitle->Location = Point(10, 10);

            // === Настройка dataGridViewInventory ===
            this->dataGridViewInventory->Location = Point(10, 40);
            this->dataGridViewInventory->Size = System::Drawing::Size(700, 250);
            this->dataGridViewInventory->ReadOnly = true;
            this->dataGridViewInventory->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dataGridViewInventory->AllowUserToAddRows = false;
            this->dataGridViewInventory->AllowUserToDeleteRows = false;
            this->dataGridViewInventory->MultiSelect = false;
            this->dataGridViewInventory->TabIndex = 0;

            // === Итоговые метки ===
            this->labelTotalItems->Location = Point(10, 300);
            this->labelTotalItems->AutoSize = true;
            this->labelTotalItems->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 9, FontStyle::Bold);

            this->labelTotalValue->Location = Point(10, 325);
            this->labelTotalValue->AutoSize = true;
            this->labelTotalValue->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 9, FontStyle::Bold);

            // === Группа добавления товара ===
            this->groupBoxAddProduct->Text = "Добавить новый товар";
            this->groupBoxAddProduct->Location = Point(10, 360);
            this->groupBoxAddProduct->Size = System::Drawing::Size(700, 120);
            this->groupBoxAddProduct->TabIndex = 1;

            this->labelProductName->Text = "Наименование:";
            this->labelProductName->Location = Point(10, 20);
            this->labelProductName->AutoSize = true;

            this->textBoxProductName->Location = Point(120, 18);
            this->textBoxProductName->Size = System::Drawing::Size(200, 22);
            this->textBoxProductName->TabIndex = 2;

            this->labelQuantity->Text = "Количество:";
            this->labelQuantity->Location = Point(10, 50);
            this->labelQuantity->AutoSize = true;

            this->textBoxQuantity->Location = Point(120, 48);
            this->textBoxQuantity->Size = System::Drawing::Size(80, 22);
            this->textBoxQuantity->TabIndex = 3;

            this->labelPrice->Text = "Цена:";
            this->labelPrice->Location = Point(220, 50);
            this->labelPrice->AutoSize = true;

            this->textBoxPrice->Location = Point(260, 48);
            this->textBoxPrice->Size = System::Drawing::Size(80, 22);
            this->textBoxPrice->TabIndex = 4;

            // === Цветные кнопки ===
            this->buttonAddProduct->Text = "Добавить";
            this->buttonAddProduct->Location = Point(600, 15);
            this->buttonAddProduct->Size = System::Drawing::Size(80, 25);
            this->buttonAddProduct->TabIndex = 5;
            this->buttonAddProduct->Click += gcnew EventHandler(this, &Produkt::buttonAddProduct_Click);
            this->buttonAddProduct->BackColor = System::Drawing::Color::DodgerBlue;
            this->buttonAddProduct->ForeColor = System::Drawing::Color::White;
            this->buttonAddProduct->FlatStyle = FlatStyle::Flat;

            this->buttonEditProduct->Text = "Сохранить";
            this->buttonEditProduct->Location = Point(600, 45);
            this->buttonEditProduct->Size = System::Drawing::Size(80, 25);
            this->buttonEditProduct->Enabled = false;
            this->buttonEditProduct->TabIndex = 6;
            this->buttonEditProduct->Click += gcnew EventHandler(this, &Produkt::buttonEditProduct_Click);
            this->buttonEditProduct->BackColor = System::Drawing::Color::LightGreen;
            this->buttonEditProduct->ForeColor = System::Drawing::Color::Black;
            this->buttonEditProduct->FlatStyle = FlatStyle::Flat;

            this->buttonCancelEdit->Text = "Отменить";
            this->buttonCancelEdit->Location = Point(500, 45);
            this->buttonCancelEdit->Size = System::Drawing::Size(80, 25);
            this->buttonCancelEdit->Enabled = false;
            this->buttonCancelEdit->TabIndex = 7;
            this->buttonCancelEdit->Click += gcnew EventHandler(this, &Produkt::buttonCancelEdit_Click);
            this->buttonCancelEdit->BackColor = System::Drawing::Color::Tomato;
            this->buttonCancelEdit->ForeColor = System::Drawing::Color::White;
            this->buttonCancelEdit->FlatStyle = FlatStyle::Flat;

            this->buttonImportCSV->Text = "Импорт из Excel (CSV)";
            this->buttonImportCSV->Location = Point(350, 80);
            this->buttonImportCSV->Size = System::Drawing::Size(180, 25);
            this->buttonImportCSV->TabIndex = 8;
            this->buttonImportCSV->Click += gcnew EventHandler(this, &Produkt::buttonImportCSV_Click);

            array<Control^>^ groupControls = {
                this->labelProductName, this->textBoxProductName,
                this->labelQuantity, this->textBoxQuantity,
                this->labelPrice, this->textBoxPrice,
                this->buttonAddProduct, this->buttonEditProduct,
                this->buttonCancelEdit, this->buttonImportCSV
            };
            this->groupBoxAddProduct->Controls->AddRange(groupControls);

            // === Кнопка закрытия ===
            this->buttonClose->Text = "Закрыть";
            this->buttonClose->Location = Point(570, 490);
            this->buttonClose->Size = System::Drawing::Size(120, 30);
            this->buttonClose->TabIndex = 9;
            this->buttonClose->Click += gcnew EventHandler(this, &Produkt::buttonClose_Click);

            // === События ===
            this->dataGridViewInventory->CellDoubleClick += gcnew DataGridViewCellEventHandler(this, &Produkt::dataGridViewInventory_CellDoubleClick);
            this->dataGridViewInventory->KeyDown += gcnew KeyEventHandler(this, &Produkt::dataGridViewInventory_KeyDown);
            this->textBoxQuantity->KeyPress += gcnew KeyPressEventHandler(this, &Produkt::textBoxQuantity_KeyPress);
            this->textBoxPrice->KeyPress += gcnew KeyPressEventHandler(this, &Produkt::textBoxPrice_KeyPress);
            this->textBoxQuantity->Leave += gcnew EventHandler(this, &Produkt::textBoxQuantity_Leave);
            this->textBoxPrice->Leave += gcnew EventHandler(this, &Produkt::textBoxPrice_Leave);

            // === Добавление на форму ===
            array<Control^>^ mainControls = {
                this->labelTitle,
                this->dataGridViewInventory,
                this->labelTotalItems,
                this->labelTotalValue,
                this->groupBoxAddProduct,
                this->buttonClose
            };
            this->Controls->AddRange(mainControls);

            // === Настройка формы ===
            this->AutoSize = true;
            this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
            this->MaximizeBox = false;
            this->MinimizeBox = true;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->MinimumSize = System::Drawing::Size(720, 530);
            this->BackColor = System::Drawing::Color::PowderBlue;
            this->Load += gcnew EventHandler(this, &Produkt::Produkt_Load_1);
        }
#pragma endregion

    private:
        void InitializeDatabase()
        {
            sqlite3* db;
            String^ dbPath = GetDatabasePath();
            pin_ptr<const wchar_t> wpath = PtrToStringChars(dbPath);
            int rc = sqlite3_open16(wpath, &db);
            if (rc) {
                MessageBox::Show("Ошибка открытия БД: " + gcnew String(sqlite3_errmsg(db)),
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Убрали AUTOINCREMENT!
            const char* sql = R"(
                CREATE TABLE IF NOT EXISTS Products (
                    Id INTEGER PRIMARY KEY,
                    Name TEXT NOT NULL UNIQUE,
                    Quantity INTEGER NOT NULL CHECK(Quantity >= 0),
                    Price REAL NOT NULL CHECK(Price >= 0)
                );
            )";

            char* errMsg = 0;
            rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
            if (rc != SQLITE_OK) {
                String^ msg = gcnew String(errMsg);
                MessageBox::Show("Ошибка SQL: " + msg, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                sqlite3_free(errMsg);
            }
            sqlite3_close(db);
        }

        void LoadProduktDataFromDB()
        {
            productList = gcnew List<ProductData^>();
            dataGridViewInventory->Columns->Clear();
            dataGridViewInventory->Columns->Add("ID", "ID");
            dataGridViewInventory->Columns->Add("Name", "Наименование");
            dataGridViewInventory->Columns->Add("Quantity", "Количество");
            dataGridViewInventory->Columns->Add("Price", "Цена (руб)");
            dataGridViewInventory->Columns->Add("Total", "Стоимость (руб)");

            dataGridViewInventory->Columns["Name"]->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
            dataGridViewInventory->Columns["ID"]->Width = 50;
            dataGridViewInventory->Columns["Quantity"]->Width = 80;
            dataGridViewInventory->Columns["Price"]->Width = 100;
            dataGridViewInventory->Columns["Total"]->Width = 120;

            sqlite3* db;
            String^ dbPath = GetDatabasePath();
            pin_ptr<const wchar_t> wpath = PtrToStringChars(dbPath);
            int rc = sqlite3_open16(wpath, &db);
            if (rc) {
                MessageBox::Show("Не удалось подключиться к базе данных. Будут использованы тестовые данные.",
                    "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                AddTestProducts();
                DisplayAllProducts();
                UpdateSummary();
                return;
            }

            const char* sql = "SELECT Id, Name, Quantity, Price FROM Products ORDER BY Id;";
            sqlite3_stmt* stmt;
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                MessageBox::Show("Ошибка запроса к БД. Загружены тестовые данные.",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                AddTestProducts();
                DisplayAllProducts();
                UpdateSummary();
                return;
            }

            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                const unsigned char* name = sqlite3_column_text(stmt, 1);
                int qty = sqlite3_column_int(stmt, 2);
                double price = sqlite3_column_double(stmt, 3);
                if (name) {
                    String^ nameStr = gcnew String(reinterpret_cast<const char*>(name));
                    AddProductToList(id, nameStr, qty, price);
                }
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            if (productList->Count == 0) {
                AddTestProducts();
            }

            // Обновляем nextProductId как MAX(Id) + 1
            nextProductId = 1;
            for each (ProductData ^ p in productList)
                if (p->Id >= nextProductId) nextProductId = p->Id + 1;

            DisplayAllProducts();
            UpdateSummary();
        }

        void SaveProductToDB(int id, String^ name, int quantity, double price)
        {
            sqlite3* db;
            String^ dbPath = GetDatabasePath();
            pin_ptr<const wchar_t> wpath = PtrToStringChars(dbPath);
            int rc = sqlite3_open16(wpath, &db);
            if (rc) return;

            const char* sql = "REPLACE INTO Products (Id, Name, Quantity, Price) VALUES (?, ?, ?, ?);";
            sqlite3_stmt* stmt;
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
            if (rc == SQLITE_OK) {
                sqlite3_bind_int(stmt, 1, id);
                pin_ptr<const wchar_t> wname = PtrToStringChars(name);
                sqlite3_bind_text16(stmt, 2, wname, -1, SQLITE_TRANSIENT);
                sqlite3_bind_int(stmt, 3, quantity);
                sqlite3_bind_double(stmt, 4, price);
                sqlite3_step(stmt);
            }
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }

        void AddTestProducts()
        {
            AddProductToList(1, "Ноутбук HP Pavilion", 15, 55000);
            AddProductToList(2, "Смартфон Samsung A54", 42, 30000);
            AddProductToList(3, "Наушники Sony WH-1000XM5", 28, 3500);
            AddProductToList(4, "Клавиатура Logitech", 65, 4600);
            AddProductToList(5, "Мышь беспроводная", 120, 1900);
            AddProductToList(6, "Монитор 27\" 4K", 12, 4300);
            AddProductToList(7, "Внешний жесткий диск 2TB", 35, 7600);
            AddProductToList(8, "Роутер Wi-Fi", 40, 9000);
            AddProductToList(9, "Пауэрбанк 20000 mAh", 85, 2500);
            AddProductToList(10, "USB-C кабель", 200, 900);

            // Обновляем nextProductId после тестовых данных
            nextProductId = 11;
        }

        void AddProductToList(int id, String^ name, int quantity, double price)
        {
            ProductData^ newProduct = gcnew ProductData(id, name, quantity, price);
            productList->Add(newProduct);
        }

        void DisplayAllProducts()
        {
            dataGridViewInventory->Rows->Clear();
            for each (ProductData ^ product in productList)
            {
                dataGridViewInventory->Rows->Add(
                    product->Id.ToString(),
                    product->Name,
                    product->Quantity.ToString(),
                    product->Price.ToString("F2"),
                    product->Total.ToString("F2")
                );
            }
        }

        void AddInventoryItem(int id, String^ name, int quantity, double price)
        {
            AddProductToList(id, name, quantity, price);
            SaveProductToDB(id, name, quantity, price);
            DisplayAllProducts();
            UpdateSummary();
        }

        void UpdateInventoryItem(int id, String^ name, int quantity, double price)
        {
            for each (ProductData ^ product in productList)
            {
                if (product->Id == id)
                {
                    product->Name = name;
                    product->Quantity = quantity;
                    product->Price = price;
                    product->Total = quantity * price;
                    break;
                }
            }
            SaveProductToDB(id, name, quantity, price);
            DisplayAllProducts();
            UpdateSummary();
        }

        void UpdateSummary()
        {
            int totalItems = 0;
            double totalValue = 0;
            for each (ProductData ^ product in productList)
            {
                totalItems += product->Quantity;
                totalValue += product->Total;
            }
            labelTotalItems->Text = String::Format("Всего товаров: {0} шт.", totalItems);
            labelTotalValue->Text = String::Format("Общая стоимость: {0:F2} руб", totalValue);
        }

        bool ValidateProductData(String^% productName, int% quantity, double% price)
        {
            if (String::IsNullOrWhiteSpace(textBoxProductName->Text))
            {
                MessageBox::Show("Введите наименование", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            if (!Int32::TryParse(textBoxQuantity->Text, quantity) || quantity < 1 || quantity > 100000)
            {
                MessageBox::Show("Количество должно быть от 1 до 100 000 шт.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return false;
            }

            if (!Double::TryParse(textBoxPrice->Text, price) || price < 1.0 || price > 1000000.0)
            {
                MessageBox::Show("Цена должна быть от 1.00 до 1 000 000.00 руб.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return false;
            }

            productName = textBoxProductName->Text->Trim();
            return true;
        }

        void EnableEditMode(int productId)
        {
            for each (ProductData ^ p in productList) {
                if (p->Id == productId) {
                    isEditing = true; editingProductId = productId;
                    textBoxProductName->Text = p->Name;
                    textBoxQuantity->Text = p->Quantity.ToString();
                    textBoxPrice->Text = p->Price.ToString("F2");
                    groupBoxAddProduct->Text = "Редактирование товара (ID: " + productId + ")";
                    buttonAddProduct->Enabled = false;
                    buttonEditProduct->Enabled = true;
                    buttonCancelEdit->Enabled = true;
                    return;
                }
            }
        }

        void DisableEditMode()
        {
            isEditing = false;
            editingProductId = -1;
            textBoxProductName->Clear();
            textBoxQuantity->Clear();
            textBoxPrice->Clear();
            groupBoxAddProduct->Text = "Добавить новый товар";
            buttonAddProduct->Enabled = true;
            buttonEditProduct->Enabled = false;
            buttonCancelEdit->Enabled = false;
        }

        // === ОБРАБОТЧИКИ СОБЫТИЙ ===

        System::Void buttonAddProduct_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ name; int qty; double price;
            if (!ValidateProductData(name, qty, price)) return;

            // Проверка на дубликат
            for each (ProductData ^ p in productList)
            {
                if (p->Name->Equals(name, StringComparison::OrdinalIgnoreCase))
                {
                    MessageBox::Show("Товар с таким наименованием уже существует!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
            }

            int newId = GetNextProductId();
            AddInventoryItem(newId, name, qty, price);
            nextProductId = newId + 1; // Обновляем глобальный счётчик
            MessageBox::Show("Товар добавлен в базу данных!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        System::Void buttonEditProduct_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (!isEditing) return;
            String^ name; int qty; double price;
            if (!ValidateProductData(name, qty, price)) return;

            // Проверка на дубликат (кроме текущего товара)
            for each (ProductData ^ p in productList)
            {
                if (p->Id != editingProductId && p->Name->Equals(name, StringComparison::OrdinalIgnoreCase))
                {
                    MessageBox::Show("Товар с таким наименованием уже существует!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
            }

            UpdateInventoryItem(editingProductId, name, qty, price);
            DisableEditMode();
            MessageBox::Show("Товар обновлён в базе данных!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        System::Void buttonImportCSV_Click(System::Object^ sender, System::EventArgs^ e)
        {
            OpenFileDialog^ dlg = gcnew OpenFileDialog();
            dlg->Filter = "CSV файлы (*.csv)|*.csv|Все файлы (*.*)|*.*";
            if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            StreamReader^ reader = nullptr;
            sqlite3* db = nullptr;
            sqlite3_stmt* stmtSelect = nullptr;
            sqlite3_stmt* stmtUpdate = nullptr;
            sqlite3_stmt* stmtInsert = nullptr;
            try {
                reader = gcnew StreamReader(dlg->FileName, Encoding::GetEncoding(1251));
                reader->ReadLine(); // skip header

                String^ dbPath = GetDatabasePath();
                pin_ptr<const wchar_t> wpath = PtrToStringChars(dbPath);
                int rc = sqlite3_open16(wpath, &db);
                if (rc) throw gcnew Exception("БД недоступна");

                const char* sqlSelect = "SELECT Id FROM Products WHERE Name = ?";
                const char* sqlUpdate = "UPDATE Products SET Quantity = ?, Price = ? WHERE Name = ?";
                const char* sqlInsert = "INSERT INTO Products (Id, Name, Quantity, Price) VALUES (?, ?, ?, ?)";

                rc = sqlite3_prepare_v2(db, sqlSelect, -1, &stmtSelect, 0);
                if (rc != SQLITE_OK) throw gcnew Exception("Ошибка подготовки SELECT");
                rc = sqlite3_prepare_v2(db, sqlUpdate, -1, &stmtUpdate, 0);
                if (rc != SQLITE_OK) throw gcnew Exception("Ошибка подготовки UPDATE");
                rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmtInsert, 0);
                if (rc != SQLITE_OK) throw gcnew Exception("Ошибка подготовки INSERT");

                int count = 0;
                String^ line;
                while ((line = reader->ReadLine()) != nullptr) {
                    line = line->Trim();
                    if (line->Length == 0) continue;
                    array<String^>^ parts = line->Split(L',');
                    if (parts->Length < 3) continue;

                    String^ name = parts[0]->Trim(L'\"', L' ');
                    int qty; double price;
                    if (!Int32::TryParse(parts[1]->Trim(L'\"', L' '), qty) ||
                        !Double::TryParse(parts[2]->Trim(L'\"', L' '), price)) continue;
                    if (qty <= 0 || price <= 0) continue;

                    pin_ptr<const wchar_t> wname = PtrToStringChars(name);

                    sqlite3_bind_text16(stmtSelect, 1, wname, -1, SQLITE_TRANSIENT);
                    if (sqlite3_step(stmtSelect) == SQLITE_ROW) {
                        // Обновляем существующий — ID не меняем
                        sqlite3_reset(stmtUpdate);
                        sqlite3_bind_int(stmtUpdate, 1, qty);
                        sqlite3_bind_double(stmtUpdate, 2, price);
                        sqlite3_bind_text16(stmtUpdate, 3, wname, -1, SQLITE_TRANSIENT);
                        sqlite3_step(stmtUpdate);
                    }
                    else {
                        // Вставляем новый — берём следующий ID
                        int newId = GetNextProductId();
                        sqlite3_reset(stmtInsert);
                        sqlite3_bind_int(stmtInsert, 1, newId);
                        sqlite3_bind_text16(stmtInsert, 2, wname, -1, SQLITE_TRANSIENT);
                        sqlite3_bind_int(stmtInsert, 3, qty);
                        sqlite3_bind_double(stmtInsert, 4, price);
                        sqlite3_step(stmtInsert);
                        // Обновляем nextProductId
                        nextProductId = newId + 1;
                    }
                    sqlite3_reset(stmtSelect);
                    count++;
                }

                MessageBox::Show(String::Format("Импорт завершён! Обработано: {0} товаров", count),
                    "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                LoadProduktDataFromDB();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (reader) delete reader;
                if (stmtSelect) sqlite3_finalize(stmtSelect);
                if (stmtUpdate) sqlite3_finalize(stmtUpdate);
                if (stmtInsert) sqlite3_finalize(stmtInsert);
                if (db) sqlite3_close(db);
            }
        }

        System::Void buttonClose_Click(System::Object^ sender, System::EventArgs^ e) { this->Close(); }

        System::Void dataGridViewInventory_CellDoubleClick(System::Object^ sender, DataGridViewCellEventArgs^ e) {
            if (e->RowIndex >= 0) {
                String^ idStr = dataGridViewInventory->Rows[e->RowIndex]->Cells[0]->Value->ToString();
                int id; if (Int32::TryParse(idStr, id)) EnableEditMode(id);
            }
        }

        System::Void dataGridViewInventory_KeyDown(System::Object^ sender, KeyEventArgs^ e)
        {
            if (e->KeyCode == System::Windows::Forms::Keys::Delete && dataGridViewInventory->SelectedRows->Count > 0)
            {
                if (MessageBox::Show("Удалить выбранный товар?", "Подтверждение",
                    MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
                {
                    int id = Convert::ToInt32(dataGridViewInventory->SelectedRows[0]->Cells[0]->Value);

                    for (int i = productList->Count - 1; i >= 0; i--)
                    {
                        if (productList[i]->Id == id)
                        {
                            productList->RemoveAt(i);
                            break;
                        }
                    }

                    sqlite3* db;
                    String^ dbPath = GetDatabasePath();
                    pin_ptr<const wchar_t> wpath = PtrToStringChars(dbPath);
                    int rc = sqlite3_open16(wpath, &db);
                    if (rc == SQLITE_OK) {
                        const char* sql = "DELETE FROM Products WHERE Id = ?;";
                        sqlite3_stmt* stmt;
                        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
                        if (rc == SQLITE_OK) {
                            sqlite3_bind_int(stmt, 1, id);
                            sqlite3_step(stmt);
                            sqlite3_finalize(stmt);
                        }
                        sqlite3_close(db);
                    }

                    LoadProduktDataFromDB();
                }
            }
        }

        System::Void textBoxQuantity_KeyPress(System::Object^ sender, KeyPressEventArgs^ e) {
            if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar)) {
                e->Handled = true;
            }
        }

        System::Void textBoxPrice_KeyPress(System::Object^ sender, KeyPressEventArgs^ e) {
            if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && e->KeyChar != '.' && e->KeyChar != ',') {
                e->Handled = true;
            }
            if (e->KeyChar == ',') e->KeyChar = '.';
        }

        System::Void textBoxQuantity_Leave(System::Object^ sender, System::EventArgs^ e)
        {
            int qty;
            if (!Int32::TryParse(textBoxQuantity->Text, qty) || qty < 1)
            {
                MessageBox::Show("Количество должно быть целым числом от 1 до 100 000.", "Ошибка ввода",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                textBoxQuantity->Text = "1";
            }
            else if (qty > 100000)
            {
                MessageBox::Show("Максимальное количество — 100 000 шт.", "Ошибка ввода",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                textBoxQuantity->Text = "100000";
            }
            else
            {
                textBoxQuantity->Text = qty.ToString();
            }
        }

        System::Void textBoxPrice_Leave(System::Object^ sender, System::EventArgs^ e)
        {
            double price;
            if (!Double::TryParse(textBoxPrice->Text, price) || price < 1.0)
            {
                MessageBox::Show("Цена должна быть от 1.00 руб.", "Ошибка ввода",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                textBoxPrice->Text = "1.00";
            }
            else if (price > 1000000.0)
            {
                MessageBox::Show("Максимальная цена — 1 000 000.00 руб.", "Ошибка ввода",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                textBoxPrice->Text = "1000000.00";
            }
            else
            {
                textBoxPrice->Text = price.ToString("F2");
            }
        }

        System::Void buttonCancelEdit_Click(System::Object^ sender, System::EventArgs^ e) {
            DisableEditMode();
        }

        System::Void Produkt_Load_1(System::Object^ sender, System::EventArgs^ e) {}

        System::Void OnFormClosed(System::Object^ sender, FormClosedEventArgs^ e)
        {
            delete this;
        }
    };
}