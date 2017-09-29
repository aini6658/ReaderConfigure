#pragma once
#include "Interface.h"

enum class COM_BAUD_TYPE
	:INT
{
	_9600 = 0,
	_38400,
	_57600,
	_115200,
};

enum class COM_FRAME_TYPE
	:INT
{
	_8E1 = 0,
	_8N1,
	_8O1,
};

class CCOMPortUI 
	: public CButton,
	public CCommPortUI
{
	DECLARE_DYNAMIC(CCOMPortUI)

public:
	CWnd			*m_pParent;
	CFont			*m_pFont;

	CStatic			 m_lb_com_port;
	CStatic			 m_lb_com_baud;
	CStatic			 m_lb_comm_frame;

	CComboBox		 m_cbb_com_port;
	CComboBox		 m_cbb_com_baud;
	CComboBox		 m_cbb_com_frame;

public:
	CCOMPortUI(CWnd * pParent = NULL);
	virtual ~CCOMPortUI();

	BOOL Create(CRect &rect);
	virtual BOOL Hid();
	virtual BOOL Show();
	virtual BOOL Destroy();
	virtual BOOL GetParams(CString& Connstr);
	virtual void Update();

protected:
	virtual INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL SendMessage(INT nMsg, WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


