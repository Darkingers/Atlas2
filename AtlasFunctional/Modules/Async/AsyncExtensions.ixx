module;

#include "../../../Macros/Macros.h"
#include <chrono>
#include <thread>

export module AtlasAsync:AsyncExtensions;
import AtlasDefinitions;
import AtlasConcepts;
import AtlasExceptions;
import AtlasFunctionalTraits;
import AtlasTypeInfo;

export namespace Atlas
{
	class DLLApi Async
	{
		public: template<typename InvokableType>
		inline static void Invoke( InvokableType type )
		{
			std::thread t( type );
			t.detach( );
		}

		public: template<typename InvokableType>
		static void WaitUntil( InvokableType condition , unsigned int timeout_ms = -1 , unsigned int sleep_ms = 100 )
		{
			std::chrono::milliseconds sleepDuration( 2000 );
			if ( timeout_ms == -1 )
			{
				while ( !condition( ) )
				{
					std::this_thread::sleep_for( sleepDuration );
				}
			}
			/*else
			{
				unsigned int current = 0;

				while ( current < timeout_ms )
				{
					if ( condition( ) )
					{
						return;
					}

					std::this_thread::sleep_for( sleepTime );
					current += sleep_ms;
				}

				Throw<TimeoutException>( "Timed out" , timeout_ms );
			}*/
		}
	};
}