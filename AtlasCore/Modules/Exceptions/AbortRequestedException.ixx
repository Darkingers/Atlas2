module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:AbortRequestedException;
import :Exception;

export namespace Atlas
{
	class DLLApi AbortRequestedException :
		public Exception
	{
		public: AbortRequestedException( const char* message , const void* sender ) noexcept:
			Exception( message , sender )
		{
			
		}
	};

	template<typename SenderType = void , typename... Args>
	class DLLApi ExtendedAbortRequestedException :
		public ExtendedException<SenderType , Args...>
	{
		public:
		AbortRequestedException( const char* message ,const SenderType* source = nullptr, const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}