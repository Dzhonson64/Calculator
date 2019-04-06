#include "pch.h"
#include <stack>
#include <iostream>
using namespace std;
struct Node {
	Node * head = nullptr;
	Node * pDown = nullptr;
	char data;
	int size;
}newNode1;
struct Node2 {
	Node * head = nullptr;
	Node * pDown = nullptr;
	double data;
	int size;
}newNode2;
/*CHAR*/
void push(char item, Node *& node);
void show(Node *& node);
char pop(Node *& node);
int size(Node *& node);
int empty(Node *& node);
char top(Node *& node);

/*INT*/
void push(char item, Node2 *& node);
void show(Node2 *& node);
int pop(Node2 *& node);
int size(Node2 *& node);
int empty(Node2 *& node);
int top(Node2 *& node);



bool f(string str);

int calc(string str);
int charToNum(char str);
void operations(char operators);
int main() {
	cout << calc("(2+2*2)+1*2") << endl;
}

void push(char item, Node *& node) {
	if(node->head == nullptr) {
		node->head = new Node;
		node->head->data = item;
	}
	else {
	Node *temp = node->head;
	node->head = new Node;
	node->head->data = item;
	node->head->pDown = temp;
	}
	node->size++;
}
void show(Node *& node) {
	Node *temp = node->head;
	if(node->size == 1) {
		cout << temp->data;
	}
	else {
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->pDown;
		}
	}
	cout << endl;
}
char pop(Node *& node) {
	Node *temp = node->head;
	int oldData = temp->data;
	node->head = node->head->pDown;
	node->size--;
	delete temp;
	return oldData;
}
int size(Node *& node) {
	return node->size;
}
int empty(Node *& node) {
	if (node->head == nullptr) {
		return 1;
	}else{
		return 0;
	}
}
char top(Node *& node) {
	if (node->head != nullptr) {
		return node->head->data;
	}
	else {
		return ' ';
	}
	
}









void push(char item, Node2 *& node) {
	if (node->head == nullptr) {
		node->head = new Node;
		node->head->data = item;
	}
	else {
		Node *temp = node->head;
		node->head = new Node;
		node->head->data = item;
		node->head->pDown = temp;
	}
	node->size++;
}
void show(Node2 *& node) {
	Node *temp = node->head;
	if (node->size == 1) {
		cout << temp->data;
	}
	else {
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->pDown;
		}
	}
	cout << endl;
}
int pop(Node2 *& node) {
	Node *temp = node->head;
	int oldData = temp->data;
	node->head = node->head->pDown;
	node->size--;
	delete temp;
	return oldData;
}
int size(Node2 *& node) {
	return node->size;
}
int empty(Node2 *& node) {
	if (node->head == nullptr) {
		return 1;
	}
	else {
		return 0;
	}
}
int top(Node2 *& node) {
	if (node->head != nullptr) {
		return node->head->data;
	}
	else {
		return 0;
	}

}
/*bool f(string str) {
	struct Node * node = &newNode1;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(' || str[i] == '[') push(str[i]);
		else {
			if (empty())
				return 0;
			if ((top() == '[' && str[i] == ']') || //по дурацки!
				top() == '(' && str[i] == ')') // там по другому можно но понятнее было

				pop();
		}
	}
	return empty();
}*/




void operations(char operats) { //выполнение операций
	struct Node * operators = &newNode1;
	struct Node2 * operands = &newNode2;
	

	switch (operats)
	{
	case '*': {
		int a = pop(operands); // берём "верхний" операнд
		int b = pop(operands); // берём операнд, который ниже "верхнего"
		pop(operators); // удаляем операцию, т.к уже её выполняем
		push(a * b, operands); // добавляем в результате вместо двух операндов результат их вычисления
		break;
	}
	case '/': {
		int a = pop(operands);
		int b = pop(operands);
		pop(operators);
		push(b / a, operands);;
		break;
	}
	case '-': {
		int a = pop(operands);
		int b = pop(operands);
		pop(operators);
		push(b - a, operands);
		break;
	}
	case '+': {
		int a = pop(operands);
		int b = pop(operands);
		pop(operators);
		push(a + b, operands);
		
		break; 
	}
	case '(': {
		push('(', operators);
		break;
	}
	default:{
		cout << "ERROR!!!" << endl;
		break;
		}
	}

}

int charToNum(char str) { // перевод из char в int
	return str - '0';
}

int calc(string str) { // основная ф-ия подсчёта
	struct Node * operators = &newNode1;
	struct Node2 * operands = &newNode2;
	for (int i = 0; i < str.size(); i++)
	{
		
		if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-' || str[i] == '(' || str[i] == ')') { // если это арифм. оператор
			char topChar = top(operators); //берём header-оператор на данный момент из стека
			if (empty(operators) || topChar == '(' /*|| topChar == '+' || topChar == '-'*/ || str[i] == '(') { // если первоначально стек пуст или данный элемент скобка, то добавляем в стек
				push(str[i], operators);
			}
			else if ((topChar == '+' || topChar == '-') && (str[i] == '+' || str[i] == '-') || (topChar == '*' || topChar == '/') && (str[i] == '*' || str[i] == '/')) { // если у нас операции с равным приоритетом, то выполняем операция, которая лежит в данный момент в стеке и ??? ...(наверно должны новую добавить операцию в стек) ???
				operations(str[i]);
				push(str[i], operators);
			}
			else if (str[i] == ')') { // если у нас закрывающаяся круглая скобка, то выполняем в ней операции, пока не встретим ( !!! Проверить!!!
				while (top(operators) != '('){
					operations(top(operators));
				}
				pop(operators); // после выполенения выражений в скобках, удаляем открывающуюся скобку из стека
			}
			else if (topChar == '*' || topChar == '/') { // если header-операция умножения или деления, то выполняем её, т.к. они имеют приоритет по местонахождению, относительно новой операции
				operations(str[i]);
				push(str[i], operators);
			}
			else {
				push(str[i], operators);
			}
		}
		else { // если это цифра, то добаляем в стек операндов
			push(charToNum(str[i]), operands);			
		}
		
	}

	// Далее выполняем оставшиеся операции, которые остались в стеке
	int sizeOperators = size(operators); 
	for (int i = 0; i < sizeOperators; i++) {
		int a = pop(operands);
		int b = pop(operands);
		char c = pop(operators);
		if (c == '*' ) {
			push(a * b, operands);
			continue;
		}
		if (c == '/') {
			push(b / a, operands);
			continue;
		}
		if (c == '+') {
			push(a + b, operands);
			continue;
		}
		if (c == '-') {
			push(b - a, operands);
			continue;
		}
	}
	return pop(operands); // в результате у нас остаётся 1 элемент в операндах - и это ОТВЕТ
}