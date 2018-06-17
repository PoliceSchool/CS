#include <iostream>
using namespace std;

struct Node {
	int data;
	Node *next;
};

typedef struct Node Node;

Node* ReverseList(Node *head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	Node *p1 = head;
	Node *p2 = p1->next;
	Node *p3 = p2->next;

	p1->next = nullptr;  //������ͷ��Ϊβ
	while (p3 != nullptr) {
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	p2->next = p1; //������β��Ϊͷ
	head = p2;
	return head;
}




int main(void) {

}