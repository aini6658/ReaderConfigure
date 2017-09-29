#pragma once

#include "Interface.h"
#include <afxwin.h>



class CUSBPortUI :
	public CButton,
	public CCommPortUI
{
	DECLARE_DYNAMIC(CUSBPortUI)

public:
	CWnd			*m_pParent;
	CFont			*m_pFont;

private:

	
	CStatic				m_lb_usb_open_type;
	CStatic				m_lb_serial_number;
	CComboBox			m_cbb_usb_open_type;
	CComboBox			m_cbb_serial_number;

public:
	CUSBPortUI(CWnd *pParent = NULL);
	~CUSBPortUI();

	// ³ÉÔ±º¯Êý
	BOOL Create(CRect &rect);

	virtual BOOL Hid();
	virtual BOOL Show();
	virtual BOOL Destroy();
	virtual BOOL GetParams(CString& Connstr);
	virtual void Update();

protected:
	virtual INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnCbnSelchangeUSBOpenType();
	virtual BOOL SendMessage(INT nMsg, WPARAM wParam,LPARAM lParam);
	LRESULT OnEnumReader(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

