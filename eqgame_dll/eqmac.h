#ifndef EQMAC_H
#define EQMAC_H

#include <cstdint>
#include <cstring>
#include <cmath>

#include <windows.h>

const char* EQ_STRING_WINDOW_TITLE = "EverQuest";
const char* EQ_STRING_WINDOW_TITLE_EQW = "EQW beta 2.32";

const char* EQ_STRING_EQ = "EQ";
const char* EQ_STRING_EQW = "EQW";

const char* EQ_STRING_PROCESS_NAME = "eqgame.exe";

const char* EQ_STRING_GRAPHICS_DLL_NAME = "EQGfx_Dx8.dll";

const char* EQ_STRING_EQW_DLL_NAME = "eqw.dll";
const wchar_t* EQ_WIDESTRING_EQW_DLL_NAME = L"eqw.dll";

const float EQ_PI = 3.14159265358979f;

#define EQ_TIMER 0x007989D4 // DWORD ; time elapsed in milliseconds

#define EQ_IS_IN_GAME 0x00798550 // BYTE

#define EQ_IS_AUTO_ATTACK_ENABLED 0x007F6FFE // BYTE

#define EQ_IS_NET_STATUS_ENABLED 0x007985EC // BYTE

#define EQ_IS_NOT_TYPING_IN_CHAT 0x0079856C // BYTE

#define EQ_IS_INSPECT_ENABLED 0x007CF28C // BYTE

#define EQ_EXPERIENCE_MAX 350 // the progress bar (0-350)

#define EQ_ALTERNATE_ADVANCEMENT_EXPERIENCE_MAX 330 // the progress bar (0-330)

#define EQ_DINPUT_ROOT            0x8092DC
#define EQ_DINPUT_DEVICE_KEYBOARD 0x8092E0
#define EQ_DINPUT_DEVICE_MOUSE    0x8092E4

#define EQ_IS_KEY_PRESSED_SHIFT   0x0080931C // DWORD
#define EQ_IS_KEY_PRESSED_CONTROL 0x00809320 // DWORD
#define EQ_IS_KEY_PRESSED_ALT     0x0080932C // DWORD

#define EQ_IS_CAPSLOCK_ENABLED 0x00809324 // DWORD
#define EQ_IS_NUMLOCK_ENABLED  0x00809328 // DWORD

#define EQ_IS_SHOW_NPC_NAMES_ENABLED 0x0063D6CC // BYTE ; Options -> Display -> Show NPC Names

#define EQ_BASE_ADDRESS 0x00400000 // eqgame.exe base address

#define EQ_POINTER_GRAPHICS_DLL 0x007F9C50 // EQGfx_Dx8.DLL base address

#define EQ_POINTER_EQGfx_Dx8__t3dSetCameraLocation 0x007F9AE4

#define EQ_GRAPHICS_DLL_DEFERRED_2D_ITEMS_MAX 4000 // t3dDefer...

#define EQ_POINTER_StringTable 0x007F9490 // eqstr_xx.txt

#define EQ_POINTER_CAMERA_INFO 0x0063B928

#define EQ_CAMERA_PITCH_DEFAULT -8.5f // 119.5 + 8.5 = 128 everquest degrees = 90 degrees
#define EQ_CAMERA_PITCH_MIN -119.5f
#define EQ_CAMERA_PITCH_MAX 119.5f

#define EQ_POINTER_CXWndManager 0x00809DB4

#define EQ_POINTER_SPELL_MANAGER 0x00805CB0

#define EQ_POINTER_EqSoundManager 0x0063DEA8

#define EQ_POINTER_CInvSlotMgr 0x0063D6B4

#define EQ_POINTER_FONT_ARIAL10 0x0063D3A8
#define EQ_POINTER_FONT_ARIAL12 0x0063D3AC
#define EQ_POINTER_FONT_ARIAL14 0x0063D3B0
#define EQ_POINTER_FONT_ARIAL15 0x0063D3B4
#define EQ_POINTER_FONT_ARIAL16 0x0063D3B8
#define EQ_POINTER_FONT_ARIAL20 0x0063D3BC

// requires old UI from 1999 (NewUI=FALSE in eqclient.ini)
// pointers are NULL while using new UI from Luclin expansion
// ASCII table characters (0-128)
// [pointer + DWORD * ASCII character index] = glyph size
#define EQ_POINTER_FONT_GLYPH_SIZES_ARIAL10 0x00809444
#define EQ_POINTER_FONT_GLYPH_SIZES_ARIAL12 0x00809448
#define EQ_POINTER_FONT_GLYPH_SIZES_ARIAL14 0x0080944C
#define EQ_POINTER_FONT_GLYPH_SIZES_ARIAL15 0x00809450
#define EQ_POINTER_FONT_GLYPH_SIZES_ARIAL16 0x00809454
#define EQ_POINTER_FONT_GLYPH_SIZES_ARIAL20 0x00809458

// eqw.dll+offset
#define EQ_OFFSET_EQW_IS_FOREGROUND_WINDOW 0x8000 // DWORD
#define EQ_OFFSET_EQW_DONT_CAPTURE_MOUSE   0x97B0 // DWORD

#define EQ_TOOLTIP_TEXT_BACKGROUND_COLOR 0xC8000080 // ARGB 0xAARRGGBB

#define EQ_POINTER_CEverQuest 0x00809478
#define EQ_OFFSET_CEverQuest_GAME_STATE 0x5AC // DWORD

#define EQ_POINTER_CDisplay 0x007F9510
#define EQ_OFFSET_CDisplay_IS_CURSOR_ITEM                     0x0040 // BYTE ; when you pick up and hold an item on your mouse cursor
#define EQ_OFFSET_CDisplay_IS_CURSOR_HOTKEY                   0x0042 // BYTE ; when you pick up and hold a hotkey button on your mouse cursor
#define EQ_OFFSET_CDisplay_TIMER                              0x00C8 // DWORD ; global timer in milliseconds, 1000 milliseconds = 1 second
#define EQ_OFFSET_CDisplay_STRING_SPRITE_FONT_TEXTURE_POINTER 0x2E08 // S3D_FONTTEXTURE* for CDisplay::ChangeDagStringSprite

#define EQ_POINTER_CBuffWindow     0x0063D638
#define EQ_POINTER_CGiveWnd        0x0063D678
#define EQ_POINTER_CHotButtonWnd   0x0063D628
#define EQ_POINTER_CItemDisplayWnd 0x0063D5E0
#define EQ_POINTER_CTradeWnd       0x0063D668
#define EQ_POINTER_CSpellBookWnd   0x0063D64C
#define EQ_POINTER_CLootWnd        0x0063D65C
#define EQ_POINTER_CTrackingWnd    0x0063D67C

#define EQ_NUM_COMMANDS 277 // 0-276
#define EQ_NUM_BUFFS 15
#define EQ_NUM_SPELLS 4000
#define EQ_NUM_SPELL_GEMS 8
#define EQ_NUM_GROUP_MEMBERS 5
#define EQ_NUM_INVENTORY_SLOTS 21
#define EQ_NUM_INVENTORY_PACK_SLOTS 8
#define EQ_NUM_INVENTORY_BANK_SLOTS 8
#define EQ_NUM_SKILLS 74
#define EQ_NUM_SPELL_BOOK_SPELLS 250 // 32 pages, 8 spells per page, should be 256?
#define EQ_NUM_SPAWNS 8192
#define EQ_NUM_GUILDS 512
#define EQ_NUM_LOOT_WINDOW_ITEMS 30
#define EQ_NUM_HOTBUTTONS 10
#define EQ_NUM_HOTBUTTONS_TOTAL 100
#define EQ_NUM_CONTAINER_SLOTS 10

#define EQ_FONT_SIZE_DEFAULT 3

#define EQ_OFFSET_ITEM_INFO_NAME             0x000 // STRING [0x40]
#define EQ_OFFSET_ITEM_INFO_LORE_NAME        0x040 // STRING [0x50]
#define EQ_OFFSET_ITEM_INFO_ID_FILE          0x090 // STRING [0x06]
#define EQ_OFFSET_ITEM_INFO_WEIGHT           0x0AE // BYTE ; multiply by 0.1 for actual decimal weight
#define EQ_OFFSET_ITEM_INFO_IS_NO_RENT       0x0AF // BYTE ; 255 = False
#define EQ_OFFSET_ITEM_INFO_IS_NO_DROP       0x0B0 // BYTE ; 255 = False
#define EQ_OFFSET_ITEM_INFO_SIZE             0x0B1 // BYTE ; EQ_ITEM_SIZE_x
#define EQ_OFFSET_ITEM_INFO_IS_CONTAINER     0x0B2 // BYTE ; 1 = True
#define EQ_OFFSET_ITEM_INFO_ID               0x0B4 // WORD
#define EQ_OFFSET_ITEM_INFO_ICON             0x0B6 // WORD
#define EQ_OFFSET_ITEM_INFO_EQUIP_SLOT       0x0B8 // DWORD
#define EQ_OFFSET_ITEM_INFO_EQUIPPABLE_SLOTS 0x0BC // DWORD
#define EQ_OFFSET_ITEM_INFO_COST             0x0C0 // DWORD
#define EQ_OFFSET_ITEM_INFO_IS_STACKABLE     0x0F6 // BYTE ; can have quantity more than 1
#define EQ_OFFSET_ITEM_INFO_QUANTITY         0x116 // BYTE ; count, amount

#define EQ_ITEM_INFO_NAME_SIZE      0x40
#define EQ_ITEM_INFO_LORE_NAME_SIZE 0x50
#define EQ_ITEM_INFO_ID_FILE_SIZE   0x06

#define EQ_ITEM_INFO_NULL 0x00000000

#define EQ_ITEM_SIZE_TINY   0
#define EQ_ITEM_SIZE_SMALL  1
#define EQ_ITEM_SIZE_MEDIUM 2
#define EQ_ITEM_SIZE_LARGE  3
#define EQ_ITEM_SIZE_GIANT  4

#define EQ_ITEM_NO_DROP_TRUE  0x00
#define EQ_ITEM_NO_DROP_FALSE 0xFF

#define EQ_ITEM_NO_RENT_TRUE  0x00
#define EQ_ITEM_NO_RENT_FALSE 0xFF

#define EQ_ZONE_ID 0x007B9648 // DWORD

#define EQ_ZONE_ID_FREPORTW       9   // West Freeport
#define EQ_ZONE_ID_COMMONS        21  // West Commonlands
#define EQ_ZONE_ID_ECOMMONS       22  // East Commonlands
#define EQ_ZONE_ID_CSHOME         26  // Sunset Home
#define EQ_ZONE_ID_FIELDOFBONE    78  // The Field of Bone
#define EQ_ZONE_ID_SLEEPER        128 // Sleeper's Tomb
#define EQ_ZONE_ID_BAZAAR         151 // The Bazaar
#define EQ_ZONE_ID_NEXUS          152 // The Nexus
#define EQ_ZONE_ID_SSERU          159 // Sanctus Seru
#define EQ_ZONE_ID_TUTORIAL       183 // Tutorial Zone
#define EQ_ZONE_ID_LOAD           184 // Loading
#define EQ_ZONE_ID_LOAD2          185 // Loading
#define EQ_ZONE_ID_POKNOWLEDGE    202 // The Plane of Knowledge
#define EQ_ZONE_ID_POTRANQUILITY  203 // Plane of Tranquility
#define EQ_ZONE_ID_POTIMEA        219 // Plane of Time
#define EQ_ZONE_ID_POTIMEB        223 // Plane of Time

#define EQ_STRUCTURE_ZONE_INFO 0x00798784 // STRUCT
#define EQ_OFFSET_ZONE_INFO_PLAYER_NAME  0x0000 // STRING [0x40]
#define EQ_OFFSET_ZONE_INFO_SHORT_NAME   0x0040 // STRING [0x20]
#define EQ_OFFSET_ZONE_INFO_LONG_NAME    0x0060 // STRING [0x80]
#define EQ_OFFSET_ZONE_INFO_SAFE_POINT_Y 0x01E8 // FLOAT
#define EQ_OFFSET_ZONE_INFO_SAFE_POINT_X 0x01EC // FLOAT
#define EQ_OFFSET_ZONE_INFO_SAFE_POINT_Z 0x01F0 // FLOAT

#define EQ_ZONE_INFO_PLAYER_NAME_SIZE 0x40
#define EQ_ZONE_INFO_SHORT_NAME_SIZE  0x20
#define EQ_ZONE_INFO_LONG_NAME_SIZE   0x80

#define EQ_ZONE_GRAVITY_DEFAULT 0.400000006

#define EQ_STRUCTURE_COMMAND_LIST 0x00609AF8 // STRUCT

// /viewport
#define EQ_STRUCTURE_VIEWPORT 0x00798548 // STRUCT

#define EQ_VIEWPORT_CLASSIC_UI_WIDTH  400
#define EQ_VIEWPORT_CLASSIC_UI_HEIGHT 320

#define EQ_VIEWPORT_CLASSIC_UI_OFFSET_X 119 // pixels of the Classic UI where the OPTIONS and HELP buttons are located, 3D viewport is to the right
#define EQ_VIEWPORT_CLASSIC_UI_OFFSET_Y 0

#define EQ_CLASSIC_UI_WIDTH  640
#define EQ_CLASSIC_UI_HEIGHT 480

#define EQ_CLASSIC_UI_CHAT_WINDOW_X      112
#define EQ_CLASSIC_UI_CHAT_WINDOW_Y      327
#define EQ_CLASSIC_UI_CHAT_WINDOW_WIDTH  414
#define EQ_CLASSIC_UI_CHAT_WINDOW_HEIGHT 153

#define EQ_POINTER_WORLD_INFO 0x007F9494
#define EQ_OFFSET_WORLD_INFO_HOUR   0x04 // BYTE
#define EQ_OFFSET_WORLD_INFO_MINUTE 0x05 // BYTE
#define EQ_OFFSET_WORLD_INFO_DAY    0x06 // BYTE
#define EQ_OFFSET_WORLD_INFO_MONTH  0x07 // BYTE
#define EQ_OFFSET_WORLD_INFO_YEAR   0x08 // BYTE

#define EQ_POINTER_GROUND_SPAWN_INFO 0x007F949C
#define EQ_OFFSET_GROUND_SPAWN_INFO_PREV_SPAWN_INFO_POINTER 0x00 // DWORD
#define EQ_OFFSET_GROUND_SPAWN_INFO_NEXT_SPAWN_INFO_POINTER 0x04 // DWORD
#define EQ_OFFSET_GROUND_SPAWN_INFO_ID                      0x08 // WORD
#define EQ_OFFSET_GROUND_SPAWN_INFO_DROP_ID                 0x0C // WORD
#define EQ_OFFSET_GROUND_SPAWN_INFO_Z                       0x90 // FLOAT
#define EQ_OFFSET_GROUND_SPAWN_INFO_X                       0x94 // FLOAT
#define EQ_OFFSET_GROUND_SPAWN_INFO_Y                       0x98 // FLOAT
#define EQ_OFFSET_GROUND_SPAWN_INFO_NAME                    0x9C // STRING [0x40]

#define EQ_GROUND_SPAWN_INFO_NAME_SIZE 0x40

// ??
//#define EQ_DOORS_INFO_POINTER 0x007F94B8

// class EQ_Character
#define EQ_POINTER_EQ_Character 0x007F94E8
#define EQ_POINTER_CHAR_INFO EQ_POINTER_EQ_Character
#define EQ_OFFSET_CHAR_INFO_NAME               0x0002 // STRING [0x40]
#define EQ_OFFSET_CHAR_INFO_MANA               0x009A // WORD
#define EQ_OFFSET_CHAR_INFO_STUNNED_STATE      0x009E // BYTE ; EQ_STUNNED_STATE_x
#define EQ_OFFSET_CHAR_INFO_BUFF1              0x0264 // STRUCT ; first buff ; 15 buffs max
#define EQ_OFFSET_CHAR_INFO_STANDING_STATE     0x0B64 // BYTE ; EQ_STANDING_STATE_x
#define EQ_OFFSET_CHAR_INFO_PLATINUM           0x0B68 // DWORD
#define EQ_OFFSET_CHAR_INFO_GOLD               0x0B6C // DWORD
#define EQ_OFFSET_CHAR_INFO_SILVER             0x0B70 // DWORD
#define EQ_OFFSET_CHAR_INFO_COPPER             0x0B74 // DWORD
#define EQ_OFFSET_CHAR_INFO_BANK_PLATINUM      0x0B78 // DWORD
#define EQ_OFFSET_CHAR_INFO_BANK_GOLD          0x0B7C // DWORD
#define EQ_OFFSET_CHAR_INFO_BANK_SILVER        0x0B80 // DWORD
#define EQ_OFFSET_CHAR_INFO_BANK_COPPER        0x0B84 // DWORD
#define EQ_OFFSET_CHAR_INFO_SPAWN_INFO_POINTER 0x0D74 // DWORD

