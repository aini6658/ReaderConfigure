#pragma once


class CCommPortUI 
{
public:
	virtual INT GetParams(CString& dest) = 0;

	virtual BOOL Hid() = 0;
	virtual BOOL Show() = 0;
	virtual void Update() = 0;
	virtual INT Create(CRect &rect) = 0;
	virtual BOOL Destroy() = 0;

	virtual BOOL SendMessage(INT nMsg, WPARAM wParam,LPARAM lParam) = 0;
};


