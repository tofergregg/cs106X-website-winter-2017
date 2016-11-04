#include "ourStack.h"
#include "error.h"

OurStack::OurStack() {
	head = NULL;
}

bool OurStack::isEmpty() {
	return head == NULL;
}

void OurStack::push(int value) {
    Node* node = new Node;
    // pushing "value"
    node->value = value;

    node->next = head;

    head = node;
}

int OurStack::peek() {
	if (isEmpty()) {
        throw "Why did you do that?  That makes bunnies sad.";
	}
	
	return head->value;
}

int OurStack::pop() {
	if (isEmpty()) {
        throw "Why did you do that?  That makes bunnies sad.";
	}
	
    Node* result = head;
	head = head->next;

	int value = result->value;
	delete result;
	return value;
}

OurStack::~OurStack() {
    while (head != NULL) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

