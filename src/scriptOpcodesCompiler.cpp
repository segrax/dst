#include "stdafx.h"
#include "scriptHandler.h"
#include "scriptHandlerCompiler.h"

namespace script {

	void	_scriptHandlerCompiler::o_goto(   ) {
		int labelPos = scriptLabelGet( _currentLine );
		
		*(_scriptPtr) |= 0x80;
		*(_scriptPtr) |= swapWord(labelPos);

	}

	void	_scriptHandlerCompiler::o_setreturn(   ) {
		//*(_scriptPtr) |= 0x40;

	}

	void	_scriptHandlerCompiler::o_push(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));

		/*if(_scriptDataNext) {
			_scriptLastPush = _scriptDataNext;
			dataPrint( _scriptDataNext );
		} else {
			_scriptLastPush = _scriptData;
			dataPrint( _scriptData );
		}*/
	}

	void	_scriptHandlerCompiler::o_pusharg(   ) {
		*(_scriptPtr) |= 0x20;
		*(_scriptPtr+1) |= swapWord(atoi(_currentLine.c_str()));
		_scriptPtr++;
		_scriptPos++;
	}

	void	_scriptHandlerCompiler::o_pusharg1(   ) {
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

		//dataPrint( _scriptData );
		//_stackCount += (_scriptData & 0xF);
	}

	void	_scriptHandlerCompiler::o_spsub(   ) {
		*(_scriptPtr) |= 0x40;
		*(_scriptPtr) |= swapWord(atoi(_currentLine.c_str()));

		//dataPrint( _scriptData );
		//_stackCount -= (_scriptData & 0xF);
	}

	void	_scriptHandlerCompiler::o_execute(   ) {
		word opcode = 0;
		*(_scriptPtr) |= 0x40;

		opcode = scriptOpcodeFind( _currentLine, _opcodesExecute );
		
		*(_scriptPtr) |= swapWord(opcode);

//		cout << left << _opcodesExecute[ _scriptData ].description << " ";
		
	//	(this->*_opcodesExecute[ _scriptData ].function)( );
	}

	void	_scriptHandlerCompiler::o_ifnotgoto(   ) {
		int labelPos = scriptLabelGet( _currentLine );
		int line = 0;
		//stringstream in;

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

	void	_scriptHandlerCompiler::o_execute_House_Null(  ) {

	}

	void	_scriptHandlerCompiler::o_execute_Building_Null(  ) {

	}

	void	_scriptHandlerCompiler::o_execute_Unit_Null(  ) {

	}

	void	_scriptHandlerCompiler::o_execute_Unit_GetDetail(  ) {
		
		//cout << nameUnitDetails[ _scriptLastPush ];
	}

}
