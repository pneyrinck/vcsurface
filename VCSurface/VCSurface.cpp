// VCSurface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

#include <iostream>

#include "vcontrol.h"
void addModuleControl(struct VControlModule* module, const char* id, const char* name, int index, const char* sendType, const char* receiveType);
int getKey();

int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	struct VControlModule* module = VControlApiSurfaceCreate("utas", "UTAS Surface", 0, false);
	int index = 0;
	addModuleControl(module, "record", "Record", index++, kVControlParameterTypeMomentary, kVControlParameterTypeBoolean);
	addModuleControl(module, "mute1", "Mute 1", index++, kVControlParameterTypeMomentary, kVControlParameterTypeBoolean);
	addModuleControl(module, "mute2", "Mute 2", index++, kVControlParameterTypeMomentary, kVControlParameterTypeBoolean);
	addModuleControl(module, "memloc1", "Location 1", index++, kVControlParameterTypeMomentary, kVControlParameterTypeBoolean);
	addModuleControl(module, "memloc2", "Location 2", index++, kVControlParameterTypeMomentary, kVControlParameterTypeBoolean);
	VControlModulePublish(module);
	VControlSurfaceServerConnect("127.0.0.1", "",  8080, "/surfaces");


	while (true)
	{
		printf("pressed q to quit\n");
		int i = getKey();
		if (i == 81)
			break;
	}
	system("pause");

	VControlSurfaceServerConnect("", "", 8080, "/surfaces");
	return 0;
}

void addModuleControl(struct VControlModule* module, const char* id, const char* name, int index, const char* sendType, const char* receiveType)
{
	VControlApiAddControl(module, index, id, sendType);
	struct SVControlPropertyValue nameVal = { cVControlPropertyType_String, name };
	VControlModuleUpdateControlPropertyValue(module, index, kVControlProperty_Name, nameVal);
	struct SVControlPropertyValue typeVal = { cVControlPropertyType_String, receiveType };
	VControlModuleUpdateControlPropertyValue(module, index, kVControlProperty_FeedbackType, typeVal);
}

int getKey()
{
	while (true)
	{
		for (int i = 8; i <= 256; i++)
		{
			if (GetAsyncKeyState(i) & 0x7FFF)
			{

				// This if filters the keys, i want to allow direction arrows
				// and q for quit. If you want to add more just add the code for the key,
				// to know the key code just coment the if line and print the keycode. 
				//if ((i >= 37 && i <= 40) || i == 81)
					return i;
			}
		}
	}
}