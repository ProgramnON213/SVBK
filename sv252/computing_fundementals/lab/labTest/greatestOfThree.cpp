#include <iostream>
using namespace std;

struct Node{
int data;
Node* next;
};
struct LList{
Node* head;
};

bool isLengthOver(const LList& list, int length = 2) {
    int l = 0;
    Node* cur = list.head;
    while (cur != nullptr) {
        l++;
        cur = cur->next;
    }
    return l > length;
}

void greatestOfThree(const LList& list, int& first, int& second, int& third) {
    if (!isLengthOver(list)) {
        first = -1; second = -1; third = -1;
        return;
    }

    int left; int mid; int right;
    Node* cur = list.head;
    left = cur->data;   cur = cur->next;
    mid = cur->data;    cur = cur->next;
    right = cur->data;  cur = cur->next;

    int tempSum = left + mid + right;
    first = left;
    second = mid;
    third = right;

    while (cur != nullptr) {
        left = mid;
        mid = right;
        right = cur->data;
        if (left + mid + right >= tempSum) {
            tempSum = left + mid + right;
            first = left;
            second = mid;
            third = right;
        }
        cur = cur->next;
    }
    
    return;
}

int main() {
    // ========================================================
    // Test Case 1: Danh sách dài, có nhiều bộ tổng bằng nhau
    // Danh sách: 1 -> 2 -> 3 -> 0 -> 2 -> 2 -> 2
    // Có hai bộ (1,2,3) tổng = 6. Hàm phải gán bộ ở cuối cùng.
    // ========================================================
    Node* tail3 = new Node{2, nullptr};
    Node* tail2 = new Node{2, tail3};
    Node* tail1 = new Node{2, tail2};
    Node* mid0  = new Node{0, tail1};
    Node* head3 = new Node{3, mid0};
    Node* head2 = new Node{2, head3};
    Node* head1 = new Node{1, head2};
    LList list1 = {head1};

    int f1 = 0, s1 = 0, t1 = 0;
    cout << "--- Test 1: Danh sach 1->2->3->0->2->2->2 ---" << endl;
    greatestOfThree(list1, f1, s1, t1);
    cout << "Ket qua (first, second, third): " << f1 << ", " << s1 << ", " << t1 << endl;


    // ========================================================
    // Test Case 2: Danh sách không đủ 3 phần tử (chỉ có 2)
    // Danh sách: 10 -> 20
    // ========================================================
    Node* short2 = new Node{20, nullptr};
    Node* short1 = new Node{10, short2};
    LList list2 = {short1};

    int f2 = 0, s2 = 0, t2 = 0;
    cout << "\n--- Test 2: Danh sach 10->20 (Khong du 3 phan tu) ---" << endl;
    greatestOfThree(list2, f2, s2, t2);
    cout << "Ket qua (first, second, third): " << f2 << ", " << s2 << ", " << t2 << endl;


    // ========================================================
    // Dọn dẹp bộ nhớ
    // ========================================================
    while (list1.head) { 
        Node* temp = list1.head; 
        list1.head = list1.head->next; 
        delete temp; 
    }
    while (list2.head) { 
        Node* temp = list2.head; 
        list2.head = list2.head->next; 
        delete temp; 
    }

    return 0;
}