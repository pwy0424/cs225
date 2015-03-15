/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class HT>
WordFreq<HT>::WordFreq( const string & infile ) : filename( infile ) { /* nothing */ }

template <template <class K, class V> class HT>
vector< pair<string, int> > WordFreq<HT>::getWords( int threshold ) const {
    TextFile infile( filename );
    vector< pair<string, int> > ret;
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */
	//Hash hasher;
    /*LPHashTable<string, int> hashTable(256);
    while( infile.good() ) 
    {
    	string word = infile.getNextWord();
    	int val = 0;
    	if(hashTable.keyExists(word)) val = hashTable.find( word ); 
    	hashTable.remove(word);
    	hashTable.insert(word, val + 1);
	}
	vector< pair<string, int> > newvect;
	for( int i = 0; i < hashTable.size(); i++ ) 
	{
        if( hashTable.table()[i] != NULL ) newvect.push_back( *(hashTable.table()[i]) );
    }
	for(unsigned int j = 0; j < newvect.size(); j++ ) 
	{
    	if( newvect[j].second >= threshold ) ret.push_back( newvect[j] );
    }*/
	HT<string, int> hashTable(256);
    while( infile.good() ) {
        string word = infile.getNextWord();
        hashTable[word]++;
    }
    // we iterate over the hash tables using iterators: it->first will give
    // us the key, it->second will give us the value. it++ moves to the
    // next (key, value) pair in the HashTable.
    typename HT<string, int>::iterator it;
    for( it = hashTable.begin(); it != hashTable.end(); it++ ) {
        if( it->second >= threshold ) ret.push_back( *it );
    }
    return ret;
}
