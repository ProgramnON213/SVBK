#include <iostream>
using namespace std;

class LLNode{
public:
int val;
LLNode* next;
LLNode();
LLNode(int val, LLNode* next);
};

LLNode::LLNode() : val(0), next(nullptr) {}
LLNode::LLNode(int val, LLNode* next) : val(val), next(next) {}

int getValue(LLNode* list) {
    if (list == nullptr) {return 0;}
    return list->val + getValue(list->next) * 10;
}

LLNode* createList(int n) {
    if (n == 0) {return 0;}
    LLNode* head = new LLNode;
    LLNode* tail = head;

    while (n != 0) {
        tail->val = n % 10;
        tail->next = nullptr;
        n /= 10;
        if (n != 0) {
            tail->next = new LLNode;
            tail = tail->next;
        }
    }

    return head;
}

LLNode* addLinkedList(LLNode* l0, LLNode* l1) {
    return createList(getValue(l0) + getValue(l1));
}

// --- Các hàm hỗ trợ kiểm thử ---

// Hàm tạo danh sách từ mảng để set up test case nhanh gọn
LLNode* createList(int arr[], int size) {
    if (size == 0) return nullptr;
    LLNode* head = new LLNode(arr[0], nullptr);
    LLNode* curr = head;
    for (int i = 1; i < size; ++i) {
        curr->next = new LLNode(arr[i], nullptr);
        curr = curr->next;
    }
    return head;
}

// Hàm in danh sách
void printList(LLNode* head) {
    cout << "[";
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) cout << ", ";
        head = head->next;
    }
    cout << "]\n";
}

// Hàm dọn dẹp bộ nhớ
void freeList(LLNode* head) {
    while (head != nullptr) {
        LLNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// --- Hàm Main ---
int main() {
    // ========================================================
    // Test Case 1: Giống ví dụ của đề bài
    // l0 = [2, 3] (đại diện số 32)
    // l1 = [1, 8] (đại diện số 81)
    // Kỳ vọng: 32 + 81 = 113 -> [3, 1, 1]
    // ========================================================
    int arr0[] = {2, 3};
    int arr1[] = {1, 8};

    LLNode* l0 = createList(arr0, 2);
    LLNode* l1 = createList(arr1, 2);

    cout << "--- Test 1 ---" << endl;
    cout << "Danh sach l0: "; printList(l0);
    cout << "Danh sach l1: "; printList(l1);

    LLNode* result1 = addLinkedList(l0, l1);

    cout << "Ket qua l0 + l1: "; printList(result1); cout << endl;


    // ========================================================
    // Test Case 2: Độ dài hai danh sách khác nhau và có nhớ liên tục
    // l0 = [9, 9, 9] (đại diện số 999)
    // l1 = [1]       (đại diện số 1)
    // Kỳ vọng: 999 + 1 = 1000 -> [0, 0, 0, 1]
    // ========================================================
    int arr2[] = {9, 9, 9};
    int arr3[] = {1};

    LLNode* l2 = createList(arr2, 3);
    LLNode* l3 = createList(arr3, 1);

    cout << "--- Test 2 ---" << endl;
    cout << "Danh sach l0: "; printList(l2);
    cout << "Danh sach l1: "; printList(l3);

    LLNode* result2 = addLinkedList(l2, l3);

    cout << "Ket qua l0 + l1: "; printList(result2); cout << endl;

    // Dọn dẹp bộ nhớ
    freeList(l0); freeList(l1); freeList(result1);
    freeList(l2); freeList(l3); freeList(result2);

    return 0;
}