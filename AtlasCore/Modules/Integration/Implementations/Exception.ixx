module;

#include "../../../../Macros/Macros.h"

export module AtlasIntegration:Exception;

export namespace Atlas
{
	class DLLApi Exception 
	{
		public:
		virtual ~Exception( ) = default;
		
		public:
		virtual const char* ToString( ) const noexcept = 0;
	};
}