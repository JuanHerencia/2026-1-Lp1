#include <stdio.h> 
#include <iostream>
using namespace std;
int main(void) { 
    char nombre[50]; 
    int  n,i = 0; 
cout<<"Ingrese el numero: ";
	cin>>n;
	while (i<n){
		cout<<i<<endl;
		i++;
	}


     return 0; 
} 

int calcular_nacimiento(int edad) { 
    return ANIO_ACTUAL - edad; 
} 
