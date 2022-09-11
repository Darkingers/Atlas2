module;

#include "../../../Macros/Macros.h"
#include <vector>
#include <map>

export module AtlasEventHandlig:Event;
import AtlasDefinitions;
import AtlasFunctionalTraits;
import AtlasInvokers;

export namespace Atlas
{
	template<typename... Args>
	class DLLApi Event :
		public Trait::Invokable<void , Event<Args...>, Args...>
	{
		private: using LambdaType = Definition::LambdaFunction<void , Args...>;
		private: using StaticType = Definition::StaticFunction<void , Args...>;

		private: std::map<unsigned int,LambdaType> _invoked;
		
	};

}