#define EQ_CHAR_INFO_NAME_SIZE 0x40

#define EQ_BUFF_SIZE 0x0A // size of buff struct
#define EQ_OFFSET_BUFF_UNKNOWN0000       0x00 // BYTE
#define EQ_OFFSET_BUFF_CASTER_LEVEL      0x01 // BYTE ; level of player who casted the buff
#define EQ_OFFSET_BUFF_MODIFIER          0x02 // BYTE ; divide by 10 to get Bard song modifier
#define EQ_OFFSET_BUFF_UNKNOWN0003       0x03 // BYTE ; damage shield = -1
#define EQ_OFFSET_BUFF_SPELL_ID          0x04 // WORD
#define EQ_OFFSET_BUFF_TICKS             0x06 // DWORD ; duration in ticks ; seconds = ticks * 3

#define EQ_SPELL_ID_NULL 0xFFFF // WORD

#define EQ_BUFF_TYPE_DETRIMENTAL           0
#define EQ_BUFF_TYPE_BENEFICIAL            1
#define EQ_BUFF_TYPE_BENEFICIAL_GROUP_ONLY 2

#define EQ_POINTER_SPAWNS_BEGIN 0x007F9498 // spawn list

#define EQ_POINTER_GROUND_SPAWNS_BEGIN 0x007F949C // ground spawn list

#define EQ_POINTER_DOOR_SPAWNS_BEGIN 0x007F94B8 // door list

// class EQPlayer
#define EQ_POINTER_PLAYER_SPAWN_INFO     0x007F94CC
#define EQ_POINTER_TARGET_SPAWN_INFO     0x007F94EC
#define EQ_POINTER_CONTROLLED_SPAWN_INFO 0x007F94E0

// targetted spawns
#define EQ_POINTER_TRADE_SPAWN_INFO      0x007F94C8
#define EQ_POINTER_MERCHANT_SPAWN_INFO   0x007F94F8
#define EQ_POINTER_BANKER_SPAWN_INFO     0x007F94FC
#define EQ_POINTER_CORPSE_SPAWN_INFO     0x007F9500
#define EQ_POINTER_GAMEMASTER_SPAWN_INFO 0x007F9504

#define EQ_SPAWN_INFO_NULL 0x00000000

#define EQ_OFFSET_SPAWN_INFO_NAME                    0x0001 // STRING [0x1E]
#define EQ_OFFSET_SPAWN_INFO_ZONE_ID                 0x0044 // DWORD
#define EQ_OFFSET_SPAWN_INFO_Y                       0x0048 // FLOAT
#define EQ_OFFSET_SPAWN_INFO_X                       0x004C // FLOAT
#define EQ_OFFSET_SPAWN_INFO_Z                       0x0050 // FLOAT
#define EQ_OFFSET_SPAWN_INFO_HEADING                 0x0054 // FLOAT ; facing direction, rotation
#define EQ_OFFSET_SPAWN_INFO_MOVEMENT_SPEED          0x005C // FLOAT
#define EQ_OFFSET_SPAWN_INFO_NEXT_SPAWN_INFO_POINTER 0x0078
#define EQ_OFFSET_SPAWN_INFO_PREV_SPAWN_INFO_POINTER 0x007C
#define EQ_OFFSET_SPAWN_INFO_ACTOR_INFO_POINTER      0x0084
#define EQ_OFFSET_SPAWN_INFO_CHAR_INFO_POINTER       0x0088
#define EQ_OFFSET_SPAWN_INFO_CAMERA_HEIGHT           0x008C // FLOAT ; height from where your character's eyes see
#define EQ_OFFSET_SPAWN_INFO_MODEL_HEIGHT_OFFSET     0x0090 // FLOAT ; height above/below the ground
#define EQ_OFFSET_SPAWN_INFO_SPAWN_ID                0x0094 // WORD
#define EQ_OFFSET_SPAWN_INFO_PET_OWNER_SPAWN_ID      0x0096 // WORD
#define EQ_OFFSET_SPAWN_INFO_HP_MAX                  0x0098 // DWORD
#define EQ_OFFSET_SPAWN_INFO_HP_CURRENT              0x009C // DWORD
#define EQ_OFFSET_SPAWN_INFO_GUILD_ID                0x00A0 // WORD
#define EQ_OFFSET_SPAWN_INFO_TYPE                    0x00A8 // BYTE ; EQ_SPAWN_TYPE_x
#define EQ_OFFSET_SPAWN_INFO_CLASS                   0x00A9 // BYTE ; EQ_CLASS_x
#define EQ_OFFSET_SPAWN_INFO_RACE                    0x00AA // WORD ; EQ_RACE_x
#define EQ_OFFSET_SPAWN_INFO_LEVEL                   0x00AD // BYTE
#define EQ_OFFSET_SPAWN_INFO_HIDE_STATE              0x00AE // BYTE
#define EQ_OFFSET_SPAWN_INFO_STANDING_STATE          0x00B1 // BYTE ; EQ_STANDING_STATE_x
#define EQ_OFFSET_SPAWN_INFO_PRIMARY                 0x00C2 // WORD
#define EQ_OFFSET_SPAWN_INFO_SECONDARY               0x00C4 // WORD ; offhand
#define EQ_OFFSET_SPAWN_INFO_MODEL_HEIGHT            0x00F0 // FLOAT ; height / size / actor scale factor
#define EQ_OFFSET_SPAWN_INFO_IS_LINKDEAD             0x0108 // BYTE
#define EQ_OFFSET_SPAWN_INFO_IS_AFK                  0x011C // BYTE
#define EQ_OFFSET_SPAWN_INFO_LAST_NAME               0x012C // STRING [0x20]

#define EQ_SPAWN_INFO_NAME_SIZE      0x1E
#define EQ_SPAWN_INFO_LAST_NAME_SIZE 0x20

#define EQ_SPAWN_TYPE_PLAYER        0
#define EQ_SPAWN_TYPE_NPC           1
#define EQ_SPAWN_TYPE_NPC_CORPSE    2
#define EQ_SPAWN_TYPE_PLAYER_CORPSE 3
#define EQ_SPAWN_TYPE_ANY_CORPSE    254

#define EQ_SPAWN_TARGET_TYPE_CAN_TARGET    0x00
#define EQ_SPAWN_TARGET_TYPE_CAN_TARGET2   0x01
#define EQ_SPAWN_TARGET_TYPE_CANNOT_TARGET 0x41

#define EQ_OFFSET_ACTOR_INFO_TIME_STAMP                  0x0058 // DWORD
#define EQ_OFFSET_ACTOR_INFO_TIME_STAMP_LAST_TICK        0x005C // DWORD
#define EQ_OFFSET_ACTOR_INFO_HEIGHT                      0x00B8 // FLOAT
#define EQ_OFFSET_ACTOR_INFO_CASTING_SPELL_TIME_STAMP    0x00CC // DWORD
#define EQ_OFFSET_ACTOR_INFO_CASTING_SPELL_TIME_STAMP_EX 0x00E0 // DWORD
#define EQ_OFFSET_ACTOR_INFO_ANIMATION                   0x0184 // BYTE
#define EQ_OFFSET_ACTOR_INFO_IS_HOLDING_BOTH             0x0260 // DWORD
#define EQ_OFFSET_ACTOR_INFO_IS_HOLDING_SECONDARY        0x0264 // DWORD
#define EQ_OFFSET_ACTOR_INFO_IS_HOLDING_PRIMARY          0x0268 // DWORD
#define EQ_OFFSET_ACTOR_INFO_CASTING_SPELL_ID            0x027C // WORD
#define EQ_OFFSET_ACTOR_INFO_CASTING_SPELL_GEM_NUMBER    0x027E // BYTE
#define EQ_OFFSET_ACTOR_INFO_IS_NOT_MOVING               0x032D // BYTE
#define EQ_OFFSET_ACTOR_INFO_IS_LFG                      0x0438 // BYTE

#define EQ_SPELL_GEM_NUMBER_BARD_SINGING 255

// class EQ_Main
// Classic UI from 1999 and the Velious UI
// when using NewUI=FALSE in eqclient.ini
#define EQ_POINTER_EQ_Main 0x007F9574
#define EQ_OFFSET_EQ_Main_UI_STATE                        0x00E88 // BYTE ; EQ_CLASSIC_UI_STATE_x
#define EQ_OFFSET_EQ_Main_SPELL_BOOK_SCRIBE_SPELL_TIMER   0x00E94 // WORD
#define EQ_OFFSET_EQ_Main_SPELL_BOOK_MEMORIZE_SPELL_TIMER 0x00E96 // WORD
#define EQ_OFFSET_EQ_Main_IS_LOOT_WINDOW_OPEN             0x5F30C // DWORD ; 1 = Loot window is open, looting a corpse
#define EQ_OFFSET_EQ_Main_IS_SIDE_WINDOW_OPEN             0x5F314 // DWORD ; trade window, loot window, bank window, merchant window
#define EQ_OFFSET_EQ_Main_CHAT_WINDOW_X                   0x98C68 // DWORD
#define EQ_OFFSET_EQ_Main_CHAT_WINDOW_Y                   0x98C6C // DWORD
#define EQ_OFFSET_EQ_Main_CHAT_WINDOW_WIDTH               0x98C70 // DWORD
#define EQ_OFFSET_EQ_Main_CHAT_WINDOW_HEIGHT              0x98C74 // DWORD
#define EQ_OFFSET_EQ_Main_CHAT_WINDOW_UNKNOWN             0x98C78 // DWORD
#define EQ_OFFSET_EQ_Main_CHAT_WINDOW_IS_VISIBLE          0x98C7C // DWORD
#define EQ_OFFSET_EQ_Main_CHAT_WINDOW_IS_DRAGGING         0x98C80 // DWORD
#define EQ_OFFSET_EQ_Main_CHAT_WINDOW_IS_RESIZING         0x98C84 // DWORD

#define EQ_UI_STATE 0x0063B918 // BYTE

#define EQ_WINDOW_HWND 0x00798540 // HWND

#define EQ_RESOLUTION_WIDTH  0x00798564 // DWORD
#define EQ_RESOLUTION_HEIGHT 0x00798568 // DWORD

#define EQ_MOUSE_CURSOR_WIDTH  16 // pixels
#define EQ_MOUSE_CURSOR_HEIGHT 16 // pixels

#define EQ_MOUSE_X_REAL 0x008092E8 // DWORD ; read/write, DirectInput Mouse
#define EQ_MOUSE_Y_REAL 0x008092EC // DWORD ; read/write, DirectInput Mouse

#define EQ_MOUSE_X 0x00798580 // WORD ; read only
#define EQ_MOUSE_Y 0x00798582 // WORD ; read-only

#define EQ_MOUSE_CLICK_STATE 0x00798614 // DWORD

#define EQ_MOUSE_CLICK_STATE_LEFT  0x01000001
#define EQ_MOUSE_CLICK_STATE_RIGHT 0x00010100
#define EQ_MOUSE_CLICK_STATE_BOTH  0x01010101

#define EQ_MOUSE_LOOK_STATE 0x007985EA // DWORD

#define EQ_MOUSE_LOOK_STATE_FALSE 0x00010000
#define EQ_MOUSE_LOOK_STATE_TRUE  0x00010001

#define EQ_MOUSE_TIMER_RIGHT_CLICK 0x0079862C
#define EQ_MOUSE_TIMER_LEFT_CLICK  0x00798630

#define EQ_CXWND_MOUSE_X 0x00809DD0 // DWORD
#define EQ_CXWND_MOUSE_Y 0x00809DD4 // DWORD

#define EQ_CXWND_MANAGER_MOUSE_HOVER_WINDOW 0x00809DD8 // DWORD

#define EQ_MOUSE_WHEEL_DELTA_UP   120
#define EQ_MOUSE_WHEEL_DELTA_DOWN -120

#define EQ_CAMERA_VIEW 0x0063BE68 // DWORD ; EQ_CAMERA_VIEW_x

#define EQ_CAMERA_VIEW_FIRST_PERSON  0
#define EQ_CAMERA_VIEW_THIRD_PERSON1 1
#define EQ_CAMERA_VIEW_THIRD_PERSON2 2
#define EQ_CAMERA_VIEW_THIRD_PERSON3 3
#define EQ_CAMERA_VIEW_THIRD_PERSON4 4

#define EQ_CAMERA_VIEW_THIRD_PERSON2_ZOOM 0x007996C0 // FLOAT ; min is spawn model height offset, max is 200.0f
#define EQ_CAMERA_VIEW_THIRD_PERSON3_ZOOM 0x007996DC // FLOAT ; min is spawn model height offset, max is 200.0f
#define EQ_CAMERA_VIEW_THIRD_PERSON4_ZOOM 0x007996F8 // FLOAT ; min is spawn model height offset, max is 200.0f

#define EQ_CAMERA_VIEW_THIRD_PERSON_ZOOM_MAX 0x005E8538 // FLOAT ; equals 200.0f

#define EQ_IS_HIDING_OR_TRACKING 0x007989E2 // WORD

#define EQ_IS_HIDING_OR_TRACKING_EQUALS_NONE     0xFFFF
#define EQ_IS_HIDING_OR_TRACKING_EQUALS_HIDING   0x001D
#define EQ_IS_HIDING_OR_TRACKING_EQUALS_TRACKING 0x0035

#define EQ_RACE_UNKNOWN   0
#define EQ_RACE_HUMAN     1
#define EQ_RACE_BARBARIAN 2
#define EQ_RACE_ERUDITE   3
#define EQ_RACE_WOOD_ELF  4
#define EQ_RACE_HIGH_ELF  5
#define EQ_RACE_DARK_ELF  6
#define EQ_RACE_HALF_ELF  7
#define EQ_RACE_DWARF     8
#define EQ_RACE_TROLL     9
#define EQ_RACE_OGRE      10
#define EQ_RACE_HALFLING  11
#define EQ_RACE_GNOME     12
#define EQ_RACE_IKSAR     128
#define EQ_RACE_VAH_SHIR  130
#define EQ_RACE_FROGLOK   330

#define EQ_CLASS_UNKNOWN                  0
#define EQ_CLASS_WARRIOR                  1
#define EQ_CLASS_CLERIC                   2
#define EQ_CLASS_PALADIN                  3
#define EQ_CLASS_RANGER                   4
#define EQ_CLASS_SHADOWKNIGHT             5
#define EQ_CLASS_DRUID                    6
#define EQ_CLASS_MONK                     7
#define EQ_CLASS_BARD                     8
#define EQ_CLASS_ROGUE                    9
#define EQ_CLASS_SHAMAN                   10
#define EQ_CLASS_NECROMANCER              11
#define EQ_CLASS_WIZARD                   12
#define EQ_CLASS_MAGICIAN                 13
#define EQ_CLASS_ENCHANTER                14
#define EQ_CLASS_BEASTLORD                15
#define EQ_CLASS_BANKER                   16
#define EQ_CLASS_WARRIOR_GUILDMASTER      17 // EQ_CLASS_WARRIOR + 16
#define EQ_CLASS_CLERIC_GUILDMASTER       18
#define EQ_CLASS_PALADIN_GUILDMASTER      19
#define EQ_CLASS_RANGER_GUILDMASTER       20
#define EQ_CLASS_SHADOWKNIGHT_GUILDMASTER 21
#define EQ_CLASS_DRUID_GUILDMASTER        22
#define EQ_CLASS_MONK_GUILDMASTER         23
#define EQ_CLASS_BARD_GUILDMASTER         24
#define EQ_CLASS_ROGUE_GUILDMASTER        25
#define EQ_CLASS_SHAMAN_GUILDMASTER       26
#define EQ_CLASS_NECROMANCER_GUILDMASTER  27
#define EQ_CLASS_WIZARD_GUILDMASTER       28
#define EQ_CLASS_MAGICIAN_GUILDMASTER     29
#define EQ_CLASS_ENCHANTER_GUILDMASTER    30
#define EQ_CLASS_BEASTLORD_GUILDMASTER    31 // EQ_CLASS_BEASTLORD + 16
#define EQ_CLASS_MERCHANT                 32
#define EQ_CLASS_GUILDMASTER_BEGIN        17
#define EQ_CLASS_GUILDMASTER_END          31

