#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};

node *createLinkedList(int n); // The implementation is provided implicitly

void replace(node* head, int position, int value)
{
  //TODO
  if (position < 0) {return;}
  
  node* cur = head;
  for (int i = 0; i < position; i++) {
      cur = cur->next;
      if (cur == nullptr) {return;}
  }
  
  cur->data = value;
  return;
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
  int pos, val;
  cin>>pos>>val;
  replace(head, pos, val);
  print(head);
  return 0;
}
