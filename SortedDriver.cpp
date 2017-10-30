//Jasmine Vaira 10/23/17
// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that 
//   process the sorted sequences.


#include "stdafx.h"
#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty; 
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	double lNeighbor = 0;	//distance from left neighbor
	double rNeighbor = 0;	//distance from right neighbor
	double nDistance = 0;	//distance from nearest neighbor
	double lastnDistance = 0;	//previous element's distance from nearest neighbor
	double mIso = number.front();	//most isolated number

	for (u_int i = 0; i < number.size(); i++)
	{
		
		if (i == 0)	//case for first element in vector
		{
			lNeighbor = 0;	//there is no left neighbor so we just set it to 0
			rNeighbor = abs(number.at(i) + number.at(i + 1));	//compute distance from right neighbor
		}
		else if (number.at(i) == number.back()) //case for last element in vector
		{
			lNeighbor = abs(number.at(i) - number.at(i - 1));	//compute distance from left neighbor
			rNeighbor = 0;	//there is no right neighbor so we just set it to 0
		}
		else	//for all items except the first and last items
		{
			lNeighbor = abs(number.at(i) - number.at(i - 1));	//compute distance from left neighbor
			rNeighbor = abs(number.at(i) + number.at(i + 1));	//compute distance from right neighbor
		}
		nDistance = min(lNeighbor, rNeighbor);	//compute distance from nearest neighbor
		if (nDistance > lastnDistance)
		{
			mIso = number.at(i);
		}
		lastnDistance = nDistance;
	}

	return mIso;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	int numDif = 0;		//number of words in A that don't occur in B
	int numSame = 0;	//number of words in A that also occur in B
	A.front();	//start at front of A
	B.front();	//start at front of B
	while (A.empty() == FALSE)	//while A not empty
	{
		while (B.empty() == FALSE)	//while B not empty
		{
			if (A.back() != B.back())
			{
				numDif++;	//increment different counter
			}
			else if (A.back() == B.back())
			{
				numSame++;	//increment same counter
			}
			B.pop_back();	//remove last element of B
		}
		A.pop_back();	//remove last element of B
	}
	numDif = abs(numSame - numDif);	//compute difference
	return numDif;	//return number of words occurring in A but not B
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}