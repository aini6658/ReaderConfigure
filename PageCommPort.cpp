// PageCommPort.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReaderConfigureApp.h"
#include "PageCommPort.h"
#include "Resource.h"

typedef CPageCommPort		ThisClass;
typedef CDialogEx				BaseClass;
// CPageCommPort

IMPLEMENT_DYNAMIC(CPageCommPort, CDialogEx)

BEGIN_MESSAGE_MAP(CPageCommPort, CDialogEx)


	ON_WM_CLOSE()
END_MESSAGE_MAP()

CPageCommPort::CPageCommPort(CWnd* Parent)
	:CDialogEx(CPageCommPort::IDD, Parent)
{
	
}

CPageCommPort::~CPageCommPort()
{

}



// CPageCommPort ��Ϣ�������



void ThisClass::OnClose()
{
	CDialogEx::OnClose();
}

void ThisClass::OnCancel()
{}

void ThisClass::OnOK()
{}
