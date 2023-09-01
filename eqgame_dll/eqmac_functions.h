#ifndef EQMAC_FUNCTIONS_H
#define EQMAC_FUNCTIONS_H

#include <cstdint>
#include <cstring>
#include <cmath>

#include "eqmac.h"

#define EQ_FUNCTION_AT_ADDRESS(function,offset) __declspec(naked) function\
{\
    __asm{mov eax, offset};\
    __asm{jmp eax};\
}

#define EQ_FUNCTION_AT_VARIABLE_ADDRESS(function,variable) __declspec(naked) function\
{\
    __asm{mov eax, [variable]};\
    __asm{jmp eax};\
}

#define EQ_FUNCTION_AT_VIRTUAL_ADDRESS(function,virtualoffset) __declspec(naked) function\
{\
    __asm{mov eax, [ecx]};\
    __asm{lea eax, [eax+virtualoffset]};\
    __asm{mov eax, [eax]};\
    __asm{jmp eax};\
}

typedef struct _MOUSECLICK {
	BYTE ConfirmLeftClick;// DO NOT WRITE TO THIS BYTE
	BYTE ConfirmRightClick;// DO NOT WRITE TO THIS BYTE
	BYTE RightClick;
	BYTE LeftClick;
} MOUSECLICK, *PMOUSECLICK;

template <class T>
T EQ_ReadMemory(DWORD address)
{
	T* buffer = (T*)address;
	return (*buffer);
}

template <class T>
void EQ_WriteMemory(DWORD address, T value)
{
	T* buffer = (T*)address;
	*buffer = value;
}

void EQ_ReadMemoryString(DWORD address, size_t size, char result[])
{
	char *buffer = new char[size + 1];

	for (size_t i = 0; i < size; i++)
	{
		buffer[i] = *(unsigned char*)(address + i);
	}

	result = buffer;

	delete[] buffer;
}

void EQ_WriteMemoryString(DWORD address, const char* value)
{
	size_t length = strlen(value);

	size_t j = 0;

	for (size_t i = 0; i < length; i++)
	{
		*(unsigned char*)(address + j) = value[i];
		j++;
	}

	*(unsigned char*)(address + j) = '\0';
}

// direct input

//IDirectInput8** EQ_ppIDirectInput8 = (IDirectInput8**)EQ_DINPUT_ROOT;
//#define EQ_IDirectInput8 (*EQ_ppIDirectInput8)

//IDirectInputDevice8** EQ_ppIDirectInputDevice8_Keyboard = (IDirectInputDevice8**)EQ_DINPUT_DEVICE_KEYBOARD;
//#define EQ_IDirectInputDevice8_Keyboard (*EQ_ppIDirectInputDevice8_Keyboard)

//IDirectInputDevice8** EQ_ppIDirectInputDevice8_Mouse = (IDirectInputDevice8**)EQ_DINPUT_DEVICE_MOUSE;
//#define EQ_IDirectInputDevice8_Mouse (*EQ_ppIDirectInputDevice8_Mouse)

// object structures

EQZONEINFO* EQ_OBJECT_pZoneInfo = (EQZONEINFO*)EQ_STRUCTURE_ZONE_INFO;
#define EQ_OBJECT_ZoneInfo (*EQ_OBJECT_pZoneInfo)

EQVIEWPORT* EQ_OBJECT_pViewPort = (EQVIEWPORT*)EQ_STRUCTURE_VIEWPORT;
#define EQ_OBJECT_ViewPort (*EQ_OBJECT_pViewPort)

EQGUILDLIST* EQ_OBJECT_pGuildList = (EQGUILDLIST*)EQ_STRUCTURE_GUILD_LIST;
#define EQ_OBJECT_GuildList (*EQ_OBJECT_pGuildList)

EQCOMMANDLIST* EQ_OBJECT_pCommandList = (EQCOMMANDLIST*)EQ_STRUCTURE_COMMAND_LIST;
#define EQ_OBJECT_CommandList (*EQ_OBJECT_pCommandList)

// object pointers

EQSPELLLIST** EQ_OBJECT_ppSpellList = (EQSPELLLIST**)EQ_POINTER_SPELL_MANAGER;
#define EQ_OBJECT_SpellList (*EQ_OBJECT_ppSpellList)

EQCAMERAINFO** EQ_OBJECT_ppCameraInfo = (EQCAMERAINFO**)EQ_POINTER_CAMERA_INFO;
#define EQ_OBJECT_CameraInfo (*EQ_OBJECT_ppCameraInfo)

EQCHARINFO** EQ_OBJECT_ppCharInfo = (EQCHARINFO**)EQ_POINTER_CHAR_INFO;
#define EQ_OBJECT_CharInfo (*EQ_OBJECT_ppCharInfo)

EQSPAWNINFO** EQ_OBJECT_ppSpawnsBegin = (EQSPAWNINFO**)EQ_POINTER_SPAWNS_BEGIN;
#define EQ_OBJECT_FirstSpawn (*EQ_OBJECT_ppSpawnsBegin)

EQGROUNDSPAWNINFO** EQ_OBJECT_ppGroundSpawnsBegin = (EQGROUNDSPAWNINFO**)EQ_POINTER_GROUND_SPAWNS_BEGIN;
#define EQ_OBJECT_FirstGroundSpawn (*EQ_OBJECT_ppGroundSpawnsBegin)

EQDOORSPAWNINFO** EQ_OBJECT_ppDoorSpawnsBegin = (EQDOORSPAWNINFO**)EQ_POINTER_DOOR_SPAWNS_BEGIN;
#define EQ_OBJECT_FirstDoorSpawn (*EQ_OBJECT_ppDoorSpawnsBegin)

EQSPAWNINFO** EQ_OBJECT_ppPlayerSpawnInfo = (EQSPAWNINFO**)EQ_POINTER_PLAYER_SPAWN_INFO;
#define EQ_OBJECT_PlayerSpawn (*EQ_OBJECT_ppPlayerSpawnInfo)

EQSPAWNINFO** EQ_OBJECT_ppTargetSpawnInfo = (EQSPAWNINFO**)EQ_POINTER_TARGET_SPAWN_INFO;
#define EQ_OBJECT_TargetSpawn (*EQ_OBJECT_ppTargetSpawnInfo)

EQSPAWNINFO** EQ_OBJECT_ppCorpseSpawnInfo = (EQSPAWNINFO**)EQ_POINTER_CORPSE_SPAWN_INFO;
#define EQ_OBJECT_CorpseSpawn (*EQ_OBJECT_ppCorpseSpawnInfo)

EQCEVERQUEST** EQ_OBJECT_ppCEverquest = (EQCEVERQUEST**)EQ_POINTER_CEverQuest;
#define EQ_OBJECT_CEverQuest (*EQ_OBJECT_ppCEverquest)

EQCXWNDMANGER** EQ_OBJECT_ppCXWndManager = (EQCXWNDMANGER**)EQ_POINTER_CXWndManager;
#define EQ_OBJECT_CXWndManager (*EQ_OBJECT_ppCXWndManager)

EQCITEMDISPLAYWND** EQ_OBJECT_ppCItemDisplayWnd = (EQCITEMDISPLAYWND**)EQ_POINTER_CItemDisplayWnd;
#define EQ_OBJECT_CItemDisplayWnd (*EQ_OBJECT_ppCItemDisplayWnd)

EQCBUFFWINDOW** EQ_OBJECT_ppCBuffWindow = (EQCBUFFWINDOW**)EQ_POINTER_CBuffWindow;
#define EQ_OBJECT_CBuffWindow (*EQ_OBJECT_ppCBuffWindow)

EQCLOOTWND** EQ_OBJECT_ppCLootWnd = (EQCLOOTWND**)EQ_POINTER_CLootWnd;
#define EQ_OBJECT_CLootWnd (*EQ_OBJECT_ppCLootWnd)

EQCSPELLBOOKWND** EQ_OBJECT_ppCSpellBookWnd = (EQCSPELLBOOKWND**)EQ_POINTER_CSpellBookWnd;
#define EQ_OBJECT_CSpellBookWnd (*EQ_OBJECT_ppCSpellBookWnd)

class CXStr;
class CXWndManager;
class CSidlScreenWnd;
class CXWnd;
class CXPoint;
class CXRect;
class StringTable;
class EQ_Main;
class CDisplay;
class CEverQuest;
class EQPlayer;
class EQ_Character;
class EQ_Item;
class EQ_Spell;
class CInvSlot;
class CInvSlotMgr;
class CButtonWnd;
class CHotButtonWnd;
class CLootWnd;
class CTradeWnd;
class CItemDisplayWnd;
class CBuffWindow;
class CSpellBookWnd;
class CTrackingWnd;

class CXStr
{
public:
	CXStr::~CXStr(void);
	CXStr::CXStr(char const *);
	void CXStr::operator+=(char const *);
	void CXStr::operator=(char const *);
	class CXStr& CXStr::operator=(class CXStr const&);
};

class CXWndManager
{
public:
	int CXWndManager::DrawCursor(void) const;
	int CXWndManager::DrawWindows(void) const;
};

CXWndManager** EQ_CLASS_ppCXWndManager = (CXWndManager**)EQ_POINTER_CXWndManager;
#define EQ_CLASS_CXWndManager (*EQ_CLASS_ppCXWndManager)

class CSidlScreenWnd
{
public:
	//
};

class CXWnd
{
public:
	void CXWnd::DrawTooltipAtPoint(int x, int y);
	class CXRect CXWnd::GetRelativeRect(void) const;
	class CXRect CXWnd::GetScreenRect(void) const;
};

