#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>
#include <math.h>

//NEED TO ADD EITHER FORMULA OR HARD WIRE MORE
using namespace std;	

//Declaring all of my functions
string TileCheck(string Row, int j);
string ConsecutiveCheck(int Check[], int a);
bool NewmanAble(int a);
string NewmanCheck(int Check[], int a);
int PolyDiv(int Check[], int BigPhi[], int a, int b);
string CM_Check(int a, int Check[]);
bool BigPi(bool SA[], int a);
bool T2_if(bool SA[]);
bool T2_then(bool SA[], int Check[], int a);
double evalPolyDiv(int N[],int Ndeg, int D[], int Ddeg, int point);

//Declaring my prime power Phi's globally 
//so I don't have to reallocate multiple times
	int Phi2  []={1,1};
	int Phi3  []={1,1,1};
	int Phi4  []={1,0,1};
	int Phi5  []={1,1,1,1,1};
	int Phi8  []={1,0,0,0,1};
	int Phi7  []={1,1,1,1,1,1,1};
	int Phi9  []={1,0,0,1,0,0,1};
	int Phi11 []={1,1,1,1,1,1,1,1,1,1,1};
	int Phi13 []={1,1,1,1,1,1,1,1,1,1,1,1,1};
    int Phi17 []={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
/////////////////////////////////////////////////////

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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////	
int main(){
	 int R=18; //Size of original Fourier Matrix RxR
	 int a=6; //Size of created Hadamard submatrix
	 int n = 0; //Number of numbers in the .txt file
     int arr[100000]; //Large array to hold numbers
	 
	 //Reading .txt file shenanigans 
	 ifstream File;
	 File.open("R18a6.txt");
	  while(!File.eof())
    {
        File >> arr[n];
        n++;
    }
	 File.close();
	 //cout<<n<<endl;
	 //Array of strings to check to see if columns are the same
	 //I Found strings to be easier check because of concat
	 string checkCol[n/a+3];
	
	for(int l=0; l<n; l++) {
		checkCol[l/a]=checkCol[l/a]+to_string(arr[l])+" ";
	}
	
	
	int firsttime = 1;
	
	//Will Check all of the columns for sameness
	//If they are the same they will cout the line and run it through tiling checks.
	for(int i=2; i<((n/a)-2); i+=2) {
			if(checkCol[i-2].compare(checkCol[i])==0 && firsttime>0) {
				cout<<checkCol[i-2]<<" has these rows that are the same: \n \n";
				
				cout<<checkCol[i-1]<<TileCheck(checkCol[i-1],a)<<"\n";
				firsttime--;
				if(checkCol[i].compare(checkCol[i+2])!=0)
					cout<<checkCol[i+1]<<TileCheck(checkCol[i+1],a)<<"\n  \n  \n";
			}
			else if(checkCol[i-2].compare(checkCol[i])==0){
				cout<<checkCol[i-1]<<TileCheck(checkCol[i-1],a)<<"\n";
				if(checkCol[i].compare(checkCol[i+2])!=0)
					cout<<checkCol[i+1]<<TileCheck(checkCol[i+1],a)<<"\n  \n \n";
			}
			else {
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

//We are testing this first as opposed to Newman for testing CM
//I'll flip this around later to increase performace



response=CM_Check(a, checkIt);

cout<<response<<endl;
if(response.compare("Needs to be checked.")==0 && NewmanAble(a)){
	response=NewmanCheck(checkIt, a);
	//cout<<"Newman";
}

if(response.compare("Needs to be checked.")==0){
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
		return "These tile (consecutive)";
	
	return "Need to check";
}

//This function checks to see if we can use Newman Method
//Only checks numbers that we can likely produce currently
bool NewmanAble(int a){
	for(int i=0; i<4; i++) {
		if(a==pow(2,i))
			return true;
	}
	
	for(int i=0; i<3; i++) {
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
	for(int i=a-1; i>=0; i--){
		for(int j=i-1;  j>-1 ; j--){
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
	else if(differences[k]%p==0){
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
		return "                                     BIG FAILURE!!! LOOK AT THIS!!!.";
	
}

//Instead of Long Div I am using deg of Check+1 function evals
int PolyDiv(int Check[], int BigPhi[], int a, int b) {

bool alwaysZero=true;


//makes the Check array into an easier to process form
int N[a+1];
int CheckCoef=0;					
	for (int i = 0; i < a+1; i++ ) {
		if(Check[CheckCoef]==i){
			N[i]=1;
			CheckCoef++;
		}
		else{
			N[i]=0;
		}
	}

//the Deg of A(x) +1 function evals
//If A(x_0) mod Phi(x_0) != 0 then it will be false
for(int i=0; i<4;i++){
   if(evalPolyDiv(N,a+1,BigPhi,b+1,i)!=0)
    alwaysZero=false;
}

	return alwaysZero;
}


//this function will return A(x_0) mod Phi(x_0)
double evalPolyDiv(int N[],int Ndeg, int D[], int Ddeg, int point){
     int Neval=0;
     int Deval=0;

    for(int i=0; i<Ndeg; i++){
        Neval+=N[i]*pow(point,i);
    }

    for(int i=0; i<Ddeg; i++){
        Deval+=D[i]*pow(point,i);
    }
	//cout<<"pointth time "<<point<<"   Neval: "<<Neval<<"  Deval:  "<<Deval<<endl;
	//cout<<Neval%Deval<<endl;
    return Neval%Deval;

}

//This function tests the CM Properties
string CM_Check(int a, int Check[]){

	int polyDeg=Check[a-1];
	//This array of booleans will track our set of S_A 's
	//I am indexing this with 0 (i.e. if Phi_2 divides SA[2]==true)
	bool SA[100];
	
//This series of if statements will generate S_A up to 17
	if(polyDeg>=1){
		SA[2]=PolyDiv(Check, Phi2, polyDeg, 1);
		//cout<<" Phi_2 : "<<SA[2]<<endl;
	}

	if(polyDeg>=2){
		SA[3]=PolyDiv(Check, Phi3, polyDeg, 2);
		//cout<<"Phi_3 : "<<SA[3]<<endl;
		SA[4]=PolyDiv(Check, Phi4, polyDeg, 2);
		//cout<<"Phi_4 : "<<SA[4]<<endl;
	}


	if(polyDeg>=4){
		SA[5]= PolyDiv(Check, Phi5, polyDeg, 4); //4
		//cout<<" Phi_5 : "<<SA[5]<<endl;
		SA[8]=PolyDiv(Check, Phi8, polyDeg, 4);
		//cout<<" Phi_8 : "<<SA[8]<<endl;
	}

	if(polyDeg>=6){
		SA[7]= PolyDiv(Check, Phi7, polyDeg, 6); //6
		//cout<<" Phi_7 : "<<SA[7]<<endl;
		SA[9]=PolyDiv(Check, Phi9, polyDeg, 6);
		//cout<<" Phi_9 : "<<SA[9]<<endl;
	}

	if(polyDeg>=10){
		SA[11]= PolyDiv(Check, Phi11, polyDeg, 10); //10
		//cout<<" Phi_11 : "<<SA[11]<<endl;
	}

	if(polyDeg>=12){
		SA[13]= PolyDiv(Check, Phi13, polyDeg, 12); //12
		//cout<<" Phi_13 : "<<SA[13]<<endl;
	}

	if(polyDeg>=16){
		SA[17]= PolyDiv(Check, Phi17, polyDeg, 16); //16
		//cout<<" Phi_17 : "<<SA[17]<<endl;
	}

	//Starting to test T1

	bool T1=false;

	//BigPi returns true if A(1)=the multiplication 
	T1=BigPi(SA,a);

	//So we know if T1 worked
	if(T1){
		cout<< "T1 WIN!";
	}


	//Starting to test T2
	bool T2=false;

	//Not if or then is implies 
	//T2_if(SA) will check for duplicate prime powers (hard wired for our small possibilities)
	//T2_then will multiply out the SA's and the check if Phi_{\forall s \in S} divides A(x)
	//Note: T2_then does not run if NOT T2_if is true
	T2=(!(T2_if(SA))||(T2_then(SA,Check,a)));

	if(T2){
		cout<< "T2 win!!";
	}
//If both conditions are met we return CM Met for the set
if(T1&&T2){
return "CM Met";

}

//Otherwise return needs to be checked
return "Needs to be checked.";
}

bool BigPi(bool SA[], int a){

	int BigPiValue=1;
//These Phi_prime power(1) always equals it's base prime
//Will make this Big number proof later
	if(SA[2])
	BigPiValue*=2;

	if(SA[3])
	BigPiValue*=3;

	if(SA[4])
	BigPiValue*=2;

	if(SA[5])
	BigPiValue*=5;

	if(SA[7])
	BigPiValue*=7;

	if(SA[8])
	BigPiValue*=2;

	if(SA[9])
	BigPiValue*=3;

	if(SA[11])
	BigPiValue*=11;

	if(SA[13])
	BigPiValue*=13;

	if(SA[17])
	BigPiValue*=17;

//cout<<"Big Pi Value: "<<BigPiValue<<endl;
if(BigPiValue==a)
	return true;

return false;

}

bool T2_if(bool SA[]){

//	cout<<"if is running"<<endl;
//will make work for big numbers later

	if(SA[2]&&SA[4])
		return false;

	if(SA[2]&&SA[8])
		return false;

	if(SA[8]&&SA[4])
		return false;

	if(SA[3]&&SA[9])
		return false;


		return true;
}

bool T2_then(bool SA[], int Check[], int a){

	//cout<<"T2_then needed"<<endl;

	int BigS=1;
//finds the product of all s \in S_A
	for(int i=1; i<30; i++){
		if(SA[i])
		BigS*=i;
	}

//Catches the cases when S_A is just one element
if(BigS==2 || BigS==3 || BigS==4 || BigS==5 || BigS==7 || BigS==8 || BigS== 9 || BigS==11 || BigS==13 || BigS==17)
	return true; 

//The rest
if(BigS==6){
	int Phi6 []={1,-1,1};
	return PolyDiv(Check, Phi6  ,Check[a-1], 2);
}
else if(BigS==10){
	int Phi10 []={1,-1,1,-1,1};
	return PolyDiv(Check, Phi10  ,Check[a-1], 4);
}
else if(BigS==12){
	int Phi12 []={1,0,-1,0,1};
	return PolyDiv(Check, Phi12  ,Check[a-1], 4);
}
else if(BigS==14){
	int Phi14 []={1,-1,1,-1,1,-1,1};
	return PolyDiv(Check, Phi14  ,Check[a-1], 6);
}
else if(BigS==15){
	int Phi15 []={1,-1,0,1,-1,1,0,-1,1};
	return PolyDiv(Check, Phi15  ,Check[a-1], 8);
}
else if(BigS==16){
	int Phi16 []={1,0,0,0,0,0,0,0,1};
	return PolyDiv(Check, Phi16  ,Check[a-1], 8);
}
else if(BigS==18){
	int Phi18 []={1,0,0,-1,0,0,1};
	return PolyDiv(Check, Phi18  ,Check[a-1], 6);
}
else if(BigS==20){
	int Phi20 []={1,0,-1,0,1,0,-1,0,1};
	return PolyDiv(Check, Phi20  ,Check[a-1], 8);
}
else if(BigS==21){
	int Phi21 []={1,-1,0,1,-1,1,0,-1,1};
	return PolyDiv(Check, Phi21  ,Check[a-1], 8);
}
else if(BigS==22){
	int Phi22 []={1,-1,1,-1,1,-1,1,-1,1,-1,1};
	return PolyDiv(Check, Phi22 ,Check[a-1], 10);
}
else if(BigS==22){
	int Phi22 []={1,-1,1,-1,1,-1,1,-1,1,-1,1};
	return PolyDiv(Check, Phi22 ,Check[a-1], 10);
}
else if(BigS==24){
	int Phi24 []={1,0,0,0,-1,0,0,0,1};
	return PolyDiv(Check, Phi24 ,Check[a-1], 8);
}
else if(BigS==26){
	int Phi26 []={1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1};
	return PolyDiv(Check, Phi26 ,Check[a-1], 12);
}
else if(BigS==27){
	int Phi27 []={1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1};
	return PolyDiv(Check, Phi27 ,Check[a-1], 12);
}



	

return false;
}
