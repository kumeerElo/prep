#include<iostream>
using namespace std;
#include <algorithm>
#include <vector>
#include <sstream>
#include<stack>

void print_sorted_order(vector<string>& ss)
{
	std::sort(ss.begin(), ss.end());
	
	for (auto citer = ss.begin(); citer != ss.end(); citer++){
		cout << *citer << " ";
	}
	cout << endl;

}

// in place copy, string looks jumlbed up, not good for seeing results in compact form

string remove_three_or_more(string s, int size)
{
	int startC = 0;
	int repCount = 1;
	int endC = 0;
	int k=0;

	for (int i =0; i<size-1; i++){
		if (s[i] == s[i+1]){
			repCount++;
			if (startC == 0 && i!=0)
				startC = i;
			continue;
		}
		if (s[i] != s[i+1] && repCount >=3){
			endC = i+1;
			for (int j = endC; j<endC+repCount && j< size; j++){
				s[startC+k] = s[j];
				k++;
			}
			size -= repCount;	
			return remove_three_or_more(s,size);
			break;
		}			
	}
	return s;
}

//this one creates a new string and passes it around

string remove_three_or_more_new_string(string s, int size)
{
	int startC = 0;
	int repCount = 1;
	int endC = 0;
	int k=0;
	string newS;

	for (int i =0; i<size-1; i++){
		if (s[i] == s[i+1]){
			repCount++;
			if (startC == 0 && i!=0)
				startC = i;
			continue;
		}
		if (s[i] != s[i+1] && repCount >=3){
			endC = i+1;
			for (int j=0; j< startC; j++)
				newS.push_back(s[j]);
			for (int j=endC; j< size; j++)
				newS.push_back(s[j]);
			return remove_three_or_more_new_string(newS, newS.size());
			break;
		}			
	}
	return s;
}

bool is_operator(const char c)
{
	switch(c){
		case '+':
		case '-':
		case '*':
		case '/':
			return true;
		default:
			return false;
	}
}

void reverse_order_2(const string& str)
{
	int index =0;
	vector<string> nums;

	while (index < str.size()){
		if (is_operator(str[index])){
			string s = "";
			s += str[index];
			nums.push_back(s);
			index++;
			continue;
		}
		ostringstream os;
		while (!is_operator(str[index]) && index < str.size() ){
			os << str[index];
			index++;
		}
		nums.push_back(os.str());
	}

	stack<string> st;
	for (int i=0; i<nums.size(); i++){
			st.push(nums[i]);
	}

	while(!st.empty()){
		cout << st.top() << " ";
		st.pop();
	}
		cout << endl;
}

/*
bool is_parenthesis(const char c)
{
	switch(c){
		case '(':
		case ')':
		case '[':
		case ']':
			return true;

	}
}
*/

char get_counter_part(const char c)
{
	if (c == '(')
		return ')';
	else if (c == '{')
		return '}';
	else if (c == '[')
		return ']';
}

bool isLeftSide (const char c){
	if (c == '(' || c == '{' || c == '[')
		return true;
	return false;
}

bool isRightSide (const char c){
	if (c == ')' || c == '}' || c == ']')
		return true;
	return false;
}

bool check_parenthesis(const string& s)
{
	stack<char> st;
	char c;

	for (int i=0; i< s.size(); i++){
		if (isLeftSide(s[i])){
			st.push(s[i]);
		}
		if (isRightSide(s[i])){
			if (st.empty())
				return false;
			else{
				c = st.top();
				st.pop();
				if (s[i] == ')' && c != '(')
					return false;
				if (s[i] == '}' && c != '{')
					return false;
				if (s[i] == ']' && c != '[')
					return false;
			}
		}
	}

	if (!st.empty())
		return false;
	return true;
}

/*
void print_permutation(string& s, int idx )
{
	if (idx == s.size()-1)
		cout << s << "\t";

	for (int i=idx; i<s.size(); i++){


	}
}
*/

