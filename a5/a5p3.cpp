#include <iostream>

using namespace std;

int main(){
	string a="nickel", b = "dime", c = "quarter", d = "loonie";
	int x=0;
	while (!(x==125)){
		cout << x << "    " << a << "     " << x+5 << endl;
		cout << x << "    " << b << "     " << x+10 << endl;
		cout << x << "    " << c << "     " << x+25 << endl;
		cout << x << "    " << d << "     " << x+100 << endl;
		x=x+5;
	}
	return 0;
}

