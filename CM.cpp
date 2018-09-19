//Most Up to date version of Tiling Check Program
//Can handle Newman Method

//CM Properties
//Can Check Condition T1 (up to deg{A}<=20)
//Can Check Condition T2 (unreliably)


//Tiling Set
//Need to Get Period N
//Need to Get Translation Set B

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>
#include <math.h>
#include <vector>

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
string findB(bool SA[], int N);
bool isPrimePower(int n);


void Print(char c, int d, double* A) {
	int i;

	for (i=0; i < d+1; i++)
			cout << c << "[" << i << "]= " << A[i] << endl;
	cout << "Degree of " << c << ": " << d << endl << endl;
}

int gcd(int a, int b) 
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
} 

vector<int> PolyMultiply(int A[], vector<int> B, int m, int n) 
{ 
   int *prod = new int[m+n-1]; 
  
   // Initialize the porduct polynomial 
   for (int i = 0; i<m+n-1; i++) 
     prod[i] = 0; 
  
int Barray[n];
for(int q=n-1; q> -1; q--){
Barray[q]=B.back();
B.pop_back();
}
   // Multiply two polynomials term by term 
  
   // Take ever term of first polynomial 
   for (int i=0; i<m; i++) 
   { 
     // Multiply the current term of first polynomial 
     // with every term of second polynomial. 
     for (int j=0; j<n; j++) 
         prod[i+j] += A[i]*Barray[j]; 
   } 

   vector<int> answer;

   for(int h=0;h<m+n-1;h++){
	   answer.push_back(prod[h]);
   }
  
   return answer; 
} 

int findlcm(bool arr[], int n) 
{ 
	int ans=0;
    // Initialize result 
	for(int q=1; q<n; q++){
		if(arr[q]){
		ans = arr[q]; 
		q=n+2;
		}
	}
    
  
    // ans contains LCM of arr[0], ..arr[i] 
    // after i'th iteration, 
    for (int i = 1; i < n; i++)
		if(arr[i]){ 
        ans = (((i * ans)) / 
                (gcd(i, ans))); 
		}
  
    return ans; 
} 

