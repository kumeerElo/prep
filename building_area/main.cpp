#include<iostream>
using namespace std;
#include<vector>

struct Building
{
	Building(int begin, int end, int height):m_begin(begin), m_end(end), m_height(height){}
	int m_begin;
	int m_end;
	int m_height;
};

struct compare_building
{
	bool operator()(const Building& a, const Building& b){
		return a.m_end > b.m_end;
	}
};

// calculate area of skyline 
int calculate_area(const vector<Building>& bls)
{
	const int xLimit = 200;
	
	//Building last = std::max(bls.begin(), bls.end(), compare_building());
	//const int xLimit = last.m_end;

	vector<int> heights(xLimit,0);

	for (int i=0; i<bls.size(); i++){
		Building bl = bls[i];
		if (bl.m_begin < 0 || bl.m_end > xLimit)
			throw runtime_error ("building out of range");

		for (int j= bls[i].m_begin; j<bls[i].m_end; j++){
			heights[j] = bls[i].m_height;
		}
	}

	/*for (int i =0; i<xLimit; i++){
		cout << "i: " << i << "heights[i]: " << heights[i] <<endl;
	}*/

	int x1 = 0;
	int x2 = 0;
	int h = 0;
	int area = 0;
	int j=0;

	for (int i=0; i<heights.size(); ){
		x1 = i;
		h = heights[i];
		for (j=i+1; j<heights.size(); j++){
			if (heights[j]!=h){
				x2 = j-1;
				break;
			}
		}
		area += (x2-x1+1)*h;
		i = j;	
	}
	return area;
}

int max_rectangle(const vector<Building>& bls)
{
	const int xLimit = 200;
	
	vector<int> heights(xLimit,0);

	for (int i=0; i<bls.size(); i++){
		Building bl = bls[i];
		if (bl.m_begin < 0 || bl.m_end > xLimit)
			throw runtime_error ("building out of range");

		for (int j= bls[i].m_begin; j<bls[i].m_end; j++){
			heights[j] = bls[i].m_height;
		}
	}

	int h = 0;
	int x1 =0;
	int x2 = 0;
	int j=0;
	int area = 0;

	for (int i=0; i<heights.size();){
		h = heights[i];
		if (h == 0){
			i++;
			continue;
		}
		x1 = i;

		for (j=i+1; j<heights.size(); j++){
			if (heights[j] < h && heights[j]!=0) 
				h = heights[j];	
			if (heights[j] == 0){
				x2 = j-1;
				int tmp = (1+x2-x1)*h;
				cout << "one set of adjacent buildings: " << endl;
				cout << "x1: " << x1 << " x2: " << x2 << " h " << h << " area: " << tmp <<endl;
				if (tmp > area)
					area = tmp;
				break;
			}
		}
		i = j;
	}
	return area;
}

int main()
{
//populate building vector
	vector<Building> bls;
	int start = 0;
	int end = 0;
	int height = 0;
	
	cout << "enter start, end and height of the building" << endl;

	while (cin >> start >> end >> height){
		bls.push_back(Building(start, end, height));
		cout << "enter start, end and height of the building" << endl;
	}

	int area = max_rectangle(bls);
	cout << "max rectangle is: " << area << endl;
/*
	int area = calculate_area(bls);
	cout << "area is: " << area << endl;
*/
}