class CXPoint
{
public:
	DWORD X;
	DWORD Y;
};

class CXRect
{
public:
	//CXRect::CXRect();
	//CXRect::CXRect(int x1, int y1, int x2, int y2)
	//{
	//X1 = x1;
	//Y1 = y1;
	//X2 = x2;
	//Y2 = y2;
	//}

	DWORD X1;
	DWORD Y1;
	DWORD X2;
	DWORD Y2;
};

class StringTable
{
public:
	char* StringTable::getString(unsigned long id, bool* unknown);
};

StringTable** EQ_CLASS_ppStringTable = (StringTable**)EQ_POINTER_StringTable;
#define EQ_CLASS_StringTable (*EQ_CLASS_ppStringTable)

class EQ_Main
{
public:
	int* __cdecl EQ_Main::ReleaseLoot(void);
};

EQ_Main** EQ_CLASS_ppEQ_Main = (EQ_Main**)EQ_POINTER_EQ_Main;
#define EQ_CLASS_EQ_Main (*EQ_CLASS_ppEQ_Main)

class CDisplay
{
public:
	void CDisplay::Render_World(void);
	void CDisplay::RealRender_World(void);
	void CDisplay::MoveLocalPlayerToSafeCoords(void);
	static int __cdecl CDisplay::WriteTextHD2(const char* text, int x, int y, int color, int font);
	PEQSTRINGSPRITE CDisplay::ChangeDagStringSprite(PEQDAGINFO dag, int fontTexture, char* text);
	int __cdecl CDisplay::SetNameSpriteState(class EQPlayer* spawn, bool show);
	int __cdecl CDisplay::SetNameSpriteTint(class EQPlayer* spawn);
};

CDisplay** EQ_CLASS_ppCDisplay = (CDisplay**)EQ_POINTER_CDisplay;
#define EQ_CLASS_CDisplay (*EQ_CLASS_ppCDisplay)

class CEverQuest
{
public:
	void CEverQuest::InterpretCmd(class EQPlayer* spawn, char* text);
	void CEverQuest::dsp_chat(const char* text, short color, bool filtered);
	void CEverQuest::dsp_chat(const char* text);
	int __cdecl CEverQuest::LMouseDown(unsigned short x, unsigned short y);
	int __cdecl CEverQuest::LMouseUp(unsigned short x, unsigned short y);
	int __cdecl CEverQuest::RMouseDown(unsigned short x, unsigned short y);
	int __cdecl CEverQuest::RMouseUp(unsigned short x, unsigned short y);
	char* CEverQuest::trimName(char* spawnName);
	int CEverQuest::MoveToZone(char* zoneShortName, char* text, int destinationType, int zoneRequestReason);
	int CEverQuest::MoveToZone(int zoneId, char* text, int destinationType, int zoneRequestReason);
	int CEverQuest::LootCorpse(class EQPlayer* spawn, int unknown);
	void CEverQuest::DropHeldItemOnGround(bool showDropMessage);
};

CEverQuest** EQ_CLASS_ppCEverQuest = (CEverQuest**)EQ_POINTER_CEverQuest;
#define EQ_CLASS_CEverQuest (*EQ_CLASS_ppCEverQuest)

class EQPlayer
{
public:
	void EQPlayer::ChangeHeight(float height);
	void EQPlayer::ChangePosition(uint8_t standingState);
	void EQPlayer::FacePlayer(class EQPlayer* spawn);
};

class EQ_Character
{
public:
	unsigned short EQ_Character::Max_Mana(void);
	void EQ_Character::eqspa_movement_rate(short unknown);
	int EQ_Character::CastSpell(unsigned char gem, short spellId, EQITEMINFO** item, short unknown);
	int EQ_Character::StopSpellCast(unsigned char gem);
	int EQ_Character::StopSpellCast(unsigned char gem, short spellId);
	int EQ_Character::UseSkill(unsigned char skill, class EQPlayer* targetSpawn);
};

EQ_Character** EQ_CLASS_ppEQ_Character = (EQ_Character**)EQ_POINTER_EQ_Character;
#define EQ_CLASS_EQ_Character (*EQ_CLASS_ppEQ_Character)

class EQ_Item
{
public:
	//
};

class EQ_Spell
{
public:
	//
};

class CInvSlot
{
public:
	void CInvSlot::HandleRButtonUp(int x, int y);
};

class CInvSlotMgr
{
public:
	class CInvSlot* CInvSlotMgr::FindInvSlot(int slotId);
};

CInvSlotMgr** EQ_CLASS_ppCInvSlotMgr = (CInvSlotMgr**)EQ_POINTER_CInvSlotMgr;
#define EQ_CLASS_CInvSlotMgr (*EQ_CLASS_ppCInvSlotMgr)

class CButtonWnd
{
public:
	//
};

class CHotButtonWnd : public CSidlScreenWnd
{
public:
	void CHotButtonWnd::DoHotButton(unsigned short buttonIndex, bool allowAutoRightClick);
};

CHotButtonWnd** EQ_CLASS_ppCHotButtonWnd = (CHotButtonWnd**)EQ_POINTER_CHotButtonWnd;
#define EQ_CLASS_CHotButtonWnd (*EQ_CLASS_ppCHotButtonWnd)

class CLootWnd : public CSidlScreenWnd
{
public:
	void CLootWnd::Deactivate(void);
	void CLootWnd::RequestLootSlot(int slotIndex, bool autoLoot);
};

CLootWnd** EQ_CLASS_ppCLootWnd = (CLootWnd**)EQ_POINTER_CLootWnd;
#define EQ_CLASS_CLootWnd (*EQ_CLASS_ppCLootWnd)

class CTradeWnd : public CSidlScreenWnd
{
public:
	void CTradeWnd::Activate(class EQPlayer* spawn, bool isTargetNpc); // if (isTargetNpc == true) show Give Window
};

CTradeWnd** EQ_CLASS_ppCTradeWnd = (CTradeWnd**)EQ_POINTER_CTradeWnd;
#define EQ_CLASS_CTradeWnd (*EQ_CLASS_ppCTradeWnd)

class CItemDisplayWnd : public CSidlScreenWnd
{
public:
	void CItemDisplayWnd::SetItem(class EQ_Item* item, bool unknown);
	void CItemDisplayWnd::SetSpell(short spellId, bool hasDescription, int unknown);
};

CItemDisplayWnd** EQ_CLASS_ppCItemDisplayWnd = (CItemDisplayWnd**)EQ_POINTER_CItemDisplayWnd;
#define EQ_CLASS_CItemDisplayWnd (*EQ_CLASS_ppCItemDisplayWnd)

class CBuffWindow : public CSidlScreenWnd
{
public:
	void CBuffWindow::RefreshBuffDisplay(void);
	void CBuffWindow::OnProcessFrame();
	void CBuffWindow::PostDraw(void);
};

CBuffWindow** EQ_CLASS_ppCBuffWindow = (CBuffWindow**)EQ_POINTER_CBuffWindow;
#define EQ_CLASS_CBuffWindow (*EQ_CLASS_ppCBuffWindow)

class CSpellBookWnd : public CSidlScreenWnd
{
public:
	void CSpellBookWnd::Activate(void);
	char* CSpellBookWnd::UpdateSpellBookDisplay(void);
	bool CSpellBookWnd::StartSpellMemorization(int spellBookIndex, int spellGemIndex, bool unknown);
	int CSpellBookWnd::FinishMemorizing(int spellGemIndex, int spellId);
	int CSpellBookWnd::GetSpellMemTicksLeft(void);
};

CSpellBookWnd** EQ_CLASS_ppCSpellBookWnd = (CSpellBookWnd**)EQ_POINTER_CSpellBookWnd;
#define EQ_CLASS_CSpellBookWnd (*EQ_CLASS_ppCSpellBookWnd)

class CTrackingWnd : public CSidlScreenWnd
{
public:
	void CTrackingWnd::Activate(void);
};

CTrackingWnd** EQ_CLASS_ppCTrackingWnd = (CTrackingWnd**)EQ_POINTER_CTrackingWnd;
#define EQ_CLASS_CTrackingWnd (*EQ_CLASS_ppCTrackingWnd)

/* CXStr */

// constructor
#define EQ_FUNCTION_CXStr__CXStr_char_const 0x00575F30
#ifdef EQ_FUNCTION_CXStr__CXStr_char_const
EQ_FUNCTION_AT_ADDRESS(CXStr::CXStr(char const *), EQ_FUNCTION_CXStr__CXStr_char_const);
#endif

// append
#define EQ_FUNCTION_CXStr__operator_plus_equal_char_const 0x00577310
#ifdef EQ_FUNCTION_CXStr__operator_plus_equal_char_const
EQ_FUNCTION_AT_ADDRESS(void CXStr::operator+=(char const *), EQ_FUNCTION_CXStr__operator_plus_equal_char_const);
#endif

// set
#define EQ_FUNCTION_CXStr__operator_equal_char_const 0x00576190
#ifdef EQ_FUNCTION_CXStr__operator_equal_char_const
EQ_FUNCTION_AT_ADDRESS(void CXStr::operator=(char const *), EQ_FUNCTION_CXStr__operator_equal_char_const);
#endif

// set
#define EQ_FUNCTION_CXStr__operator_equal_CXStr_const 0x00576140
#ifdef EQ_FUNCTION_CXStr__operator_equal_CXStr_const
EQ_FUNCTION_AT_ADDRESS(class CXStr& CXStr::operator=(class CXStr const&), EQ_FUNCTION_CXStr__operator_equal_CXStr_const);
#endif

