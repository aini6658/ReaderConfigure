#if !defined( __CTAG_H__ )
#define __CTAG_H__

//#pragma warning(disable:4200)

struct CTag
{
	DWORD	AIPType;
	DWORD	TagType;
	DWORD	AntID;
	BYTE	AFI;
	BYTE	DSFID;
	BYTE	SerialNumber[1];
};

#endif /* !__CTAG_H__ */ 