#include "HashTable.h"
#include <iostream>
#include <cstring>
 using namespace std;

        /**
         * Internal method to test if a positive number is prime.
         * Not an efficient algorithm.
         */
        bool isPrime( int n )
        {
            if( n == 2 || n == 3 )
                return true;

            if( n == 1 || n % 2 == 0 )
                return false;

            for( int i = 3; i * i <= n; i += 2 )
                if( n % i == 0 )
                    return false;

            return true;
        }

        /**
         * Internal method to return a prime number at least as large as n.
         * Assumes n > 0.
         */
        int nextPrime( int n )
        {
            if( n % 2 == 0 )
                n++;

            for( ; !isPrime( n ); n += 2 )
                ;

            return n;
        }

        /**
         * Construct the hash table.
         */
        template <class HashedObj>
        HashTable<HashedObj>::HashTable( const HashedObj & notFound, int size )
          : ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
        {
            makeEmpty( );
        }

        /**
         * Insert item x into the hash table. If the item is
         * already present, then do nothing.
         */
        template <class HashedObj>
        void HashTable<HashedObj>::insert( const HashedObj & x )
        {
                // Insert x as active
            int currentPos = findPos( x );
            if( isActive( currentPos ) )
                return;

            if( array[ currentPos ].info != DELETED )
                ++currentSize;

            array[ currentPos ] = HashEntry( x, ACTIVE );

                // Rehash; see Section 5.5
            if( currentSize > array.size( ) / 2 )
                rehash( );
        }

        /**
         * Expand the hash table.
         */
        template <class HashedObj>
        void HashTable<HashedObj>::rehash( )
        {
            vector<HashEntry> oldArray = array;

                // Create new double-sized, empty table
            array.resize( nextPrime( 2 * oldArray.size( ) ) );
            for( int j = 0; j < array.size( ); j++ )
                array[ j ].info = EMPTY;

                // Copy table over
            currentSize = 0;
            for( int i = 0; i < oldArray.size( ); i++ )
                if( oldArray[ i ].info == ACTIVE )
                    insert( oldArray[ i ].element );
        }

        /**
         * Method that performs quadratic probing resolution.
         * Return the position where the search for x terminates.
         */
        template <class HashedObj>
        int HashTable<HashedObj>::findPos( const HashedObj & x ) const
        {
/* 1*/      int collisionNum = 0;
/* 2*/      int currentPos = hash1( x, array.size( ) );

/* 3*/      while( array[ currentPos ].info != EMPTY &&
                   array[ currentPos ].element != x )
            {
/* 4*/          currentPos += 2 * ++collisionNum - 1;  // Compute ith probe
/* 5*/          if( currentPos >= array.size( ) )
/* 6*/              currentPos -= array.size( );
            }

/* 7*/      return currentPos;
        }


        /**
         * Remove item x from the hash table.
         */
        template <class HashedObj>
        void HashTable<HashedObj>::remove( const HashedObj & x )
        {
            int currentPos = findPos( x );
            if( isActive( currentPos ) )
                array[ currentPos ].info = DELETED;
        }

        /**
         * Find item x in the hash table.
         * Return the matching item or ITEM_NOT_FOUND if not found
         */
        template <class HashedObj>
        const HashedObj & HashTable<HashedObj>::find( const HashedObj & x ) const
        {
            int currentPos = findPos( x );
            if( isActive( currentPos ) )
                return array[ currentPos ].element;
            else
                return ITEM_NOT_FOUND;
        }

        /**
         * Make the hash table logically empty.
         */
        template <class HashedObj>
        void HashTable<HashedObj>::makeEmpty( )
        {
            currentSize = 0;
            for( int i = 0; i < array.size( ); i++ )
                array[ i ].info = EMPTY;
        }

        /**
         * Deep copy.
         */
        template <class HashedObj>
        const HashTable<HashedObj> & HashTable<HashedObj>::
        operator=( const HashTable<HashedObj> & rhs )
        {
            if( this != &rhs )
            {
                array = rhs.array;
                currentSize = rhs.currentSize;
            }
            return *this;
        }


        /**
         * Return true if currentPos exists and is active.
         */
        template <class HashedObj>
        bool HashTable<HashedObj>::isActive( int currentPos ) const
        {
            return array[ currentPos ].info == ACTIVE;
        }

        template <class HashedObj>
        void HashTable<HashedObj>::display() const
        {
            int HashedIndex = 0;
            cout << "Index" << "    Element\n---------------------------\n";
            for(HashEntry i: array)
            {
                if(i.info == ACTIVE)
                {
                    cout << HashedIndex << "   ->   " << i.element << "\n";
                    HashedIndex++;
                }
            }
        }

        /**
         * A hash routine for string objects.
         */
        int hash1( const string & key, int tableSize )
        {
            int hashVal = 0;

            for( int i = 0; i < key.length( ); i++ )
                hashVal = 37 * hashVal + key[ i ];

            hashVal %= tableSize;
            if( hashVal < 0 )
                hashVal += tableSize;

            return hashVal;
        }


        /**
         * A hash routine for ints.
         */
        int hash1( int key, int tableSize )
        {
            if( key < 0 ) key = -key;
            return key % tableSize;
        }

