//// ReaderType.cpp : 实现文件
////
//
#include "stdafx.h"
//#include "Reader.h"
//#include "afxdialogex.h"
//#include "rfidlib_reader.h"
//#include <crtdbg.h>
//#include "PageCommPort.h"
//#include "PageUSB.h"
//
//typedef CTagReader			_This;
//typedef CDialog				_Base;
//
//// CReaderType 对话框
//
//IMPLEMENT_DYNAMIC(CTagReader, CDialog)
//
//BEGIN_MESSAGE_MAP(CTagReader, CDialog)
//	ON_CBN_SELCHANGE(CBB_READER_TYPE, &CTagReader::OnCbnSelchangeReaderType)
//	ON_CBN_SELCHANGE(CBB_COMM_TYPE, &CTagReader::OnCbnSelchangeCommType)
//END_MESSAGE_MAP()
//
//
//static CONST PTCHAR m_support_reader_type[] = { SUPPORT_READER_TYPE , _T("")};
//static CONST PTCHAR m_support_comm_type[] = { SUPPORT_COMM_TYPE , _T("")};
//
//CTagReader::CTagReader(CWnd* pParent /*=NULL*/)
//	: 
//	CDialog(CTagReader::IDD, pParent),
//	m_reader_driver_info_list(NULL),
//	m_hReader(NULL),
//	m_hTag(NULL),
//	m_comm_port(NULL),
//	m_parent(pParent),
//	m_dnInvenParamList(RFID_HANDLE_NULL)
//{
//
//}
//
//CTagReader::~CTagReader()
//{
//	Delete(m_reader_driver_info_list);
//	Delete(m_comm_port);
//
//}
//
//void CTagReader::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//	
//	DDX_Control(pDX, CBB_READER_TYPE, m_cbb_reader_type);
//	DDX_Control(pDX, CBB_COMM_TYPE, m_cbb_comm_type);
//	//DDX_CBIndex(pDX, CBB_COMM_TYPE, m_comm_type);
//}
//
//
//BOOL _This::OnInitDialog()
//{
//	_Base::OnInitDialog();
//
//	// 获取加载的驱动的数量
//	m_driver_count = RDR_GetLoadedReaderDriverCount();
//
//	TCHAR info[64];
//	ZeroMemory(info, sizeof(info));
//	SIZE_T  nSize = sizeof(info);
//
//	m_reader_driver_info_list = new RDRDVR_INFO[m_driver_count];
//
//	// 搜索加载的驱动并添加 ReaderType
//	for (INT i = 0; i < m_driver_count; i++)
//	{
//		RDR_GetLoadedReaderDriverOpt(i, _T(LOADED_RDRDVR_OPT_CATALOG), info, &nSize);
//
//		if (!_tcscmp(_T(RDRDVR_TYPE_READER), info))
//		{
//			ZeroMemory(info, SIZE_OF_TCHAR(nSize));
//			nSize = sizeof(info);
//
//			RDR_GetLoadedReaderDriverOpt(i, _T(LOADED_RDRDVR_OPT_NAME), info, &nSize);
//			m_cbb_reader_type.AddString(m_reader_driver_info_list[i].reader_type = info);
//
//			ZeroMemory(info, SIZE_OF_TCHAR(nSize));
//			nSize = sizeof(info);
//
//			RDR_GetLoadedReaderDriverOpt(i, _T(LOADED_RDRDVR_OPT_ID), info, &nSize);
//			m_reader_driver_info_list[i].driver_id = _tcstoul(info, 0, 10);
//
//			ZeroMemory(info, SIZE_OF_TCHAR(nSize));
//			nSize = sizeof(info);
//
//			RDR_GetLoadedReaderDriverOpt(i, _T(LOADED_RDRDVR_OPT_COMMTYPESUPPORTED), info, &nSize);
//			m_reader_driver_info_list[i].comm_type_supported = _tcstoul(info, 0, 10);
//
//			ZeroMemory(info, SIZE_OF_TCHAR(nSize));
//			nSize = sizeof(info);
//		}
//	}
//
//	SetCurReaderType(READER_TYPE::RL8000);
//	SetCurCommType(COMM_TYPE::USB);
//
//	return TRUE;
//}
//
//READER_TYPE	_This::GetCurReaderType()CONST
//{
//	CString csReaderType;
//	LPTSTR szReader_Type;
//
//	m_cbb_reader_type.GetWindowText(csReaderType);
//
//	for (INT i = 0; !IsEmptyStr(szReader_Type = m_support_reader_type[i]); i++)
//	{
//		if (!_tcscmp(csReaderType, szReader_Type))
//			return static_cast<READER_TYPE>(i);
//	}
//
//	return READER_TYPE::UNKOWN;
//}
//
//
//READER_TYPE	_This::SetCurReaderType(READER_TYPE ReaderType)
//{
//	ASSERT(ReaderType != READER_TYPE::UNKOWN);
//
//	// 因加载的驱动可能少，可能多，依照枚举值选择不可靠
//	LPCTSTR szReaderType = m_support_reader_type[static_cast<INT>(ReaderType)];
//	INT i = m_cbb_reader_type.GetCount();
//
//	while (i--)
//	{
//		CString lbtext;
//		m_cbb_reader_type.GetLBText(i, lbtext);
//
//		// 如果是目标读写器类型则退出循环
//		if (!_tcscmp(lbtext, szReaderType))
//			break;
//	}
//
//	if (m_cbb_reader_type.SetCurSel(i) != CB_ERR)
//	{
//		// 调整可用的通讯类型
//		SendMessage(WM_COMMAND, MAKEWPARAM(CBB_READER_TYPE, CBN_SELCHANGE), reinterpret_cast<LPARAM>(m_cbb_reader_type.m_hWnd));
//		return ReaderType;
//	}
//	
//	return READER_TYPE::UNKOWN;
//}
//
//COMM_TYPE _This::GetCurCommType()CONST
//{
//	CString csCommType;
//	LPTSTR szComm_Type;
//
//	m_cbb_comm_type.GetWindowText(csCommType);
//
//	for (INT i = 0; !IsEmptyStr(szComm_Type = m_support_comm_type[i]); i++)
//	{
//		if (!_tcscmp(csCommType, szComm_Type))
//			return static_cast<COMM_TYPE>(i);
//	}
//	
//	return COMM_TYPE::UNKOWN;
//}
//
//
//COMM_TYPE _This::SetCurCommType(COMM_TYPE CommType)
//{
//	LPCTSTR szCommType = m_support_comm_type[static_cast<INT>(CommType)];
//	
//	INT i = m_cbb_comm_type.GetCount();
//
//	while (i--)
//	{
//		CString lbText;
//		m_cbb_comm_type.GetLBText(i, lbText);
//
//		if (!_tcscmp(lbText, szCommType))
//		{
//			break;
//		}
//	}
//
//	COMM_TYPE ret = static_cast<COMM_TYPE>(m_cbb_comm_type.SetCurSel(i));
//	OnCbnSelchangeCommType();
//
//	return ret;
//}
//
//
//void CTagReader::OnCbnSelchangeReaderType()
//{
//	// 保存已选项
//	COMM_TYPE saved = GetCurCommType();
//
//	// 清空项
//	m_cbb_comm_type.ResetContent();
//
//	INT CurReaderType = (INT)GetCurReaderType();
//
//	// 添加 CommType
//	FLAG_T CommTypeSupported = m_reader_driver_info_list[CurReaderType].comm_type_supported;
//
//	if ((CommTypeSupported & COMMTYPE_COM_EN) != 0)
//	{
//		m_cbb_comm_type.AddString(_T(CONNSTR_NAME_COMMTYPE_COM));
//	}
//	if ((CommTypeSupported & COMMTYPE_USB_EN) != 0)
//	{
//		m_cbb_comm_type.AddString(_T(CONNSTR_NAME_COMMTYPE_USB));
//	}
//	if ((CommTypeSupported & COMMTYPE_NET_EN) != 0)
//	{
//		m_cbb_comm_type.AddString(_T(CONNSTR_NAME_COMMTYPE_NET));
//	}
//	if ((CommTypeSupported & COMMTYPE_BLUETOOTH_EN) != 0)
//	{
//		m_cbb_comm_type.AddString(_T(CONNSTR_NAME_COMMTYPE_BLUETOOTH));
//	}
//
//	// 恢复选择（若选项不存在，将返回-1）
//	if (saved != COMM_TYPE::UNKOWN)
//		if(SetCurCommType(saved) == COMM_TYPE::UNKOWN)
//			m_cbb_comm_type.SetCurSel(0);
//	else
//		m_cbb_comm_type.SetCurSel(0);
//}
//
//
//void CTagReader::OnCbnSelchangeCommType()
//{
//	COMM_TYPE comm_type = this->GetCurCommType();
//
//	if (m_comm_port)
//	{
//		((CDialog*)m_comm_port)->DestroyWindow();
//		m_comm_port = NULL;
//	}
//
//	switch (comm_type)
//	{
//	case COMM_TYPE::COM:
//
//
//		break;
//
//	case COMM_TYPE::USB:
//
//
//		m_comm_port = (CTagComm*)new CTagUSB(m_support_reader_type[static_cast<INT>(GetCurReaderType())]);
//
//		((CTagUSB*)m_comm_port)->Create(IDD_TAGUSB);
//		((CTagUSB*)m_comm_port)->SetWindowPos(m_parent, 15, 62, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
//		((CTagUSB*)m_comm_port)->ShowWindow(SW_SHOW);
//
//		break;
//
//	case COMM_TYPE::NET:
//
//
//		break;
//
//	case COMM_TYPE::BLUETOOTH:
//
//
//		break;
//
//	default:
//		break;
//	}
//
//
//}
//
//
//ERROR_TYPE CTagReader::Open()
//{
//
//	CString reader_type = m_support_reader_type[static_cast<INT>(this->GetCurReaderType())];
//	CString comm_type = m_support_comm_type[static_cast<INT>(this->GetCurCommType())];
//
//	CString m_comm_params = _T(CONNSTR_NAME_RDTYPE) _T("=") + reader_type + _T(";")
//		_T(CONNSTR_NAME_COMMTYPE) _T("=") + comm_type + _T(";");
//
//	(m_comm_port)->PrintParams(m_comm_params);
//
//	if (RDR_Open(m_comm_params, &m_hReader)!=NOERROR)
//	{
//		MessageBox(_T("RDR_Open Failed!"));
//		return ERROR_TYPE::OpenFailed;
//	}
//
//
//
//	return ERROR_TYPE::NoMatter;
//}
//
//
//ERROR_TYPE CTagReader::Inventory()
//{
//	m_dnInvenParamList = RDR_CreateInvenParamSpecList();
//
//	
//	//if (Info.AIPType | AIP_TYPE::AIP_TYPE_ISO15693)
//	//	ISO15693_CreateInvenParam(
//	//	m_dnInvenParamList,
//	//	Info.AntenalID,
//	//	Info.EnableAFI,
//	//	Info.AFI,
//	//	Info.SlotType
//	//	);
//
//	//if (Info.AIPType | AIP_TYPE::AIP_TYPE_ISO14443A)
//	//	ISO14443A_CreateInvenParam(
//	//	m_dnInvenParamList,
//	//	Info.AntenalID
//	//	);
//
//	//if (Info.AIPType | AIP_TYPE::AIP_TYPE_ISO18000p3m3)
//	//	ISO18000p3m3_CreateInvenParam(
//	//	m_dnInvenParamList,
//	//	Info.AntenalID,
//	//	Info.Sel,
//	//	Info.Session,
//	//	Info.Q
//	//	);
//
//
//	if (m_dnInvenParamList)
//	{
//		DNODE_Destroy(m_dnInvenParamList);
//		m_dnInvenParamList = RFID_HANDLE_NULL;
//	}
//
//	return ERROR_TYPE::NoMatter;
//}