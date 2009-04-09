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
#include "scriptHandlerCompiler.h"

namespace script {

	void	_scriptHandlerCompiler::o_goto(   ) {
		int labelPos = scriptLabelGet( _currentLine );
		int bb = 0;

		if(!_modePreProcess && labelPos == -1)
			*( (byte*) bb) = 01;

		*(_scriptPtr) |= 0x80;
		*(_scriptPtr) |= swapWord(labelPos);

	}

	void	_scriptHandlerCompiler::o_setreturn(   ) {
		//*(_scriptPtr) |= 0x40;

	}

	void	_scriptHandlerCompiler::o_push(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_pusharg(   ) {
		*(_scriptPtr) |= 0x20;
		*(_scriptPtr+1) |= swapWord(atoi(_currentLine.c_str()));
		_scriptPtr++;
		_scriptPos++;
	}

	void	_scriptHandlerCompiler::o_pushval(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_pushreg(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_pushframeMinArg(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_pushframePluArg(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_popret(   ) {
		*(_scriptPtr) |= 0x40;

		if(_currentLine == "(Return)")
			_currentLine = "1";
		else {
			_currentLine = "0";
		}

		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_popreg(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_popframeMinArg(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_popframePluArg(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_spadd(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_spsub(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_execute(   ) {
		word opcode = 0;
		*(_scriptPtr) |= 0x40;

		opcode = scriptOpcodeFind( _currentLine, _opcodesExecute );
		
		*(_scriptPtr) |= swapWord(opcode);
		
		(this->*_opcodesExecute[ opcode ].function)( );
	}

	void	_scriptHandlerCompiler::o_ifnotgoto(   ) {
		int labelPos = scriptLabelGet( _currentLine );
		int line = 0;

		*(_scriptPtr) |= 0x20;

		line = labelPos;

		line |= 0x8000;

		*(_scriptPtr+1) = swapWord(line);

		_scriptPtr++;
		_scriptPos++;
	}

	void	_scriptHandlerCompiler::o_negate(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));
	}

	void	_scriptHandlerCompiler::o_evaluate(   ) {
		word opcode = 0;
		*(_scriptPtr) |= 0x40;

		opcode = scriptOpcodeFind( _currentLine, _opcodesEvaluate );
		
		*(_scriptPtr) |= swapWord(opcode);
	}

	void	_scriptHandlerCompiler::o_return(   ) {

	}


	// Evaluate Operators
	void	_scriptHandlerCompiler::o_evaluate_IfEither( 	) {
		
	}

	void	_scriptHandlerCompiler::o_evaluate_Equal(   ) {

	}

	void	_scriptHandlerCompiler::o_evaluate_NotEqual(   ) {

	}

	void	_scriptHandlerCompiler::o_evaluate_CompareGreaterEqual(   ) {

	}

	void	_scriptHandlerCompiler::o_evaluate_CompareGreater(   ) {

	}

	void	_scriptHandlerCompiler::o_evaluate_CompareLessEqual(   ) {

	}
	void	_scriptHandlerCompiler::o_evaluate_CompareLess(   ) {

	}
	void	_scriptHandlerCompiler::o_evaluate_Add(   ) {

	}
	void	_scriptHandlerCompiler::o_evaluate_Subtract(   ) {

	}
	void	_scriptHandlerCompiler::o_evaluate_Multiply(   ) {

	}

	void	_scriptHandlerCompiler::o_evaluate_Divide(   ) {

	}
	void	_scriptHandlerCompiler::o_evaluate_ShiftRight(   ) {

	}

	void	_scriptHandlerCompiler::o_evaluate_ShiftLeft(   ) {

	}

	void	_scriptHandlerCompiler::o_evaluate_And(   ) {

	}

	void	_scriptHandlerCompiler::o_evaluate_Or(   ) {

	}

	void	_scriptHandlerCompiler::o_evaluate_DivideRemainder(   ) {

	}

	void	_scriptHandlerCompiler::o_evaluate_XOR(   ) {

	}

	void	_scriptHandlerCompiler::o_execute_Unit_GetDetail(  ) {
		static string	detailName;
		*_sourceFile >> detailName;
	}

}
