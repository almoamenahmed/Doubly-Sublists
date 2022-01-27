#include <iostream>
#include <fstream>
#include <string>
using namespace std;
ofstream outputfile("errorlog.txt");
struct Node {
	int data;
	struct Node* prev, * next;
};
struct Node* getNode(int data)
{
	struct Node* newNode = new (struct Node);
	newNode->data = data;
	newNode->prev = newNode->next = NULL;
	return newNode;
}
void sortedInsert(struct Node** head_ref, struct Node* newNode);
void removeEntry(struct Node** head_ref, int deleteVal);
void printList(struct Node* head, char ch);
int main()
{
	struct Node* headFullList = NULL;
	struct Node* evenList = NULL;
	struct Node* oddList = NULL;
	int choice;
	string line;
	ifstream readFile("integer.dat");
	cout << "\n\t**Doubly Linked List Modification**\n";
	if (readFile.is_open())
	{
		while (getline(readFile, line))
		{
			int data = atoi(line.c_str());
			if (data < 1)
			{
				outputfile << data << " is a negative entry! Please enter something greater than 0!" << endl;
					cout << data << " Error: Negative Entry\n";
			}
			else
			{
				struct Node* new_node_fulllist = getNode(data);
				sortedInsert(&headFullList, new_node_fulllist);
				if (data % 2 == 0)
				{
					struct Node* new_node_sublist = getNode(data);
					sortedInsert(&evenList, new_node_sublist);
				}
				else if (data % 2 != 0)
				{
					struct Node* new_node_sublist = getNode(data);
					sortedInsert(&oddList, new_node_sublist);
				}
			}
		}
		readFile.close();
	}
	else {
		outputfile << "Error: File not Found!" << endl;
		cout << "File not Found!";
	}
	do {
		cout << "\n1. Add Data Entry to List";
		cout << "\n2. Delete Data Entry from List";
		cout << "\n3. Display Ascending Full List with Even and Odd Sublists";
		cout << "\n4. Display Descending Full List with Even and Odd Sublists";
		cout << "\n5. Exit Program";
		cout << "\n\nEnter Selection 1-5: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			int newData;
			cout << "Insert a new value: ";
			cin >> newData;
			if (newData < 1) {
				cout << " is a negative entry! Please enter something greater than 0!" <<
					endl;
				outputfile << newData << " Error: Negative Entry\n";
			}
			else
			{
				struct Node* new_node_fulllist = getNode(newData);
				sortedInsert(&headFullList, new_node_fulllist);
				if (newData % 2 == 0)
				{
					struct Node* new_node_sublist = getNode(newData);
					sortedInsert(&evenList, new_node_sublist);
				}
				else if (newData % 2 != 0)
				{
					struct Node* new_node_sublist = getNode(newData);
					sortedInsert(&oddList, new_node_sublist);
				}
			}
			break;
		case 2:
			int deleteVal;
			cout << "Delete a Present Data Entry: ";
			cin >> deleteVal;
			if (deleteVal < 1) {
				cout << newData << " is a negative entry! Please enter something greater than 0!" << endl;
					outputfile << deleteVal << " Error: Negative Input\n";
			}
			else
			{
				removeEntry(&headFullList, deleteVal);
				if (deleteVal % 2 == 0)
				{
					removeEntry(&evenList, deleteVal);
				}
				if (deleteVal % 2 != 0)
				{
					removeEntry(&oddList, deleteVal);
				}
			}
			break;
		case 3:
			cout << "Ascending List: ";
			printList(headFullList, 'A');
			cout << "Even sublist: ";
			printList(evenList, 'A');
			cout << "Odd sublist: ";
			printList(oddList, 'A');
			break;
		case 4:
			cout << "Descending List: ";
			printList(headFullList, 'D');
			cout << "Even sublist: ";
			printList(evenList, 'D');
			cout << "Odd sublist: ";
			printList(oddList, 'D');
			break;
		case 5:
			cout << "Thanks for using the program!";
			break;
		default:
			cout << "\nWrong Input!" << endl;
		}
	} while (choice != 5);
	outputfile.close();
	return 0;
}
void sortedInsert(struct Node** head_ref, struct Node* newNode)
{
	struct Node* current;
	if (*head_ref == NULL)
		*head_ref = newNode;
	else if ((*head_ref)->data >= newNode->data) {
		newNode->next = *head_ref;
		newNode->next->prev = newNode;
		*head_ref = newNode;
	}
	else {
		current = *head_ref;
		while (current->next != NULL && current->next->data <= newNode->data) {
			if (current->next->data == newNode->data) {
				outputfile << "Error : " << newNode->data << " is already in the list" << endl;
				cout << "Error : " << newNode->data << " is already in the list" << endl;
				return;
			}
			current = current->next;
		}
		newNode->next = current->next;
		if (current->next != NULL)
			newNode->next->prev = newNode;
		current->next = newNode;
		newNode->prev = current;
	}
}
void removeEntry(struct Node** head_ref, int deleteVal)
{
	struct Node* temp;
	if (*head_ref == NULL)
	{
		outputfile << "Error : Can't delete '" << deleteVal << " because list is empty" << endl;
		cout << "Error : Can't delete '" << deleteVal << " because list is empty" << endl;
		return;
	}
	if ((*head_ref)->next == NULL) {
		if ((*head_ref)->data == deleteVal)
		{
			temp = (*head_ref);
			(*head_ref) = NULL;
			free(temp);
			return;
		}
		else
		{
			outputfile << "Error : Can't find " << deleteVal << " data to delete into the list " << endl;
			cout << "Error : Can't find " << deleteVal << " data to delete into the list " << endl;
			return;
		}
	}
	if ((*head_ref)->data == deleteVal)
	{
		temp = (*head_ref);
		(*head_ref) = (*head_ref)->next;
		(*head_ref)->prev = NULL;
		free(temp);
		return;
	}
	temp = (*head_ref)->next;
	while (temp->next != NULL)
	{
		if (temp->data == deleteVal)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(temp);
			return;
		}
		temp = temp->next;
	}
	if (temp->data == deleteVal)
	{
		temp->prev->next = NULL;
		free(temp);
		return;
	}
	outputfile << "Error : Can't find " << deleteVal << " data to delete into the list " << endl;
	cout << "Error : Can't find " << deleteVal << " data to delete into the list " << endl;
	return;
}
void printList(struct Node* head, char ch)
{
	if (ch == 'A') {
		while (head != NULL)
		{
			cout << head->data << " ";
			head = head->next;
		}
	}
	else if (ch == 'D') {
		while (head->next != NULL)
			head = head->next;
		while (head != NULL)
		{
			cout << head->data << " ";
			head = head->prev;
		}
	}
	cout << endl;
}