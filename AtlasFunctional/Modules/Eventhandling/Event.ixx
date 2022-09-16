module;

#include "../../../Macros/Macros.h"
#include <vector>
#include <map>

export module AtlasEvent;
import AtlasDefinitions;
import AtlasConcepts;
import AtlasMeta;
import AtlasExceptions;
import AtlasInterfaces;
import AtlasFunctionalTraits;
import AtlasMethods;

export namespace Atlas
{
	template<typename... Args>
	class DLLApi Event :
		public Trait::Invokable<void , Event<Args...>, Args...>
	{
		private: using LambdaType = Definition::LambdaFunction<void , Args...>;
		private: using StaticType = Definition::StaticFunction<void , Args...>;
		private: using InterfaceType = Interface::IInvokable<void , Args...>;
		private: using EventType = Event<Args...>;

		struct InstanceWrapper
		{
			void* Instance;
			void* Function;
			InterfaceType Invoked;

			InstanceWrapper(void* instance, void* function, InterfaceType invoked ) noexcept :
				Instance( instance ),
				Function( function ),
				Invoked( invoked )
			{}
		};
		
		
		private: std::vector<LambdaType> _lambdas;
		private: std::vector<StaticType> _static;
		private: std::vector<InstanceWrapper> _wrapped;

		
		public:
		Event( ) noexcept
		{}

		public:
		void Invoke( Args&&... arguments )
		{
			for ( auto invoked : _lambdas )
			{
				invoked( std::forward<Args&&>( arguments )... );
			}

			for ( auto invoked : _static )
			{
				invoked( std::forward<Args&&>( arguments )... );
			}

			for ( auto wrapper : _wrapped )
			{
				wrapper.Invoked( std::forward<Args&&>( arguments )... );
			}
		}

		public: template<typename InvokedType>
		void Subscribe( InvokedType invoked )
		{
			_lambdas.emplace_back( invoked );
		}

		public: template<typename InvokedType>
			requires Concept::IsSame<InvokedType, StaticType>
		void Subscribe( InvokedType invoked )
		{
			_static.emplace_back( invoked );
		}

		public: template<typename ClassType, typename InvokedType>
		void Subscribe( ClassType instance, InvokedType invoked )
		{
			_wrapped.emplace_back( Wrap( instance , invoked ) );
		}

		public: template<typename InvokedType>
		void Unsubscribe( InvokedType invoked )
		{
			Meta::Vector::Remove( _lambdas, invoked );
		}	

		public: template<typename InvokedType>
			requires Concept::IsSame<InvokedType , StaticType>
		void Unsubscribe( InvokedType invoked )
		{
			Meta::Vector::Remove( _static , invoked );
		}

		public: template<typename ClassType , typename InvokedType>
		void Unsubscribe( ClassType instance , InvokedType invoked )
		{
			auto condition = [ &instance , &invoked ]( const InstanceWrapper& wrapper )
			{
				return wrapper.Instance == (void*) instance && wrapper.Function == (void*) invoked;
			};

			Meta::Vector::RemoveIf( _wrapped , condition );
		}

		public: template<typename InvokedType>
		void operator+=( InvokedType invoked )
		{
			Subscribe( invoked );
		}

		public: template<typename InvokedType>
		void operator-=( InvokedType invoked )
		{
			Unsubscribe( invoked );
		}

		private: template<typename ClassType , typename InvokedType>
		InstanceWrapper Wrap( ClassType instance , InvokedType invoked )
		{
			InstanceWrapper( instance , invoked , Method::Create( instance , invoked ) );
		}
	};
}