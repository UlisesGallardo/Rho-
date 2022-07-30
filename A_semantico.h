
	#include <bits/stdc++.h>
	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <sstream>
	#include <queue>
	#include <stack>
	#include "A_sintactico.h"
	
	using namespace std;
	
	
	void Simular(vector <Instruccion*>vector_instrucciones, map<string, vector<string> >tabla_var){
		cout<<"-----------------------------------------------------------ANALIZADOR SEMANTICO-----------------------------------------\n";
		for(int i=0; i<vector_instrucciones.size(); i++){
			vector_instrucciones[i]->ejecutar(tabla_var);
		}
	}
	
	
	void simular_instrucciones(vector<vector<string> > t, map<string, string> instrucciones, map<string, vector<string> > &tabla_var){
		cout<<"-----------------------------------------------------------ANALIZADOR SINTACTICO-----------------------------------------\n";
		vector <Instruccion*>vector_instrucciones;
		Evaluar obj(tabla_var);
		vector_instrucciones = obj.ejecutar(t,instrucciones,tabla_var);
		for(int i=0; i<vector_instrucciones.size(); i++){
			vector_instrucciones[i]->print();
		}
		Simular(vector_instrucciones,tabla_var);
	}
	
