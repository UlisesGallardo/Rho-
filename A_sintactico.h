
	#include <bits/stdc++.h>
	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <sstream>
	#include <queue>
	#include "E_expresiones.h"
	using namespace std;
	
	map<string, vector<string> > tabla_var;
	/*
		Caso 1: Declarar
		Caso 2:	Asignar
		Caso 3: Imprimir
		Caso 4: Leer
		Caso 5:	For
		caso 6: While
		caso 7: Condicional
	
	*/
	
	
	class Instruccion{
		public:
			Instruccion(){
			}
			~Instruccion(){	
			}
			//virtual map<string, vector<string> > 
			virtual void ejecutar(map<string, vector<string> > &tabla_var){
				//return tabla_var;
			}
			virtual void print(){
				
			}
	};
	
	class Declarar: public Instruccion {
		public:
			vector<string> variables;
			string tipo;
			Declarar(){
			}
			Declarar(vector<string>variables,string tipo){
				this->variables = variables;
				this->tipo = tipo;
			}
			~Declarar(){
			}
		//	map<string, vector<string> > 
			void ejecutar(map<string, vector<string> > &tabla_var){
				for(int i=0; i<variables.size();i++){
					vector<string>v;
					if(tipo=="alfa"){	//Numeros
						int x=0;
						stringstream ss;
						ss<<x;
						string xx;
						ss>>xx;
						v.push_back(tipo);	//Tipo de dato
						v.push_back("0");	//Valor inicial de cualquier variable 
						tabla_var.insert(make_pair(variables[i],v));
					}else if(tipo=="beta"){	//string
						string x ="";
						v.push_back(tipo);
						v.push_back(x);
						tabla_var.insert(make_pair(variables[i],v));
					}else if(tipo=="gamma"){	//float
						float x = 0.0;
						stringstream ss;
						ss<<x;
						string xx;
						ss>>xx;
						v.push_back(tipo);
						v.push_back(xx);
						tabla_var.insert(make_pair(variables[i],v));
					}else if(tipo=="delta"){	//Bool
						v.push_back(tipo);
						v.push_back("0");
						tabla_var.insert(make_pair(variables[i],v));
					}
				}
			//	return tabla_var;
			}
			void print(){
				cout<<"DECLARAR: "<<tipo<<" : ";
				for(int i=0; i<variables.size();i++){
					cout<<variables[i]<<", ";
				}
				cout<<"\n";
			}
	};

	
	class Asignar : public Instruccion{
		public:
			string variable;
			string tipo_dato;
			string expresion_final;
			vector<string>expresion;
			string valor_final;
			Asignar(){
			}
			Asignar(vector<string>expresion, string variable){
				this->expresion = expresion;
				this->variable = variable;
				string cad = "";
				for(int i=0; i<expresion.size();i++){
					cad+=expresion[i];
				}
				this->expresion_final = cad;	
			}
			~Asignar(){	
			}
			//map<string, vector<string> > 
			void ejecutar(map<string, vector<string> > &tabla_var){
				string expresion_1="";
				for(int i=0; i<expresion.size(); i++){
					expresion_1+=expresion[i]+" ";
				}
				string tipo = tabla_var[variable][0],valor="";
				if(tipo=="beta"){//string o cadena
					valor = expresion_1;
					tabla_var[variable][1] = expresion_1;
				}else if(tipo=="alfa"){ //enteros
					int res = e_expresiones(expresion,tabla_var);
					valor = to_string(res);
					tabla_var[variable][1] = to_string(res);
				}else if(tipo=="gamma"){// flotantes
					float res = e_expresiones(expresion,tabla_var);
					valor = to_string(res);
					tabla_var[variable][1] = to_string(res);
				}else if(tipo=="delta"){//bool
					int res = e_expresiones(expresion,tabla_var);
					valor = to_string(res);
					tabla_var[variable][1] = to_string(res);
				}
			
			
			//	return tabla_var;
			}
			void print(){
				cout<<"ASIGNAR: "<<variable<<" :: "<<expresion_final<<"\n";
			}
	};
	
	
	class Imprimir: public Instruccion{
		public:
			string cadena_imprimir;
			vector<string> expresiones;
			Imprimir(){	
			}
			Imprimir(vector<string>expresiones){
				this->expresiones = expresiones;
				string cad = "";
				for(int i=0; i<expresiones.size();i++){
					cad+=expresiones[i];
				}
				this->cadena_imprimir = cad;
			}
			~Imprimir(){	
			}
			//map<string, vector<string> > 
			void ejecutar(map<string, vector<string> > &tabla_var){
				string cad="";
				vector<string> statements;
				bool entrar = false;
				for(int i=0; i<=expresiones.size();i++){
					if(i!=expresiones.size()){
						if(expresiones[i]!=":"){
							cad+=expresiones[i];
						}else{
							entrar = true;
						}
						
					}else{
						entrar = true;
					}
					if(entrar){
						statements.push_back(cad);
						cad="";
						entrar = false;
					}
					
				}
				string ImprimirFinal="";
				for(int i=0; i<statements.size();i++){
					if(statements[i].find("<<") != string::npos){
						std::size_t pos = statements[i].find(">>");
						string cadena = statements[i].substr(2,pos-2);
						ImprimirFinal+=cadena;
					}else{	
						vector<string>ex;
						ex.push_back(statements[i]);
						//cout<<statements[i]<<" ";
						float res = e_expresiones(ex,tabla_var);
						if(res-((int)res)==0){
							int x = (int)res;
							ImprimirFinal+=to_string(x);
						}else{
							ImprimirFinal+=to_string(res);
						}
					}
				}
				
				//cout<<"->";
				for(int i=0; i<ImprimirFinal.size();i++){
					if(i+1<ImprimirFinal.size()){
						if((int)ImprimirFinal[i]==92 && ImprimirFinal[i+1]=='n'){
							//cout<<"(salto de linea)\n";
							i = i+2;
						}else{
							cout<<ImprimirFinal[i];
						}
					}else{
							cout<<ImprimirFinal[i];
					}
				}
				cout<<"\n";
			//	return tabla_var;
			}
			void print(){
				cout<<"IMPRIMIR: "<<cadena_imprimir<<"\n";
			}
	};
	/*
	class Leer: Instruccion{
		public:
			vector<string> valor_ing;
			vector<string>variables;
			vector<string> expresiones;
			Leer(){	
			}
			Leer(vector<string> expresiones){
				this->expresiones = expresiones;
			}
			~Leer(){
			}
			
			void print(){
				cout<<"LEER: ";
				for(int i=0; i<variables.size();i++){
					cout<<variables[i]<<":";
				}
				cout<<"\n";
			}
			
			map<string, vector<string> > ejecutar(map<string, vector<string> > tabla_var){
				vector<string>var;
				for(int k=0; k<expresiones.size();k++){
				//	cout<<expresiones[k]<<"\n";
					if(expresiones[k]!=":")var.push_back(expresiones[k]);
				}
				
				this->variables = var;
				
				for(int i=0; i<var.size(); i++){
					string tipo = tabla_var[var[i]][0];
					string variable = var[i];
					Asignar obj;
					////////////////////////////////////////////////////////////////////////Cambiar todo
					
					vector<string>v;
					if(tipo=="alfa"){
						int x; cin>>x;
						
						if(cin.fail()) // Si no se introduce un número
						{
							this->valor_ing.push_back("No valido");
						    cin.clear(); // Borrar la entrada no válida
						    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Saltar la entrada
						}else{
							this->valor_ing.push_back(to_string(x));
							v.push_back(to_string(x));
							tabla_var = obj.ejecutar(v,tabla_var,variable);
							//fflush(stdin);
							cin.ignore();
						}
					
					}else if(tipo=="beta"){
						string x; getline(cin,x);
						this->valor_ing.push_back(x);
						v.push_back(x);
						tabla_var = obj.asignar_valores(v,tabla_var,variable);
						fflush(stdin);
					}else if(tipo=="gamma"){
						float x; cin>>x;
						this->valor_ing.push_back(to_string(x));
						v.push_back(to_string(x));
						tabla_var = obj.asignar_valores(v,tabla_var,variable);
						//fflush(stdin);
						cin.ignore();
					}else if(tipo=="delta"){
						bool x; cin>>x;
						this->valor_ing.push_back(to_string(x));
						v.push_back(to_string(x));
						tabla_var = obj.asignar_valores(v,tabla_var,variable);
						//fflush(stdin);
						cin.ignore();
					}
				}
				return tabla_var;
			}
	};
	
	*/

	
	//Crear una funcion guardar o en el mismo constructor para que me guarde lo que ya tenía hecho. 
	
	class Evaluar{
		public:
			
			class For: public Instruccion{
				public:
					vector<Instruccion*>instrucciones;
					int inicio;
					int fin;
					int incremento;
					string variable;
					vector<vector<string> > tokens_for;
					map<string, string> instrucciones_e;
					
					For(){
					}
					For(string variable, int inicio, int fin, int incremento, vector<vector<string> > tokens, map<string, string> instrucciones_e, map<string, vector<string> > &tabla_var){
						this->variable = variable;
						this->inicio = inicio;
						this->fin = fin;
						this->incremento = incremento;
						this->tokens_for = tokens;
						this->instrucciones_e = instrucciones_e;
						Evaluar obj1(tabla_var);
						this->instrucciones = obj1.ejecutar(tokens_for,instrucciones_e,tabla_var);
					}
					~For(){
					}
					//map<string, vector<string> > 
					void ejecutar(map<string, vector<string> > &tabla_var){
						//cout<<"-----------------------------------------------------FOR---------------------------------------------\n";
						int i = inicio;
						tabla_var[variable][1] = to_string(i);
						
						while(i<=fin){
							for(int j=0; j<instrucciones.size();j++){
								instrucciones[j]->ejecutar(tabla_var);
							}
							i+=incremento;
							tabla_var[variable][1] = to_string(i);
						}
						//return tabla_var;
					}
					void print(){
						cout<<"FOR:\n";
						for(int i=0; i<instrucciones.size();i++){
							instrucciones[i]->print();
						}
						cout<<"Fin del For\n";
					}
			};
			class While:public Instruccion{
				public:
					vector<Instruccion*>instrucciones;
					vector<string> expresion_while;
					vector<vector<string> >nuevos_tokens;
					map<string, string> instrucciones_e;
					While(){
					}
					While(vector<vector<string> >nuevos_tokens, vector<string> expresion_while, map<string, string> instrucciones_e, map<string, vector<string> > &tabla_var){
						this->expresion_while = expresion_while;
						this->nuevos_tokens = nuevos_tokens;
						this->instrucciones_e = instrucciones_e;
						Evaluar obj2(tabla_var);
						this->instrucciones = obj2.ejecutar(nuevos_tokens,instrucciones_e,tabla_var);
					}
					~While(){
					}
					void ejecutar(map<string, vector<string> > &tabla_var){
						int condicion = e_expresiones(expresion_while,tabla_var);
						while(condicion){
							for(int i=0; i<instrucciones.size();i++){
								instrucciones[i]->ejecutar(tabla_var);
							}
							condicion = e_expresiones(expresion_while,tabla_var);
						}
					}
					void print(){
						cout<<"WHILE:\n";
						for(int i=0; i<instrucciones.size();i++){
							instrucciones[i]->print();
						}
						cout<<"Fin del While\n";
					}
			};
			class If:public Instruccion{
				public:
					string condicion;
					vector<string>expresion;
					vector<Instruccion*>instruccionesA;
					vector<Instruccion*>instruccionesB;
					If(){
					}
					If(vector<string>condicion, vector<vector<string> >nuevos_tokens, vector<vector<string> >nuevos_tokens_2,map<string, string> instrucciones_e,map<string, vector<string> > &tabla_var){
						string cad="";
						for(int i=0; i<condicion.size();i++){
							cad+=condicion[i];
						}
						this->condicion = cad;
						this->expresion = condicion;
						Evaluar obj2(tabla_var);
						this->instruccionesA = obj2.ejecutar(nuevos_tokens,instrucciones_e,tabla_var);
						Evaluar obj3(tabla_var);
						this->instruccionesB = obj3.ejecutar(nuevos_tokens_2,instrucciones_e,tabla_var);
					}
					~If(){
					}
					void ejecutar(map<string, vector<string> > &tabla_var){
						int res = e_expresiones(expresion,tabla_var);
						if(res){
							for(int i=0; i<instruccionesA.size();i++){
								instruccionesA[i]->ejecutar(tabla_var);
							}
						}else{
							for(int i=0; i<instruccionesB.size();i++){
								instruccionesB[i]->ejecutar(tabla_var);
							}
						}
					}
					void print(){
						cout<<"IF:"<<condicion<<"\n";
						for(int i=0; i<instruccionesA.size();i++){
							instruccionesA[i]->print();
						}
						cout<<"Fin del IF\n";
						if(instruccionesB.size()!=0){
							cout<<"Inicio de ELSE\n";
							for(int i=0; i<instruccionesB.size();i++){
								instruccionesB[i]->print();
							}
							cout<<"Fin de ELSE\n";
						}	
					}
			};
			
			
			Evaluar(){
			}
			Evaluar( map<string, vector<string> > tabla_var){
				tabla_var = tabla_var;
			}
			~Evaluar(){
			}
			vector<Instruccion*> ejecutar(vector<vector<string> > t, map<string, string> instrucciones, map<string, vector<string> > &tabla_var){
				vector <Instruccion*>vector_instrucciones;
				for(int i=0; i<t.size(); i++){
					string casos = t[i][0];
						//Tokens para Declarar
						if(casos=="@"){		
								vector<string >variables;
								string tipo = "";
								int iter = i+1;
								
								while(instrucciones.find(t[iter][0])==instrucciones.end() && t[iter][0]!=";"){
									//cout<<espacios<<t[iter][0]<<" ";
									if(t[iter][0][0]=='$'){
											variables.push_back(t[iter][0]);
									}
									if(t[iter][0] == "alfa"|| t[iter][0]== "beta"|| t[iter][0]=="gamma"|| t[iter][0]=="delta"){
										tipo = t[iter][0];
									}
									iter++;
								}
								Instruccion* obj = new Declarar(variables,tipo);
								vector_instrucciones.push_back(obj);
								i = iter;
								
						//Tokens para asignar		
						}else if(casos[0]=='$'){
								if(t[i+1][0]==":"){
									vector<string> expresion;
									string variable = casos;
									int iter = i+1;
									int con=0;
									while(instrucciones.find(t[iter][0])==instrucciones.end() || t[iter][0]!=";"){
										//cout<<espacios<<t[iter][0]<<" ";
										if(con==2)expresion.push_back(t[iter][0]);
										if(t[iter][0] ==":")con++;
										iter++;
									}
									
									Instruccion* obj = new Asignar(expresion,variable);
									vector_instrucciones.push_back(obj);
									i = iter-1;
								}
					//Tokens para imprimir			
						}else if(casos=="omega"){
							int iter = i+1;
							vector<string> expresion;
							bool entrar = false;
							while(instrucciones.find(t[iter][0])==instrucciones.end()){
								if(entrar && t[iter][0]!="]"){
									//cout<<t[iter][0]<<" ";
									expresion.push_back(t[iter][0]);
								}
								if(t[iter][0]==";")break;
								if(t[iter][0]=="[")entrar = true;
								iter++;
							}
						
							Instruccion* obj = new Imprimir(expresion);  
							vector_instrucciones.push_back(obj);
							
							i = iter;
						
						//Tokens para leer	
						}else if(casos=="sigma"){//Caso 4
						
						/*
							cout<<espacios<<"LEER->";
							int iter = i+1;
							vector<string> expresion;	//Expresion Completa
							while(t[iter][0]!="]"){
								if(t[iter][0]==";") break;
							//	if(t[iter][0]!="[" && t[iter][0]!=":"){
								if(t[iter][0]!="["){
								//	cout<<espacios<<t[iter][0]<<" ";
									expresion.push_back(t[iter][0]);
								}
								iter++;
							}
								
							leer obj4;
							tabla_var = obj4.leer_variables(tabla_var,expresion);
							obj4.print(espacios);
							/*
							for(map<string, vector<string> >::iterator it = tabla_var.begin(); it!=tabla_var.end(); it++){
								vector<string> vec =  it->second;
								cout<<it->first<<" ";
								for(int k=0; k<vec.size();k++){
									cout<<vec[k]<<" ";
								}
							}*/
							
						//	i = iter;
							cout<<"\n";
							
							
						//Tokens para for
						}else if(casos=="eta"){	//Caso 5
						
							int iter = i+1;
							vector<string> variables_for;
							bool entrar = false;
							
							queue<string>q;
							vector<vector<string> >nuevos_tokens;	
							while(true){
								if(t[iter][0]=="{"){
									q.push("{");
									iter++;
									break;
								}
								if(entrar && t[iter][0]!="]" && t[iter][0]!=","){
									variables_for.push_back(t[iter][0]);
								}
								
								if(t[iter][0]=="["){
									entrar = true;
								}
								//cout<<t[iter][0]<<" ";
								iter++;
							}
							int ini,fin,incremento;
							if(variables_for.size()>=4){
								ini = stoi(variables_for[1]);
								fin = stoi(variables_for[2]);
								incremento = stoi(variables_for[3]);
							}	
							
							while(!q.empty()){
								if(t[iter][0]=="{"){
									q.push("{");
								}else if(t[iter][0]=="}"){
									q.pop();
								}
								nuevos_tokens.push_back(t[iter]);
								iter++;
							}
							//cout<<"variables_for: "<<ini<<" "<<fin<<" "<<incremento<<"\n";
							Instruccion* obj = new For(variables_for[0],ini,fin,incremento,nuevos_tokens,instrucciones, tabla_var);
							vector_instrucciones.push_back(obj);
							i = iter-1;		//Sin el -1 se saltará una línea de tokens. 
							
							
						//Tokens para while
						}else if(casos=="tau"){	//Caso 6
						
							//cout<<espacios<<"WHILE ->";
							queue<string>q;
							vector<vector<string> >nuevos_tokens;
							vector<string> expresion_while;
							bool entrar = false;
							int iter = i+1;
							
							while(true){
								if(t[iter][0]=="{"){
									q.push("{");
									iter++;
									break;
								}
								if(entrar && t[iter][0]!="]"){
									expresion_while.push_back(t[iter][0]);
								}
								
								if(t[iter][0]=="["){
									entrar = true;
								}
								
								//cout<<t[iter][0];
								iter++;
							}
						
							while(!q.empty()){
								if(t[iter][0]=="{"){
									q.push("{");
								}else if(t[iter][0]=="}"){
									q.pop();
								}
								//cout<<t[iter][0]<<" ";	//Todo lo que va a contener el for
								nuevos_tokens.push_back(t[iter]);
								iter++;
							}
							
							
							Instruccion * obj5 = new While(nuevos_tokens,expresion_while,instrucciones, tabla_var);
							vector_instrucciones.push_back(obj5);
							i = iter-1;
							
				
						//Tokens para if y else
						}else if(casos=="fi"){//Caso 7

							vector<string> expresion;
							vector<vector<string> >nuevos_tokens;
							
							int iter = i+1;
							bool entrar = false;
							while(instrucciones.find(t[iter][0])==instrucciones.end()){
								//cout<<t[iter][0];
								if(entrar && t[iter][0]!= "]"){
									expresion.push_back(t[iter][0]);
								}
								if(t[iter][0]=="]") break;
								if(t[iter][0]=="["){
									entrar = true;
								}
								iter++;
							}
			
							queue<string>q;		//Obtener todas las intrucciones dentro del if
							while(true){
								if(t[iter][0]=="{"){
									q.push("{");
									iter++;
									break;
								}
								iter++;
							}
							
							
							while(!q.empty()){		//Obtener la primera llave del if
								if(t[iter][0]=="{"){
									q.push("{");
								}else if(t[iter][0]=="}"){
									q.pop();
								}
								nuevos_tokens.push_back(t[iter]);
								iter++;
							}	
							vector<vector<string> >nuevos_tokens2;
							if(t[iter][0]=="psi"){
								queue<string>qq;
								while(true){
									if(t[iter][0]=="{"){
										qq.push("{");
										iter++;
										break;
									}
									iter++;
								}
								while(!qq.empty()){
									if(t[iter][0]=="{"){
										qq.push("{");
									}else if(t[iter][0]=="}"){
										qq.pop();
									}
									nuevos_tokens2.push_back(t[iter]);
									iter++;
								}	
							}
							
							Instruccion * obj7 = new If(expresion,nuevos_tokens,nuevos_tokens2,instrucciones, tabla_var);
							vector_instrucciones.push_back(obj7);
							
							i = iter-1;	//Sin el -1 no considerará la siguiente instrucción
							cout<<"\n";
						
						}
				}
			//	return tabla_var;
				return vector_instrucciones;
			}	
	};
