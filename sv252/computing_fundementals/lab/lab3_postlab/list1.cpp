#include <iostream>
using namespace std;

struct node
{
  int data;
  node *next;
};

node *createLinkedList(int n); // The implementation is provided implicitly

void addNodeToEnd(node*& head, node*& tail, node* n) {
    node* newNode = new node;
    newNode->data = n->data;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = tail->next;
    }
}

node* concatNode(node* l1, node* l2) {
    node* cur = l1;
    if (l1 == nullptr) {return l2;}
    if (l2 == nullptr) {return l1;}
    
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    
    cur->next = l2;
    return l1;
}

node* evenThenOddLinkedList(node *head)
{
  //TODO
  node* evenHead = nullptr;
  node* evenTail = nullptr;
  
  node* oddHead = nullptr;
  node* oddTail = nullptr;
  
  node* cur = head;
  if (cur == nullptr) {return cur;}
  
  while (cur != nullptr) {
      if (cur->data % 2 == 0) {
          addNodeToEnd(evenHead, evenTail, cur);
      }
      else {
          addNodeToEnd(oddHead, oddTail, cur);
      }
      cur = cur->next;
  }
  
  return concatNode(evenHead, oddHead);
}

void print(node *head)
{
  while (head != nullptr)
  {
    cout << head->data << " ";
    head = head->next;
  }
  cout<<endl;
}
int main()
{
  int n = 0;
  cin >> n;
  node *head = createLinkedList(n);
  print(head);
  head = evenThenOddLinkedList(head);
  print(head);
  return 0;
}