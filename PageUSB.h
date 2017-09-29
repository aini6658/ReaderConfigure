#pragma once

#include "resource.h"
#include "PageCommPort.h"


// USB������
typedef enum class _USB_OPEN_TYPE{
	NONE_ADDRESSED	= 0,
	SERIAL_NUMBER	= 1,
}USB_OPEN_TYPE;

// HIDö����Ϣ����
typedef enum class _HID_ENUM_INFO_TYPE{
	DRIVERPATH		= 0,
	SERIAL_NUMBER	= 1,
}HID_ENUM_INFO_TYPE;
// CPageUSB �Ի���

class CPageUSB 
	:public CPageCommPort
{
	DECLARE_DYNAMIC(CPageUSB)

public:
	CPageUSB(CWnd* pParent = NULL);
	CPageUSB(LPCTSTR devID, HID_ENUM_INFO_TYPE InfType = HID_ENUM_INFO_TYPE::SERIAL_NUMBER, CWnd* pParent = NULL);
	virtual ~CPageUSB();

// �ؼ�
private:
	CStatic		m_lb_open_type;
	CStatic		m_lb_Serial_Number;
	CComboBox	m_cbb_open_type;
	CComboBox	m_cbb_serial_number;

// ��Ա
private:
	CArray<CString> m_HID_Readers;

// �¼�
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnCancel();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnCbnSelchangeUsbOpenType();

	int Hid_ReaderEnum(LPCTSTR devID, HID_ENUM_INFO_TYPE InfType = HID_ENUM_INFO_TYPE::SERIAL_NUMBER);
	INT GetParams(CString& src);

// ��Ա����
public:
	// %d %s  =  AddrMode   SerNum
	// 
	INT PrintParams(CString& src);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnEnChangeSerialNumber();
};
