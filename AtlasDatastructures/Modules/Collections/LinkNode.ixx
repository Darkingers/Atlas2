module;

#include "../../../Macros/Macros.h"

export module AtlasCollections:LinkNode;
import AtlasDefinitions;

export namespace Atlas
{
	/*template<typename DataType>
	class DLLApi LinkNode
	{
		private: using LinkNodeType = LinkNode<DataType>;

		public: DataType Data;
		public: LinkNodeType* Next;
		public: LinkNodeType* Previous;


		public:
		LinkNode( const DataType& data )  :
			Data( data )
		{

		}

		public: template<typename... Args>
		LinkNode( Args&&... arguments ) 
		{
			if constexpr ( sizeof...( arguments ) > 0 )
			{
				this->Add( std::forward<Args>(arguments)... );
			}
		}

		public:
		LinkNode( DataType&& data )  :
			Data(  std::move(data) )
		{

		}

		public:
		~LinkNode() 
		{
		}

		public:
		LinkNode& First() const 
		{
			if ( Previous != nullptr )
			{
				return Previous->First();
			}
			else
			{
				return *this;
			}
		}

		public:
		LinkNode* First(Condition<DataType> condition) const 
		{
			LinkNode* first = condition(*Data) ? this : nullptr;
			LinkNode* current = Previous;
			
			while ( current != nullptr )
			{
				if ( condition( *current ) )
				{
					first = current;
				}

				current = current->Previous;
			}

			if ( first != nullptr )
			{
				return first;
			}
			else
			{
				current = Next;
				while ( current != nullptr )
				{
					if ( condition( *current ) )
					{
						return current;
					}

					current = current->Next;
				}

				return nullptr;
			}
		}

		public:
		LinkType* First( Condition<DataType> condition ) const 
		{
			return this->First( [&condition] ( const LinkType& link )
			{
				return condition( link.Data );
			} );
		}
		
		public: 
		LinkType& Last() const 
		{
			if ( Next != nullptr )
			{
				return Next->Last();			
			}
			else
			{
				return *this;
			}
		}

		public:
		LinkType* Last( Condition<LinkType> condition ) const 
		{
			LinkType* last = condition( *this ) ? this : nullptr;
			LinkType* current = Next;

			while ( current != nullptr )
			{
				if ( condition( *current ) )
				{
					last = current;
				}

				current = current->Next;
			}

			if ( last != nullptr )
			{
				return last;
			}
			else
			{
				current = Previous;
				while ( current != nullptr )
				{
					if ( condition( *current ) )
					{
						return current;
					}
					current = current->Previous;
				}

				return nullptr;
			}
		}

		public:
		LinkType* Last( Condition<DataType> condition ) const 
		{
			return this->Last( [&condition] ( const LinkType& link )
			{
				return condition( link.Data );
			} );
		}

		public:
		const bool Contains(const DataType& data) const 
		{
			return this->Any( [&data] ( const LinkType link )
			{
				return data == link.Data;
			} );
		}

		public:
		const bool Any( Condition<DataType> condition ) const 
		{
			return this->Any( [&condition] ( const LinkType& link )
			{
				return condition( link.Data );
			}
		}

		public:
		const bool Any( Condition<LinkType> condition ) const 
		{
			if ( condition(*this))
			{
				return true;
			}
			else
			{			
				return ( Next != nullptr && Next->Any( condition ) ) || ( Previous != nullptr && Previous->Any( condition ) );
			}		
		}
	
		public: 
		LinkType& DeleteFollowingLinks() 
		{
			if ( Next != nullptr )
			{
				Next->DeleteFollowingLinks();
				delete Next;
			}

			Next = nullptr;

			return *this;
		}
		
		public:
		LinkType& DeleteFollowingLinksIf( Condition<DataType> condition ) 
		{
			return this->DeleteFollowingLinksIf( [&condition] ( const LinkType& link )
			{
				return condition( link.Data );
			} );
		}

		public:
		LinkType& DeleteFollowingLinksIf( Condition<LinkType> condition) 
		{
			if ( Next == nullptr )
			{
				return *this;
			}

			LinkType* start = this;
			LinkType* current = this->Next;
			bool doExit = false;

			while ( true )
			{
				while ( condition( *current ) )
				{
					if ( current->Next == nullptr )
					{
						delete current;
						doExit = true;
						break;
					}
					else
					{
						current = current->Next;
						delete current->Previous;
					}
				}

				if ( doExit )
				{
					start->Next = nullptr;
					break;
				}
				else
				{
					start->Next = current;
					current->Previous = start;

					start = current;
					current = start->Next;
				}
			}

			return *this;
		}

		public: 
		LinkType& DeletePreviousLinks() 
		{
			if ( Previous != nullptr )
			{
				Previous->DeletePreviousLinks();
				delete Previous;
			}

			Previous = nullptr;

			return *this;
		}

		public:
		LinkType& DeletePreviousLinksIf( Condition<DataType> condition ) 
		{
			return this->DeletePreviousLinksIf( [&condition] ( const LinkType& link )
			{
				return condition( link.Data );
			} );
		}

		public:
		LinkType& DeletePreviousLinksIf( Condition<LinkType> condition ) 
		{
			if ( Previous == nullptr )
			{
				return *this;
			}

			LinkType* start = this;
			LinkType* current = this->Previous;
			bool doExit = false;

			while ( true )
			{
				while ( condition( *current) )
				{
					if ( current->Previous == nullptr )
					{
						delete current;
						doExit = true;
						break;
					}
					else
					{
						current = current->Previous;
						delete current->Next;
					}
				}

				if ( doExit )
				{
					start->Previous = nullptr;
					break;
				}
				else
				{
					start->Previous = current;
					current->Next = start;

					start = current;
					current = start->Previous;
				}
			}

			return *this;
		}

		public: template<typename... Args>
		LinkType& InsertBefore( LinkType& inserted, Args... arguments ) 
		{
			LinkType* previous = Previous;

			inserted.Next = this;
			inserted.Previous = previous;

			Previous = &inserted;

			if ( previous != nullptr )
			{
				previous->Next = &inserted;
			}

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return inserted;
			}
			else
			{
				return inserted.InsertBefore( arguments... );				
			}		
		}
		
		public: template<typename... Args>
		LinkType& InsertBefore( DataType& inserted, Args... arguments ) 
		{
			return this->InsertBefore( *new LinkType( inserted ), arguments... );
		}
		
		public: template<typename CollectionType, typename... Args> requires Concepts::AtlasIterableCollection<CollectionType, DataType, Functor<DataType>, Condition<DataType>>
		LinkType& InsertBefore( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( DataType& data ) mutable
			{		
				last = &last->InsertBefore( data );
			} );

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertBefore( arguments... );				
			}
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::AtlasIterableCollection<CollectionType, LinkType, Functor<LinkType>, Condition<LinkType>>
		LinkType& InsertBefore( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( LinkType& link ) mutable
			{
				last = &last->InsertBefore( link );
			} );

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertBefore( arguments... );			
			}
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::StandardIterableCollection<CollectionType, DataType>
		LinkType& InsertBefore( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			for ( auto data : collection )
			{
				last = &last->InsertBefore( *data );
			}

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertBefore( arguments... );
			}
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::StandardIterableCollection<CollectionType, LinkType>
		LinkType& InsertBefore( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			for ( auto link : collection )
			{
				last = &last->InsertBefore( *link );
			}

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertBefore( arguments... );			
			}
		}

		public: template<typename... Args>
		LinkType& InsertAfter( LinkType& inserted, Args... arguments ) 
		{
			LinkType* next = Next;

			inserted.Next = next;
			inserted.Previous = this;

			Next = &inserted;

			if ( next != nullptr )
			{
				next->Previous = &inserted;
			}


			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return inserted;
			}
			else
			{
				return inserted.InsertAfter( arguments... );			
			}
		}

		public: template<typename... Args>
		LinkType& InsertAfter( DataType& inserted, Args... arguments ) 
		{
			return this->InsertAfter( *new LinkType( inserted ), arguments... );
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::AtlasIterableCollection<CollectionType, DataType, Functor<DataType>, Condition<DataType>>
		LinkType& InsertAfter( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( DataType& data ) mutable
			{
				last = &last->InsertAfter( data );
			} );

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertAfter( arguments... );			
			}
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::AtlasIterableCollection<CollectionType, LinkType, Functor<LinkType>, Condition<LinkType>>
		LinkType& InsertAfter( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( LinkType& link ) mutable
			{
				last = &last->InsertAfter( link );
			} );

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertAfter( arguments... );
			}
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::StandardIterableCollection<CollectionType, DataType>
		LinkType& InsertAfter( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			for ( auto data : collection )
			{
				last = &last->InsertAfter( *data );
			}

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertAfter( arguments... );				
			}
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::StandardIterableCollection<CollectionType, LinkType>
		LinkType& InsertAfter( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			for ( auto link : collection )
			{
				last = &last->InsertAfter( *link );
			}

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertAfter( arguments... );			
			}
		}

		public: template<typename... Args>
		LinkType& Add( Args... arguments )
		{
			return this->Add( arguments... );
		}

		public: template<typename... Args>
		LinkType& Add( DataType& data, Args... arguments )
		{
			return this->Add( *new LinkType( data), arguments... ) );
		}

		public: template<typename... Args>
		LinkType& Add( LinkType& link, Args... arguments )
		{
			Next = link;
			link->Previous = *this;

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return link;
			}
			else
			{
				return link->Add( arguments... );
			}
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::AtlasIterableCollection<CollectionType, DataType, Functor<DataType>, Condition<DataType>>
		LinkType& Add( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( DataType& data ) mutable
			{
				last = &last->Add( data );
			} );

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->Add( arguments... );
			}
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::AtlasIterableCollection<CollectionType, LinkType, Functor<LinkType>, Condition<LinkType>>
		LinkType& Add( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( LinkType& link ) mutable
			{
				last = &last->Add( link );
			} );

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->Add( arguments... );
			}
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::StandardIterableCollection<CollectionType, DataType>
		LinkType& Add( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			for ( DataType* data : collection )
			{			
				last = &last->Add( data );
			}

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->Add( arguments... );
			}
		}

		public: template<typename CollectionType, typename... Args> requires Concepts::StandardIterableCollection<CollectionType, LinkType>
		LinkType& Add( CollectionType& collection, Args... arguments )
		{
			LinkType* last = this;
			for ( LinkType* link : collection )
			{
				last = &last->Add( data );
			}

			if constexpr ( sizeof...( arguments ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->Add( arguments... );
			}
		}*/
	//};
}