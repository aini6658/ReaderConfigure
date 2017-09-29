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

	

	CArray<DRIVERINFO>	 m_driver_info_list;			// �Ѽ��ص���������Ϣ
	RFID_READER_HANDLE	 m_hReader;						// ��д�����
	RFID_TAG_HANDLE	     m_hTag;						// ��ǩ���
	RFID_DN_HANDLE		 m_dnInvenParamList;			// �̵�����б���
	INT					 m_TotalCount;					// ��ȡ���ı�ǩ������
	BYTE				 m_AFI;
	DWORD				 m_dwAntennaInterfaceCount;
	CArray<CTag>		*m_cTags;

	INT					 m_cinfg_addr;		// д�벢δ����Ŀ鿪ʼ��ַ
	INT					 m_cinfg_count;		// д�벢δ����Ŀ鳤��
	INT					 m_cinfg_size;		// д�벢δ����Ŀ�ĳߴ�

public:
	CArray<DRIVERINFO>* GetDriverInfoList();
	// ���豸
	err_t Open(const CString& ConnectStr);

	static err_t Enum(LPCTSTR DevID, COMM_TYPE CommType = COMM_TYPE::USB);

	err_t GetReaderInfo(LPTSTR buf,PDWORD nSize);

	// �ر��豸
	err_t Close();

	// �����������
	INT GetAntCount();

	// ��ȡ����Э������
	err_t GetTagAIPName(CTag cTag, PVOID pBuf, SIZE_T* nSize);

	// ��ȡ��ǹ��������
	err_t GetTagTypeName(CTag cTag, PVOID pBuf, SIZE_T* nSize);

	// �����̵�����б�
	err_t CreatInvenParamList();

	// �����̵�����б�
	err_t DestroyInvenParamList();

	// ���ӵ���ǩ
	err_t TagConnect(DWORD TagType, BYTE AddrMOde, BYTE uid[]);

	// ��ȡ��ǩ��
	err_t TagReadBlock(DWORD dwBlockAddr, DWORD dwBlockCount, PVOID buff, INT nMaxSize);

	// д��ǩ��
	err_t TagWriteBlock(DWORD dwBlockAddr, DWORD dwBlockCount, PVOID buff, INT nWrtten);


	// дAFI
	err_t TagWriteAFI(BYTE AFI);

	// ��ȡ��ǩ��Ϣ
	err_t GetTagInfo(TagInfo& info);

	// ��ȡEAS״̬
	err_t CheckEAS(BYTE *EASFlag);

	// �ر�EAS
	err_t TagDisableEAS();

	// ʹ��EAS
	err_t TagEnableEAS();

	// �Ͽ���ǩ������
	err_t TagDisconnect();

	// ����̵����
	err_t AddInvenParam(InvenParamStruct& Info);

	// �̵�ͽ��ͱ�ǩ����
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