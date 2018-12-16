#include <bits/stdc++.h>

using namespace std;

/**
* @brief dump elements in list with given order.
* @param start iterator of list for dumping
* @param output will be printed in order obtained from this order list.
*/
void dump( list<int>::const_iterator __first, initializer_list<int> orders ) {
    ofstream output( "card.out" );
    for ( int distance : orders ) {
        advance( __first, distance );
        output << *__first << ' ';
    }
    output.close();
}

int main(void)
{
    ifstream    input_stream( "card.inp" );
    int         num_card, num_action;

    input_stream >> num_card >> num_action;

    list<int>::iterator iter1, iter2;
    list<int>           cards( num_card );
    
    /// create sequence list increases by one.
    iota( cards.begin(), cards.end(), 1 ); 

    string  action;
    int     begin_offset, end_offset;

    for ( int i = 0; i < num_action; i++ ) {
        input_stream >> action;

        if ( action == "Shuffle" ) {
            /// pop card in the middle and insert it in the front.
            /// repeat this works until the last card.
            iter1 = ( iter2 = cards.begin() );
            advance( iter2, (num_card + 1) / 2 );

            while ( iter2 != cards.end() ) {
                ++iter1;
                cards.insert( iter1, *iter2 );
                iter2 = cards.erase( iter2 );
            }
        } else {
            /// pop a bundle of cards from original cards, store it on the other space temporarily.
            /// lastly, insert it at the back of the original cards.
            input_stream >> begin_offset >> end_offset;

            iter1 = ( iter2 = cards.begin() );
            advance( iter1, begin_offset - 1 );
            advance( iter2, end_offset );

            list<int> temp_cards;
            temp_cards.splice( temp_cards.begin(), cards, iter1, iter2 );
            cards.splice( cards.end(), temp_cards );
        }
    }

    /// dump the mixed cards.
    initializer_list<int> orders { 0, ( num_card / 2 ) - 1, ( num_card + 1 ) / 2 };
    dump( cards.cbegin(), orders );

    input_stream.close();
    return EXIT_SUCCESS;
}