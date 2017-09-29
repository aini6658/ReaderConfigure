#include "stdafx.h"
#include "ConfigurationPageUI.h"
#include "CReaderUI.h"
#include <tchar.h>

typedef CConfigurationPageUI			_This;
typedef CMFCPropertyGridCtrl			_Base;

IMPLEMENT_DYNAMIC(CConfigurationPageUI, CMFCPropertyGridCtrl)

BEGIN_MESSAGE_MAP(CConfigurationPageUI, CMFCPropertyGridCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()

#pragma comment(lib,"SQLite3.lib")

CConfigurationPageUI::CConfigurationPageUI(CWnd *pParent)
	:CMFCPropertyGridCtrl()
{

	if (sqlite3_open16(".\\Configration.DB",&m_DB) != SQLITE_OK)
	{
		sqlite3_close(m_DB);
	}
	//sqlite3_stmt *pstmt;
	//LPCWSTR tail;
	//LPSTR errmsg;

	//err_t ret;
	//ret = sqlite3_prepare16(m_DB,
	//	"create table M201("
	//	"root_id INT PRIMARY KEY NOT NULL,"
	//	"parent_id INT NOT NULL,"
	//	"name TEXT NOT NULL,"
	//	"rang TEXT NOT NULL"
	//	");"
	//	"insert into M201 values(1,1,'通讯接口','-')",
	//	-1, &pstmt, (CONST VOID**)&tail
	//	);

	//sqlite3_errmsg16(m_DB);

	//ret = sqlite3_step(pstmt);
	
	m_pParent = pParent;
}

CConfigurationPageUI::~CConfigurationPageUI()
{
	sqlite3_close(m_DB);
}

BOOL _This::Create(CRect &rect)
{
	CRect parent_rect;

	m_pFont = ((CReaderUI*)m_pParent)->m_pFont;

	m_pParent->GetWindowRect(&parent_rect);

	if (!_Base::Create(WS_CHILD, rect, m_pParent, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	rect.right = parent_rect.right;
	rect.bottom = parent_rect.bottom;
	//ret = SetWindowPos(m_pParent, rect.left, rect.top, parent_rect.right, parent_rect.bottom, SWP_NOACTIVATE | SWP_NOZORDER);

	SetFont(m_pFont);
	ShowWindow(SW_SHOW);
	UpdateWindow();

	return TRUE;
}

INT _This::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	_Base::OnCreate(lpCreateStruct);

	EnableHeaderCtrl(FALSE);
	//EnableDescriptionArea();
	SetVSDotNetLook();
	MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("通讯接口"));
	CMFCPropertyGridProperty* pGroup11 = new CMFCPropertyGridProperty(_T("总线地址"),_T("1"));

	for (int i = 0; i < 256; i++)
	{
		TCHAR buf[32];

		_itot_s(i, buf, 32, 10);
		pGroup11->AddOption(buf);
	}

	pGroup1->AddSubItem(pGroup11);
	AddProperty(pGroup1);


	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("系统工作模式"));
	CMFCPropertyGridProperty* pGroup21 = new CMFCPropertyGridProperty(_T("工作模式"),_T("主机控制模式"));
	CMFCPropertyGridProperty* pGroup22 = new CMFCPropertyGridProperty(_T("扫描参数"));
	CMFCPropertyGridProperty* pGroup221 = new CMFCPropertyGridProperty(_T("数据块的开始地址"),_variant_t(0), _T("0"));
	CMFCPropertyGridProperty* pGroup222 = new CMFCPropertyGridProperty(_T("扫描数据块数量"),_T("8"));
	CMFCPropertyGridProperty* pGroup223 = new CMFCPropertyGridProperty(_T("扫描标签序列号"),_T("0"));
	CMFCPropertyGridProperty* pGroup224 = new CMFCPropertyGridProperty(_T("扫描数据块"),_T("0"));
	CMFCPropertyGridProperty* pGroup225 = new CMFCPropertyGridProperty(_T("扫描内容输出格式"),_T("0"));
	CMFCPropertyGridProperty* pGroup226 = new CMFCPropertyGridProperty(_T("分隔符类型"),_T("0"));
	CMFCPropertyGridProperty* pGroup227 = new CMFCPropertyGridProperty(_T("系统分隔符值"),_T("0"));
	CMFCPropertyGridProperty* pGroup228 = new CMFCPropertyGridProperty(_T("自定义分隔符值"),_T("0"));
	CMFCPropertyGridProperty* pGroup229 = new CMFCPropertyGridProperty(_T("结束符类型"),_T("0"));
	CMFCPropertyGridProperty* pGroup22A = new CMFCPropertyGridProperty(_T("系统结束符值"),_T("0"));
	CMFCPropertyGridProperty* pGroup22B = new CMFCPropertyGridProperty(_T("自定义结束符值"),_T("0"));

	pGroup21->AddOption(_T("主机控制模式"));
	pGroup21->AddOption(_T("扫描模式"));

	for (int i = 0; i < 256; i++)
	{
		TCHAR buf[32];

		_itot_s(i, buf, 32, 10);
		pGroup221->AddOption(buf);
	}

	pGroup22->AddSubItem(pGroup221);
	pGroup22->AddSubItem(pGroup222);
	pGroup22->AddSubItem(pGroup223);
	pGroup22->AddSubItem(pGroup224);
	pGroup22->AddSubItem(pGroup225);
	pGroup22->AddSubItem(pGroup226);
	pGroup22->AddSubItem(pGroup227);
	pGroup22->AddSubItem(pGroup228);
	pGroup22->AddSubItem(pGroup229);
	pGroup22->AddSubItem(pGroup22A);
	pGroup22->AddSubItem(pGroup22B);

	pGroup2->AddSubItem(pGroup21);
	pGroup2->AddSubItem(pGroup22);
	AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("射频功率"));

	CMFCPropertyGridProperty* pGroup31 = new CMFCPropertyGridProperty(_T("功率大小"), _T("0.75W"));
	pGroup31->AddOption(_T("0.25W"));
	pGroup31->AddOption(_T("0.50W"));
	pGroup31->AddOption(_T("0.75W"));
	pGroup31->AddOption(_T("1.00W"));
	pGroup31->AddOption(_T("1.25W"));
	pGroup31->AddOption(_T("1.50W"));

	pGroup3->AddSubItem(pGroup31);
	AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("空中协议参数"));
	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("ASK调制深度"), _T("OOK 100%"));
	CMFCPropertyGridProperty* pGroup42 = new CMFCPropertyGridProperty(_T("副载波"), _T("双副载波"));
	pGroup41->AddOption(_T("ASK 10%"));
	pGroup41->AddOption(_T("OOK 100%"));

	pGroup42->AddOption(_T("单副载波"));
	pGroup42->AddOption(_T("双副载波"));

	pGroup4->AddSubItem(pGroup41);
	pGroup4->AddSubItem(pGroup42);
	AddProperty(pGroup4);
	
	return 0;
}


