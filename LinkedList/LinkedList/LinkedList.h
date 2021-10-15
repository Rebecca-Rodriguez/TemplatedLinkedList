#pragma once
#include <iostream>
#include <exception>
#include <vector>
using namespace std;

template <typename T>
class LinkedList
{
public:
	// Nested Class
	struct Node
	{
		T data;					// the data being stored
		Node* next;				// pointer to the next node
		Node* prev;				// the pointer to the previous node
		// Ensure next and previous are nullptr by default
		Node()
		{
			next = nullptr;
			prev = nullptr;
		}
	};

	// Default Constructor
	LinkedList();

	// Copy Constructor
	LinkedList(const LinkedList<T>& list);

	// Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	// Removal
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();

	// Accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	// Behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* mode) const;
	void PrintReverseRecursive(const Node* mode) const;

	// Operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Destructor
	~LinkedList();

private:
	Node* head;					// Node pointer for the head
	Node* tail;					// Node pointer for the tail
	unsigned int _count;			// counting nodes in list
};

// ========================== CLASS DECLARATIONS & FUNCTION DEFINITIONS ========================== //

template <typename T>
LinkedList<T>::LinkedList()
{
	// Default Constructor
	_count = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	// Copy Constructor
	this->_count = 0;
	this->head = nullptr;
	this->tail = nullptr;

	Node* copy = list.head;
	while (copy != nullptr)
	{
		AddTail(copy->data);
		copy = copy->next;
	}
}

template <typename T>
void LinkedList<T>::AddHead(const T& data)
{
	Node* temp = new Node;				// Create a new node
	temp->data = data;					// assign data being passed in to the node
	temp->next = nullptr;				// set the "next" to null
	temp->prev = nullptr;				// set the "prev" to null

	if (head == nullptr)				// if there is no head
	{
		head = temp;					// basically makes a list of just this node
		tail = temp;
		head->next = nullptr;
		head->prev = nullptr;
	}
	else
	{
		head->prev = temp;
		if (_count == 1)
		{
			tail->prev = temp;
		}
		temp->next = head;				// if there is a head, set the current head as next
		head = temp;					// set the temp as the head
	}
	_count++;							// increase the number of nodes
}

template <typename T>
void LinkedList<T>::AddTail(const T& data)
{
	Node* temp = new Node;				// Create a new node
	temp->data = data;					// assign data being passed in to the node
	temp->next = nullptr;				// set the "next" to null
	temp->prev = nullptr;				// set the "prev" to null

	if (tail == nullptr)				// if there is no tail
	{
		head = temp;					// basically makes a list of just this node
		tail = temp;
		tail->next = nullptr;
		tail->prev = nullptr;
	}
	else
	{
		tail->next = temp;
		if (_count == 1)
		{
			head->next = temp;
		}
		temp->prev = tail;				// if there is a tail, set the current tail as previous
		temp->next = nullptr;
		tail = temp;					// set the temp as the tail
		temp = nullptr;
	}
	_count++;							// increase the number of nodes
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count)
{
	int j = (int)count - 1;
	for (int i = j; 0 <= i; i--)
	{
		AddHead(data[i]);
	}
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		AddTail(data[i]);
	}
}

template <typename T>
void  LinkedList<T>::InsertAfter(Node* node, const T& data)
{
	// Given a pointer to a node, create a new node to store the passed in value,
	// after the indicated node.

	Node* temp = new Node;
	temp->data = data;
	temp->prev = node;
	temp->next = node->next;

	node->next->prev = temp;
	node->next = temp;
	_count++;
}

template <typename T>
void  LinkedList<T>::InsertBefore(Node* node, const T& data)
{
	// Ditto, except insert the new node before the indicated node.

	Node* temp = new Node;
	temp->data = data;
	temp->next = node;
	temp->prev = node->prev;

	node->prev->next = temp;
	node->prev = temp;
	_count++;
}

