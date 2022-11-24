module;

#include "../../../../Macros/Macros.h"

export module AtlasIntegration:IException;

export namespace Atlas
{
	class DLLApi IException 
	{
		public:
		virtual ~IException( ) = default;
		
		public:
		virtual const char* ToString( ) const noexcept = 0;
	};
}