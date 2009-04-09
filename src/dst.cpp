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
#include "scriptHandler.h"
#include "scriptHandlerDecompiler.h"
#include "scriptHandlerCompiler.h"

using namespace script;

int main( int argc, char *argv[]) {
	bool result = false;
	cout << "Dune II Script Tools v" << version << endl << endl;

	if(argc < 3) {
		cout << "Usage:" << endl;
		cout << "d: Decompile" << endl;
		cout << "c: Compile" << endl;
		cout << "dst d script.emc" << endl;
		cout << "dst c script.txt" << endl;
		return 0;
	}

	if( tolower(*argv[1]) == 'd' ) {
		_scriptHandlerDecompiler script( argv[2] );
		result = script.decompile( );

	} else if( tolower(*argv[1]) == 'c' ) {
		_scriptHandlerCompiler script( argv[2] );
		result = script.compile( );
	}

	cout << endl;

	if( !result )
			cout << "Failed" << endl;
		else
			cout << "Done" << endl;
}
