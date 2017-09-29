#include "stdafx.h"
#include "CUSBPortUI.h"
#include "CReaderUI.h"

typedef CUSBPortUI			_This;
typedef CButton				_Base;

IMPLEMENT_DYNAMIC(CUSBPortUI, CButton)

BEGIN_MESSAGE_MAP(CUSBPortUI, CButton)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(CBB_USB_OPEN_TYPE, OnCbnSelchangeUSBOpenType)
	ON_MESSAGE(WM_ENUM_READER,OnEnumReader)
END_MESSAGE_MAP()

CUSBPortUI::CUSBPortUI(CWnd *pParent /*= NULL*/)
	:CButton(),
	m_pParent(NULL)
{
	pParent->AssertValid();

	m_pParent = pParent;
	
}


CUSBPortUI::~CUSBPortUI()
{
}


BOOL _This::Create(CRect &rect)
{
	m_pParent->AssertValid();
	m_pParent->UpdateData();
	m_pFont = ((CReaderUI*)m_pParent)->m_pFont;

	BOOL ret = _Base::Create(
		GB_USB_PORT_TEXT,
		BS_GROUPBOX | WS_CHILD,
		CRect(rect.left, rect.top, rect.right, rect.bottom),
		m_pParent, DG_COMM_PORT
		);

	SetFont(m_pFont);

	return TRUE;
}

void _This::Update()
{
	UpdateWindow();
}

BOOL _This::Hid()
{
	return ShowWindow(SW_HIDE);
}

BOOL _This::Show()
{
	return ShowWindow(SW_SHOW);
}

BOOL _This::Destroy()
{
	BOOL ret = DestroyWindow();

	return ret;
}

BOOL _This::GetParams(CString& Connstr)
{
	CString SerialNum;
	m_cbb_serial_number.GetWindowText(SerialNum);

	Connstr.AppendFormat(
		_T(CONNSTR_NAME_HIDADDRMODE) _T("=%d;")
		_T(CONNSTR_NAME_HIDSERNUM) _T("=%s;"),
		(INT)m_cbb_usb_open_type.GetCurSel(),
		SerialNum
		);
	return TRUE;
}

INT _This::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	_Base::OnCreate(lpCreateStruct);

	AssertValid();

	BOOL ret = m_lb_usb_open_type.Create(
		LB_USB_OPEN_TYPE_TEXT,
		WS_CHILD | WS_VISIBLE,
		LB_USB_OPEN_TYPE_POS,
		this
		);

	ASSERT(ret != 0);

	ret = m_lb_serial_number.Create(
		LB_SERIAL_NUMBER_TEXT,
		WS_CHILD | WS_VISIBLE,
		LB_SERIAL_NUMBER_POS,
		this
		);

	ASSERT(ret != 0);

	ret = m_cbb_usb_open_type.Create(
		WS_VSCROLL | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CBB_USB_OPEN_TYPE_POS,
		this,
		CBB_USB_OPEN_TYPE
		);

	ASSERT(ret != 0);

	m_cbb_usb_open_type.AddString(_T("None Addressed"));
	m_cbb_usb_open_type.AddString(_T("Serial Number"));
	m_cbb_usb_open_type.SetCurSel(0);

	ret = m_cbb_serial_number.Create(
		WS_DISABLED | WS_VSCROLL | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CBB_SERIAL_NUMBER_POS,
		this,
		CBB_SERIAL_NUMBER
		);

	ASSERT(ret != 0);


	m_lb_usb_open_type.SetFont(m_pFont);
	m_lb_serial_number.SetFont(m_pFont);
	m_cbb_usb_open_type.SetFont(m_pFont);
	m_cbb_serial_number.SetFont(m_pFont);

	return 0;
}

BOOL _This::SendMessage(INT nMsg, WPARAM wParam, LPARAM lParam)
{
	return _Base::SendMessage(nMsg, wParam, lParam);
}

void _This::OnCbnSelchangeUSBOpenType()
{
	INT cur_usb_open_type;
	if ( cur_usb_open_type = m_cbb_usb_open_type.GetCurSel())
	{
		if (cur_usb_open_type != -1)
		{

		}
	}


}

LRESULT _This::OnEnumReader(WPARAM wParam,LPARAM lParam)
{
	m_cbb_serial_number.AddString(_T("FFFFFFFFFF"));
	m_cbb_serial_number.SetCurSel(0);
	return 1;
}