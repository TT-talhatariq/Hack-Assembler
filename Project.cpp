#include<iostream>
#include <bits/stdc++.h>
#include<string>
using namespace std;

//For clearing all black lines and comments
void clear_comments_and_blankLines(string file_name);
void clear_inline_comments_and_indentation(string file_name);
//Function for conversion of decimal to binary
string decimal_to_binary(int number);
//Function for add padding zeros in binary number (as instruction is of `6 bit) 
string add_zero_to_bin(string binary);

//For conversion to machine code
string to_JMP(string ins);
string to_D(string ins);
string to_C(string ins);

//For breakage of instruction into fields and then generating machine code
string Cinstruction_to_MachineCode(string instruction);

int main(){
		string fname;
	//	cout << "Input your file name with extension(keep care of lowerCase & UpperCase letters): ";
	//	cin >> fname;
		
		
		string var;
		
		clear_comments_and_blankLines("addv0.asm");
        clear_inline_comments_and_indentation("addv0.asm");
        
        
		ifstream ifile;
		ifile.open("addv0.asm");
		
		ofstream ofile;
		ofile.open("addv0.hack");
		while(!ifile.eof()){
			
		getline(ifile, var);
		cout << var << endl;	
		
		if(var[0] == '@'){
			string tmp = "";
			string address;
			tmp = var.substr(1, var.length());
			
			int num = stoi(tmp);
			address = decimal_to_binary(num);
			address = add_zero_to_bin(address);
				
			ofile << address << endl;
		}
		else{
			string comp;
			comp = Cinstruction_to_MachineCode(var);
			ofile << comp << endl;
		}
		
		}			
	
		ifile.close();
		ofile.close();
	//cout << Cinstruction_to_MachineCode("D-1;JEQ") << endl;
	//cout << Cinstruction_to_MachineCode("0;JMP") << endl;
//	cout << Cinstruction_to_MachineCode("0;JMP") << endl;
//	cout << Cinstruction_to_MachineCode("0;JMP");
//	 clear_comments_and_blankLines("detail.txt");
//	 clear_inline_comments_and_indentation("detail.txt");
	}
	
void clear_comments_and_blankLines(string file_name){
	ifstream file1;
	ofstream file2;
	file1.open(file_name.c_str());					//Opening of two Files for deleting & Updating Particular Record
	file2.open("temp.asm");
	
	string var;
	while(!file1.eof()){
		
		getline(file1, var, '\n');
		
		if(var[0] == '/' || var == "")
			continue;
		
		else
			file2 << var << endl;
	}
	
	file1.close();
	file2.close();
	remove(file_name.c_str());
	rename("temp.asm", file_name.c_str());
}
void clear_inline_comments_and_indentation(string file_name){
	ifstream file1;
	ofstream file2;
	file1.open(file_name.c_str());					//Opening of two Files for deleting & Updating Particular Record
	file2.open("temp.asm");
	
	char ch;
	while(!file1.eof()){
		
		file1.get(ch);
		
		if(ch == ' ')
			continue;
		if( ch == '/'){
			file1.ignore(100, '\n');
			file2 << '\n';		
			continue;
		}
			file2 << ch ;
	}
	
	file1.close();
	file2.close();
	remove(file_name.c_str());
	rename("temp.asm", file_name.c_str());
	
}
string decimal_to_binary(int number){
	string num = "";
	
    while (number > 0) {
        // storing remainder in binary array
        number % 2 == 1  ? num += "1" : num += "0";
        number = number / 2;
    }
    reverse(num.begin(), num.end());
 	return num;
}

string add_zero_to_bin(string binary){
	string code = "";
	for(int i=binary.length(); i<16; i++){
		code += "0";
	}
	code+=binary;
	return code;
}

string to_JMP(string ins){
	
	if (ins == "JGT")   return "001" ;
	if (ins == "JEQ")   return "010";  
	if (ins == "JGE")   return "011";  
	if (ins == "JLT")   return "100"  ;
	if (ins == "JNE")   return "101";  
	if (ins == "JLE" )  return "110" ; 
	if (ins == "JMP")   return "111"  ;

}

string to_D(string ins){
	
	if (ins == "M")    return "001" ;
	if (ins == "D")    return "010";  
	if (ins == "MD")   return "011";  
	if (ins == "A")    return "100"  ;
	if (ins == "AM")   return "101";  
	if (ins == "AD" )  return "110" ; 
	if (ins == "AMD")  return "111"  ;
}

string to_C(string ins){
	
		//All Cases
		if(ins == "0")           return "0101010";
		
		else if(ins == "1")      return "0111111";
		else if(ins == "-1")     return "0111010";
		else if(ins == "D")      return "0001100";
		else if(ins == "A")      return "0110000";
		else if(ins == "!D")     return "0001101";
		else if(ins == "!A")     return "0110001";
		else if(ins == "-D")     return "0001111";
		else if(ins == "-A")     return "0110011";
		else if(ins == "D+1")    return "0011111";
		else if(ins == "A+1")    return "0110111";
		else if(ins == "D-1")    return "0001110";
		else if(ins == "A-1")    return "0110010";
		else if(ins == "D+A")    return "0000010";
		else if(ins == "D-A")    return "0010011";
		else if(ins == "A-D")    return "0000111";
		else if(ins == "D&A")    return "0000000";
		else if(ins == "D|A")    return "0010101";
		
		//M catogery with a == 1
		else if(ins == "M")     return "1110000";
		else if(ins == "!M")    return "1110001";
		else if(ins == "-M")    return "1110011";
		else if(ins == "M+1")   return "1110111";
		else if(ins == "A-1")   return "1110010";
		else if(ins == "D+A")   return "1000010";
		else if(ins == "D-A")   return "1010011";
		else if(ins == "A-D")   return "1000111";
		else if(ins == "D&A")   return "1000000";
		else if(ins == "D|A")   return "1010101";
	    
}

string Cinstruction_to_MachineCode(string instruction){
	
	string left, right;
	
	string jmp, dest, comp;
	bool jump = false;
	
	//I searched
	size_t found = instruction.find('=');
    if (found != string::npos){
	
		left = instruction.substr(0, found);
    	right = instruction.substr(found+1, instruction.length());
	}
	
	else{
		found = instruction.find(';');
		left = instruction.substr(0, found);
    	right = instruction.substr(found+1, instruction.length());
		jump = true;
	}
	
	if(!jump){
		
		jmp = "000";
		dest = to_D(left);	
		comp = to_C(right);

	}
	else{
	
		dest = "000";
		comp = to_C(left);
		jmp = to_JMP(right);
	}
	
	return "111"+comp+dest+jmp;
}

