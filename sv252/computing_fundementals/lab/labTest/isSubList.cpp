#include <iostream>
using namespace std;

struct Node{
int data;
Node* next;
};
struct LList{
Node* head;
};

int getLength(const LList& list) {
    Node* cur = list.head;
    int count = 0;
    while (cur != nullptr) {
        count++;
        cur = cur->next;
    }
    return count;
}

bool find(LList list, int n) {
    Node* cur = list.head;
    while (cur != nullptr) {
        if (cur->data == n) {return true;}
        cur = cur->next;
    }
    return false;
}

int isSublist(const LList& list1, const LList& list2) {
    LList small;
    LList big;
    if (getLength(list1) < getLength(list2)) {
        small = list1;
        big = list2;
    }
    else {
        small = list2;
        big = list1;
    }

    if (getLength(small) == 0) {return 0;}
    Node* cur = small.head;
    while (cur != nullptr) {
        if (!find(big, cur->data)) {return -1;}
        cur = cur->next;
    }

    return getLength(small);
}

// --- Các hàm hỗ trợ cho việc kiểm thử (không bắt buộc trong bài làm) ---
void append(LList& list, int val) {
    Node* newNode = new Node{val, nullptr};
    if (list.head == nullptr) {
        list.head = newNode;
        return;
    }
    Node* curr = list.head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
}

void freeList(LList& list) {
    while (list.head != nullptr) {
        Node* temp = list.head;
        list.head = list.head->next;
        delete temp;
    }
}

void printList(const LList& list) {
    if (!list.head) {
        cout << "{}";
        return;
    }
    Node* curr = list.head;
    cout << "{";
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) cout << ", ";
        curr = curr->next;
    }
    cout << "}";
}

int main() {
    // ========================================================
    // Test Case 1: Đúng như ví dụ 1 của đề bài
    // list1 = {1, 2, 3, 1, 2, 4}
    // list2 = {2, 3, 1}
    // Kỳ vọng: Trả về 3 (độ dài của list2)
    // ========================================================
    LList list1 = {nullptr};
    append(list1, 1); append(list1, 2); append(list1, 3); 
    append(list1, 1); append(list1, 2); append(list1, 4);

    LList list2 = {nullptr};
    append(list2, 2); append(list2, 3); append(list2, 1);

    cout << "--- Test 1 ---" << endl;
    cout << "list1: "; printList(list1); cout << endl;
    cout << "list2: "; printList(list2); cout << endl;
    cout << "Ket qua isSublist(list1, list2): " << isSublist(list1, list2) << " (Ky vong: 3)\n\n";

    // ========================================================
    // Test Case 2: Đúng như ví dụ 2 của đề bài (không phải con)
    // list3 = {5, 2, 1}
    // list4 = {1, 2, 3, 1, 2, 4}
    // Kỳ vọng: Trả về -1
    // ========================================================
    LList list3 = {nullptr};
    append(list3, 5); append(list3, 2); append(list3, 1);
    
    LList list4 = {nullptr}; // Tái sử dụng dữ liệu giống list 1
    append(list4, 1); append(list4, 2); append(list4, 3); 
    append(list4, 1); append(list4, 2); append(list4, 4);

    cout << "--- Test 2 ---" << endl;
    cout << "list3: "; printList(list3); cout << endl;
    cout << "list4: "; printList(list4); cout << endl;
    cout << "Ket qua isSublist(list3, list4): " << isSublist(list3, list4) << " (Ky vong: -1)\n\n";

    // ========================================================
    // Test Case 3: Chú ý của đề bài (Danh sách rỗng)
    // list_empty = {}
    // list2 = {2, 3, 1}
    // Kỳ vọng: Trả về 0 (danh sách rỗng là con của mọi danh sách)
    // ========================================================
    LList list_empty = {nullptr};

    cout << "--- Test 3 ---" << endl;
    cout << "list_empty: "; printList(list_empty); cout << endl;
    cout << "list2: "; printList(list2); cout << endl;
    cout << "Ket qua isSublist(list_empty, list2): " << isSublist(list_empty, list2) << " (Ky vong: 0)\n\n";

    // ========================================================
    // Dọn dẹp bộ nhớ
    // ========================================================
    freeList(list1);
    freeList(list2);
    freeList(list3);
    freeList(list4);
    // list_empty không cần free vì đang trỏ null

    return 0;
}
