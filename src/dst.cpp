/*  DST  -  Dune 2 Script Tools
 *  

 *  
 * 
 *	 $Id$
 * 
 */

#include "stdafx.h"
#include "scriptHandler.h"
#include "scriptHandlerDecompiler.h"
#include "scriptHandlerCompiler.h"


using namespace script;

int main( int argc, char *argv[]) {

	if(argc < 3) {
		cout << "usage:" << endl;
		cout << "d: decompile" << endl;
		cout << "c: compile" << endl;
		cout << "dst.exe d script.emc" << endl;
		return 2;
	}

	if( tolower(*argv[1]) == 'd' ) {
		_scriptHandlerDecompiler script( argv[2] );

		if( script.decompile( ) == false)
			cout << "Failed!";

	} else if( tolower(*argv[1]) == 'c' ) {
		_scriptHandlerCompiler script( argv[2] );

		if( script.compile( ) == false)
			cout << "Failed!";
	}
}