#define EQ_OFFSET_CLASS_GUILDMASTER 16 // EQ_CLASS_x + 16 = EQ_CLASS_x_GUILDMASTER

#define EQ_STRUCTURE_GUILD_LIST 0x007F9C94 // EQGUILDINFO

#define EQ_STRUCTURE_GROUP_LIST 0x007913F8 // EQSPAWNINFO
#define EQ_GROUP_MEMBERS_MAX 5

#define EQ_GUILD_ID_NULL 0xFFFF // WORD

#define EQ_GENDER_MALE   0x00
#define EQ_GENDER_FEMALE 0x01

#define EQ_DEITY_BERTOXXULOUS  0x00C9
#define EQ_DEITY_BRELL_SERILIS 0x00CA
#define EQ_DEITY_CAZIC_THULE   0x00CB
#define EQ_DEITY_INNORUK       0x00CE
#define EQ_DEITY_KARANA        0x00CF
#define EQ_DEITY_QUELLIOUS     0x00D2
#define EQ_DEITY_RALLOS_ZEK    0x00D3
#define EQ_DEITY_THE_TRIBUNAL  0x00D6
#define EQ_DEITY_TUNARE        0x00D7
#define EQ_DEITY_AGNOSTIC      0x018C

#define EQ_UI_STATE_CLASSIC    0x01 // old UI from the year 1999
#define EQ_UI_STATE_DEFAULT    0x02
#define EQ_UI_STATE_FULLSCREEN 0x03

// EQPlayer::ChangePosition(BYTE standingState)
#define EQ_STANDING_STATE_STANDING 0x64
#define EQ_STANDING_STATE_FROZEN   0x66 // stunned / mesmerized / feared ; You lose control of yourself!
#define EQ_STANDING_STATE_LOOTING  0x69 // looting or binding wounds
#define EQ_STANDING_STATE_SITTING  0x6E
#define EQ_STANDING_STATE_DUCKING  0x6F // crouching
#define EQ_STANDING_STATE_FEIGNED  0x73 // feign death
#define EQ_STANDING_STATE_DEAD     0x78

#define EQ_STUNNED_STATE_FALSE       0x00
#define EQ_STUNNED_STATE_TRUE        0x01
#define EQ_STUNNED_STATE_UNCONSCIOUS 0x03
#define EQ_STUNNED_STATE_DEAD        0x04

#define EQ_LEVITATION_STATE_FALSE 0x00
#define EQ_LEVITATION_STATE_TRUE  0x02
#define EQ_LEVITATION_STATE_NPC   0x03

#define EQ_ANONYMOUS_STATE_FALSE    0x00
#define EQ_ANONYMOUS_STATE_TRUE     0x01
#define EQ_ANONYMOUS_STATE_ROLEPLAY 0x02
#define EQ_ANONYMOUS_STATE_BOTH     0x03

#define EQ_GAME_STATE_CHARACTER_SELECT 1
#define EQ_GAME_STATE_ZONING           3
#define EQ_GAME_STATE_ZONING2          4
#define EQ_GAME_STATE_IN_GAME          5
#define EQ_GAME_STATE_LOADING_SCREEN   6
#define EQ_GAME_STATE_ZONING3          7

#define EQ_GUILD_STATUS_MEMBER  0
#define EQ_GUILD_STATUS_OFFICER 1
#define EQ_GUILD_STATUS_LEADER  2

#define EQ_MOUSE_ICON_ARROW             0
#define EQ_MOUSE_ICON_SIZE_ALL          1
#define EQ_MOUSE_ICON_SIZE_LEFT         2
#define EQ_MOUSE_ICON_SIZE_TOP          3
#define EQ_MOUSE_ICON_SIZE_RIGHT        4
#define EQ_MOUSE_ICON_SIZE_BOTTOM       5
#define EQ_MOUSE_ICON_SIZE_TOP_LEFT     6
#define EQ_MOUSE_ICON_SIZE_TOP_RIGHT    7
#define EQ_MOUSE_ICON_SIZE_BOTTOM_LEFT  8
#define EQ_MOUSE_ICON_SIZE_BOTTOM_RIGHT 9

#define EQ_HEADING_MAX 512.0f // yaw

#define EQ_SKILL_1H_BLUNT               0
#define EQ_SKILL_1H_SLASHING            1
#define EQ_SKILL_2H_BLUNT               2
#define EQ_SKILL_2H_SLASHING            3
#define EQ_SKILL_ABJURATION             4
#define EQ_SKILL_ALTERATION             5
#define EQ_SKILL_APPLY_POISON           6
#define EQ_SKILL_ARCHERY                7
#define EQ_SKILL_BACKSTAB               8
#define EQ_SKILL_BIND_WOUND             9
#define EQ_SKILL_BASH                   10
#define EQ_SKILL_BLOCK                  11
#define EQ_SKILL_BRASS_INSTRUMENTS      12
#define EQ_SKILL_CHANNELING             13
#define EQ_SKILL_CONJURATION            14
#define EQ_SKILL_DEFENSE                15
#define EQ_SKILL_DISARM                 16
#define EQ_SKILL_DISARM_TRAPS           17
#define EQ_SKILL_DIVINATION             18
#define EQ_SKILL_DODGE                  19
#define EQ_SKILL_DOUBLE_ATTACK          20
#define EQ_SKILL_DRAGON_PUNCH           21
#define EQ_SKILL_TAIL_RAKE              21
#define EQ_SKILL_DUAL_WIELD             22
#define EQ_SKILL_EAGLE_STRIKE           23
#define EQ_SKILL_EVOCATION              24
#define EQ_SKILL_FEIGN_DEATH            25
#define EQ_SKILL_FLYING_KICK            26
#define EQ_SKILL_FORAGE                 27
#define EQ_SKILL_HAND_TO_HAND           28
#define EQ_SKILL_HIDE                   29
#define EQ_SKILL_KICK                   30
#define EQ_SKILL_MEDITATE               31
#define EQ_SKILL_MEND                   32
#define EQ_SKILL_OFFENSE                33
#define EQ_SKILL_PARRY                  34
#define EQ_SKILL_PICK_LOCK              35
#define EQ_SKILL_PIERCING               36
#define EQ_SKILL_RIPOSTE                37
#define EQ_SKILL_ROUND_KICK             38
#define EQ_SKILL_SAFE_FALL              39
#define EQ_SKILL_SENSE_HEADING          40
#define EQ_SKILL_SINGING                41
#define EQ_SKILL_SNEAK                  42
#define EQ_SKILL_SPECIALIZE_ABJURATION  43
#define EQ_SKILL_SPECIALIZE_ALTERATION  44
#define EQ_SKILL_SPECIALIZE_CONJURATION 45
#define EQ_SKILL_SPECIALIZE_DIVINATION  46
#define EQ_SKILL_SPECIALIZE_EVOCATION   47
#define EQ_SKILL_PICK_POCKETS           48
#define EQ_SKILL_STRINGED_INSTRUMENTS   49
#define EQ_SKILL_SWIMMING               50
#define EQ_SKILL_THROWING               51
#define EQ_SKILL_TIGER_CLAW             52
#define EQ_SKILL_TRACKING               53
#define EQ_SKILL_WIND_INSTRUMENTS       54
#define EQ_SKILL_FISHING                55
#define EQ_SKILL_MAKE_POISON            56
#define EQ_SKILL_TINKERING              57
#define EQ_SKILL_RESEARCH               58
#define EQ_SKILL_ALCHEMY                59
#define EQ_SKILL_BAKING                 60
#define EQ_SKILL_TAILORING              61
#define EQ_SKILL_SENSE_TRAPS            62
#define EQ_SKILL_BLACKSMITHING          63
#define EQ_SKILL_FLETCHING              64
#define EQ_SKILL_BREWING                65
#define EQ_SKILL_ALCOHOL_TOLERANCE      66
#define EQ_SKILL_BEGGING                67
#define EQ_SKILL_JEWELRY_MAKING         68
#define EQ_SKILL_POTTERY                69
#define EQ_SKILL_PERCUSSION_INSTRUMENTS 70
#define EQ_SKILL_INTIMIDATION           71
#define EQ_SKILL_BERSERKING             72
#define EQ_SKILL_TAUNT                  73
#define EQ_SKILL_FRENZY                 74
#define EQ_SKILL_GENERIC_TRADESKILL     75
#define EQ_SKILL_SLAM                   111

#define EQ_HOTBUTTTON_TYPE1_ATTACK       1 // Melee or Range
#define EQ_HOTBUTTTON_TYPE1_SKILL1       2
#define EQ_HOTBUTTTON_TYPE1_SKILL2       3
#define EQ_HOTBUTTTON_TYPE1_SOCIAL_MACRO 4
#define EQ_HOTBUTTTON_TYPE1_ITEM         5
#define EQ_HOTBUTTTON_TYPE1_DEFAULT      6
#define EQ_HOTBUTTTON_TYPE1_SPELL_GEM    7

#define EQ_HOTBUTTTON_TYPE2_EMPTY 255

// EQ_Character::eqspa_movement_rate
#define EQ_MOVEMENT_SPEED_MODIFIER_AA_RUN1        0.08f
#define EQ_MOVEMENT_SPEED_MODIFIER_AA_RUN2        0.14f
#define EQ_MOVEMENT_SPEED_MODIFIER_AA_RUN3        0.21f
#define EQ_MOVEMENT_SPEED_MODIFIER_SPIRIT_OF_WOLF 0.30f

// CEverQuest::MoveToZone
#define EQ_ZONE_REQUEST_REASON_ZONE_TRANSFER 0
/*
enum ZoneReason
{
ZoneTransfer = 0,
ClickZone = 1,
VehicleTransfer = 2,
Summon = 3,
GotoPlayer = 5,
PortalSpell = 7,
ZoneCommand = 8,
Resurrect = 9,
Death = 10,
Teleport = 11
};
*/

#define EQ_TEXT_COLOR_BLACK       0x00
#define EQ_TEXT_COLOR_GRAY        0x01
#define EQ_TEXT_COLOR_GREEN       0x02
#define EQ_TEXT_COLOR_GRAY2       0x03
#define EQ_TEXT_COLOR_BLUE        0x04
#define EQ_TEXT_COLOR_PINK        0x05
#define EQ_TEXT_COLOR_GRAY3       0x06
#define EQ_TEXT_COLOR_WHITE       0x07
#define EQ_TEXT_COLOR_GRAY4       0x08
#define EQ_TEXT_COLOR_GRAY5       0x09
#define EQ_TEXT_COLOR_WHITE2      0x0A
#define EQ_TEXT_COLOR_GRAY6       0x0B
#define EQ_TEXT_COLOR_LIGHT_GRAY  0x0C
#define EQ_TEXT_COLOR_RED         0x0D
#define EQ_TEXT_COLOR_LIGHT_GREEN 0x0E
#define EQ_TEXT_COLOR_YELLOW      0x0F
#define EQ_TEXT_COLOR_LIGHT_BLUE  0x10
#define EQ_TEXT_COLOR_GRAY7       0x11
#define EQ_TEXT_COLOR_CYAN        0x12
#define EQ_TEXT_COLOR_GRAY8       0x13
#define EQ_TEXT_COLOR_BLACK2      0x14

#define EQ_GRAPHICS_DLL_FUNCTION_NAME_t3dWorldSpaceToScreenSpace "t3dWorldSpaceToScreenSpace" // EQGfx_Dx8.t3dWorldSpaceToScreenSpace

#define EQ_POINTER_WORLD_SPACE_TO_SCREEN_SPACE_CAMERA_DATA 0x0063B924 // pass this to function as first argument

#define EQ_WORLD_SPACE_TO_SCREEN_SPACE_RESULT_FAILURE 0xFFFF3D3E // world space to screen space failed because the location is not on screen

#define EQ_GRAPHICS_DLL_FUNCTION_NAME_t3dDeferLine "t3dDeferLine" // EQGfx_Dx8.t3dDeferLine
#define EQ_GRAPHICS_DLL_FUNCTION_NAME_t3dDeferRect "t3dDeferRect" // EQGfx_Dx8.t3dDeferRect
#define EQ_GRAPHICS_DLL_FUNCTION_NAME_t3dDeferQuad "t3dDeferQuad" // EQGfx_Dx8.t3dDeferQuad

