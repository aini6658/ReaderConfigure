#pragma once
#include "AWnd.h"


// CPageCommPort

class CPageCommPort 
	: public CDialogEx
{
	DECLARE_DYNAMIC(CPageCommPort)

	enum { IDD = PAGE_COMM_PORT };

public:
	CWnd *m_window;
	CPageCommPort(CWnd* Parent = NULL);
	virtual ~CPageCommPort();

	virtual INT GetParams(CString& dest) = 0;

protected:
	afx_msg void OnClose();
	afx_msg void OnCancel();
	afx_msg void OnOK();
	//virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};


