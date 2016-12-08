/********** PART A *************/

DBTree::~DBTree() {
	for (int i = 0; i < 3; i++) {
		if(children[i] != NULL) {
			delete children[i];
		}
	}
}

/********** PART B *************/

// same as in the answer sheet

/********** PART C *************/

void DBTree::Remove(int value) {
	int index = -1;
    for (int i = 0; i < values.size(); i++) {
        if (values[i] == value) {
            values.removeAt(i)
            index = i;
            break;
        }
    }
    if (index != -1) {
        if (!IsLeaf()) {
            int childIndex = GetChildIndex();
            int promotedValue;
            if (childIndex > index)
                promotedValue = ExtractSmallest();
            else
                promotedValue = ExtractLargest();
            values[index] = promotedValue;
        }
    } else {
        int childIndex = GetChildIndexToFollow(value);
        if(children[childIndex] != NULL) {
        	children[childIndex]->remove(value);
        	if(children[childIndex]->values.isEmpty()) {
        		delete children[childIndex];
        		children[childIndex] =  NULL;
        	}
        }
    }
}

/********** PART D *************/

// same as in the answer sheet