void print_substring(int idx, const string& s)
{
	int len = 0;
	while (len <= s.size()-idx){ // subtraction by idx is important
		cout << s.substr(idx,len) << " ";
		len++;
	}
	cout << endl;
}

void print_all_substring(const string& s)
{
	for (int i=0; i<s.size(); i++){
		print_substring(i,s);
	}
}

void tokenize_string(const string& s, vector<string>&tokens)
{
	int bIdx =0;
	int eIdx =0;
	string sub;

	while (1){
		eIdx = s.find('.', eIdx);
		if (eIdx != string::npos){
			sub = s.substr(bIdx, eIdx-bIdx);
			tokens.push_back(sub);
			eIdx++;
			bIdx = eIdx;
		}
		else{
			sub = s.substr(bIdx, s.size());
			tokens.push_back(sub);
			break;
		}
	}
}

void get_substring(int idx, const string& s, vector<string>&ss)
{
	int step = 1;
	while (step+idx != s.size()+1){
		ss.push_back(s.substr(idx,step));
		step++;
	}
}

int add_all_substring_numbers(const string& s)
{
	vector<string> ss;

	for (int i=0; i<s.size(); i++){
		get_substring(i,s,ss);
	}

	cout << "substrings are : " << endl;
	for (int i=0; i<ss.size(); i++){
		cout << ss[i] << " ";
	}
	cout << endl;
	
	long tot = 0;
	for (int i=0; i<ss.size(); i++){
		tot += std::stoi(ss[i]);	
	}
	cout << "total addition is: " << tot << endl;
}

bool is_rotated (const string& s, const string& rs)
{
	if (rs.size() > s.size())
		return false;

	string sTwice = s+s;
	
	int pos = sTwice.find(rs);
	if (pos != string::npos){
		cout << "pos: " << pos << endl; 	
		return true;
	}
	return false;
}

int convert_numerals(const char c)
{
	switch(c){
		case 'I':
			return 1;
		case 'V':
			return 5;
		case 'X':
			return 10;
		case 'L':
			return 50;
		case 'C':
			return 100;
		default:
			return 999999;
	}
}

void roman_to_int(const string& s)
{
	if (s.size() ==1){
		cout << "roman: " << s << " int: " << convert_numerals(s[0])<< endl;
		return;
	}

	int tot =0;
	bool isTwoDigit = false;
	
	for (int i=0; i<s.size()-1; i++){
		if (convert_numerals(s[i]) < convert_numerals(s[i+1])){
			tot += (convert_numerals(s[i+1]) - convert_numerals(s[i]));
			i++;
			isTwoDigit = true;
		}
		else{
			tot += convert_numerals(s[i]);
			isTwoDigit = false;
		}
	}
	
	if (!isTwoDigit){
		tot+=convert_numerals(s[s.size()-1]);
	}

	cout << "roman: " << s << " int: " << tot << endl;
}

int main(){
	string s = "";

	while (cin >> s){
		roman_to_int(s);
	}

/*	string refS = "";
	cout << "enter base string followed by other string" << endl;

	while (cin >> s >> refS){
		cout << "is_rotated: " << is_rotated(s, refS) << endl;		
	}
*/
/*	while (cin >>s){
		add_all_substring_numbers(s);
	}
*/

/*
	vector<string> tokens;
	while (cin >> s){
		tokenize_string(s, tokens);
		for (int i=0; i<tokens.size(); i++)
			cout << tokens[i] << " ";
		cout << endl;
	}
*/
/*	while (cin >> s){
		print_all_substring(s);
	}
*/
	/*while (cin >> s){
		cout << "is_good: " <<  check_parenthesis(s) << endl;
	}*/

	/*while (cin >> s){
		reverse_order_2(s);		
	}*/

	/*vector<string> vs;
	cout << "enter strings one after another separated by space" <<endl;
	while (cin >> s){
		cout << "after removing: " << remove_three_or_more_new_string(s, s.size()) << endl;
	}*/
/*
	while (cin >> s && s != "na")
		vs.push_back(s);
	
	print_sorted_order(vs);
*/
}
