
	#include <bits/stdc++.h>
	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <sstream>
	#include <queue>
	#include "A_lexico.h"
	#include "A_semantico.h"
	
	using namespace std;	
	
	int main(){
		//Tokens
		map<string, string>token;
		//Tabla de símbolos o variables. 
		//todo almacenarlo como cadena y usar el identificaor de tipo de dato para cambiar los valores cuando sea necesario.
		map<string, vector<string> >tabla_var;
		
		//Tabla de instrucciones
		map<string, string> instrucciones;
		
		ifstream file,tabla;
		string name,n;
		name = "archivo1.txt";
		n = "NumeroToken.txt";
		file.open(name.c_str(),ios::in);
		tabla.open(n.c_str(),ios::in);
		
		string numero = " "; 
		while(!tabla.eof()){
			string txt;
			vector<string>v;
			getline(tabla,txt);
	    	if(isdigit(txt[0])){
				numero = txt;
			}else {
				token[txt] = numero;
				if(txt=="sigma"|| txt== "omega" || txt== "tau" || txt=="eta" || txt=="fi" || txt== "psi" || txt== "@" || txt ==";"){
					instrucciones[txt] = txt;//Cambiar por set? 
				}
			}				
		
		}
	
		//Analisis usando automata finito
		vector<vector<string> > t;//Total de tokens por todas cada l�nea del archivo,guardando el identificador, n�mero de token y tipo
		
		cout<<"-----------------------------------------------------------ANALIZADOR LEXICO-----------------------------------------\n";
		while(!file.eof()){
			string texto;
			vector<string>v;
			getline(file,texto);
			
			//stringstream tokens(texto);			
			vector<vector<string> > T = e_tokens(token,texto);//Obtener tokens por l�nea	
		
			for(int i=0; i<T.size(); i++){
				t.push_back(T[i]);	//Guardar todas las l�neas. 
			}
			
		}

		simular_instrucciones(t,instrucciones,tabla_var);
		
	}
