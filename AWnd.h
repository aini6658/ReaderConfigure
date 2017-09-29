#pragma once
#include <wtypes.h>



class AWnd
{


public:
	AWnd(HINSTANCE m_hInstance, HWND Parent);
	~AWnd();
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HWND m_hParent;
	
public:
	BOOL CreateEx(LPCTSTR szTitle, DWORD dwStyleEx, DWORD dwStyle, INT x, INT y, INT nWidth, INT nHigh);
	BOOL Update();
	BOOL Show();
	BOOL Hide();
	BOOL Destroy();

protected:
	LRESULT Default();
	VOID OnClose();

	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

