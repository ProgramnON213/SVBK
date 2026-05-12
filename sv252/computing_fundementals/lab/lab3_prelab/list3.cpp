#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};
node *createLinkedList(int n)
{
  // TO DO
  node* head = nullptr;
  for (int i = 0; i < n; i++) {
      int curData;
      cin >> curData;
      node* temp = new node;
      temp->data = curData;
      temp->next = nullptr;
      if (head == nullptr) {
          head = temp;
      }
      else {
          temp->next = head;
          head = temp;
      }
  }
  return head;
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
  if (n > 0)
  {
    node *head = createLinkedList(n);
    print(head);
  }
  else
  {
    cout << "Invalid n" << endl;
  }
  return 0;
}