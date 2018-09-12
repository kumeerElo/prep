#include<iostream>
using namespace std;
#include<vector>
#include<map>

struct List
{
	List():m_val(99999), m_next(NULL){}
	List(int i):m_val(i),m_next(NULL){}
	List* next(){return m_next;}
	int val(){return m_val;}
	int m_val;
	List* m_next;
};

List* create_new_list(const vector<int>& vi)
{
	if (vi.size() == 0)
		return NULL;

	List* first = new List(vi[0]);
	List* copy = first;

	for (int i=1; i<vi.size(); i++){
		List* l2 = new List(vi[i]);
		copy->m_next = l2;
		copy = l2;
	}
	return first;
}

void print_list(List* l)
{
	while (l!=NULL){
		cout << l->m_val << " ";
		l = l->m_next;	
	}
	cout << endl;
}

int middle(List* l)
{
	List* slow = l;
	List* fast = l;

	while (fast->next() != NULL && fast->next()->next() !=NULL){
		slow = slow->next();
		fast = fast->next()->next();
	}
	return slow->val();
}

List* reverse_list(List* l)
{
	if (l == NULL)
		return NULL;

	List* prev = NULL;
	List* after = NULL;
	
	while(l){
		after = l->next();	
		l->m_next = prev;
		prev = l;
		if (after == NULL)
			break;
		l = after;	
	}
	return l;
}

List* rotate_list(List* l, int pivot)
{
	int count = 0;

	List* prev = NULL;
	List* head = NULL;
	List* first = l;

	while (l->next()){
		count++;
		if (count == pivot){
			head = l;
			prev->m_next = NULL;
			break;
		}
		prev = l;
		l = l->next();
	}

//find last element--

	List* last = head;
	while (last->next()){
		last = last->next();
	}

	last->m_next = first;
	return head;	
}

bool is_loop(List* l)
{
	if (l == NULL || l->next() == NULL)
		return false;
	
	List* slow = l;
	List* fast = l;

	if (fast->next() == NULL || fast->next()->next() == NULL)
		return true;
	fast = fast->next()->next();

	while (1){
		if (slow ==fast)
			return true;
		if (fast->next() == NULL || fast->next()->next() == NULL)
			return false;
		slow = slow->next();
		fast = fast->next()->next();
	}
}

List* kth_from_end(List* l, int k)
{
	if (l == NULL)
		return NULL;

	List* copy = l;

	while (1){
		for (int i=0; i<k;i++){
			if (copy == NULL)
				return NULL;
			copy = copy->next();
		}
		if (copy == NULL)
			return l;

		l = l->next();
		copy =l;
	}
}

List* combine_two_lists(List* l1, List* l2)
{
	if (l2 == NULL)
		return l1;
	if (l1 == NULL)
		return l2;

	List* head = NULL;

	if (l1->m_val > l2->m_val){
		head = l2;
		l2 = l2->next();
	}
	else{
		head = l1;
		l1 = l1->next();
	}

	List* first = head;

	bool isL1Done = false;
	bool isL2Done = false;

	while (1){
		if (l1 == NULL && l2 == NULL){
			isL1Done = true;
			isL2Done = true;
			break;
		}
		if (l1 == NULL && l2 != NULL){
			isL1Done = true;
			break;
		}
		if (l2 == NULL && l1 != NULL){
			isL2Done = true;
			break;
		}
		if (l1->m_val < l2->m_val){
			head->m_next = l1;
			head = head->next();
			l1 = l1->next();
		}
		else{
			head->m_next = l2;
			head = head->next();
			l2 = l2->next();
		}
	}

	if (isL1Done && isL2Done){
		head->m_next = NULL;
		return first;
	}

	if (isL1Done){
		head->m_next = l2;
		return first;
	}

	if (isL2Done){
		head->m_next = l1;
		return first;
	}

}

List* remove_a_node_2(List* l, int val)
{
	if (l == NULL)
		return NULL;

	List* first = l;
	List* prev = NULL;

	while(l){
		if (l->m_val == val){
			if (prev == NULL){
				first = l->next();
				delete l;
				l = first;
				continue;
			}else{
				prev->m_next = l->next();
				List* nextL = l->next();
				delete l;
				l = nextL;
				continue;
			}
		}
		prev = l;
		l = l->next();
	}

	return first;	
}

