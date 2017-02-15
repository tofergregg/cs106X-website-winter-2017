/*********************************************************
 * File: OurStack.hh
 *
 * A class representing a stack that holds integers.
 */
#ifndef OurStack_Included
#define OurStack_Included

class OurStack {
public:
    OurStack(string str);
	~OurStack();

	bool isEmpty();
	
	void push(int value);
    int peek();
	int pop();

private:
    struct Node {
		int value;
        Node* next;
	};
	
    Node* head;
    //int size;
};


#endif
