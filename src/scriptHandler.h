namespace script {

	struct labelPosition {
		word	_scriptPos;
		string	_name;
	};

	class _scriptHandler {
	protected:
		// Opcode Definitions
		typedef void (_scriptHandler::*opcodefuncPtr)(  );

		struct _Opcode {
			const char		*description;
			opcodefuncPtr	 function;
		};

		// Opcode Functions
		const _Opcode	*_opcodes;					// Script Opcodes
		const _Opcode	*_opcodesEvaluate;			// Evaluate Command Opcodes
		const _Opcode	*_opcodesExecute;			// Execute Functions


		const char		*_fileName;					// Open File
		word			*_headerPointers;			// function pointers

		unsigned short int	 _pointerCount;			// Number of script "function" pointers
		size_t				 _scriptSize;			// Size of script

		bool			 _modePreProcess;			// In Pre-Process mode?

		const char	   **_objectNames;				// Pointer to current script object names
		const char	   **_objectFunctions;			// Pointer to current script executable functions

		const byte		*_scriptBuffer;				// script byte stream
		word			*_scriptPtr;				// Pointer in _scriptBuffer to current opcode
		word			 _scriptPos;				// Line number of current opcode
		const byte		*_scriptStart;				// pointer in _scriptBuffer to start of actual script
		_scriptTypes	 _scriptType;				// Type of script (BUILD/TEAM/UNIT)

		vector<labelPosition> _scriptLabels;		// List of memory locations which can/are jumped to

		void output( string text, bool endLine = true ) {
			if( _modePreProcess )
				return;

			cout << text;
			if( endLine )
				cout << endl;
		}

		inline int scriptLabelGet( string label ) {
			int pos = scriptLabel( label );
		
			if(pos == -1)
				return -1;

			return _scriptLabels[pos]._scriptPos;
		}

		inline int scriptLabel( string label ) {
			static vector<labelPosition>::iterator		labelIT;
			int											pos = 0;

			for( labelIT = _scriptLabels.begin(); labelIT != _scriptLabels.end(); labelIT++, pos++ ) {
				
				if( label.compare((*labelIT)._name) == 0 )
					return pos;
			}

			// No labels here
			return -1;
		}

		inline int scriptLabel( word position ) {
			static vector<labelPosition>::iterator		labelIT;
			int											pos = 0;

			for( labelIT = _scriptLabels.begin(); labelIT != _scriptLabels.end(); labelIT++, pos++ ) {
				
				if( (*labelIT)._scriptPos == position )
					return pos;
			}

			// No labels here
			return -1;
		}

		inline void scriptLabelAdd( string label, word position ) {
			labelPosition	LP;
			int				labelPos = scriptLabel( position );

			if( labelPos == -1 ) {
				LP._name		= label.substr( 0, label.size() -1 );
				LP._scriptPos	= position;

				_scriptLabels.push_back( LP );
			}
		}

		public:
			// Constructor
							 _scriptHandler( const char *fileName );
							~_scriptHandler();
		
			word			 scriptOpcodeFind(  string opcodeStr, const _Opcode *opcodes );	// Search the opcode table for 'Opcode' string
			// Virtual Functions

			// Opcode Prepare
			virtual void	 opcodesSetup();
			virtual void	 opcodesBuildingsSetup();
			virtual void	 opcodesUnitsSetup();
			virtual void	 opcodesHousesSetup();

			// Opcodes
			virtual void	 o_goto				(  )	= 0;					
			virtual void	 o_setreturn		(   )	= 0;
			virtual void	 o_push				(   )	= 0;
			virtual void	 o_pusharg			(   )	= 0;
			virtual void	 o_pusharg1			(   )   = 0;
			virtual void	 o_pushreg			(   )	= 0;
			virtual void	 o_pushframeMinArg	(   )	= 0;
			virtual void	 o_pushframePluArg	(   )	= 0;
			virtual void	 o_popret			(   )	= 0;
			virtual void	 o_popreg			(   )	= 0;
			virtual void	 o_popframeMinArg	(   )	= 0;
			virtual void	 o_popframePluArg	(   )	= 0;
			virtual void	 o_spadd			(   )	= 0;
			virtual void	 o_spsub			(   )	= 0;
			virtual void	 o_execute			(   )	= 0;
			virtual void	 o_ifnotgoto		(   )	= 0;
			virtual void	 o_negate			(   )	= 0;
			virtual void	 o_evaluate			(   )	= 0;
			virtual void	 o_return			(   )	= 0;

			// Opcode Evaluation Modes
			virtual void	 o_evaluate_IfEither( 	)				= 0;
			virtual void	 o_evaluate_Equal(   )					= 0;
			virtual void	 o_evaluate_NotEqual(   )				= 0;
			virtual void	 o_evaluate_CompareGreaterEqual(   )	= 0;
			virtual void	 o_evaluate_CompareGreater(   )			= 0;
			virtual void	 o_evaluate_CompareLessEqual(   )		= 0;
			virtual void	 o_evaluate_CompareLess(   )			= 0;
			virtual void	 o_evaluate_Add(   )					= 0;
			virtual void	 o_evaluate_Subtract(   )				= 0;
			virtual void	 o_evaluate_Multiply(   )				= 0;
			virtual void	 o_evaluate_Divide(   )					= 0;
			virtual void	 o_evaluate_ShiftRight(   )				= 0;
			virtual void	 o_evaluate_ShiftLeft(   )				= 0;
			virtual void	 o_evaluate_And(   )					= 0;
			virtual void	 o_evaluate_Or(   )						= 0;
			virtual void	 o_evaluate_DivideRemainder(   )		= 0;
			virtual void	 o_evaluate_XOR(   )					= 0;

			// Opcode Execute Functions
			// Buildings
			virtual void	 o_execute_Building_Null(  )			= 0;

			// Units
			virtual void	 o_execute_Unit_Null(  )				= 0;
			virtual void	 o_execute_Unit_GetDetail(  )			= 0;

			// Houses
			virtual void	 o_execute_House_Null(  )				= 0;
		};

};
