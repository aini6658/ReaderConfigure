
// ConfigurationDlg.h : ͷ�ļ�
//

#pragma once


// CConfigurationDlg �Ի���
class CConfigurationDlg : public CDialogEx
{
// ����
public:
	CConfigurationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_READERCONFIGURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void OnClose();
	void OnOK();
	void OnCancel();

	DECLARE_MESSAGE_MAP()
};
