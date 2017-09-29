#pragma once


#include <map>

#include "Interface.h"
#include "ConfigurationPageUI.h"
#include "CReader.h"
#include "Resource.h"

#define _rect(x,y,width,height)		(x),(y),((x)+width),((y)+height)

#define WC_ChapterReader		WC_DIALOG
#define DEFAULT_DEVID			READER_TYPE::M201
#define DEFAULT_COMMPORT		COMM_TYPE::USB

//#define DEFAULT_FONT			_U"MS Shell Dlg"
//#define NO_NAME					_T("")
#define GB_USB_PORT_TEXT		_T("USB")
#define GB_COM_PORT_TEXT		_T("Serial Port")
#define LB_READER_TYPE_TEXT		_T("Reder Type:")
#define LB_COMM_TYPE_TEXT		_T("Comm Type:")
#define BN_OPEN_TEXT			_T("Open")
#define BN_CLOSE_TEXT			_T("Close")
#define LB_USB_OPEN_TYPE_TEXT	_T("USB Open Type:")
#define LB_SERIAL_NUMBER_TEXT	_T("Serial Number:")
#define LB_SERIAL_NUMBER_TEXT	_T("Serial Number:")
#define BN_CONFIG_READ_TEXT		_T("Read Config")
#define BN_CONFIG_WRITE_TEXT	_T("Write Config")
#define BN_CONFIG_SAVE_TEXT		_T("Save")
#define LB_CONFIG_START_TEXT	_T("Start:")
#define LB_CONFIG_COUNT_TEXT	_T("Count:")
#define LB_CONFIG_SIZE_PER_BLOCK_TEXT	_T("Size Per Block:")
#define LB_COM_PORT_TEXT				_T("COM:")
#define LB_COM_BAUD_TEXT				_T("Baud:")
#define LB_COM_FRAME_TEXT				_T("Frame:")
#define BN_CONFIG_LOAD_FILE_TEXT		_T("Load Config From File")
#define BN_CONFIG_SAVE_FILE_TEXT		_T("Save Config To File")
#define BN_CONFIG_RESET_TEXT			_T("reset")
// CReaderUI
#define LB_READER_TYPE_POS				CRect(5, 9, 70, 25)
#define LB_COMM_TYPE_POS				CRect(5, 36, 70, 50)
#define CBB_READER_TYPE_POS				CRect(70, 6, 160, 0)
#define CBB_COMM_TYPE_POS				CRect(70, 33, 160, 0)
#define BN_OPEN_POS						_rect(5, 195, 75, 25)
#define BN_CLOSE_POS					_rect(85, 195, 75, 25)
#define DG_COMM_PORT_POS				CRect(5, 60, 160, 190)
#define PGC_ConfigurationPage_POS		CRect(165, 0, 600, 300)
#define LB_CONFIG_START_POS				CRect(5, 225, 40, 245)
#define LB_CONFIG_COUNT_POS				CRect(85, 225, 120, 245)
#define CBB_CONFIG_START_POS			CRect(40, 223, 80, 243)
#define CBB_CONFIG_COUNT_POS			CRect(120, 223, 160, 243)
#define LB_CONFIG_SIZE_PER_BLOCK_POS	CRect(5, 254, 80, 269)
#define CBB_CONFIG_SIZE_PER_BLOCK_POS	CRect(85, 252, 160, 267)
#define BN_CONFIG_SAVE_POS				_rect(5, 310, 75, 25)
#define BN_CONFIG_READ_POS				CRect(5, 280, 80, 305)
#define BN_CONFIG_WRITE_POS				CRect(85, 280, 160, 305)
#define BN_CONFIG_LOAD_FILE_POS			_rect(5,340,155,25)
#define BN_CONFIG_SAVE_FILE_POS			_rect(5,370,155,25)
#define BN_CONFIG_RESET_POS				_rect(85,310,75,25)


// CCOMPortUI
#define LB_COM_PORT_POS					CRect(5,20,40,45)
#define LB_COM_BAUD_POS					CRect(5,60,40,85)
#define LB_COM_FRAME_POS				CRect(5,100,40,125)
#define CBB_COM_PORT_POS				CRect(40,18,150,43)
#define CBB_COM_BAUD_POS				CRect(40,58,150,83)
#define CBB_COM_FRAME_POS				CRect(40,98,150,123)


