#include <iostream>
#include <conio.h>
using namespace std;

class CDLLNode {
public:
	int info;
	CDLLNode *next;
	CDLLNode *prev;
	CDLLNode() {
		next = 0;
		prev = 0;
	}
	CDLLNode(int i, CDLLNode *n = 0, CDLLNode *p = 0) {
		info = i;
		next = n;
		prev = p;
	}
};

class CircularDoublyLinkedList {
protected:
	CDLLNode *head, *tail;
public:
	CircularDoublyLinkedList()
	{
		head = tail = 0;
	}
	~CircularDoublyLinkedList();
	void addToHead(int);
	void addToTail(int);
	int deleteFromHead();
	int deleteFromTail();
	void deleteNode(int);
	void printList();
	bool isEmpty()
	{
		return head == 0;
	}
	bool isInList(int);
	void reverse();
};

CircularDoublyLinkedList::~CircularDoublyLinkedList()
{
	if (!isEmpty())
	{
		CDLLNode *tmp = tail;
		CDLLNode *tmp_;
		do {
			tmp_ = tmp;
			tmp = tmp->next;
			delete tmp_;
		} while (tmp != tail);
		tail = 0;
	}
}

void CircularDoublyLinkedList::addToHead(int el)
{
	if (head == 0)
	{
		head = tail = new CDLLNode(el, head, head);
	}
	else
	{
		head->prev = new CDLLNode(el, head, tail);
		tail->next = head->prev;
		head = head->prev;
	}
}

void CircularDoublyLinkedList::addToTail(int el)
{
	if (tail == 0)
	{
		head = tail = new CDLLNode(el, tail, tail);
	}
	else
	{
		tail->next = new CDLLNode(el, head, tail);
		head->prev = tail->next;
		tail = tail->next;
	}
}

int CircularDoublyLinkedList::deleteFromHead()
{
	if (!isEmpty())
	{
		int info;

		if (head == tail)
		{
			info = head->info;
			delete head;
			head = tail = 0;
		}
		else
		{
			CDLLNode *tmp = head;
			info = tmp->info;
			tail->next = tmp->next;
			tmp->next->prev = tail;
			head = tmp->next;
			delete tmp;
			tmp = 0;
		}

		return info;
	}
	return -1;
}

int CircularDoublyLinkedList::deleteFromTail()
{
	if (!isEmpty())
	{
		int info;

		if (head == tail)
		{
			info = tail->info;
			delete tail;
			head = tail = 0;
		}
		else
		{
			CDLLNode *tmp = tail;
			info = tmp->info;
			tmp->prev->next = head;
			head->prev = tmp->prev;
			delete tmp;
			tmp = 0;
		}
		return info;
	}
	return -1;
}

void CircularDoublyLinkedList::deleteNode(int el)
{
	if (!isEmpty())
	{
		if (head == tail)
		{
			delete head;
			head = tail = 0;
		}
		else if (head->info == el)
		{
			CDLLNode *tmp = head;
			tail->next = tmp->next;
			tmp->next->prev = tail;
			head = tmp->next;
			delete tmp;
			tmp = 0;
		}
		else if (tail->info == el)
		{
			CDLLNode *tmp = tail;
			tmp->prev->next = head;
			head->prev = tmp->prev;
			delete tmp;
			tmp = 0;
		}
		else
		{
			CDLLNode *tmp = head;
			for (tmp; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
			if (tmp != 0)
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				delete tmp;
				tmp = 0;
			}
		}
	}
}

void CircularDoublyLinkedList::printList()
{
	if (!isEmpty() && head != tail)
	{
		CDLLNode *tmp = head;
		do
		{
			cout << tmp->info << " ";
			tmp = tmp->next;
		} while (tmp != head);
		cout << endl;
	}

	else if (head == tail)
	{
		cout << head->info << " " << endl;
	}
}

bool CircularDoublyLinkedList::isInList(int el)
{
	CDLLNode *tmp;
	for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
	return tmp != 0;
}

void CircularDoublyLinkedList::reverse()
{
	if (head != tail) {
		CDLLNode *temp = head;
		head = tail;
		tail = temp;
		CDLLNode *temp2;
		do
		{
			temp2 = temp->next;
			temp->next = temp->prev;
			temp->prev = temp2;
			temp = temp->next;
		} while (temp != tail);
	}
	else {
		return;
	}
}

int main()
{
	cout << "Circular Doubly Linked List" << endl;
	cout << "--------------------------------------" << endl;
	CircularDoublyLinkedList list;
	list.addToHead(1);
	list.addToHead(2);
	list.addToHead(3);
	list.addToHead(4);
	list.addToHead(5);
	list.addToTail(6);
	list.addToTail(7);
	cout << "Current list: "; list.printList();
	list.reverse();
	cout << "After reversing: "; list.printList();
	list.addToHead(3);
	list.addToHead(4);
	cout << "Adding to head: "; list.printList();
	list.addToTail(5);
	list.addToTail(6);
	cout << "Adding to tail: "; list.printList();
	list.reverse();
	cout << "After reversing: "; list.printList();
	list.deleteFromHead();
	cout << "Deleting from head: "; list.printList();
	list.deleteFromTail();
	cout << "Deleting from tail: "; list.printList();
	list.deleteNode(2);
	cout << "Deleting '2': "; list.printList();
	cout << "Finding '3': "; (list.isInList(3)) ? (cout << "true") : (cout << "false");

	_getch();
	return 0;
}