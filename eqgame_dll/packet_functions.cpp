#include "eqgame.h"
#include <memory.h>
#include <iostream>
#include <string>

/*#include "..\zlib_x86\include\zlib.h"

voidpf eqemu_alloc_func(voidpf opaque, uInt items, uInt size) {
	voidpf tmp = new char[items*size];
	return(tmp);
}

void eqemu_free_func(voidpf opaque, voidpf address) {
	delete[](char *)address;
}

int DeflatePacket(const unsigned char* in_data, int in_length, unsigned char* out_data, int max_out_length) {
	if (in_data == nullptr) {
		return(0);
	}

	z_stream zstream;
	memset(&zstream, 0, sizeof(zstream));
	int zerror;

	zstream.next_in = const_cast<unsigned char *>(in_data);
	zstream.avail_in = in_length;
	zstream.zalloc = eqemu_alloc_func;
	zstream.zfree = eqemu_free_func;
	zstream.opaque = Z_NULL;
	deflateInit(&zstream, Z_FINISH);
	zstream.next_out = out_data;
	zstream.avail_out = max_out_length;
	zerror = deflate(&zstream, Z_FINISH);

	if (zerror == Z_STREAM_END)
	{
		deflateEnd(&zstream);
		return zstream.total_out;
	}
	else
	{
		zerror = deflateEnd(&zstream);
		return 0;
	}
}

unsigned int InflatePacket(const unsigned char* indata, unsigned int indatalen, unsigned char* outdata, unsigned int outdatalen, bool iQuiet) {

	if (indata == nullptr)
		return(0);

	z_stream zstream;
	int zerror = 0;
	int i;

	zstream.next_in = const_cast<unsigned char *>(indata);
	zstream.avail_in = indatalen;
	zstream.next_out = outdata;
	zstream.avail_out = outdatalen;
	zstream.zalloc = eqemu_alloc_func;
	zstream.zfree = eqemu_free_func;
	zstream.opaque = Z_NULL;

	i = inflateInit2(&zstream, 15);
	if (i != Z_OK) {
		return 0;
	}

	zerror = inflate(&zstream, Z_FINISH);

	if (zerror == Z_STREAM_END) {
		inflateEnd(&zstream);
		return zstream.total_out;
	}
	else {
		if (!iQuiet) {
			std::cout << "Error: InflatePacket: inflate() returned " << zerror << " '";
			if (zstream.msg)
				std::cout << zstream.msg;
			std::cout << "'" << std::endl;
		}

		if (zerror == -4 && zstream.msg == 0)
		{
			return 0;
		}

		zerror = inflateEnd(&zstream);
		return 0;
	}
}*/