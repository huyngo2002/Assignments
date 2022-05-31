#include <string>
using namespace std;

class Node {
public:
	string Info;
	Node* pNext;
};

class Stack {
	Node* pHead;
public:
	Stack() {
		pHead = NULL;
	}

	~Stack() {
		Node* p;
		while (!IsEmpty())
		{
			p = pHead;
			pHead = p->pNext;
			delete p;
		}
	}

	bool IsEmpty() {
		return (pHead == NULL ? true : false);
	}

	Node* CreateNode(string x) {
		Node* p = new Node();
		p->Info = x;
		p->pNext = NULL;
		return p;
	}

	void Push(string x) {
		Node* p = CreateNode(x);
		if (IsEmpty()) {
			pHead = p;
		}
		else {
			p->pNext = pHead;
			pHead = p;
		}
	}

	bool Pop(string& x) {
		if (IsEmpty())
			return false;
		else {
			Node* p = pHead;
			x = p->Info;
			pHead = p->pNext;
			delete p;
		}
		return true;
	}

	Node* GetHead() {
		return pHead;
	}
};

