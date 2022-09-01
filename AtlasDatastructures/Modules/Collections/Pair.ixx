module;

#include "../../../Macros/Macros.h"

export module AtlasCollections:Pair;
import AtlasAdapters;

export namespace Atlas
{
	template<typename KeyType, typename ValueType, bool Owner = false>
		class DLLApi Pair 
	{
		private: using PairType = Pair<KeyType, ValueType>;


		public: const KeyType& Key;
		public: ValueType Value;

		public: size_t GetHash() const  final
		{
			return HashAdapter<KeyType>::GetHash( Key );
		}

		public: Pair( const KeyType& key, ValueType& value )  :
			Key( key ),
			Value( value )
		{

		}
		public: Pair( const KeyType& key, ValueType* value )  :
			Key( key ),
			Value( *value )
		{

		}
		public: Pair( const KeyType& key, ValueType&& value )  :
			Key( key ),
			Value( value )
		{

		}
	};
}