template <typename T>
void  LinkedList<T>::InsertAt(const T& data, unsigned int index)
{
	// Inserts a new Node to store the first parameter, at the index-th location.
	// So if you specified 3 as the index, the new Node should have 3 Nodes before it.
	// Throws an out_of_range exception if given an invalid index.

	if (index > _count)
	{
		throw out_of_range("Bad index");
	}
	else if (index == _count)
	{
		Node* temp = new Node;
		temp->data = data;
		tail->next = temp;
		temp->prev = tail;
		temp->next = nullptr;
		tail = temp;

		_count++;
	}
	else
	{
		Node* temp = new Node;
		unsigned int countIndex = 0;
		temp->data = data;

		Node* ptr = Head();

		while (countIndex != index)
		{
			ptr = ptr->next;
			countIndex++;
		}
		// Update the new node's attributes
		temp->prev = ptr->prev;
		temp->next = ptr;

		//Update the adjacent Nodes
		if (ptr->prev != nullptr)
		{
			ptr->prev->next = temp;
		}
		else
		{
			head = temp;
		}

		// Update the old node at i'th position
		ptr->prev = temp;

		_count++;
	}
}

template <typename T>
bool LinkedList<T>::RemoveHead()
{
	// Deletes the first Node in the list. Returns whether or not the Node was removed.

	if (head == nullptr)
	{
		return false;
	}
	else if (head->next == nullptr)
	{
		Node* temp = head;
		delete temp;
		head = nullptr;
		tail = nullptr;
		_count--;
		return true;
	}
	else
	{
		Node* temp = head;
		head->next->prev = nullptr;
		head = head->next;
		delete temp;
		_count--;
		return true;
	}
}

template <typename T>
bool LinkedList<T>::RemoveTail()
{
	// Deletes the last Node, returning whether or not the operation was successful.

	if (tail == nullptr)
	{
		return false;
	}
	else if (tail->prev == nullptr)
	{
		Node* temp = tail;
		delete temp;
		tail = nullptr;
		head = nullptr;
		_count--;
		return true;
	}
	else
	{
		Node* temp = tail;
		tail->prev->next = nullptr;
		tail = tail->prev;
		delete temp;
		_count--;
		return true;
	}
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data)
{
	// Remove ALL Nodes containing values matching that of the passed - in parameter.
	// Returns how many instances were removed.

	unsigned int elementRemoved = 0;
	Node* temp = head;
	Node* ptr;

	while (temp != nullptr)
	{
		ptr = temp->next;
		if (temp->data == data)
		{
			if (temp->prev == nullptr)
			{
				temp->next->prev = nullptr;
			}
			else if (temp->next == nullptr)
			{
				temp->prev->next = nullptr;
			}
			else
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			delete temp;
			elementRemoved++;
		}
		temp = ptr;
	}
	_count -= elementRemoved;
	return elementRemoved;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
	// Deletes the index-th Node from the list, returning whether or not the operation
	// was successful.

	if (index > _count)
	{
		return false;
	}
	else
	{
		Node* temp = Head();
		unsigned int indexCount = 0;

		while (indexCount != index)
		{
			temp = temp->next;
			indexCount++;
		}
		if (temp->prev == nullptr)
		{
			temp->next->prev = nullptr;
		}
		else if (temp->next == nullptr)
		{
			temp->prev->next = nullptr;
		}
		else
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
		}
		delete temp;
		_count--;
		return true;
	}
}

