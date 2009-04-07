
#include "stdafx.h"
#include "scriptHandler.h"
#include "scriptHandlerDecompiler.h"

namespace script {

	_scriptHandlerDecompiler::_scriptHandlerDecompiler( const char *fileName ) : _scriptHandler(fileName) {

		_scriptLastPush = 0;
		_opcodesExecute = 0;

		opcodesSetup();
	}

	_scriptHandlerDecompiler::~_scriptHandlerDecompiler() {
		
	}

	bool _scriptHandlerDecompiler::scriptLoad() {
		ifstream		 fileScript;
		size_t			 scriptSize;


		fileScript.open( _fileName, ios::in | ios::binary );

		if( fileScript.is_open() == false )
			return false;

		// Read File Size
		fileScript.seekg( 0, ios::end );
		scriptSize = fileScript.tellg();
		fileScript.seekg( ios::beg );

		// Load file into _scriptBuffer
		_scriptBuffer = new byte[ scriptSize ];
		if( fileScript.read( (char*) _scriptBuffer, scriptSize ) == false)
			return false;
		
		fileScript.close();

		return true;
	}

	bool _scriptHandlerDecompiler::headerRead() {
		word		*buffer = (word*) (_scriptBuffer + 0x12);
		size_t		 ptrCount;

		// Number of script functions
		_pointerCount = readWord( buffer ) / 2;
		buffer++;

		_headerPointers = new word[_pointerCount];

		for(ptrCount = 0; ptrCount < _pointerCount; ptrCount++) {
			_headerPointers[ptrCount] = readWord( buffer );
			buffer++;
		}

		// Skip 'DATA' tag
		buffer += 2;	// 2 Words

		// Not sure if this word is actually part of a DWORD, or 2 useless bytes?
		buffer++;

		// Size of the upcoming script data
		_scriptSize = readWord( buffer );
		buffer++;

		// Start of script data
		_scriptStart = (byte*) buffer;

		if(_pointerCount == 0x06) {
			cout << "[House]" << endl;
			_scriptType		 = _scriptHOUSE;
			_objectNames	 = nameHouses;
			opcodesHousesSetup();
		}

		if(_pointerCount == 0x13) {
			cout << "[Build]" << endl;
			_scriptType		 = _scriptBUILD;
			_objectNames	 = nameStructures;
			opcodesBuildingsSetup();
		}

		if(_pointerCount == 0x1B) {
			cout << "[Unit]" << endl;
			_scriptType		 = _scriptUNIT;
			_objectNames	 = nameUnits;
			opcodesUnitsSetup();
		}

		return true;
	}

	bool _scriptHandlerDecompiler::scriptNextStart( ) {
		bool found = false;

		// Loop through each pointer and write the section names out
		for( int count = 0; count <= _pointerCount; count++ ) {

			// In TEAM.EMC for example, two objects use the same script
			if( _scriptPos == (word) _headerPointers[count]) {
				if(found==false)
					cout << endl;

				// Write the section name in square brackets
				cout << "[" << _objectNames[count] << "]" << endl;
				found = true;
			}
		}

		return found;
	}

	bool _scriptHandlerDecompiler::decompile() {
		
		// Load the script into a _scriptBuffer, then read the header information
		scriptLoad();
		headerRead();

		// Map out all labels
		_modePreProcess = true;
		if(scriptDecompile() == false)
			return false;

		// Decompile the script 
		_modePreProcess = false;

		return scriptDecompile();
	}

	bool _scriptHandlerDecompiler::scriptDecompile( ) {
		_opcodeCurrent  = 0;
		_scriptData		= _scriptDataNext = 0;
		_scriptPtr		= 0;
		_scriptPtrEnd	= 0;
		_scriptPos		= 0;
		_stackCount		= 0xF;

		_scriptPos		= 0;
		_scriptPtr		= (word*)  _scriptStart;
		_scriptPtrEnd	= (word*) (_scriptStart + _scriptSize);

		output( "[General]" );

		while( _scriptPtr <  _scriptPtrEnd ) {

			if( !_modePreProcess ) {
				scriptNextStart();

				// Check if label location, print label if so
				if( scriptLabel( _scriptPos ) > -1)
					cout << "l" << _scriptPos << ":" << endl;
			}

			_scriptDataNext = 0;
			_scriptData		= readWord( _scriptPtr );
			_scriptPtr++;
			_scriptPos++;

			// Keep the opcode
			_opcodeCurrent = _scriptData >> 8;
			_opcodeCurrent &= 0x1F;
			
			if( _scriptData & 0x8000 ) {
				// Opcode uses 14 bits
				_opcodeCurrent = 0;
				_scriptData &= 0x7FFF;
			} else
				// Opcode only requires 1 byte
				if( _scriptData & 0x4000 ) {
					_scriptData &= 0xFF;
			} else 	
				// Opcode uses the next WORD, grab it
				if( _scriptData & 0x2000 ) {
					_scriptDataNext = readWord( _scriptPtr );
					_scriptPtr++;
					_scriptPos++;
				}
			

			// Print opcode
			if( !_modePreProcess )
				cout << setw(20) << left << _opcodes[ _opcodeCurrent ].description;

			// Excute opcode
			(this->*_opcodes[ _opcodeCurrent ].function)( );

			//cout  << setw(20) << " ";
			//cout  << hex << uppercase << "S: 0x" << _stackCount << endl;
			if( !_modePreProcess )
				cout << endl;
		}

		return true;
	}

}
