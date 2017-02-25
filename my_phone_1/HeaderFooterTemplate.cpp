//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "HeaderFooterTemplate.h"
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
THeaderFooterForm *HeaderFooterForm;
//---------------------------------------------------------------------------
__fastcall THeaderFooterForm::THeaderFooterForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THeaderFooterForm::Button1Click(TObject *Sender)
{
	this->Label1->Text = "Hello!";
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button2Click(TObject *Sender)
{
	Bluetooth1->Enabled = true;
	this->Memo1->Lines->Add("Bluetooth1->Enabled");
	this->Memo1->Lines->Add(Bluetooth1->Enabled);
	this->Memo1->Lines->Add("Bluetooth1->StateConnected");
	this->Memo1->Lines->Add(Bluetooth1->StateConnected);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button3Click(TObject *Sender)
{
	//this->Bluetooth1->PairedDevices()->Count;

	this->Memo1->Lines->Add("paired devices: " +
						IntToStr(this->Bluetooth1->PairedDevices()->Count));
	this->Memo1->Lines->Add("++++++++++++++++");
	for( char i = 0; i < this->Bluetooth1->PairedDevices()->Count; i++)
	{

		TBluetoothDevice * dev = this->Bluetooth1->PairedDevices()->First() + i;


		this->Memo1->Lines->Add("device name");
		this->Memo1->Lines->Add( dev->DeviceName );

		if (dev->DeviceName == "HC-05")
		{
			this->Memo1->Lines->Add("HC-05 FOUNDED!!!");

			this->Memo1->Lines->Add("         ");
			this->Memo1->Lines->Add("services count: " +
				IntToStr(dev->GetServices()->Count)
			);


			TBluetoothService serv = dev->GetServices()->First();
			this->Memo1->Lines->Add(
				serv.Name
			);

			//******************************************************



			//******************************************************
			this->Memo1->Lines->Add("         ");
			this->Memo1->Lines->Add("try connected...");
			this->Memo1->Lines->Add("         ");
			my_sock =  dev->CreateClientSocket(
				serv.UUID,
				true);

			my_sock->Connect();


			if (my_sock->Connected) {
				this->Memo1->Lines->Add("CONNECTED!!!");
			}else{
				this->Memo1->Lines->Add("connection False");
			}
		}


	}
	//this->Bluetooth1->DiscoverDevices(1000);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Bluetooth1DiscoveryEnd(TObject * const Sender,
		  TBluetoothDeviceList * const ADeviceList)
{
	this->Memo1->Lines->Add("discovery ended");
	this->Memo1->Lines->Add("founded: " +
						IntToStr(this->Bluetooth1->LastDiscoveredDevices->Count));
	this->Memo1->Lines->Add("------------");

	for( char i = 0; i < this->Bluetooth1->LastDiscoveredDevices->Count; i++){

		TBluetoothDevice * dev = this->Bluetooth1->LastDiscoveredDevices->First() + i;


		this->Memo1->Lines->Add("device name");
		this->Memo1->Lines->Add( dev->DeviceName );

		if (dev->DeviceName == "HC-05") {
			this->Memo1->Lines->Add("HC-05 FOUNDED!!!");
		}

		this->Memo1->Lines->Add("is pared");
		this->Memo1->Lines->Add(
		dev->IsPaired
		);
		this->Memo1->Lines->Add("         ");
		this->Memo1->Lines->Add("services count: " +
			IntToStr(dev->GetServices()->Count)
		);

		for (char i = 0; i < dev->GetServices()->Count; i++) {
			TBluetoothService serv = dev->GetServices()->operator[](i);
			this->Memo1->Lines->Add(
				serv.Name
			);
		}


	}
}
//---------------------------------------------------------------------------


void __fastcall THeaderFooterForm::Button4Click(TObject *Sender)
{
	String str = "sd";
	this->my_sock->SendData(str.BytesOf());
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button5Click(TObject *Sender)
{
	DynamicArray<System::Byte> cmd;
	cmd.set_length(1);
	cmd[0] = 0x05;
	this->my_sock->SendData(cmd);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button7Click(TObject *Sender)
{
	DynamicArray<System::Byte> cmd;
	cmd.set_length(1);
	cmd[0] = 0x07;
	this->my_sock->SendData(cmd);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button6Click(TObject *Sender)
{
	DynamicArray<System::Byte> cmd;
	cmd.set_length(1);
	cmd[0] = 0x06;
	this->my_sock->SendData(cmd);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button8Click(TObject *Sender)
{
	DynamicArray<System::Byte> cmd;
	cmd.set_length(1);
	cmd[0] = 0x08;
	this->my_sock->SendData(cmd);
}
//---------------------------------------------------------------------------

