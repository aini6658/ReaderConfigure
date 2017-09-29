
// ConfigurationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "App.h"
#include "Main.h"
#include "afxdialogex.h"
//#include "AWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef CConfigurationDlg	_This;
typedef CDialogEx			_Base;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg 
	: public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConfigurationDlg �Ի���



CConfigurationDlg::CConfigurationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigurationDlg::IDD, pParent),
	m_readerUI(NULL)
{
	m_IsOpened = FALSE;
	IfAutoOpen = FALSE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_config_blocks = (PBYTE)malloc(16 * 32);
	ZeroMemory(m_config_blocks, 16 * 32);
}

CConfigurationDlg::~CConfigurationDlg()
{
	if (m_config_blocks)
	{
		free(m_config_blocks);
		m_config_blocks = NULL;
	}
}

void CConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, ED_HEXT_EDIT, m_ed_hex_edit);
	DDX_Control(pDX, LB_SHOW, m_lb_show);
}

BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	//ON_MESSAGE(WM_COMMAND,)
	ON_BN_CLICKED(BN_OPEN, OnBnClickedBnOpen)
	ON_BN_CLICKED(BN_CLOSE, OnBnClickedBnClose)

	ON_BN_CLICKED(BN_CONFIG_READ, OnBnClickedBnConfigRead)
	ON_BN_CLICKED(BN_CONFIG_WRITE, OnBnClickedBnConfigWrite)
	ON_BN_CLICKED(BN_CONFIG_SAVE, OnBnClickedBnConfigSave)
	ON_CBN_SELCHANGE(CBB_CONFIG_SIZE_PER_BLOCK, OnEnChangeCOnfigSizePerBlock)
	ON_CBN_SELCHANGE(CBB_CONFIG_START, OnEnChangeCOnfigStart)
	ON_CBN_SELCHANGE(CBB_CONFIG_COUNT, OnEnChangeCOnfigCount)
	ON_BN_CLICKED(BN_CONFIG_LOAD_FILE, OnBnClickedBnConfigLoadFile)
	ON_BN_CLICKED(BN_CONFIG_SAVE_FILE, OnBnClickedBnConfigSaveFile)
	ON_BN_CLICKED(BN_CONFIG_RESET, OnBnClickedBnConfigReset)

	
	ON_WM_TIMER()
END_MESSAGE_MAP()

//extern CApp theApp;
// CConfigurationDlg ��Ϣ�������

BOOL CConfigurationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	CRect rect;
	GetClientRect(&rect);

	m_readerUI = new CReaderUI(this);
	BOOL X = m_readerUI->Create(CRect(0, 0, 160, rect.Height()));

	m_readerUI->SetDriverList(m_reader.GetDriverInfoList());

	TCHAR buf[32];
	for (INT i = 1; i < 16; i++)
	{
		_itot_s(i, buf, 32, 10);
		m_readerUI->m_cbb_config_size_per_block.AddString(buf);
		m_readerUI->m_cbb_config_size_per_block.SetCurSel(8-1);
	}
	for (INT i = 0; i < 32; i++)
	{
		_itot_s(i, buf, 32, 10);
		m_readerUI->m_cbb_config_start.AddString(buf);
		m_readerUI->m_cbb_config_start.SetCurSel(0);
	}

	for (INT i = 1; i < 33; i++)
	{
		_itot_s(i, buf, 32, 10);
		m_readerUI->m_cbb_config_count.AddString(buf);
		m_readerUI->m_cbb_config_count.SetCurSel(0);
	}
	
	m_ed_hex_edit.m_sa =0 ;

	OnEnChangeCOnfigSizePerBlock();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// No Ok or Cancel Button
void _This::OnClose(){
	_Base::OnCancel();
}
void _This::OnCancel(){}

void _This::OnOK()
{
	//OnBnClickedBnOpen();
}

void CConfigurationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CConfigurationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CConfigurationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void _This::OnBnClickedBnOpen()
{
	
	if (!m_IsOpened)
	{
		CString Connstr;
		m_readerUI->GetConnstr(Connstr);

		if (NOERROR == m_reader.Open(Connstr))
		{
			m_IsOpened = TRUE;
			//m_readerUI->m_bn_open.SetWindowText(BN_CLOSE_TEXT);
			m_readerUI->m_bn_open.EnableWindow(FALSE);
			m_readerUI->m_bn_close.EnableWindow(TRUE);
			m_readerUI->m_bn_config_read.EnableWindow(TRUE);
			m_readerUI->m_bn_config_write.EnableWindow(TRUE);
			m_readerUI->m_bn_config_save.EnableWindow(TRUE);
			m_readerUI->m_bn_config_load_file.EnableWindow(TRUE);
			m_readerUI->m_bn_config_save_file.EnableWindow(TRUE);
			m_readerUI->m_bn_config_reset.EnableWindow(TRUE);
			SetTimer(1, 200, NULL);
			
			return;
		}

		ShowMessage(_T("Reader Open Failed!"));
		return;
	}
	
	ShowMessage(_T("Reader is already Open!"));
	return;
}

void _This::OnBnClickedBnClose()
{
	m_reader.Close();
	m_IsOpened = FALSE;

	KillTimer(1);
	//IfAutoOpen = FALSE;
	m_readerUI->m_bn_open.EnableWindow(TRUE);
	m_readerUI->m_bn_close.EnableWindow(FALSE);
	m_readerUI->m_bn_config_read.EnableWindow(FALSE);
	m_readerUI->m_bn_config_write.EnableWindow(FALSE);
	m_readerUI->m_bn_config_save.EnableWindow(FALSE);
	m_readerUI->m_bn_config_load_file.EnableWindow(FALSE);
	m_readerUI->m_bn_config_save_file.EnableWindow(FALSE);
	m_readerUI->m_bn_config_reset.EnableWindow(FALSE);
	
}

void _This::OnBnClickedBnConfigRead()
{
	CString buf;

	m_readerUI->m_cbb_config_start.GetWindowText(buf);
	INT nAddr = _ttoi(buf);

	m_readerUI->m_cbb_config_count.GetWindowText(buf);
	INT nCount = _ttoi(buf);

	m_readerUI->m_cbb_config_size_per_block.GetWindowText(buf);
	INT nSize = _ttoi(buf);

	err_t ret = m_reader.GetConfigBlock(m_config_blocks + nAddr*nSize, nAddr, nCount, nSize);

	if (ret != NOERROR)
	{
		ShowMessage(_T("Read ConfigBlocks Failed!"));
	}
	else {

		m_ed_hex_edit.m_sa = nAddr;
		m_ed_hex_edit.m_bpr = nSize;

		m_ed_hex_edit.SetData(m_config_blocks + nAddr*nSize, nCount*nSize) ;
		m_ed_hex_edit.RedrawWindow();

		ShowMessage(_T("Read ConfigBlocks succeeded!"));
	}

}

void _This::OnBnClickedBnConfigWrite()
{
	CString buf;

	m_readerUI->m_cbb_config_start.GetWindowText(buf);
	INT nAddr = _ttoi(buf);

	m_readerUI->m_cbb_config_count.GetWindowText(buf);
	INT nCount = _ttoi(buf);

	m_readerUI->m_cbb_config_size_per_block.GetWindowText(buf);
	INT nSize = _ttoi(buf);

	m_ed_hex_edit.GetData(m_config_blocks + nAddr * nSize, 0, nCount * nSize);

	err_t ret = m_reader.SetConfigBlock(m_config_blocks + nAddr * nSize, nAddr, nCount, nSize);

	if (ret != NOERROR)
	{
		ShowMessage(_T("Write ConfigBlocks Failed!"));
	}
	else
	{
		ShowMessage(_T("Write ConfigBlocks succeeded!"));
	}
}

void _This::OnBnClickedBnConfigSave()
{
	CString buf;

	m_readerUI->m_cbb_config_start.GetWindowText(buf);
	INT nAddr = _ttoi(buf);

	m_readerUI->m_cbb_config_count.GetWindowText(buf);
	INT nCount = _ttoi(buf);


	err_t ret = m_reader.SaveConfigBlock(nAddr,nCount);
	
	if (ret != NOERROR)
	{
		ShowMessage(_T("Save ConfigBlocks Failed!"));
	}
	else
	{
		ShowMessage(_T("Save ConfigBlocks succeeded!"));
	}
}

void _This::OnBnClickedBnConfigReset()
{
	if (m_reader.ResetConfig() != S_OK)
	{
		ShowMessage(_T("Reset ConfigBlocks Failed!"));
	}
	else
	{
		ShowMessage(_T("Reset ConfigBlocks succeeded!"));
	}
}

