#include "StdAfx.h"
#include "CReader.h"
#include "rfidlib.h"
#include "rfidlib_reader.h"
#include "rfidlib_aip_ISO15693.h"
#include "rfidlib_aip_iso14443A.h"
#include "rfidlib_aip_iso18000p3m3.h"

#pragma comment(lib,"rfidlib_reader.lib")
#pragma comment(lib,"rfidlib_aip_ISO15693.lib")
#pragma comment(lib,"rfidlib_aip_iso14443A.lib")
#pragma comment(lib,"rfidlib_aip_iso18000p3m3.lib")

typedef CReader		_This;



_This::CReader()
	:m_cinfg_addr(0),
	m_cinfg_count(0)
{
	

	RDR_LoadReaderDrivers(_T("\\drivers"));
	
	for (UINT i = 0; i < RDR_GetLoadedReaderDriverCount(); i++)
	{

		DWORD nSize;
		TCHAR tmp[64];
		DRIVERINFO info;

		memset(tmp, 0, sizeof(tmp));
		nSize = sizeof(tmp) / sizeof(TCHAR);
		RDR_GetLoadedReaderDriverOpt(i, _T(LOADED_RDRDVR_OPT_CATALOG), tmp, &nSize);

		if (!_tcscmp(tmp, _T(RDRDVR_TYPE_READER))){

			ZeroMemory(tmp, SIZE_OF_TCHAR(nSize));
			nSize = sizeof(tmp) / sizeof(TCHAR);
			RDR_GetLoadedReaderDriverOpt(i, _T(LOADED_RDRDVR_OPT_NAME), tmp, &nSize);
			info.DriverName = tmp;

			ZeroMemory(tmp, SIZE_OF_TCHAR(nSize));
			nSize = sizeof(tmp) / sizeof(TCHAR);
			RDR_GetLoadedReaderDriverOpt(i, _T(LOADED_RDRDVR_OPT_ID), tmp, &nSize);
			info.DriverID = _tcstol(tmp,NULL,10);

			ZeroMemory(tmp, SIZE_OF_TCHAR(nSize));
			nSize = sizeof(tmp) / sizeof(TCHAR);
			RDR_GetLoadedReaderDriverOpt(i, _T(LOADED_RDRDVR_OPT_COMMTYPESUPPORTED), tmp, &nSize);
			info.CommTypeSupported = _tcstol(tmp,NULL,10);

			m_driver_info_list.Add(info);

		}
	}
	m_cTags = new CArray<CTag>;
	//m_dwAntennaInterfaceCount = (BYTE)RDR_GetAntennaInterfaceCount(m_hDevice);
	

}

CArray<DRIVERINFO>* _This::GetDriverInfoList()
{
	return &m_driver_info_list;
}

_This::~CReader(void)
{

	
}
err_t _This::Open(const CString& csConStr){
	return RDR_Open(csConStr,&m_hReader);
}

err_t Enum(LPCTSTR DevID, COMM_TYPE CommType)
{
	INT nCount;

	switch (CommType)
	{
	// 枚举串口设备
	case COMM_TYPE::COM:
		nCount = (INT)::COMPort_Enum();

		for (INT i = 0;; i++)
		{
			TCHAR buf[32];
			INT nSize = SIZE_OF_TCHAR(32);
			::COMPort_GetEnumItem(i, buf, (DWORD)nSize);
		}

		break;

	// 枚举USB设备
	case COMM_TYPE::USB:
		nCount = (INT)::HID_Enum(DevID);

		for (INT i = 0;; i++)
		{
			TCHAR buf[32];
			INT nSize = SIZE_OF_TCHAR(32);
			::HID_GetEnumItem(i, HID_ENUM_INF_TYPE_SERIALNUM, buf, (DWORD*)&nSize);
		}

		break;
	default:
		break;
	}

	return NOERROR;
}

err_t _This::Close(){
	err_t ret;

	if (m_hReader)
	{
		ret = RDR_Close(m_hReader);
		m_hReader = NULL;
	}

	return ret;
}

err_t _This::GetTagAIPName(CTag cTag,PVOID pBuf,SIZE_T *nSize)
{
	return RDR_GetAIPTypeName(m_hReader,cTag.AIPType, (LPTSTR)pBuf, nSize);
}