// direct input key scan codes (DIK_*)
#define EQ_KEY_NULL            0x00
#define EQ_KEY_ESCAPE          0x01
#define EQ_KEY_1               0x02
#define EQ_KEY_2               0x03
#define EQ_KEY_3               0x04
#define EQ_KEY_4               0x05
#define EQ_KEY_5               0x06
#define EQ_KEY_6               0x07
#define EQ_KEY_7               0x08
#define EQ_KEY_8               0x09
#define EQ_KEY_9               0x0A
#define EQ_KEY_0               0x0B
#define EQ_KEY_MINUS           0x0C
#define EQ_KEY_DASH            EQ_KEY_MINUS
#define EQ_KEY_EQUALS          0x0D
#define EQ_KEY_BACK            0x0E
#define EQ_KEY_BACKSPACE       EQ_KEY_BACK
#define EQ_KEY_TAB             0x0F
#define EQ_KEY_Q               0x10
#define EQ_KEY_W               0x11
#define EQ_KEY_E               0x12
#define EQ_KEY_R               0x13
#define EQ_KEY_T               0x14
#define EQ_KEY_Y               0x15
#define EQ_KEY_U               0x16
#define EQ_KEY_I               0x17
#define EQ_KEY_O               0x18
#define EQ_KEY_P               0x19
#define EQ_KEY_LBRACKET        0x1A
#define EQ_KEY_LEFT_BRACKET    EQ_KEY_LBRACKET
#define EQ_KEY_RBRACKET        0x1B
#define EQ_KEY_RIGHT_BRACKET   EQ_KEY_RBRACKET
#define EQ_KEY_RETURN          0x1C
#define EQ_KEY_ENTER           EQ_KEY_RETURN
#define EQ_KEY_LCONTROL        0x1D
#define EQ_KEY_LEFT_CONTROL    EQ_KEY_LCONTROL
#define EQ_KEY_A               0x1E
#define EQ_KEY_S               0x1F
#define EQ_KEY_D               0x20
#define EQ_KEY_F               0x21
#define EQ_KEY_G               0x22
#define EQ_KEY_H               0x23
#define EQ_KEY_J               0x24
#define EQ_KEY_K               0x25
#define EQ_KEY_L               0x26
#define EQ_KEY_SEMICOLON       0x27
#define EQ_KEY_APOSTROPHE      0x28
#define EQ_KEY_GRAVE           0x29
#define EQ_KEY_TILDE           EQ_KEY_GRAVE
#define EQ_KEY_LSHIFT          0x2A
#define EQ_KEY_LEFT_SHIFT      EQ_KEY_LSHIFT
#define EQ_KEY_BACKSLASH       0x2B
#define EQ_KEY_Z               0x2C
#define EQ_KEY_X               0x2D
#define EQ_KEY_C               0x2E
#define EQ_KEY_V               0x2F
#define EQ_KEY_B               0x30
#define EQ_KEY_N               0x31
#define EQ_KEY_M               0x32
#define EQ_KEY_COMMA           0x33
#define EQ_KEY_PERIOD          0x34
#define EQ_KEY_SLASH           0x35
#define EQ_KEY_RSHIFT          0x36
#define EQ_KEY_RIGHT_SHIFT     EQ_KEY_RSHIFT
#define EQ_KEY_MULTIPLY        0x37
#define EQ_KEY_NUMPADSTAR      EQ_KEY_NUMPAD_MULTIPLY
#define EQ_KEY_NUMPAD_MULTIPLY EQ_KEY_NUMPAD_MULTIPLY
#define EQ_KEY_LMENU           0x38
#define EQ_KEY_LALT            EQ_KEY_LMENU
#define EQ_KEY_LEFT_LALT       EQ_KEY_LMENU
#define EQ_KEY_SPACE           0x39
#define EQ_KEY_SPACEBAR        EQ_KEY_SPACE
#define EQ_KEY_CAPITAL         0x3A
#define EQ_KEY_CAPSLOCK        EQ_KEY_CAPITAL
#define EQ_KEY_CAPS_LOCK       EQ_KEY_CAPITAL
#define EQ_KEY_F1              0x3B
#define EQ_KEY_F2              0x3C
#define EQ_KEY_F3              0x3D
#define EQ_KEY_F4              0x3E
#define EQ_KEY_F5              0x3F
#define EQ_KEY_F6              0x40
#define EQ_KEY_F7              0x41
#define EQ_KEY_F8              0x42
#define EQ_KEY_F9              0x43
#define EQ_KEY_F10             0x44
#define EQ_KEY_NUMLOCK         0x45
#define EQ_KEY_NUM_LOCK        EQ_KEY_NUMLOCK
#define EQ_KEY_SCROLL          0x46
#define EQ_KEY_SCROLL_LOCK     EQ_KEY_SCROLL
#define EQ_KEY_NUMPAD7         0x47
#define EQ_KEY_NUMPAD8         0x48
#define EQ_KEY_NUMPAD9         0x49
#define EQ_KEY_SUBTRACT        0x4A
#define EQ_KEY_NUMPADMINUS     EQ_KEY_SUBTRACT
#define EQ_KEY_NUMPAD_SUBTRACT EQ_KEY_SUBTRACT
#define EQ_KEY_NUMPAD4         0x4B
#define EQ_KEY_NUMPAD5         0x4C
#define EQ_KEY_NUMPAD6         0x4D
#define EQ_KEY_ADD             0x4E
#define EQ_KEY_NUMPADPLUS      0x4E
#define EQ_KEY_NUMPAD_ADD      0x4E
#define EQ_KEY_NUMPAD1         0x4F
#define EQ_KEY_NUMPAD2         0x50
#define EQ_KEY_NUMPAD3         0x51
#define EQ_KEY_NUMPAD0         0x52
#define EQ_KEY_DECIMAL         0x53
#define EQ_KEY_NUMPADPERIOD    EQ_KEY_DECIMAL
#define EQ_KEY_NUMPAD_PERIOD   EQ_KEY_DECIMAL
#define EQ_KEY_OEM_102         0x56
#define EQ_KEY_F11             0x57
#define EQ_KEY_F12             0x58
#define EQ_KEY_F13             0x64
#define EQ_KEY_F14             0x65
#define EQ_KEY_F15             0x66
#define EQ_KEY_KANA            0x70
#define EQ_KEY_ABNT_C1         0x73
#define EQ_KEY_CONVERT         0x79
#define EQ_KEY_NOCONVERT       0x7B
#define EQ_KEY_NO_CONVERT      EQ_KEY_NOCONVERT
#define EQ_KEY_YEN             0x7D
#define EQ_KEY_ABNT_C2         0x7E
#define EQ_KEY_NUMPADEQUALS    0x8D
#define EQ_KEY_NUMPAD_EQUALS   EQ_KEY_NUMPADEQUALS
#define EQ_KEY_PREVTRACK       0x90
#define EQ_KEY_CIRCUMFLEX      EQ_KEY_PREVTRACK
#define EQ_KEY_PREV_TRACK      EQ_KEY_PREVTRACK
#define EQ_KEY_AT              0x91
#define EQ_KEY_COLON           0x92
#define EQ_KEY_UNDERLINE       0x93
#define EQ_KEY_KANJI           0x94
#define EQ_KEY_STOP            0x95
#define EQ_KEY_AX              0x96
#define EQ_KEY_UNLABELED       0x97
#define EQ_KEY_NEXTTRACK       0x99
#define EQ_KEY_NEXT_TRACK      EQ_KEY_NEXTTRACK
#define EQ_KEY_NUMPADENTER     0x9C
#define EQ_KEY_NUMPAD_ENTER    EQ_KEY_NUMPADENTER
#define EQ_KEY_RCONTROL        0x9D
#define EQ_KEY_RIGHT_CONTROL   EQ_KEY_RCONTROL
#define EQ_KEY_MUTE            0xA0
#define EQ_KEY_CALCULATOR      0xA1
#define EQ_KEY_PLAYPAUSE       0xA2
#define EQ_KEY_PLAY_PAUSE      EQ_KEY_PLAYPAUSE
#define EQ_KEY_MEDIASTOP       0xA4
#define EQ_KEY_MEDIA_STOP      EQ_KEY_MEDIASTOP
#define EQ_KEY_VOLUMEDOWN      0xAE
#define EQ_KEY_VOLUME_DOWN     EQ_KEY_VOLUMEDOWN
#define EQ_KEY_VOLUMEUP        0xB0
#define EQ_KEY_VOLUME_UP       EQ_KEY_VOLUMEUP
#define EQ_KEY_WEBHOME         0xB2
#define EQ_KEY_WEB_HOME        EQ_KEY_WEBHOME
#define EQ_KEY_NUMPADCOMMA     0xB3
#define EQ_KEY_NUMPAD_COMMA    EQ_KEY_NUMPADCOMMA
#define EQ_KEY_DIVIDE          0xB5
#define EQ_KEY_NUMPADSLASH     EQ_KEY_DIVIDE
#define EQ_KEY_NUMPAD_DIVIDE   EQ_KEY_DIVIDE
#define EQ_KEY_SYSRQ           0xB7
#define EQ_KEY_RMENU           0xB8
#define EQ_KEY_RALT            EQ_KEY_RMENU
#define EQ_KEY_RIGHT_ALT       EQ_KEY_RMENU
#define EQ_KEY_PAUSE           0xC5
#define EQ_KEY_HOME            0xC7
#define EQ_KEY_UP              0xC8
#define EQ_KEY_UPARROW         EQ_KEY_UP
#define EQ_KEY_UP_ARROW        EQ_KEY_UP
#define EQ_KEY_PRIOR           0xC9
#define EQ_KEY_PGUP            EQ_KEY_PRIOR
#define EQ_KEY_PAGE_UP         EQ_KEY_PRIOR
#define EQ_KEY_LEFT            0xCB
#define EQ_KEY_LEFTARROW       EQ_KEY_LEFT
#define EQ_KEY_LEFT_ARROW      EQ_KEY_LEFT
#define EQ_KEY_RIGHT           0xCD
#define EQ_KEY_RIGHTARROW      EQ_KEY_RIGHT
#define EQ_KEY_RIGHT_ARROW     EQ_KEY_RIGHT
#define EQ_KEY_END             0xCF
#define EQ_KEY_DOWN            0xD0
#define EQ_KEY_DOWNARROW       EQ_KEY_DOWN
#define EQ_KEY_DOWN_ARROW      EQ_KEY_DOWN
#define EQ_KEY_NEXT            0xD1
#define EQ_KEY_PGDN            EQ_KEY_NEXT
#define EQ_KEY_PAGE_DOWN       EQ_KEY_NEXT
#define EQ_KEY_INSERT          0xD2
#define EQ_KEY_DELETE          0xD3
#define EQ_KEY_LWIN            0xDB
#define EQ_KEY_LEFT_START      EQ_KEY_LWIN
#define EQ_KEY_RWIN            0xDC
#define EQ_KEY_RIGHT_START     EQ_KEY_RWIN
#define EQ_KEY_APPS            0xDD
#define EQ_KEY_POWER           0xDE
#define EQ_KEY_SLEEP           0xDF
#define EQ_KEY_WAKE            0xE3
#define EQ_KEY_WEBSEARCH       0xE5
#define EQ_KEY_WEB_SEARCH      EQ_KEY_WEBSEARCH
#define EQ_KEY_WEBFAVORITES    0xE6
#define EQ_KEY_WEB_FAVORITES   EQ_KEY_WEBFAVORITES
#define EQ_KEY_WEBREFRESH      0xE7
#define EQ_KEY_WEB_REFRESH     EQ_KEY_WEBREFRESH
#define EQ_KEY_WEBSTOP         0xE8
#define EQ_KEY_WEB_STOP        EQ_KEY_WEBSTOP
#define EQ_KEY_WEBFORWARD      0xE9
#define EQ_KEY_WEB_FORWARD     EQ_KEY_WEBFORWARD
#define EQ_KEY_WEBBACK         0xEA
#define EQ_KEY_WEB_BACK        EQ_KEY_WEBBACK
#define EQ_KEY_MYCOMPUTER      0xEB
#define EQ_KEY_MY_COMPUTER     EQ_KEY_MYCOMPUTER
#define EQ_KEY_MAIL            0xEC
#define EQ_KEY_MEDIASELECT     0xED
#define EQ_KEY_MEDIA_SELECT    EQ_KEY_MEDIASELECT

#define EQ_INVENTORY_SLOT_EAR_LEFT    0
#define EQ_INVENTORY_SLOT_HEAD        1
#define EQ_INVENTORY_SLOT_FACE        2
#define EQ_INVENTORY_SLOT_EAR_RIGHT   3
#define EQ_INVENTORY_SLOT_NECK        4
#define EQ_INVENTORY_SLOT_SHOULDERS   5
#define EQ_INVENTORY_SLOT_ARMS        6
#define EQ_INVENTORY_SLOT_BACK        7
#define EQ_INVENTORY_SLOT_WRIST_LEFT  8
#define EQ_INVENTORY_SLOT_WRIST_RIGHT 9
#define EQ_INVENTORY_SLOT_RANGED      10
#define EQ_INVENTORY_SLOT_HANDS       11
#define EQ_INVENTORY_SLOT_PRIMARY     12
#define EQ_INVENTORY_SLOT_SECONDARY   13
#define EQ_INVENTORY_SLOT_RING_LEFT   14
#define EQ_INVENTORY_SLOT_RING_RIGHT  15
#define EQ_INVENTORY_SLOT_CHEST       16
#define EQ_INVENTORY_SLOT_LEGS        17
#define EQ_INVENTORY_SLOT_FEET        18
#define EQ_INVENTORY_SLOT_WAIST       19
#define EQ_INVENTORY_SLOT_AMMO        20
#define EQ_INVENTORY_SLOT_BAG1        21
#define EQ_INVENTORY_SLOT_BAG2        22
#define EQ_INVENTORY_SLOT_BAG3        23
#define EQ_INVENTORY_SLOT_BAG4        24
#define EQ_INVENTORY_SLOT_BAG5        25
#define EQ_INVENTORY_SLOT_BAG6        26
#define EQ_INVENTORY_SLOT_BAG7        27
#define EQ_INVENTORY_SLOT_BAG8        28
#define EQ_INVENTORY_SLOT_FIRST       EQ_INVENTORY_SLOT_EAR_LEFT
#define EQ_INVENTORY_SLOT_LAST        EQ_INVENTORY_SLOT_BAG8

const size_t EQ_STRINGSIZE_TEXT_COLOR_NAME = 21;

const char* EQ_STRING_TEXT_COLOR_NAME[EQ_STRINGSIZE_TEXT_COLOR_NAME] =
{
	"Black",
	"Gray",
	"Green",
	"Gray 2",
	"Blue",
	"Pink",
	"Gray 3",
	"White",
	"Gray 4",
	"Gray 5",
	"White 2",
	"Gray 6",
	"Light Gray",
	"Red",
	"Light Green",
	"Yellow",
	"Light Blue",
	"Gray 7",
	"Cyan",
	"Gray 8",
	"Black 2",
};

const size_t EQ_STRINGSIZE_RACE_NAME = 13;

const char* EQ_STRING_RACE_NAME[EQ_STRINGSIZE_RACE_NAME] =
{
	"Unknown",
	"Human",
	"Barbarian",
	"Erudite",
	"Wood Elf",
	"High Elf",
	"Dark Elf",
	"Half Elf",
	"Dwarf",
	"Troll",
	"Ogre",
	"Halfling",
	"Gnome",
	// Iksar
	// Vah Shir
	// Froglok
};

const size_t EQ_STRINGSIZE_RACE_SHORT_NAME = 13;

const char* EQ_STRING_RACE_SHORT_NAME[EQ_STRINGSIZE_RACE_SHORT_NAME] =
{
	"UNK",
	"HUM",
	"BAR",
	"ERU",
	"ELF",
	"HIE",
	"DEF",
	"HEF",
	"DWF",
	"TRL",
	"OGR",
	"HFL",
	"GNM",
	// IKS
	// VAH
	// FRG
};

const size_t EQ_STRINGSIZE_CLASS_NAME = 33;

const char* EQ_STRING_CLASS_NAME[EQ_STRINGSIZE_CLASS_NAME] =
{
	"Unknown",
	"Warrior",
	"Cleric",
	"Paladin",
	"Ranger",
	"Shadow Knight",
	"Druid",
	"Monk",
	"Bard",
	"Rogue",
	"Shaman",
	"Necromancer",
	"Wizard",
	"Magician",
	"Enchanter",
	"Beastlord",
	"Banker",
	"Warrior GM",
	"Cleric GM",
	"Paladin GM",
	"Ranger GM",
	"Shadow Knight GM",
	"Druid GM",
	"Monk GM",
	"Bard GM",
	"Rogue GM",
	"Shaman GM",
	"Necromancer GM",
	"Wizard GM",
	"Magician GM",
	"Enchanter GM",
	"Beastlord GM",
	"Merchant",
};

const size_t EQ_STRINGSIZE_CLASS_SHORT_NAME = 33;

const char* EQ_STRING_CLASS_SHORT_NAME[EQ_STRINGSIZE_CLASS_SHORT_NAME] =
{
	"UNK",
	"WAR",
	"CLR",
	"PAL",
	"RNG",
	"SHD",
	"DRU",
	"MNK",
	"BRD",
	"ROG",
	"SHM",
	"NEC",
	"WIZ",
	"MAG",
	"ENC",
	"BST",
	"BANKER",
	"WAR",
	"CLR",
	"PAL",
	"RNG",
	"SHD",
	"DRU",
	"MNK",
	"BRD",
	"ROG",
	"SHM",
	"NEC",
	"WIZ",
	"MAG",
	"ENC",
	"BST",
	"MERCHANT",
};

const size_t EQ_STRINGSIZE_SKILL_NAME = 76;

const char* EQ_STRING_SKILL_NAME[EQ_STRINGSIZE_SKILL_NAME] =
{
	"1H Blunt",
	"1H Slashing",
	"2H Blunt",
	"2H Slashing",
	"Abjuration",
	"Alteration",
	"Apply Poison",
	"Archery",
	"Backstab",
	"Bind Wound",
	"Bash",
	"Block",
	"Brass Instruments",
	"Channeling",
	"Conjuration",
	"Defense",
	"Disarm",
	"Disarm Traps",
	"Divination",
	"Dodge",
	"Double Attack",
	"Dragon Punch", // also "Tail Rake"
	"Dual Wield",
	"Eagle Strike",
	"Evocation",
	"Feign Death",
	"Flying Kick",
	"Forage",
	"Hand To Hand",
	"Hide",
	"Kick",
	"Meditate",
	"Mend",
	"Offense",
	"Parry",
	"Pick Lock",
	"Piercing",
	"Riposte",
	"Round Kick",
	"Safe Fall",
	"Sense Heading",
	"Singing",
	"Sneak",
	"Specialize Abjuration",
	"Specialize Alteration",
	"Specialize Conjuration",
	"Specialize Divination",
	"Specialize Evocation",
	"Pick Pockets",
	"Stringed Instruments",
	"Swimming",
	"Throwing",
	"Tiger Claw",
	"Tracking",
	"Wind Instruments",
	"Fishing",
	"Make Poison",
	"Tinkering",
	"Research",
	"Alchemy",
	"Baking",
	"Tailoring",
	"Sense Traps",
	"Blacksmithing",
	"Fletching",
	"Brewing",
	"Alcohol Tolerance",
	"Begging",
	"Jewelry Making",
	"Pottery",
	"Percussion Instruments",
	"Intimidation",
	"Berserking",
	"Taunt",
	"Frenzy",
	"Generic Tradeskill",
	//"Slam", // Slam is skill index 111
};