template <typename T>
void LinkedList<T>::Clear()
{
	// Deletes all Nodes. Don't forget the node count—how many nodes do you have after
	// you deleted all of them?

	Node* ptr = head;
	Node* temp;
	while (ptr != nullptr)
	{
		temp = ptr->next;
		delete ptr;
		ptr = temp;
	}
	head = nullptr;
	tail = nullptr;						// set tail to null
	_count = 0;							// reset node count
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const
{
	return _count;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
	// Find all nodes which match the passed in parameter value, and store a pointer to
	// that node in the passed in vector. Use of a parameter like this (passing a
	// something in by reference, and storing data for later use) is called an output
	// parameter.
	Node* temp = head;

	while (temp != nullptr)
	{
		if (temp->data == value)
		{
			outData.push_back(temp);
		}
		temp = temp->next;
	}
	temp = nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const
{
	Node* temp = head;

	while (temp != nullptr)
	{
		if (temp->data == data)				// if data value matches the pass in parameter
		{
			return temp;					// retrun pointer to that node
		}

		temp = temp->next;					// go to the "next" in list
	}
	return nullptr;							// Returns nullptr if no matching node found
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
	Node* temp = head;

	while (temp != nullptr)
	{
		if (temp->data == data)				// if data value matches the pass in parameter
		{
			return temp;					// retrun pointer to that node
		}

		temp = temp->next;					// go to the "next" in list
	}
	return nullptr;							// Returns nullptr if no matching node found
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
	// Given an index, return a pointer to the node at that index. Throws an exception
	// of type out_of_range if the index is out of range. Const and non-const versions.
	if (index >= _count)
	{
		throw out_of_range("Bad index");
	}
	else
	{
		unsigned int indexCounter = 0;
		Node* temp = head;
		while (indexCounter != index)
		{
			temp = temp->next;
			indexCounter++;
		}
		return temp;
	}
}

// CHECK THIS
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
	if (index >= _count)
	{
		throw out_of_range("Bad index");
	}
	else
	{
		unsigned int indexCounter = 0;
		Node* temp = head;
		while (indexCounter != index)
		{
			temp = temp->next;
			indexCounter++;
		}
		return temp;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
	// Returns the head pointer. Const and non-const versions.
	return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
	return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
	// Returns the tail pointer. Const and non-const versions.
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
	return tail;
}

template <typename T>
void LinkedList<T>::PrintForward() const
{
	Node* temp = head;
	while (temp != nullptr)				// Iterator through all of the nodes and print out their values, one a time.
	{
		cout << temp->data << endl;
		temp = temp->next;
	}
	delete temp;
	temp = nullptr;
}

template <typename T>
void LinkedList<T>::PrintReverse() const
{
	Node* temp = tail;
	while (temp != nullptr)
	{
		cout << temp->data << endl;
		temp = temp->prev;
	}
	delete temp;
	temp = nullptr;
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* mode) const
{
	// This function takes in a pointer to a Node—a starting node. From that node,
	// recursively visit each node that follows, in forward order, and print their
	// values. This function MUST be implemented using recursion, or tests using it
	// will be worth no points. Check your textbook for a reference on recursion.

	if (mode == nullptr)
	{
		return;
	}
	cout << mode->data << endl;
	PrintForwardRecursive(mode->next);
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* mode) const
{
	// Reverse previous function

	if (mode == nullptr)
	{
		return;
	}
	cout << mode->data << endl;
	PrintReverseRecursive(mode->prev);
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
	// Overloaded subscript operator. Takes an index, and returns data from the
	// index-th node. Throws an out_of_range exception for an invalid index.
	// Const and non-const versions.

	if (index >= _count)
	{
		throw out_of_range("Bad index");
	}
	else
	{
		unsigned int indexCounter = 0;
		Node* temp = head;

		while (indexCounter != 0)
		{
			temp = temp->next;
			indexCounter++;
		}
		return temp->data;
	}
}


template <typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
	if (index >= _count)
	{
		throw out_of_range("Bad index");
	}
	else
	{
		unsigned int indexCounter = 0;
		Node* temp = head;

		while (indexCounter != 0)
		{
			temp = temp->next;
			indexCounter++;
		}
		return temp->data;
	}
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	// Overloaded equality operator. Given listA and listB, is listA equal to listB?
	// What would make one Linked List equal to another? If each of its nodes were
	// equal to the corresponding node of the other. (Similar to comparing two arrays,
	// just with non-contiguous data).
	Node* temp = head;
	bool isEqual = true;

	if (_count != rhs._count)
	{
		return false;
	}
	for (unsigned int i = 0; i < _count; i++)
	{
		if (temp->data != rhs.GetNode(i)->data)
		{
			isEqual = false;
		}
		temp = temp->next;
	}
	delete temp;
	temp = nullptr;
	return isEqual;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
	// Assignment operator. After listA = listB, listA == listB is true.
	// Can you utilize any of your existing functions to make write this one?
	// (Hint: Yes you can.)

	_count = 0;
	Clear();

	if (rhs._count > 0)
	{
		for (unsigned int i = 0; i < rhs._count; i++)
		{
			AddTail(rhs.GetNode(i)->data);
		}
	}

	return *this;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	// Destructor
	Clear();
}