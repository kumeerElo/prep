#include<iostream>
using namespace std;
#include<stack>

class List
{
public:
	List():m_val(9999),m_next(NULL){}
	List(int v):m_val(v), m_next(NULL){}
	int val(){return m_val;}
	List* next(){return m_next;}
	void setNext(List* next){m_next =next;}
private:
	int m_val;
	List* m_next;	
};

class Stack
{
public:
	Stack():m_top(NULL),m_size(0){}
	void push(int v);
	void pop();
	int top();
	bool empty();
	int size();
	void print();
private:
	List* m_top;
	int m_size;
};

void Stack::push(int v)
{
	if (m_size == 0){
		m_top = new List(v);
		m_size++;
	}
	else{
		List* l = new List(v);
		l->setNext(m_top);
		m_top = l;	
		m_size++;
	}
}

void Stack::pop()
{
	if (m_size ==0)
		return;
	List* l = m_top;
	m_top = m_top->next();
	delete l;
	m_size--;
}

int Stack::top()
{
	if (m_size ==0)
		throw std::runtime_error("empty stack");
	return m_top->val();
}

void Stack::print()
{
	while(m_size){
		cout << m_top->val() << " ";
		pop();
	}
	cout << endl;
}

class Queue
{
public:
	Queue():m_front(NULL),m_back(NULL),m_size(0){}
	void push_front(int n);
	void push_back(int n);
	void pop_front();
	void pop_back();
	int front(){return m_front->val();}
	int back(){return m_back->val();}
	int size(){return m_size;}
	int empty(){return !m_size;}
	void print();
private:
	List* m_front;
	List* m_back;
	int m_size;
};

void Queue::push_back(int n)
{
	if (m_size == 0){
		m_front = new List(n);
		m_back = m_front;
		m_size++;
	}
	else{
		List* l = new List(n);
		l->setNext(m_back);
		m_back = l;
		m_size++;
	}
}

void Queue::push_front(int n)
{
	if (m_size == 0){
		m_front = new List(n);
		m_back = m_front;
		m_size++;
	}
	else{
		List* l = new List(n);
		l->setNext(m_front);
		m_front = l;
		m_size++;
	}
}

void Queue::pop_front()
{
	if (m_size == 0)
		return;

	List* copy = m_front;
	m_front = m_front->next();
	delete copy;
	m_size--;
}

void Queue::pop_back()
{
	if (m_size == 0)
		return;

	List* copy = m_back;
	m_back = m_back->next();
	delete copy;
	m_size--;
}

void Queue::print()
{
	while(m_size){
		cout << front() << " ";
		pop_front();	
	}
	cout << endl;
}

class QueueWithStack
{
public:
	QueueWithStack(){}
	void push_front(int n);
	void push_back(int n);
	int pop_front();
	int pop_back();
	//int front(){return m_front.top();}
	//int back(){return m_back.top();}
	//int size(){return m_front.size() + m_back.size();}
	//int empty(){return !size();}
	void print();
private:
	stack<int> m_front;
	stack<int> m_back;
};

void QueueWithStack::push_back(int n)
{
	m_back.push(n);
}

void QueueWithStack::push_front(int n)
{
	m_front.push(n);
}

int QueueWithStack::pop_front()
{
	if (!m_front.empty()){
		int top = m_front.top();
		m_front.pop();
		return top;
	}else{
		if (m_back.empty())
			return 99999;
		while(!m_back.empty()){
			int top = m_back.top();
			m_back.pop();	
			m_front.push(top);
		}
		int top = m_front.top();
		m_front.pop();
		return top;
	}
}

void QueueWithStack::print()
{
	while(m_front.size() + m_back.size() >0){
		cout << pop_front() << " ";
	}
	cout << endl;
}

int main()
{
	int n=0;

	QueueWithStack q;	
	while (cin >> n && n != 99)
		q.push_back(n);

	cout << "now entry to the front " << endl;
	while (cin >> n && n != 99)
		q.push_front(n);

	cout << "queue is: " << endl;
	q.print();
	
/*
	Queue queue;	
	while (cin >> n && n != 99)
		queue.push_back(n);

	cout << "queue is: " << endl;
	queue.print();
*/	
	/*Stack st;	
	while (cin >> n && n != 99)
		st.push(n);

	cout << "stack is: " << endl;
	st.print();
	*/
}