const size_t EQ_KEYVALUESTRINGLISTSIZE_DOOR_SPAWN_NAME_DESCRIPTION = 22;

const char* EQ_KEYVALUESTRINGLIST_DOOR_SPAWN_NAME_DESCRIPTION[][2] =
{
	{ "POKTELE500",    "Plane of Knowledge Portal" }, // POK book

	{ "POKAAPORT500",  "Ak'Anon Portal" },
	{ "POKCABPORT500", "Cabilis Portal" },
	{ "POKERPORT500",  "Erudin Portal" },
	{ "POKFELPORT500", "Felwithe Portal" },
	{ "POKFVPORT500",  "Firiona Vie Portal" },
	{ "POKFPTPORT500", "Freeport Portal" },
	{ "POKGROPORT500", "Grobb Portal" },
	{ "POKHALPORT500", "Halas Portal" },
	{ "POKKALPORT500", "Kaladim Portal" },
	{ "POKKELPORT500", "Kelethin Portal" },
	{ "POKNRKPORT500", "Neriak Portal" },
	{ "POKOGPORT500",  "Oggok Portal" },
	{ "POKOVPORT500",  "Overthere Portal" },
	{ "POKPPORT500",   "Paineel Portal" },
	{ "POKPTPORT500",  "Plane of Tranquility Portal" },
	{ "POKQNSPORT500", "Qeynos Portal" },
	{ "POKRVPORT500",  "Rivervale Portal" },
	{ "POKSHPORT500",  "Shar Vahl Portal" },
	{ "POKTGDPORT500", "The Great Divide Portal" },
	{ "POKTNPORT500",  "The Nexus Portal" },

	{ "FAYLEVATOR",    "Faydark Elevator" },
};

const size_t EQ_KEYVALUESTRINGLISTSIZE_GROUND_SPAWN_NAME_DESCRIPTION = 11;

const char* EQ_KEYVALUESTRINGLIST_GROUND_SPAWN_NAME_DESCRIPTION[][2] =
{
	{ "IT27_ACTORDEF",    "Book" },
	{ "IT28_ACTORDEF",    "Book" },
	{ "IT63_ACTORDEF",    "Small Bag" },
	{ "IT64_ACTORDEF",    "Large Bag" },
	{ "IT66_ACTORDEF",    "Forge" },
	{ "IT69_ACTORDEF",    "Oven" },
	{ "IT70_ACTORDEF",    "Brew Barrel" },
	{ "IT73_ACTORDEF",    "Kiln" },
	{ "IT74_ACTORDEF",    "Pottery Wheel" },
	{ "IT128_ACTORDEF",   "Sewing Kit" },
	{ "IT10645_ACTORDEF", "Book" },
};

// font glpyh sizes use ASCII table indexes

int EQ_FONT_GLYPH_SIZES_ARIAL10[128] =
{
	6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,
	2 ,3 ,3 ,4 ,4 ,7 ,5 ,2 ,3 ,3 ,3 ,5 ,2 ,3 ,2 ,2 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,2 ,2 ,5 ,5 ,5 ,4 ,
	8 ,5 ,5 ,6 ,6 ,5 ,5 ,6 ,6 ,2 ,4 ,5 ,4 ,7 ,6 ,6 ,5 ,6 ,6 ,5 ,5 ,6 ,5 ,7 ,5 ,5 ,5 ,2 ,2 ,2 ,3 ,4 ,
	3 ,4 ,4 ,4 ,4 ,4 ,2 ,5 ,4 ,2 ,2 ,3 ,2 ,6 ,4 ,4 ,4 ,5 ,3 ,4 ,2 ,4 ,3 ,5 ,3 ,3 ,4 ,3 ,3 ,3 ,5 ,6 ,
};

int EQ_FONT_GLYPH_SIZES_ARIAL12[128] =
{
	7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,
	3 ,3 ,3 ,5 ,5 ,8 ,6 ,2 ,3 ,3 ,4 ,5 ,3 ,3 ,3 ,3 ,5 ,5 ,5 ,5 ,5 ,5 ,5 ,5 ,5 ,5 ,3 ,3 ,5 ,5 ,5 ,5 ,
	9 ,6 ,6 ,7 ,7 ,6 ,6 ,7 ,7 ,3 ,5 ,6 ,5 ,7 ,7 ,7 ,6 ,7 ,7 ,6 ,5 ,7 ,6 ,9 ,5 ,7 ,6 ,3 ,3 ,3 ,3 ,5 ,
	3 ,5 ,5 ,5 ,5 ,5 ,4 ,5 ,5 ,2 ,2 ,5 ,2 ,8 ,5 ,5 ,5 ,5 ,3 ,5 ,3 ,5 ,6 ,6 ,5 ,6 ,4 ,3 ,3 ,3 ,5 ,7 ,
};

int EQ_FONT_GLYPH_SIZES_ARIAL14[128] =
{
	8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,
	3 ,2 ,4 ,6 ,6 ,10,7 ,2 ,4 ,4 ,4 ,6 ,3 ,4 ,3 ,3 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,3 ,3 ,6 ,6 ,6 ,6 ,
	11,8 ,7 ,7 ,7 ,6 ,6 ,8 ,7 ,2 ,5 ,7 ,6 ,8 ,7 ,8 ,6 ,8 ,7 ,7 ,6 ,7 ,8 ,10,7 ,8 ,7 ,3 ,3 ,3 ,5 ,6 ,
	4 ,6 ,6 ,6 ,6 ,6 ,4 ,6 ,6 ,2 ,2 ,5 ,2 ,8 ,6 ,6 ,6 ,6 ,4 ,6 ,3 ,6 ,6 ,10,6 ,6 ,6 ,4 ,2 ,4 ,6 ,8 ,
};

int EQ_FONT_GLYPH_SIZES_ARIAL15[128] =
{
	9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,
	3 ,3 ,4 ,7 ,7 ,11,8 ,2 ,4 ,4 ,5 ,7 ,3 ,4 ,3 ,3 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,3 ,3 ,7 ,7 ,7 ,7 ,
	12,7 ,8 ,9 ,9 ,8 ,7 ,9 ,9 ,3 ,6 ,8 ,7 ,9 ,9 ,9 ,8 ,9 ,9 ,8 ,7 ,9 ,7 ,11,7 ,7 ,7 ,3 ,3 ,3 ,5 ,7 ,
	4 ,7 ,7 ,6 ,7 ,7 ,3 ,7 ,7 ,3 ,3 ,6 ,3 ,11,7 ,7 ,7 ,7 ,4 ,7 ,3 ,7 ,5 ,9 ,5 ,5 ,5 ,4 ,3 ,4 ,7 ,9 ,
};

int EQ_FONT_GLYPH_SIZES_ARIAL16[128] =
{
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
	4 ,3 ,5 ,7 ,7 ,12,9 ,2 ,4 ,4 ,5 ,8 ,4 ,4 ,4 ,4 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,4 ,4 ,8 ,8 ,8 ,7 ,
	13,9 ,9 ,9 ,9 ,9 ,8 ,10,9 ,3 ,6 ,9 ,7 ,11,9 ,10,9 ,10,9 ,9 ,7 ,9 ,9 ,13,7 ,9 ,7 ,4 ,4 ,4 ,5 ,7 ,
	4 ,7 ,7 ,7 ,7 ,7 ,3 ,7 ,7 ,3 ,3 ,7 ,3 ,11,7 ,7 ,7 ,7 ,4 ,7 ,4 ,7 ,5 ,9 ,7 ,7 ,7 ,4 ,3 ,4 ,8 ,10,
};

int EQ_FONT_GLYPH_SIZES_ARIAL20[128] =
{
	13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
	5 ,5 ,6 ,9 ,9 ,15,11,3 ,6 ,6 ,7 ,10,5 ,6 ,5 ,5 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,5 ,5 ,10,10,10,9 ,
	17,11,11,12,12,11,10,12,11,5 ,9 ,11,9 ,13,11,12,11,12,11,11,9 ,11,11,17,11,11,9 ,5 ,5 ,5 ,7 ,9 ,
	6 ,9 ,9 ,9 ,9 ,9 ,5 ,9 ,9 ,4 ,3 ,8 ,3 ,13,9 ,9 ,9 ,9 ,6 ,8 ,4 ,9 ,7 ,11,7 ,9 ,8 ,6 ,5 ,6 ,10,13,
};

/****************************************************************************************************/

typedef struct _EQLOCATION
{
	FLOAT Y;
	FLOAT X;
	FLOAT Z;
} EQLOCATION, *PEQLOCATION;

typedef struct _EQLINE
{
	FLOAT X1;
	FLOAT Y1;
	FLOAT Z1;
	FLOAT X2;
	FLOAT Y2;
	FLOAT Z2;
} EQLINE, *PEQLINE;

typedef struct _EQRECT
{
	FLOAT X1;
	FLOAT Y1;
	FLOAT Z1;
	FLOAT X2;
	FLOAT Y2;
	FLOAT Z2;
	FLOAT X3;
	FLOAT Y3;
	FLOAT Z3;
	FLOAT X4;
	FLOAT Y4;
	FLOAT Z4;
} EQRECT, *PEQRECT;

typedef struct _EQMAPLINE
{
	struct _EQMAPLINE* Next;
	FLOAT X1;
	FLOAT Y1;
	FLOAT Z1;
	FLOAT X2;
	FLOAT Y2;
	FLOAT Z2;
	union
	{
		struct
		{
			BYTE B;
			BYTE G;
			BYTE R;
			BYTE Unused;
		};
		DWORD RGB;
	};
	BYTE Layer;
} EQMAPLINE, *PEQMAPLINE;

typedef struct _EQMAPPOINT
{
	struct _EQMAPPOINT* Next;
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
	union
	{
		struct
		{
			BYTE B;
			BYTE G;
			BYTE R;
			BYTE Unused;
		};
		DWORD Color;
	};
	DWORD Size;
	CHAR Text[128];
	BYTE Layer;
} EQMAPPOINT, *PEQMAPPOINT;

typedef struct _EQARGBCOLOR
{
	union
	{
		struct
		{
			BYTE B;
			BYTE G;
			BYTE R;
			BYTE A;
		};
		DWORD Color;
	};
} EQARGBCOLOR, *PEQARGBCOLOR;

typedef struct _EQRGBCOLOR
{
	BYTE B;
	BYTE G;
	BYTE R;
} EQRGBCOLOR, *PEQRGBCOLOR;

typedef struct _EQFONT
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ DWORD Size;
} EQFONT, *PEQFONT;

typedef struct _EQCAMERAINFO
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ DWORD RegionNumber;
	/* 0x0008 */ FLOAT Y;
	/* 0x000C */ FLOAT X;
	/* 0x0010 */ FLOAT Z;
	/* 0x0014 */ FLOAT Heading; // Yaw
	/* 0x0018 */ FLOAT Pitch;
	/* 0x001C */ FLOAT Roll;
	/* 0x0020 */ FLOAT FieldOfView;
	/* 0x0024 */ FLOAT AspectRatio;
	/* 0x0028 */ FLOAT Unknown0028;
	/* 0x002C */ FLOAT Unknown002C;
	/* 0x0030 */ FLOAT DrawDistance;
	/* 0x0034 */ BYTE Unknown0034[20];
	/* 0x0048 */ DWORD ResolutionWidth;
	/* 0x004C */ DWORD ResolutionHeight;
	/* 0x0050 */ BYTE Unknown0050[12];
	/* 0x005C */ FLOAT Unknown005C;
	/* 0x0060 */ FLOAT Unknown0060;
	/* 0x0064 */ FLOAT ResolutionWidthHalf;
	/* 0x0068 */ FLOAT ResolutionHeightHalf;
	/* ...... */
} EQCAMERAINFO, *PEQCAMERAINFO;

typedef struct _EQLIGHTINSTANCEINFO
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ DWORD Unknown0004;
	/* 0x0008 */ DWORD Unknown0008;
	/* 0x000C */ DWORD Unknown000C;
	/* 0x0010 */ DWORD Unknown0010;
	/* 0x0014 */ DWORD CurrentFrame;
	/* 0x0018 */ DWORD UpdateInterval;
	/* 0x001C */ DWORD SkipFrames;
	/* ...... */
} EQLIGHTINSTANCEINFO, *PEQLIGHTINSTANCEINFO;

typedef struct _EQLIGHTINFO
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ DWORD Unknown0004;
	/* 0x0008 */ DWORD Tag;
	/* 0x000C */ DWORD Type;
	/* 0x0010 */ struct _EQLIGHTINSTANCEINFO* LightInstance;
	/* 0x0014 */ FLOAT Y;
	/* 0x0018 */ FLOAT X;
	/* 0x001C */ FLOAT Z;
	/* 0x0020 */ FLOAT RadiusOfInfluence;
	/* 0x0024 */ DWORD Unknown0024;
	/* 0x0028 */ DWORD Unknown0028;
	/* 0x002C */ PVOID Unknown002C;
	/* ...... */
} EQLIGHTINFO, *PEQLIGHTINFO;

typedef struct _EQZONEINFO
{
	/* 0x0000 */ CHAR PlayerName[64]; // [0x40]
	/* 0x0040 */ CHAR ShortName[32]; // [0x20]
	/* 0x0060 */ CHAR LongName[128]; // [0x80]
	/* 0x00E0 */ BYTE Unknown00E0[150];
	/* 0x0176 */ BYTE Type;
	/* 0x0177 */ BYTE FogColorRed[4];
	/* 0x017B */ BYTE FogColorGreen[4];
	/* 0x017F */ BYTE FogColorBlue[4];
	/* 0x0183 */ BYTE Unknown0183;
	/* 0x0184 */ FLOAT Unknown0184;
	/* 0x0188 */ FLOAT Unknown0188;
	/* 0x018C */ FLOAT Unknown018C;
	/* 0x0190 */ FLOAT Unknown0190;
	/* 0x0194 */ FLOAT Unknown0194;
	/* 0x0198 */ FLOAT Unknown0198;
	/* 0x019C */ FLOAT Unknown019C;
	/* 0x01A0 */ FLOAT Unknown01A0;
	/* 0x01A4 */ FLOAT Gravity;
	/* 0x01A8 */ BYTE Unknown01A8;
	/* 0x01A9 */ BYTE Unknown01A9;
	/* 0x01AA */ BYTE Unknown01AA;
	/* 0x01AB */ BYTE Unknown01AB;
	/* 0x01AC */ BYTE Unknown01AC;
	/* 0x01AD */ BYTE Unknown01AD[45];
	/* 0x01DA */ BYTE SkyType;
	/* 0x01DB */ BYTE Unknown01DB[9];
	/* 0x01E4 */ FLOAT ExperienceMultiplier;
	/* 0x01E8 */ FLOAT SafeCoordsY; // CDisplay::MoveLocalPlayerToSafeCoords
	/* 0x01EC */ FLOAT SafeCoordsX;
	/* 0x01F0 */ FLOAT SafeCoordsZ;
	/* 0x01F4 */ FLOAT Unknown01F4;
	/* 0x01F8 */ FLOAT Unknown01F8;
	/* 0x01FC */ FLOAT MinClip; // draw distance (minimum Far Clip Plane)
	/* 0x0200 */ FLOAT MaxClip; // draw distance (maximum Far Clip Plane)
								/* ...... */
} EQZONEINFO, *PEQZONEINFO;

