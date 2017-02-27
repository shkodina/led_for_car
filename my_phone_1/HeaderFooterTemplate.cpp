//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "HeaderFooterTemplate.h"
#include <vector>
#include "my_cmd_prot.h"
#include "matrix_defs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
THeaderFooterForm *HeaderFooterForm;
//---------------------------------------------------------------------------
void THeaderFooterForm::send_command(char in_cmd)
{
	DynamicArray<System::Byte> cmd;
	cmd.set_length(1);
	cmd[0] = in_cmd;
	try{
	this->my_sock->SendData(cmd);
	}catch(...){
		this->Memo1->Lines->Add("Exception while SendData() - Reboot Device");
		this->Memo1->GoToTextEnd();
		this->TabControl1->ActiveTab = this->TabItem3;
	}
	return;
}
//---------------------------------------------------------------------------
void THeaderFooterForm::send_command(char in_cmd, char data)
{
	DynamicArray<System::Byte> cmd;
	cmd.set_length(1);
	cmd[0] = in_cmd;

	try{
	this->my_sock->SendData(cmd);
	}catch(...){
		this->Memo1->Lines->Add("Exception while SendData() - Reboot Device");
		this->Memo1->GoToTextEnd();
		this->TabControl1->ActiveTab = this->TabItem3;
	}

	cmd[0] = data;

	try{
	this->my_sock->SendData(cmd);
	}catch(...){
		this->Memo1->Lines->Add("Exception while SendData() - Reboot Device");
		this->Memo1->GoToTextEnd();
		this->TabControl1->ActiveTab = this->TabItem3;
	}

	return;

}
//---------------------------------------------------------------------------
void THeaderFooterForm::send_str(String str, char num_of_str)
{
	DynamicArray<System::Byte> cmd;

	cmd.set_length(str.Length() + 2);

	cmd[0] = num_of_str ? SET_STR1 : SET_STR0;

	for (int i = 0; i < str.Length(); i++) {
		cmd[i+1] = str[i];
	}

	cmd[cmd.Length-1] = STR_STOP;

	DynamicArray<System::Byte> bb;
	bb.set_length(1);
	try{
		for (int i = 0; i < cmd.get_length(); i++) {
			bb[0] = cmd[i];
			try{
				this->my_sock->SendData(bb);
			}catch(...){
				this->Memo1->Lines->Add("Exception while SendData(bb) - Reboot Device");
				this->Memo1->GoToTextEnd();
				this->TabControl1->ActiveTab = this->TabItem3;
			}
		}
		//this->my_sock->SendData(cmd);
	}catch(...){
		this->Memo1->Lines->Add("Exception while SendData(cmd) - Reboot Device");
		this->Memo1->GoToTextEnd();
		this->TabControl1->ActiveTab = this->TabItem3;
	}
	return;
}
//---------------------------------------------------------------------------
__fastcall THeaderFooterForm::THeaderFooterForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THeaderFooterForm::Button1Click(TObject *Sender)
{
	send_command(CLEAR0ROW);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button2Click(TObject *Sender)
{
	Bluetooth1->Enabled = true;
	this->Memo1->Lines->Add("Bluetooth1->Enabled");
	this->Memo1->Lines->Add(Bluetooth1->Enabled);
	this->Memo1->Lines->Add("Bluetooth1->StateConnected");
	this->Memo1->Lines->Add(Bluetooth1->StateConnected);
    this->Memo1->GoToTextEnd();
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


			 try{
				//******************************************************
				this->Memo1->Lines->Add("         ");
				this->Memo1->Lines->Add("trying connected...");
				this->Memo1->Lines->Add("         ");
				my_sock =  dev->CreateClientSocket(
					serv.UUID,
					true);

				my_sock->Connect();

				this->Memo1->Lines->Add("Connected.");
			}catch(...){
				this->Memo1->Lines->Add("Exception!");
				this->Memo1->Lines->Add("Reset Bluetooth and try again.");
			}
		}
	}
	this->Memo1->GoToTextEnd();
	//this->Bluetooth1->DiscoverDevices(1000);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Bluetooth1DiscoveryEnd(TObject * const Sender,
		  TBluetoothDeviceList * const ADeviceList)
{
	;
}
//---------------------------------------------------------------------------