//Declaring my prime power Phi's globally 
//so I don't have to reallocate multiple times
	int Phi2  []={1,1};
	int Phi3  []={1,1,1};
	int Phi4  []={1,0,1};
	int Phi5  []={1,1,1,1,1};
	int Phi8  []={1,0,0,0,1};
	int Phi7  []={1,1,1,1,1,1,1};
	int Phi9  []={1,0,0,1,0,0,1};
	int Phi16 []={1,0,0,0,0,0,0,0,1};
	int Phi11 []={1,1,1,1,1,1,1,1,1,1,1};
	int Phi13 []={1,1,1,1,1,1,1,1,1,1,1,1,1};
    int Phi17 []={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	int Phi32 []={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	int Phi19 []={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	int Phi27 []={1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1};
	int Phi25 []={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
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
	 int R=15; //Size of original Fourier Matrix RxR
	 int a=3; //Size of created Hadamard submatrix
	 int n = 0; //Number of numbers in the .txt file
     int arr[1000000]; //Large array to hold numbers
	 
	 //Reading .txt file shenanigans 
	 ifstream File;
	 File.open("data/R15a3.txt");
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
	
	
	
	ofstream FileOut;
	FileOut.open("data/R15a3tilesets.txt");
	int firsttime = 1;
	//Will Check all of the columns for sameness
	//If they are the same they will cout the line and run it through tiling checks.
	for(int i=3; i<((n/a)-3); i+=3) {
			if(checkCol[i-3].compare(checkCol[i])==0 && firsttime>0) {
				cout<<checkCol[i-3]<<" has these rows that are the same: \n \n";
				FileOut<<checkCol[i-3]<<" has these rows that are the same: \n \n";
				
				cout<<checkCol[i-2]<<TileCheck(checkCol[i-2],a)<<"\n";
				FileOut<<checkCol[i-2]<<TileCheck(checkCol[i-2],a)<<"\n";
				firsttime--;
				if(checkCol[i].compare(checkCol[i+3])!=0){
					cout<<checkCol[i+1]<<TileCheck(checkCol[i+1],a)<<"\n  \n  \n";
					FileOut<<checkCol[i+1]<<TileCheck(checkCol[i+1],a)<<"\n  \n  \n";
				}
					
			}
			else if(checkCol[i-3].compare(checkCol[i])==0){
				cout<<checkCol[i-2]<<TileCheck(checkCol[i-2],a)<<"\n";
				FileOut<<checkCol[i-2]<<TileCheck(checkCol[i-2],a)<<"\n";
				if(checkCol[i].compare(checkCol[i+3])!=0){
					cout<<checkCol[i+1]<<TileCheck(checkCol[i+1],a)<<"\n  \n \n";
					FileOut<<checkCol[i+1]<<TileCheck(checkCol[i+1],a)<<"\n  \n \n";
				}
					
			}
			else {
				firsttime=1;
			}
	}

	FileOut.close();	
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



response=CM_Check(a, checkIt)+"\n";

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

	int dN, dD, dd, dq, dr;	// degrees of vectors
	int i;					// iterators

// setting the degrees of vectors
	dN=a;
	dD=b;
	dq = dN-dD;
	dr = dD-1;


// allocation and initialization of vectors
	double N[dN+1];	
	int checkNumber=0;	
	for ( int i = 0; i < dN+1; i++ ) {
		if(Check[checkNumber]==i){
			N[i]=1;
			checkNumber++;
		}
		else{
			N[i]=0;
		}
	}




	double D[dN+1];
	//cout << "Enter the coefficients of D:"<<endl;	
	for ( int i = 0; i < dD+1; i++ ) {
		D[i]=BigPhi[i];
	}

	double d[dN+1];
	for( i = dD+1 ; i < dN+1; i++ ) {
		D[i] = 0;
	}

	double q[dq+1];
	for( i = 0 ; i < dq + 1 ; i++ ) {
		q[i] = 0;
	}

	double r[dr+1];
	for( i = 0 ; i < dr + 1 ; i++ ) {
		r[i] = 0;
	}

	if( dD < 0) {
	//	cout << "Degree of D is less than zero. Error!";
	}

	//cout << "-- Procedure --" << endl << endl;
	if( dN >= dD ) {
		while(dN >= dD) {
// d equals D shifted right
			for( i = 0 ; i < dN + 1 ; i++ ) {
				d[i] = 0;
			}
			for( i = 0 ; i < dD + 1 ; i++ ) {
				d[i+dN-dD] = D[i];
			}
			dd = dN;

			//Print( 'd', dd, d );

// calculating one element of q
			q[dN-dD] = N[dN]/d[dd];

			//Print( 'q', dq, q );

// d equals d * q[dN-dD]
			for( i = 0 ; i < dd + 1 ; i++ ) {
				d[i] = d[i] * q[dN-dD];
			}

			//Print( 'd', dd, d );

// N equals N - d
			for( i = 0 ; i < dN + 1 ; i++ ) {
				N[i] = N[i] - d[i];
			}
			dN--;
			for(int j=dN; j>-1; j--){
				if(N[j]!=0){
					dN=j;
					j=-1;
				}
			}

			//Print( 'N', dN, N );
			//cout << "-----------------------" << endl << endl;

		}

	}

// r equals N
	for( i = 0 ; i < dN + 1 ; i++ ) {
		r[i] = N[i];
	}
	dr = dN;

	//cout << "=========================" << endl << endl;
	//cout << "-- Result --" << endl << endl;

//Print( 'q', dq, q );
//	Print( 'r', dr, r );

	

	bool answer=true;

	for(int i=0; i<=dr; i++){
		if(r[i]!=0)
		answer=false;
	}
	


return answer;
}



//This function tests the CM Properties
string CM_Check(int a, int Check[]){

	int polyDeg=Check[a-1];
	//This array of booleans will track our set of S_A 's
	//I am indexing this with 0 (i.e. if Phi_2 divides SA[2]==true)
	bool SA[100];
	for(int i=0;i<50;i++)
		SA[i]=false;
//This series of if statements will generate S_A up to 17
	if(polyDeg>=1){
		SA[2]=PolyDiv(Check, Phi2, polyDeg, 1);
		if(SA[2])
			cout<<" Phi_2 : "<<SA[2]<<endl;
	}

	if(polyDeg>=2){
		SA[3]=PolyDiv(Check, Phi3, polyDeg, 2);
		if(SA[3])
			cout<<"Phi_3 : "<<SA[3]<<endl;

		SA[4]=PolyDiv(Check, Phi4, polyDeg, 2);
		if(SA[4])
			cout<<"Phi_4 : "<<SA[4]<<endl;
	}


	if(polyDeg>=4){
		SA[5]= PolyDiv(Check, Phi5, polyDeg, 4); //4
		if(SA[5])
			cout<<" Phi_5 : "<<SA[5]<<endl;
		SA[8]=PolyDiv(Check, Phi8, polyDeg, 4);
		if(SA[8])
			cout<<" Phi_8 : "<<SA[8]<<endl;
	}

	if(polyDeg>=6){
		SA[7]= PolyDiv(Check, Phi7, polyDeg, 6); //6
		if(SA[7])
			cout<<" Phi_7 : "<<SA[7]<<endl;
		SA[9]=PolyDiv(Check, Phi9, polyDeg, 6);
		if(SA[9])
			cout<<" Phi_9 : "<<SA[9]<<endl;
	}

	if(polyDeg>=8){
		SA[16]=PolyDiv(Check, Phi16, polyDeg, 8); //6
			if(SA[16])
			cout<<" Phi_16 : "<<SA[16]<<endl;
	}

	if(polyDeg>=10){
		SA[11]= PolyDiv(Check, Phi11, polyDeg, 10); //10
		if(SA[11])
			cout<<" Phi_11 : "<<SA[11]<<endl;
	}

	if(polyDeg>=12){
		SA[13]= PolyDiv(Check, Phi13, polyDeg, 12); //12
		if(SA[13])
			cout<<" Phi_13 : "<<SA[13]<<endl;
	}

	if(polyDeg>=16){
		SA[17]= PolyDiv(Check, Phi17, polyDeg, 16); //16
		if(SA[17])
		cout<<" Phi_17 : "<<SA[17]<<endl;
		SA[32]= PolyDiv(Check, Phi32, polyDeg, 16);
		if(SA[32])
		cout<<" Phi_32 : "<<SA[32]<<endl;
	}

	if(polyDeg>=18){
		SA[19]= PolyDiv(Check, Phi19, polyDeg, 18); //18
		if(SA[19])
		cout<<" Phi_19 : "<<SA[19]<<endl;
		SA[27]= PolyDiv(Check, Phi27, polyDeg, 18);
		if(SA[27])
		cout<<" Phi_27 : "<<SA[27]<<endl;
	}

	if(polyDeg>=20){
		SA[25]= PolyDiv(Check, Phi25, polyDeg, 20); //20
		if(SA[25])
		cout<<" Phi_25 : "<<SA[25]<<endl;
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
	int N=findlcm(SA,30); 
	string B=findB(SA,N);
	cout<<B<<endl;
return "CM Met"+B;

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

	if(SA[16])
	BigPiValue*=2;

	if(SA[17])
	BigPiValue*=17;

	if(SA[19])
	BigPiValue*=19;

	if(SA[25])
	BigPiValue*=5;

	if(SA[27])
	BigPiValue*=3;

	if(SA[32])
	BigPiValue*=2;

	

//cout<<"Big Pi Value: "<<BigPiValue<<endl;
//cout<<"A "<<a<<endl;
if(BigPiValue==a)
	return true;

return false;

}

bool T2_if(bool SA[]){

//	cout<<"if is running"<<endl;
//will make work for big numbers later

	if(SA[2]&&SA[3])
		return true;

	if(SA[3]&&SA[8])
		return true;

	if(SA[3]&&SA[4])
		return true;

	if(SA[16]&&SA[3])
		return true;

	if(SA[2]&&SA[9])
		return true;

	if(SA[9]&&SA[8])
		return true;

	if(SA[9]&&SA[4])
		return true;

	if(SA[16]&&SA[9])
		return true;

	if(SA[2]&&SA[5])
		return true;

	if(SA[5]&&SA[8])
		return true;

	if(SA[5]&&SA[4])
		return true;

	if(SA[16]&&SA[5])
		return true;



		return false;
}

bool T2_then(bool SA[], int Check[], int a){

	//cout<<"T2_then needed"<<endl;

	int BigS=1;
//finds the product of all s \in S_A
	for(int i=1; i<50; i++){
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

string findB(bool SA[], int N){

	
	vector<int> SAnumbers;

	for(int i=0; i<25; i++){
		if(SA[i])
			SAnumbers.push_back(i);
	}

	int Nfactors[N+1];

	for(int i=1; i<N+1; i++){
		if(N%i==0){
			Nfactors[i]=i;
		}
		else Nfactors[i]=0;
	}

	//for(int i=1; i<N+1; i++)
	//	cout<<i<<":   "<<Nfactors[i];

	vector<int> SB;

	for(int i=1; i<N+1; i++){
		if(isPrimePower(Nfactors[i])){
			int whatever=0;
			for(int j=0; j<SAnumbers.size(); j++){
				if(Nfactors!=0 && Nfactors[i]!=SAnumbers.at(j)){
					whatever++;
				}
			}
			if(whatever==SAnumbers.size())
			SB.push_back(Nfactors[i]);
		}
	}


string period = to_string(N);
string answer= "  T="+period+"Z";
vector<int> B;
B.push_back(1);
///////////////////////////

for(int j=SB.size(); j>0; j--){

int max=1;
	//Need to look at SB.bacK()

for(int i=1; i<N+1; i++){
if(Nfactors[i]!=0 && gcd(SB.back(),i)==1 && i>max)
	max=i;
}

if(max==1){
	if(SB.back()==2)
		B=PolyMultiply(Phi2,B,2,B.size());
	else if(SB.back()==3)
		B=PolyMultiply(Phi3,B,3,B.size());
	else if(SB.back()==4)
		B=PolyMultiply(Phi4,B,3,B.size());
	else if(SB.back()==5)
		B=PolyMultiply(Phi5,B,5,B.size());	
	else if(SB.back()==7)
		B=PolyMultiply(Phi7,B,7,B.size());
	else if(SB.back()==8)
		B=PolyMultiply(Phi8,B,5,B.size());
	else if(SB.back()==9)
		B=PolyMultiply(Phi9,B,7,B.size());
	else if(SB.back()==11)
		B=PolyMultiply(Phi11,B,11,B.size());
	else if(SB.back()==13)
		B=PolyMultiply(Phi13,B,13,B.size());
	else if(SB.back()==16)
		B=PolyMultiply(Phi16,B,9,B.size());

} else{

	if(SB.back()==2){
		int Comp[2*max-1];

		for(int i=0; i<2*max-1; i++){
			Comp[i]=0;
		}

		for(int i=0; i<2; i++){
			Comp[max*i]=Phi2[i];
		}

		B=PolyMultiply(Comp,B,2*max-1,B.size());
	} else if(SB.back()==3){
		int Comp[3*max-1];

		for(int i=0; i<3*max-1; i++){
			Comp[i]=0;
		}

		for(int i=0; i<3; i++){
			Comp[max*i]=Phi3[i];
		}

		B=PolyMultiply(Comp,B,3*max-1,B.size());
	} else if(SB.back()==4){
		int Comp[3*max-1];

		for(int i=0; i<3*max-1; i++){
			Comp[i]=0;
		}

		for(int i=0; i<3; i++){
			Comp[max*i]=Phi4[i];
		}

		B=PolyMultiply(Comp,B,3*max-1,B.size());
	} else if(SB.back()==5){
		int Comp[5*max-1];

		for(int i=0; i<5*max-1; i++){
			Comp[i]=0;
		}

		for(int i=0; i<5; i++){
			Comp[max*i]=Phi5[i];
		} 

		B=PolyMultiply(Comp,B,5*max-1,B.size());
	} else if(SB.back()==7){
		int Comp[7*max-1];

		for(int i=0; i<7*max-1; i++){
			Comp[i]=0;
		}

		for(int i=0; i<7; i++){
			Comp[max*i]=Phi7[i];
		}

		B=PolyMultiply(Comp,B,7*max-1,B.size());
	} else if(SB.back()==8){
		int Comp[5*max-1];

		for(int i=0; i<5*max-1; i++){
			Comp[i]=0;
		}

		for(int i=0; i<5; i++){
			Comp[max*i]=Phi8[i];
		}

		B=PolyMultiply(Comp,B,5*max-1,B.size());
	} else if(SB.back()==9){
		int Comp[7*max-1];

		for(int i=0; i<7*max-1; i++){
			Comp[i]=0;
		}

		for(int i=0; i<7; i++){
			Comp[max*i]=Phi9[i];
		}

		B=PolyMultiply(Comp,B,7*max-1,B.size());
	}else if(SB.back()==11){
		int Comp[11*max-1];

		for(int i=0; i<11*max-1; i++){
			Comp[i]=0;
		}

		for(int i=0; i<11; i++){
			Comp[max*i]=Phi11[i];
		}

		B=PolyMultiply(Comp,B,11*max-1,B.size());
	} else if(SB.back()==13){
		int Comp[13*max-1];

		for(int i=0; i<13*max-1; i++){
			Comp[i]=0;
		}

		for(int i=0; i<13; i++){
			Comp[max*i]=Phi13[i];
		}

		B=PolyMultiply(Comp,B,13*max-1,B.size());
	} else if(SB.back()==16){
		int Comp[9*max-1];

		for(int i=0; i<9*max-1; i++){
			Comp[i]=0;
		}

		for(int i=0; i<9; i++){
			Comp[max*i]=Phi16[i];
		}

		B=PolyMultiply(Comp,B,9*max-1,B.size());
	}

}


if(SB.size()==1){
	int abc=0;
	answer=answer+" + {";
	for(int k=0; k<B.size(); k++){
		if(abc!=0 && B.at(k)!=0){
			answer=answer+" , "+to_string(k);
		}
		if(abc==0 && B.at(k)!=0){
			answer=answer+to_string(k);
			abc++;
		}
	}
		answer=answer+"}";
}

SB.pop_back();
}
ofstream FileOut;

//////////////////////////
return answer;
}

bool isPrimePower(int n){

	if(n==0 || n==1)
		return false;

	if(n==2 || n==4 || n==8 || n==16 || n==32)
		return true;

	if(n==3 || n==9 || n==27)
		return true;

	if(n==5 || n== 25)
		return true;

	if(n==7 || n==11 || n==13 ||n==17 || n==19 || n==23 || n==29)
		return true;
	
	return false;

}

	

