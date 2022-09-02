module;

#include "../../../Macros/Macros.h"

export module AtlasCollections:Bucket;
import AtlasDefinitions;
import AtlasInterfaces;
import AtlasValidation;
import AtlasMemoryFunctions;
import AtlasConfiguration;
import AtlasAdapters;
import :Pair;
import :LinkNode;

export namespace Atlas
{
	export namespace Atlas
	{
		template<typename KeyType , typename ValueType , unsigned int Slots = 1000>
		class DLLApi Bucket:
			public IHashable
		{
			/*private: using BucketType = Bucket<KeyType , ValueType , Slots>;
			private: using PairType = Pair<KeyType , ValueType >;
			private: using LinkType = LinkNode<PairType>;

			protected: LinkType* [Buckets] _data;


			public:
			unsigned int GetHash( ) const  final
			{
				unsigned int hash = MemoryFunctions::GetHash( this , sizeof( BucketType ) );

				for ( unsigned int i = 0; i < Buckets; )
				{
					for (LinkType current = _data[i]; current != nullptr; current = current->Next )
					{
						hash ^= HashAdapter<DataType>::GetHash(current->Data ) % hash;
					}
				}

				return hash;
			}

			public: template<typename... Args>
			Bucket( Args&&... argumentss )
			{
				if constexpr ( sizeof...( arguments ) > 0 )
				{
					this->Add( arguments... );
				}
			}

			public:
			~Bucket( )
			{
				for ( int i = 0; i < Buckets; ++i )
				{
					if ( _data[i] != nullptr )
					{
						_data[i]->DeleteFollowingLinks( );
					}
				}
			}

			private:
			const unsigned int GetIndex( const KeyType& key )
			{
				return _hasher( key ) % Buckets;
			}

			public:
			const LinkType& GetPair( const KeyType& key )
			{
				return  *( _data + GetIndex( key ) );
			}

			public: template<typename... Args>
			HashMapType& Add( PairType& pair , Args... arguments )
			{
				const unsigned int index = GetIndex( pair.Key );

				LinkType* entry = _data + index;
				if ( entry == nullptr )
				{
					_data[index] = new LinkType( pair );
					return *this;
				}


				LinkType* previous;

				while ( entry->Next != nullptr )
				{
					CheckKey( entry->Data.Key , pair.key );

					entry = entry->Next;
				}

				CheckKey( entry->Data.Key , pair.key );

				entry->Add( *new LinkType( pair );

				if constexpr ( sizeof...( arguments ) == 0 )
				{
					return *this;
				}
				else
				{
					return this->Add( arguments... );
				}

			}

			public: template<typename... Args>
			HashMapType& Add( const KeyType& key , ValueType& value , Args... arguments )
			{
				return this->Add( *new PairType( key , value ) , arguments... );
			}

			public: template<typename CollectionType , typename... Args> requires Concepts::AtlasIterableCollection<CollectionType , PairType , Functor<PairType> , Condition<PairType>>
			HashMapType& Add( CollectionType& collection , Args... arguments )
			{
				collection.ForEach( [ ]( PairType& pair ) mutable
				{
					this->Add( pair );
				} );

				if constexpr ( sizeof...( arguments ) == 0 )
				{
					return *this;
				}
				else
				{
					return this->Add( arguments... );
				}
			}

			public: template<typename CollectionType , typename... Args> requires Concepts::StandardIterableCollection<CollectionType , PairType>
			HashMapType& Add( CollectionType& collection , Args... arguments )
			{
				for ( auto pair : collection )
				{
					this->Add( pair );
				}

				if constexpr ( sizeof...( arguments ) == 0 )
				{
					return *this;
				}
				else
				{
					return this->Add( arguments... );
				}
			}

			public:
			ValueType& Get( const KeyType& key )
			{
				LinkType* entry = &this->GetPair( key );

				while ( entry != nullptr );
				{
					if ( entry->Data.Key == key )
					{
						return entry->Data.Value;
					}

					entry = entry->Next;
				}


				throw NotFoundException( "Key " + key + " was not found!" );
			}

			private:
			void CheckKey( KeyType existingKey , KeyType newKey )
			{
				if ( existingKey == newKey )
				{
					throw AlreadyExistsException( "Key " + existingKey + " already exists!" )
				}
			}

			public:
			bool ContainsValue( const ValueType& value )
			{
				for ( auto bucket : _data )
				{
					if ( bucket.Contains( value ) )
					{
						return true;
					}
				}

				return false;
			}

			public:
			ValueType& operator[]( const KeyType& key )
			{
				return Get( key );
			}*/
		};
	}
}