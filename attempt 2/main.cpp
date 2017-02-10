#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>
#include "SetList.h"
#include "MapArray.h"
#include <map>

using namespace std;

void test1a( SetList<string> w   )
{
//	cout << "called" << endl;
	if ( begin(w) == nullptr  )
		cout << "begin() is nullptr" << endl;
	for_each( begin(w), end(w) , [] ( string s) { cout << s  << endl; } );
}
void testFind( SetList<string> w )
{
	if ( w.find("has") != end(w) )
		cout << "Test 1 for find works" << endl;
	if ( w.find("the") != end(w) )
		cout << "Test 2 for find works" << endl;
	if ( w.find("wordnotpresent") == nullptr  )
		cout << "Test 3 for find works" << endl;
}

void test1b ( MapArray<string,int> m )
{
//	cout << "called" << endl;
	if ( m.begin() == nullptr)
		cout << "m.begin() is nullptr" << endl;
	if ( m.end() == nullptr )
		cout << "m.end() is nullptr" << endl;
	for_each( m.begin(), m.end(), 
	[] ( pair<string,int> P )
	{
		cout << P.first << "        " << P.second << endl;
	});
} 

string to_Lower( string & word)
{
	string returnStr = "";
	for_each( word.begin(), word.end(),
	[&] (char c)
	{
		returnStr += tolower(c);
	});
	return returnStr;
}

void testDec( MapArray<string,int> m )
{
	MapArray<string,int>::iterator p = m.begin();
	cout <<  p->first << endl;
	p++;
	cout << p->first << endl;
	p--;
	cout << p->first << endl;
} 

int main()
{
	ifstream stopFile;
	stopFile.open("stopwords.txt");
	SetList<string> stopWords;
	for_each( istream_iterator<string>(stopFile),
		  istream_iterator<string>(),
		  [&] ( string s ) { stopWords.insert(s); 
				     //cout << "added " << s << endl;
				   } );
	stopFile.close();
//	test1a( stopWords );
//	testFind( stopWords );

	ifstream testFile;
	testFile.open("sample_doc.txt");
	MapArray<string,int> words;
	for_each ( istream_iterator<string>(testFile),
		   istream_iterator<string>(),
		   [&] ( string s) 
		   {
//			cout << s << endl;
//			cout << "loop" << endl;
//			cout << "insert called" << endl;	
			string testStr = to_Lower(s);
		   	if (  testStr != "a" && stopWords.find(testStr) == stopWords.end() )
			{	
				if ( words.find(testStr) != words.end() )
				{
					words.increment(testStr);
				}
				else
				{
					words.insert ( make_pair( testStr, 1 ) ); 
				}
			}
		   }
		 );
	testFile.close();
//	test1b( words );
	
//	testDec( words );
	
	
	ofstream freqOutput;
	freqOutput.open("frequency.txt");
	for_each( words.begin(), words.end(), [&] ( pair<string,int> P) { freqOutput << P.first << "\t" << P.second << endl;  } );
	freqOutput.close(); 
	
	return 0;
}