void _This::OnEnChangeCOnfigSizePerBlock()
{
	CString buf;

	m_readerUI->m_cbb_config_start.GetWindowText(buf);
	INT nAddr = _ttoi(buf);

	m_readerUI->m_cbb_config_count.GetWindowText(buf);
	INT nCount = _ttoi(buf);

	m_readerUI->m_cbb_config_size_per_block.GetWindowText(buf);
	INT nSize = _ttoi(buf);

	m_ed_hex_edit.m_sa = nAddr;
	m_ed_hex_edit.m_bpr = nSize;

	m_ed_hex_edit.SetData(m_config_blocks + nAddr*nSize, nCount * nSize);
	m_ed_hex_edit.RedrawWindow();
}

void _This::OnEnChangeCOnfigStart()
{
	CString buf;
	TCHAR temp[32];
	INT x;
	m_readerUI->m_cbb_config_start.GetWindowText(buf);
	INT nAddr = _ttoi(buf);

	m_readerUI->m_cbb_config_count.GetWindowText(buf);
	INT nCount = _ttoi(buf);

	m_readerUI->m_cbb_config_size_per_block.GetWindowText(buf);
	INT nSize = _ttoi(buf);

	m_readerUI->m_cbb_config_count.ResetContent();

	for (INT i = 1; i < (33 - nAddr); i++)
	{
		_itot_s(i, temp, 32, 10);
		m_readerUI->m_cbb_config_count.AddString(temp);
	}

	if (nCount < m_readerUI->m_cbb_config_count.GetCount())
	{
		_itot_s(nCount, temp, 32, 10);
		x = m_readerUI->m_cbb_config_count.SelectString(-1, temp);
	}
	else
	{
		m_readerUI->m_cbb_config_count.SetCurSel(0);
		OnEnChangeCOnfigCount();
		return;
	}
	
	m_ed_hex_edit.m_sa = nAddr;

	m_ed_hex_edit.SetData(m_config_blocks + nAddr * nSize, nCount * nSize);
	m_ed_hex_edit.RedrawWindow();

}

void _This::OnEnChangeCOnfigCount()
{
	CString buf;

	m_readerUI->m_cbb_config_start.GetWindowText(buf);
	INT nAddr = _ttoi(buf);

	m_readerUI->m_cbb_config_count.GetWindowText(buf);
	INT nCount = _ttoi(buf);

	m_readerUI->m_cbb_config_size_per_block.GetWindowText(buf);
	INT nSize = _ttoi(buf);

	m_ed_hex_edit.SetData(m_config_blocks + nAddr * nSize, nCount * nSize);
	m_ed_hex_edit.RedrawWindow();
}