//template<class HashedObj>
        int main()
        {
            HashTable<int> intHashTable(8);
            intHashTable.insert(5);
            intHashTable.insert(6);
            intHashTable.insert(9);
            intHashTable.insert(3);
            intHashTable.insert(12);
            intHashTable.insert(4);
            intHashTable.insert(99);
            intHashTable.insert(33);
            intHashTable.insert(44);
            intHashTable.insert(10);
            intHashTable.insert(1);
            intHashTable.insert(0);
            cout<<"\n\n<<<<<<<<<<<<<<<   DISPLAYING AFTER INSERTING INTEGER VALUES INTO THE HASH TABLE   >>>>>>>>>>>>>>>\n\n";
            intHashTable.display();

            HashTable<char> charHashTable('a');
            charHashTable.insert('k');
            charHashTable.insert('z');
            charHashTable.insert('f');
            charHashTable.insert('d');
            charHashTable.insert('i');
            charHashTable.insert('v');
            charHashTable.insert('g');
            charHashTable.insert('s');
            charHashTable.insert('o');
            charHashTable.insert('l');
            cout<<"\n\n<<<<<<<<<<<<<<<   DISPLAYING AFTER INSERTING CHARACHTER VALUES INTO THE HASH TABLE    >>>>>>>>>>>>>>>\n\n";
            charHashTable.display();

            HashTable<float> floatHashTable(1.2);
            floatHashTable.insert(3.5);
            floatHashTable.insert(4.162);
            floatHashTable.insert(15.983);
            floatHashTable.insert(0.15893);
            floatHashTable.insert(9.9);
            floatHashTable.insert(5.2);
            floatHashTable.insert(34.042);
            floatHashTable.insert(96.6);
            floatHashTable.insert(99.99999);
            floatHashTable.insert(3.142857);
            cout<<"\n\n<<<<<<<<<<<<<<<   DISPLAYING AFTER INSERTING FLOAT VALUES INTO THE HASH TABLE    >>>>>>>>>>>>>>>\n\n";
            floatHashTable.display();

            HashTable<string> stringHashTable("SomeString");
            stringHashTable.insert("India");
            stringHashTable.insert("USA");
            stringHashTable.insert("New Zealand");
            stringHashTable.insert("Spain");
            stringHashTable.insert("Norway");
            stringHashTable.insert("Sweden");
            stringHashTable.insert("Finland");
            stringHashTable.insert("Germany");
            stringHashTable.insert("UK");
            stringHashTable.insert("Australia");

            cout<<"\n\n<<<<<<<<<<<<<<<   DISPLAYING AFTER INSERTING STRING VALUES INTO THE HASH TABLE    >>>>>>>>>>>>>>>\n\n";
            stringHashTable.display();

            cout<<"\n\n<<<<<<<<<<<<<<<   DISPLAYING AFTER SEARCHING FOR \"India\" IN STRING HASH TABLE    >>>>>>>>>>>>>>>\n\n";
            if (stringHashTable.find("India") == "India")
                cout << "India exists in the hash table.";
            else
                cout << "India does not exist in the hash table.";

            cout<<"\n\n<<<<<<<<<<<<<<<   DISPLAYING AFTER SEARCHING FOR \"Scotland\" IN STRING HASH TABLE    >>>>>>>>>>>>>>>\n\n";
            if (stringHashTable.find("Scotland") == "Scotland")
                cout << "Scotland exists in the hash table.";
            else
                cout << "Scotland does not exist in the hash table.";

            stringHashTable.remove("Australia");
            cout<<"\n\n<<<<<<<<<<<<<<<   DISPLAYING AFTER REMOVING \"Australia\" FROM STRING HASH TABLE    >>>>>>>>>>>>>>>\n\n";
            stringHashTable.display();
            stringHashTable.makeEmpty();

            cout<<"\n\n<<<<<<<<<<<<<<<   DISPLAYING AFTER EMPTYING THE STRING HASH TABLE   >>>>>>>>>>>>>>>\n\n";
            stringHashTable.display();
            intHashTable.makeEmpty();
            charHashTable.makeEmpty();
            floatHashTable.makeEmpty();
            return 0;
        }