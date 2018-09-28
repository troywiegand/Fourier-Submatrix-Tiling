//This is the first version of the Tiling Check Program that only does Newman method


#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

string NewmanCheck(int Check[], int a);

int main(){ 
int a;
cout<<"How big is this subsequence? ";
cin>>a;
int Check[a];
for(int i=0; i<a; i++){
	cout<<"Enter the "<<i<<" th element:";
	cin>>Check[i];
}

for(int i=0; i<a; i++){
	cout<<Check[i]<<"   ";
}

cout<<"\n"<<NewmanCheck(Check, a)<<endl;



return 0;
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
		return " BIG FAILURE!!! LOOK AT THIS!!!.";
	
}