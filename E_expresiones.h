
	#include <bits/stdc++.h>
	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <sstream>
	#include <queue>
	#include <stack>
	
	using namespace std;
	
	map<string,int>mapa;
	
	string remover(string s){
		s.erase(remove(s.begin(),s.end(),' '),s.end());
		return s;
	}
	
	vector<string> dividir(string s){
		vector<string>div;
		string num="";
		for(int i=0; i<(int)s.size();i++){
			
			if(isdigit(s[i])){
				int ini =i,con=i;
				bool flotante = false;
				
				
				
				while((isdigit(s[con]) || s[i]=='.') && con<s.size()){
					if(s[i]=='.'){
						flotante = true;
					}
					num+=s[con];
					i++;
					con++;
				}
				if(ini-1==0){	//Caso donde el numero es -1 al principio de cadena.
						if(!isdigit(s[ini-1])) {
							if(!(s[ini-1] == '('  || s[ini-1] == ')')){
								num=s[ini-1]+num;
							}
					}
				}else{	//Caso donde hay signo entre dos numeros
					if(ini-2>=0){	
						if(!isdigit(s[ini-2]) && !isdigit(s[ini-1]) && !(s[ini-1]=='(' || s[ini-1]==')' ) && s[ini-1]!='@'){ //Caso donde hay dos signos juntos
							num=s[ini-1]+num;
					 	}	
					}
				}
				
				
				
					
				//CAMBIAR A FLOTANTE O A ENTERO
				if(flotante){
					div.push_back(to_string(stof(num)));	
				}else{
					div.push_back(to_string(stoi(num)));	
				}
				
				num="";
			}
			if(i >=s.size()  ){		//En el caso de que i salga del rango
				break;
			}
			
			if(s[i]=='$'){
				string variable="";
				variable+=s[i];
				i++;
				int con=i;
				
				string valor="";
				stringstream ss;
				ss<<s[con];
				ss>>valor;
				//cout<<"valor"<<valor<<" ";
				//cout<<s<<"\n";
				while(con<s.size()){
					if(mapa.find(valor)!=mapa.end()) break;
					valor = "";
					variable+=s[con];
					i++;
					con++;
					
					stringstream char_to_string;
					char_to_string<<s[con];
					char_to_string>>valor;
					//cout<<"valor"<<valor<<" ";
				}
				//cout<<"variable:"<<variable<<"<-";
				div.push_back(variable);
				
			}
			if((s[i]=='(' || s[i]==')')){
				stringstream ss; 
				string h="";
				ss<<s[i]; 
				ss>>h;
				div.push_back(h);
			}else if(!isdigit(s[i])){
				string booleano = "";
				
				if(s[i]=='>'){
					booleano+=s[i];
					s[i]='@';
					if(s[i+1]== '=' ){
						booleano+=s[i+1];
						s[i+1]='@';
						i++;
					}
				}else if(s[i]=='<'){
					booleano+=s[i];
					s[i]='@';
					if(s[i+1]== '=' ){
						booleano+=s[i+1];
						s[i+1]='@';
						i++;
					}
				}else if(s[i]=='='){
					booleano+=s[i];
					s[i]='@';
					if(s[i+1]== '=' ){
						booleano+=s[i+1];
						s[i+1]='@';
						i++;
					}
				}else if(s[i]=='!'){
					booleano+=s[i];
					s[i]='@';
					if(s[i+1]== '=' ){
						booleano+=s[i+1];
						s[i+1]='@';
						i++;
					}
				}else if(s[i]=='|'){
					if(s[i+1]=='|'){
						booleano+=s[i];
						booleano+=s[i+1];
						s[i]='@';
						s[i+1]='@';
						i++;
					}
				}else if(s[i]=='&'){
					if(s[i+1]=='&'){
						booleano+=s[i];
						booleano+=s[i+1];
						s[i]='@';
						s[i+1]='@';
						i++;
					}
				}
				
				if(booleano!=""){
					div.push_back(booleano);
				}else{
					stringstream ss; 
					string h="";
					ss<<s[i]; 
					ss>>h;
		 			if((s[i-1]!='+' || s[i-1]!='-') &&  s[i-1]!='@'){
		 				div.push_back(h);
		 				s[i]='@';
		 			}
				}
	 			//cout<<s<<"\n";
			}
		}
		return div;
	}
	
	
	queue<string> evaluar(vector<string> v){

		queue<string>q;
		stack<string>pila;
		
		for(int i=0; i<(int)v.size();i++){
			if(isdigit(v[i][v[i].size()-1]) || v[i][0]=='$'){
				q.push(v[i]);
			}else if(v[i]=="("){
				pila.push(v[i]);
			}else if(v[i]==")"){
				while(!pila.empty() && pila.top()!="("){
						q.push(pila.top());
						pila.pop();
				}	
				if(!pila.empty()) pila.pop();
			}else{
					while(!pila.empty() ){
						if(mapa[v[i]]<=mapa[pila.top()]&& pila.top()!="("){
							q.push(pila.top());
							pila.pop();
						}else{
							break;
						}
				    }		
				pila.push(v[i]);
			}
		}
		while(!pila.empty()){
			q.push(pila.top());
			pila.pop();
		}
		
		return q;
	}


	float evaluar(string s, map<string, vector<string> >tabla_var){
		mapa["("] = 7;
		mapa[")"] = 7;
		mapa["*"] = 6;
		mapa["/"] = 6;
		mapa["+"] = 5;
		mapa["-"] = 5;
		mapa["%"] = 5;
		mapa[">="] = 4;
		mapa["<="] = 4;
		mapa[">"] = 4;
		mapa["<"] = 4;
		mapa["=="] = 4;
		mapa["!="] = 3;
		mapa["!"] = 2;
		mapa["||"] = 1;
		mapa["&&"] = 0;
		mapa["="] = -1;

		string ss = s; 
		
		vector<string>v ;
		ss = remover(ss);
		v = dividir(ss);
		
		for(int i=0; i<v.size();i++){
			//cout<<"["<<v[i]<<"]";
		}
		
		
		queue<string >q = evaluar(v);
		stack<float>pila;	//Todo lo pasa a float, para en distintos casos convertirlo a int
		
		
		while(!q.empty()){
			
			string val = q.front();
			if(isdigit(val[val.size()-1]) || val[0]=='$'){
				float x=0;
				if(val[0]=='$'){
					//Caso 1: variable
					string valor = tabla_var[val][1];
					stringstream ss;
					ss<<valor;
					ss>>x;
					//cout<<"valor"<<x;
					
				}else{
					//Caso 2: numero
					stringstream ss;
					ss<<q.front();
					ss>>x;
					//cout<<"x:"<<x<<"\n";
				}				

				pila.push(x);
			}else{
				
				if(pila.size()<=1 && q.front()!="!"){
					break;
				}
				string operador = q.front(); 
				float num1=-1,num2=-1;
				
				
				
				num2 = pila.top(); pila.pop();
				if(operador!="!"){
					num1 = pila.top(); pila.pop();
				}
				//cout<<"["<<operador<<"]";
				float res=0;
				//cout<<"\n";
				if(operador == "+"){
					//cout<<num1<<"+"<<num2<<"\n";
					res= num1+num2;
				}else if(operador == "-"){
					//cout<<num1<<"-"<<num2<<"\n";
					res = num1-num2;
				}else if(operador == "*") {
					//cout<<num1<<"*"<<num2<<"\n";
					res = num1*num2;
				}else if(operador == "/") {
					//cout<<num1<<"/"<<num2<<"\n";
					res = num1/num2;
				}else if(operador == "==") {
					//cout<<num1<<"=="<<num2<<"\n";
					if(num1==num2) res = 1;
					else res = 0;
				}else if(operador == ">=") {
					//cout<<num1<<">="<<num2<<"\n";
					if(num1>=num2) res = 1;
					else res = 0;
				}else if(operador == "<=") {
					//cout<<num1<<"<="<<num2<<"\n";
					if(num1<=num2) res = 1;
					else res = 0;
				}else if(operador == "!=") {
					//cout<<num1<<"!="<<num2<<"\n";
					if(num1!=num2) res = 1;
					else res = 0;
				}else if(operador == "!") {
					//cout<<"!"<<num2<<"\n";
					if(!num2) res = 1;
					else res = 0;
				}else if(operador == "&&") {
					//cout<<num1<<"&&"<<num2<<"\n";
					if(num1&&num2) res = 1;
					else res = 0;
				}else if(operador == "||"){
					//cout<<num1<<"||"<<num2<<"\n";
					if(num1||num2) res = 1;
					else res = 0;
				}else if(operador == ">"){
					//cout<<num1<<">"<<num2<<"\n";
					if(num1>num2) res = 1;
					else res = 0;
				}else if(operador == "<"){
					//cout<<num1<<"<"<<num2<<"\n";
					if(num1<num2) res = 1;
					else res = 0;
				}else if(operador == "%"){
					//cout<<num1<<"<"<<num2<<"\n";
					res = int(num1)%int(num2);
				}
				pila.push(res);
			}
			q.pop();
	    	}	
	    	//cout<<"resultado "<<pila.top();
	    	return pila.top();
	}

	
	float e_expresiones(vector<string>v, map<string, vector<string> >tabla_var){
		string cad = "";
			for(int i=0; i<v.size(); i++){
				cad+=v[i];
			}
		//cout<<cad<<" ";
		return evaluar(cad, tabla_var);
	}

	
