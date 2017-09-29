#pragma once
#include "afxpropertygridctrl.h"
#include "..\Sqlite3\sqlite3.h"

class CConfigurationPageUI :
	public CMFCPropertyGridCtrl
{
	DECLARE_DYNAMIC(CConfigurationPageUI)
public:
	CConfigurationPageUI(CWnd *pParent = NULL);
	~CConfigurationPageUI();


public:
	CWnd			*m_pParent;
	CFont			*m_pFont;
private:

	sqlite3			*m_DB;
	CButton			m_config_read;
	CButton			m_config_write;
	CButton			m_config_save;
	CButton			m_config_save_to_file;
	CButton			m_config_open_from_file;

public:
	BOOL Create(CRect &rect);
	

	

protected:

	virtual INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

