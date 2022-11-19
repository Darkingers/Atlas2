module;

#include "../../../../Macros/Macros.h"

export module AtlasValidation:ValidationException;

import AtlasIntegration;

export namespace Atlas
{
	class DLLApi ValidationException :
		public Exception
	{
		private: const char* _message;

		public:
		constexpr ValidationException( const char* message ) 
			noexcept :
			_message( message )
		{} 
		
		public:
		constexpr ~ValidationException( ) 
			noexcept = default;

		public:
		constexpr const char* ToString( )
			const noexcept final
		{
			return _message;
		}
	};
}