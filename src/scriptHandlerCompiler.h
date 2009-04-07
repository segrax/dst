

namespace script {

	class _scriptHandlerCompiler : public _scriptHandler {
	private:
		ifstream		*_sourceFile;				// Source-Code file	

		string			 _currentLine, _opcodeCurrent, _data;
		word			 _opcode;

		bool			 headerCreate();			// Insert the header
		bool		     scriptCompile( );			// Compile to the byte code
		bool			 scriptSave();				// Save the buffer to disk
		int				 scriptSectionCheck();		// Check for section name in _currentLine

	public:
						 _scriptHandlerCompiler( const char *fileName );
						~_scriptHandlerCompiler();

		bool			 compile();

	private:
		// Opcodes
		void			 o_goto				(  );					
		void			 o_setreturn		(   );
		void			 o_push				(   );
		void			 o_pusharg			(   );
		void			 o_pusharg1			(   );
		void			 o_pushreg			(   );
		void			 o_pushframeMinArg	(   );
		void			 o_pushframePluArg	(   );
		void			 o_popret			(   );
		void			 o_popreg			(   );
		void			 o_popframeMinArg	(   );
		void			 o_popframePluArg	(   );
		void			 o_spadd			(   );
		void			 o_spsub			(   );
		void			 o_execute			(   );
		void			 o_ifnotgoto		(   );
		void			 o_negate			(   );
		void			 o_evaluate			(   );
		void			 o_return			(   );

		void			 o_evaluate_IfEither( 	);
		void			 o_evaluate_Equal(   );
		void			 o_evaluate_NotEqual(   );
		void			 o_evaluate_CompareGreaterEqual(   );
		void			 o_evaluate_CompareGreater(   );
		void			 o_evaluate_CompareLessEqual(   );
		void			 o_evaluate_CompareLess(   );
		void			 o_evaluate_Add(   );
		void			 o_evaluate_Subtract(   );
		void			 o_evaluate_Multiply(   );
		void			 o_evaluate_Divide(   );
		void			 o_evaluate_ShiftRight(   );
		void			 o_evaluate_ShiftLeft(   );
		void			 o_evaluate_And(   );
		void			 o_evaluate_Or(   );
		void			 o_evaluate_DivideRemainder(   );
		void			 o_evaluate_XOR(   );

		void			 o_execute_House_Null(  );
		void			 o_execute_Building_Null(  );
		void			 o_execute_Unit_Null(  );
		void			 o_execute_Unit_GetDetail(  );
	};

}
