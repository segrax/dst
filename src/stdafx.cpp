/* DST  -  Dune 2 Script Tools
 *  
 * Copyright (C) 2009 segra
 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  
 * 
 * $Id$
 * 
 */

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