err_t _This::GetTagTypeName(CTag cTag,PVOID pBuf,SIZE_T *nSize){
	return RDR_GetTagTypeName(m_hReader,cTag.AIPType, cTag.TagType, (LPTSTR)pBuf, nSize);
}

err_t _This::TagDisconnect(){

	err_t ret;

	ret = RDR_TagDisconnect(m_hReader,m_hTag);
	m_hTag = NULL;

	return ret;
}

err_t _This::GetTagInfo(_This::TagInfo& info)
{
	return ISO15693_GetSystemInfo(m_hReader, m_hTag, info.uid, &(info.DSFID), &(info.AFI), &(info.nBlokSize), &(info.nTotalBlocks), &(info.ICRef));
}

err_t _This::CheckEAS(BYTE *EASFlag)
{ 
	return NXPICODESLI_EASCheck(m_hReader, m_hTag, EASFlag);
}

// 读取标签块
err_t _This::TagReadBlock(DWORD dwBlockAddr,DWORD dwBlockCount, PVOID buff ,INT nMaxSize)
{
	ASSERT(m_hReader != RFID_HANDLE_NULL);
	ASSERT(m_hTag != RFID_HANDLE_NULL);

	DWORD nRead = 0;
	DWORD bytesBlkDatRead = 0;
	
	return ISO15693_ReadMultiBlocks(
		m_hReader,
		m_hTag,
		FALSE,
		dwBlockAddr,
		dwBlockCount,
		&nRead,
		(PBYTE)buff,
		nMaxSize,
		&bytesBlkDatRead
		);
}

err_t _This::GetReaderInfo(LPTSTR buf,PDWORD nSize)
{
	return RDR_GetReaderInfor(m_hReader,0 ,buf , nSize);
}

err_t _This::TagWriteAFI(BYTE AFI)
{
	return ISO15693_WriteAFI(m_hReader, m_hTag, AFI);
}

// 写标签块
err_t _This::TagWriteBlock(DWORD dwBlockAddr,DWORD dwBlockCount, PVOID buff,INT nWritten){
	ASSERT(m_hReader != RFID_HANDLE_NULL);
	ASSERT(m_hTag != RFID_HANDLE_NULL);

	return ISO15693_WriteMultipleBlocks(m_hReader, m_hTag, dwBlockAddr, dwBlockCount, (PBYTE)buff, nWritten);
}

INT _This::GetAntCount(){
	ASSERT(m_hReader!=RFID_HANDLE_NULL);

	return RDR_GetAntennaInterfaceCount(m_hReader);
}

err_t _This::CreatInvenParamList()
{
	m_dnInvenParamList = RDR_CreateInvenParamSpecList();
	
	ASSERT(m_dnInvenParamList != RFID_HANDLE_NULL);

	return NOERROR;
}

err_t _This::DestroyInvenParamList()
{
	err_t ret;

	if (m_dnInvenParamList)
	{
		ret = DNODE_Destroy(m_dnInvenParamList);
		m_dnInvenParamList = RFID_HANDLE_NULL;
	}

	return ret;
}

err_t _This::AddInvenParam(InvenParamStruct& Info)
{
	if(Info.AIPType|(DWORD)AIP_TYPE::ISO15693)
		ISO15693_CreateInvenParam(
			m_dnInvenParamList,
			Info.AntenalID, 
			Info.EnableAFI,
			Info.AFI, 
			Info.SlotType
			) ;

	if(Info.AIPType|(DWORD)AIP_TYPE::ISO14443A)
		ISO14443A_CreateInvenParam(
		m_dnInvenParamList,
		Info.AntenalID
		) ;

	if(Info.AIPType|(DWORD)AIP_TYPE::ISO18000p3m3)
		ISO18000p3m3_CreateInvenParam(
		m_dnInvenParamList,
		Info.AntenalID,
		Info.Sel,
		Info.Session,
		Info.Q
		) ;

	return NOERROR;
}


