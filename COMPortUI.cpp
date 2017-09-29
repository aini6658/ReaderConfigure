// COMPortUI.cpp : 实现文件
//

#include "stdafx.h"
#include "COMPortUI.h"
#include "CReaderUI.h"

typedef CCOMPortUI	_This;
typedef CButton		_Base;
// CCOMPortUI

IMPLEMENT_DYNAMIC(CCOMPortUI, CButton)

CCOMPortUI::CCOMPortUI(CWnd * pParent)
{
	m_pParent = pParent;
}

CCOMPortUI::~CCOMPortUI()
{
}


BEGIN_MESSAGE_MAP(CCOMPortUI, CButton)
	ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL _This::Create(CRect &rect)
{
	m_pParent->AssertValid();
	m_pParent->UpdateData();
	m_pFont = ((CReaderUI*)m_pParent)->m_pFont;

	BOOL ret = _Base::Create(
		GB_COM_PORT_TEXT,
		DS_CONTROL | BS_GROUPBOX | WS_CHILD,
		CRect(rect.left, rect.top, rect.right, rect.bottom),
		m_pParent, DG_COMM_PORT
		);

	SetFont(m_pFont);

	

	return TRUE;
}


INT _This::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	_Base::OnCreate(lpCreateStruct);

	BOOL ret = m_lb_com_port.Create(
		LB_COM_PORT_TEXT,
		WS_CHILD | WS_VISIBLE,
		LB_COM_PORT_POS,
		this
		);

	ASSERT(ret != 0);

	ret = m_lb_com_baud.Create(
		LB_COM_BAUD_TEXT,
		WS_CHILD | WS_VISIBLE|WS_ACTIVECAPTION ,
		LB_COM_BAUD_POS,
		this
		);

	ASSERT(ret != 0);

	ret = m_lb_comm_frame.Create(
		LB_COM_FRAME_TEXT,
		WS_CHILD | WS_VISIBLE,
		LB_COM_FRAME_POS,
		this
		);

	ASSERT(ret != 0);


	ret = m_cbb_com_port.Create(
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CBB_COM_PORT_POS,
		this,
		CBB_COM_PORT
		);

	ASSERT(ret != 0);
	
	ret = m_cbb_com_baud.Create(
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CBB_COM_BAUD_POS,
		this,
		CBB_COM_BAUD
		);

	ASSERT(ret != 0);

	ret = m_cbb_com_frame.Create(
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CBB_COM_FRAME_POS,
		this,
		CBB_COM_FRAME
		);

	ASSERT(ret != 0);


	m_lb_com_port.SetFont(m_pFont);
	m_lb_com_baud.SetFont(m_pFont);
	m_lb_comm_frame.SetFont(m_pFont);

	m_cbb_com_port.SetFont(m_pFont);
	m_cbb_com_baud.SetFont(m_pFont);
	m_cbb_com_frame.SetFont(m_pFont);


	return 0;
}

void _This::Update()
{

	UINT nCOMCnt = COMPort_Enum();
	for (UINT i = 0; i < nCOMCnt; i++)
	{
		TCHAR comName[16];
		ZeroMemory(comName, SIZE_OF_TCHAR(16));
		
		COMPort_GetEnumItem(i, comName, SIZE_OF_TCHAR(16));
		m_cbb_com_port.AddString(comName);
	}

	if (m_cbb_com_port.GetCount() > 0) 
		m_cbb_com_port.SetCurSel(0);

	m_cbb_com_baud.AddString(_T("9600"));
	m_cbb_com_baud.AddString(_T("38400"));
	m_cbb_com_baud.AddString(_T("57600"));
	m_cbb_com_baud.AddString(_T("115200"));

	m_cbb_com_baud.SetCurSel((INT)(COM_BAUD_TYPE::_38400));

	m_cbb_com_frame.AddString(_T("8E1"));
	m_cbb_com_frame.AddString(_T("8N1"));
	m_cbb_com_frame.AddString(_T("8O1"));

	m_cbb_com_frame.SetCurSel((INT)(COM_FRAME_TYPE::_8E1));

	_Base::UpdateWindow();
}

BOOL _This::Hid()
{
	return _Base::ShowWindow(SW_HIDE);
}

BOOL _This::Show()
{
	return _Base::ShowWindow(SW_SHOW);
}

BOOL _This::Destroy()
{
	BOOL ret =_Base:: DestroyWindow();

	return ret;
}

BOOL _This::GetParams(CString& Connstr)
{
	// RDType=M201;CommType=COM;COMName=COM4;BaudRate=38400;Frame=8E1;BusAddr=255"
	CString ComName; 
	CString BaudRate;
	CString Frame; 

	m_cbb_com_port.GetWindowText(ComName);
	m_cbb_com_baud.GetWindowText(BaudRate);
	m_cbb_com_frame.GetWindowText(Frame);

	Connstr.AppendFormat(
		_T(CONNSTR_NAME_COMNAME) _T("=%s;")
		_T(CONNSTR_NAME_COMBARUD) _T("=%s;")
		_T(CONNSTR_NAME_COMFRAME) _T("=%s;")
		_T(CONNSTR_NAME_BUSADDR) _T("=255"),
		ComName,
		BaudRate,
		Frame
		);
	return TRUE;
}

BOOL _This::SendMessage(INT nMsg, WPARAM wParam, LPARAM lParam)
{
	return _Base::SendMessage(nMsg, wParam, lParam);
}


// CCOMPortUI 消息处理程序


