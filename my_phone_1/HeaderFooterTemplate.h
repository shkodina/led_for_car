//---------------------------------------------------------------------------

#ifndef HeaderFooterTemplateH
#define HeaderFooterTemplateH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <System.Bluetooth.Components.hpp>
#include <System.Bluetooth.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.TabControl.hpp>
//---------------------------------------------------------------------------
class THeaderFooterForm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *Footer;
	TBluetooth *Bluetooth1;
	TButton *Button2;
	TMemo *Memo1;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TTabControl *TabControl1;
	TTabItem *TabItem1;
	TTabItem *TabItem2;
	TTabItem *TabItem3;
	TTabItem *TabItem4;
	TPanel *Panel1;
	TPanel *Panel2;
	TButton *Button1;
	TButton *Button9;
	TPanel *Panel3;
	TPanel *Panel4;
	TButton *ButSTR_00;
	TButton *ButSTR_01;
	TButton *ButSTR_02;
	TPanel *Panel5;
	TStyleBook *StyleBook1;
	TButton *BtClrR1R;
	TButton *BtClrR1G;
	TButton *BtClrR1B;
	TPanel *Panel6;
	TButton *BtClrR0R;
	TButton *BtClrR0G;
	TButton *BtClrR0B;
	TButton *BtClrR1Y;
	TButton *BtClrR0Y;
	TButton *BtCltR1P;
	TButton *BtClrR0P;
	TButton *BtClrR1S;
	TButton *BtClrR0S;
	TButton *Button10;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Bluetooth1DiscoveryEnd(TObject * const Sender, TBluetoothDeviceList * const ADeviceList);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall ButSTR_00Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall ButSTR_01Click(TObject *Sender);
	void __fastcall ButSTR_02Click(TObject *Sender);
	void __fastcall BtClrR1RClick(TObject *Sender);
	void __fastcall BtClrR1GClick(TObject *Sender);
	void __fastcall BtClrR1BClick(TObject *Sender);
	void __fastcall BtClrR0RClick(TObject *Sender);
	void __fastcall BtClrR0GClick(TObject *Sender);
	void __fastcall BtClrR0BClick(TObject *Sender);
	void __fastcall BtClrR1YClick(TObject *Sender);
	void __fastcall BtClrR0YClick(TObject *Sender);
	void __fastcall BtCltR1PClick(TObject *Sender);
	void __fastcall BtClrR0PClick(TObject *Sender);
	void __fastcall BtClrR1SClick(TObject *Sender);
	void __fastcall BtClrR0SClick(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall THeaderFooterForm(TComponent* Owner);
	TBluetoothSocket * my_sock;
	void send_command(char cmd);
	void send_command(char cmd, char data);
	void send_str(String str, char num_of_str);
};
//---------------------------------------------------------------------------
extern PACKAGE THeaderFooterForm *HeaderFooterForm;
//---------------------------------------------------------------------------
#endif
