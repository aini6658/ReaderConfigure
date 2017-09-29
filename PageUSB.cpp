// TagUSB.cpp : 实现文件
//

#include "stdafx.h"
#include "PageUSB.h"

typedef CPageUSB			ThisClass;
typedef CDialog			BaseClass;

// CPageUSB 对话框

IMPLEMENT_DYNAMIC(CPageUSB, CPageCommPort)

BEGIN_MESSAGE_MAP(CPageUSB, CPageCommPort)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDOK, OnCancel)
	
	//ON_CBN_SELCHANGE(CBB_USB_OPEN_TYPE, &CPageUSB::OnCbnSelchangeUsbOpenType)
	//ON_EN_CHANGE(CBB_SERIAL_NUMBER, &CPageUSB::OnEnChangeSerialNumber)
END_MESSAGE_MAP()

CPageUSB::CPageUSB(CWnd* pParent /*=NULL*/)
	: CPageCommPort(pParent)
{

}

CPageUSB::CPageUSB(LPCTSTR devID, HID_ENUM_INFO_TYPE InfType, CWnd* pParent /*=NULL*/)
	: CPageCommPort(pParent)
{
	
	Hid_ReaderEnum(devID, InfType);
}

CPageUSB::~CPageUSB()
{
}

void ThisClass::OnCancel(){
}

BOOL ThisClass::OnInitDialog()
{

	BaseClass::OnInitDialog();

	// USB打开类型
	m_cbb_open_type.AddString(_T("None Addressed"));
	m_cbb_open_type.AddString(_T("Serial Number"));
	m_cbb_open_type.SetCurSel((INT)USB_OPEN_TYPE::NONE_ADDRESSED);

	// 因为默认打开类型为None Addressed，所以禁用序列号框
	CString Default_SN;
	//Default_SN.LoadString(IDS_DEFAULT_SN);
	m_cbb_serial_number.SetWindowText(Default_SN);
	m_cbb_serial_number.EnableWindow(FALSE);

	return TRUE;
}

void ThisClass::DoDataExchange(CDataExchange* pDX)
{
	BaseClass::DoDataExchange(pDX);

	//DDX_Control(pDX, LB_USB_OPEN_TYPE, m_lb_open_type);
	//DDX_Control(pDX, LB_SERIAL_NUMBER, m_lb_Serial_Number);
	//DDX_Control(pDX, CBB_USB_OPEN_TYPE, m_cbb_open_type);
	//DDX_Control(pDX, CBB_SERIAL_NUMBER, m_cbb_serial_number);
}



int ThisClass::Hid_ReaderEnum(LPCTSTR devID, HID_ENUM_INFO_TYPE InfType)
{
	m_HID_Readers.RemoveAll();
	INT nCount = 0;
	//nCount = HID_Enum(devID);
	DWORD nSize = MAX_PATH;

	for (INT i = 0; i < nCount; i++){

		TCHAR str[MAX_PATH];
		ZeroMemory(str, MAX_PATH);

		int err = HID_GetEnumItem(nCount, (BYTE)InfType, str, &nSize);

		//if(!err)m_HID_Readers.Add(CString(str));
	}
	
	return nCount;
}








INT ThisClass::GetParams(CString& src)
{
	SIZE_T nSize = src.GetLength();
	INT Succeeded_Count = 0;

	CString csSerNum;
	m_cbb_serial_number.GetWindowText(csSerNum);

	src.AppendFormat(_T(CONNSTR_NAME_HIDADDRMODE) _T("=%d;")
		_T(CONNSTR_NAME_HIDSERNUM) _T("=%s"),
		m_cbb_open_type.GetCurSel(), csSerNum);

	nSize = src.GetLength() - nSize;

	if (nSize == 1)
	{
		Succeeded_Count = 1;
	}
	if (nSize > 1)
	{
		Succeeded_Count = 2;
	}

	return Succeeded_Count;
}

#pragma region "控件事件"

///
/// S/N
///
void CPageUSB::OnEnChangeSerialNumber()
{
//	INT nSize = m_cbb_serial_number
}


/// 
/// USB 打开类型
/// 
void CPageUSB::OnCbnSelchangeUsbOpenType()
{
	USB_OPEN_TYPE OpenType = (USB_OPEN_TYPE)m_cbb_open_type.GetCurSel();

	if (OpenType != USB_OPEN_TYPE::NONE_ADDRESSED)
	{
		m_cbb_serial_number.EnableWindow(TRUE);
		

	}else{

		m_cbb_serial_number.EnableWindow(FALSE);
	}
}

#pragma endregion "控件事件"





