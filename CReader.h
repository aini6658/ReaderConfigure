#pragma once
#include "rfidlib.h"
#include "CTag.h"
#include <map>

typedef enum class _READER_TYPE {
	UNKOWN = -1,
	M201 = 0,
	RD120M,
	RD242,
	SSR100,
	RD5100,
	RL8000,
	RPAN,
}READER_TYPE;

typedef enum class _COMM_TYPE {
	UNKOWN = -1,
	COM = 0,
	USB,
	NET,
	BLUETOOTH,
}COMM_TYPE;

typedef enum class _AIP_TYPE {
	ISO14443A		= 1,
	ISO14443B		= 2,
	ISO15693		= 4,
	ISO18000p3m3	= 8,
}AIP_TYPE; 

typedef enum _SLOT_TYPE{
	SLOT_TYPE_DEFAULT		= 0,
	SLOT_TYPE_1				= 1,
	SLOT_TYPE_16			= 16,
}SLOT_TYPE;


typedef struct _DRIVERINFO
{
	CString DriverName;
	DWORD DriverID;
	DWORD CommTypeSupported;
}DRIVERINFO;

class CReader
{
public:
	class InvenParamStruct;
	class TagInfo;

public:
	CReader(void);
	~CReader(void);

private:

	

	CArray<DRIVERINFO>	 m_driver_info_list;			// 已加载的驱动的信息
	RFID_READER_HANDLE	 m_hReader;						// 读写器句柄
	RFID_TAG_HANDLE	     m_hTag;						// 标签句柄
	RFID_DN_HANDLE		 m_dnInvenParamList;			// 盘点参数列表句柄
	INT					 m_TotalCount;					// 读取到的标签的总数
	BYTE				 m_AFI;
	DWORD				 m_dwAntennaInterfaceCount;
	CArray<CTag>		*m_cTags;

	INT					 m_cinfg_addr;		// 写入并未保存的块开始地址
	INT					 m_cinfg_count;		// 写入并未保存的块长度
	INT					 m_cinfg_size;		// 写入并未保存的块的尺寸

public:
	CArray<DRIVERINFO>* GetDriverInfoList();
	// 打开设备
	err_t Open(const CString& ConnectStr);

	static err_t Enum(LPCTSTR DevID, COMM_TYPE CommType = COMM_TYPE::USB);

	err_t GetReaderInfo(LPTSTR buf,PDWORD nSize);

	// 关闭设备
	err_t Close();

	// 获得天线数量
	INT GetAntCount();

	// 获取空中协议名称
	err_t GetTagAIPName(CTag cTag, PVOID pBuf, SIZE_T* nSize);

	// 获取标枪类型名称
	err_t GetTagTypeName(CTag cTag, PVOID pBuf, SIZE_T* nSize);

	// 创建盘点参数列表
	err_t CreatInvenParamList();

	// 销毁盘点参数列表
	err_t DestroyInvenParamList();

	// 连接到标签
	err_t TagConnect(DWORD TagType, BYTE AddrMOde, BYTE uid[]);

	// 读取标签块
	err_t TagReadBlock(DWORD dwBlockAddr, DWORD dwBlockCount, PVOID buff, INT nMaxSize);

	// 写标签块
	err_t TagWriteBlock(DWORD dwBlockAddr, DWORD dwBlockCount, PVOID buff, INT nWrtten);


	// 写AFI
	err_t TagWriteAFI(BYTE AFI);

	// 读取标签信息
	err_t GetTagInfo(TagInfo& info);

	// 获取EAS状态
	err_t CheckEAS(BYTE *EASFlag);

	// 关闭EAS
	err_t TagDisableEAS();

	// 使能EAS
	err_t TagEnableEAS();

	// 断开标签的连接
	err_t TagDisconnect();

	// 添加盘点参数
	err_t AddInvenParam(InvenParamStruct& Info);

	// 盘点和解释标签数据
	err_t InvenTory();

	err_t GetConfigBlock(PBYTE datas, INT BlockAddr, INT BlockCount, INT BlockSzie);
	err_t SetConfigBlock(PBYTE datas, INT BlockAddr, INT BlockCount, INT BlockSzie);
	err_t SaveConfigBlock(INT BlockAddr, INT BlockCount);

	err_t ResetConfig();
	CArray<CTag>* GetTags();
};


class CReader::InvenParamStruct{
public:
	DWORD		AIPType;
	BYTE		AntenalID;
	BOOLEAN		EnableAFI;
	BYTE		AFI;
	BYTE		SlotType;
	BYTE		Sel;
	BYTE		Session;
	BYTE		Q;
};


class CReader::TagInfo{
public:
	BYTE		uid[8];
	BYTE		DSFID;
	BYTE		AFI;
	DWORD		nBlokSize;
	DWORD		nTotalBlocks;
	BYTE		ICRef;
};