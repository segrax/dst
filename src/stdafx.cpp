#include "stdafx.h"

word	readWord( const void *buffer ) {
	const byte *byteNext = (const byte *) buffer;
	return (byteNext[0] << 8) + byteNext[1];
}

word	swapWord(  word buffer ) {
	const byte *byteNext = (const byte *) &buffer;
	return (byteNext[0] << 8) + byteNext[1];
}

dword	readDWord( const void *buffer ) {
	const byte *dwordNext = (const byte *) buffer;
    return (dwordNext[0] << 24) + (dwordNext[1] << 16) + (dwordNext[2] << 8) + (dwordNext[3]);
}

dword	swapDWord( dword buffer ) {
	const word *DW = (word*) &buffer;

	return (DW[0] << 16) + (DW[1]);
}