// sizeof 0x0A
typedef struct _EQBUFFINFO
{
	/* 0x0000 */ BYTE BuffType;
	/* 0x0001 */ BYTE CasterLevel; // level of player who casted the buff
	/* 0x0002 */ BYTE Modifier; // divide by 10 to get Bard song modifier
	/* 0x0003 */ BYTE Activated;
	/* 0x0004 */ WORD SpellId;
	/* 0x0006 */ WORD Ticks; //  duration in ticks ; seconds = ticks * 3
	/* 0x0008 */ WORD Counters;
	/* 0x000A */
} EQBUFFINFO, *PEQBUFFINFO;

typedef struct _EQITEMCOMMONINFO
{
	/* 0x00E4 */ INT8 Strength;       // STR
	/* 0x00E5 */ INT8 Stamina;        // STA
	/* 0x00E6 */ INT8 Charisma;       // CHA
	/* 0x00E7 */ INT8 Dexterity;      // DEX
	/* 0x00E8 */ INT8 Intelligence;   // INT
	/* 0x00E9 */ INT8 Agility;        // AGI
	/* 0x00EA */ INT8 Wisdom;         // WIS
	/* 0x00EB */ INT8 SaveMagic;      // SV MAGIC
	/* 0x00EC */ INT8 SaveFire;       // SV FIRE
	/* 0x00ED */ INT8 SaveCold;       // SV COLD
	/* 0x00EE */ INT8 SaveDisease;    // SV DISEASE
	/* 0x00EF */ INT8 SavePoison;     // SV POISON
	/* 0x00F0 */ INT16 Health;        // HP
	/* 0x00F2 */ INT16 Mana;          // Mana
	/* 0x00F4 */ INT16 ArmorClass;    // AC
	/* 0x00F6 */ BYTE Unknown0246[2];
	/* 0x00F8 */ BYTE Light;
	/* 0x00F9 */ BYTE AttackDelay;    // Atk Delay
	/* 0x00FA */ BYTE Damage;         // DMG
	/* 0x00FB */ BYTE IsStackableEx;
	/* 0x00FC */ BYTE Range;
	/* 0x00FD */ BYTE Skill;
	/* 0x00FE */ BYTE Magic;
	/* 0x00FF */ BYTE CastingLevelEx;
	/* 0x0100 */ BYTE Material; // 0=None, 1=Leather, 2=Chain, 3=Plate, 4=Silk, etc
	/* 0x0101 */ BYTE Unknown0258[3];
	/* 0x0104 */ DWORD Color;
	/* 0x0108 */ BYTE Unknown0264[2];
	/* 0x010A */ WORD SpellIdEx;
	/* 0x010C */ WORD Classes; // bitwise flag
	/* 0x010E */ BYTE Unknown0270[2];
	/* 0x0110 */ WORD Races; // bitwise flag
	/* 0x0112 */ BYTE Unknown0274[2];
	/* 0x0114 */ BYTE IsStackable;
	/* 0x0115 */ BYTE CastingLevel; // also weapon proc level
	union
	{
		/* 0x0116 */ BYTE StackCount;
		/* 0x0116 */ BYTE Charges;
	};
	/* 0x0117 */ BYTE EffectType;
	/* 0x0118 */ WORD SpellId;
	/* 0x011A */ BYTE Unknown0123[10];
	/* 0x0124 */ WORD SkillModId;
	/* 0x0126 */ INT8 SkillModPercent;
	/* ...... */
} EQITEMCOMMONINFO, *PEQITEMCOMMONINFO;

typedef struct _EQITEMCONTAINERINFO
{
	/* 0x00E4 */ struct _EQITEMINFO* Item[EQ_NUM_CONTAINER_SLOTS];
	/* 0x010C */ BYTE Combine;
	/* 0x010D */ BYTE Capacity; // num slots
	/* 0x010E */ BYTE IsOpen;
	/* 0x010F */ BYTE SizeCapacity;
	/* 0x0110 */ BYTE WeightReduction; // percent
									   /* ...... */
} EQITEMCONTAINERINFO, *PEQITEMCONTAINERINFO;

typedef struct _EQITEMBOOKINFO
{
	/* 0x00E4 */ BYTE Unknown0228[3];
	/* 0x00E7 */ CHAR File[15];
	/* ...... */
} EQITEMBOOKINFO, *PEQITEMBOOKINFO;

typedef struct _EQITEMINFO
{
	/* 0x0000 */ CHAR Name[64]; // [0x40]
	/* 0x0040 */ CHAR LoreName[80]; // [0x50]
	/* 0x0090 */ CHAR IdFile[6]; // [0x06]
	/* 0x0096 */ BYTE Unknown0096[24];
	/* 0x00AE */ BYTE Weight; // multiply by 0.1 for actual decimal weight
	/* 0x00AF */ BYTE NoRent; // 0x00 = True, 0xFF = False
	/* 0x00B0 */ BYTE NoDrop; // 0x00 = True, 0xFF = False
	/* 0x00B1 */ BYTE Size; // EQ_ITEM_SIZE_x
	/* 0x00B2 */ BYTE IsContainer;
	/* 0x00B3 */ BYTE Unknown00B3;
	/* 0x00B4 */ WORD Id;
	/* 0x00B6 */ WORD Icon;
	/* 0x00B8 */ DWORD EquipSlot;
	/* 0x00BC */ DWORD EquippableSlots; // flag
	/* 0x00C0 */ DWORD Cost; // value in copper, sells to merchant for value
	/* 0x00C4 */ BYTE Unknown00C4[32];
	union
	{
		/* 0x00E4 */ EQITEMCOMMONINFO    Common;
		/* 0x00E4 */ EQITEMCONTAINERINFO Container;
		/* 0x00E4 */ EQITEMBOOKINFO      Book;
	};
	/* ...... */
} EQITEMINFO, *PEQITEMINFO;

// class EQ_Spell
// sizeof 0x110
// reference eqemulator /common/sp.dat.h
typedef struct _EQSPELLINFO
{
	/* 0x0000 */ DWORD Id;
	/* 0x0004 */ FLOAT Range;
	/* 0x0008 */ FLOAT AoeRange;
	/* 0x000C */ FLOAT PushBack;
	/* 0x0010 */ FLOAT PushUp;
	/* 0x0014 */ DWORD CastTime;
	/* 0x0018 */ DWORD RecoveryTime;
	/* 0x001C */ DWORD RecastTime;
	/* 0x0020 */ DWORD DurationFormula;
	/* 0x0024 */ DWORD Duration;
	/* 0x0028 */ DWORD AoeDuration;
	/* 0x002C */ WORD Mana;
	/* 0x002E */ short Base[12];
	/* 0x0046 */ short Max[12];
	/* 0x005E */ WORD BookIcon;
	/* 0x0060 */ WORD GemIcon;
	/* 0x0062 */ short ReagentId[4];
	/* 0x006A */ short ReagentCount[4];
	/* 0x0072 */ BYTE Unknown0146[8];
	/* 0x007A */ BYTE Calc[12];
	/* 0x0086 */ BYTE LightType;
	/* 0x0087 */ BYTE BuffType; // 0x00 = Detrimental, 0x01 = Beneficial, 0x02 = Beneficial (Group Only)
	/* 0x0088 */ BYTE Activated; // unknown
	/* 0x0089 */ BYTE ResistType;
	/* 0x008A */ BYTE Attribute[12];
	/* 0x0096 */ BYTE TargetType;
	/* 0x0097 */ BYTE FizzleAdjustment;
	/* 0x0098 */ BYTE SkillType;
	/* 0x0099 */ BYTE ZoneType; // 0x01 = Outdoors, 0x02 = Dungeons, 0xFF = Any
	/* 0x009A */ BYTE ZoneType2;
	/* 0x009B */ BYTE EnvironmentType;
	/* 0x009C */ BYTE TimeOfDay;
	/* 0x009D */ BYTE Level[15]; // minimum level to cast for each class
	/* 0x00AC */ BYTE Unknown0192[36];
	/* 0x00D0 */ PCHAR Name;        // [32]
	/* 0x00D4 */ PCHAR Target;      // [16]
	/* 0x00D8 */ PCHAR Extra;       // [32] ; Teleport zone, pet name summoned or item summoned
	/* 0x00DC */ PCHAR YouCast;     // [40]
	/* 0x00E0 */ PCHAR OtherCasts;  // [40]
	/* 0x00E4 */ PCHAR CastOnYou;   // [32]
	/* 0x00E8 */ PCHAR CastOnOther; // [40]
	/* 0x00EC */ PCHAR WearOff;     // [32]
									/* ...... */
} EQSPELLINFO, *PEQSPELLINFO;

typedef struct _EQSPELLLIST
{
	struct _EQSPELLINFO* Spell[EQ_NUM_SPELLS];
} EQSPELLLIST, *PEQSPELLLIST;

// 21 inventory slots
typedef struct _EQINVENTORY
{
	/* 00 */ struct _EQITEMINFO* EarLeft;
	/* 01 */ struct _EQITEMINFO* Head;
	/* 02 */ struct _EQITEMINFO* Face;
	/* 03 */ struct _EQITEMINFO* EarRight;
	/* 04 */ struct _EQITEMINFO* Neck;
	/* 05 */ struct _EQITEMINFO* Shoulders;
	/* 06 */ struct _EQITEMINFO* Arms;
	/* 07 */ struct _EQITEMINFO* Back;
	/* 08 */ struct _EQITEMINFO* WristLeft;
	/* 09 */ struct _EQITEMINFO* WristRight;
	/* 10 */ struct _EQITEMINFO* Ranged;
	/* 11 */ struct _EQITEMINFO* Hands;
	/* 12 */ struct _EQITEMINFO* Primary;
	/* 13 */ struct _EQITEMINFO* Secondary;
	/* 14 */ struct _EQITEMINFO* RingLeft;
	/* 15 */ struct _EQITEMINFO* RingRight;
	/* 16 */ struct _EQITEMINFO* Chest;
	/* 17 */ struct _EQITEMINFO* Legs;
	/* 18 */ struct _EQITEMINFO* Feet;
	/* 19 */ struct _EQITEMINFO* Waist;
	/* 20 */ struct _EQITEMINFO* Ammo;
} EQINVENTORY, *PEQINVENTORY;

// class EQ_Character
typedef struct _EQCHARINFO
{
	/* 0x0000 */ BYTE Unknown0000[2];
	/* 0x0002 */ CHAR Name[64]; // [0x40]
	/* 0x0042 */ CHAR LastName[70]; // [0x46] ; surname or title
	/* 0x0088 */ WORD Gender; // EQ_GENDER_x
	/* 0x008A */ WORD Race; // EQ_RACE_x
	/* 0x008C */ WORD Class; // EQ_CLASS_x
	/* 0x008E */ WORD Unknown008E;
	/* 0x0090 */ WORD Level;
	/* 0x0092 */ WORD Unknown0092;
	/* 0x0094 */ DWORD Experience; // EXP
	/* 0x0098 */ WORD PracticePoints; // Training window
	/* 0x009A */ WORD Mana;
	/* 0x009C */ WORD BaseHP;
	/* 0x009E */ WORD StunnedState; // EQ_STUNNED_STATE_x
	/* 0x00A0 */ WORD BaseSTR;
	/* 0x00A2 */ WORD BaseSTA;
	/* 0x00A4 */ WORD BaseCHA;
	/* 0x00A6 */ WORD BaseDEX;
	/* 0x00A8 */ WORD BaseINT;
	/* 0x00AA */ WORD BaseAGI;
	/* 0x00AC */ WORD BaseWIS;
	/* 0x00AE */ BYTE Unknown00AE[438];
	/* 0x0264 */ struct _EQBUFFINFO Buff[EQ_NUM_BUFFS];
	/* 0x02FA */ BYTE Unknown02FA[1080];
	/* 0x0732 */ WORD SpellBook[EQ_NUM_SPELL_BOOK_SPELLS];
	/* 0x0926 */ BYTE Unknown0926[524];
	/* 0x0B32 */ WORD MemorizedSpell[EQ_NUM_SPELL_GEMS]; // spell gem spell ids
	/* 0x0B42 */ BYTE Unknown0B42[14];
	/* 0x0B50 */ WORD Unknown0B50;
	/* 0x0B52 */ WORD Unknown0B52;
	/* 0x0B54 */ FLOAT ZoneEnterY;
	/* 0x0B58 */ FLOAT ZoneEnterX;
	/* 0x0B5C */ FLOAT ZoneEnterZ;
	/* 0x0B60 */ FLOAT Unknown0060;
	/* 0x0B64 */ BYTE StandingState; // EQ_STANDING_STATE_x
	/* 0x0B65 */ BYTE Unknown0B65[3];
	/* 0x0B68 */ DWORD Platinum;
	/* 0x0B6C */ DWORD Gold;
	/* 0x0B70 */ DWORD Silver;
	/* 0x0B74 */ DWORD Copper;
	/* 0x0B78 */ DWORD BankPlatinum;
	/* 0x0B7C */ DWORD BankGold;
	/* 0x0B80 */ DWORD BankSilver;
	/* 0x0B84 */ DWORD BankCopper;
	/* 0x0B88 */ DWORD CursorPlatinum; // currency held on the mouse cursor
	/* 0x0B8C */ DWORD CursorGold;
	/* 0x0B90 */ DWORD CursorSilver;
	/* 0x0B94 */ DWORD CursorCopper;
	/* 0x0B98 */ BYTE Unknown0B98[16];
	/* 0x0BA8 */ WORD Skill[EQ_NUM_SKILLS];
	/* 0x0C3C */ BYTE Unknown0C3C[64];
	/* 0x0C7C */ WORD Vision1;
	/* 0x0C7E */ BYTE Unknown0C7E[12];
	/* 0x0C8A */ WORD Vision2;
	/* 0x0C8C */ BYTE Unknown0C8C[120];
	/* 0x0D04 */ DWORD IsSwimmingUnderwater;
	/* 0x0D08 */ BYTE Unknown0D08[4];
	/* 0x0D0C */ BYTE Unknown0D0C[4];
	/* 0x0D10 */ BYTE IsAutoSplitEnabled;
	/* 0x0D11 */ BYTE Unknown0D11[43];
	/* 0x0D3C */ DWORD Unknown0D3C;
	/* 0x0D40 */ BYTE Unknown0D40[20];
	/* 0x0D54 */ DWORD Hunger;
	/* 0x0D58 */ DWORD Thirst;
	/* 0x0D5C */ BYTE Unknown0D5C[20];
	/* 0x0D70 */ DWORD ZoneId;
	/* 0x0D74 */ struct _EQSPAWNINFO* SpawnInfo;
	/* 0x0D78 */ struct _EQITEMINFO* CursorItem;
	union
	{
		/* 0x0D7C */ struct _EQINVENTORY Inventory;
		/* 0x0D7C */ struct _EQITEMINFO* InventoryItem[EQ_NUM_INVENTORY_SLOTS];
	};
	/* 0x0DD0 */ struct _EQITEMINFO* InventoryPackItem[EQ_NUM_INVENTORY_PACK_SLOTS];
	/* 0x0DF0 */ BYTE Unknown0DF0[116];
	/* 0x0E64 */ DWORD Unknown0E64;
	/* 0x0E68 */ BYTE Unknown0E68[32];
	/* 0x0E88 */ DWORD Unknown0E88;
	/* 0x0E8C */ BYTE Unknown0E8C[56];
	/* 0x0EC4 */ DWORD ZoneBoundId;
	/* 0x0EC8 */ DWORD Unknown0EC8;
	/* 0x0ECC */ DWORD Unknown0ECC;
	/* 0x0ED0 */ DWORD Unknown0ED0;
	/* 0x0ED4 */ DWORD ZoneBirthId;
	/* 0x0ED8 */ FLOAT ZoneBoundY;
	/* 0x0EDC */ DWORD Unknown0EDC;
	/* 0x0EE0 */ DWORD Unknown0EE0;
	/* 0x0EE4 */ DWORD Unknown0EE4;
	/* 0x0EE8 */ FLOAT ZoneBirthY;
	/* 0x0EEC */ FLOAT ZoneBoundX;
	/* 0x0EF0 */ DWORD Unknown0EF0;
	/* 0x0EF4 */ DWORD Unknown0EF4;
	/* 0x0EF8 */ DWORD Unknown0EF8;
	/* 0x0EFC */ FLOAT ZoneBirthX;
	/* 0x0F00 */ FLOAT ZoneBoundZ;
	/* 0x0F04 */ DWORD Unknown0F04;
	/* 0x0F08 */ DWORD Unknown0F08;
	/* 0x0F0C */ DWORD Unknown0F0C;
	/* 0x0F10 */ FLOAT ZoneBirthZ;
	/* 0x0F14 */ BYTE Unknown0F14[1080];
	/* 0x134C */ WORD Deity;
	/* 0x134E */ WORD GuildId;
	/* 0x1350 */ BYTE Unknown1350[8];
	/* 0x1358 */ BYTE Unknown1358;
	/* 0x1359 */ BYTE Unknown1359;
	/* 0x135A */ BYTE Unknown135A;
	/* 0x135B */ BYTE Unknown135B;
	/* 0x135C */ BYTE Unknown135C;
	/* 0x135D */ BYTE Unknown135D;
	/* 0x135E */ BYTE Stamina; // yellow endurance bar ; 100 = Empty, 0 = Full
	/* 0x135F */ BYTE Unknown135F;
	/* 0x1360 */ BYTE Unknown1360;
	/* 0x1361 */ BYTE AnonymousState;
	/* 0x1362 */ BYTE Unknown1362;
	/* 0x1363 */ BYTE GuildStatus; // guild rank
	/* 0x1364 */ BYTE Drunkness; // 0 = Not Drunk, counts down over time
	/* 0x1365 */ BYTE Unknown1365[451];
	/* 0x1528 */ DWORD AlternateAdvancementExperience;
	/* 0x152C */ BYTE Unknown152C[476];
	/* 0x1708 */ BYTE AirSupply; // air remaining while swimming underwater
	/* 0x1709 */ BYTE Unknown1709[2475];
	/* 0x20B4 */ struct _EQITEMINFO* InventoryBankItem[EQ_NUM_INVENTORY_BANK_SLOTS];
	/* ...... */
} EQCHARINFO, *PEQCHARINFO;

