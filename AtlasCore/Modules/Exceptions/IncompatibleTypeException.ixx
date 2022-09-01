module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:IncompatibleTypeException;
import :Exception;

export namespace Atlas
{

	template<typename SenderType = void , typename... Args>
	class DLLApi IncompatibleTypeException :
		public Exception<SenderType , Args...>
	{
		public:
		IncompatibleTypeException( const char* message , const SenderType* source = nullptr , const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}