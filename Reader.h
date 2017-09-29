//
///*
//	本模块主要功能：
//	1：创建时遍历已加载的驱动并加入到 CBB_READER_TYPE 中
//	2：支持动态选择读写器类型和通讯类型
//
//*/
//
//#pragma once
//#include "Resource.h"
//#include "rfidlib.h"
//
//#define SUPPORT_READER_TYPE		\
//	_T("M201"),		\
//	_T("MF102U"),	\
//	_T("RD242"),	\
//	_T("SSR100"),	\
//	_T("RD5100"),	\
//	_T("RL8000"),	\
//	_T("RPAN")
//
//
//#define SUPPORT_COMM_TYPE				\
//	_T(CONNSTR_NAME_COMMTYPE_COM),		\
//	_T(CONNSTR_NAME_COMMTYPE_USB),		\
//	_T(CONNSTR_NAME_COMMTYPE_NET),		\
//	_T(CONNSTR_NAME_COMMTYPE_BLUETOOTH)
//
//
//typedef enum class _READER_TYPE {
//	UNKOWN = -1,
//	M201 = 0,
//	MF102U,
//	RD242,
//	SSR100,
//	RD5100,
//	RL8000,
//	RPAN,
//}READER_TYPE;
//
//typedef enum class _COMM_TYPE {
//	UNKOWN = -1,
//	COM = 0,
//	USB,
//	NET,
//	BLUETOOTH,
//}COMM_TYPE;
//
//typedef enum class _ERROR_TYPE {
//	Internal = 0x80000000i32,
//	OpenFailed,
//	Param,
//	Unkown = -1,
//	NoMatter = 0,
//}ERROR_TYPE;
//
//class CTagReader 
//	: public CDialog
//{
//
//	DECLARE_DYNAMIC(CTagReader)
//	
//private:
//	typedef struct _RDRDVR_INFO
//	{
//		CString reader_type;
//		ID driver_id;
//		FLAG_T comm_type_supported;
//	}RDRDVR_INFO, *LPRDRDVR_INFO;
//	
//public:
//
//	CTagReader(CWnd* pParent = NULL);   // 标准构造函数
//	virtual ~CTagReader();
//
//	enum { IDD = PAGE_READER };
//private:
//	// UI成员
//	CComboBox				 m_cbb_reader_type;
//	CComboBox				 m_cbb_comm_type;
//	CWnd					*m_parent;
//	CString					 m_comm_params;
//
//	// 驱动属性
//	LPRDRDVR_INFO			 m_reader_driver_info_list;
//	INT						 m_driver_count;
//	CTagComm				*m_comm_port;
//
//	// 读写器成员
//	RFID_READER_HANDLE		 m_hReader;					// 读写器句柄
//	RFID_TAG_HANDLE			 m_hTag;					// 标签句柄
//	RFID_DN_HANDLE			 m_dnInvenParamList;		// 盘点参数列表句柄
//	INT						 m_TotalCount;				// 读取到的标签的总数
//	BYTE					 m_AFI;
//	DWORD					 m_dwAntennaInterfaceCount;
//	//CArray<CTag>			*m_cTags;
//	//static CONST PTCHAR		m_support_reader_type[];
//	//static CONST PTCHAR		m_support_comm_type[];
//private:
//
//
//public:
//	READER_TYPE	GetCurReaderType()CONST;
//	COMM_TYPE	GetCurCommType()CONST;
//	//COMM_TYPE	GetCurCommType()CONST;
//	COMM_TYPE GetSupportAIPType();
//	READER_TYPE	SetCurReaderType(READER_TYPE ReaderType);
//	COMM_TYPE	SetCurCommType(COMM_TYPE commType);
//
//	ERROR_TYPE Open();
//	ERROR_TYPE Inventory();
//	ERROR_TYPE OpenTag();
//	ERROR_TYPE WriteTagData();
//	ERROR_TYPE ReadTagData();
//
//protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
//	virtual BOOL OnInitDialog();
//	afx_msg void OnCbnSelchangeReaderType();
//	afx_msg void OnCbnSelchangeCommType();
//
//	DECLARE_MESSAGE_MAP()
//};
//
//