// used for name and guild name above head of each spawn
typedef struct _EQSTRINGSPRITE
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ DWORD Unknown0004; // id or index?
	/* 0x0008 */ DWORD Unknown0008;
	/* 0x000C */ DWORD Unknown000C;
	/* 0x0010 */ DWORD Unknown0010;
	/* 0x0014 */ PVOID Unknown0014;
	/* 0x0018 */ PCHAR Text;
	/* 0x001C */ DWORD TextLength;
	/* 0x0020 */ DWORD Unknown0020;
	/* 0x0024 */ DWORD MaxScaleFactor1; // s3dSetStringSpriteMaxScaleFactor
	/* 0x0028 */ FLOAT MaxScaleFactor2; // s3dSetStringSpriteMaxScaleFactor
	/* 0x002C */ FLOAT MaxScaleFactor3; // s3dSetStringSpriteMaxScaleFactor
	/* 0x0030 */ DWORD IsYonClipEnabled; // s3dSetStringSpriteYonClip (draw distance)
	/* 0x0034 */ DWORD YonClipDistance; // s3dSetStringSpriteYonClip (draw distance)
	/* 0x0038 */ FLOAT Unknown0038; // unknown modifier for scale
	/* 0x003C */ DWORD Width; // how wide the text is stretched
	/* 0x0040 */ DWORD Height; // how tall the text is stretched
	/* 0x0044 */ FLOAT Unknown0044; // unknown multiplier
	/* 0x0048 */ struct _EQRGBCOLOR Color; // s3dSetStringSpriteTint
										   /* ...... */
} EQSTRINGSPRITE, *PEQSTRINGSPRITE;

// model skeleton animation?
typedef struct _EQTRACKINFO
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ DWORD Unknown0004;
	/* 0x0008 */ PCHAR Name; // x_TRACK, x_POINT_TRACK, etc
							 /* ...... */
} EQTRACKINFO, *PEQTRACKINFO;

// model skeleton bones
// T3D_DAG
typedef struct _EQDAGINFO
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ PCHAR Name; // x_DAG, x_POINT_DAG, etc
	/* 0x0008 */ struct _EQSTRINGSPRITE* StringSprite;
	/* 0x000C */ struct _EQDAGINFO* Parent;
	/* 0x0010 */ struct _EQMODELINFO* ModelInfo;
	/* 0x0014 */ struct _EQTRACKINFO* Track1;
	/* 0x0018 */ struct _EQTRACKINFO* Track2;
	/* 0x001C */ BYTE Unknown001C[96];
	/* 0x007C */ FLOAT Y;
	/* 0x0080 */ FLOAT X;
	/* 0x0084 */ FLOAT Z;
	/* 0x0088 */ BYTE Unknown0088[96];
	/* 0x00E8 */ DWORD NumChildren;
	/* 0x00EC */ struct _EQDAGCHILDREN* Children;
	/* ...... */
} EQDAGINFO, *PEQDAGINFO;

typedef struct _EQDAGCHILDREN
{
	/* 0x0000 */ struct _EQDAGINFO* Child[32];
} EQDAGCHILDREN, *PEQDAGCHILDREN;

typedef struct _EQACTORCOLLISIONINFO
{
	/* 0x0000 */ DWORD CollisionVolumeType;
	/* 0x0004 */ DWORD Unknown0004;
	/* 0x0008 */ FLOAT CollisionSize;
	/* ...... */
} EQACTORCOLLISIONINFO, *PEQACTORCOLLISIONINFO;

// T3D_tagACTORINSTANCE
typedef struct _EQACTORINSTANCEINFO
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ DWORD Unknown0004;
	/* 0x0008 */ DWORD Unknown0008;
	/* 0x000C */ DWORD Unknown000C;
	/* 0x0010 */ FLOAT WorldX;
	/* 0x0014 */ FLOAT WorldY;
	/* 0x0018 */ FLOAT WorldZ;
	/* 0x001C */ DWORD Unknown001C;
	/* 0x0020 */ DWORD Unknown0020;
	/* 0x0024 */ DWORD Unknown0024;
	/* 0x0028 */ DWORD RegionNumber;
	/* 0x002C */ struct _EQACTORCOLLISIONINFO* CollisionInfo;
	/* 0x0030 */ DWORD Unknown0030;
	/* 0x0034 */ FLOAT ScaleFactor;
	/* 0x0038 */ FLOAT BoundingRadius;
	/* 0x003C */ BYTE Unknown003C[36];
	/* 0x0060 */ struct _EQSPAWNINFO* UserData;
	/* ...... */
} EQACTORINSTANCEINFO, *PEQACTORINSTANCEINFO;

typedef struct _EQMODELINFO
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ DWORD Unknown0004;
	/* 0x0008 */ DWORD Unknown0008;
	/* 0x000C */ DWORD Unknown000C;
	/* 0x0010 */ DWORD Unknown0010;
	/* 0x0014 */ PVOID Unknown0014;
	/* 0x0018 */ PVOID Unknown0018;
	/* 0x001C */ struct _EQACTORINSTANCEINFO* ActorInstance;
	/* 0x0020 */ DWORD NumDag; // includes Root
	/* 0x0024 */ struct _EQDAGINFO* DagRoot; // first dag
											 /* ...... */
} EQMODELINFO, *PEQMODELINFO;

typedef struct _EQACTORINFO
{
	/* 0x0000 */ struct _EQACTORINSTANCEINFO* ActorInstance;
	/* 0x0004 */ struct _EQLIGHTINFO* LightInfo; // PointLight
	/* 0x0008 */ char ActorDef[64]; // xxx_ACTORDEF string (HUM_ACTORDEF, ELM_ACTORDEF, etc)
	/* 0x0048 */ FLOAT Z;
	/* 0x004C */ FLOAT ZCeiling; // Z axis of the ceiling or first collision above player
	/* 0x0050 */ PVOID Unknown0050; // EqMobileEmitter*
	/* 0x0054 */ DWORD Unknown0054;
	/* 0x0058 */ DWORD UnknownTimer1;
	/* 0x005C */ DWORD UnknownTimer2;
	/* 0x0060 */ DWORD UnknownTimer3;
	/* 0x0064 */ DWORD UnknownTimer4;
	/* 0x0068 */ DWORD Unknown0068;
	/* 0x006C */ DWORD Unknown006C;
	/* 0x0070 */ DWORD Unknown0070;
	/* 0x0074 */ DWORD UnknownTimer5;
	/* 0x0078 */ DWORD UnknownTimer6;
	/* 0x007C */ DWORD UnknownTimer7;
	/* 0x0080 */ WORD LevitationMovementCounter; // loops from 0 to 512 while levitating, causes up/down movement, 0xFFFF = Not Levitating
	/* 0x0082 */ WORD DrunkMovementCounter; // loops from 0 to 512 while drunk, causes left/right movement, 0xFFFF = Not Drunk
	/* 0x0084 */ WORD Unknown0084;
	/* 0x0086 */ WORD Unknown0086;
	/* 0x0088 */ FLOAT DrunkMovementModifier; // how far left/right the player moves while drunk
	/* 0x008C */ FLOAT LevitationMovementModifier; // how far up/down the player moves while levitating
	/* 0x0090 */ BYTE IsAffectedByGravity; // gravity is enabled for the player (disabled while levitating)
	/* 0x0091 */ BYTE Unknown0091; // equals 0, 11 or 13
	/* 0x0092 */ BYTE Unknown0092;
	/* 0x0093 */ BYTE Unknown0093;
	/* 0x0094 */ PVOID Unknown0094; // pointer, static address 0x006EC6E8 has same value
	/* 0x0098 */ PVOID Unknown0098; // pointer, static address 0x006EC6E8 has same value
	/* 0x009C */ PVOID Unknown009C; // pointer, static address 0x006EC6E8 has same value
	/* 0x00A0 */ BYTE IsSwimmingUnderwater;
	/* 0x00A1 */ BYTE SwimmingWaterType; // 5,6,9,10 = Water, 7 = Lava, 8 = Freezing Water (7 and 8 cause damage!)
	/* 0x00A2 */ BYTE SwimmingFeetTouchingWater; // 0 = False, 5 = True
	/* 0x00A3 */ BYTE SwimmingUnknown1; // 0 = False, 5 = True
	/* 0x00A4 */ BYTE SwimmingUnknown2;
	/* 0x00A5 */ BYTE SwimmingUnknown3;
	/* 0x00A6 */ BYTE SwimmingUnknown4;
	/* 0x00A7 */ BYTE SwimmingUnknown5;
	/* 0x00A8 */ FLOAT MovementFriction1; // used for sliding on ice or slippery surfaces (Default = 0.625)
	/* 0x00AC */ FLOAT MovementFriction2; // used for sliding on ice or slippery surfaces (Default = 0.8000000119)
	/* 0x00B0 */ FLOAT JumpHeightModifier; // how high the player jumps (Default = 1.350000024)
	/* 0x00B4 */ FLOAT Unknown00B4;
	/* 0x00B8 */ FLOAT Unknown00B8;
	/* 0x00BC */ FLOAT MovementSpeedModifier; // how much slower/faster you move
	/* 0x00C0 */ BYTE Unknown00C0[196];
	/* 0x0184 */ DWORD Animation;
	/* 0x0188 */ BYTE Unknown0188[44];
	/* 0x01B4 */ DWORD IsInvisible; // NPCs only? used by /hidecorpses command
	/* 0x01B8 */ BYTE Unknown01B8[168];
	/* 0x0260 */ DWORD IsHoldingBoth;
	/* 0x0264 */ DWORD IsHoldingSecondary;
	/* 0x0268 */ DWORD IsHoldingPrimary;
	/* 0x026C */ BYTE Unknown026C[4];
	/* 0x0270 */ BYTE Unknown0270[4];
	/* 0x0274 */ BYTE Unknown0274[4];
	/* 0x0278 */ BYTE Unknown0278[4];
	/* 0x027C */ WORD CastingSpellId;
	/* 0x027E */ BYTE CastingSpellGemNumber; // 255 = Bard Singing
	/* 0x027F */ BYTE Unknown027F;
	/* 0x0280 */ BYTE Unknown0280[4];
	/* 0x0284 */ struct _EQMODELINFO* ModelInfo;
	/* 0x0288 */ struct _EQDAGINFO* DagHeadPoint;
	/* 0x028C */ struct _EQDAGINFO* DagHead;
	/* 0x0290 */ struct _EQDAGINFO* DagUnknown;
	/* 0x0294 */ struct _EQDAGINFO* DagRightPoint;
	/* 0x0298 */ struct _EQDAGINFO* DagLeftPoint;
	/* 0x029C */ struct _EQDAGINFO* DagShieldPoint;
	/* 0x02A0 */ BYTE Unknown02A0[128];
	/* 0x0320 */ BYTE MovementType; // 0 = None, 4 = Walking, 6 = Running, 7 = Swimming
	/* 0x0321 */ BYTE Unknown0321[12];
	/* 0x032D */ BYTE IsMovingTimer; // 0 = Moving, 1-6 = Recently Stopped Moving, 200 = Not Moving
	/* 0x032E */ BYTE Unknown032E[266];
	/* 0x0438 */ DWORD IsLookingForGroup;
	/* 0x043C */ DWORD IsTrader;
	/* ...... */
} EQACTORINFO, *PEQACTORINFO;