err_t _This::InvenTory()
{
	INT Index = 0;
	err_t err = NOERROR;

	ASSERT(m_hReader != RFID_HANDLE_NULL);
	ASSERT(m_dnInvenParamList != RFID_HANDLE_NULL);

	// 清空上次读取的标签
	m_TotalCount = 0;
	m_cTags->RemoveAll();

	BYTE AIType = AI_TYPE_NEW;

label_inventory:

	err = RDR_TagInventory(m_hReader, AIType, 0, NULL, m_dnInvenParamList);

	if ((err == NOERROR) || (err == -21))
	{
		m_TotalCount += RDR_GetTagDataReportCount(m_hReader);
		RFID_DN_HANDLE hReport = RDR_GetTagDataReport(m_hReader, RFID_SEEK_FIRST);

		while (hReport != RFID_HANDLE_NULL)
		{
			
			CString SerialNumber;
			CTag Tag;

			err = ISO15693_ParseTagDataReport(
				hReport,
				&(Tag.AIPType),
				&(Tag.TagType),
				&(Tag.AntID),
				&(Tag.DSFID),
				Tag.SerialNumber
				);

			if(err == NOERROR)
				m_cTags->Add(Tag);

			hReport = RDR_GetTagDataReport(m_hReader, RFID_SEEK_NEXT);
			
		}

	}/* end if */
		
	//}/* end while */

	if(err == -21) // 可能有标签未读完
	{
		AIType = AI_TYPE_CONTINUE;
		goto label_inventory;
	}


	return NOERROR;
}

err_t _This::TagConnect(DWORD TagType, BYTE AddrMOde, BYTE uid[])
{
	if (m_hTag != RFID_HANDLE_NULL) return -1;

	err_t err;
	err = ISO15693_Connect(m_hReader,TagType,AddrMOde,uid,&m_hTag);

		if(AddrMOde == 0 ){
		/* 
		* if select none address mode after inventory need to reset the tag first,because the tag is stay quiet now  
		* if the tag is in ready state ,do not need to call reset
		*/
		err = ISO15693_Reset(m_hReader,m_hTag) ;

		if(err != 0){
			//MessageBox( _T("reset tag fail!"),_T("error"),MB_OK) ;
			RDR_TagDisconnect(m_hReader,m_hTag);
			m_hTag =NULL ;
		}
	}
		return err;
}

CArray<CTag>* _This::GetTags(){
	return m_cTags;
}

err_t _This::TagDisableEAS(){
	return NXPICODESLI_DisableEAS(m_hReader, m_hTag);
}

err_t _This::TagEnableEAS()
{
	return NXPICODESLI_EableEAS(m_hReader, m_hTag);
}


err_t _This::GetConfigBlock(PBYTE datas, INT BlockAddr, INT BlockCount, INT BlockSzie)
{
	
	err_t ret = NOERROR;

	for (INT i = 0; i < BlockCount; i++)
	{
		ret = RDR_ConfigBlockRead(m_hReader, BlockAddr++, datas, BlockSzie);
		datas += BlockSzie;
		if (ret != NOERROR)return ret;
	}
	

	return ret;
}

err_t _This::SetConfigBlock(PBYTE datas, INT BlockAddr, INT BlockCount, INT BlockSzie)
{
	err_t ret = NOERROR;

	for (INT i = 0; i < BlockCount; i++)
	{
		ret = RDR_ConfigBlockWrite(m_hReader, BlockAddr++, datas, BlockSzie, -1);
		datas += BlockSzie;
		if (ret != NOERROR)
		{
			return ret;
		}
	}

	// 失败将不能保存
	//m_cinfg_addr = min(m_cinfg_addr, BlockAddr);
	//m_cinfg_count = max(m_cinfg_count, BlockCount);
	//m_cinfg_size = BlockSzie;

	return ret;
}


err_t _This::SaveConfigBlock(INT BlockAddr, INT BlockCount)
{
	err_t ret = NOERROR;

	for (INT i = 0; i < BlockCount; i++)
	{
		ret = RDR_ConfigBlockSave(m_hReader, BlockAddr++);
		if (ret != NOERROR)return ret;
	}
	// m_cinfg_addr = m_cinfg_count = 0;

	return ret;
}

err_t _This::ResetConfig()
{
	return ::RDR_LoadFactoryDefault(m_hReader);
}