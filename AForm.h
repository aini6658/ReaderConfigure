

#if !defined( __AFORM_H__ )
#define __AFORM_H__



#define NoOKCancel() \
void ThisClass::OnCancel(){} \
void ThisClass::OnClose() \
{ \
	BaseClass::OnCancel(); \
} 

#ifndef _std
#	define _std   ::std::
#endif

#ifndef _sizeof
#	define _sizeof(x) ((SIZE_T)sizeof(x))
#endif

#ifndef _fied
#	define  _fied		static const
#endif


#define OFUNC_BEGIN(name, ret_type) \
class name { public:ret_type operator()

#define OFUNC_END };

#include <./types.h>
#include <./mcrt.h>
#include <./mafx.h>


#endif /* !__AFORM_H__ */ 