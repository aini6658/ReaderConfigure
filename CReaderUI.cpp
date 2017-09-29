// WrapperReader.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "CReaderUI.h"
#include "CUSBPortUI.h"
#include "COMPortUI.h"

typedef CReaderUI			_This;
typedef CDialogEx			_Base;

IMPLEMENT_DYNAMIC(CReaderUI, CDialogEx)

BEGIN_MESSAGE_MAP(CReaderUI, CDialogEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(CBB_READER_TYPE, OnCbnSelchangeReaderType)
	ON_CBN_SELCHANGE(CBB_COMM_TYPE, OnCbnSelchangeCommType)
	
	
END_MESSAGE_MAP()


static CONST PTCHAR m_support_reader_type[] = { SUPPORT_READER_TYPE, 0 };
static CONST PTCHAR m_support_comm_type[] = { SUPPORT_COMM_TYPE, 0 };


CReaderUI::CReaderUI(CWnd *pParent/* = NULL*/):
	CDialogEx(CReaderUI::IDD, pParent),	
	m_pParent(NULL)
	
{
	pParent->AssertValid();

	m_pParent = pParent;
}

CReaderUI::~CReaderUI()
{

}


BOOL _This::Create(CRect &rect)
{
	//m_pParent->AssertValid();

	m_pFont = m_pParent->GetFont();

	BOOL ret = CreateEx(
		WS_EX_TRANSPARENT,
		WC_ChapterReader,
		NO_NAME,
		DS_CONTROL | WS_ACTIVECAPTION | DS_SETFONT | DS_FIXEDSYS | WS_CHILD | WS_TABSTOP,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		m_pParent->m_hWnd, NULL, NULL
		);

	ShowWindow(SW_SHOW);
	UpdateWindow();

	m_CommPort = new CUSBPortUI(this);
	ret = m_CommPort->Create(DG_COMM_PORT_POS);
	m_CommPort->Show();
	m_CommPort->Update();
	//m_configuration = new CConfigurationPageUI(this);
	//ret = m_configuration->Create(CRect(165, 0, rect.right - rect.left, rect.bottom - rect.top));

	return ret;
}


BOOL _This::SetDriverList(CArray<DRIVERINFO> *pdriver_info_list)
{
	// 清空
	m_driver_info_list.RemoveAll();

	LPCTSTR szReader_Type;
	DRIVERINFO CurDriverInfo;

	// 复制驱动支持列表
	for (INT x = 0, y = 0; szReader_Type = m_support_reader_type[x]; x++)
	{
		//BOOL IsSupported = FALSE;

		// 判断是否已加载以及支持
		for (INT z = 0; z < pdriver_info_list->GetCount(); z++)
		{
			CurDriverInfo = pdriver_info_list->ElementAt(z);

			if (!_tcscmp(CurDriverInfo.DriverName, szReader_Type))
			{
				m_cbb_reader_type.AddString(CurDriverInfo.DriverName);
				break;
			}
		}

		m_driver_info_list.Add(CurDriverInfo);
			
	}// 复制驱动支持列表


	SetCurReaderType(DEFAULT_DEVID);
	SetCurCommType(DEFAULT_COMMPORT);
	//m_CommPort->SendMessage(WM_COMMAND, MAKEWPARAM(CBB_USB_OPEN_TYPE, CBN_SELCHANGE), (LPARAM)this->m_hWnd);
	m_CommPort->SendMessage(WM_ENUM_READER, (WPARAM)m_support_reader_type[(INT)GetCurReaderType()], (LPARAM)m_support_comm_type[(INT)GetCurCommType()]);

	return TRUE;
}

READER_TYPE	_This::GetCurReaderType()CONST
{
	CString csReaderType;
	LPTSTR szReader_Type;

	m_cbb_reader_type.GetWindowText(csReaderType);

	for (INT i = 0; szReader_Type = m_support_reader_type[i]; i++)
	{
		if (!_tcscmp(csReaderType, szReader_Type))
			return static_cast<READER_TYPE>(i);
	}

	return READER_TYPE::UNKOWN;
}

READER_TYPE	_This::SetCurReaderType(READER_TYPE ReaderType)
{
	ASSERT(ReaderType != READER_TYPE::UNKOWN);

	// 因加载的驱动可能少，可能多，依照枚举值选择不可靠
	CString lbtext;
	LPCTSTR szReaderType = m_support_reader_type[static_cast<INT>(ReaderType)];
	INT i = m_cbb_reader_type.GetCount();

	while (i--)
	{

		m_cbb_reader_type.GetLBText(i, lbtext);

		// 如果是目标读写器类型则退出循环
		if (!_tcscmp(lbtext, szReaderType))
			break;
	}

	if (m_cbb_reader_type.SetCurSel(i) != CB_ERR)
	{
		// 调整可用的通讯类型
		SendMessage(WM_COMMAND, MAKEWPARAM(CBB_READER_TYPE, CBN_SELCHANGE), reinterpret_cast<LPARAM>(m_cbb_reader_type.m_hWnd));
		return ReaderType;
	}

	return READER_TYPE::UNKOWN;
}

COMM_TYPE _This::GetCurCommType()CONST
{
	CString csCommType;
	LPTSTR szComm_Type;

	m_cbb_comm_type.GetWindowText(csCommType);


	for (INT i = 0; szComm_Type = m_support_comm_type[i]; i++)
	{
		if (!_tcscmp(csCommType, szComm_Type))
			return static_cast<COMM_TYPE>(i);
	}

	return COMM_TYPE::UNKOWN;
}

COMM_TYPE _This::SetCurCommType(COMM_TYPE CommType)
{
	LPCTSTR szCommType = m_support_comm_type[static_cast<INT>(CommType)];

	INT i = m_cbb_comm_type.GetCount();

	while (i--)
	{
		CString lbText;
		m_cbb_comm_type.GetLBText(i, lbText);

		if (!_tcscmp(lbText, szCommType))
		{
			break;
		}
	}

	COMM_TYPE ret = static_cast<COMM_TYPE>(m_cbb_comm_type.SetCurSel(i));
	//OnCbnSelchangeCommType();

	return ret;
}

void _This::OnCbnSelchangeReaderType()
{
	FLAG_T CommTypeSupported = NULL;

	// 保存已选项
	COMM_TYPE saved = GetCurCommType();

	if (saved == COMM_TYPE::UNKOWN)
	{
		saved = (COMM_TYPE)0;
	}

	// 清空项
	m_cbb_comm_type.ResetContent();

	READER_TYPE CurReaderType = GetCurReaderType();

	if (CurReaderType != READER_TYPE::UNKOWN)
	{
		CommTypeSupported = m_driver_info_list.ElementAt((INT)CurReaderType).CommTypeSupported;
	}

	if ((CommTypeSupported & COMMTYPE_COM_EN) != 0)
	{
		m_cbb_comm_type.AddString(_T(CONNSTR_NAME_COMMTYPE_COM));
	}
	if ((CommTypeSupported & COMMTYPE_USB_EN) != 0)
	{
		m_cbb_comm_type.AddString(_T(CONNSTR_NAME_COMMTYPE_USB));
	}
	if ((CommTypeSupported & COMMTYPE_NET_EN) != 0)
	{
		m_cbb_comm_type.AddString(_T(CONNSTR_NAME_COMMTYPE_NET));
	}
	if ((CommTypeSupported & COMMTYPE_BLUETOOTH_EN) != 0)
	{
		m_cbb_comm_type.AddString(_T(CONNSTR_NAME_COMMTYPE_BLUETOOTH));
	}

	if (m_cbb_comm_type.SetCurSel((INT)saved) == (INT)COMM_TYPE::UNKOWN)
	{
		m_cbb_comm_type.SetCurSel(0);
	}


}

void _This::OnCbnSelchangeCommType()
{
	COMM_TYPE comm_type = GetCurCommType();

	CCommPortUI *CommPort_temp = NULL;

	switch (comm_type)
	{
	case COMM_TYPE::COM:
		CommPort_temp = static_cast<CCommPortUI*>(new CCOMPortUI(this));
		((CCOMPortUI*)CommPort_temp)->Create(DG_COMM_PORT_POS);

		break;

	case COMM_TYPE::USB:
		CommPort_temp = static_cast<CCommPortUI*>(new CUSBPortUI(this));
		((CUSBPortUI*)CommPort_temp)->Create(DG_COMM_PORT_POS);


		break;

	default:
		CommPort_temp = static_cast<CCommPortUI*>(new CUSBPortUI(this));
		((CUSBPortUI*)CommPort_temp)->Create(DG_COMM_PORT_POS);

		break;
	}

	m_CommPort->Hid();
	CommPort_temp->Show();
	CommPort_temp->Update();
	m_CommPort->Destroy();
	m_CommPort = CommPort_temp;
}

BOOL _This::GetConnstr(CString& Connstr)
{
	Connstr = _T("");

	Connstr.Append(
		// RDType=XXXX；CommType=XXX;AddrMode=X;SerNum=XXXXXXXXXX;
		_T(CONNSTR_NAME_RDTYPE) _T("=") + CString(m_support_reader_type[(INT)GetCurReaderType()]) + _T(";")
		_T(CONNSTR_NAME_COMMTYPE) _T("=") +  CString(m_support_comm_type[(INT)GetCurCommType()]) + _T(";")
		);
	m_CommPort->GetParams(Connstr);

	return TRUE;
}


// CReaderUI 消息处理程序
INT _This::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	_Base::OnCreate(lpCreateStruct);

	//m_bn_config_save = new CButton();

	BOOL ret = m_lb_reader_type.Create(
		LB_READER_TYPE_TEXT,
		WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		LB_READER_TYPE_POS,
		this
		);

	ASSERT(ret != 0);

	ret = m_lb_comm_type.Create(
		LB_COMM_TYPE_TEXT,
		WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		LB_COMM_TYPE_POS,
		this
		);

	ASSERT(ret != 0);

	ret = m_cbb_reader_type.Create(
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CBB_READER_TYPE_POS,
		this,
		CBB_READER_TYPE
		);

	ASSERT(ret != 0);

	ret = m_cbb_comm_type.Create(
		WS_TABSTOP | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CBB_COMM_TYPE_POS,
		this,
		CBB_COMM_TYPE
		);

	ASSERT(ret != 0);

	// mfc 动态创建的按键设置为默认按键
	ret = m_bn_open.CreateEx(
		0,
		WC_BUTTON,
		BN_OPEN_TEXT,
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		CRect(BN_OPEN_POS),
		this,
		BN_OPEN
		);

	ASSERT(ret != 0);

	ret = m_bn_close.CreateEx(
		0,
		WC_BUTTON,
		BN_CLOSE_TEXT,
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		CRect(BN_CLOSE_POS),
		this,
		BN_CLOSE
		);

	ASSERT(ret != 0);
	
	ret = m_bn_config_load_file.CreateEx(
		0,
		WC_BUTTON,
		BN_CONFIG_LOAD_FILE_TEXT,
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		CRect(BN_CONFIG_LOAD_FILE_POS),
		this,
		BN_CONFIG_LOAD_FILE
		);

	ASSERT(ret != 0);

	ret = m_bn_config_save_file.CreateEx(
		0,
		WC_BUTTON,
		BN_CONFIG_SAVE_FILE_TEXT,
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		CRect(BN_CONFIG_SAVE_FILE_POS),
		this,
		BN_CONFIG_SAVE_FILE
		);

	ASSERT(ret != 0);

	ret = m_bn_config_read.Create(
		BN_CONFIG_READ_TEXT,
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		CRect(BN_CONFIG_READ_POS),
		this,
		BN_CONFIG_READ
		);

	ASSERT(ret != 0);

	ret = m_bn_config_write.Create(
		BN_CONFIG_WRITE_TEXT,
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		CRect(BN_CONFIG_WRITE_POS),
		this,
		BN_CONFIG_WRITE
		);
	ASSERT(ret != 0);

	ret = m_bn_config_save.CreateEx(
		0,
		WC_BUTTON,
		BN_CONFIG_SAVE_TEXT,
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		CRect(BN_CONFIG_SAVE_POS),
		this,
		BN_CONFIG_SAVE
		);

	ASSERT(ret != 0);

	ret = m_bn_config_reset.CreateEx(
		0,
		WC_BUTTON,
		BN_CONFIG_RESET_TEXT,
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		CRect(BN_CONFIG_RESET_POS),
		this,
		BN_CONFIG_RESET
		);

	ASSERT(ret != 0);

	ret = m_cbb_config_start.Create(
		WS_VSCROLL | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CBB_CONFIG_START_POS,
		this,
		CBB_CONFIG_START
		);
	ASSERT(ret != 0);

	ret = m_cbb_config_count.Create(
		WS_VSCROLL | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CBB_CONFIG_COUNT_POS,
		this,
		CBB_CONFIG_COUNT
		);

	ASSERT(ret != 0);

	ret = m_lb_config_start.Create(
		LB_CONFIG_START_TEXT,
		WS_CHILD | WS_VISIBLE,
		LB_CONFIG_START_POS,
		this
		);

	ASSERT(ret != 0);

	ret = m_lb_config_count.Create(
		LB_CONFIG_COUNT_TEXT,
		WS_CHILD | WS_VISIBLE,
		LB_CONFIG_COUNT_POS,
		this
		);
	
	ASSERT(ret != 0);

	ret = m_lb_config_size_per_block.Create(
		LB_CONFIG_SIZE_PER_BLOCK_TEXT,
		WS_CHILD | WS_VISIBLE,
		LB_CONFIG_SIZE_PER_BLOCK_POS,
		this
		);

	ASSERT(ret != 0);

	ret = m_cbb_config_size_per_block.Create(
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		CBB_CONFIG_SIZE_PER_BLOCK_POS,
		this,
		CBB_CONFIG_SIZE_PER_BLOCK
		);

	ASSERT(ret != 0);

	m_bn_config_reset.SetFont(m_pFont);
	m_bn_config_load_file.SetFont(m_pFont);
	m_bn_config_save_file.SetFont(m_pFont);
	m_cbb_config_size_per_block.SetFont(m_pFont);
	m_lb_config_size_per_block.SetFont(m_pFont);
	m_bn_config_save.SetFont(m_pFont);
	m_lb_config_start.SetFont(m_pFont);
	m_lb_config_count.SetFont(m_pFont);
	m_bn_config_read.SetFont(m_pFont);
	m_bn_config_write.SetFont(m_pFont);
	m_cbb_config_start.SetFont(m_pFont);
	m_cbb_config_count.SetFont(m_pFont);
	m_lb_reader_type.SetFont(m_pFont);
	m_lb_comm_type.SetFont(m_pFont);
	m_cbb_reader_type.SetFont(m_pFont);
	m_cbb_comm_type.SetFont(m_pFont);
	m_bn_open.SetFont(m_pFont);
	m_bn_close.SetFont(m_pFont);

	m_bn_close.EnableWindow(FALSE);
	m_bn_config_read.EnableWindow(FALSE);
	m_bn_config_write.EnableWindow(FALSE);
	m_bn_config_save.EnableWindow(FALSE);
	m_bn_config_load_file.EnableWindow(FALSE);
	m_bn_config_save_file.EnableWindow(FALSE);
	m_bn_config_reset.EnableWindow(FALSE);
	return 0;
}

VOID _This::OnDestroy()
{
	_Base::OnDestroy();
}


BOOL _This::OnCommand(WPARAM wParam,LPARAM lParam)
{
	INT wmId = LOWORD(wParam);
	INT wmEvent = HIWORD(wParam);

	switch (wmId)
	{
	// 自行处理的事件
	case CBB_READER_TYPE:
		break;


	case CBB_COMM_TYPE:


		break;
	default:
		return m_pParent->PostMessage(WM_COMMAND, wParam, lParam);
	}

	return _Base::OnCommand(wParam, lParam);
}