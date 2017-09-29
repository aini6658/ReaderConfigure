#include "stdafx.h"
#include "AWnd.h"
#include "Resource.h"


typedef AWnd ThisClass;
typedef void BaseClass;



ThisClass::AWnd(HINSTANCE m_hInstance, HWND Parent)
	:m_hInstance(m_hInstance),
	m_hWnd(NULL),
	m_hParent(Parent)
{


}


BOOL ThisClass::CreateEx
(LPCTSTR szTitle, DWORD dwStyleEx, DWORD dwStyle, INT x, INT y, INT nWidth, INT nHigh)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.lpszClassName = _T("AWnd");
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCE(IDC_AFORM);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.hIconSm = NULL;


	ATOM atom = RegisterClassEx(&wcex);

	HWND hWnd = CreateWindowEx(
		dwStyleEx, 
		_T("AWnd"), szTitle,
		dwStyle,
		x, y, nWidth, nHigh, m_hParent,
		NULL,
		m_hInstance, 
		NULL
		);

	if (!hWnd)
	{
		return FALSE;
	}

	return TRUE;
}

ThisClass::~AWnd()
{

}

BOOL ThisClass::Update()
{
	return ::UpdateWindow(m_hWnd);
}

BOOL ThisClass::Show()
{
	return ::ShowWindow(m_hWnd,SW_SHOW);
}

BOOL ThisClass::Hide()
{
	return ::ShowWindow(m_hWnd,SW_HIDE);
}

BOOL ThisClass::Destroy()
{
	return DestroyWindow(m_hWnd);
}

LRESULT ThisClass::Default()
{
	MSG msg;
	::GetMessage(&msg, m_hWnd, NULL, NULL);
	return DefWindowProc(msg.message, msg.wParam, msg.lParam);
}
VOID ThisClass::OnClose()		{Default();}

LRESULT ThisClass::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, message, wParam, lParam);
}

LRESULT CALLBACK ThisClass::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	INT wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		//switch (wmId)
		//{
		//case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			//break;
		//case IDM_EXIT:
			//DestroyWindow(hWnd);
			//break;

		//default:
			//return DefWindowProc(hWnd, message, wParam, lParam);
		//}
		//break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	//case WM_GETMINMAXINFO:

	//case WM_NCCREATE:

	//case WM_NCDESTROY:

	default:
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}