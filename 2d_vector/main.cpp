#include<iostream>
#include<vector>
using namespace std;


void print_v2d(const vector<vector<int>>& v2d)
{
	int row = v2d.size();
	int col = 0;
	if (row)
		col = v2d[0].size();
	else 
		throw std::runtime_error("not a 2d vector");

	for (int i =0; i<row;i++){
		for (int j=0; j<col; j++){
			cout << v2d[i][j] << " ";
		}
		cout << endl;
	}
}

void print_vector(int** v2d, int row, int col)
{
	for (int i=0; i<row; i++){
		for (int j=0; j<col; j++){
			cout << v2d[i][j] << " ";
		}
		cout << endl;	
	}
}



void create_vector_using_ptr()
{
	int row = 3;
	int col = 3;

	int**v2d = new int*[row];

	for (int i=0;i<row;i++){
		v2d[i] = new int[col];
		for (int j=0;j<col;j++){
			v2d[i][j]=(i+10)*(j+2);
		}
	}
	
	cout << "v2d:" << endl; 
	print_vector(v2d,row, col);

}

void get_transpose(int** v2d, int row, int col)
{
	for (int i=0; i<row; i++){
		for (int j=i+1; j<col; j++){
				int tmp = v2d[i][j];
				v2d[i][j]=v2d[j][i];
				v2d[j][i] =tmp;
		}
	}
}

void rotate_v2d(int** v2d, int row, int col)
{
	get_transpose(v2d, row, col);

	for (int i =0; i<row; i++){
		for (int j=0; j<col/2; j++){
			int tmp = v2d[i][j];
			v2d[i][j]=v2d[i][col-1-j];
			v2d[i][col-1-j] = tmp;
		}
	}
}

int main()
{
	int row = 4;
	int col = 4;

	int**v2d = new int*[row];

	for (int i=0;i<row;i++){
		v2d[i] = new int[col];
		for (int j=0;j<col;j++){
			v2d[i][j]=(i+10)*(j+2);
		}
	}
	
	cout << "v2d:" << endl; 
	print_vector(v2d,row, col);

/*	rotate_v2d(v2d, row,col);

	cout << "rotate:" << endl; 
	print_vector(v2d,row, col);
*/
/*
	get_transpose(v2d, row,col);

	cout << "transpose:" << endl; 
	print_vector(v2d,row, col);
*/


/*
	int row =2;
	int col =3;
	vector<vector<int>> v2d;

	for (int i=0; i<row; i++)
		v2d.push_back(vector<int>());

	int n = 0;
	cout << "enter some numbers" << endl;

	for (int i =0; i<row;i++){
		for (int j=0; j<col;j++){
			cin >> n;
			v2d[i].push_back(n);
		}
	}	
	cout << "v2d: " << endl;
	print_v2d(v2d);
*/
}
