#pragma once
#include "Mapa.h"
#include "PersonajePrincipal.h"
#include "Villano.h"
namespace JuegoFinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			timer1->Interval = 130; // velocidad de actualización
			timer1->Enabled = true;
			protagonista = gcnew PersonajePrincipal(5,5,"sprites and backgrounds/Jugador1.png",3,4);
			
			// ajout : conectar a GM
			gm = gcnew GameManager();

			DoubleBuffered = true;
			this->KeyPreview = true;//permite captar la teclas. Incluso si tengo lo botones, textbox,
			this->KeyUp += gcnew KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			//antagonista = gcnew Villano(10, 20, "imagenes/Enemigo.png",this->ClientSize.Width,this->ClientSize.Height,5,4);
			contador = 0;

			// ------------ MAPAS CORREGIDOS ------------
			fondo1 = gcnew Mapa(0, 0, "sprites and backgrounds/fondo1.png",protagonista);
			fondo2 = gcnew Mapa(0, 0, "sprites and backgrounds/fondo2.png",protagonista);

			mapaActual = fondo1;

			this->ClientSize = System::Drawing::Size(
				mapaActual->WidthMapa,
				mapaActual->HeightMapa
			);
			// ------------------------------------------
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:
	private: System::Windows::Forms::Timer^ timer1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		PersonajePrincipal^ protagonista;
		array<bool>^ teclas;
		// ajout connectar a GameManager
		GameManager^ gm;


		Keys teclaActual;
	private: System::Windows::Forms::Label^ lblAgua;


		   int contador;
		   Graphics^ gr;
		   // MAPAS
		   Mapa^ fondo1;
		   Mapa^ fondo2;
	private: System::Windows::Forms::Label^ lbl_DAÑO;
		   Mapa^ mapaActual;
		   
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->lblAgua = (gcnew System::Windows::Forms::Label());
			this->lbl_DAÑO = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			gm = gcnew GameManager(); 
			teclas = gcnew array<bool>(4);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// lblAgua
			// 
			this->lblAgua->AutoSize = true;
			this->lblAgua->Location = System::Drawing::Point(50, 22);
			this->lblAgua->Name = L"lblAgua";
			this->lblAgua->Size = System::Drawing::Size(90, 16);
			this->lblAgua->TabIndex = 0;
			this->lblAgua->Text = L"FLORES:";
			this->lblAgua->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// lbl_DAÑO
			// 
			this->lbl_DAÑO->AutoSize = true;
			this->lbl_DAÑO->Location = System::Drawing::Point(157, 22);
			this->lbl_DAÑO->Name = L"lbl_DAÑO";
			this->lbl_DAÑO->Size = System::Drawing::Size(90, 16);
			this->lbl_DAÑO->TabIndex = 1;
			this->lbl_DAÑO->Text = L"DAÑO";
			this->lbl_DAÑO->Click += gcnew System::EventHandler(this, &MyForm::lbl_DAÑO_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(974, 691);
			this->Controls->Add(this->lbl_DAÑO);
			this->Controls->Add(this->lblAgua);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		protagonista->seleccionSprite(e->Graphics);
		mapaActual->mostrarMapa(e->Graphics, teclaActual);
		//antagonista->seleccionSprite(e->Graphics);
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		protagonista->mover(teclaActual);
		mapaActual->moverEnemigos();
		mapaActual->moverJugador(teclas);

		bool colMurcielago = mapaActual->colisionMurcielago();
		bool colCocodrilo = mapaActual->colisionCocodrilo();
		gm->Dano(colMurcielago, colCocodrilo);

		int indiceFlor = -1;
		bool colFlor = mapaActual->colisionFlor(indiceFlor);
		if (colFlor && indiceFlor >= 0) {
			mapaActual->flores[indiceFlor]->activo = false;
			gm->Recolectar();
		}

		lbl_DAÑO->Text = "DAÑO: " + gm->contadorDaño.ToString();
		lblAgua->Text = "FLORES: " + gm->contadorFlores.ToString();

		if (gm->verificarDerrota()) {
			timer1->Enabled = false;
			MessageBox::Show("Has Perdido");
			this->Close();
			return;
		}

		if (mapaActual == fondo1 && protagonista->getY() > this->ClientSize.Height - 60) {
			mapaActual = fondo2;
			protagonista->setY(10);
		}
		if (mapaActual == fondo2 && protagonista->getY() < 10) {
			mapaActual = fondo1;
			protagonista->setY(this->ClientSize.Height - 70);
		}

		this->Invalidate();
	}

	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		teclaActual = e->KeyCode;
	}

	private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		teclaActual = Keys::None; //"Ya no estoy presionando nada"
	}

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
		


	}
	private: System::Void lbl_DAÑO_Click(System::Object^ sender, System::EventArgs^ e) {
	}


};
}
