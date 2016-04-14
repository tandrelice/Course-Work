#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){
	string input;
	while(!cin.eof()){
		if(input.length() >= 7 && (input[0] == 'C' && input[1] == 'o' 
			&& input[2] == 'o' && input[3] == 'k' && input[4] == 'i' 
				&& input[5] == 'e' && input[6] == ':'))
		{
		cout << input << endl;
		}
		getline(cin,input);
	}
	return 0;
}