/* CXWndManager */

#define EQ_FUNCTION_CXWndManager__DrawCursor 0x0059E320
#ifdef EQ_FUNCTION_CXWndManager__DrawCursor
EQ_FUNCTION_AT_ADDRESS(int CXWndManager::DrawCursor(void) const, EQ_FUNCTION_CXWndManager__DrawCursor);
#endif

#define EQ_FUNCTION_CXWndManager__DrawWindows 0x0059E000
#ifdef EQ_FUNCTION_CXWndManager__DrawWindows
EQ_FUNCTION_AT_ADDRESS(int CXWndManager::DrawWindows(void) const, EQ_FUNCTION_CXWndManager__DrawWindows);
#endif

/* CXWnd */

#define EQ_FUNCTION_CXWnd__DrawTooltipAtPoint 0x00574800
#ifdef EQ_FUNCTION_CXWnd__DrawTooltipAtPoint
EQ_FUNCTION_AT_ADDRESS(void CXWnd::DrawTooltipAtPoint(int, int), EQ_FUNCTION_CXWnd__DrawTooltipAtPoint);
#endif

#define EQ_FUNCTION_CXWnd__GetRelativeRect 0x005750C0
#ifdef EQ_FUNCTION_CXWnd__GetRelativeRect
EQ_FUNCTION_AT_ADDRESS(class CXRect CXWnd::GetRelativeRect(void) const, EQ_FUNCTION_CXWnd__GetRelativeRect);
#endif

#define EQ_FUNCTION_CXWnd__GetScreenRect 0x005751C0
#ifdef EQ_FUNCTION_CXWnd__GetScreenRect
EQ_FUNCTION_AT_ADDRESS(class CXRect CXWnd::GetScreenRect(void) const, EQ_FUNCTION_CXWnd__GetScreenRect);
#endif

/* StringTable */

#define EQ_FUNCTION_StringTable__getString 0x00550EFE
#ifdef EQ_FUNCTION_StringTable__getString
EQ_FUNCTION_AT_ADDRESS(char* StringTable::getString(unsigned long id, bool* unknown), EQ_FUNCTION_StringTable__getString);
#endif

/* EQ_Main */

#define EQ_FUNCTION_EQ_Main__ReleaseLoot 0x0047F2BD
#ifdef EQ_FUNCTION_EQ_Main__ReleaseLoot
EQ_FUNCTION_AT_ADDRESS(int* _cdecl EQ_Main::ReleaseLoot(void), EQ_FUNCTION_EQ_Main__ReleaseLoot);
#endif

/* CDisplay */

#define EQ_FUNCTION_CDisplay__Render_World 0x004AA8BC
#ifdef EQ_FUNCTION_CDisplay__Render_World
typedef int(__thiscall* EQ_FUNCTION_TYPE_CDisplay__Render_World)(void* this_ptr);
EQ_FUNCTION_AT_ADDRESS(void CDisplay::Render_World(void), EQ_FUNCTION_CDisplay__Render_World);
#endif

#define EQ_FUNCTION_CDisplay__RealRender_World 0x004AAA1B
#ifdef EQ_FUNCTION_CDisplay__RealRender_World
typedef int(__thiscall* EQ_FUNCTION_TYPE_CDisplay__RealRender_World)(void* this_ptr);
EQ_FUNCTION_AT_ADDRESS(void CDisplay::RealRender_World(void), EQ_FUNCTION_CDisplay__RealRender_World);
#endif

#define EQ_FUNCTION_CDisplay__MoveLocalPlayerToSafeCoords 0x004B459C
#ifdef EQ_FUNCTION_CDisplay__MoveLocalPlayerToSafeCoords
EQ_FUNCTION_AT_ADDRESS(void CDisplay::MoveLocalPlayerToSafeCoords(void), EQ_FUNCTION_CDisplay__MoveLocalPlayerToSafeCoords);
#endif

#define EQ_FUNCTION_CDisplay__WriteTextHD2 0x004AA5AA
#ifdef EQ_FUNCTION_CDisplay__WriteTextHD2
typedef int(__cdecl* EQ_FUNCTION_TYPE_CDisplay__WriteTextHD2)(const char* text, int x, int y, int color, int font);
EQ_FUNCTION_AT_ADDRESS(int CDisplay::WriteTextHD2(const char*, int, int, int, int), EQ_FUNCTION_CDisplay__WriteTextHD2);
#endif

#define EQ_FUNCTION_CDisplay__ChangeDagStringSprite 0x004B0AA8
#ifdef EQ_FUNCTION_CDisplay__ChangeDagStringSprite
typedef int(__thiscall* EQ_FUNCTION_TYPE_CDisplay__ChangeDagStringSprite)(void* this_ptr, PEQDAGINFO dag, int fontTexture, char* text);
EQ_FUNCTION_AT_ADDRESS(PEQSTRINGSPRITE CDisplay::ChangeDagStringSprite(PEQDAGINFO, int, char*), EQ_FUNCTION_CDisplay__ChangeDagStringSprite);
#endif

#define EQ_FUNCTION_CDisplay__SetNameSpriteState 0x004B0BD9
#ifdef EQ_FUNCTION_CDisplay__SetNameSpriteState
typedef int(__thiscall* EQ_FUNCTION_TYPE_CDisplay__SetNameSpriteState)(void* this_ptr, class EQPlayer* spawn, bool show);
EQ_FUNCTION_AT_ADDRESS(int CDisplay::SetNameSpriteState(class EQPlayer*, bool), EQ_FUNCTION_CDisplay__SetNameSpriteState);
#endif

#define EQ_FUNCTION_CDisplay__SetNameSpriteTint 0x004B114D
#ifdef EQ_FUNCTION_CDisplay__SetNameSpriteTint
typedef int(__thiscall* EQ_FUNCTION_TYPE_CDisplay__SetNameSpriteTint)(void* this_ptr, class EQPlayer* spawn);
EQ_FUNCTION_AT_ADDRESS(int CDisplay::SetNameSpriteTint(class EQPlayer*), EQ_FUNCTION_CDisplay__SetNameSpriteTint);
#endif

/* CEverQuest */

#define EQ_FUNCTION_CEverQuest__InterpretCmd 0x0054572F
#ifdef EQ_FUNCTION_CEverQuest__InterpretCmd
typedef int(__thiscall* EQ_FUNCTION_TYPE_CEverQuest__InterpretCmd)(void* this_ptr, class EQPlayer* spawn, char* text);
EQ_FUNCTION_AT_ADDRESS(void CEverQuest::InterpretCmd(class EQPlayer*, char*), EQ_FUNCTION_CEverQuest__InterpretCmd);
#endif

#define EQ_FUNCTION_CEverQuest__dsp_chat 0x00537F99
#ifdef EQ_FUNCTION_CEverQuest__dsp_chat
typedef int(__thiscall* EQ_FUNCTION_TYPE_CEverQuest__dsp_chat)(void* this_ptr, const char* text, short textColor, bool b);
EQ_FUNCTION_AT_ADDRESS(void CEverQuest::dsp_chat(const char*, short, bool), EQ_FUNCTION_CEverQuest__dsp_chat);
#endif

#define EQ_FUNCTION_CEverQuest__dsp_chat2 0x005380FD
#ifdef EQ_FUNCTION_CEverQuest__dsp_chat2
EQ_FUNCTION_AT_ADDRESS(void CEverQuest::dsp_chat(const char*), EQ_FUNCTION_CEverQuest__dsp_chat2);
#endif

#define EQ_FUNCTION_CEverQuest__LMouseDown 0x005465AA
#ifdef EQ_FUNCTION_CEverQuest__LMouseDown
typedef int(__thiscall* EQ_FUNCTION_TYPE_CEverQuest__LMouseDown)(void* this_ptr, unsigned short x, unsigned short y);
EQ_FUNCTION_AT_ADDRESS(int __cdecl CEverQuest::LMouseDown(unsigned short, unsigned short), EQ_FUNCTION_CEverQuest__LMouseDown);
#endif

#define EQ_FUNCTION_CEverQuest__LMouseUp 0x00531614
#ifdef EQ_FUNCTION_CEverQuest__LMouseUp
typedef int(__thiscall* EQ_FUNCTION_TYPE_CEverQuest__LMouseUp)(void* this_ptr, unsigned short x, unsigned short y);
EQ_FUNCTION_AT_ADDRESS(int __cdecl CEverQuest::LMouseUp(unsigned short, unsigned short), EQ_FUNCTION_CEverQuest__LMouseUp);
#endif

#define EQ_FUNCTION_CEverQuest__RMouseDown 0x0054699D
#ifdef EQ_FUNCTION_CEverQuest__RMouseDown
typedef int(__thiscall* EQ_FUNCTION_TYPE_CEverQuest__RMouseDown)(void* this_ptr, unsigned short x, unsigned short y);
EQ_FUNCTION_AT_ADDRESS(int __cdecl CEverQuest::RMouseDown(unsigned short, unsigned short), EQ_FUNCTION_CEverQuest__RMouseDown);
#endif

#define EQ_FUNCTION_CEverQuest__RMouseUp 0x00546B71
#ifdef EQ_FUNCTION_CEverQuest__RMouseUp
typedef int(__thiscall* EQ_FUNCTION_TYPE_CEverQuest__RMouseUp)(void* this_ptr, unsigned short x, unsigned short y);
EQ_FUNCTION_AT_ADDRESS(int __cdecl CEverQuest::RMouseUp(unsigned short, unsigned short), EQ_FUNCTION_CEverQuest__RMouseUp);
#endif

