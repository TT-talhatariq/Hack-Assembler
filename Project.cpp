#include<iostream>
#include<fstream>
#include <algorithm> 
#include<string>
#include<cstring>
using namespace std;

//Generating name for .hack extension
string output_filename(string name);
//For clearing all blank lines, Indentation and comments, Inline Comments
void clear_comments_and_blankLines(string file_name);
void clear_inline_comments_and_indentation(string file_name);

//Function for conversion of decimal to binary
string decimal_to_binary(int number);

//Function for add padding zeros in binary number (as instruction is of 16 bit for our Hack Computer) 
string add_zero_to_bin(string binary);

//For conversion to machine code
string to_JMP(string ins);
string to_D(string ins);
string to_C(string ins);

//For breakage of instruction into fields and then generating machine code-
string Cinstruction_to_MachineCode(string instruction);

int main(){
	//Will take the file name for user in runtime to save him from difficulty of writing manually
	string fname;
	cout << "Input your file name with extension(keep care of lowerCase & UpperCase letters): ";	
	cin >> fname;
	
	// Code for creating name of Output File with .hack Extension
	string output_file = output_filename(fname);
	//Checking if input file exists or not
	ifstream file;
	file.open(fname.c_str());
	if(!file.is_open()){
		cout << "File Does'nt Exist\n" << endl;	
		return 0;
		}
	else{
		file.close();
		//cout << "Assembly Code is in process of translation, please wait\n\n";
		string var;
		//First we will clear all blank lines, indentation, comments
		clear_comments_and_blankLines(fname);
		clear_inline_comments_and_indentation("temp.asm");
      
    	//opening of file(user entered name)
		ifstream ifile;
		ifile.open("temp.asm");
		//creating and opening of .hack file(for writing machine code) with same name as user entered
		ofstream ofile;
		ofile.open(output_file);
		
		//Traversing through data of file, and after converting it to machine code, will write it .hack file
		while(!ifile.eof()){
			
			getline(ifile, var)	;		//will read line by line (remeber that all comments,blank lines are removed above)
			//When address instruction will come	
			if(var == "") continue;
			if(var[0] == '@'){
				string tmp = "";
				string address;
				
				tmp = var.substr(1, var.length());			//removing @ from address
				
				int num = stoi(tmp);					//converting string to int for converting it into binary
				address = decimal_to_binary(num);
				address = add_zero_to_bin(address);	   //Adding zeros for compeleting 16 bits
				
				ofile << address << endl;			 //Writing in file	
			}
			
			//Else C instruction handler
			else{
				
				string comp;
				/*
				  Every thing related to parsing, code generation, gathering is handled properly
				  thorough this funtion, which is using some further funtions in it
				*/			
				
				comp = Cinstruction_to_MachineCode(var);
				ofile << comp << endl;
			}
			    
		}
		//Closing files			
		ifile.close();
		ofile.close();
	}
	   cout << "\nAssembly Code Translated into Hack Machine Code\n\nCheck "<< output_file << " file in\
 your folder\nThanks your Patience";
	
	return 0;
}
string output_filename(string name){
	
		//First break name from extension, and then add .hack extension with it
	size_t fo = name.find('.');
    if (fo != string::npos)
		return name.substr(0, fo) + ".hack";
}

void clear_comments_and_blankLines(string file_name){
	
	//Opening asm file and another temporary file 
	ifstream file1;
	ofstream file2;
	
	file1.open(file_name.c_str());				
	file2.open("temp.asm");    //A temporary file without all comments
	
	string var;
	while(!file1.eof()){
		getline(file1, var, '\n');
	
		//if there is comment then no need to write that line in temporary file		
		if(var[0] == '/' || var == "") continue;
		if(var == "\n") 	continue;    //If new line, then no need to write
		
		else
			file2 << var << endl;
	
		}
 
	//closing both files
	file1.close();
	file2.close();
}

