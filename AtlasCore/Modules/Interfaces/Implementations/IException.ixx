module;

#include "../../../../Macros/Macros.h"

export module AtlasCoreInterfaces:IException;

export namespace Atlas
{
	class DLLApi IException 
	{
		
	public:

		
		virtual ~IException( ) = default;
		
		virtual const char* ToString( ) const noexcept = 0;
	};
}