#define EQ_FUNCTION_CEverQuest__trimName 0x00537D39
#ifdef EQ_FUNCTION_CEverQuest__trimName
EQ_FUNCTION_AT_ADDRESS(char* CEverQuest::trimName(char*), EQ_FUNCTION_CEverQuest__trimName);
#endif

#define EQ_FUNCTION_CEverQuest__MoveToZone 0x005460B5
#ifdef EQ_FUNCTION_CEverQuest__MoveToZone
typedef int(__thiscall* EQ_FUNCTION_TYPE_CEverQuest__MoveToZone)(void* this_ptr, char*, char*, int, int);
EQ_FUNCTION_AT_ADDRESS(int CEverQuest::MoveToZone(char*, char*, int, int), EQ_FUNCTION_CEverQuest__MoveToZone);
#endif

#define EQ_FUNCTION_CEverQuest__MoveToZone2 0x00546081
#ifdef EQ_FUNCTION_CEverQuest__MoveToZone2
typedef int(__thiscall* EQ_FUNCTION_TYPE_CEverQuest__MoveToZone2)(void* this_ptr, int, char*, int, int);
EQ_FUNCTION_AT_ADDRESS(int CEverQuest::MoveToZone(int, char*, int, int), EQ_FUNCTION_CEverQuest__MoveToZone2);
#endif

#define EQ_FUNCTION_CEverQuest__LootCorpse 0x00547808
#ifdef EQ_FUNCTION_CEverQuest__LootCorpse
typedef signed int(__thiscall* EQ_FUNCTION_TYPE_CEverQuest__LootCorpse)(void* this_ptr, class EQPlayer* spawn, int unknown);
EQ_FUNCTION_AT_ADDRESS(int CEverQuest::LootCorpse(class EQPlayer*, int), EQ_FUNCTION_CEverQuest__LootCorpse);
#endif

#define EQ_FUNCTION_CEverQuest__DropHeldItemOnGround 0x00530D7E
#ifdef EQ_FUNCTION_CEverQuest__DropHeldItemOnGround
typedef signed int(__thiscall* EQ_FUNCTION_TYPE_CEverQuest__DropHeldItemOnGround)(void* this_ptr, bool showDropMessage);
EQ_FUNCTION_AT_ADDRESS(void CEverQuest::DropHeldItemOnGround(bool showDropMessage), EQ_FUNCTION_CEverQuest__DropHeldItemOnGround);
#endif

/* EQPlayer */

#define EQ_FUNCTION_EQPlayer__ChangeHeight 0x0050C160
#ifdef EQ_FUNCTION_EQPlayer__ChangeHeight
EQ_FUNCTION_AT_ADDRESS(void EQPlayer::ChangeHeight(float), EQ_FUNCTION_EQPlayer__ChangeHeight);
#endif

#define EQ_FUNCTION_EQPlayer__ChangePosition 0x0050BE3C
#ifdef EQ_FUNCTION_EQPlayer__ChangePosition
EQ_FUNCTION_AT_ADDRESS(void EQPlayer::ChangePosition(uint8_t), EQ_FUNCTION_EQPlayer__ChangePosition);
#endif

#define EQ_FUNCTION_EQPlayer__FacePlayer 0x00508120
#ifdef EQ_FUNCTION_EQPlayer__FacePlayer
EQ_FUNCTION_AT_ADDRESS(void EQPlayer::FacePlayer(class EQPlayer*), EQ_FUNCTION_EQPlayer__FacePlayer);
#endif

/* EQ_Character */

#define EQ_FUNCTION_EQ_Character__Max_Mana 0x004B9483
#ifdef EQ_FUNCTION_EQ_Character__Max_Mana
EQ_FUNCTION_AT_ADDRESS(unsigned short EQ_Character::Max_Mana(void), EQ_FUNCTION_EQ_Character__Max_Mana);
#endif

#define EQ_FUNCTION_EQ_Character__eqspa_movement_rate 0x004CAABA
#ifdef EQ_FUNCTION_EQ_Character__eqspa_movement_rate
typedef int(__thiscall* EQ_FUNCTION_TYPE_EQ_Character__eqspa_movement_rate)(void* this_ptr, short unknown);
EQ_FUNCTION_AT_ADDRESS(void EQ_Character::eqspa_movement_rate(short), EQ_FUNCTION_EQ_Character__eqspa_movement_rate);
#endif

#define EQ_FUNCTION_EQ_Character__CastSpell 0x004C483B
#ifdef EQ_FUNCTION_EQ_Character__CastSpell
typedef int(__thiscall* EQ_FUNCTION_TYPE_EQ_Character__CastSpell)(void* this_ptr, unsigned char gem, short spellId, EQITEMINFO** item, short unknown);
EQ_FUNCTION_AT_ADDRESS(int EQ_Character::CastSpell(unsigned char, short, EQITEMINFO**, short), EQ_FUNCTION_EQ_Character__CastSpell);
#endif

#define EQ_FUNCTION_EQ_Character__StopSpellCast 0x004CB510
#ifdef EQ_FUNCTION_EQ_Character__StopSpellCast
typedef int(__thiscall* EQ_FUNCTION_TYPE_EQ_Character__StopSpellCast)(void* this_ptr, unsigned char gem, short spellId);
EQ_FUNCTION_AT_ADDRESS(int EQ_Character::StopSpellCast(unsigned char, short), EQ_FUNCTION_EQ_Character__StopSpellCast);
#endif

#define EQ_FUNCTION_EQ_Character__StopSpellCast2 0x004CB4E8
#ifdef EQ_FUNCTION_EQ_Character__StopSpellCast2
typedef int(__thiscall* EQ_FUNCTION_TYPE_EQ_Character__StopSpellCast2)(void* this_ptr, unsigned char gem);
EQ_FUNCTION_AT_ADDRESS(int EQ_Character::StopSpellCast(unsigned char), EQ_FUNCTION_EQ_Character__StopSpellCast2);
#endif

#define EQ_FUNCTION_EQ_Character__UseSkill 0x004BDF2F
#ifdef EQ_FUNCTION_EQ_Character__UseSkill
typedef int(__thiscall* EQ_FUNCTION_TYPE_EQ_Character__UseSkill)(void* this_ptr, unsigned char skill, class EQPlayer* targetSpawn);
EQ_FUNCTION_AT_ADDRESS(int EQ_Character::UseSkill(unsigned char, class EQPlayer*), EQ_FUNCTION_EQ_Character__UseSkill);
#endif

/* CInvSlot */

#define EQ_FUNCTION_CInvSlot__HandleRButtonUp 0x00422804
#ifdef EQ_FUNCTION_CInvSlot__HandleRButtonUp
typedef int(__thiscall* EQ_FUNCTION_TYPE_CInvSlot__HandleRButtonUp)(void* this_ptr, int x, int y);
EQ_FUNCTION_AT_ADDRESS(void CInvSlot::HandleRButtonUp(int, int), EQ_FUNCTION_CInvSlot__HandleRButtonUp);
#endif

/* CInvSlotMgr */

#define EQ_FUNCTION_CInvSlotMgr__FindInvSlot 0x00423010
#ifdef EQ_FUNCTION_CInvSlotMgr__FindInvSlot
EQ_FUNCTION_AT_ADDRESS(class CInvSlot* CInvSlotMgr::FindInvSlot(int), EQ_FUNCTION_CInvSlotMgr__FindInvSlot);
#endif

/* CHotButtonWnd */

#define EQ_FUNCTION_CHotButtonWnd__DoHotButton 0x004209BD
#ifdef EQ_FUNCTION_CHotButtonWnd__DoHotButton
EQ_FUNCTION_AT_ADDRESS(void CHotButtonWnd::DoHotButton(unsigned short, bool), EQ_FUNCTION_CHotButtonWnd__DoHotButton);
#endif

/* CLootWnd */

#define EQ_FUNCTION_CLootWnd__Deactivate 0x0042651F
#ifdef EQ_FUNCTION_CLootWnd__Deactivate
typedef int(__thiscall* EQ_FUNCTION_TYPE_CLootWnd__Deactivate)(void* this_ptr);
EQ_FUNCTION_AT_ADDRESS(void CLootWnd::Deactivate(void), EQ_FUNCTION_CLootWnd__Deactivate);
#endif

#define EQ_FUNCTION_CLootWnd__RequestLootSlot 0x00426B02
#ifdef EQ_FUNCTION_CLootWnd__RequestLootSlot
EQ_FUNCTION_AT_ADDRESS(void CLootWnd::RequestLootSlot(int, bool), EQ_FUNCTION_CLootWnd__RequestLootSlot);
#endif

/* CTradeWnd */

#define EQ_FUNCTION_CTradeWnd__Activate 0x004392C9
#ifdef EQ_FUNCTION_CTradeWnd__Activate
EQ_FUNCTION_AT_ADDRESS(void CTradeWnd::Activate(class EQPlayer*, bool), EQ_FUNCTION_CTradeWnd__Activate);
#endif

/* CItemDisplayWnd */