// sizeof 0x168
typedef struct _EQSPAWNINFO
{
	/* 0x0000 */ BYTE Unknown0000; // always equals 0x03
	/* 0x0001 */ CHAR Name[30]; // [0x1E]
	/* 0x001F */ BYTE Unknown001F[37];
	/* 0x0044 */ DWORD ZoneId; // EQ_ZONE_ID_x
	/* 0x0048 */ FLOAT Y;
	/* 0x004C */ FLOAT X;
	/* 0x0050 */ FLOAT Z;
	/* 0x0054 */ FLOAT Heading; // camera view left/right, yaw
	/* 0x0058 */ FLOAT Unknown0058;
	/* 0x005C */ FLOAT MovementSpeed;
	/* 0x0060 */ FLOAT MovementSpeedY;
	/* 0x0064 */ FLOAT MovementSpeedX;
	/* 0x0068 */ FLOAT MovementSpeedZ;
	/* 0x006C */ FLOAT MovementSpeedHeading;
	/* 0x0070 */ FLOAT Unknown0070;
	/* 0x0074 */ FLOAT Pitch; // camera view up/down
	/* 0x0078 */ struct _EQSPAWNINFO* Prev;
	/* 0x007C */ struct _EQSPAWNINFO* Next;
	/* 0x0080 */ PVOID Unknown0080;
	/* 0x0084 */ struct _EQACTORINFO* ActorInfo;
	/* 0x0088 */ struct _EQCHARINFO* CharInfo;
	/* 0x008C */ FLOAT CameraHeightOffset;
	/* 0x0090 */ FLOAT ModelHeightOffset;
	/* 0x0094 */ WORD SpawnId;
	/* 0x0096 */ WORD PetOwnerSpawnId; // spawn id of the owner of this pet spawn
	/* 0x0098 */ DWORD HpMax;
	/* 0x009C */ DWORD HpCurrent;
	/* 0x00A0 */ WORD GuildId;
	/* 0x00A2 */ BYTE Unknown00A2[6];
	/* 0x00A8 */ BYTE Type; // EQ_SPAWN_TYPE_x
	/* 0x00A9 */ BYTE Class; // EQ_CLASS_x
	/* 0x00AA */ WORD Race;  // EQ_RACE_x
	/* 0x00AC */ BYTE Gender; // EQ_GENDER_x
	/* 0x00AD */ BYTE Level;
	/* 0x00AE */ BYTE IsHidden; // 0 = Visible, 1 = Invisible
	/* 0x00AF */ BYTE IsSneaking; // sneaking or snared ; 0 = Normal Movement Speed, 1 = Slow Movement Speed
	/* 0x00B0 */ BYTE IsPlayerKill; // PVP flagged with red name by Priest of Discord
	/* 0x00B1 */ BYTE StandingState; // EQ_STANDING_STATE_x
	/* 0x00B2 */ BYTE LightType; // EQ_LIGHT_TYPE_x
	/* 0x00B3 */ BYTE Unknown00B3;
	/* 0x00B4 */ WORD EquipmentMaterialType[7]; // EQ_EQUIPMENT_MATERIAL_TYPE_x ; Head,Chest,Arms,Wrist,Hands,Legs,Feet
	/* 0x00C2 */ WORD EquipmentPrimaryItemType; // EQ_EQUIPMENT_ITEM_TYPE_x ; Primary
	/* 0x00C4 */ WORD EquipmentSecondaryItemType; // EQ_EQUIPMENT_ITEM_TYPE_x ; Secondary
	/* 0x00C6 */ WORD Unknown00C6;
	/* 0x00C8 */ BYTE Unknown00C8[36];
	/* 0x00EC */ DWORD Unknown00EC;
	/* 0x00F0 */ FLOAT Height; // model height or size/scale (shrink, grow, etc)
	/* 0x00F4 */ FLOAT Unknown00F4;
	/* 0x00F8 */ FLOAT Unknown00F8;
	/* 0x00FC */ FLOAT Unknown00FC;
	/* 0x0100 */ FLOAT MovementBackwardSpeedMultiplier; // modifies how fast you move backwards (Default = 0.4600000083)
	/* 0x0104 */ FLOAT MovementForwardSpeedMultiplier; // modifies how fast you move forwards (Default = 0.6999999881)
	/* 0x0108 */ BYTE IsLinkDead; // LD
	/* 0x0109 */ BYTE IsGameMaster; // GM
	/* 0x010A */ WORD LevitationState; // EQ_LEVITATION_STATE_x
	/* 0x010C */ DWORD TargetType; // EQ_SPAWN_TARGET_TYPE_x
	/* 0x0110 */ DWORD Unknown0110;
	/* 0x0114 */ DWORD AnonymousState; // EQ_ANONYMOUS_STATE_x, /anonymous and /roleplay
	/* 0x0118 */ DWORD Unknown0118;
	/* 0x011C */ DWORD IsAwayFromKeyboard; // AFK
	/* 0x0120 */ BYTE Unknown0120[4];
	/* 0x0124 */ DWORD AlternateAdvancementRank; // AA points title value (0-3) (Venerable, Baroness, etc)
	/* 0x0128 */ BYTE Unknown0128[4];
	/* 0x012C */ CHAR LastName[22]; // surname or title
	/* 0x0142 */ BYTE Unknown0142[10];
	/* 0x014C */ WORD GuildStatus; // guild rank
	/* 0x014E */ WORD Deity; // EQ_DEITY_x
	/* 0x0150 */ BYTE Unknown0150;
	/* 0x0151 */ BYTE Unknown0151[6];
	/* 0x0157 */ BYTE Unknown0157[5];
	/* 0x015C */ DWORD Unknown015C;
	/* 0x0160 */ DWORD Unknown0160;
	/* 0x0164 */ DWORD Unknown0164;
	/* 0x0168 */
} EQSPAWNINFO, *PEQSPAWNINFO;

typedef struct _EQGROUNDSPAWNINFO
{
	/* 0x0000 */ struct _EQGROUNDSPAWNINFO* Prev;
	/* 0x0004 */ struct _EQGROUNDSPAWNINFO* Next;
	/* 0x0008 */ WORD Id;
	/* 0x000A */ BYTE Unknown000A[2];
	/* 0x000C */ WORD DropId;
	/* 0x000E */ BYTE Unknown000E[2];
	/* 0x0010 */ WORD Unknown0010;
	/* 0x0012 */ BYTE Unknown0012[2];
	/* 0x0014 */ DWORD Unknown0014; // pointer
	/* 0x0018 */ BYTE Unknown0018[116];
	/* 0x008C */ FLOAT Heading;
	/* 0x0090 */ FLOAT Z;
	/* 0x0094 */ FLOAT X;
	/* 0x0098 */ FLOAT Y;
	/* 0x009C */ CHAR Name[30];
	/* ...... */
} EQGROUNDSPAWNINFO, *PEQGROUNDSPAWNINFO;

typedef struct _EQDOORSPAWNINFO
{
	/* 0x0000 */ BYTE Unknown0000[4];
	/* 0x0004 */ struct _EQDOORSPAWNINFO* Prev;
	/* 0x0008 */ struct _EQDOORSPAWNINFO* Next;
	/* 0x000C */ BYTE Unknown000C;
	/* 0x000D */ CHAR Name[11];
	/* 0x0018 */ DWORD Unknown0018;
	/* 0x001C */ BYTE Unknown001C[4];
	/* 0x0020 */ FLOAT DefaultY;
	/* 0x0024 */ FLOAT DefaultX;
	/* 0x0028 */ FLOAT DefaultZ;
	/* 0x002C */ FLOAT DefaultHeading;
	/* 0x0030 */ FLOAT Angle;
	/* 0x0034 */ FLOAT Y;
	/* 0x0038 */ FLOAT X;
	/* 0x003C */ FLOAT Z;
	/* 0x0040 */ FLOAT Heading;
	/* ...... */
} EQDOORSPAWNINFO, *PEQDOORSPAWNINFO;

typedef struct _EQGROUPLIST
{
	struct _EQSPAWNINFO* GroupMember[EQ_NUM_GROUP_MEMBERS];
} EQGROUPLIST, *PEQGROUPLIST;

// sizeof 0x96
typedef struct _EQGUILDINFO
{
	/* 0x0000 */ CHAR Name[32];
	/* 0x0032 */ BYTE Unknown0032[64];
} EQGUILDINFO, *PEQGUILDINFO;

typedef struct _EQGUILDLIST
{
	struct _EQGUILDINFO Guild[EQ_NUM_GUILDS];
} EQGUILDLIST, *PEQGUILDLIST;

// sizeof 0x14
typedef struct _EQCOMMANDINFO
{
	/* 0x0000 */ DWORD Id;
	/* 0x0004 */ PCHAR Name;
	/* 0x0008 */ PCHAR Name2;
	union
	{
		/* 0x000C */ VOID(__stdcall* Function)(PEQSPAWNINFO, PCHAR);
		/* 0x000C */ DWORD FunctionAddress;
	};
	/* 0x0010 */ WORD Restriction;
	/* 0x0012 */ WORD Category;
} EQCOMMANDINFO, *PEQCOMMANDINFO;

typedef struct _EQCOMMANDLIST
{
	struct _EQCOMMANDINFO Command[EQ_NUM_COMMANDS];
} EQCOMMANDLIST, *PEQCOMMANDLIST;

typedef struct _EQHOTBUTTONINFO
{
	/* 0x0000 */ BYTE Type1;
	/* 0x0001 */ BYTE Unknown0001;
	/* 0x0002 */ BYTE Type2;
	/* 0x0003 */ BYTE Unknown0003;
} EQHOTBUTTONINFO, *PEQHOTBUTTONINFO;

typedef struct _EQHOTBUTTONLIST
{
	struct _EQHOTBUTTONINFO HotButton[EQ_NUM_HOTBUTTONS_TOTAL];
} EQHOTBUTTONLIST, *PEQHOTBUTTONLIST;

// /viewport
typedef struct _EQVIEWPORT
{
	/* 0x0000 */ WORD X1;
	/* 0x0002 */ WORD Y1;
	/* 0x0004 */ WORD X2;
	/* 0x0006 */ WORD Y2;
} EQVIEWPORT, *PEQVIEWPORT;

typedef struct _EQCEVERQUEST
{
	/* 0x0000 */ BYTE Unknown0000[1448];
	
	/* 0x05A9 */ DWORD WorldAuth;
	/* 0x05AC */ DWORD GameState; // EQ_GAME_STATE_x
} EQCEVERQUEST, *PEQEVERQUEST;

typedef struct _EQCXWNDMANGER
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ DWORD WindowList;
	/* 0x0008 */ DWORD Unknown0008;
	/* 0x000C */ DWORD Unknown000C;
	/* 0x0010 */ DWORD Unknown0010;
	/* 0x0014 */ DWORD LastPressedKeyCode;
	/* 0x0018 */ DWORD LastKeyboardMouseInputTimer;
	/* 0x001C */ DWORD Unknown001C;
	/* 0x0020 */ DWORD Unknown0020;
	/* 0x0024 */ DWORD Unknown0024;
	/* 0x0028 */ DWORD Unknown0028;
	/* 0x002C */ DWORD Unknown002C;
	/* 0x0030 */ DWORD FocusedWindow; // maybe last clicked window
	/* 0x0034 */ DWORD DraggedWindow; // mouse dragging
	/* 0x0038 */ DWORD Unknown0038;
	/* 0x003C */ DWORD HoveredWindow; // mouse hover over
	/* 0x0040 */ DWORD Unknown0040;
	/* 0x0044 */ DWORD Unknown0044;
	/* 0x0048 */ DWORD Unknown0048;
	/* 0x004C */ DWORD MouseX;
	/* 0x0050 */ DWORD MouseY;
	/* 0x0054 */ DWORD KeyboardModifierKeyFlags; // CTRL, SHIFT and ALT
	/* 0x0058 */ DWORD Unknown0058;
	/* 0x005C */ DWORD MouseIcon;
	/* 0x0060 */ DWORD Unknown0060;
	/* 0x0064 */ DWORD TitleBarClickedX; // window titlebar
	/* 0x0068 */ DWORD TitleBarClickedY; // window titlebar
										 /* ...... */
} EQCXWNDMANGER, *PEQCXWNDMANGER;

typedef struct _EQCXRECT
{
	DWORD X1;
	DWORD Y1;
	DWORD X2;
	DWORD Y2;
} EQCXRECT, *PEQCXRECT;

typedef struct _EQCXSTR
{
	/* 0x0000*/ DWORD Font; // 1,6 = Window Title or Button Text, 8 = Hot Button Small Text
	/* 0x0004*/ DWORD MaxLength;
	/* 0x0008*/ DWORD Length;
	/* 0x000C*/ DWORD Encoding; // 0 = ASCII, 1 = Unicode
	/* 0x0010*/ PCRITICAL_SECTION Lock;
	/* 0x0014*/ CHAR Text[1]; // use Length and MaxLength
} EQCXSTR, *PEQCXSTR;

// CXWnd and CSidlScreenWnd share these same properties
// sizeof 0xAC
typedef struct _EQWND
{
	/* 0x0000 */ DWORD Unknown0000; // struct _CSIDLWNDVFTABLE *pvfTable; struct _CXWNDVFTABLE *pvfTable;
	/* 0x0004 */ DWORD MouseHoverTimer;
	/* 0x0008 */ DWORD Unknown0008; // usually equals 2000
	/* 0x000C */ DWORD Unknown000C; // usually equals 500
	/* 0x0010 */ BYTE Unknown0010;
	/* 0x0011 */ BYTE Unknown0011;
	/* 0x0012 */ BYTE IsLocked;
	/* 0x0013 */ BYTE Unknown0013;
	/* 0x0014 */ PVOID Unknown0014;
	/* 0x0018 */ DWORD Unknown0018;
	/* 0x001C */ struct _EQWND* ParentWnd;
	/* 0x0020 */ struct _EQWND* FirstChildWnd;
	/* 0x0024 */ struct _EQWND* NextSiblingWnd;
	/* 0x0028 */ BYTE HasChildren;
	/* 0x0029 */ BYTE HasSiblings;
	/* 0x002A */ BYTE Unknown0030[2];
	/* 0x002C */ DWORD Flags;
	/* 0x0030 */ struct _EQCXRECT Location;
	/* 0x0040 */ struct _EQCXRECT LocationPlaceholder; // used when minimizing the window
	/* 0x0050 */ BYTE IsVisible; // show
	/* 0x0051 */ BYTE IsEnabled;
	/* 0x0052 */ BYTE IsMinimized;
	/* 0x0053 */ BYTE Unknown0053;
	/* 0x0054 */ BYTE IsOpen;
	/* 0x0055 */ BYTE Unknown0055;
	/* 0x0056 */ BYTE IsMouseOver; // mouse is hovering over
	/* 0x0057 */ BYTE Unknown0057;
	/* 0x0058 */ DWORD WindowStyleFlags;
	/* 0x005C */ struct _EQFONT* FontPointer;
	/* 0x0060 */ PEQCXSTR Text;
	/* 0x0064 */ PEQCXSTR ToolTipText;
	/* 0x0068 */ BYTE Unknown0068[28];
	/* 0x0084 */ PEQCXSTR XmlToolTipText;
	/* 0x0088 */ BYTE Unknown0088[22];
	/* 0x009E */ BYTE AlphaTransparency;
	/* 0x009F */ BYTE Unknown009F;
	/* 0x00A0 */ BYTE ZLayer;
	/* 0x00A1 */ BYTE Unknown00A1[7];
	/* 0x00A8 */ DWORD DrawTemplate;
	/* 0x00AC */
} EQWND, *PEQWND;

// the moveable resizable parent windows
// class CSidlScreenWnd
// sizeof 0x138
typedef struct _EQCSIDLWND
{
	/* 0x0000 */ struct _EQWND EQWnd;
	/* 0x00AC */ BYTE Unknown00AC[140]; // skips the rest
										/* 0x0138 */
} EQCSIDLWND, *PEQCSIDLWND;

// usually a child window like a button or label
// sizeof 0x138
typedef struct _EQCXWND
{
	/* 0x0000 */ struct _EQWND EQWnd;
	/* 0x00AC */ BYTE Unknown00AC[140]; // skips the rest
										/* 0x0138 */
} EQCXWND, *PEQCXWND;

typedef struct _EQCITEMDISPLAYWND
{
	/* 0x0000 */ struct _EQCSIDLWND CSidlWnd;
	/* 0x0138 */ BYTE Unknown0138[4];
	/* 0x013C */ struct _EQCSIDLWND* DisplayWnd; // the item stats text window
	/* 0x0140 */ BYTE Unknown0140[4];
	/* 0x0144 */ PEQCXSTR DisplayText; // the item name is the title text
	/* 0x0148 */ PEQCXSTR WindowTitle; // the item stats text
	/* 0x014C */ struct _EQITEMINFO Item;
	/* ...... */
} EQCITEMDISPLAYWND, *PEQCITEMDISPLAYWND;

typedef struct _EQCBUFFWINDOW
{
	/* 0x0000 */ struct _EQCSIDLWND CSidlWnd;
	/* 0x0138 */ BYTE Unknown0138[68];
	/* 0x017C */ struct _EQCSIDLWND* BuffButtonWnd[EQ_NUM_BUFFS]; // CButtonWnd
																  /* 0x01B8 */
																  /* ...... */
} EQCBUFFWINDOW, *PEQCBUFFWINDOW;

typedef struct _EQCLOOTWND
{
	/* 0x0000 */ struct _EQCSIDLWND CSidlWnd;
	/* 0x0138 */ DWORD ItemSlotIndex[EQ_NUM_LOOT_WINDOW_ITEMS];
	/* 0x01B0 */ DWORD Timer;
	/* 0x01B4 */ PVOID Unknown01B4;
	/* 0x01B8 */ struct _EQITEMINFO* Item[EQ_NUM_LOOT_WINDOW_ITEMS];
	/* ...... */
} EQCLOOTWND, *PEQCLOOTWND;

typedef struct _EQCSPELLBOOKWND
{
	/* 0x0000 */ struct _EQCSIDLWND CSidlWnd;
	/* 0x0138 */ DWORD ItemSlotIndex[EQ_NUM_LOOT_WINDOW_ITEMS];
	/* 0x01B0 */ DWORD Timer;
	/* 0x01B4 */ PVOID Unknown01B4;
	/* 0x01B8 */ struct _EQITEMINFO* Item[EQ_NUM_LOOT_WINDOW_ITEMS];
	/* ...... */
} EQCSPELLBOOKWND, * PEQSPELLBOOKWND;

typedef struct _EQCINVSLOT
{
	/* 0x0000 */ DWORD Unknown0000;
	/* 0x0004 */ DWORD Unknown0004;
	/* 0x0008 */ DWORD Unknown0008;
	/* 0x000C */ DWORD SlotId;
	/* ...... */
} EQCINVSLOT, *PEQCINVSLOT;

#endif // EQMAC_H
