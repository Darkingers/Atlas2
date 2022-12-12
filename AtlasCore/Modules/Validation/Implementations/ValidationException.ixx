module;

#include "../../../../Macros/Macros.h"

export module AtlasValidation:ValidationException;

import AtlasCoreInterfaces;

export namespace Atlas
{
	class DLLApi ValidationException :
		public IException
	{
	private: 
		
		const char* _message;

	public:
		
		constexpr ValidationException( const char* message ) 
			noexcept :
			_message( message )
		{} 
		
		constexpr ~ValidationException( ) 
			noexcept = default;

		constexpr const char* ToString( )
			const noexcept final
		{
			return _message;
		}
	};
}