void _This::OnBnClickedBnConfigLoadFile()
{
	CStringA Text;

	INT BlockStart = -1;
	INT BlokNumber;
	INT BlokSize;

	CString csFilePath;

	TCHAR szFilter[] = _T("Configure file(*.xml)|*.xml|All file(*.*)|*.*||");

	CFileDialog FileDlg(TRUE, _T("xml"), _T("ConfigFile"), 0, szFilter, this);

	if (FileDlg.DoModal() != IDOK){return;}

	csFilePath = FileDlg.GetPathName();

	HANDLE hFile = ::CreateFile(
		csFilePath,
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		ShowMessage(_T("CreateFile Failed!"));
		return;
	}

	DWORD nLen;

	nLen = (UINT)::GetFileSize(hFile, NULL);

	if (nLen == 0)
	{
		ShowMessage(_T("This ConfigFile With Zero Size!"));
		return;
	}

	Text.Preallocate(nLen);

	::ReadFile(hFile, Text.GetBuffer(), Text.GetAllocLength(), &nLen, NULL);

	LPSTR pos;

	if ((pos = strstr(Text.GetBuffer(),("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>") ))== NULL)
	{
		ShowMessage(_T("Unkown XML Format!"));
		::CloseHandle(hFile);
		return;
	}

	pos += sizeof("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>") - 1;

	LPSTR pos_s;
		
	pos_s = strstr(pos, "<BlockCfg DeviceType=\"");

	if (pos_s == NULL)return;

	pos_s += sizeof("<BlockCfg DeviceType=\"") - 1;

	pos = strstr(pos_s, "\">");

	if (pos == NULL)return;

	INT DeviceType = strtol(pos_s, &pos, 10);

	//pos_s = pos + sizeof("\">") - 1;

	CString DeviceInfo;
	DeviceInfo.Preallocate(128);
	DWORD nSize = DeviceInfo.GetAllocLength();
	err_t ret = m_reader.GetReaderInfo(DeviceInfo.GetBuffer(), &nSize);
	DeviceInfo.ReleaseBuffer();
	INT ds = DeviceInfo.Find(_T(';')) + 1;
	INT de = DeviceInfo.Find(_T(';'), ds);
	INT i;
	CHAR dt[16];

	// ʡȥ�ַ�ת��
	for (i = 0; i < (de - ds); i++)
	{
		dt[i] = (CHAR)(DeviceInfo.GetBuffer())[ds + i];
	}

	dt[i] = '\0';

	// ����豸�����Ƿ����
	if (strtol(dt, NULL, 10) != DeviceType)
	{
		ShowMessage(_T("Device Type Error!"));
		::CloseHandle(hFile);
		return;
	}

	for (INT i = 0; pos != NULL; i++)
	{
		pos_s = strstr(pos, "<BlockBuffer No=\"");

		if (pos_s == NULL)break;
		pos_s += sizeof("<BlockBuffer No=\"") - 1;

		pos = strstr(pos_s, "\">");

		if (pos == NULL)break;
		// ���ַ�㳤��
		if ((pos - pos_s) == 0)break;

		BlokNumber = strtol(pos_s, &pos, 10);
		if (BlockStart == -1)BlockStart = BlokNumber;

		pos_s = (pos + sizeof("\">") - 1);

		pos = strstr(pos_s, "</BlockBuffer>");

		BlokSize = (pos - pos_s) >> 1;

		CHAR temp[3] = "00";
		PBYTE data_ptr = m_config_blocks + BlockStart*BlokSize;

		for (INT j = 0; j < BlokSize; j++)
		{
			temp[0] = pos_s[j*2];
			temp[1] = pos_s[j*2+1];
			data_ptr[i*BlokSize+j]=(BYTE)strtol(temp, NULL, 16);
		}
	}

	pos += sizeof("</BlockBuffer>") - 1;
	pos = strstr(pos, "</BlockCfg>");

	::CloseHandle(hFile);

	if (pos == 0)
	{
		ShowMessage(_T("Not a vaild config file��"));
	}

	TCHAR buf[32];

	_itot_s(BlokNumber - BlockStart + 1, buf, 32, 10);
	m_readerUI->m_cbb_config_count.SelectString(-1, buf);

	_itot_s(BlokSize, buf, 32, 10);
	m_readerUI->m_cbb_config_size_per_block.SelectString(-1, buf);

	_itot_s(BlockStart, buf, 32, 10);
	m_readerUI->m_cbb_config_start.SelectString(-1, buf);

	m_ed_hex_edit.m_sa = BlockStart;
	m_ed_hex_edit.m_bpr = BlokSize;

	m_ed_hex_edit.SetData(m_config_blocks + BlockStart * BlokSize, (BlokNumber - BlockStart + 1)* BlokSize);
	m_ed_hex_edit.RedrawWindow();

}


