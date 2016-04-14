#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool has_semi (string a){
	int position;
	position = a.find(";");
	if(position < 0){
		return false;
	}
	else return true;
}

string before_semi (string a){
	int position;
	string temp;
	position = a.find(";");
	temp = a.substr(0, position);
	return temp;
}

string after_semi (string a){
	int position;
	string temp;
	position = a.find(";");
	temp = a.substr(position + 1);
	return temp;
}

int main(){
        string input1, input2, C1, C2, input2_sub;
        while(!cin.eof()){
		getline(cin, input1);
                if(input1.length() >= 7 && (input1[0] == 'C' && input1[1] == 'o'
                        && input1[2] == 'o' && input1[3] == 'k' && input1[4] == 'i'
                                && input1[5] == 'e' && input1[6] == ':'))
                {
                	while(!cin.eof()){
				getline(cin, input2);
				if (input2.length() >= 7 && (input2[0] == 'C' && input2[1] == 'o'
					&& input2[2] == 'o' && input2[3] == 'k' && input2[4] == 'i'
						&& input2[5] == 'e' && input2[6] == ':')){
					if (input1.compare(input2) == 0){
						cout << "Found" << endl;
						return 0;
					}	
					else{
						input1 = input1.substr(8);
						input2 = input2.substr(8);
						input2_sub = input2;
						while ( input1 != ""){
							if (has_semi(input1)){
								C1 = before_semi(input1);
								input1 = after_semi(input1);
								input2 = input2_sub;
								while (input2 != ""){
									if (has_semi(input2)){
										C2 = before_semi(input2);
										input2 = after_semi(input2);
										if (C1.compare(C2) == 0){
											cout << "Found" << endl;
											return 0;
										}
									}
									else{
										C2 = input2;
										input2 ="";
										if (C1.compare(C2) == 0){
											cout << "Found" << endl;
											return 0;
										}
									}
								}
							}
							else{
								C1 = input1;
								input1 = "";
								input2 = input2_sub;
                                                                while (input2 != ""){
                                                                        if (has_semi(input2)){
                                                                                C2 = before_semi(input2);
                                                                                input2 = after_semi(input2);
                                                                                if (C1.compare(C2) == 0){
                                                                                        cout << "Found" << endl;
                                                                                        return 0;
                                                                                }
                                                                        }
                                                                        else{
                                                                                C2 = input2;
                                                                                input2 ="";
                                                                                if (C1.compare(C2) == 0){
                                                                                        cout << "Found" << endl;
                                                                                        return 0;
                                                                                }
                                                                        }
                                                                }
							}
						}
						cout << "Not found" << endl;
						return 0;
					}
				}
			}
                }
        }
        return 0;
}
