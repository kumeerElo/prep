#include<iostream>
using namespace std;

class Bst
{
public:
	Bst():m_val(9999), m_left(NULL), m_right(NULL){}
	Bst(int val):m_val(val), m_left(NULL), m_right(NULL){}
	Bst* left(){return m_left;}
	Bst* right(){return m_right;}
	int val(){return m_val;}
	void setLeft(Bst* node){m_left = node;}
	void setRight(Bst* node){m_right = node;}
private:
	int m_val;
	Bst* m_left;
	Bst* m_right;
};

Bst* insert(Bst* root, int v)
{
	if (root == NULL){
		root = new Bst(v);
		return root;
	}

	if (v<=root->val()){
		Bst* left = insert(root->left(), v);
		root->setLeft(left);
	}
	else{
		Bst* right = insert(root->right(), v);
		root->setRight(right);
	}

	return root;
}

void print_inorder(Bst* root)
{
	if (root==NULL)
		return;

	print_inorder(root->left());
	cout << root->val() << " ";
	print_inorder(root->right());
}

void print_preorder(Bst* root)
{
	if (root==NULL)
		return;

	cout << root->val() << " ";
	print_preorder(root->left());
	print_preorder(root->right());
}

Bst* search_tree(Bst* root, int v)
{
	if (root == NULL || root->val()==v)
		return root;

	if (v < root->val())	
		return search_tree(root->left(),v);
	else
		return search_tree(root->right(),v);
	//cout << "val: " << root->val() << endl;
}

int min(Bst* root)
{
	while (root->left()){
		root = root->left();	
	}
	return root->val();
}

void print_left_view(Bst* b)
{
	if (b == NULL)
		return;

	cout << b->val() << " ";

	if (b->left())
		print_left_view(b->left());
	else
		print_left_view(b->right());
}

bool is_bst_1(Bst* root)
{
	if (root->left()){
		return is_bst_1(root->left());
	}
	else if (root->right()){
		return is_bst_1(root->right());
	}

	if (root->left()){
		if (root->val() > root->left()->val())
			return true;
		return false;
	}

	if (root->right()){
		if (root->val() < root->right()->val())
			return true;
		return false;
	}
}

void print_all_paths(Bst* root)
{
	if (root->left() == NULL && root->right() == NULL ){
		cout << root->val() << endl;
		return;
	}

	//cout << root->val() << " ";
	
	if (root->left()){
		cout << root->val() << " ";
		print_all_paths(root->left());
	}
	if(root->right()){
		cout << root->val() << " ";
		print_all_paths(root->right());
	}
}

int main()
{
	int n=0;
	Bst* root = NULL;

	while (cin >> n && n !=99){
		root = insert(root,n);
	}	

	cout << "inorder bst: " << endl;
	print_inorder(root);	
	cout << endl;

	cout << "all paths" << endl;	
	print_all_paths(root);

//	print_left_view(root);

	//cout << "min: " << min(root) << endl;


	/*cout << "preorder bst: " << endl;
	print_preorder(root);	
	cout << endl;*/

/*
	Bst* found = search_tree(root,7);
	if (found)
		cout << "found" << endl;
	else 
		cout << "not found" << endl;
*/
}
