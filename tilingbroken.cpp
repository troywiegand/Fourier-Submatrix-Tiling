#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;	

string TileCheck(string Row, int j);
string ConsecutiveCheck(int Check[], int a);
bool NewmanAble(int a);
string NewmanCheck(int Check[], int a);


template <typename T>
    std::string to_string(T value)
    {
      //create an output string stream
      std::ostringstream os ;

      //throw the value into the string stream
      os << value ;

      //convert the string stream into a string and return
      return os.str() ;
    }

template <typename T>
T StringToNumber ( const string &Text, T defValue = T() )
{
    stringstream ss;
    for ( string::const_iterator i=Text.begin(); i!=Text.end(); ++i )
        if ( isdigit(*i) || *i=='e' || *i=='-' || *i=='+' || *i=='.' )
            ss << *i;
    T result;
    return ss >> result ? result : defValue;
}	
	
int main(){
	 int R=8;
	 int a=4;
	 int j=R-a;
	 int n = 0;
     int arr[10000];
	 
	 
	 ifstream File;
	 File.open("R8a4.txt");
	  while(!File.eof())
    {
        File >> arr[n];
        n++;
    }
	 File.close();
	 
	 /*
	 for(int i=0; i<n; i++) {
		 if(i%7==0 && i!=0)
			 cout<<"\n";
		 cout<< arr[i] <<"  ";
		 
	 }
	 */
	 string checkCol[n/a];
	
	for(int l=0; l<n; l++) {
		checkCol[l/a]=checkCol[l/a]+to_string(arr[l])+" ";
	}
	
	/*
	for(int l=0; l<n/j; l++) {
		cout<<checkCol[l]<<"\n";
	}
	*/
	
	int firsttime = 1;
	
	for(int i=3; i<n/a; i+=3) {
			if(checkCol[i-3].compare(checkCol[i])==0 && firsttime>0) {
				cout<<checkCol[i-3]<<" has these rows to check: \n";
				
				cout<<checkCol[i-2]<<TileCheck(checkCol[i-2],a)<<"\n";
				firsttime--;
				if(checkCol[i].compare(checkCol[i+3])!=0)
					cout<<checkCol[i+1]<<TileCheck(checkCol[i+1],a)<<"\n";
			}
			else if(checkCol[i-3].compare(checkCol[i])==0){
				cout<<checkCol[i-2]<<TileCheck(checkCol[i-2],a)<<"\n";
				if(checkCol[i].compare(checkCol[i+3])!=0)
					cout<<checkCol[i+1]<<TileCheck(checkCol[i+1],a)<<"\n";
			}
			else {
				cout<<"\n";
				firsttime=1;
			}
	}	
	return 0;
}

string TileCheck(string Row, int a){
	cout<<"tile check begin";
	string response;
	int checkIt [a];
	int k=0;
	std::string delimiter = " ";
	size_t pos = 0;
std::string token;
while ((pos = Row.find(delimiter)) != std::string::npos) {
    token = Row.substr(0, pos);
	checkIt[k++]= (int) StringToNumber ( token, 0.0 );
    Row.erase(0, pos + delimiter.length());
}
cout<<"tile check";
response=ConsecutiveCheck(checkIt, a);

if(NewmanAble(a)){
	response=NewmanCheck(checkIt, a);
}





	return response;
}

string ConsecutiveCheck(int Check[], int a){
	int t=0;
	
	for(int i=0; i<a-1; i++) {
		t+=Check[i+1]-Check[i];
	}
	
	if(t==a-1)
		return "These tile";
	
	return "Need to check";
}

bool NewmanAble(int a){
	cout<<"Newman Check";
	for(int i=0; i<3; i++) {
		if(a==pow(2,i))
			return true;
	}
	
	for(int i=0; i<2; i++) {
		if(a==pow(3,i))
			return true;
	}
	
	if(a==5 || a==7 || a==11 || a==13)
		return true;
		
	return false;
}

string NewmanCheck(int Check[], int a){
	int p,alpha;
	
	if(a==2 || a==3 || a==5 || a==7 || a==11 || a==13){
		p=a;
		alpha=1;
	}
	else if(a==4|| a==9){
		p=(a,0.5);
		alpha=2;
	}
	else {
		p=2;
		alpha=3;
	}
		
	int differences[a*(a-1)/2];
	int d=0;
	for(int i=a-1; i>1; i--){
		for(int j=a-2; j<i; j--){
			differences[d++]=Check[i]-Check[j];
		}
	}
	
	bool Alpha3=false;
	bool Alpha2=false;
	bool Alpha1=false;
	bool Alpha0=false;
	
	
	for(int k=0; k<d; k++){
	
	if(differences[k]%p==0){
		Alpha1=true;
	}
	else if(differences[k]%(p*p)==0){
		Alpha2=true;
	}
	else if(differences[k]%(p*p*p)==0){
		Alpha3=true;
	} 	
	else{
		Alpha0=true;
	}
	}
	
	int Beta=0;
	
	if(Alpha0)
		Beta++;
	
	if(Alpha1)
		Beta++;
	
	if(Alpha2)
		Beta++;
	
	if(Alpha3)
		Beta++;
	
	if(Beta<=alpha)
		return "It tiles through the Newman Method";
	else
		return "It fails to tiles through the Newman Method.";
	
}
