module;

#include "../../../Macros/Macros.h"

export module AtlasIterators:ListIterator;
import AtlasInterfaces;

export namespace Atlas
{
	template<typename DataType, typename NodeType>
	class DLLApi ListIterator :
        public Interface::IIterator<DataType>
	{
        private: using IteratorType = ListIterator<DataType, NodeType>;

        public: using iterator_category = std::bidirectional_iterator_tag;
        public: using difference_type = std::ptrdiff_t;
        public: using value_type = DataType;
        public: using pointer = DataType*;
        public: using reference = DataType&;




        private: NodeType* _current;


        public:
        constexpr ListIterator( NodeType* current ) :
            _current( current )
        {

        }

        public:
        constexpr ~ListIterator( ) final
        {}

        public:
        constexpr  DataType& operator*( ) final
        {
            return _current->Data;
        }

        public:
        constexpr  DataType* operator->( ) final
        {
            return &(_current->Data);
        }

        public:
        constexpr IteratorType& operator++( ) final
        {
            _current = _current->Next;
            return *this;
        }

        public:
        constexpr IteratorType& operator++( int) final
        {
            IteratorType tmp = *this;
            _current = _current->Next;
            return tmp;
        }

        public:
        constexpr IteratorType& operator--( ) final
        {
            _current = _current->Previous;
            return *this;
        }

        public:
        constexpr IteratorType operator--( int ) final
        {
            IteratorType tmp = *this; 
            _current = _current->Previous;
            return tmp;
        }

        constexpr friend bool operator== ( const IteratorType& a , const IteratorType& b )
        {
            return a._current == b._current;
        };

        constexpr friend bool operator!= ( const IteratorType& a , const IteratorType& b )
        {
            return a._current != b._current;
        };
	};
}