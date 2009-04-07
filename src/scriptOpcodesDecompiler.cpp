#include "stdafx.h"
#include "scriptHandler.h"
#include "scriptHandlerDecompiler.h"

namespace script {

	void	_scriptHandlerDecompiler::o_goto(   ) {
		int labelPos = scriptLabel( _scriptData );

		if( !_modePreProcess ) {

			if( labelPos == -1)
				dataPrint( _scriptData );
			else
				cout << "l" << _scriptLabels[labelPos]._scriptPos;

		} else {
			if(labelPos == -1)
				scriptLabelAdd("", _scriptData);
		}
	}

	void	_scriptHandlerDecompiler::o_setreturn(   ) {
		if(_scriptDataNext) {
			dataPrint( _scriptDataNext );
		} else {
			dataPrint( _scriptData );
		}
	}

	void	_scriptHandlerDecompiler::o_push(   ) {
		word data = _scriptData;
		if(_scriptData == 0)
			data = _scriptDataNext;

		_stackCount--;

		dataPrint(data);
	}

	void	_scriptHandlerDecompiler::o_pusharg(   ) {
		_stackCount--;

		if(_scriptDataNext) {
			_scriptLastPush = _scriptDataNext;
			dataPrint( _scriptDataNext );
		} else {
			_scriptLastPush = _scriptData;
			dataPrint( _scriptData );
		}
	}

	void	_scriptHandlerDecompiler::o_pusharg1(  ) {
		o_pusharg();
	}

	void	_scriptHandlerDecompiler::o_pushreg(   ) {
		_stackCount--;
		
		if(_scriptDataNext) {
			dataPrint( _scriptDataNext );
		} else {
			dataPrint( _scriptData );
		}
	}

	void	_scriptHandlerDecompiler::o_pushframeMinArg(   ) {
		_stackCount--;
		_stackCount--;
		if(_scriptDataNext) {
			dataPrint( _scriptDataNext );
		} else {
			dataPrint( _scriptData );
		}
	}

	void	_scriptHandlerDecompiler::o_pushframePluArg(   ) {
		_stackCount--;
		_stackCount--;
		if(_scriptDataNext) {
			dataPrint( _scriptDataNext );
		} else {
			dataPrint( _scriptData );
		}
	}

	void	_scriptHandlerDecompiler::o_popret(   ) {
		if( _scriptData == 1) {
			if( !_modePreProcess )
				cout << " (Return)";
			return;

		} else 
			_stackCount++;

		_stackCount++;
	}

	void	_scriptHandlerDecompiler::o_popreg(   ) {
		_stackCount++;

		if(_scriptDataNext) {
			dataPrint( _scriptDataNext );
		} else {
			dataPrint( _scriptData );
		}

	}

	void	_scriptHandlerDecompiler::o_popframeMinArg(   ) {
		_stackCount++;
		_stackCount++;
		if(_scriptDataNext) {
			dataPrint( _scriptDataNext );
		} else {
			dataPrint( _scriptData );
		}
	}

	void	_scriptHandlerDecompiler::o_popframePluArg(   ) {
		_stackCount++;
		_stackCount++;
		if(_scriptDataNext) {
			dataPrint( _scriptDataNext );
		} else {
			dataPrint( _scriptData );
		}
	}

	void	_scriptHandlerDecompiler::o_spadd(   ) {
		dataPrint( _scriptData );
		_stackCount += (_scriptData & 0xF);
	}

	void	_scriptHandlerDecompiler::o_spsub(   ) {
		dataPrint( _scriptData );
		_stackCount -= (_scriptData & 0xF);
	}

	void	_scriptHandlerDecompiler::o_execute(   ) {

		if( !_modePreProcess )
			cout << left << _opcodesExecute[ _scriptData ].description << " ";
		
		(this->*_opcodesExecute[ _scriptData ].function)( );
	}

	void	_scriptHandlerDecompiler::o_ifnotgoto(   ) {
		int labelPos;

		if(_scriptDataNext) {
			labelPos = scriptLabel( _scriptDataNext & 0x7FFF );

			if( _modePreProcess )  {
				if( labelPos == -1)
					scriptLabelAdd("", _scriptDataNext & 0x7FFF);

			} else {
				if( labelPos == -1)
					dataPrint( _scriptDataNext & 0x7FFF );
				else
					cout << "l" << _scriptLabels[labelPos]._scriptPos;
			}

		} else {
			labelPos = scriptLabel( _scriptData );

			if( _modePreProcess ) {
				if( labelPos == -1 )
					scriptLabelAdd("", _scriptData);
			} else {
				if( labelPos == -1)
					dataPrint( _scriptData );
				else
					cout << "l" << _scriptLabels[labelPos]._scriptPos;
			}
		}
	}

	void	_scriptHandlerDecompiler::o_negate(   ) {
		dataPrint( _scriptData );
	}

	void	_scriptHandlerDecompiler::o_evaluate(   ) {

		if( !_modePreProcess )
			cout << _opcodesEvaluate[ _scriptData ].description;

		(this->*_opcodesEvaluate[ _scriptData ].function)( );
	}

	void	_scriptHandlerDecompiler::o_return(   ) {

	}


	// Evaluate Operators
	void	_scriptHandlerDecompiler::o_evaluate_IfEither( 	) {
		
	}

	void	_scriptHandlerDecompiler::o_evaluate_Equal(   ) {

	}

	void	_scriptHandlerDecompiler::o_evaluate_NotEqual(   ) {

	}

	void	_scriptHandlerDecompiler::o_evaluate_CompareGreaterEqual(   ) {

	}

	void	_scriptHandlerDecompiler::o_evaluate_CompareGreater(   ) {

	}

	void	_scriptHandlerDecompiler::o_evaluate_CompareLessEqual(   ) {

	}
	void	_scriptHandlerDecompiler::o_evaluate_CompareLess(   ) {

	}
	void	_scriptHandlerDecompiler::o_evaluate_Add(   ) {

	}
	void	_scriptHandlerDecompiler::o_evaluate_Subtract(   ) {

	}
	void	_scriptHandlerDecompiler::o_evaluate_Multiply(   ) {

	}

	void	_scriptHandlerDecompiler::o_evaluate_Divide(   ) {

	}
	void	_scriptHandlerDecompiler::o_evaluate_ShiftRight(   ) {

	}

	void	_scriptHandlerDecompiler::o_evaluate_ShiftLeft(   ) {

	}

	void	_scriptHandlerDecompiler::o_evaluate_And(   ) {

	}

	void	_scriptHandlerDecompiler::o_evaluate_Or(   ) {

	}

	void	_scriptHandlerDecompiler::o_evaluate_DivideRemainder(   ) {

	}

	void	_scriptHandlerDecompiler::o_evaluate_XOR(   ) {

	}

	void	_scriptHandlerDecompiler::o_execute_Building_Null(  ) {

	}

	void	_scriptHandlerDecompiler::o_execute_Unit_Null(  ) {

	}

	void	_scriptHandlerDecompiler::o_execute_Unit_GetDetail(  ) {
		if( !_modePreProcess )
			cout << nameUnitDetails[ _scriptLastPush ];
	}

	void	_scriptHandlerDecompiler::o_execute_House_Null(  ) {

	}

}