void clear_inline_comments_and_indentation(string file_name){
	ifstream file1;
	ofstream file2;
	file1.open(file_name.c_str());					
	file2.open("tmp.asm");
	
	char ch;
	while(!file1.eof()){
		
		file1.get(ch);			//Reading file charater by charater for removing indentation
		
		//if there is indenation in start, then no need to write, just move on
		if(ch == ' ' || ch == '\t')
			continue;
			
		//if there is In_Line comment. ignore it till end line 
		if( ch == '/'){
			file1.ignore(100, '\n');
			file2 << '\n';		
			continue;
		}
			file2 << ch;
	}
	
	file1.close();
	file2.close();
	
	//Removing temp file and the renaming temporary file with original name
	remove(file_name.c_str());
	rename("tmp.asm", file_name.c_str());
}
string decimal_to_binary(int number){
	string num = "";
	
    while (number > 0) {
        //Condtion for reminder
        number % 2 == 1  ? num += "1" : num += "0";
        number = number / 2;
    }
    
    //Reversing the string (cuz its order is in reverse)
    
	//I searched reverse techiques from Google and found this buitlin method via a site
	//names geeksforgeeks. here is the link: https://www.geeksforgeeks.org/reverse-a-string-in-c-cpp-different-methods/
	reverse(num.begin(), num.end());
 	return num;
}

string add_zero_to_bin(string binary){
	string code = "";
	
	for(int i=binary.length(); i<16; i++){			//Loop for adding 0'ros
		code += "0";
	}
	
	code+=binary;
	return code;
}

string to_JMP(string ins){
	
	//JMP Case
	if (ins == "JGT")   return "001" ;
	if (ins == "JEQ")   return "010";  
	if (ins == "JGE")   return "011";  
	if (ins == "JLT")   return "100"  ;
	if (ins == "JNE")   return "101";  
	if (ins == "JLE" )  return "110" ; 
	if (ins == "JMP")   return "111"  ;

}

string to_D(string ins){
	// Dest Case
	if (ins == "M")    return "001" ;
	if (ins == "D")    return "010";  
	if (ins == "MD")   return "011";  
	if (ins == "A")    return "100"  ;
	if (ins == "AM")   return "101";  
	if (ins == "AD" )  return "110" ; 
	if (ins == "AMD")  return "111"  ;
}

string to_C(string ins){
	
		//TO Computation Cases
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
		else if(ins == "M-1")   return "1110010";
		else if(ins == "D+M")   return "1000010";
		else if(ins == "D-M")   return "1010011";
		else if(ins == "M-D")   return "1000111";
		else if(ins == "D&M")   return "1000000";
		else if(ins == "D|M")   return "1010101";
	    
}

string Cinstruction_to_MachineCode(string instruction){
	
	string left, right;		//Two variables for breakage of instruction
	
	string jmp, dest, comp;  //Parts of instruction
	bool jump = false;       //checker if instruction is dest=comp or comp;jump
	
	//I searched finding a character (=, ;) techiques from Google and found this buitlin method via a site
	//names geeksforgeeks.here is the link: https://www.geeksforgeeks.org/string-find-in-cpp/
	
	size_t found = instruction.find('=');
    if (found != string::npos){
		
		//For breaking instruction into two parts
		//dest = comp instruction
		left = instruction.substr(0, found);
    	right = instruction.substr(found+1, instruction.length());
		}

	else{
		//comp = jump Instruction
		found = instruction.find(';');
		left = instruction.substr(0, found);
    	right = instruction.substr(found+1, instruction.length());
		jump = true;
		}
	//	cout << left << " " << right << endl;	
	
	//If instruction is dest = comp;
	if(!jump){
		jmp = "000";
		dest = to_D(left);	
		comp = to_C(right);
		}
	//else instruction is comp;jump
	else{
		dest = "000";
		comp = to_C(left);
		jmp = to_JMP(right);
		}
	
	//Summing up all the parts
	return "111"+comp+dest+jmp;
}

