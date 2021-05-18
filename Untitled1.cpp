#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main(){
	ifstream file;
	file.open("detail.txt");
	ofstream ofile;
	ofile.open("abc.txt");
	
	string ab;
	while(!file.eof()){
		getline(file, ab);
		ofile << ab;
	}
	remove("detail.txt");
	rename("abc.txt", "detail.txt");
	file.close();
	ofile.close();
}
