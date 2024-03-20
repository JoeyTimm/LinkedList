#include "Sequence.h"

Sequence::Sequence(size_type sz) : // general constructor
    head(nullptr),
    tail(nullptr),
    numElts(sz)
{
    if (sz > 0) {
        // link all the nodes together to maybe fix seg faults
        SequenceNode *currentNode = new SequenceNode(); // make new node
        head = currentNode;                             // set head to the new node
        for (int i = 0; i <= numElts; i++) {            // cycle through all nodes
            currentNode->next = new SequenceNode(); // allocate space for next node
            if (i == numElts - 1) { // check if need to make new node the tail
                tail = currentNode;
                tail->next = nullptr; // maybe change this back to currentNode if still having problems
                return;
            }
            SequenceNode *temp = currentNode; // hold place of current node so you can set the next nodes previous pointer to it
            currentNode = currentNode->next;  // set the current node equal to the next node in the sequence (which is now the new node instead of null)
            currentNode->prev = temp;         // now that currentNode is pointing to the next node, that nodes previous pointer can point to the temp from before
        }
    }
}

Sequence::Sequence(const Sequence &s) {
    head = tail = nullptr;
    numElts = 0;
    if (s.head != nullptr) {
        SequenceNode *toCopy = s.head; // make temporary node equal to head
        for (int i = 0; i < s.numElts; i++){ // loop through whole sequence
            push_back(toCopy->elt); // calls push back using the sequence
            toCopy = toCopy->next;  // move to next node
        }
    }
}

Sequence::~Sequence() { 
    if (head != nullptr) {
        SequenceNode *destroyMe = head;
        while (destroyMe != nullptr) {
            SequenceNode *destroyNext = destroyMe->next;
            delete destroyMe; //SOME KIND OF EXCEPTION HERE?
            destroyMe = destroyNext;
        }
    }
    head=nullptr;
    tail=nullptr;
    numElts=0;
}

Sequence &Sequence::operator=(const Sequence &s) { 
    if (head != nullptr) { //destroys the sequeunce that this is being called on
        SequenceNode *destroyMe = head;
        while (destroyMe != nullptr) {
            SequenceNode *destroyNext = destroyMe->next;
            delete destroyMe;
            destroyMe = destroyNext;
        }
        head = tail = nullptr;
        numElts = 0;
    }

    //actual copying part
    SequenceNode *toCopy = s.head; // make temporary node equal to head
    for (int i = 0; i < s.numElts; i++) {      // loop through whole sequence
        push_back(toCopy->elt); // calls push back using the sequence
        toCopy = toCopy->next;  // move to next node
    }    
    return *this;
}

Sequence::value_type &Sequence::operator[](size_type position) {
    SequenceNode *temp = new SequenceNode;
    temp = head;
    for (int i = 0; i < position + 1; i++) {
        if (i == position) {
            return temp->elt;
        }
        temp = temp->next;
    }
    throw exception();
}

void Sequence::push_back(const value_type &value) {
    SequenceNode *newNode = new SequenceNode(value); // make new node
    if (numElts == 0) { // if sequence is empty, make new node both head and tail
        head = newNode;
        tail = newNode;
    }
    else {
        SequenceNode *temp = tail; // make copy of tail
        newNode->prev = tail;      // set previous equal to the tail since this will be one after the tail
        tail->next = newNode;      // make the next value of the tail node equal to the new node
        tail = newNode;            // set tail of the sequence equal to the new node
    }
    numElts++; // increment number of elements
}

void Sequence::pop_back() { 
    if (numElts ==1){
        delete head;
        head = nullptr;
        tail = nullptr;
        numElts--;
        
    } else if (numElts==0){
        throw exception();
    } else {
    tail = tail->prev;    // make tail equal to the node before the tail
    delete tail->next;    // gets rid of the node so there are no memory leaks
    tail->next = nullptr; // make sure tail does not point to a next node
    numElts--;            // decrement number of elements
    }

}

void Sequence::insert(size_type position, value_type value) { 
    if (position >= numElts) { //throw exception if position not valid
        throw exception();
    } else if (position ==0){
        SequenceNode *newNode = new SequenceNode(value); 
        SequenceNode *newSecond = head;
        head=newNode; //set head equal to the new node
        head->next=newSecond; //set the heads next to point to the previous head
        newSecond->prev=head; //set the previous heads previous to point to the new head
        numElts++; //make sure to increment element total
    }else {
    SequenceNode *newNode = new SequenceNode(value);
    SequenceNode *current = head;
    for (int i = 0; i < position + 1; i++) { // cycle to the node after where we want our new node
        if (i == position) {         // when at the node after where we want ours...
            current->prev = newNode; // set that nodes previous to equal our new one
            newNode->next = current; // set our new nodes next to this node after ours
            current = head;          // reset current before panning through list again
            for (int k = 0; k < position; k++) { // then recycle to the node before our node
                if (k == position - 1) { // when at node before where we want ours
                    current->next = newNode; // make the node before ours point to our new one
                    newNode->prev = current; // make our new nodes previous point to the one before
                }
                current = current->next;
            }
        }
        current = current->next;
    }
    numElts++; // increment number of elements in list
    }
}

const Sequence::value_type &Sequence::front() const { // return first element
    if (head == nullptr){ //throw exception if no head
            throw exception();
    } else{
            return head->elt;
    }

}

const Sequence::value_type &Sequence::back() const { // return last element
    if (tail==nullptr){ //throw exception if no tail
        throw exception();
    } else{
        return tail->elt;
    }
    
}

bool Sequence::empty() const { // check if empty
    if (numElts == 0) {
        return true; // if empty return true
    } 
    else {
        return false;
    }
}

Sequence::size_type Sequence::size() const { // return seq size
    return numElts;
}

void Sequence::clear() { 
    if (head != nullptr) {
        SequenceNode *destroy = head;
        while (destroy != nullptr) {
            SequenceNode *destroyNext = destroy->next;
            delete destroy;
            destroy = destroyNext;
        }
    }
    head = nullptr;
    tail=nullptr;
    numElts=0;
}

void Sequence::erase(size_type position, size_type count) {
    if (position+count > numElts){ //make sure inputs are valid
        throw exception();
    } else if (position==0){ //for if erasing from first node forward/head will be deleted
        SequenceNode* deleteMe = head;
        for (int i=0; i<count; i++) {
                SequenceNode* deleteNext = deleteMe->next;
                delete deleteMe; 
                deleteMe = deleteNext;   
        }
        head=deleteMe;
    }
    else {
        SequenceNode* savePoint1 = head; 
        for (int i=0; i<position-1; i++){ //get first savePoint, which is the node before where we want to start deleting
            savePoint1=savePoint1->next;
        }
        SequenceNode* deleteMe = savePoint1->next;  //delete me will start after our save, or in other words the first node we want to delete
        for (int j=0; j<count; j++) {
                SequenceNode* deleteNext = deleteMe->next;
                delete deleteMe; 
                deleteMe = deleteNext;   
        }
            SequenceNode* savePoint2 = deleteMe; 
            savePoint1->next=savePoint2;
            if (savePoint2==nullptr){ //for if tail gets erased
                tail=savePoint1;
            } 
            else{
                savePoint2->prev=savePoint1;
            }
        numElts-=count;
    }
}

ostream &operator<<(ostream &os, const Sequence &s) {
    os << "< ";
    Sequence:: SequenceNode *current = s.head;
    while (current->next != nullptr) { //pan through sequence and add each node element to the output
        os << current->elt << ", ";
        current = current->next;
    }
    os << s.tail->elt << " >" << endl; //need to make sure to print tail since while loop stops at tail
    return os;
}