void remove_a_node_3(List** ptrL, int val)
{
	List* l = *ptrL;	
	if (l == NULL)
		return;

	List* first = l;
	List* prev = NULL;

	while(l){
		if (l->m_val == val){
			if (prev == NULL){
				first = l->next();
				delete l;
				l = first;
				continue;
			}else{
				prev->m_next = l->next();
				List* nextL = l->next();
				delete l;
				l = nextL;
				continue;
			}
		}
		prev = l;
		l = l->next();
	}
}

List* remove_duplicate(List* l)
{
	map<int,bool> isPresent;
	List* save = l;
	List* prev = NULL;

	while (l){
		if (isPresent.find(l->m_val) == isPresent.end()){
			isPresent[l->m_val] = true;
		}else{
			prev->m_next = l->next();
			List* nextElement = l->next();
			delete l;
			l = nextElement;
			continue;
		}
		prev = l;
		l = l->next();
	}
	return save;
}

void insert_element(List** ptrL, int refVal, int val)
{
	List* l = *ptrL;
	if (l == NULL)
		return;

	List* next = l->next();

	while(l){
		if (l->m_val == refVal){
			List* elem = new List(val);
			l->m_next = elem;
			elem->m_next = next;
			return;	
		}
		l = l->next();
		next = l->next();
	}
}

List* add_two_nums(List* l1, List* l2)
{
	if (l2 == NULL)
		return l1;
	else if (l1 ==NULL)
		return l2;
	else if (l1 == NULL && l2 == NULL)
		return NULL;

	List* save = l1;
	int carry = 0;

	List* prevL1 = NULL;
	
	while (l1){
		if (l2){
			l1->m_val = l1->m_val + l2->m_val + carry;
			carry = l1->m_val/10;
			l1->m_val = l1->m_val%10;
			l2 = l2->next();
		}else{
			l1->m_val = l1->m_val + carry;	
			carry = l1->m_val/10;
			l1->m_val = l1->m_val%10;
		}
		prevL1 = l1;
		l1 = l1->next();
	}

	List* prevL2 = NULL;

	if (l2){
		prevL1->m_next = l2;
		while (l2){
			l2->m_val +=carry;
			carry = l2->m_val/10;
			l2->m_val = l2->m_val%10;
			prevL2 = l2;
			l2 = l2->next();
		}
	}

	if (carry){
		List* lastEl = new List(carry);
		if (prevL2)
			prevL2->m_next = lastEl;  	
		else 
			prevL1->m_next = lastEl;  	
	}

	return save;
}

int main()
{
	int n = 0;

	vector<int>vi;
	cout << "enter some numbers for list1 " << endl;
	while (cin >> n && n != 99)
		vi.push_back(n);		

	vector<int>vi2;
	cout << "enter some numbers for list2 " << endl;
	while (cin >> n && n != 99)
		vi2.push_back(n);		

	List* l1 = create_new_list(vi);
	cout << "list1: " << endl;
	print_list(l1);

	List* l2 = create_new_list(vi2);
	cout << "list2: " << endl;
	print_list(l2);
	
	List* l3 = add_two_nums(l1, l2);
	cout << "added list: " << endl;
	print_list(l3);

/*	insert_element(&l1, 20,100);
	cout << "after removing duplicates " << endl;
	print_list(l1);
*/

/*
	List* l2 = remove_duplicate(l1);

	cout << "after removing duplicates " << endl;
	print_list(l2);
*/

/*
	//List* l2 = remove_a_node_2(l1,20);
	remove_a_node_3(&l1,20);
	cout << "list after removing 20: " << endl;
	print_list(l1);
*/

/*
	vector<int>vi2;
	cout << "enter some numbers for list 2" << endl;
	while (cin >> n && n != 99)
		vi2.push_back(n);		

	List* l2 = create_new_list(vi2);
	cout << "list2: " << endl;
	print_list(l2);

	List* cL = combine_two_lists(l1,l2);

	cout << "conbined: " << endl;
	print_list(cL);
*/


/*
	List *k = kth_from_end(l,3);
	if (k){
		cout << "k: " << k->m_val << endl;
	}
	else 
		cout << "not found" << endl;
*/
/*
	List* first = l;

	while (l->next())
		l = l->next();

	l->m_next = first;

	cout << "is_loop: " << is_loop(first) << endl;
*/

/*
	List* rl = rotate_list(l,3);
	cout << "rotated: " << endl;
	print_list(rl);
*/
/*
	List* rl = reverse_list(l);
	cout << "original : " << endl;
	print_list(rl);
*/
	//cout << "middle elemebt is: " << middle(l) << endl;
}
