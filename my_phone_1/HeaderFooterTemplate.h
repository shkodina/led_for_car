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
//---------------------------------------------------------------------------
class THeaderFooterForm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *Header;
	TToolBar *Footer;
	TLabel *HeaderLabel;
	TButton *Button1;
	TLabel *Label1;
	TBluetooth *Bluetooth1;
	TButton *Button2;
	TMemo *Memo1;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Bluetooth1DiscoveryEnd(TObject * const Sender, TBluetoothDeviceList * const ADeviceList);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);



private:	// User declarations
public:		// User declarations
	__fastcall THeaderFooterForm(TComponent* Owner);
    TBluetoothSocket * my_sock;
};
//---------------------------------------------------------------------------
extern PACKAGE THeaderFooterForm *HeaderFooterForm;
//---------------------------------------------------------------------------
#endif
