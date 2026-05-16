#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};
node *createLinkedList(int n); // The implementation is provided implicitly
void mergeList(node* head1, node* head2)
{
    node* cur = head1;
    if (head1 == nullptr) {return;}
    if (head2 == nullptr) {return;}
    
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    
    cur->next = head2;
    return;
}
void print(node *head)
{
  while (head != nullptr)
  {
    cout << head->data << endl;
    head = head->next;
  }
}
int main()
{
  int n = 0;
  cin >> n;
  node *head = createLinkedList(n);
  int m;
  cin>>m;
  node *head1 = createLinkedList(m);
  mergeList(head, head1);
  print(head);
  return 0;
}
