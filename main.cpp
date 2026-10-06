#include "list.h"

// Check if the list is empty
bool isEmpty(Node* head) {
    return head == nullptr;
}

// Push element to the head
void pushHead(Node*& head, int value, int& ptrMoves) {
    Node* newNode = new Node{ value, nullptr };
    ptrMoves++;

    if (isEmpty(head)) {
        newNode->next = newNode;
        ptrMoves++;
        head = newNode;
        ptrMoves++;
        return;
    }

    Node* tail = head;
    ptrMoves++;

    while (tail->next != head) {
        ptrMoves++;
        tail = tail->next;
        ptrMoves++;
    }
    ptrMoves++;

    newNode->next = head;
    ptrMoves++;
    tail->next = newNode;
    ptrMoves++;
    head = newNode;
    ptrMoves++;
}

// Push element to the tail
void pushTail(Node*& head, int value, int& ptrMoves) {
    Node* newNode = new Node{ value, nullptr };
    ptrMoves++;

    if (isEmpty(head)) {
        newNode->next = newNode;
        ptrMoves++;
        head = newNode;
        ptrMoves++;
        return;
    }

    Node* tail = head;
    ptrMoves++;

    while (tail->next != head) {
        ptrMoves++;
        tail = tail->next;
        ptrMoves++;
    }
    ptrMoves++;

    newNode->next = head;
    ptrMoves++;
    tail->next = newNode;
    ptrMoves++;
}

// Get total length of the circular list
int getLength(Node* head) {
    if (isEmpty(head)) return 0;
    int length = 0;
    Node* curr = head;
    do {
        length++;
        curr = curr->next;
    } while (curr != head);
    return length;
}

// Print elements in the list
void printList(Node* head) {
    if (isEmpty(head)) {
        cout << "List is empty [ ] (Length: 0)\n";
        return;
    }

    cout << "  ";
    Node* curr = head;
    do {
        cout << curr->data << " ";
        curr = curr->next;
    } while (curr != head);
    cout << "  (Length: " << getLength(head) << ")\n";
}

// Free allocated memory
void freeList(Node*& head) {
    if (isEmpty(head)) return;

    Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }
    tail->next = nullptr;

    Node* curr = head;
    Node* nextNode = nullptr;
    while (curr != nullptr) {
        nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    head = nullptr;
}

//  TASK A: Delete first and last occurrence of element E 
int taskA(Node*& head, int E) {
    int ptrMoves = 0;
    if (isEmpty(head)) return ptrMoves;

    Node* firstPrev = nullptr;
    Node* firstNode = nullptr;
    Node* lastPrev = nullptr;
    Node* lastNode = nullptr;

    Node* tail = head;
    ptrMoves++;
    while (tail->next != head) {
        ptrMoves++;
        tail = tail->next;
        ptrMoves++;
    }
    ptrMoves++;

    Node* prev = tail;
    Node* curr = head;
    ptrMoves += 2;

    do {
        ptrMoves++;
        if (curr->data == E) {
            if (firstNode == nullptr) {
                firstNode = curr;
                firstPrev = prev;
                ptrMoves += 2;
            }
            lastNode = curr;
            lastPrev = prev;
            ptrMoves += 2;
        }
        prev = curr;
        curr = curr->next;
        ptrMoves += 2;
    } while (curr != head);
    ptrMoves++;

    if (firstNode == nullptr) return ptrMoves;

    auto removeNode = [&](Node* pNode, Node* targetNode) {
        if (head == nullptr) return;

        if (head->next == head && head == targetNode) {
            delete head;
            head = nullptr;
            ptrMoves += 2;
            return;
        }

        pNode->next = targetNode->next;
        ptrMoves++;

        if (targetNode == head) {
            head = targetNode->next;
            ptrMoves++;
        }

        delete targetNode;
        };

    if (firstNode == lastNode) {
        removeNode(firstPrev, firstNode);
    }
    else {
        removeNode(lastPrev, lastNode);
        if (firstPrev == lastNode) {
            firstPrev = lastPrev;
            ptrMoves++;
        }
        removeNode(firstPrev, firstNode);
    }

    return ptrMoves;
}

// TASK B: Move maximum element to head 
int taskB(Node*& head) {
    int ptrMoves = 0;
    if (isEmpty(head) || head->next == head) return ptrMoves;

    Node* tail = head;
    ptrMoves++;
    while (tail->next != head) {
        ptrMoves++;
        tail = tail->next;
        ptrMoves++;
    }
    ptrMoves++;

    Node* maxNode = head;
    Node* maxPrev = tail;
    ptrMoves += 2;

    Node* prev = head;
    Node* curr = head->next;
    ptrMoves += 2;

    while (curr != head) {
        ptrMoves++;
        if (curr->data > maxNode->data) {
            maxNode = curr;
            maxPrev = prev;
            ptrMoves += 2;
        }
        prev = curr;
        curr = curr->next;
        ptrMoves += 2;
    }
    ptrMoves++;

    if (maxNode == head) return ptrMoves;

    maxPrev->next = maxNode->next;
    ptrMoves++;

    maxNode->next = head;
    ptrMoves++;

    tail->next = maxNode;
    ptrMoves++;

    head = maxNode;
    ptrMoves++;

    return ptrMoves;
}

// TASK C: Recursively count nodes
int countNodesRecursive(Node* curr, Node* head, int& ptrMoves) {
    ptrMoves++;
    if (curr == nullptr) return 0;

    ptrMoves++;
    if (curr->next == head) {
        return 1;
    }

    ptrMoves++;
    return 1 + countNodesRecursive(curr->next, head, ptrMoves);
}

int taskC(Node* head, int& nodeCount) {
    int ptrMoves = 0;
    if (isEmpty(head)) {
        nodeCount = 0;
        return ptrMoves;
    }
    nodeCount = countNodesRecursive(head, head, ptrMoves);
    return ptrMoves;
}

int main() {
    Node* list = nullptr;
    int dummyPtr = 0;

    // Populate initial list: [ 5, 3, 9, 3, 7, 3, 1 ]
    pushTail(list, 5, dummyPtr);
    pushTail(list, 3, dummyPtr);
    pushTail(list, 9, dummyPtr);
    pushTail(list, 3, dummyPtr);
    pushTail(list, 7, dummyPtr);
    pushTail(list, 3, dummyPtr);
    pushTail(list, 1, dummyPtr);

    cout << " INITIAL LIST \n";
    printList(list);

    // Task A: Remove first & last E=3
    int movesA = taskA(list, 3);
    cout << "Task A (Remove first & last E=3)\n";
    printList(list);
    cout << "\n";

    // Task B: Move max (9) to head
    int movesB = taskB(list);
    cout << " Task B (Move max to head) \n";
    printList(list);
    cout << "\n";

    // Task C: Recursive count
    int countC = 0;
    int movesC = taskC(list, countC);
    cout << "Task C(Recursive count) \n";
    cout << "Counted nodes: " << countC << "\n";
    printList(list);
    cout << "\n";

    // Pointer Moves Table Output
    cout << "                 POINTER MOVES TABLE\n";
    cout << "| Task   | Task Description                         | Pointer Moves |\n";
    cout << "|--------|------------------------------------------|---------------|\n";
    cout << "| Task A | Delete first & last occurrence of E      | " << movesA << "            |\n";
    cout << "| Task B | Move maximum element to head             | " << movesB << "            |\n";
    cout << "| Task C | Recursively count nodes in list          | " << movesC << "            |\n";

    freeList(list);
    return 0;
}