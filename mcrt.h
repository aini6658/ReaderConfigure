


#if !defined( __MCRT_H__ )
#define __MCRT_H__


#define Delete(pObj)	\
	if (pObj)			\
	{					\
		delete pObj;	\
		pObj = NULL;	\
	}	

#define _zfree(pMem)	\
	if (pMem)			\
	{					\
		free(pMem);	\
		pMem = NULL;	\
	}	

#define IsEmptyStr(lptstr)	\
	((lptstr)[0] == _T('\0'))?1:0


#define size_of(_var,_item_ty)	(sizeof(_var)/sizeof(_item_ty))
#define NO_NAME _T("")

#endif /* !__MCRT_H__ */ 