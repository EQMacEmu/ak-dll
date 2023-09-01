//#include "..\zlib_x86\include\zlib.h"

#ifndef PACKET_FUNCTIONS_H
#define PACKET_FUNCTIONS_H


struct Merchant_DelItem_Struct
{
	/*000*/	unsigned short	npcid;			// Merchant NPC's entity id
	/*002*/	unsigned short	playerid;		// Player's entity id
	/*004*/	unsigned char	itemslot;       // Slot of the item you want to remove
	/*005*/	unsigned char	type;     // 0x40
							  /*006*/
};
/*
voidpf eqemu_alloc_func(voidpf opaque, uInt items, uInt size);
void eqemu_free_func(voidpf opaque, voidpf address);



int DeflatePacket(const unsigned char* in_data, int in_length, unsigned char* out_data, int max_out_length);
unsigned int InflatePacket(const unsigned char* indata, unsigned int indatalen, unsigned char* outdata, unsigned int outdatalen, bool iQuiet = false);
*/
#endif
