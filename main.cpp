#include "SkipList.h"
#include <ctime>

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	unsigned int start = 0, stop = 0, result = 0;
	int n = 10000, find = 99, counter, comparisons, traversals, total;
	int resultArr[100];
	
	SkipList<int> list1;
	for (int i = 0; i < 20; i++)
		list1.insert(rand() % 100 + 1);
	cout << "list1 contains ==> ";
	list1.print();
	cout << "The length of list1 is " << list1.getLength() << endl;
	cout << "Searching for '" << find << "' in the list..." << endl;
	if (list1.search(find))
		cout << "The item " << find << " is in the list" << endl;
	else
		cout << "The item " << find << " is NOT in the list" << endl;
	cout << "The list10k made " << list1.getComparisons() << " comparisons to search for '99'" << endl;
	
	cout << "\nMaking a copy of list1 by copy constructor ==> ";
	SkipList<int> list2(list1);
	list2.print();
	
	cout << "\nMaking a copy of list1 by assignment operator ==> ";
	SkipList<int> list3;
	list3 = list1;
	list3.print();
	cout << endl;
	
	cout << "Now list10k is inserting 10,000 items ranging from 1 to 20,000 into the list..." << endl;

	counter = 0;
	comparisons = 0;
	traversals = 0;
	while (counter < 30)
	{
		SkipList<int> list10k;

		start = int(clock());
		for (int i = 0; i < n; i++)
			list10k.insert(rand() % 20000 + 1);
		stop = int(clock());
		
		result = stop - start;
		resultArr[counter] = result;
		list10k.search(find);
		comparisons += list10k.getComparisons();
		traversals += list10k.getTraversals();
		counter++;
	}
	for (int k = 0; k < 100; k++)
		total += resultArr[k];
	cout << "The time it took to insert " << n << " items is " << ((float)total) / 30 << " seconds " << endl;
	cout << "The average total number of traversals done for insertion is " << traversals / 30 << endl;
	cout << "The average total number of comparisons made to search for an item is " << comparisons / 30 << endl;
	
	
	return 0;
}









