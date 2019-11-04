#pragma once

template <typename T>
struct Node
{
	T data;
	Node* next;

};
template <typename T>
void insert(Node<T> * &head, Node<T> * &newNode)
{
	newNode->next = head;
	head = newNode;
}
template <typename T>
void remove(Node<T> * &head, Node<T> * &deleteNode)
{
	Node<T> * prev = head;
	if (prev == deleteNode)
	{

	}
	while (prev->next!=nullptr&& prev->next!=deleteNode)
	{
		prev = prev->next;
	}
	prev->next = prev->next->next;
}