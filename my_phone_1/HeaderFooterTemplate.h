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
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.adomxmldom.hpp>
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
	TPanel *Panel7;
	TButton *Bstr1;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TButton *Button15;
	TPanel *Panel8;
	TEdit *Edit1;
	TButton *Button16;
	TButton *Button17;
	TButton *Button18;
	TButton *Button19;
	TComboBox *ComboBox1;
	TLabel *Label1;
	TPanel *Panel9;
	TPanel *Panel10;
	TPanel *Panel11;
	TButton *Button20;
	TXMLDocument *XMLDocument1;
	TPanel *Panel12;
	TPanel *Panel13;
	TPanel *Panel14;
	TButton *ButSTR_03;
	TButton *ButSTR_04;
	TButton *ButSTR_05;
	TButton *ButSTR_06;
	TButton *ButSTR_07;
	TButton *ButSTR_08;
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
	void __fastcall Bstr1Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button20Click(TObject *Sender);
	void __fastcall ButSTR_03Click(TObject *Sender);
	void __fastcall ButSTR_04Click(TObject *Sender);
	void __fastcall ButSTR_05Click(TObject *Sender);
	void __fastcall ButSTR_06Click(TObject *Sender);
	void __fastcall ButSTR_07Click(TObject *Sender);
	void __fastcall ButSTR_08Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall THeaderFooterForm(TComponent* Owner);
	TBluetoothSocket * my_sock;
	void send_command(char cmd);
	void send_command(char cmd, char data);
	void send_str(String str, char num_of_str);
	void send_str_from_button(int n);

	void bt_auto_connect();
    void read_config();



	struct MatrixString {
		String str;
		char color;
		char row;
		String hint;
	};

	struct Config {
		Config (){
            psmatrix_name = "HC-05";
		}

		String psmatrix_name;
    };

	MatrixString mstrings[9];
    Config cnf;
};
//---------------------------------------------------------------------------
extern PACKAGE THeaderFooterForm *HeaderFooterForm;
//---------------------------------------------------------------------------
#endif