void __fastcall THeaderFooterForm::Button4Click(TObject *Sender)
{
	Bluetooth1->Enabled = false;
	this->Memo1->Lines->Add("Bluetooth1->Enabled");
	this->Memo1->Lines->Add(Bluetooth1->Enabled);
	this->Memo1->Lines->Add("Bluetooth1->StateConnected");
	this->Memo1->Lines->Add(Bluetooth1->StateConnected);
	Bluetooth1->CleanupInstance();
    this->Memo1->GoToTextEnd();
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button5Click(TObject *Sender)
{
	send_command(SCROL0ROW_START);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button7Click(TObject *Sender)
{
	send_command(SCROL0ROW_STOP);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button6Click(TObject *Sender)
{
	send_command(SCROL1ROW_START);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button8Click(TObject *Sender)
{
	send_command(SCROL1ROW_STOP);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::ButSTR_00Click(TObject *Sender)
{
	String str = "  Thanks!  ";
	send_str(str, 0);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::FormClose(TObject *Sender, TCloseAction &Action)

{
/*
	if (my_sock->Connected) {
		my_sock->Close();
	}
*/
	my_sock->Close();
	Bluetooth1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button9Click(TObject *Sender)
{
	send_command(CLEAR1ROW);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::ButSTR_01Click(TObject *Sender)
{
	String str = "  Sorry!  ";
	send_str(str, 1);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::ButSTR_02Click(TObject *Sender)
{
	String str = "Too close man! ";
	send_str(str, 1);
}
//---------------------------------------------------------------------------
void __fastcall THeaderFooterForm::BtClrR1RClick(TObject *Sender)
{
	send_command(SET_COLOR1, COLOR_R);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtClrR1GClick(TObject *Sender)
{
	send_command(SET_COLOR1, COLOR_G);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtClrR1BClick(TObject *Sender)
{
	send_command(SET_COLOR1, COLOR_B);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtClrR0RClick(TObject *Sender)
{
	send_command(SET_COLOR0, COLOR_R);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtClrR0GClick(TObject *Sender)
{
 	send_command(SET_COLOR0, COLOR_G);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtClrR0BClick(TObject *Sender)
{
	send_command(SET_COLOR0, COLOR_B);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtClrR1YClick(TObject *Sender)
{
	send_command(SET_COLOR1, COLOR_R | COLOR_G);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtClrR0YClick(TObject *Sender)
{
	send_command(SET_COLOR0, COLOR_R | COLOR_G);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtCltR1PClick(TObject *Sender)
{
	send_command(SET_COLOR1, COLOR_R | COLOR_B);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtClrR0PClick(TObject *Sender)
{
	send_command(SET_COLOR0, COLOR_R | COLOR_B);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtClrR1SClick(TObject *Sender)
{
	send_command(SET_COLOR1, COLOR_G | COLOR_B);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::BtClrR0SClick(TObject *Sender)
{
	send_command(SET_COLOR0, COLOR_G | COLOR_B);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button10Click(TObject *Sender)
{
	Bluetooth1->Enabled = true;
	usleep(500000);
	for( char i = 0; i < this->Bluetooth1->PairedDevices()->Count; i++)
	{
		TBluetoothDevice * dev = this->Bluetooth1->PairedDevices()->First() + i;
		if (dev->DeviceName == "HC-05")
		{
			this->Memo1->Lines->Add("HC-05 FOUNDED!!!");
			TBluetoothService serv = dev->GetServices()->First();
			this->Memo1->Lines->Add(
				serv.Name
			);

			char try_count = 10;
			while (try_count--){
				try{
					this->Memo1->Lines->Add("trying connected...");
					my_sock =  dev->CreateClientSocket(
						serv.UUID,
						true);

					my_sock->Connect();

					this->Memo1->Lines->Add("Connected.");
					this->Memo1->GoToTextEnd();
					this->Memo1->Repaint();

					this->TabControl1->ActiveTab = this->TabItem1;
					return;
				}catch(...){
					this->Memo1->Lines->Add("Exception!");
					this->Memo1->Lines->Add("Reset Bluetooth and try again.");
                    this->Memo1->Repaint();
					usleep(1000000);
				}
			}
			this->Memo1->Lines->Add("Try reboot Device or Matrix");
			this->Memo1->GoToTextEnd();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Bstr1Click(TObject *Sender)
{
	send_command(SHOW_MEMORED_STR, 0);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button11Click(TObject *Sender)
{
	send_command(SHOW_MEMORED_STR, 1);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button12Click(TObject *Sender)
{
	send_command(SHOW_MEMORED_STR, 2);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button13Click(TObject *Sender)
{
	send_command(SHOW_MEMORED_STR, 3);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button14Click(TObject *Sender)
{
	send_command(SHOW_MEMORED_STR, 4);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button15Click(TObject *Sender)
{
    send_command(SHOW_MEMORED_STR, 5);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button19Click(TObject *Sender)
{
    this->Edit1->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button17Click(TObject *Sender)
{
	String str = this->Edit1->Text;
	send_str(str, 0);
	this->TabControl1->ActiveTab = this->TabItem1;
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button18Click(TObject *Sender)
{
	String str = this->Edit1->Text;
	send_str(str, 1);
	this->TabControl1->ActiveTab = this->TabItem1;
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::Button16Click(TObject *Sender)
{
	char num = -1;
	num = this->ComboBox1->Selected->Text.ToInt() - 1 ;
	send_command(SET_STR0_MEMORED, num);
}
//---------------------------------------------------------------------------