#define EQ_FUNCTION_CItemDisplayWnd__SetItem 0x00423640
#ifdef EQ_FUNCTION_CItemDisplayWnd__SetItem
typedef int(__thiscall* EQ_FUNCTION_TYPE_CItemDisplayWnd__SetItem)(void* this_ptr, class EQ_Item* item, bool unknown);
EQ_FUNCTION_AT_ADDRESS(void CItemDisplayWnd::SetItem(class EQ_Item*, bool), EQ_FUNCTION_CItemDisplayWnd__SetItem);
#endif

#define EQ_FUNCTION_CItemDisplayWnd__SetSpell 0x00425957
#ifdef EQ_FUNCTION_CItemDisplayWnd__SetSpell
typedef int(__thiscall* EQ_FUNCTION_TYPE_CItemDisplayWnd__SetSpell)(void* this_ptr, int spellId, bool hasDescription, int unknown);
EQ_FUNCTION_AT_ADDRESS(void CItemDisplayWnd::SetSpell(short, bool, int), EQ_FUNCTION_CItemDisplayWnd__SetSpell);
#endif

/* CBuffWindow */

#define EQ_FUNCTION_CBuffWindow__SetBuffIcon 0x00409520

#define EQ_FUNCTION_CBuffWindow__RefreshBuffDisplay 0x00409334
#ifdef EQ_FUNCTION_CBuffWindow__RefreshBuffDisplay
typedef int(__thiscall* EQ_FUNCTION_TYPE_CBuffWindow__RefreshBuffDisplay)(void* this_ptr);
EQ_FUNCTION_AT_ADDRESS(void CBuffWindow::RefreshBuffDisplay(void), EQ_FUNCTION_CBuffWindow__RefreshBuffDisplay);
#endif

#define EQ_FUNCTION_CBuffWindow__RefreshIconArrangement 0x004090E9

#define EQ_FUNCTION_CBuffWindow__OnProcessFrame 0x00408F9F
#ifdef EQ_FUNCTION_CBuffWindow__OnProcessFrame
typedef int(__thiscall* EQ_FUNCTION_TYPE_CBuffWindow__OnProcessFrame)(void* this_ptr);
EQ_FUNCTION_AT_ADDRESS(void CBuffWindow::OnProcessFrame(), EQ_FUNCTION_CBuffWindow__OnProcessFrame);
#endif

#define EQ_FUNCTION_CBuffWindow__PostDraw 0x004095FE
#ifdef EQ_FUNCTION_CBuffWindow__PostDraw
typedef int(__thiscall* EQ_FUNCTION_TYPE_CBuffWindow__PostDraw)(void* this_ptr);
EQ_FUNCTION_AT_ADDRESS(void CBuffWindow::PostDraw(void), EQ_FUNCTION_CBuffWindow__PostDraw);
#endif

/* CSpellBookWnd */

#define EQ_FUNCTION_CSpellBookWnd__Activate 0x0043441F
#ifdef EQ_FUNCTION_CSpellBookWnd__Activate
typedef int(__thiscall* EQ_FUNCTION_TYPE_CSpellBookWnd__Activate)(void* this_ptr);
EQ_FUNCTION_AT_ADDRESS(void CSpellBookWnd::Activate(void), EQ_FUNCTION_CSpellBookWnd__Activate);
#endif

#define EQ_FUNCTION_CSpellBookWnd__UpdateSpellBookDisplay 0x004343E7
#ifdef EQ_FUNCTION_CSpellBookWnd__UpdateSpellBookDisplay
typedef int(__thiscall* EQ_FUNCTION_TYPE_CSpellBookWnd__UpdateSpellBookDisplay)(void* this_ptr);
EQ_FUNCTION_AT_ADDRESS(char* CSpellBookWnd::UpdateSpellBookDisplay(void), EQ_FUNCTION_CSpellBookWnd__UpdateSpellBookDisplay);
#endif

#define EQ_FUNCTION_CSpellBookWnd__StartSpellMemorization 0x00434A05
#ifdef EQ_FUNCTION_CSpellBookWnd__StartSpellMemorization
typedef int(__thiscall* EQ_FUNCTION_TYPE_CSpellBookWnd__StartSpellMemorization)(void* this_ptr, int, int, bool);
EQ_FUNCTION_AT_ADDRESS(bool CSpellBookWnd::StartSpellMemorization(int, int, bool), EQ_FUNCTION_CSpellBookWnd__StartSpellMemorization);
#endif

#define EQ_FUNCTION_CSpellBookWnd__FinishMemorizing 0x00434B38
#ifdef EQ_FUNCTION_CSpellBookWnd__FinishMemorizing
typedef int(__thiscall* EQ_FUNCTION_TYPE_CSpellBookWnd__FinishMemorizing)(void* this_ptr, int, int);
EQ_FUNCTION_AT_ADDRESS(int CSpellBookWnd::FinishMemorizing(int, int), EQ_FUNCTION_CSpellBookWnd__FinishMemorizing);
#endif

#define EQ_FUNCTION_CSpellBookWnd__GetSpellMemTicksLeft 0x00434C05
#ifdef EQ_FUNCTION_CSpellBookWnd__GetSpellMemTicksLeft
typedef int(__thiscall* EQ_FUNCTION_TYPE_CSpellBookWnd__GetSpellMemTicksLeft)(void* this_ptr);
EQ_FUNCTION_AT_ADDRESS(int CSpellBookWnd::GetSpellMemTicksLeft(void), EQ_FUNCTION_CSpellBookWnd__GetSpellMemTicksLeft);
#endif

/* CTrackingWnd */

#define EQ_FUNCTION_CTrackingWnd__Activate 0x004382A1
#ifdef EQ_FUNCTION_CTrackingWnd__Activate
typedef int(__thiscall* EQ_FUNCTION_TYPE_CTrackingWnd__Activate)(void* this_ptr);
EQ_FUNCTION_AT_ADDRESS(void CTrackingWnd::Activate(void), EQ_FUNCTION_CTrackingWnd__Activate);
#endif

/* OTHER */

#define EQ_FUNCTION_DrawNetStatus 0x0054D3AE
#ifdef EQ_FUNCTION_DrawNetStatus
typedef int(__cdecl* EQ_FUNCTION_TYPE_DrawNetStatus)(int, unsigned short, unsigned short, unsigned short x, unsigned short y, int, unsigned short, unsigned long, long, unsigned long);
#endif

#define EQ_FUNCTION_HandleMouseWheel 0x0055B2E0
#ifdef EQ_FUNCTION_HandleMouseWheel
typedef int(__cdecl* EQ_FUNCTION_TYPE_HandleMouseWheel)(int mouseWheelDelta);
#endif

#define EQ_FUNCTION_ProcessKeyDown 0x00525B04
#ifdef EQ_FUNCTION_ProcessKeyDown
typedef int(__cdecl* EQ_FUNCTION_TYPE_ProcessKeyDown)(int key);
#endif

#define EQ_FUNCTION_ProcessKeyUp 0x0052462A
#ifdef EQ_FUNCTION_ProcessKeyUp
typedef int(__cdecl* EQ_FUNCTION_TYPE_ProcessKeyUp)(int key);
#endif

#define EQ_FUNCTION_ProcessMovementKeys 0x005257FA
#ifdef EQ_FUNCTION_ProcessMovementKeys
typedef int(__cdecl* EQ_FUNCTION_TYPE_ProcessMovementKeys)(int key);
#endif

#define EQ_FUNCTION_GetKey 0x0055AFE2
#ifdef EQ_FUNCTION_GetKey
typedef int(__cdecl* EQ_FUNCTION_TYPE_GetKey)(void);
#endif

#define EQ_FUNCTION_ExecuteCmd 0x0054050C

#define EQ_FUNCTION_send_message 0x0054E51A

#define EQ_FUNCTION_CastRay 0x004F20DB
#ifdef EQ_FUNCTION_CastRay
EQ_FUNCTION_AT_ADDRESS(int __cdecl EQ_CastRay(class EQPlayer* spawn, float y, float x, float z), EQ_FUNCTION_CastRay);
#endif

#define EQ_FUNCTION_AutoInventory 0x004F0EEB
#ifdef EQ_FUNCTION_AutoInventory
typedef int(__cdecl* EQ_FUNCTION_TYPE_AutoInventory)(PEQCHARINFO character, EQITEMINFO** item, short unknown);
EQ_FUNCTION_AT_ADDRESS(int __cdecl EQ_AutoInventory(PEQCHARINFO character, EQITEMINFO** item, short unknown), EQ_FUNCTION_AutoInventory);
#endif

#define EQ_FUNCTION_get_melee_range 0x004F3898
#ifdef EQ_FUNCTION_get_melee_range
EQ_FUNCTION_AT_ADDRESS(float __cdecl EQ_get_melee_range(class EQPlayer* spawn1, class EQPlayer* spawn2), EQ_FUNCTION_get_melee_range);
#endif

#define EQ_FUNCTION_flush_mouse 0x0055B5B9
#ifdef EQ_FUNCTION_flush_mouse
EQ_FUNCTION_AT_ADDRESS(signed int EQ_flush_mouse(), EQ_FUNCTION_flush_mouse);
#endif

/* EQGfx_Dx8.DLL */

// world to screen function
typedef int(__cdecl* EQ_FUNCTION_TYPE_EQGfx_Dx8__t3dWorldSpaceToScreenSpace)(int cameraDataPointer, EQLOCATION*, float* resultX, float* resultY);
EQ_FUNCTION_TYPE_EQGfx_Dx8__t3dWorldSpaceToScreenSpace EQGfx_Dx8__t3dWorldSpaceToScreenSpace;

