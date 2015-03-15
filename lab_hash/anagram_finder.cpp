/**
 * @file anagram_finder.cpp
 * Implementation of the AnagramFinder class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "anagram_finder.h"

using std::string;
using std::vector;
using std::ofstream;
using std::endl;

/**
 * Constructs an AnagramFinder based on a filename to read potential
 * anagrams from.
 *
 * @param ifilename The name of the file to read in.
 */
template <template <class K, class V> class HT>
AnagramFinder<HT>::AnagramFinder( const string & ifilename ) : file( true ), 
        filename( ifilename ) {
    /* nothing */
}

/**
 * Constructs an AnagramFinder based on a set of strings instead of a
 * filename.
 *
 * @param istrings The set of strings to use for this finder.
 */
template <template <class K, class V> class HT>
AnagramFinder<HT>::AnagramFinder( const vector<string> & istrings ) : file( false ),
        strings( istrings ) {
    /* nothing */
}

/**
 * Determines if the given word is an anagram of the test word.
 *
 * @param word Word that is possibly an anagram.
 * @param test Word to check against.
 * @return A boolean value indicating whether word is an anagram of test.
 */
template <template <class K, class V> class HT>
bool AnagramFinder<HT>::checkWord( const string & word, const string & test ) {
    /**
     * @todo Implement this function! You should use the provided
     * templated hashtable class HT.
     */
    HT<char, int> table_1(256);
    HT<char, int> table_2(256);
    
    for(int i=0; i<word.length(); i++)
    {
        table_1[word[i]]++;
    }

    for(int i=0; i<test.length(); i++)
    {
        table_2[test[i]]++;
    }
    
	vector< pair<char, int> > vect1;
	vector< pair<char, int> > vect2;
	typename HT<char, int>::iterator it;
	for( it = table_1.begin(); it != table_1.end(); it++ ) {
        vect1.push_back( *it );
    }
	for( it = table_2.begin(); it != table_2.end(); it++ ) {
        vect2.push_back( *it );
    }

    return (vect1==vect2);
}

/**
 * Retrieves a set of words that are anagrams of a given word.
 *
 * @param word The word we wish to find anagrams of inside the finder.
 */
template <template <class K, class V> class HT>
vector<string> AnagramFinder<HT>::getAnagrams( const string & word ) {
    // set up the return vector
    vector<string> ret;

    if( file ) {
        TextFile infile( filename );
        string line;
        vector<string> tests;
        while( infile.good() ) {
            string test = infile.getNextWord();
            if( checkWord( word, test ) ) 
                ret.push_back( test );
        }
    } else {
        for( size_t i = 0; i < strings.size(); i++ ) {
            if( checkWord( word, strings[i] ) )
                ret.push_back( strings[i] );
        }
    }
    return ret;
}

/**
 * Retrieves a set of anagrams in the finder of a given words, but writes
 * them out to a file instead of returning a vector.
 *
 * @param word The word we wish to find anagrams of inside the finder.
 * @param output_file The name of the file we want to write to.
 */
template <template <class K, class V> class HT>
void AnagramFinder<HT>::writeAnagrams( const string & word, 
        const string & output_file ) {
    vector<string> anagrams = getAnagrams( word );
    ofstream outfile(output_file.c_str());
    if( outfile.is_open() ) {
        for( size_t i = 0; i < anagrams.size(); i++ )
            outfile << anagrams[i] << endl;
    }
    outfile.close();
}
