#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>         // std::thread

//this program will take any number the user picks
//and will convert it to binary
//then check all numbers prior to the user number
//to see how many of those numbers have the same amount of 1's in binary form

using namespace std;

struct params {
	int s, e, t;
};


void open_file(vector<int>&);
void convert(vector<int>);
int count(int);
void split(params);	//multi-thread

int matches = 0;
#define NUMT 16	//NUMT is number of threads
				//this can be changed in this file

int main() {
	vector<int> nums;
	open_file(nums);
	convert(nums);
	system("pause");
}

void open_file(vector<int>& nums) {

	/*ifstream infile;
	infile.open("C:\\Users\\alanm\\onebits.txt");
	int i = 0;
	while (!infile.eof()) {
		infile >> i;
		nums.push_back(i);
	}*/
	//for (int i = 0; i < nums.size(); i++)
	//	cout << nums[i] << endl;
	int temp = 0;
	cout << "Input the numbers: ";	//user enters the number they want to check
	while (true) {
		cin >> temp;
		if (temp == -1)	//uses -1 after numbers to start program
			break;
		nums.push_back(temp);
	}

}
void convert(vector<int> nums) {
	thread ts[NUMT];
	for (int i = 0; i < nums.size(); i++) {
		int thenum = nums[i];
		int temp = count(thenum);
		for (int i = 0; i < NUMT; i++){
			params p;
			p.s = ((thenum / NUMT) * i);	//sends first half of numbers to own thread
			p.e = (thenum / NUMT) * (i + 1);//sends second half of numbers to another thread
			p.t = temp;
			ts[i] = thread(split,p);
		}
		for (int i = 0; i < NUMT;i++)
			ts[i].join();
		
		cout << "THere were " << matches << " matches." << endl;
	}
	//for (int i = 0; i < ones.size(); i++)
	//	cout << ones[i] << endl;
}
int count(int thenum) {
	vector<int> ones;
	while (thenum > 0) {
		int x = thenum, count = 0;
		while (x > 0) {
			x = (x / 2);
			count++;
		}
		ones.push_back( count );
		thenum = thenum - pow(2, count - 1);
	}
	return ones.size();
}

void split(params p) {

	for (int j = p.s; j < p.e; j++) {
		if (count(j) == p.t)
			matches++;
	}
	
}