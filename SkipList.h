#ifndef SkipList_h
#define SkipList_h

#include <iostream>

using namespace std;

/**
 * This is a struct that holds the information of each nodes. The pointers for the next
 * node are stored in an array.
 */
template<class T>
struct Node
{
	T item;		
	Node** next;	
	int level;		
	
	Node(T item, int level)	
	{
		this->item = item;			
		next = new Node*[level];
		this->level = level;		
	}
	
	~Node()		
	{
		delete[] next;
	}
};

/**
 * This is the skip list class. 
 */
template<class T>
class SkipList
{
	private:
		Node<T>* head;
		static const int MAXLEVEL = 2;	
		int length;
		int traversals;
		int comparisons;
	
		/**
		 * This function is a helper function for copy constructor and assignment operator. It makes
		 * a deep copy of the entire list from the source list.
		 */
		void deepCopy(Node<T>* &temp, Node<T>* &ptr);
	
		/**
		 * This is a helper function to iterate through the list in order to find an item. It returns
		 * a pointer.
		 */
		Node<T>* traverseHelper(Node<T>* ptr, const T val);
	
		/**
		 * This funciton generates a random number of either 1 or 2 in order to simulate a fair coin flip.
		 * The random number is used as a level of elements.
		 */
		int generateLevel();
	
		void deleteList(Node<T>* &head);
	
	public:
	
		/**
		 * This is the default constructor. It creates the head dummy node, and initializes some variables.
		 */
		SkipList();
	
		/**
		 * This is the copy constructor.
		 */
		SkipList(const SkipList<T> &source);
	
		/**
		 * This is the destructor.
		 */
		~SkipList();
	
		/**
		 * This is the overloaded assginment operator function. It makes a deep copy of the source list.
		 */
		SkipList& operator=(const SkipList<T> &source);
	
		/**
		 * This function inserts elements into the right position in order.
		 */
		void insert(const T &val);
	
		/**
		 * This function searches for a node that contains an item in search.
		 */
		bool search(const T &val);
	
		/**
		 * This functin returns the total number of traversals done in order to insert elements into the list.
		 */
		int getTraversals();
	
		/**
		 * This function return the number of comparisons made in order to search for an item in the list.
		 */
		int getComparisons();
	
		/**
		 * This function prints the list.
		 */
		void print();
	
		/**
		 * This function returns the length of the list.
		 */
		int getLength();
};

template<class T>
SkipList<T>::SkipList()
{
	head = new Node<T>(0, MAXLEVEL);
	for (int i = 0; i < MAXLEVEL; i++)	
		head->next[i] = nullptr;
	length = 0;
	traversals = 0;
	comparisons = 0;
}

template<class T>
SkipList<T>::SkipList(const SkipList<T> &source)	
{
	length = 0;
	head = new Node<T>(source.head->item, MAXLEVEL);
	for (int i = 0; i < MAXLEVEL; i++)
	{
		head->item = source.head->item;
		head->next[i] = source.head->next[i];
	}
	Node<T>* temp = head;
	Node<T>* ptr = source.head->next[0];
	deepCopy(temp, ptr);		
}

template<class T>
SkipList<T>::~SkipList()
{
	delete head;
}

template<class T>
SkipList<T>& SkipList<T>::operator=(const SkipList &source)	
{
	if (this != &source)	
	{
		length = 0;
		deleteList(head);	
		head = new Node<T>(source.head->item, MAXLEVEL);
		for (int i = 0; i < MAXLEVEL; i++)
		{
			head->item = source.head->item;
			head->next[i] = source.head->next[i];
		}
		Node<T>* temp = head;
		Node<T>* ptr = source.head->next[0];
		deepCopy(temp, ptr);	
	}
	return *this;
}

template<class T>
void SkipList<T>::insert(const T &val)
{
	int lev;
	Node<T>* ptr = head;
	Node<T>* update[MAXLEVEL];	
	
	for (int i = 0; i < MAXLEVEL; i++)
		update[i] = nullptr;
	for (int j = MAXLEVEL - 1; j >= 0; j--)	
	{
		while (ptr->next[j] != nullptr && ptr->next[j]->item < val)
		{							
			ptr = ptr->next[j];
			traversals++;
		}
		update[j] = ptr;	
	}
	ptr = ptr->next[0];
	traversals++;
	lev = generateLevel();		
	ptr = new Node<T>(val, lev);	
	for (int k = 0; k < lev; k++)	
	{
		ptr->next[k] = (*update)->next[k];
		(*update)->next[k] = ptr;
	}
	length++;
}

template<class T>
bool SkipList<T>::search(const T &val)
{
	bool found;
	Node<T>* ptr = head;
	
	ptr = traverseHelper(ptr, val);		
	if (ptr == nullptr || ptr->item > val)
	{
		comparisons++;		
		found = false;
	}
	else
	{
		comparisons++;
		found = true;
	}
	return found;
}


template<class T>
void SkipList<T>::deepCopy(Node<T>* &temp, Node<T>* &ptr)
{								
	while (ptr != nullptr)
	{
		temp = temp->next[0];
		temp = new Node<T>(ptr->item, ptr->level);
		for (int i = 0; i < ptr->level; i++)
			temp->next[i] = ptr->next[i];
		ptr = ptr->next[0];
		length++;
	}
}

template<class T>
Node<T>* SkipList<T>::traverseHelper(Node<T>* ptr, const T val)
{
	for (int i = MAXLEVEL - 1; i >= 0; i--)
	{
		while (ptr->next[i] != nullptr && ptr->next[i]->item < val)
		{
			comparisons++;
			ptr = ptr->next[i];
		}
	}
	ptr = ptr->next[0];
	return ptr;
}

template<class T>
int SkipList<T>::generateLevel()
{
	return rand() % 2 + 1;	
}

template<class T>
void SkipList<T>::print()	
{
	if (head->next[0] != nullptr)
	{
		Node<T>* ptr = head->next[0];
		while (ptr->next[0] != nullptr)
		{
			cout << ptr->item << " - ";
			ptr = ptr->next[0];
		}
		cout << ptr->item << endl;
	}
	else
		cout << "The list is empty" << endl;
}

template<class T>
int SkipList<T>::getTraversals()
{
	return traversals;
}

template<class T>
int SkipList<T>::getComparisons()
{
	return comparisons;
}

template<class T>
int SkipList<T>::getLength()
{
	return length;
}

template<class T>
void SkipList<T>::deleteList(Node<T>* &ptr)	
{
	while (ptr != nullptr)
	{
		Node<T>* deleteMe = ptr;
		ptr = ptr->next[0];
		delete deleteMe;
	}
}

#endif /* SkipList_h */
























