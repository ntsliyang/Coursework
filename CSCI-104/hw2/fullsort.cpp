#include <iostream>

struct Node
{
	int value;
	Node *next;
};

Node* fullsort(Node* );
Node* locate(Node*);
Node* remove(Node*, Node*, Node*);
Node* insert(Node*, Node*, Node*);

Node* fullsort(Node* in) {
	if(in == NULL || in->next == NULL) {
		return in; 
	}
	else {
		if (in != NULL) {
			if (in->next != NULL) {
				if (!in->next->next) {
					if (in->value > in->next->value) {
						int number = in->value;
						in->value = in->next->value;
						in->next->value = number;
						return in;
					}
				}
			}
		}
		Node* temp = locate(in);
		if (temp == NULL) return in;
		Node* h = remove(in, in, temp);
		// in is the head, while temp is the wrong node
		return insert(h, h, temp);
	}
}

Node* locate(Node* in) {
	if (in == NULL || in->next == NULL) return NULL;
	else {
		// 1 2 4 3 5
		// 3 2 
		// 1 2 3 4 5
		if (in->value > in->next->value && in->next->next == NULL) {
			int number = in->value;
			in->value = in->next->value;
			in->next->value = number;
			return NULL;
		}
		else if (in->next->next){
			if (in->value > in->next->value && in->value > in->next->next->value) {
			// 1 5 3 4 
			// 3 1 1 1 1
			return in;
			}
			else if (in->value < in->next->value && in->value > in->next->next->value) {
				// 1 3 4 2
				return in->next->next;
			}
			else if (in->value > in->next->value && in->value <= in->next->next->value) {
				// 1 2 4 3 5
				return in->next;
			}
		}
		return locate(in->next);
	}
}

Node* remove(Node* head, Node* in, Node* in2) {
	// in is the head, while in2 is the wrong node
	if (in2 == head) {
		// 2 1 3 4 5 
		// 1 2 5 4 5
		Node* tmp = in2->next;
		head = tmp;
		return head;
	}
	else if (!in) return NULL;
	else if (in->next == in2) {
		// 2 3 1 4 5
		in->next = in->next->next;
		return head;
	}
	return remove(head, in->next, in2);
}

Node* insert(Node* head, Node* h, Node* in2) {
	// h is the new head, in2 is the wrong node 
	// 1 2 5 4 5
	// 3 1 2 3 4 5
	if (h == NULL) return head;
	if (in2->value < h->value && h == head) {
		// 2 1 3 4 5
		// 2 3 1 4 5
		Node* tmp = head;
		in2->next = tmp;
		head = in2;
		return head;
	}
	else if (in2->value > h->value && h->next == NULL) {
		// 1 5 3 4
		// 3 1 1 1 1
		h->next = in2;
		in2->next = NULL;
		return head;
	}
	else if (h->next) {
		if (in2->value > h->value && in2->value <= h->next->value) {
			// 1 2 4 3 5
			Node* tmp = h->next;
			h->next = in2;
			in2->next = tmp;
			return head;
		}
	}
	return insert(head, h->next, in2);
}
