#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;	

//Declaring all of my functions
string TileCheck(string Row, int j);
string ConsecutiveCheck(int Check[], int a);
bool NewmanAble(int a);
string NewmanCheck(int Check[], int a);


//Converts things to strings
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

//Converts strings to numbers
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
	 int R=8; //Size of original Fourier Matrix RxR
	 int a=4; //Size of created Hadamard submatrix
	 int n = 0; //Number of numbers in the .txt file
     int arr[100]; //Large array to hold numbers
	 
	 //Reading .txt file shenanigans 
	 ifstream File;
	 File.open("test.txt");
	  while(!File.eof())
    {
        File >> arr[n];
        n++;
    }
	 File.close();
	 
	 //Array of strings to check to see if columns are the same
	 //I Found strings to be easier check because of concat
	 string checkCol[n/a];
	
	for(int l=0; l<n; l++) {
		checkCol[l/a]=checkCol[l/a]+to_string(arr[l])+" ";
	}
	
	
	int firsttime = 1;
	
	//Will Check all of the columns for sameness
	//If they are the same they will cout the line and run it through tiling checks.
	for(int i=3; i<((n/a)-3); i+=3) {
			if(checkCol[i-3].compare(checkCol[i])==0 && firsttime>0) {
				cout<<checkCol[i-3]<<" has these rows that are the same: \n";
				
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
	//Will let us know if the subsequence works
	string response;
	//Small array of the subsequence 
	int checkIt [a];
	//Splices the string back into ints
	int k=0;
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	while ((pos = Row.find(delimiter)) != std::string::npos) {
    token = Row.substr(0, pos);
	checkIt[k++]= (int) StringToNumber ( token, 0.0 );
    Row.erase(0, pos + delimiter.length());
}


//Only have Newman Power of Prime method and consecutive to check tiling
//Currently

if(NewmanAble(a)){
	response=NewmanCheck(checkIt, a);
}
else{
	response=ConsecutiveCheck(checkIt, a);
}
	return response;
}

//This function will see if the difference between every element of the 
//subsequence is 1 and return the apropiate response.
string ConsecutiveCheck(int Check[], int a){
	int t=0;
	
	for(int i=0; i<a-1; i++) {
		t+=Check[i+1]-Check[i];
	}
	
	if(t==a-1)
		return "These tile";
	
	return "Need to check";
}

//This function checks to see if we can use Newman Method
//Only checks numbers that we can likely produce currently
bool NewmanAble(int a){
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


//Still only works for smaller a values.
string NewmanCheck(int Check[], int a){
	int p,alpha;
	
	if(a==2 || a==3 || a==5 || a==7 || a==11 || a==13){
		p=a;
		alpha=1;
	}
	else if(a==4|| a==9){
		p=pow(a,0.5);
		alpha=2;
	}
	else {
		p=2;
		alpha=3;
	}
	
	int differences[(a*(a-1))/2];
	int d=0;
	for(int i=a-1; i>1; i--){
		for(int j=a-2; j<i && j>0 ; j--){
			differences[d++]=Check[i]-Check[j];
		}
	}
	
	bool Alpha3=false;
	bool Alpha2=false;
	bool Alpha1=false;
	bool Alpha0=false;
	
	for(int k=0; k<d; k++){
	
	if(differences[k]%(p*p*p)==0){
		Alpha3=true;
	}
	else if(differences[k]%(p*p)==0){
		Alpha2=true;
	}
	else (differences[k]%p==0){
		Alpha1=true;
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
		return "It tiles through the Newman Method.";
	else	
		return "It fails to tiles through the Newman Method.";
	
}