// CUSBPortUI
#define LB_USB_OPEN_TYPE_POS			CRect(5, 20, 145, 39)
#define LB_SERIAL_NUMBER_POS			CRect(5, 70, 145, 89)
#define CBB_USB_OPEN_TYPE_POS			CRect(5, 40, 149, 54)
#define CBB_SERIAL_NUMBER_POS			CRect(5, 90, 149, 104)

//

#define CONSTANT_UNKOWN_READER_TYPE_NAME _T("UNKOWN")

#define SUPPORT_READER_TYPE		\
	_T("M201"),		\
	_T("RD120M"),	\
	_T("RD242"),	\
	_T("SSR100"),	\
	_T("RD5100"),	\
	_T("RL8000"),	\
	_T("RPAN")


#define SUPPORT_COMM_TYPE				\
	_T(CONNSTR_NAME_COMMTYPE_COM),		\
	_T(CONNSTR_NAME_COMMTYPE_USB),		\
	_T(CONNSTR_NAME_COMMTYPE_NET),		\
	_T(CONNSTR_NAME_COMMTYPE_BLUETOOTH)


// CReaderUI
enum {
	RS_USER	= 0x8000,
	BN_OPEN,
	BN_CLOSE,
	DG_READER,
	CBB_READER_TYPE,
	CBB_COMM_TYPE,
	GB_COMM_PORT,
	DG_COMM_PORT,
	CBB_USB_OPEN_TYPE,
	CBB_SERIAL_NUMBER,
	BN_CONFIG_READ,
	BN_CONFIG_WRITE,
	BN_CONFIG_SAVE,
	CBB_CONFIG_START,
	CBB_CONFIG_COUNT,
	CBB_CONFIG_SIZE_PER_BLOCK,
	CBB_COM_PORT,
	CBB_COM_BAUD,
	CBB_COM_FRAME,
	BN_CONFIG_SAVE_FILE,
	BN_CONFIG_LOAD_FILE,
	BN_CONFIG_RESET,
};

enum 
{
	WM_ENUM_READER = WM_USER + 100, 
};


class CReaderUI : 
	public CDialogEx
{
	DECLARE_DYNAMIC(CReaderUI)

public:
	CFont				*m_pFont;
	CWnd				*m_pParent;

	CButton				 m_bn_open;
	CButton				 m_bn_close;

	CComboBox			 m_cbb_config_start;
	CComboBox			 m_cbb_config_count;
	CComboBox			 m_cbb_config_size_per_block;

	CButton				 m_bn_config_read;
	CButton				 m_bn_config_write;
	CButton				 m_bn_config_save;
	CButton				 m_bn_config_load_file;
	CButton				 m_bn_config_save_file;
	CButton				 m_bn_config_reset;

	enum { IDD = IDD_READERUI };

private:


	CArray<DRIVERINFO>   m_driver_info_list;
	CConfigurationPageUI*m_configuration;
	
	//CButton				 m_gb_comm_port;
	CStatic				 m_lb_reader_type;
	CStatic				 m_lb_comm_type;

	CComboBox			 m_cbb_reader_type;
	CComboBox			 m_cbb_comm_type;



	CStatic				 m_lb_config_start;
	CStatic				 m_lb_config_count;
	CStatic				 m_lb_config_size_per_block;
	
	CCommPortUI			*m_CommPort;

public:
	CReaderUI(CWnd *pParent = NULL);
	virtual ~CReaderUI();

	// 成员函数
	BOOL Create(CRect &rect);
	BOOL GetConnstr(CString& Connstr);
	BOOL CreatMap(std::map<INT,CString> x);

	// 设置加载的驱动支持的 Reader Type 和 Comm Type，进行排序，检查有效性以及是否支持
	BOOL SetDriverList(CArray<DRIVERINFO> *driver_info_list);

	// 可动态获取读写器和通讯接口类型（即使新加了驱动也不会对原有数值有影响）
	READER_TYPE	GetCurReaderType()CONST;
	READER_TYPE	SetCurReaderType(READER_TYPE ReaderType);
	COMM_TYPE GetCurCommType()CONST;
	COMM_TYPE SetCurCommType(COMM_TYPE CommType);

	
protected:
	// 事件

	virtual INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual VOID OnDestroy();

	// 向父窗口转发控件消息
	virtual BOOL OnCommand(WPARAM wparam,LPARAM lparam);
	void OnCbnSelchangeReaderType();
	void OnCbnSelchangeCommType();

	friend class CUSBPortUI;

	DECLARE_MESSAGE_MAP()
};


