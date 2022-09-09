module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IEnumerable;
import AtlasDefinitions;

export namespace Atlas::Interface
{
	template<typename DataType>
	class DLLApi IEnumerable
	{
		private: using ConditionType = Definition::Condition<DataType>;

		public: 
		virtual bool Contains( const DataType&& data )const  = 0;

		public:
		virtual bool Contains( const ConditionType&& condition )const  = 0;

		public:
		virtual unsigned int Count()const  = 0;

		public:
		virtual unsigned int Count( const DataType&& data )const  = 0;

		public:
		virtual unsigned int Count( const ConditionType&& condition )const  = 0;

		public: 
		virtual bool All( const DataType&& data )const  = 0;

		public:
		virtual bool All( const ConditionType&& condition )const  = 0;

		public: 
		virtual bool Any( const DataType&& data )const  = 0;

		public:
		virtual bool Any( const ConditionType&& condition )const  = 0;

		public: 
		virtual DataType& First( const ConditionType&& condition )const = 0;

		public: 
		virtual DataType* FirstOrNullptr( const ConditionType&& condition )const  = 0;
	};
}