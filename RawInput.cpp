#include "stdafx.h"
#include "RawInput.h"

/* 
** WM_INPUT_DEVICE_CHANGE
**   wParam 
**     GIDC_ARRIVAL		A new device has been added to the system.
**     GIDC_REMOVAL		A device has been removed from the system.
**	 lParam				The handle to the raw input device. Call GetRawInputDeviceInfo to get 
**   					more information regarding the device.
*/
CRawInput::CRawInput()
{

	RAWINPUTDEVICE Rid;
	Rid.usUsagePage = 0xFF;
	Rid.usUsage = 0x01;
	Rid.dwFlags = 0;
	Rid.hwndTarget = 0;

	if (RegisterRawInputDevices(&Rid, 1, sizeof(Rid)))
	{

	}

}


CRawInput::~CRawInput()
{
}
