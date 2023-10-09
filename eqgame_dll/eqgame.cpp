#include <Windows.h>
#include <stdio.h>
#include <map>
#include <time.h>
#include "..\Detours\inc\detours.h"
//#include "..\zlib_x86\include\zlib.h"
#include "eqmac.h"
#include "eqmac_functions.h"
#include "eqgame.h"
#include <dxgi.h>
#include <ctime>
#include <iostream>
#include <string>
#include <iomanip>

#include <random>
#include <iostream>

#define BYTEn(x, n) (*((BYTE*)&(x)+n))
#define BYTE1(x) BYTEn(x, 0)
#define BYTE2(x) BYTEn(x, 1)
//#include "Common.h"

#define FREE_THE_MOUSE
//#define LOGGING

extern void Pulse();
extern bool was_background;
extern void LoadIniSettings();
extern void SetEQhWnd();
extern HMODULE heqwMod;
extern HWND EQhWnd;
HANDLE myproc = 0;
bool title_set = false;
std::string new_title("");
bool first_maximize = true;
bool can_fullscreen = false;
bool ignore_right_click = false;
bool ignore_right_click_up = false;
bool ignore_left_click = false;
bool ignore_left_click_up = false;
DWORD focus_regained_time = 0;

bool ResolutionStored = false;
DWORD resx = 0;
DWORD resy = 0;
DWORD bpp = 0;
DWORD refresh = 0;
HMODULE eqmain_dll = 0;
BOOL bExeChecksumrequested = 0;
BOOL g_mouseWheelZoomIsEnabled = true;
unsigned int g_buffWindowTimersFontSize = 3;
bool has_focus = true;
WINDOWINFO stored_window_info;
bool window_info_stored = false;
WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };
bool start_fullscreen = false;
bool startup = true;
POINT posPoint;
DWORD o_MouseEvents = 0x0055B3B9;
DWORD o_MouseCenter = 0x0055B722;

bool g_bEnableBrownSkeletons = false;
bool g_bEnableExtendedNameplates = true;
bool auto_login = false;
char UserName[64];
char PassWord[64];

typedef signed int(__cdecl* ProcessGameEvents_t)();
ProcessGameEvents_t return_ProcessGameEvents;
ProcessGameEvents_t return_ProcessMouseEvent;
//ProcessGameEvents_t return_SetMouseCenter;

DWORD d3ddev = 0;
DWORD eqgfxMod = 0;
BOOL bWindowedMode = true;

BOOL RightHandMouse = true;

typedef struct _detourinfo
{
	DWORD_PTR tramp;
	DWORD_PTR detour;
}detourinfo;
std::map<DWORD,_detourinfo> ourdetours;


#define FUNCTION_AT_ADDRESS(function,offset) __declspec(naked) function\
{\
	__asm{mov eax, offset};\
	__asm{jmp eax};\
}

#define EzDetour(offset,detour,trampoline) AddDetourf((DWORD)offset,detour,trampoline)

void PatchA(LPVOID address, const void *dwValue, SIZE_T dwBytes) {
	unsigned long oldProtect;
	VirtualProtect((void *)address, dwBytes, PAGE_EXECUTE_READWRITE, &oldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)address, dwBytes);
	memcpy((void *)address, dwValue, dwBytes);
	VirtualProtect((void *)address, dwBytes, oldProtect, &oldProtect);
}

void UpdateTitle()
{
	if (new_title.length() == 0) {
		HWND cur = NULL;
		char str[255];
		int i = 0;
		do {
			i++;
			sprintf(str, "Client%d", i);
			cur = FindWindowA(NULL, str);
		} while (cur != NULL);
		new_title = str;
	}
	SetWindowTextA(EQhWnd, new_title.c_str());
#ifdef LOGGING
	std::string outlog_name(new_title);
	outlog_name += ".log";
	freopen(outlog_name.c_str(), "w", stdout);
#endif // LOGGING
}
#ifdef LOGGING
void WriteLog(std::string logstring) {

	std::time_t result = std::time(nullptr);
	std::tm * ptm = std::localtime(&result);
	if (new_title.length() > 0)
		std::cout << "[" << new_title.c_str() << "] [" << std::put_time(ptm, "%c") << "] " << logstring.c_str() << std::endl;
	else
		std::cout << "[" << std::put_time(ptm, "%c") << "] " << logstring.c_str() << std::endl;
	OutputDebugString(logstring.c_str());
	//MessageBox(NULL, outstring.c_str(), NULL, MB_OK);
}
#endif // !LOGGING

void __cdecl ResetMouseFlags() {
#ifdef LOGGING
	WriteLog("EQGAME: Resetting Mouse Flags");
#endif
	DWORD ptr = *(DWORD *)0x00809DB4;
	if (ptr)
	{
		*(BYTE*)(ptr + 85) = 0;
		*(BYTE*)(ptr + 86) = 0;
		*(BYTE*)(ptr + 87) = 0;
		*(BYTE*)(ptr + 88) = 0;
	}

	*(DWORD*)0x00809320 = 0;
	*(DWORD*)0x0080931C = 0;
	*(DWORD*)0x00809324 = 0;
	*(DWORD*)0x00809328 = 0;
	*(DWORD*)0x0080932C = 0;
}

void __cdecl ProcessAltState() {
	if(GetForegroundWindow() == EQhWnd)
	{
		if(GetAsyncKeyState(VK_MENU)&0x8000) // alt key is pressed
		{
			DWORD ptr = *(DWORD *)0x00809DB4;
			if (ptr)
			{
				*(BYTE*)(ptr + 87) = 1;
			}
			*(DWORD*)0x00799740 = 1;
			*(DWORD*)0x0080932C = 1;
		}
		else
		{
			DWORD ptr = *(DWORD *)0x00809DB4;
			if (ptr)
			{
				*(BYTE*)(ptr + 87) = 0;
			}
			*(DWORD*)0x00799740 = 0;
			*(DWORD*)0x0080932C = 0;
		}
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000) // ctrl key is pressed
		{
			DWORD ptr = *(DWORD *)0x00809DB4;
			if (ptr)
			{
				*(BYTE*)(ptr + 86) = 1;
			}
			*(DWORD*)0x0079973C = 1;
			*(DWORD*)0x00809320 = 1;
		}
		else
		{
			DWORD ptr = *(DWORD *)0x00809DB4;
			if (ptr)
			{
				*(BYTE*)(ptr + 86) = 0;
			}
			*(DWORD*)0x0079973C = 0;
			*(DWORD*)0x00809320 = 0;
		}
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000) // shift key is pressed
		{
			DWORD ptr = *(DWORD *)0x00809DB4;
			if (ptr)
			{
				*(BYTE*)(ptr + 85) = 1;
			}
			*(DWORD*)0x00799738 = 1;
			*(DWORD*)0x0080931C = 1;
		}
		else
		{
			DWORD ptr = *(DWORD *)0x00809DB4;
			if (ptr)
			{
				*(BYTE*)(ptr + 85) = 0;
			}
			*(DWORD*)0x00799738 = 0;
			*(DWORD*)0x0080931C = 0;
		}
	}
}

void AddDetourf(DWORD address, ...)
{
	va_list marker;
	int i=0;
	va_start(marker, address);
	DWORD Parameters[3];
	DWORD nParameters=0;
	while (i!=-1) 
	{
		if (nParameters<3)
		{
			Parameters[nParameters]=i;
			nParameters++;
		}
		i = va_arg(marker,int);
	}
	va_end(marker);
	if (nParameters==3)
	{
		detourinfo detinf = {0};
		detinf.detour = Parameters[1];
		detinf.tramp = Parameters[2];
		ourdetours[address] = detinf;
		DetourFunctionWithEmptyTrampoline((PBYTE)detinf.tramp,(PBYTE)address,(PBYTE)detinf.detour);
	}
}

bool CtrlPressed() {
	return *(DWORD*)0x00809320 > 0;
}
bool AltPressed() {
	return *(DWORD*)0x0080932C > 0;
}
bool ShiftPressed() {
	return *(DWORD*)0x0080931C > 0;
}

bool g_bEnableClassicMusic = false;

int g_LastMusicStop = 0;
int g_curMusicTrack = 2;

int __cdecl msg_send_corpse_equip(class EQ_Equipment *);
FUNCTION_AT_ADDRESS(int __cdecl msg_send_corpse_equip(class EQ_Equipment *),0x4DF03D);
int base_val = 362;
class Eqmachooks {
public:

	int  CEQMusicManager__Set_Trampoline(int, int, int, int, int, int, int, int, int);
	int  CEQMusicManager__Set_Detour(int musicIdx, int unknown1, int trackIdx, int volume, int unknown, int timeoutDelay, int timeInDelay, int range /* ? */, int bIsMp3)
	{
		if (g_bEnableClassicMusic)
		{
			rename("combattheme1.mp3", "combattheme1.mp3.bak");
			rename("combattheme2.mp3", "combattheme2.mp3.bak");
			rename("deaththeme.mp3", "deaththeme.mp3.bak");
			rename("eqtheme.mp3", "eqtheme.mp3.bak");
		}
		else //if (!g_bEnableClassicMusic)
		{
			rename("combattheme1.mp3.bak", "combattheme1.mp3");
			rename("combattheme2.mp3.bak", "combattheme2.mp3");
			rename("deaththeme.mp3.bak", "deaththeme.mp3");
			rename("eqtheme.mp3.bak", "eqtheme.mp3");
		}

		if (musicIdx == 2 && g_bEnableClassicMusic)
		{
			CEQMusicManager__Set_Trampoline(2500, unknown1, 0, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2501, unknown1, 1, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2502, unknown1, 2, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2503, unknown1, 3, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2504, unknown1, 4, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2505, unknown1, 5, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2506, unknown1, 6, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2507, unknown1, 7, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2508, unknown1, 8, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2509, unknown1, 9, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2510, unknown1, 10, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2511, unknown1, 11, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2512, unknown1, 12, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2513, unknown1, 13, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2514, unknown1, 14, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2515, unknown1, 15, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2516, unknown1, 16, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2517, unknown1, 17, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2518, unknown1, 18, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2519, unknown1, 19, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2520, unknown1, 20, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2521, unknown1, 21, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
			CEQMusicManager__Set_Trampoline(2522, unknown1, 22, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);
		}

		return CEQMusicManager__Set_Trampoline(musicIdx, unknown1, trackIdx, volume, unknown, timeoutDelay, timeInDelay, range, bIsMp3);

	}

	int  CEQMusicManager__Play_Trampoline(int, int);
	int  CEQMusicManager__Play_Detour(int trackIdx, int bStartStop)
	{
		if (g_bEnableClassicMusic)
		{
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(1, 3);
			auto tickCount = GetTickCount();



			if (trackIdx == 2)
			{
				if (g_LastMusicStop == 0)
				{
					g_LastMusicStop = tickCount;
				}

				if (bStartStop == 1)
				{
					if (tickCount >= g_LastMusicStop + 10000)
					{
						switch (dist(mt))
						{
						case 1:
						{
							g_curMusicTrack = 2501;
							break;
						}
						case 2:
						{
							g_curMusicTrack = 2502;
							break;
						}
						case 3:
						default:
						{
							g_curMusicTrack = 2500;
							break;
						}
						}
					}
					trackIdx = g_curMusicTrack;
				}
				else if (bStartStop == 0)
				{
					trackIdx = g_curMusicTrack;
					g_LastMusicStop = GetTickCount();
				}
			}
		}
		return CEQMusicManager__Play_Trampoline(trackIdx, bStartStop);

	}

	unsigned char CEverQuest__HandleWorldMessage_Trampoline(DWORD *,unsigned __int32,char *,unsigned __int32);
	unsigned char CEverQuest__HandleWorldMessage_Detour(DWORD *con,unsigned __int32 Opcode,char *Buffer,unsigned __int32 len)
	{
		//std::cout << "Opcode: 0x" << std::hex << Opcode << std::endl;
		if(Opcode==0x4052) {//OP_ItemOnCorpse
			return msg_send_corpse_equip((EQ_Equipment*)Buffer);
		}
		if (Opcode == 0x4038) { // OP_ShopDelItem=0x3840
			if (!*(BYTE*)0x8092D8) {
				return NULL;
				// stone skin UI doesn't like this
				/*
				Merchant_DelItem_Struct* mds = (Merchant_DelItem_Struct*)(Buffer + 2);
				std::string outstring;
				outstring = "MDS npcid = ";
				outstring += std::to_string(mds->npcid);
				outstring += " slot = ";
				outstring += std::to_string(mds->itemslot);
				WriteLog(outstring);
				if (!mds->itemslot || mds->itemslot > 29)
					return NULL;
				*/
			}			
		}
		/*if (Opcode == 0x400C) {
			// not using new UI
			if (!*(BYTE*)0x8092D8) {

				if (len > 2) {
					unsigned char *buff = new unsigned char[28960];
					memcpy(buff, Buffer, 2);
					int newsize = InflatePacket((unsigned char*)(Buffer + 2), len - 2, buff, 28960);
					std::string outstring;
					outstring = "Merchant inventory uncompressed size = ";
					outstring += " newsize = ";
					outstring += std::to_string(newsize);
					WriteLog(outstring);
					if (newsize > 0) {
						unsigned char* newbuff = new unsigned char[28960];
						memcpy(newbuff, buff, base_val);
						unsigned char* outbuff = new unsigned char[28960];
						int outsize = DeflatePacket((const unsigned char*)newbuff, base_val, outbuff, 28960);
						if (outsize > 0) {
							outstring = "Merchant inventory uncompressed size = ";
							outstring += "outsize = ";
							outstring += std::to_string(outsize);
							WriteLog(outstring);
							memcpy((unsigned char*)(buff + 2), outbuff, outsize);
							base_val += 362;
							return CEverQuest__HandleWorldMessage_Trampoline(con, Opcode, (char *)buff, outsize + 2);
						}
					}
					outstring = "Merchant inventory uncompressed size = ";
					outstring += std::to_string(newsize);
					outstring += " input sizeof Buffer = ";
					outstring += std::to_string(sizeof(Buffer));
					outstring += " input len = ";
					outstring += std::to_string(len);
					WriteLog(outstring);
					
				}
			}
		}*/
		if (Opcode == 0x41d8) { // OP_LogServer=0xc341
			can_fullscreen = true;
#ifdef LOGGING
			WriteLog("EQGAME: CEverQuest__HandleWorldMessage_Detour OP_LogServer=0xc341 Can go Fullscreen (1)");
#endif
		}
		return CEverQuest__HandleWorldMessage_Trampoline(con,Opcode,Buffer,len);
	}

	int __cdecl  CDisplay__Process_Events_Trampoline();
	int __cdecl  CDisplay__Process_Events_Detour(){
		if (EQ_OBJECT_CEverQuest != NULL && EQ_OBJECT_CEverQuest->GameState > 0 && EQ_OBJECT_CEverQuest->GameState != 255 && can_fullscreen) {
			SetEQhWnd();
			ProcessAltState();
			if (!ResolutionStored && *(DWORD*)(0x007F97D0) != 0)
			{
				DWORD ptr = *(DWORD*)(0x007F97D0);

				resx = *(DWORD*)(ptr + 0x7A28);
				resy = *(DWORD*)(ptr + 0x7A2C);
				bpp = *(DWORD*)(ptr + 0x7A20);
				refresh = *(DWORD*)(ptr + 0x7A30);

				ResolutionStored = true;
				eqgfxMod = *(DWORD*)(0x007F9C50);
				d3ddev = (DWORD)(eqgfxMod + 0x00A4F92C);
#ifdef LOGGING
				std::string outstring;
				outstring = "EQGAME: Resolution Stored: resx = ";
				outstring += std::to_string(resx);
				outstring += " resy = ";
				outstring += std::to_string(resy);
				outstring += " bbp = ";
				outstring += std::to_string(bpp);
				outstring += " refresh = ";
				outstring += std::to_string(refresh);
				WriteLog(outstring);
#endif
			}
			
			if (ResolutionStored && startup && GetForegroundWindow() == EQhWnd && !IsIconic(EQhWnd)) {
#ifdef LOGGING
				WriteLog("EQGAME: Startup - Storing window info");
#endif
				GetWindowInfo(EQhWnd, &stored_window_info);
				window_info_stored = true;
				startup = false;
				/*
				MONITORINFO monitor_info;
				monitor_info.cbSize = sizeof(monitor_info);
				GetMonitorInfo(MonitorFromWindow(EQhWnd, MONITOR_DEFAULTTONEAREST),
					&monitor_info);
				RECT window_rect(monitor_info.rcMonitor);
				DWORD monitor_x = window_rect.right - window_rect.left;
				DWORD monitor_y = window_rect.bottom - window_rect.top;
				if (monitor_x != resx || monitor_y != resy) {
					// Monitor resolution does not match game resolution
					// block initial going full screen in auto mode
					start_fullscreen = false;
					WriteLog("Startup - Monitor resolution does not match game - blocking auto full screen");
				}
#ifdef LOGGING
				std::string outstring;
				outstring = "Monitor Info: resx = ";
				outstring += std::to_string(monitor_x);
				outstring += " resy = ";
				outstring += std::to_string(monitor_y);
				WriteLog(outstring);
#endif

				*/

			}
			if (start_fullscreen && bWindowedMode && GetForegroundWindow() == EQhWnd && !IsIconic(EQhWnd)) {
				// This takes if fullscreen initially
#ifdef LOGGING
				WriteLog("EQGAME: Going Fullscreen (1)");
#endif
				if (!window_info_stored) {
#ifdef LOGGING
					WriteLog("EQGAME: Storing Window Info (1)");
#endif
					GetWindowInfo(EQhWnd, &stored_window_info);
					window_info_stored = true;
				}
				// MessageBox(NULL, "Going Full Screen", NULL, MB_OK);
				SetWindowLong(EQhWnd, GWL_STYLE,
					stored_window_info.dwStyle & ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU));

				SetWindowLong(EQhWnd, GWL_EXSTYLE,
					stored_window_info.dwExStyle & ~(WS_EX_DLGMODALFRAME |
						WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

				MONITORINFO monitor_info;
				monitor_info.cbSize = sizeof(monitor_info);
				GetMonitorInfo(MonitorFromWindow(EQhWnd, MONITOR_DEFAULTTONEAREST),
					&monitor_info);
				RECT window_rect(monitor_info.rcMonitor);

				WINDOWPLACEMENT window_placement;
				window_placement.length = sizeof(window_placement);
				
				if (first_maximize) {
					GetWindowPlacement(EQhWnd, &window_placement);
					window_placement.showCmd = SW_MINIMIZE;
					SetWindowPlacement(EQhWnd, &window_placement);
					window_placement.showCmd = SW_MAXIMIZE;
					SetWindowPlacement(EQhWnd, &window_placement);
#ifdef LOGGING
					WriteLog("EQGAME: Going Fullscreen First Maximize (2)");
#endif
				}
				SetWindowPos(EQhWnd, HWND_TOP, window_rect.left, window_rect.top,
					window_rect.right - window_rect.left, window_rect.bottom - window_rect.top,
					SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOSENDCHANGING | SWP_SHOWWINDOW);

				bWindowedMode = false;	
				first_maximize = false;
			}
			if (GetForegroundWindow() == EQhWnd && !IsIconic(EQhWnd)) {
				if (!has_focus) {
#ifdef LOGGING
					WriteLog("EQGAME: Window Regained focus after lost focus.");
#endif
					focus_regained_time = GetTickCount();
					ResetMouseFlags();
					while (ShowCursor(FALSE) >= 0);
					// regained focus
					if (ResolutionStored) {
						if (heqwMod) {
							int result;
							result = (*(int(__stdcall **)(DWORD))(**(DWORD **)d3ddev + 12))(*(DWORD *)d3ddev);
							//char str[56];
							//sprintf(str, "TestCoop = %d", result);
							//MessageBox(NULL, str, NULL, MB_OK);
							if (result == -2005530519 || result == -2005530520) {
#ifdef LOGGING
								WriteLog("EQGAME: d3d device failed - reinitializing 3d device");
#endif
								*(DWORD*)0x005FE990 = resx;
								*(DWORD*)0x005FE994 = resy;
								*(DWORD*)0x005FE998 = bpp;
								*(DWORD*)0x0063AE8C = refresh;
								((int(__cdecl*)())0x0043BBE2)();
							}
						}
						else {
							// when in full screen mode, this will end up killing window.
								*(DWORD*)0x005FE990 = resx;
								*(DWORD*)0x005FE994 = resy;
								*(DWORD*)0x005FE998 = bpp;
								*(DWORD*)0x0063AE8C = refresh;
								((int(__cdecl*)())0x0043BBE2)();
						}
					}
				}
				if (!ResolutionStored && *(DWORD*)(0x007F97D0) != 0)
				{
#ifdef LOGGING
					WriteLog("EQGAME: Storing Resolution Info (2)");
#endif
					DWORD ptr = *(DWORD*)(0x007F97D0);

					resx = *(DWORD*)(ptr + 0x7A28);
					resy = *(DWORD*)(ptr + 0x7A2C);
					bpp = *(DWORD*)(ptr + 0x7A20);
					refresh = *(DWORD*)(ptr + 0x7A30);

					ResolutionStored = true;
					eqgfxMod = *(DWORD*)(0x007F9C50);
					d3ddev = (DWORD)(eqgfxMod + 0x00A4F92C);

				}
				has_focus = true;
			}
			else {
				if (has_focus) {
#ifdef LOGGING
					WriteLog("EQGAME: Lost focus of window.  Different process in foreground.");
#endif
					ResetMouseFlags();
					ignore_right_click = true;
					ignore_left_click = true;
					focus_regained_time = 0;
					while (ShowCursor(TRUE) < 0);
				}
				has_focus = false;
				return 0;
			}
		}
		else if (!bWindowedMode && EQ_OBJECT_CEverQuest == NULL) {
			SetEQhWnd();
			ProcessAltState();
			SetWindowLong(EQhWnd, GWL_STYLE, stored_window_info.dwStyle | WS_CAPTION );
			SetWindowLong(EQhWnd, GWL_EXSTYLE, stored_window_info.dwExStyle);
#ifdef LOGGING
			WriteLog("EQGAME: EQ Object found Null Dropping Fullscreen (1)");
#endif
			if (!IsIconic(EQhWnd) && window_info_stored) {
				SetWindowPos(EQhWnd, HWND_TOP, stored_window_info.rcWindow.left, stored_window_info.rcWindow.top,
					stored_window_info.rcWindow.right - stored_window_info.rcWindow.left, stored_window_info.rcWindow.bottom - stored_window_info.rcWindow.top,
					SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOSENDCHANGING | SWP_SHOWWINDOW);
			}
			can_fullscreen = false;
			bWindowedMode = true;
			start_fullscreen = true;
			first_maximize = true;
		}
		SetEQhWnd();
		if (EQhWnd == GetForegroundWindow())
		{
			return CDisplay__Process_Events_Trampoline();
		}
		return 0;
	}
	int CDisplay__Render_World_Trampoline();
	int CDisplay__Render_World_Detour()
	{
		Pulse();
		return CDisplay__Render_World_Trampoline();
	}

	// Level of Detail preference bug fix
	int CDisplay__StartWorldDisplay_Trampoline(int zoneindex, int x);
	int CDisplay__StartWorldDisplay_Detour(int zoneindex, int x)
	{
		// this function always sets LoD to on, regardless of the user's preference
		int ret = CDisplay__StartWorldDisplay_Trampoline(zoneindex, x);

		int lod = *(char *)0x798AE8; // this is the preference the user has selected, loaded from eqOptions1.opt
		float(__cdecl * s3dSetDynamicLOD)(DWORD, float, float) = *(float(__cdecl **)(DWORD, float, float))0x007F986C; // this is a variable holding the pointer to the gfx dll function
		s3dSetDynamicLOD(lod, 1.0f, 100.0f); // apply the user's setting for real

		return ret;
	}
};

DETOUR_TRAMPOLINE_EMPTY(unsigned char Eqmachooks::CEverQuest__HandleWorldMessage_Trampoline(DWORD *,unsigned __int32,char *,unsigned __int32));
DETOUR_TRAMPOLINE_EMPTY(int Eqmachooks::CEQMusicManager__Set_Trampoline(int, int, int, int, int, int, int, int, int));
DETOUR_TRAMPOLINE_EMPTY(int Eqmachooks::CEQMusicManager__Play_Trampoline(int, int));
DETOUR_TRAMPOLINE_EMPTY(int __cdecl CEverQuest__DisplayScreen_Trampoline(char *));
DETOUR_TRAMPOLINE_EMPTY(DWORD WINAPI WritePrivateProfileStringA_tramp(LPCSTR,LPCSTR,LPCSTR, LPCSTR));
DETOUR_TRAMPOLINE_EMPTY(int __cdecl ProcessKeyDown_Trampoline(int));
DETOUR_TRAMPOLINE_EMPTY(int __cdecl ProcessKeyUp_Trampoline(int));
DETOUR_TRAMPOLINE_EMPTY(int __cdecl do_quit_Trampoline(int, int));
DETOUR_TRAMPOLINE_EMPTY(LRESULT WINAPI WndProc_Trampoline(HWND, UINT, WPARAM, LPARAM));
DETOUR_TRAMPOLINE_EMPTY(void WINAPI RightMouseDown_Trampoline(__int16, __int16));
DETOUR_TRAMPOLINE_EMPTY(void WINAPI RightMouseUp_Trampoline(__int16, __int16));
DETOUR_TRAMPOLINE_EMPTY(void WINAPI LeftMouseDown_Trampoline(__int16, __int16));
DETOUR_TRAMPOLINE_EMPTY(void WINAPI LeftMouseUp_Trampoline(__int16, __int16));
DETOUR_TRAMPOLINE_EMPTY(int Eqmachooks::CDisplay__Render_World_Trampoline());
DETOUR_TRAMPOLINE_EMPTY(int __cdecl  Eqmachooks::CDisplay__Process_Events_Trampoline());
DETOUR_TRAMPOLINE_EMPTY(HWND WINAPI CreateWindowExA_Trampoline(DWORD,LPCSTR,LPCSTR,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,LPVOID));
DETOUR_TRAMPOLINE_EMPTY(int __cdecl HandleMouseWheel_Trampoline(int));
DETOUR_TRAMPOLINE_EMPTY(int sub_4F35E5_Trampoline()); // command line parsing
DETOUR_TRAMPOLINE_EMPTY(int WINAPI sub_4B8231_Trampoline(int, signed int)); // MGB for BST
DETOUR_TRAMPOLINE_EMPTY(int Eqmachooks::CDisplay__StartWorldDisplay_Trampoline(int zoneindex, int x));

class CCharacterSelectWnd;

class CCharacterSelectWnd : public CSidlScreenWnd
{
public:
	void CCharacterSelectWnd::Quit(void);
};

#define EQ_FUNCTION_CCharacterSelectWnd__Quit 0x0040F3E0
#ifdef EQ_FUNCTION_CCharacterSelectWnd__Quit
typedef int(__thiscall* EQ_FUNCTION_TYPE_CCharacterSelectWnd__Quit)(void* this_ptr);
#endif

EQ_FUNCTION_TYPE_CCharacterSelectWnd__Quit EQMACMQ_REAL_CCharacterSelectWnd__Quit = NULL;
EQ_FUNCTION_TYPE_CEverQuest__InterpretCmd EQMACMQ_REAL_CEverQuest__InterpretCmd = NULL;

int __fastcall EQMACMQ_DETOUR_CCharacterSelectWnd__Quit(void* this_ptr, void* not_used)
{
	// Quit or Esc button pressed from character select screen
	if (!bWindowedMode)
	{
		SetEQhWnd();
		SetWindowLong(EQhWnd, GWL_STYLE, stored_window_info.dwStyle | WS_CAPTION );
		SetWindowLong(EQhWnd, GWL_EXSTYLE, stored_window_info.dwExStyle & ~(WS_EX_TOPMOST));
#ifdef LOGGING
		WriteLog("EQGAME: Going Windowed - Quit from char select");
#endif
		can_fullscreen = false;
		bWindowedMode = true;
		start_fullscreen = true;
		first_maximize = true;
	}

	return EQMACMQ_REAL_CCharacterSelectWnd__Quit(this_ptr);
}

int __cdecl CEverQuest__DisplayScreen_Detour(char *a1) {
	// this is the "Client Disconnected" screen - go back to windowed
	if (!bWindowedMode) {
		SetEQhWnd();
		SetWindowLong(EQhWnd, GWL_STYLE, stored_window_info.dwStyle | WS_CAPTION );
		SetWindowLong(EQhWnd, GWL_EXSTYLE, stored_window_info.dwExStyle & ~(WS_EX_TOPMOST));
#ifdef LOGGING
		WriteLog("EQGAME: Dropping to Windowed Mode - Client Disconnected");
#endif
		can_fullscreen = false;
		bWindowedMode = true;
		start_fullscreen = true;
		first_maximize = true;
	}

	return CEverQuest__DisplayScreen_Trampoline(a1);
}

LRESULT WINAPI WndProc_Detour(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if (EQ_OBJECT_CEverQuest != NULL && Msg != 16) {

		if (WM_WINDOWPOSCHANGED == Msg || WM_WINDOWPOSCHANGING == Msg || WM_NCCALCSIZE == Msg || WM_PAINT == Msg)
		{
			return 0;
		}
		
		if (WM_SYSCOMMAND == Msg)
		{
			if (wParam == SC_MINIMIZE)
			{
				return 0;
			}
		}
		
		if (WM_ACTIVATE == Msg || WM_ACTIVATEAPP == Msg)
		{
			if (wParam) {
				SetEQhWnd();
				//if (in_full_screen)
				//	start_fullscreen = true;
				//else
					 ShowWindow(EQhWnd, SW_SHOW);
				
				ResetMouseFlags();
				while (ShowCursor(FALSE) >= 0);
			}
			else
			{
				ResetMouseFlags();
				while (ShowCursor(TRUE) < 0);
			}
		}

		if (!bWindowedMode || start_fullscreen) {
			SetEQhWnd();
			if (EQ_OBJECT_CEverQuest->GameState > 0 && EQ_OBJECT_CEverQuest->GameState != 255 && can_fullscreen) {
				if (start_fullscreen && bWindowedMode && !IsIconic(EQhWnd)) {
					// this does not hit initially on startup
#ifdef LOGGING
					WriteLog("EQGAME: Going Fullscreen (3)");
#endif
					if (bWindowedMode && !window_info_stored) {
#ifdef LOGGING
						WriteLog("EQGAME: Storing window info");
#endif
						GetWindowInfo(EQhWnd, &stored_window_info);
						window_info_stored = true;
					}

					stored_window_info.dwStyle = GetWindowLong(EQhWnd, GWL_STYLE);
					stored_window_info.dwExStyle = GetWindowLong(EQhWnd, GWL_EXSTYLE);

					SetWindowLong(EQhWnd, GWL_STYLE,
						stored_window_info.dwStyle & ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU));

					SetWindowLong(EQhWnd, GWL_EXSTYLE,
						stored_window_info.dwExStyle & ~(WS_EX_DLGMODALFRAME |
							WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

					MONITORINFO monitor_info;
					monitor_info.cbSize = sizeof(monitor_info);
					GetMonitorInfo(MonitorFromWindow(EQhWnd, MONITOR_DEFAULTTONEAREST),
						&monitor_info);
					RECT window_rect(monitor_info.rcMonitor);

					WINDOWPLACEMENT window_placement;
					window_placement.length = sizeof(window_placement);

					if (first_maximize) {
						GetWindowPlacement(EQhWnd, &window_placement);
						window_placement.showCmd = SW_MINIMIZE;
						SetWindowPlacement(EQhWnd, &window_placement);
						window_placement.showCmd = SW_MAXIMIZE;
						SetWindowPlacement(EQhWnd, &window_placement);
					}
					if (!IsIconic(EQhWnd) && window_info_stored) {
						SetWindowPos(EQhWnd, HWND_TOP, window_rect.left, window_rect.top,
							window_rect.right - window_rect.left, window_rect.bottom - window_rect.top,
							SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOSENDCHANGING | SWP_SHOWWINDOW);
					}

					bWindowedMode = false;		
					first_maximize = false;
				}
			}
		}
	}
	else {
		if (!bWindowedMode) {
			//MessageBox(NULL, "C3", NULL, MB_OK);
#ifdef LOGGING
			WriteLog("EQGAME: Dropping Fullscreen (2)");
#endif
			SetWindowLong(EQhWnd, GWL_STYLE, stored_window_info.dwStyle | WS_CAPTION );
			SetWindowLong(EQhWnd, GWL_EXSTYLE, stored_window_info.dwExStyle | WS_EX_APPWINDOW);

			if (!IsIconic(EQhWnd) && window_info_stored) {
				SetWindowPos(EQhWnd, HWND_TOP, stored_window_info.rcWindow.left, stored_window_info.rcWindow.top,
					stored_window_info.rcWindow.right - stored_window_info.rcWindow.left, stored_window_info.rcWindow.bottom - stored_window_info.rcWindow.top,
					SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOSENDCHANGING | SWP_SHOWWINDOW);
			}
			can_fullscreen = false;
			bWindowedMode = true;
			start_fullscreen = true;
			first_maximize = true;
		}
		if (!title_set) {
			UpdateTitle();
			title_set = true;
		}
	}
	LRESULT res = WndProc_Trampoline(hWnd, Msg, wParam, lParam);
	return res;
}

void SkipLicense()
{
	DWORD offset = (DWORD)eqmain_dll + 0x255D2;
	const char test1[] = { 0xEB }; // , 0x90, 0x90, 0x90, 0x90, 0x90};
	PatchA((DWORD*)offset, &test1, sizeof(test1));
}

void SkipSplash()
{
	// Set timer for intro splash screens to 0
	const char test1[] = { 0x00, 0x00 };

	DWORD offset = (DWORD)eqmain_dll + 0x21998;
	PatchA((DWORD*)offset, &test1, sizeof(test1));
}

void SetDInputCooperativeMode()
{
	// Set timer for intro splash screens to 0
	const char test1[] = { (char)(0x06) };

	DWORD offset = (DWORD)eqmain_dll + 0x3400F;
	PatchA((DWORD*)offset, &test1, sizeof(test1));
}

// MGB for BST
int WINAPI sub_4B8231_Detour(int a1, signed int a2) {
	if (a1 == 15 && a2 == 35)
		return 1;
	return sub_4B8231_Trampoline(a1, a2);
}

// command line parsing
int sub_4F35E5_Detour(){

		const char*v3;
		int v22;
		char exename[256];
		v3 = GetCommandLineA();
		*(int*)0x00809464 = sscanf(
			v3,
			"%s %s %s %s %s %s %s %s %s",
			&exename,
			(char*)0x806410,
			(char*)0x806510,
			(char*)0x806610,
			(char*)0x806710,
			(char*)0x806810,
			(char*)0x806910,
			(char*)0x806A10,
			(char*)0x806B10);

		DWORD v59 = 0;
		int v20 = 0x00806410;

		if (*(DWORD*)0x00809464 > 1)
		{
			while (1)
			{
				v22 = strlen((const char *)v20);
				if (v22 + strlen((char *)0x00807B08) + 2 < 0x1C0)
				{
					strcat((char *)0x00807B08, (const char *)v20);
					strcat((char *)0x00807B08, " ");
				}
				if (!_strnicmp((const char *)v20, "nosound.txt", 5u))
					break;

				if (!_strnicmp((const char *)v20, "/ticket:", 8u))
				{
					char ticket_[63];
					strncpy(ticket_, (const char *)(v20 + 8), 0x3Fu);
					if (strlen(ticket_) > 1 && ticket_[strlen(ticket_) - 1] == 34)
						ticket_[strlen(ticket_)-1] = 0;

					// original code
					// strncpy((char *)0x00807D48, ticket_, 0x3Fu);
					// MessageBox(NULL, ticket_, NULL, MB_OK);

					// replacement code
					std::string userpass = ticket_;

					std::string username = userpass.substr(0, userpass.find("/"));
					std::string password = userpass.substr(userpass.find("/") + 1);

					if (username.length() > 3 && password.length() > 3) {
						strcpy((char *)0x807AC8, username.c_str()); // username
						strcpy((char *)0x807924, password.c_str()); // password = > likely needs encrypted pass?
					}
				}
				else if (!_strnicmp((const char *)v20, "/title:", 7u))
				{
					char my_title[63];
					strncpy(my_title, (const char *)(v20 + 7), 0x7Fu);
					if (strlen(my_title) > 1)
						new_title = my_title;
				}

				++v59;
				v20 += 256;
				if (v59 >= *(DWORD*)0x00809464)
					break;
			}

		}

	return sub_4F35E5_Trampoline();
}

extern bool mouse_looking;
extern POINT savedRMousePos;

void WINAPI RightMouseUp_Detour(__int16 a1, __int16 a2) {
	if (ignore_right_click_up)
		return;

	return RightMouseUp_Trampoline(a1, a2);
}

void WINAPI RightMouseDown_Detour(__int16 a1, __int16 a2) {

	if (ignore_right_click) {
		if (!(GetAsyncKeyState(VK_RBUTTON) & 0x8000)) {
			if (has_focus && focus_regained_time > 0) {
				if ((GetTickCount() - focus_regained_time) > 10) {
					ignore_right_click_up = false;
					ignore_right_click = false;
					ignore_left_click_up = false;
					ignore_left_click = false;
					focus_regained_time = 0;
				}
				else {
					ignore_right_click_up = true;
					return;
				}
			}
			else {
				ignore_right_click_up = true;
				return;
			}
		}
		else {
			ignore_right_click = false;
			ignore_right_click_up = false;
		}
	}

	RightMouseDown_Trampoline(a1, a2);
	if(EQ_OBJECT_CEverQuest != NULL && EQ_OBJECT_CEverQuest->GameState == 5) {
		if (*(DWORD*)0x007985EA == 0x00010001) {
			mouse_looking = true;
			if (savedRMousePos.x == 0 && savedRMousePos.y == 0)
			{
				savedRMousePos.x = *(DWORD*)0x008092E8;
				savedRMousePos.y = *(DWORD*)0x008092EC;
			}
		}
	}
	return;
}

void WINAPI LeftMouseUp_Detour(__int16 a1, __int16 a2) {
	if (ignore_left_click_up)
		return;

	return LeftMouseUp_Trampoline(a1, a2);
}

void WINAPI LeftMouseDown_Detour(__int16 a1, __int16 a2) {

	if (ignore_left_click) {
		if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
			if (has_focus && focus_regained_time > 0) {
				if ((GetTickCount() - focus_regained_time) > 10) {
					ignore_left_click_up = false;
					ignore_left_click = false;
					ignore_right_click_up = false;
					ignore_right_click = false;
					focus_regained_time = 0;
				}
				else {
					ignore_left_click_up = true;
					return;
				}
			}
			else {
				ignore_left_click_up = true;
				return;
			}
		}
		else {
			ignore_left_click = false;
			ignore_left_click_up = false;
		}
	}
	return LeftMouseDown_Trampoline(a1, a2);
}

void PatchSaveBypass()
{
	//const char test1[] =  { 0xEB, 0x21 };
	//PatchA((DWORD*)0x0052B70A, &test1, sizeof(test1));
	const char test1[] = { 0x00, 0x00 };
	PatchA((DWORD*)0x0052B716, &test1, sizeof(test1));
	// OP_Save
	// this stops sending OP_SAVE
	//const char test2[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
	//PatchA((DWORD*)0x00536797, &test2, sizeof(test2));
	// this forces sending OP_SAVE with size of 0.
	const char test2[] = { 0x00, 0x00 };
	PatchA((DWORD*)0x0053678C, &test2, sizeof(test2));

	//SetCooperativeLevel to 0x06 instead of 0x10 for eqgame.exe
	//const char test3[] = { 0x06 };
	//PatchA((DWORD*)0x0055B844, &test3, sizeof(test3));

	// Inverse NewUI flags for OldUI naming
	const char test4[] = { 0x00 };
	PatchA((DWORD*)0x00559866, &test4, sizeof(test4));
	
	// Inverse NewUI flags for OldUI naming
	const char test5[] = { 0x00 };
	PatchA((DWORD*)0x005598C1, &test5, sizeof(test5));

	// Inverse NewUI flags for OldUI naming
	const char test6[] = { 0x01 };
	PatchA((DWORD*)0x005598CB, &test6, sizeof(test6));

	// Change name of setting: NewUI -> OldUI
	const char test7[] = { 0x4F, 0x6C, 0x64 /*"Old"*/ };
	PatchA((DWORD*)0x0060DB1C, &test7, sizeof(test7));

	// Change name of command: /newui -> /oldui
	const char test8[] = { 0x6F, 0x6C, 0x64 /*"old"*/ };
	PatchA((DWORD*)0x0060B6E8, &test8, sizeof(test8));

	// Change string of command /oldui to match functionality:
	const char test9[] = { 0xA5 };
	PatchA((DWORD*)0x4FFAC2, &test9, sizeof(test9));
	
	// Change string of command /oldui to match functionality:
	const char test10[] = { 0xA4 };
	PatchA((DWORD*)0x4FFAE0, &test10, sizeof(test10));

	// Inverse NewUI flags for OldUI naming
	const char test11[] = { 0xC6, 0x05 };
	PatchA((DWORD*)0x005598C5, &test11, sizeof(test11));

	// Face picker enabled without Luclin models
	const char test12[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0xEB };
	PatchA((DWORD*)0x005431C1, &test12, sizeof(test12));

	if (g_bEnableBrownSkeletons)
	{
		const char test13[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0xEB };
		PatchA((DWORD*)0x0049F28F, &test13, sizeof(test13));
	}
}

typedef int(__cdecl *_s3dSetStringSpriteYonClip)(intptr_t, int, float);
_s3dSetStringSpriteYonClip s3dSetStringSpriteYonClip_Trampoline;
int __cdecl s3dSetStringSpriteYonClip_Detour(intptr_t sprite, int a2, float distance)
{
	//Log("s3dSetStringSpriteYonClip_Detour 0x%lx %d %f", sprite, a2, distance);
	if (g_bEnableExtendedNameplates == false)
		return s3dSetStringSpriteYonClip_Trampoline(sprite, a2, distance);

	if ((*(unsigned int *)&distance) == 0x428c0000) // 70.0f
	{
		a2 = 0;
		//distance = 1000.0f;
	}

	return s3dSetStringSpriteYonClip_Trampoline(sprite, a2, distance);
}
HWND WINAPI CreateWindowExA_Detour(DWORD     dwExStyle,
	LPCSTR   lpClassName,
	LPCSTR   lpWindowName,
	DWORD     dwStyle,
	int       x,
	int       y,
	int       nWidth,
	int       nHeight,
	HWND      hWndParent,
	HMENU     hMenu,
	HINSTANCE hInstance,
	LPVOID    lpParam) {

	can_fullscreen = false;
	first_maximize = true;
	if (!eqmain_dll) {
		eqmain_dll = GetModuleHandleA("eqmain.dll");
		if (eqmain_dll) {
			DWORD checkpoint = *(DWORD*)0x807410;
			DWORD delta = checkpoint - (DWORD)eqmain_dll;
			// if new_main_dll is at right location in dll
			// then add bypass for skipping license and splash screen
			if (delta == 0x25300) {
				//SkipLicense();
				if(g_bEnableExtendedNameplates)
				{
					HINSTANCE heqGfxMod = GetModuleHandle("eqgfx_dx8.dll");
					if (heqGfxMod)
					{
						_s3dSetStringSpriteYonClip s3dSetStringSpriteYonClip = (_s3dSetStringSpriteYonClip)GetProcAddress(heqGfxMod, "s3dSetStringSpriteYonClip");
						if(s3dSetStringSpriteYonClip)
						{
							( _s3dSetStringSpriteYonClip)s3dSetStringSpriteYonClip_Trampoline = (_s3dSetStringSpriteYonClip)DetourFunction((PBYTE)s3dSetStringSpriteYonClip, (PBYTE)s3dSetStringSpriteYonClip_Detour);
						}
					}
				}
				SkipSplash();
				//SetDInputCooperativeMode();
			}
			PatchSaveBypass();
		}
	}
	return CreateWindowExA_Trampoline(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

int __cdecl do_quit_Detour(int a1, int a2) {
	if (!a2 || !*(BYTE *)a2)
	{
		if (*(BYTE*)0x7CF29C)
		{
			// we are locked
		}
		else {
			// Quit or Esc button pressed from character select screen
			if (!bWindowedMode)
			{
				SetEQhWnd();
				SetWindowLong(EQhWnd, GWL_STYLE, stored_window_info.dwStyle | WS_CAPTION );
				SetWindowLong(EQhWnd, GWL_EXSTYLE, stored_window_info.dwExStyle & ~(WS_EX_TOPMOST));
#ifdef LOGGING
				WriteLog("EQGAME: Going Windowed - Used /quit from in game");
#endif
				can_fullscreen = false;
				bWindowedMode = true;
				start_fullscreen = true;
				first_maximize = true;
			}
		}
	}
	return do_quit_Trampoline(a1, a2);
}

int __cdecl ProcessKeyUp_Detour(int a1)
{
#ifdef LOGGING
	std::string outstring;
	outstring = "EQGAME: KeyPress Up = ";
	outstring += std::to_string(a1);
	WriteLog(outstring);
#endif
	if (!has_focus || has_focus && ((GetTickCount() - focus_regained_time) <= 10))
		return ProcessKeyUp_Trampoline(0x00);

	return ProcessKeyUp_Trampoline(a1);
}

int __cdecl ProcessKeyDown_Detour(int a1)
{
#ifdef LOGGING
	std::string outstring;
	outstring = "EQGAME: KeyPress Down = ";
	outstring += std::to_string(a1);
	WriteLog(outstring);
#endif

	if (!has_focus || has_focus && ((GetTickCount() - focus_regained_time) <= 10))
		return ProcessKeyDown_Trampoline(0x00);

	SetEQhWnd();
	if (EQ_OBJECT_CEverQuest != NULL && can_fullscreen && EQ_OBJECT_CEverQuest->GameState > 0 && a1 == 0x1c && AltPressed() && !ShiftPressed() && !CtrlPressed()) {
#ifdef LOGGING
		WriteLog("EQGAME: Alt - Enter Detected");
#endif
		//MessageBox(NULL, "Alt-Enter Detected", NULL, MB_OK);
		if (bWindowedMode) {
#ifdef LOGGING
			WriteLog("EQGAME: Currently in windowed mode.");
#endif
			ResetMouseFlags();

			// store window positions
			if (!window_info_stored) {
				GetWindowInfo(EQhWnd, &stored_window_info);
				window_info_stored = true;
			}

			// removed borders, etc.
			SetWindowLong(EQhWnd, GWL_STYLE,
				stored_window_info.dwStyle & ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU));

			SetWindowLong(EQhWnd, GWL_EXSTYLE,
				stored_window_info.dwExStyle & ~(WS_EX_DLGMODALFRAME |
					WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

			// find points to use for current monitor
			MONITORINFO monitor_info;
			monitor_info.cbSize = sizeof(monitor_info);
			GetMonitorInfo(MonitorFromWindow(EQhWnd, MONITOR_DEFAULTTONEAREST),
				&monitor_info);
			RECT window_rect(monitor_info.rcMonitor);

			WINDOWPLACEMENT window_placement;
			window_placement.length = sizeof(window_placement);

			if (first_maximize) {
				GetWindowPlacement(EQhWnd, &window_placement);
				window_placement.showCmd = SW_MINIMIZE;
				SetWindowPlacement(EQhWnd, &window_placement);
				window_placement.showCmd = SW_MAXIMIZE;
				SetWindowPlacement(EQhWnd, &window_placement);
			}
			SetWindowPos(EQhWnd, HWND_TOP, window_rect.left, window_rect.top,
				window_rect.right - window_rect.left, window_rect.bottom - window_rect.top,
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOSENDCHANGING | SWP_SHOWWINDOW);

			char szDefault[255];

			sprintf(szDefault, "%s", "FALSE");
			WritePrivateProfileStringA_tramp("Options", "WindowedMode", szDefault, "./eqclient.ini");
			start_fullscreen = true;
			first_maximize = false;
		}
		else
		{
			//ResetMouseFlags();
#ifdef LOGGING
			WriteLog("EQGAME: Currently in full screen mode.");
#endif
			SetWindowLong(EQhWnd, GWL_STYLE, stored_window_info.dwStyle | WS_CAPTION );
			SetWindowLong(EQhWnd, GWL_EXSTYLE, stored_window_info.dwExStyle);
			if (window_info_stored) {
				SetWindowPos(EQhWnd, HWND_TOP, stored_window_info.rcWindow.left, stored_window_info.rcWindow.top,
					stored_window_info.rcWindow.right - stored_window_info.rcWindow.left, stored_window_info.rcWindow.bottom - stored_window_info.rcWindow.top,
					SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOSENDCHANGING | SWP_SHOWWINDOW);
			}
			char szDefault[255];
			sprintf(szDefault, "%s", "TRUE");
			WritePrivateProfileStringA_tramp("Options", "WindowedMode", szDefault, "./eqclient.ini");
			start_fullscreen = false;
		}
		bWindowedMode = !bWindowedMode;
		return ProcessKeyDown_Trampoline(0x00); // null
	}

	return ProcessKeyDown_Trampoline(a1);
}

int new_height;
int new_width;

DWORD WINAPI WritePrivateProfileStringA_detour(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpString, LPCSTR lpFileName)
{
	if (lstrcmp(lpAppName, "Positions") == 0) {
		// if in fullscreen mode, we do not want to write out positions to eqw.ini
		// switching from char select can reset also
		if (EQ_OBJECT_CEverQuest != NULL && EQ_OBJECT_CEverQuest->GameState != 5 && lstrcmp(lpString, "0") == 0) {
			return true;
		}
		if (!bWindowedMode)
			return true;
	}
	DWORD ret = WritePrivateProfileStringA_tramp(lpAppName, lpKeyName, lpString, lpFileName);
	
	if (lstrcmp(lpAppName, "VideoMode") == 0) {
		if (lstrcmp(lpKeyName, "Height") == 0) {
			if (!bWindowedMode)
				window_info_stored = false;
			new_height = atoi(lpString);
		} else if (lstrcmp(lpKeyName, "Width") == 0) {
			if (!bWindowedMode)
				window_info_stored = false;
			new_width = atoi(lpString);
		}
		else if (lstrcmp(lpKeyName, "BitsPerPixel") == 0) {

			if (resy != new_height || resx != new_width) {
				ResolutionStored = false;
				resx = new_width;
				resy = new_height;

				if (!bWindowedMode) {
					// go out of full screen
					SetEQhWnd();
					SetWindowLong(EQhWnd, GWL_STYLE, stored_window_info.dwStyle | WS_CAPTION );
					SetWindowLong(EQhWnd, GWL_EXSTYLE, stored_window_info.dwExStyle);
					
					// eqw will adjust window to default loc for this resolution
					// store the windowed location
					GetWindowInfo(EQhWnd, &stored_window_info);
					window_info_stored = true;


					// removed borders, etc.
					SetWindowLong(EQhWnd, GWL_STYLE,
						stored_window_info.dwStyle & ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU));

					SetWindowLong(EQhWnd, GWL_EXSTYLE,
						stored_window_info.dwExStyle & ~(WS_EX_DLGMODALFRAME |
							WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

					// restore back to full screen
					MONITORINFO monitor_info;
					monitor_info.cbSize = sizeof(monitor_info);
					GetMonitorInfo(MonitorFromWindow(EQhWnd, MONITOR_DEFAULTTONEAREST),
						&monitor_info);
					RECT window_rect(monitor_info.rcMonitor);

					WINDOWPLACEMENT window_placement;
					window_placement.length = sizeof(window_placement);

					SetWindowPos(EQhWnd, HWND_TOP, window_rect.left, window_rect.top,
						window_rect.right - window_rect.left, window_rect.bottom - window_rect.top,
						SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOSENDCHANGING | SWP_SHOWWINDOW);

				} else {
					// we need to save the new windowed mode position
					GetWindowInfo(EQhWnd, &stored_window_info);
					first_maximize = true;
				}
			}
		}
	}

	return ret;
}


const bool IsMouseOverWindow(HWND hWnd, const int mx, const int my,
	const bool inClientSpace /*= false */)
{
	if (!IsWindowVisible(hWnd))
		return false;

	RECT windowRect;

	// Get the window in screen space
	::GetWindowRect(hWnd, &windowRect);

	if (inClientSpace)
	{
		POINT offset;
		offset.x = offset.y = 0;
		ClientToScreen(hWnd, &offset);

		// Offset the window to client space
		windowRect.left -= offset.x;
		windowRect.top -= offset.y;
		// NOTE: left and top should now be 0, 0
		windowRect.right -= offset.x;
		windowRect.bottom -= offset.y;
	}

	// Test if mouse over window
	POINT cursorPos = { mx, my };
	return PtInRect(&windowRect, cursorPos);
}

signed int __cdecl ProcessMouseEvent_Hook()
{
	bool shouldRetEarly = false;
	signed int ret = 0;

	SetEQhWnd();

#ifdef FREE_THE_MOUSE
	POINT p;
	GetCursorPos(&p);
	BYTE dval = *(BYTE*)0x007985EA;

	if (dval == 0) {
		if (!IsMouseOverWindow(EQhWnd, p.x, p.y, false))
		{
			EQ_flush_mouse();
			EQ_SetMousePosition(32767, 32767);
			while (ShowCursor(FALSE) >= 0);
			if (posPoint.x == 0 && posPoint.y == 0)
			{
				return ret;
			}
		}
		// we have stored cursor positions
		// restore cursor to previous position
		if (posPoint.x != 0 && posPoint.y != 0 && (GetForegroundWindow() == EQhWnd))
		{
			POINT pt;
			pt.x = posPoint.x;
			pt.y = posPoint.y;
			ClientToScreen(EQhWnd, &pt);
			SetCursorPos(pt.x, pt.y);
			EQ_SetMousePosition(posPoint.x, posPoint.y);
			posPoint.x = 0;
			posPoint.y = 0;
			shouldRetEarly = true;
			while (ShowCursor(TRUE) < 0);
		}
	}
#endif

	ret = return_ProcessMouseEvent();

	if (!RightHandMouse) {
		*(BYTE*)0x00798616 = BYTE1(*(DWORD*)0x8090B4) != 0;
		*(BYTE*)0x00798617 = BYTE2(*(DWORD*)0x8090B4) != 0;
	}


	if (mouse_looking && (GetForegroundWindow() == EQhWnd))
	{
		if (savedRMousePos.x != 0 && savedRMousePos.y != 0)
		{
			POINT pt;
			pt.x = savedRMousePos.x;
			pt.y = savedRMousePos.y;
			ClientToScreen(EQhWnd, &pt);
			SetCursorPos(pt.x, pt.y);
			EQ_SetMousePosition(savedRMousePos.x, savedRMousePos.y);
		}
	}
	else if (!mouse_looking || (GetForegroundWindow() != EQhWnd))
	{
		savedRMousePos.x = 0;
		savedRMousePos.y = 0;
	}

#ifdef FREE_THE_MOUSE
	if (shouldRetEarly)
	{
		return ret;
	}
	if (EQhWnd)
	{
		if (ScreenToClient(EQhWnd, &p))
		{
			if (dval == 0)
			{
				*(DWORD*)0x008092E8 = p.x;
				*(DWORD*)0x008092EC = p.y;
			}
			else
			{
				if (posPoint.x == 0 && posPoint.y == 0)
				{
					posPoint.x = *(DWORD*)0x008092E8;
					posPoint.y = *(DWORD*)0x008092EC;
					while (ShowCursor(FALSE) >= 0);
				}
			}
		}
	}
#endif
	return ret;
}

/*signed int __cdecl SetMouseCenter_Hook()//55B722
{
	signed int retval = return_SetMouseCenter();
	if (EQhWnd)
	{
		RECT windowRect;
		::GetWindowRect(EQhWnd, &windowRect);
		int width = windowRect.right - windowRect.left;
		int height = windowRect.bottom - windowRect.top;
		POINT pt;
		pt.x = posPoint.x;
		pt.y = posPoint.y;
		ClientToScreen(EQhWnd, &pt);
		SetCursorPos(pt.x, pt.y);

	}
	return retval;
}*/
extern void LoadIniSettings();

int __fastcall EQMACMQ_DETOUR_CEverQuest__InterpretCmd(void* this_ptr, void* not_used, class EQPlayer* a1, char* a2)
{
	if (a1 == NULL || a2 == NULL)
	{
		return EQMACMQ_REAL_CEverQuest__InterpretCmd(this_ptr, a1, a2);
	}

	if (strlen(a2) == 0)
	{
		return EQMACMQ_REAL_CEverQuest__InterpretCmd(this_ptr, NULL, NULL);
	}

	// double slashes not needed, convert "//" to "/" by removing first character
	if (strncmp(a2, "//", 2) == 0)
	{
		memmove(a2, a2 + 1, strlen(a2));
	}
	if (strcmp(a2, "/fps") == 0) {
		// enable fps indicator
		if (eqgfxMod) {
			if (*(BYTE*)(eqgfxMod + 0x00A4F770) == 0)
				*(BYTE*)(eqgfxMod + 0x00A4F770) = 1;
			else
				*(BYTE*)(eqgfxMod + 0x00A4F770) = 0;
		}
		return EQMACMQ_REAL_CEverQuest__InterpretCmd(this_ptr, NULL, NULL);
	}

	if (strcmp(a2, "/rfps") == 0) {
		LoadIniSettings();

		return EQMACMQ_REAL_CEverQuest__InterpretCmd(this_ptr, NULL, NULL);
	}

	else if ((strcmp(a2, "/raiddump") == 0) || (strcmp(a2, "/outputfile raid") == 0)) {
		// beginning of raid structure
		DWORD raid_ptr = 0x007914D0;
		DWORD name_ptr = raid_ptr + 72;
		DWORD level_ptr = raid_ptr + 136;
		DWORD class_ptr = raid_ptr + 144;
		DWORD is_leader_ptr = raid_ptr + 275;
		DWORD group_num_ptr = raid_ptr + 276;

		CHAR RaidLeader[64];
		CHAR CharName[64];
		CHAR Class[64];
		CHAR Level[8];
		int i = 0;
		if (*(BYTE*)(raid_ptr) == 1) {
			memcpy(RaidLeader, (char *)(0x794FA0), 64);
			char v50[64];
			char v51[256];
			time_t a2;
			a2 = time(0);
			struct tm * v4;
			v4 = localtime(&a2);
			sprintf(
				v50,
				"%04d%02d%02d-%02d%02d%02d",
				v4->tm_year + 1900,
				v4->tm_mon + 1,
				v4->tm_mday,
				v4->tm_hour,
				v4->tm_min,
				v4->tm_sec);
			sprintf(v51, "RaidRoster-%s.txt", v50);
			FILE *result;
			result = fopen(v51, "w");
			if (result != NULL) {

				while (*(BYTE *)(raid_ptr) == 1) {
					memcpy(CharName, (char *)(name_ptr), 64);
					memcpy(Level, (char *)(level_ptr), 8);
					memcpy(Class, (char *)(class_ptr), 64);
					bool group_leader = (bool)*(CHAR *)(is_leader_ptr);
					int group_num = (int)*(CHAR *)(group_num_ptr);
					group_num++;
					std::string type = "";
					if (group_leader)
						type = "Group Leader";
					if (strcmp(CharName, RaidLeader) == 0)
						type = "Raid Leader";
					raid_ptr++;
					name_ptr += 208;
					level_ptr += 208;
					class_ptr += 208;
					is_leader_ptr += 208;
					group_num_ptr += 208;

					fprintf(result, "%d\t%s\t%s\t%s\t%s\t%s\n", group_num, CharName, Level, Class, type.c_str(), "");
				}
				fclose(result);
			}
		}
		return EQMACMQ_REAL_CEverQuest__InterpretCmd(this_ptr, NULL, NULL);
	}

	return EQMACMQ_REAL_CEverQuest__InterpretCmd(this_ptr, a1, a2);
}

int sprintf_Detour_loadskin(char *const Buffer, const char *const format, ...)
{
	va_list ap;

	va_start(ap, format);
	char *cxstr = va_arg(ap, char *);
	cxstr += 20; // get the buffer inside the CXStr
	char useini = va_arg(ap, char);
	va_end(ap);

	return sprintf(Buffer, format, cxstr, useini);
}

DWORD gmfadress = 0;
DWORD wpsaddress = 0;
DWORD swAddress = 0;
DWORD cwAddress = 0;
DWORD swlAddress = 0;
DWORD uwAddress = 0;

PVOID pHandler;
bool bInitalized=false;

void CheckPromptUIChoice()
{
	char szResult[255];
	char szDefault[255];
	sprintf(szDefault, "%s", "NONE");
	DWORD error = GetPrivateProfileStringA("Defaults", "OldUI", szDefault, szResult, 255, "./eqclient.ini");
	if (strcmp(szResult, "NONE") == 0) // File not found
	{
		int Result = MessageBox(EQhWnd, "This server supports running both the Stone (Pre-Luclin) UI, and the more modern Luclin UI.\n Would you like to use the Luclin UI? This can later be adjusted ingame by typing /oldui.", "EverQuest", MB_YESNO);
		if (Result == IDYES)
		{
			WritePrivateProfileStringA_tramp("Defaults", "OldUI", "FALSE", "./eqclient.ini");
		}
		else
		{
			WritePrivateProfileStringA_tramp("Defaults", "OldUI", "TRUE", "./eqclient.ini");
		}

	}
}


void CheckClientMiniMods()
{
	char szResult[255];
	char szDefault[255];
	sprintf(szDefault, "%s", "NONE");
	DWORD error = GetPrivateProfileStringA("Defaults", "EnableBrownSkeletonHack", szDefault, szResult, 255, "./eqclient.ini");
	if (strcmp(szResult, "FALSE") == 0) // False
	{
		g_bEnableBrownSkeletons = false;
	}
	else if (strcmp(szResult, "NONE") == 0) // Not found
	{
		WritePrivateProfileStringA_tramp("Defaults", "EnableBrownSkeletonHack", "FALSE", "./eqclient.ini");
	}
	else // any other value (1, true, potato)
	{
		g_bEnableBrownSkeletons = true;
	}


	error = GetPrivateProfileStringA("Defaults", "EnableExtendedNameplateDistance", szDefault, szResult, 255, "./eqclient.ini");
	if (strcmp(szResult, "FALSE") == 0) // False
	{
		g_bEnableExtendedNameplates = false;
	}
	else if (strcmp(szResult, "NONE") == 0) // Not found
	{
		g_bEnableExtendedNameplates = false;
		WritePrivateProfileStringA_tramp("Defaults", "EnableExtendedNameplateDistance", "FALSE", "./eqclient.ini");
	}
	else
	{
		g_bEnableExtendedNameplates = true;
	}

	error = GetPrivateProfileStringA("Defaults", "EnableClassicMusic", szDefault, szResult, 255, "./eqclient.ini");
	if (strcmp(szResult, "FALSE") == 0) // False
	{
		g_bEnableClassicMusic = false;
	}
	else if (strcmp(szResult, "NONE") == 0) // Not found
	{
		g_bEnableClassicMusic = false;
		WritePrivateProfileStringA_tramp("Defaults", "EnableClassicMusic", "FALSE", "./eqclient.ini");
	}
	else
	{
		g_bEnableClassicMusic = true;
		EzDetour(0x00550AF8, &Eqmachooks::CEQMusicManager__Set_Detour, &Eqmachooks::CEQMusicManager__Set_Trampoline);
		EzDetour(0x004D54C1, &Eqmachooks::CEQMusicManager__Play_Detour, &Eqmachooks::CEQMusicManager__Play_Trampoline);
	}
}

void InitHooks()
{
	//bypass filename req
	const char test3[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,0x90, 0xEB, 0x1B, 0x90, 0x90, 0x90, 0x90 };
	PatchA((DWORD*)0x005595A7, &test3, sizeof(test3));

	PatchSaveBypass();
	//heqwMod
	HMODULE hkernel32Mod = GetModuleHandle("kernel32.dll");
	wpsaddress = (DWORD)GetProcAddress(hkernel32Mod, "WritePrivateProfileStringA");
	HMODULE huser32Mod = GetModuleHandleA("user32.dll");

	swAddress = (DWORD)GetProcAddress(huser32Mod, "ShowWindow");
	cwAddress = (DWORD)GetProcAddress(huser32Mod, "CreateWindowExA");
	swlAddress = (DWORD)GetProcAddress(huser32Mod, "SetWindowLong");
	EzDetour(0x004AA8BC, &Eqmachooks::CDisplay__Render_World_Detour, &Eqmachooks::CDisplay__Render_World_Trampoline);
	EzDetour(cwAddress, CreateWindowExA_Detour, CreateWindowExA_Trampoline);
	//here to fix the no items on corpse bug - eqmule
	EzDetour(0x004E829F, &Eqmachooks::CEverQuest__HandleWorldMessage_Detour, &Eqmachooks::CEverQuest__HandleWorldMessage_Trampoline);
	EzDetour(wpsaddress, WritePrivateProfileStringA_detour, WritePrivateProfileStringA_tramp);

	heqwMod = GetModuleHandle("eqw.dll");

	return_ProcessMouseEvent = (ProcessGameEvents_t)DetourFunction((PBYTE)o_MouseEvents, (PBYTE)ProcessMouseEvent_Hook);
	//return_SetMouseCenter = (ProcessGameEvents_t)DetourFunction((PBYTE)o_MouseCenter, (PBYTE)SetMouseCenter_Hook);

	eqgfxMod = *(DWORD*)(0x007F9C50);
	d3ddev = (DWORD)(eqgfxMod + 0x00A4F92C);
		
	EzDetour(0x0055A4F4, WndProc_Detour, WndProc_Trampoline);
	// This detours key press down handler, so we can capture alt-enter to switch video modes
	EzDetour(EQ_FUNCTION_ProcessKeyDown, ProcessKeyDown_Detour, ProcessKeyDown_Trampoline);
	EzDetour(EQ_FUNCTION_ProcessKeyUp, ProcessKeyUp_Detour, ProcessKeyUp_Trampoline);
	
	EzDetour(EQ_FUNCTION_CEverQuest__RMouseDown, RightMouseDown_Detour, RightMouseDown_Trampoline);
	EzDetour(EQ_FUNCTION_CEverQuest__RMouseUp, RightMouseUp_Detour, RightMouseUp_Trampoline);
	EzDetour(EQ_FUNCTION_CEverQuest__LMouseDown, LeftMouseDown_Detour, LeftMouseDown_Trampoline);
	EzDetour(EQ_FUNCTION_CEverQuest__LMouseUp, LeftMouseUp_Detour, LeftMouseUp_Trampoline);
	EzDetour(0x004FA8C5, do_quit_Detour, do_quit_Trampoline);
	
	EzDetour(0x00538CE6, CEverQuest__DisplayScreen_Detour, CEverQuest__DisplayScreen_Trampoline);

	// Add MGB for Beastlords
	EzDetour(0x004B8231, sub_4B8231_Detour, sub_4B8231_Trampoline);

	// Fix bug with Level of Detail setting always being turned on ignoring user's preference
	EzDetour(0x004A849E, &Eqmachooks::CDisplay__StartWorldDisplay_Detour, &Eqmachooks::CDisplay__StartWorldDisplay_Trampoline);

	// Fix bug with option window UI skin load dialog always loading default instead of selected skin
	uintptr_t addr = (intptr_t)sprintf_Detour_loadskin - (intptr_t)0x00426115;
	PatchA((void *)0x00426111, &addr, 4);

	// Fix bug with spell casting bar not showing at high spell haste values
	unsigned char jge = 0x7D;
	PatchA((void *)0x004c55b7, &jge, 1);

	//this one is here for eqplaynice - eqmule

	EzDetour(0x0055AFE2, &Eqmachooks::CDisplay__Process_Events_Detour, &Eqmachooks::CDisplay__Process_Events_Trampoline);

	// for command line parsing
	EzDetour(0x004F35E5, sub_4F35E5_Detour, sub_4F35E5_Trampoline);

	EQMACMQ_REAL_CCharacterSelectWnd__Quit = (EQ_FUNCTION_TYPE_CCharacterSelectWnd__Quit)DetourFunction((PBYTE)EQ_FUNCTION_CCharacterSelectWnd__Quit, (PBYTE)EQMACMQ_DETOUR_CCharacterSelectWnd__Quit);

	EQMACMQ_REAL_CEverQuest__InterpretCmd = (EQ_FUNCTION_TYPE_CEverQuest__InterpretCmd)DetourFunction((PBYTE)EQ_FUNCTION_CEverQuest__InterpretCmd, (PBYTE)EQMACMQ_DETOUR_CEverQuest__InterpretCmd);

	char szResult[255];
	char szDefault[255];
	sprintf(szDefault, "%s", "TRUE");
	DWORD error = GetPrivateProfileStringA("Options", "WindowedMode", szDefault, szResult, 255, "./eqclient.ini");
	if (GetLastError())
	{
		WritePrivateProfileStringA_tramp("Options", "WindowedMode", szDefault, "./eqclient.ini");
	}
	if (!strcmp(szResult, "FALSE")) {
		start_fullscreen = true;
	}
	else {
		start_fullscreen = false;
	}

	sprintf(szDefault, "%d", 1);
	error = GetPrivateProfileStringA("Options", "MouseRightHanded", szDefault, szResult, 255, "./eqclient.ini");
	if (!GetLastError()) {
		if (!strcmp(szResult, "0"))
			RightHandMouse = false;
	}
	else {
		WritePrivateProfileStringA_tramp("Options", "MouseRightHanded", szDefault, "./eqclient.ini");
	}

	sprintf(szDefault, "%d", 32);
	error = GetPrivateProfileStringA("Defaults", "VideoModeBitsPerPixel", szDefault, szResult, 255, "./eqclient.ini");
	if (!GetLastError())
	{
		// if set to 16 bit, change to 32
		if (!strcmp(szResult, "16"))
			WritePrivateProfileStringA_tramp("Defaults", "VideoModeBitsPerPixel", szDefault, "./eqclient.ini");
	}
	
	sprintf(szDefault, "%d", 32);
	error = GetPrivateProfileStringA("VideoMode", "BitsPerPixel", szDefault, szResult, 255, "./eqclient.ini");
	if (!GetLastError())
	{
		// if set to 16 bit, change to 32
		if (!strcmp(szResult, "16"))
			WritePrivateProfileStringA_tramp("VideoMode", "BitsPerPixel", szDefault, "./eqclient.ini");
	}
	else {
		// we do not have one set
		DEVMODE dm;
		// initialize the DEVMODE structure
		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);
		DWORD bits = 32;
		DWORD freq = 40;
		if (0 != EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm))
		{
			// get default display settings
			bits = dm.dmBitsPerPel;
			freq = dm.dmDisplayFrequency;
		}
		sprintf(szDefault, "%d", freq);
		WritePrivateProfileStringA_tramp("VideoMode", "RefreshRate", szDefault, "./eqclient.ini");
		sprintf(szDefault, "%d", bits);
		WritePrivateProfileStringA_tramp("VideoMode", "BitsPerPixel", szDefault, "./eqclient.ini");
	}

	// turn on chat keepalive
	sprintf(szDefault, "%d", 1);
	WritePrivateProfileStringA_tramp("Defaults", "ChatKeepAlive", szDefault, "./eqclient.ini");
	CheckClientMiniMods();
	bInitalized=true;
}

void RemoveDetour(DWORD address)
{
	for(std::map<DWORD,_detourinfo>::iterator i = ourdetours.begin();i!=ourdetours.end();i++) {
		DetourRemove((PBYTE)i->second.tramp,(PBYTE)i->second.detour);
	}
}

void ExitHooks()
{
	if(!bInitalized)
	{
		return;
	}
}

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	if (ul_reason_for_call==DLL_PROCESS_ATTACH)
	{
		InitHooks();
		LoadIniSettings();
		SetEQhWnd();
		CheckPromptUIChoice();
		return TRUE;
	}
	else if (ul_reason_for_call==DLL_PROCESS_DETACH) {
		ExitHooks();
	    return TRUE;
	}
}