// draw line function
typedef int(__cdecl* EQ_FUNCTION_TYPE_EQGfx_Dx8__t3dDeferLine)(EQLINE*, int argbColor);
EQ_FUNCTION_TYPE_EQGfx_Dx8__t3dDeferLine EQGfx_Dx8__t3dDeferLine;

// draw rectangle function
typedef int(__cdecl* EQ_FUNCTION_TYPE_EQGfx_Dx8__t3dDeferRect)(EQRECT*, int argbColor);
EQ_FUNCTION_TYPE_EQGfx_Dx8__t3dDeferRect EQGfx_Dx8__t3dDeferRect;

// draw quad function (filled rectangle)
typedef int(__cdecl* EQ_FUNCTION_TYPE_EQGfx_Dx8__t3dDeferQuad)(EQRECT*, int argbColor);
EQ_FUNCTION_TYPE_EQGfx_Dx8__t3dDeferQuad EQGfx_Dx8__t3dDeferQuad;

// EQWorldData::GetFullZoneName
// call 00523E49

void EQ_ToggleBool(bool& b)
{
	b = !b;
}

float EQ_CalculateDistance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float EQ_CalculateDistance3d(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

void EQ_Rotate2d(float cx, float cy, float& x, float& y, float angle)
{
	float radians = angle * (EQ_PI / 256.0f); // 512 / 2 = 256

	float c = cosf(radians);
	float s = sinf(radians);

	float nx = (c * (x - cx)) - (s * (y - cy)) + cx;
	float ny = (s * (x - cx)) + (c * (y - cy)) + cy;

	x = nx;
	y = ny;
}

bool EQ_IsInGame()
{
	return (EQ_OBJECT_CEverQuest != NULL && EQ_OBJECT_CEverQuest->GameState == EQ_GAME_STATE_IN_GAME);
}

bool EQ_IsAutoAttackEnabled()
{
	return (EQ_ReadMemory<BYTE>(EQ_IS_AUTO_ATTACK_ENABLED) == 1);
}

bool EQ_IsNetStatusEnabled()
{
	return (EQ_ReadMemory<BYTE>(EQ_IS_NET_STATUS_ENABLED) == 1);
}

bool EQ_IsNotTypingInChat()
{
	return (EQ_ReadMemory<BYTE>(EQ_IS_NOT_TYPING_IN_CHAT) == 1);
}

bool EQ_IsInspectEnabled()
{
	return (EQ_ReadMemory<BYTE>(EQ_IS_INSPECT_ENABLED) == 1);
}

bool EQ_IsShowNpcNamesEnabled()
{
	return (EQ_ReadMemory<BYTE>(EQ_IS_SHOW_NPC_NAMES_ENABLED) == 1);
}

bool EQ_IsKeyPressedControl()
{
	return (EQ_ReadMemory<DWORD>(EQ_IS_KEY_PRESSED_CONTROL) == 1);
}

bool EQ_IsKeyPressedAlt()
{
	return (EQ_ReadMemory<DWORD>(EQ_IS_KEY_PRESSED_ALT) == 1);
}

bool EQ_IsKeyPressedShift()
{
	return (EQ_ReadMemory<DWORD>(EQ_IS_KEY_PRESSED_SHIFT) == 1);
}

bool EQ_IsMouseHoveringOverCXWnd()
{
	return (EQ_ReadMemory<DWORD>(EQ_CXWND_MANAGER_MOUSE_HOVER_WINDOW) != NULL);
}

struct _EQRGBCOLOR EQ_GetRgbColorFromInt(int value)
{
	struct _EQRGBCOLOR rgb;

	rgb.R = (LOBYTE((value) >> 16));
	rgb.G = (LOBYTE(((WORD)(value)) >> 8));
	rgb.B = (LOBYTE(value));

	return rgb;
}

void EQ_CalculateItemCost(int cost, int& platinum, int& gold, int& silver, int& copper)
{
	// cost is in total copper value of item

	if (cost < 0)
	{
		return;
	}

	platinum = cost / 1000;
	cost = cost % 1000;

	gold = cost / 100;
	cost = cost % 100;

	silver = cost / 10;
	cost = cost % 10;

	copper = cost;
}

void EQ_GetItemCostString(int cost, char result[], size_t resultSize)
{
	int platinum = 0;
	int gold = 0;
	int silver = 0;
	int copper = 0;

	EQ_CalculateItemCost(cost, platinum, gold, silver, copper);

	char costText[128] = { 0 };

	if (platinum > 0)
	{
		char platinumText[128];
		_snprintf_s(platinumText, sizeof(platinumText), _TRUNCATE, "%dp", platinum);

		strncat_s(costText, sizeof(costText), platinumText, _TRUNCATE);
	}

	if (gold > 0)
	{
		if (platinum > 0)
		{
			strncat_s(costText, sizeof(costText), " ", _TRUNCATE);
		}

		char goldText[128];
		_snprintf_s(goldText, sizeof(goldText), _TRUNCATE, "%dg", gold);

		strncat_s(costText, sizeof(costText), goldText, _TRUNCATE);
	}

	if (silver > 0)
	{
		if (platinum > 0 || gold > 0)
		{
			strncat_s(costText, sizeof(costText), " ", _TRUNCATE);
		}

		char silverText[128];
		_snprintf_s(silverText, sizeof(silverText), _TRUNCATE, "%ds", silver);

		strncat_s(costText, sizeof(costText), silverText, _TRUNCATE);
	}

	if (copper > 0)
	{
		if (platinum > 0 || gold > 0 || silver > 0)
		{
			strncat_s(costText, sizeof(costText), " ", _TRUNCATE);
		}

		char copperText[128];
		_snprintf_s(copperText, sizeof(copperText), _TRUNCATE, "%dc", copper);

		strncat_s(costText, sizeof(costText), copperText, _TRUNCATE);
	}

	strncpy_s(result, resultSize, costText, _TRUNCATE);
}

void EQ_CalculateTickTime(int ticks, int& hours, int& minutes, int& seconds)
{
	if (ticks > 0)
	{
		seconds = ticks * 6;

		if (seconds > 0)
		{
			hours = seconds / (60 * 60);

			seconds = seconds - hours * (60 * 60);

			if (seconds > 0)
			{
				minutes = seconds / 60;

				seconds = seconds - minutes * 60;
			}
		}
	}
}

void EQ_GetTickTimeString(int ticks, char result[], size_t resultSize)
{
	int hours = 0;
	int minutes = 0;
	int seconds = 0;

	EQ_CalculateTickTime(ticks, hours, minutes, seconds);

	char timeText[128] = { 0 };

	if (hours > 0)
	{
		char hoursText[128];
		_snprintf_s(hoursText, sizeof(hoursText), _TRUNCATE, "%dh", hours);

		strncat_s(timeText, sizeof(timeText), hoursText, _TRUNCATE);
	}

	if (minutes > 0)
	{
		if (hours > 0)
		{
			strncat_s(timeText, sizeof(timeText), " ", _TRUNCATE);
		}

		char minutesText[128];
		_snprintf_s(minutesText, sizeof(minutesText), _TRUNCATE, "%dm", minutes);

		strncat_s(timeText, sizeof(timeText), minutesText, _TRUNCATE);
	}

	if (seconds > 0)
	{
		if (hours > 0 || minutes > 0)
		{
			strncat_s(timeText, sizeof(timeText), " ", _TRUNCATE);
		}

		char secondsText[128];
		_snprintf_s(secondsText, sizeof(secondsText), _TRUNCATE, "%ds", seconds);

		strncat_s(timeText, sizeof(timeText), secondsText, _TRUNCATE);
	}

	strncpy_s(result, resultSize, timeText, _TRUNCATE);
}

void EQ_GetShortTickTimeString(int ticks, char result[], size_t resultSize)
{
	int hours = 0;
	int minutes = 0;
	int seconds = 0;

	EQ_CalculateTickTime(ticks, hours, minutes, seconds);

	char timeText[128] = { 0 };

	if (hours > 0)
	{
		char hoursText[128];
		_snprintf_s(hoursText, sizeof(hoursText), _TRUNCATE, "%dh", hours);

		strncpy_s(timeText, sizeof(timeText), hoursText, _TRUNCATE);
	}
	else
	{
		if (minutes > 0)
		{
			char minutesText[128];
			_snprintf_s(minutesText, sizeof(minutesText), _TRUNCATE, "%dm", minutes);

			strncpy_s(timeText, sizeof(timeText), minutesText, _TRUNCATE);
		}
		else
		{
			if (seconds > 0)
			{
				char secondsText[128];
				_snprintf_s(secondsText, sizeof(secondsText), _TRUNCATE, "%ds", seconds);

				strncpy_s(timeText, sizeof(timeText), secondsText, _TRUNCATE);
			}
		}
	}

	strncpy_s(result, resultSize, timeText, _TRUNCATE);
}

const char* EQ_KEYVALUESTRINGLIST_GetValueByKey(const char* list[][2], size_t listSize, char key[])
{
	for (size_t i = 0; i < listSize; i++)
	{
		if (strcmp(list[i][0], key) == 0)
		{
			return list[i][1]; // return Value if Key is found
		}
	}

	return NULL;
}

int EQ_GetTextColorIdByName(const char* name)
{
	for (size_t i = 0; i < EQ_STRINGSIZE_TEXT_COLOR_NAME; i++)
	{
		if (strcmp(EQ_STRING_TEXT_COLOR_NAME[i], name) == 0)
		{
			return i;
		}
	}

	return EQ_TEXT_COLOR_WHITE;
}

const char* EQ_GetRaceName(int race)
{
	const char* name = NULL;

	switch (race)
	{
	case EQ_RACE_IKSAR:
		name = "Iksar";
		break;

	case EQ_RACE_VAH_SHIR:
		name = "Vah Shir";
		break;

	case EQ_RACE_FROGLOK:
		name = "Froglok";
		break;
	}

	if (race < (int)EQ_STRINGSIZE_RACE_NAME)
	{
		name = EQ_STRING_RACE_NAME[race];
	}

	if (name == NULL)
	{
		return "Unknown";
	}

	return name;
}

const char* EQ_GetRaceShortName(int race)
{
	const char* name = NULL;

	switch (race)
	{
	case EQ_RACE_IKSAR:
		name = "IKS";
		break;

	case EQ_RACE_VAH_SHIR:
		name = "VAH";
		break;

	case EQ_RACE_FROGLOK:
		name = "FRG";
		break;
	}

	if (race < (int)EQ_STRINGSIZE_RACE_SHORT_NAME)
	{
		name = EQ_STRING_RACE_SHORT_NAME[race];
	}

	if (name == NULL)
	{
		return "UNK";
	}

	return name;
}

const char* EQ_GetClassName(int _class)
{
	return EQ_STRING_CLASS_NAME[_class];
}

const char* EQ_GetClassShortName(int _class)
{
	return EQ_STRING_CLASS_SHORT_NAME[_class];
}

const char* EQ_GetStandingStateString(int standingState)
{
	const char* standingStateString = NULL;

	switch (standingState)
	{
	case EQ_STANDING_STATE_STANDING:
		standingStateString = "Standing";
		break;

	case EQ_STANDING_STATE_FROZEN:
		standingStateString = "Mesmerized / Feared";
		break;

	case EQ_STANDING_STATE_LOOTING:
		standingStateString = "Looting / Binding Wounds";
		break;

	case EQ_STANDING_STATE_SITTING:
		standingStateString = "Sitting";
		break;

	case EQ_STANDING_STATE_DUCKING:
		standingStateString = "Ducking";
		break;

	case EQ_STANDING_STATE_FEIGNED:
		standingStateString = "Feigning Death";
		break;

	case EQ_STANDING_STATE_DEAD:
		standingStateString = "Dead";
		break;
	}

	if (standingStateString == NULL)
	{
		return "Unknown";
	}

	return standingStateString;
}

const char* EQ_GetCardinalDirectionByHeading(float heading)
{
	const char* direction = NULL;

	heading = floorf(heading + 0.5f);

	if (heading >= 0.0f && heading <= 31.0f)
	{
		direction = "North";
	}
	else if (heading >= 32.0f && heading <= 95.0f)
	{
		direction = "North West";
	}
	else if (heading >= 96.0f && heading <= 159.0f)
	{
		direction = "West";
	}
	else if (heading >= 160.0f && heading <= 223.0f)
	{
		direction = "South West";
	}
	else if (heading >= 224.0f && heading <= 287.0f)
	{
		direction = "South";
	}
	else if (heading >= 288.0f && heading <= 351.0f)
	{
		direction = "South East";
	}
	else if (heading >= 352.0f && heading <= 415.0f)
	{
		direction = "East";
	}
	else if (heading >= 416.0f && heading <= 479.0f)
	{
		direction = "North East";
	}
	else if (heading >= 480.0f && heading <= 512.0f)
	{
		direction = "North";
	}

	return direction;
}

void EQ_CXStr_Append(PEQCXSTR* cxstr, PCHAR text)
{
	CXStr* temp = (CXStr*)cxstr;

	(*temp) += text;

	cxstr = (PEQCXSTR*)temp;
}

void EQ_CXStr_Set(PEQCXSTR* cxstr, PCHAR text)
{
	CXStr* temp = (CXStr*)cxstr;

	(*temp) = text;

	cxstr = (PEQCXSTR*)temp;
}

char* EQ_GetGuildNameById(int guildId)
{
	if (guildId == EQ_GUILD_ID_NULL)
	{
		return "Unknown Guild";
	}

	return EQ_OBJECT_GuildList.Guild[guildId].Name;
}

void EQ_WriteIntVarToChat(const char* name, int value)
{
	char text[128];
	_snprintf_s(text, sizeof(text), _TRUNCATE, "%s: %d", name, value);

	EQ_CLASS_CEverQuest->dsp_chat(text);
}

void EQ_WriteHexVarToChat(const char* name, int value)
{
	char text[128];
	_snprintf_s(text, sizeof(text), _TRUNCATE, "%s: 0x%08X", value);

	EQ_CLASS_CEverQuest->dsp_chat(text);
}

void EQ_WriteFloatVarToChat(const char* name, float value)
{
	char text[128];
	_snprintf_s(text, sizeof(text), _TRUNCATE, "%s: %.1f", name, value);

	EQ_CLASS_CEverQuest->dsp_chat(text);
}

void EQ_WriteBoolVarToChat(const char* name, bool& b)
{
	char text[128];
	_snprintf_s(text, sizeof(text), _TRUNCATE, "%s: %s", name, b ? "On" : "Off");

	EQ_CLASS_CEverQuest->dsp_chat(text);
}

void EQ_WriteStringVarToChat(const char* name, char value[])
{
	char text[128];
	_snprintf_s(text, sizeof(text), _TRUNCATE, "%s: %s", name, value);

	EQ_CLASS_CEverQuest->dsp_chat(text);
}

void EQ_WriteStringToChat(const char* text)
{
	EQ_CLASS_CEverQuest->dsp_chat(text);
}

void EQ_WriteStringToChatWithColor(const char* text, int color)
{
	EQ_CLASS_CEverQuest->dsp_chat(text, color, false);
}

void EQ_DrawText(const char* text, int x, int y, int color)
{
	DWORD fontArial14 = EQ_ReadMemory<DWORD>(EQ_POINTER_FONT_ARIAL14);

	EQ_CLASS_CDisplay->WriteTextHD2(text, x, y, color, fontArial14);
}

void EQ_DrawRectangle(float x, float y, float width, float height, int color, bool filled = false)
{
	EQRECT rect;

	// top left
	rect.X1 = x;
	rect.Y1 = y;
	rect.Z1 = 1.0f;

	// top right
	rect.X2 = x + width;
	rect.Y2 = y;
	rect.Z2 = 1.0f;

	// bottom right
	rect.X3 = x + width;
	rect.Y3 = y + height;
	rect.Z3 = 1.0f;

	// bottom left
	rect.X4 = x;
	rect.Y4 = y + height;
	rect.Z4 = 1.0f;

	if (filled == false)
	{
		EQGfx_Dx8__t3dDeferRect(&rect, color);
	}
	else
	{
		EQGfx_Dx8__t3dDeferQuad(&rect, color);
	}
}

int EQ_GetFontTextWidth(DWORD fontPointer, char text[])
{
	unsigned int textLength = strlen(text);

	if (textLength == 0)
	{
		return 0;
	}

	int* fontGlyphArray = NULL;

	if (fontPointer == EQ_POINTER_FONT_ARIAL10)
	{
		fontGlyphArray = EQ_FONT_GLYPH_SIZES_ARIAL10;
	}
	else if (fontPointer == EQ_POINTER_FONT_ARIAL12)
	{
		fontGlyphArray = EQ_FONT_GLYPH_SIZES_ARIAL12;
	}
	else if (fontPointer == EQ_POINTER_FONT_ARIAL14)
	{
		fontGlyphArray = EQ_FONT_GLYPH_SIZES_ARIAL14;
	}
	else if (fontPointer == EQ_POINTER_FONT_ARIAL15)
	{
		fontGlyphArray = EQ_FONT_GLYPH_SIZES_ARIAL15;
	}
	else if (fontPointer == EQ_POINTER_FONT_ARIAL16)
	{
		fontGlyphArray = EQ_FONT_GLYPH_SIZES_ARIAL16;
	}
	else if (fontPointer == EQ_POINTER_FONT_ARIAL20)
	{
		fontGlyphArray = EQ_FONT_GLYPH_SIZES_ARIAL20;
	}

	if (fontGlyphArray == NULL)
	{
		return 0;
	}

	int width = 0;

	for (size_t i = 0; i < textLength; i++)
	{
		int asciiIndex = (int)text[i];

		if (asciiIndex > 128)
		{
			continue;
		}

		width += fontGlyphArray[asciiIndex];
	}

	return width;
}

void EQ_DrawTooltipText(char text[], int x, int y, DWORD fontPointer)
{
	unsigned int textLength = strlen(text);

	if (textLength == 0)
	{
		return;
	}

	DWORD font = EQ_ReadMemory<DWORD>(fontPointer);

	int fontHeight = 0;

	if (fontPointer == EQ_POINTER_FONT_ARIAL10)
	{
		fontHeight = 10;
	}
	else if (fontPointer == EQ_POINTER_FONT_ARIAL12)
	{
		fontHeight = 12;
	}
	else if (fontPointer == EQ_POINTER_FONT_ARIAL14)
	{
		fontHeight = 14;
	}
	else if (fontPointer == EQ_POINTER_FONT_ARIAL15)
	{
		fontHeight = 15;
	}
	else if (fontPointer == EQ_POINTER_FONT_ARIAL16)
	{
		fontHeight = 16;
	}
	else if (fontPointer == EQ_POINTER_FONT_ARIAL20)
	{
		fontHeight = 20;
	}

	if (fontHeight == 0)
	{
		return;
	}

	int textWidth = EQ_GetFontTextWidth(fontPointer, text);

	if (textWidth == 0)
	{
		return;
	}

	textWidth = textWidth + 1;

	int textX = x - 1;

	EQ_DrawRectangle((float)textX, (float)y, (float)textWidth, (float)fontHeight, EQ_TOOLTIP_TEXT_BACKGROUND_COLOR, true);

	EQ_CLASS_CDisplay->WriteTextHD2(text, x, y, EQ_TEXT_COLOR_WHITE, font);
}

void EQ_ApplyClassicUiDrawOffset(int& x, int& y)
{
	BYTE uiState = EQ_ReadMemory<BYTE>(EQ_UI_STATE);

	if (uiState == EQ_UI_STATE_CLASSIC)
	{
		DWORD resolutionWidth = EQ_ReadMemory<DWORD>(EQ_RESOLUTION_WIDTH);
		DWORD resolutionHeight = EQ_ReadMemory<DWORD>(EQ_RESOLUTION_HEIGHT);

		if (resolutionWidth > EQ_CLASSIC_UI_WIDTH || resolutionHeight > EQ_CLASSIC_UI_HEIGHT)
		{
			int offsetX = (int)((resolutionWidth - EQ_CLASSIC_UI_WIDTH)  * 0.5f);
			int offsetY = (int)((resolutionHeight - EQ_CLASSIC_UI_HEIGHT) * 0.5f);

			x = x + offsetX;
			y = y + offsetY;
		}
	}
}

void EQ_TargetSpawn(PEQSPAWNINFO spawn)
{
	if (spawn)
	{
		EQ_WriteMemory<PEQSPAWNINFO>(EQ_POINTER_TARGET_SPAWN_INFO, spawn);
	}
}

PEQSPAWNINFO EQ_GetMyCorpse()
{
	PEQSPAWNINFO spawn = (PEQSPAWNINFO)EQ_OBJECT_FirstSpawn;

	PEQSPAWNINFO playerSpawn = (PEQSPAWNINFO)EQ_OBJECT_PlayerSpawn;

	while (spawn)
	{
		if (spawn->Type != EQ_SPAWN_TYPE_PLAYER_CORPSE)
		{
			spawn = spawn->Next;
			continue;
		}

		if (strstr(spawn->Name, playerSpawn->Name) != NULL) // TODO: strcmp needed
		{
			return spawn;
		}

		spawn = spawn->Next;
	}

	return NULL;
}

PEQSPAWNINFO EQ_GetNearestSpawn(int spawnType, float maxDistance = 400.0f)
{
	PEQSPAWNINFO spawn = (PEQSPAWNINFO)EQ_OBJECT_FirstSpawn;

	PEQSPAWNINFO playerSpawn = (PEQSPAWNINFO)EQ_OBJECT_PlayerSpawn;

	int spawnId = 0;

	float shortestDistance = 0.0f;

	while (spawn)
	{
		if (spawn->Type != spawnType && spawnType != EQ_SPAWN_TYPE_ANY_CORPSE)
		{
			spawn = spawn->Next;
			continue;
		}

		if (spawnType == EQ_SPAWN_TYPE_ANY_CORPSE)
		{
			if (spawn->Type != EQ_SPAWN_TYPE_NPC_CORPSE && spawn->Type != EQ_SPAWN_TYPE_PLAYER_CORPSE)
			{
				spawn = spawn->Next;
				continue;
			}
		}

		if (spawn == playerSpawn)
		{
			spawn = spawn->Next;
			continue;
		}

		float spawnDistance = EQ_CalculateDistance(playerSpawn->X, playerSpawn->Y, spawn->X, spawn->Y);

		if (spawnDistance > maxDistance)
		{
			spawn = spawn->Next;
			continue;
		}

		if (shortestDistance == 0.0f)
		{
			shortestDistance = spawnDistance;
		}

		if (spawnDistance <= shortestDistance)
		{
			shortestDistance = spawnDistance;

			spawnId = spawn->SpawnId;
		}

		spawn = spawn->Next;
	}

	spawn = (PEQSPAWNINFO)EQ_OBJECT_FirstSpawn;

	while (spawn)
	{
		if (spawn->SpawnId == spawnId)
		{
			return spawn;
		}

		spawn = spawn->Next;
	}

	return NULL;
}

DWORD EQ_GetStringSpriteFontTexture()
{
	DWORD display = EQ_ReadMemory<DWORD>(EQ_POINTER_CDisplay);

	DWORD fontTexture = EQ_ReadMemory<DWORD>(display + EQ_OFFSET_CDisplay_STRING_SPRITE_FONT_TEXTURE_POINTER);

	return fontTexture;
}

signed int EQ_GetSpellBookSpellIndexBySpellId(int spellId)
{
	if (spellId == EQ_SPELL_ID_NULL)
	{
		return -1;
	}

	PEQCHARINFO charInfo = (PEQCHARINFO)EQ_OBJECT_CharInfo;

	if (charInfo == NULL)
	{
		return -1;
	}

	for (size_t i = 0; i < EQ_NUM_SPELL_BOOK_SPELLS; i++)
	{
		int spellBookSpellId = charInfo->SpellBook[i];

		if (spellBookSpellId == spellId)
		{
			return i;
		}
	}

	return -1;
}

int EQ_GetSpellIdBySpellName(const char* spellName)
{
	if (strlen(spellName) == 0 || spellName == NULL)
	{
		return EQ_SPELL_ID_NULL;
	}

	for (size_t i = 0; i < EQ_NUM_SPELLS; i++)
	{
		if (strcmp(EQ_OBJECT_SpellList->Spell[i]->Name, spellName) == 0)
		{
			return i;
		}
	}

	return EQ_SPELL_ID_NULL;
}

int EQ_GetSpellGemBySpellId(int spellId)
{
	if (spellId == EQ_SPELL_ID_NULL)
	{
		return EQ_SPELL_ID_NULL;
	}

	PEQCHARINFO charInfo = (PEQCHARINFO)EQ_OBJECT_CharInfo;

	if (charInfo == NULL)
	{
		return EQ_SPELL_ID_NULL;
	}

	for (size_t i = 0; i < EQ_NUM_SPELL_GEMS; i++)
	{
		if (charInfo->MemorizedSpell[i] == spellId)
		{
			return i;
		}
	}

	return EQ_SPELL_ID_NULL;
}

void EQ_Warp(float y, float x, float z)
{
	float safeCoordsY = EQ_OBJECT_ZoneInfo.SafeCoordsY;
	float safeCoordsX = EQ_OBJECT_ZoneInfo.SafeCoordsX;
	float safeCoordsZ = EQ_OBJECT_ZoneInfo.SafeCoordsZ;

	EQ_OBJECT_ZoneInfo.SafeCoordsY = y;
	EQ_OBJECT_ZoneInfo.SafeCoordsX = x;
	EQ_OBJECT_ZoneInfo.SafeCoordsZ = z;

	EQ_CLASS_CDisplay->MoveLocalPlayerToSafeCoords();

	EQ_OBJECT_ZoneInfo.SafeCoordsY = safeCoordsY;
	EQ_OBJECT_ZoneInfo.SafeCoordsX = safeCoordsX;
	EQ_OBJECT_ZoneInfo.SafeCoordsZ = safeCoordsZ;
}

void EQ_WarpToTarget()
{
	PEQSPAWNINFO targetSpawn = (PEQSPAWNINFO)EQ_OBJECT_TargetSpawn;

	if (targetSpawn != NULL)
	{
		EQ_Warp(targetSpawn->Y, targetSpawn->X, targetSpawn->Z);
	}
}

void EQ_WarpToSpawnByName(const char* name)
{
	PEQSPAWNINFO spawn = (PEQSPAWNINFO)EQ_OBJECT_FirstSpawn;

	while (spawn)
	{
		if (strcmp(spawn->Name, name) == 0)
		{
			EQ_Warp(spawn->Y, spawn->X, spawn->Z);
			return;
		}

		spawn = spawn->Next;
	}

	spawn = (PEQSPAWNINFO)EQ_OBJECT_FirstSpawn;

	while (spawn)
	{
		if (strstr(spawn->Name, name) != NULL)
		{
			EQ_Warp(spawn->Y, spawn->X, spawn->Z);
			return;
		}

		spawn = spawn->Next;
	}
}

void EQ_SetMousePosition(int x, int y)
{
	EQ_WriteMemory<WORD>(EQ_MOUSE_X_REAL, x);
	EQ_WriteMemory<WORD>(EQ_MOUSE_Y_REAL, y);
}

void EQ_UseItem(int slotId)
{
	if (slotId >= EQ_INVENTORY_SLOT_FIRST && slotId <= EQ_INVENTORY_SLOT_LAST)
	{
		CInvSlot* slot = EQ_CLASS_CInvSlotMgr->FindInvSlot(slotId + 1); // have to add 1 because FindInvSlot does not start at 0 index

		if (slot != NULL)
		{
			WORD mouseX = EQ_ReadMemory<WORD>(EQ_MOUSE_X);
			WORD mouseY = EQ_ReadMemory<WORD>(EQ_MOUSE_Y);

			slot->HandleRButtonUp(mouseX, mouseY);

			//char text[128];
			//_snprintf_s(text, sizeof(text), _TRUNCATE, "0x%X: %d", slot, slotId);

			//EQ_CLASS_CEverQuest->dsp_chat(text);
		}
	}
}

#endif // EQMAC_FUNCTIONS_H
