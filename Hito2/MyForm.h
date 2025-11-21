#pragma once

namespace Hito2 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();

            voyageurs = gcnew array<Voyageur^>(3);
            voyageurs[0] = gcnew Voyageur("ZIGER10", 219, 193, true);
            voyageurs[1] = gcnew Voyageur("KAFKAA0", 177, 202, true);
            voyageurs[2] = gcnew Voyageur("UXUS64", 178, 202, true);
        }

    protected:
        ~MyForm()
        {
            if (components)
                delete components;
        }

    private:
        System::Windows::Forms::Button^ Start;
        System::Windows::Forms::Button^ Mostrar;
        System::Windows::Forms::Button^ Salir;
        System::Windows::Forms::Label^ Title;

        ref class Voyageur {
        public:
            String^ nom;
            int code1;
            int code2;
            bool teteBrasVecteur;

            Voyageur(String^ n, int c1, int c2, bool vec) {
                nom = n;
                code1 = c1;
                code2 = c2;
                teteBrasVecteur = vec;
            }
        };

        array<Voyageur^>^ voyageurs;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
            this->Start = (gcnew System::Windows::Forms::Button());
            this->Mostrar = (gcnew System::Windows::Forms::Button());
            this->Salir = (gcnew System::Windows::Forms::Button());
            this->Title = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // Start
            // 
            this->Start->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->Start->Location = System::Drawing::Point(130, 419);
            this->Start->Name = L"Start";
            this->Start->Size = System::Drawing::Size(220, 90);
            this->Start->TabIndex = 0;
            this->Start->Text = L"Start";
            this->Start->UseVisualStyleBackColor = false;
            this->Start->Click += gcnew System::EventHandler(this, &MyForm::Start_Click);
            // 
            // Mostrar
            // 
            this->Mostrar->BackColor = System::Drawing::SystemColors::Info;
            this->Mostrar->Location = System::Drawing::Point(401, 419);
            this->Mostrar->Name = L"Mostrar";
            this->Mostrar->Size = System::Drawing::Size(230, 90);
            this->Mostrar->TabIndex = 1;
            this->Mostrar->Text = L"Sinopsis";
            this->Mostrar->UseVisualStyleBackColor = false;
            this->Mostrar->Click += gcnew System::EventHandler(this, &MyForm::Mostrar_Click);
            // 
            // Salir
            // 
            this->Salir->BackColor = System::Drawing::SystemColors::ScrollBar;
            this->Salir->Location = System::Drawing::Point(682, 419);
            this->Salir->Name = L"Salir";
            this->Salir->Size = System::Drawing::Size(230, 90);
            this->Salir->TabIndex = 2;
            this->Salir->Text = L"Salir";
            this->Salir->UseVisualStyleBackColor = false;
            this->Salir->Click += gcnew System::EventHandler(this, &MyForm::Salir_Click);
            // 
            // Title
            // 
            this->Title->AutoSize = true;
            this->Title->Location = System::Drawing::Point(320, 120);
            this->Title->Name = L"Title";
            this->Title->Size = System::Drawing::Size(126, 20);
            this->Title->TabIndex = 3;
            this->Title->Text = L"IA VS HUMANO";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
            this->ClientSize = System::Drawing::Size(1012, 627);
            this->Controls->Add(this->Title);
            this->Controls->Add(this->Salir);
            this->Controls->Add(this->Mostrar);
            this->Controls->Add(this->Start);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

        // Bouton Start
    /*private:
        System::Void Start_Click(System::Object^ sender, System::EventArgs^ e) {

            Form^ fenetreJeu = gcnew Form();
            fenetreJeu->Text = "Jeu";

            Label^ lbl = gcnew Label();
            lbl->Text = "JEU";
            lbl->Font = gcnew System::Drawing::Font("Arial", 32, FontStyle::Bold);
            lbl->AutoSize = true;
            lbl->Location = System::Drawing::Point(100, 80);

            fenetreJeu->Controls->Add(lbl);
            fenetreJeu->ClientSize = System::Drawing::Size(350, 220);
            fenetreJeu->Show();
        }*/

    private: System::Void Start_Click(System::Object^ sender, System::EventArgs^ e) {

        Form^ fenetreJeu = gcnew Form();
        fenetreJeu->Text = "Jeu";
        fenetreJeu->ClientSize = System::Drawing::Size(500, 350);

        Label^ lbl = gcnew Label();
        lbl->Text = "JEU";
        lbl->Font = gcnew System::Drawing::Font("Arial", 32, FontStyle::Bold);
        lbl->AutoSize = true;
        lbl->Location = System::Drawing::Point(180, 20);
        fenetreJeu->Controls->Add(lbl);

        PictureBox^ sprite = gcnew PictureBox();
        sprite->Image = Image::FromFile("jugador.jpg");
        sprite->SizeMode = PictureBoxSizeMode::StretchImage;
        sprite->Location = System::Drawing::Point(150, 100);
        sprite->Size = System::Drawing::Size(200, 200);

        fenetreJeu->Controls->Add(sprite);

        fenetreJeu->Show();
    }

           // Bouton Mostrar 
    private:
        System::Void Mostrar_Click(System::Object^ sender, System::EventArgs^ e) {

            Form^ fenetreInfo = gcnew Form();
            fenetreInfo->Text = "Mostrar Informaciones";
            fenetreInfo->ClientSize = System::Drawing::Size(700, 450);

            Label^ lbl = gcnew Label();
            lbl->Text = "INFOS JUEGO :\n\nUn viajero perdido cruza un espacio con tres puertas y es arrastrado a mundos que ponen a prueba la relación entre humano e IA.\nEn cada mundo, deberá recolectar flores y cristales para recuperar su humanidad y aprender nuevos conocimientos.\nAl sobrevivir, el viajero registrará sus hallazgos en un taller antes de que cada mundo colapse.\nEn la Máquina Suprema enfrentará un reino industrial oscuro; en el Puente del Futuro, un mundo donde humanos y máquinas cooperan.\nSu aliado IA solo podrá ayudar si recolecta 6 recursos para activarlo a tiempo.\nLa última prueba : descifrar la matriz binaria que decidirá si escapa… o queda atrapado para siempre.";
            lbl->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Regular);
            lbl->AutoSize = true;
            lbl->Location = System::Drawing::Point(20, 20);
            lbl->MaximumSize = System::Drawing::Size(660, 0); 

            fenetreInfo->Controls->Add(lbl);
            fenetreInfo->Show();
        }
     

        //Bouton Salir
    private:
        System::Void Salir_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    private: System::Void Title_Click(System::Object^ sender, System::EventArgs^ e) {
    }
};
}