void _This::OnBnClickedBnConfigSaveFile()
{
	CString csFilePath;

	TCHAR szFilter[] = _T("�����ļ�(*.xml)|*.xml|�����ļ�(*.*)|*.*||");

	CFileDialog FileDlg(FALSE, _T("xml"), _T("ConfigFile"), OFN_OVERWRITEPROMPT, szFilter, this);

	FileDlg.m_ofn.lpstrTitle = _T("Save");


	if (FileDlg.DoModal() != IDOK){ return; }

	CString DeviceInfo;
	DeviceInfo.Preallocate(128);
	DWORD nSize = DeviceInfo.GetAllocLength();
	err_t ret = m_reader.GetReaderInfo(DeviceInfo.GetBuffer(), &nSize);
	DeviceInfo.ReleaseBuffer();
	INT ds = DeviceInfo.Find(_T(';')) + 1;
	INT de = DeviceInfo.Find(_T(';'), ds);
	CHAR DeviceType[16];
	INT i = 0;

	for (; i < (de - ds); i++)
	{
		DeviceType[i] = (CHAR)DeviceInfo.GetBuffer()[ds + i];
	}

	DeviceType[i] = '\0';

	if (ret == S_OK)
	{
		CStringA outbuf =
			"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\r\n"
			"<BlockCfg DeviceType=\"" + CStringA(DeviceType) + "\">\r\n"
			;

		csFilePath = FileDlg.GetPathName();

		HANDLE hFile = ::CreateFile(
			csFilePath,
			GENERIC_WRITE,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			ShowMessage(_T("CreateFile Failed!"));
			return;
		}

		CString buf;

		m_readerUI->m_cbb_config_start.GetWindowText(buf);
		INT nAddr = _ttoi(buf);

		m_readerUI->m_cbb_config_count.GetWindowText(buf);
		INT nCount = _ttoi(buf);

		m_readerUI->m_cbb_config_size_per_block.GetWindowText(buf);
		nSize = _ttoi(buf);

		ret = m_ed_hex_edit.GetData(m_config_blocks + nAddr*nSize, 0, nCount*nSize);
		//ret = m_reader.GetConfigBlock(m_config_blocks + nAddr*nSize, nAddr, nCount, nSize);

		if (ret != nCount*nSize)
		{
			ShowMessage(_T("Update buffer Failed!"));
			::CloseHandle(hFile);
			return;
		}

		for (INT i = 0; i < nCount; i++)
		{
			CStringA datas = "";

			PBYTE data_ptr = m_config_blocks + nAddr*nSize;

			for (INT j = 0; j < (INT)nSize; j++)
			{
				datas.AppendFormat("%.2X", data_ptr[i*nSize + j]);
			}

			outbuf.AppendFormat(
				"    <BlockBuffer No=\"%d\">%s</BlockBuffer>\r\n",
				nAddr + i,
				datas
				);
		}

		outbuf += "</BlockCfg>\r\n";
		outbuf.ReleaseBuffer();

		DWORD nSize = 0;

		::WriteFile(hFile, outbuf, outbuf.GetLength(), &nSize, NULL);

		::CloseHandle(hFile);

		return;
	}

	ShowMessage(_T("RDR_GetReaderInfor Failed!"));
}

void _This::ShowMessage(LPCTSTR msg)
{
	CString str = msg; //��ȡϵͳʱ�� ����

	CTime tm = CTime::GetCurrentTime();

	str += tm.Format("\n%Y-%m-%d  %H-%M-%S");

	m_lb_show.SetWindowText(str);
}


void CConfigurationDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_IsOpened)
	{
		TCHAR buf[1];
		DWORD nSize = 1;

		//if ()
		INT ret = m_reader.GetReaderInfo(buf, &nSize);

		if (ret != S_OK)
		{
			m_reader.Close();
			m_IsOpened = FALSE;

			m_readerUI->m_bn_open.EnableWindow(TRUE);
			m_readerUI->m_bn_close.EnableWindow(FALSE);
			m_readerUI->m_bn_config_read.EnableWindow(FALSE);
			m_readerUI->m_bn_config_write.EnableWindow(FALSE);
			m_readerUI->m_bn_config_save.EnableWindow(FALSE);
			m_readerUI->m_bn_config_load_file.EnableWindow(FALSE);
			m_readerUI->m_bn_config_save_file.EnableWindow(FALSE);
			m_readerUI->m_bn_config_reset.EnableWindow(FALSE);
		}
	}
	else
	{

		CString Connstr;
		m_readerUI->GetConnstr(Connstr);

		if (NOERROR == m_reader.Open(Connstr))
		{
			m_IsOpened = TRUE;
			//m_readerUI->m_bn_open.SetWindowText(BN_CLOSE_TEXT);
			m_readerUI->m_bn_open.EnableWindow(FALSE);
			m_readerUI->m_bn_close.EnableWindow(TRUE);
			m_readerUI->m_bn_config_read.EnableWindow(TRUE);
			m_readerUI->m_bn_config_write.EnableWindow(TRUE);
			m_readerUI->m_bn_config_save.EnableWindow(TRUE);
			m_readerUI->m_bn_config_load_file.EnableWindow(TRUE);
			m_readerUI->m_bn_config_save_file.EnableWindow(TRUE);
			m_readerUI->m_bn_config_reset.EnableWindow(TRUE);
			return;
		}

		ShowMessage(_T("Reader Open Failed!"));
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	CDialogEx::OnTimer(nIDEvent);
}
