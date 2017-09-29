
// ConfigurationDlg.h : 头文件
//

#pragma once
#include "CReaderUI.h"
#include "CReader.h"
#include "HexEditCtrl.h"


// CConfigurationDlg 对话框
class CConfigurationDlg : public CDialogEx
{
// 构造
public:
	CConfigurationDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CConfigurationDlg();

// 对话框数据
	enum { IDD = DG_MAIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CReaderUI			*m_readerUI;
	BOOL				 m_IsOpened;
	CReader				 m_reader;
	CHexEdit			 m_ed_hex_edit;
	PBYTE				 m_config_blocks;
	CStatic				 m_lb_show;
	BOOL				 IfAutoOpen;
public:

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void ShowMessage(LPCTSTR msg);
	void OnClose();
	void OnOK();
	void OnCancel();
	void OnBnClickedBnOpen();
	void OnBnClickedBnClose();
	void OnBnClickedBnConfigRead();
	void OnBnClickedBnConfigWrite();
	void OnBnClickedBnConfigSave();

	void PrintData(PBYTE datas);
	void ScanData(PBYTE datas);
	void OnEnChangeCOnfigSizePerBlock();
	void OnEnChangeCOnfigStart();
	void OnEnChangeCOnfigCount();

	void OnBnClickedBnConfigReset();
	void OnBnClickedBnConfigLoadFile();
	void OnBnClickedBnConfigSaveFile();
	DECLARE_MESSAGE_MAP()
public:
	
	//afx_msg void OnEnChangeHexEdit();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
