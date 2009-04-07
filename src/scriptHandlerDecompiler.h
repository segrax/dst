namespace script {
	class _scriptHandlerDecompiler : public _scriptHandler {
	private:
		word			 _scriptLastPush;			// Last push operation value

		// Runtime Data
		byte			 _opcodeCurrent;					// Current Opcode
		size_t			 _stackCount;						// Stack Count
		word			 _scriptData, _scriptDataNext;		// 
		word			*_scriptPtrEnd;						// address of beginning and end of script data

		bool			 headerRead();						// Read the header
		
		bool			 scriptDecompile();					// Decompile the script
		bool			 scriptNextStart( );				// Are we at the start of a section?
		bool			 scriptLoad();						// 

		inline void			 dataPrint( word data ) {		// Print a word to screen in decimal
			if( !_modePreProcess )
				cout << dec << uppercase  << data;
		}

		// Public Functions
	public:
						 _scriptHandlerDecompiler( const char *fileName );
						~_scriptHandlerDecompiler();

		bool			 decompile();						// Decompile a script


		//					Opcode Functions
	protected:
		
		void			 o_goto				(   );					
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

		void			 o_execute_Building_Null(  );
		void			 o_execute_Unit_Null(  );
		void			 o_execute_Unit_GetDetail(  );
		void			 o_execute_House_Null(  );
	};

};
