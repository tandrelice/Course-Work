#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

vector<double> comparetwo (vector <vector < double > > a, vector <vector <double> > b, double c){
	vector<double> n(3);
	n.at(0) = -1;
	unsigned int ia = 0, ib = 0;
	double m;
	while ( ia < a.size()){
		while (ib < b.size()){
			m = sqrt (((a.at(ia).at(0) - b.at(ib).at(0)) * (a.at(ia).at(0) - b.at(ib).at(0))) +
					(((a.at(ia)).at(1) - b.at(ib).at(1)) *(a.at(ia).at(1) - b.at(ib).at(1))));
			if (m < c){
			c = m;
			n.at(0) = c;
			n.at(1) = a.at(ia).at(3);
			n.at(2) = b.at(ib).at(3);
			}
			ib++;
		}
		ib = 0;
		ia++;
	}
	return n;
}

vector < vector < double > > comb (vector <vector <double>  > a, vector <vector <double> > b){
	int n = b.size();
	int m = a.size();
	int i = 0;
	a.resize(m+n);
	while ( i < n ){
		a.at(m+i) = b.at(i);
		i++;
	}
	return a;
}

vector<vector <double> > combine(vector <vector <double>  > a, vector <vector <double> > b){
	double c = 999999999999999999;
	vector < double > n(3);
	n = comparetwo(a, b, c);
	a = comb (a , b);
	a.at(a.size()-1).at(2) = n.at(0);
	a.at(a.size()-1).at(4) = n.at(1);
	a.at(a.size()-1).at(5) = n.at(2);
	return a;
}


vector < vector <double> > partition (vector <vector <double > > a){
	vector <vector <double> > al; vector <vector <double> > ar;
	int n, i = 0, k, alcount=0, arcount=0;
	n = ( a.size() / 2);
	k = a.at(n).at(0);
	if ( n > 0){
		while ( i < a.size()){
			if (a.at(i).at(0) < k){
				al.resize(alcount+1);
				al.at(alcount) = a.at(i);
				i++;
				alcount++;
			}
			else{
				ar.resize(arcount+1);
				ar.at(arcount) = a.at(i);
				i++;
				arcount++;
			}
		}
		return (combine ( partition(al), partition(ar)));
	}
	else{
		a.at(n).at(2) = -1;
		return a;
	}
}

int main(){
	double elemnt;
	int i = 0, k = 0;
	vector < vector <double> > a;
	int n = a.size();
	string input;
	while (cin >> input){
		istringstream stringtoint (input);
		stringtoint >> elemnt;
		if (i == 0){
			a.resize(n+1, vector <double> (6));
			a.at(n).at(0) = elemnt;
			i++;
		}
		else{
			a.at(n).at(1) = elemnt;
			a.at(n).at(3) = n;
			n++;
			i=0;
		}
	}
	sort (a.begin(), a.begin()+a.size());
	a = partition (a);
	cout << a.at(a.size()-1).at(4) << endl;
	cout << a.at(a.size()-1).at(5) << endl;
/*	while ( k < n ){
		cout << a.at(k).at(0) << " ";
		cout << a.at(k).at(1) << endl;
		k++;
	}*/
	return 0;
}
