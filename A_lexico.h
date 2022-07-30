
	#include <bits/stdc++.h>
	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <sstream>
	#include <queue>
	using namespace std;
	
	vector<vector<string> > e_tokens(map<string, string>dic, string cad){
		vector<vector<string> > token;
		int con=0;
		string s ="";
		int estado=-1;//0 texto 1 bool, 2 float, 3 o_a 4 o_r 5 o_l 6 simbolos ,7,8 numeros
		while(con<cad.size()){
			//error en = 1
			if(isalpha(cad[con]) && !cad[con]!=' '){ //identificar texto y booleanos.
				while(cad[con]!=' ' && isalpha(cad[con]) && con<cad.size()){
					s+=cad[con];
					con++;
				}
				if(s=="true"||s=="false"){
					estado=1;
				}
			}else if(cad[con]=='$'){		//Identificar nombre de variables
				s+=cad[con];
				con++;
				while(cad[con]!=' ' && (isalpha(cad[con]) || cad[con]=='_')&& con<cad.size()){
					s+=cad[con];
					con++;
				}
				estado=7;
			}else if(cad[con]=='<'&&cad[con+1]=='<'){  //Identificar cadenas de textos entre comillas
				while(cad[con-2]!='>' && cad[con-1]!='>' && con<cad.size()){		//Por mejorar, si se encuentra el caso de <<operador >>>
					s+=cad[con];
					con++;
				}
				s+=cad[con];
				con++;
				estado=0;
			}else if(isdigit(cad[con]) && con<cad.size() && !cad[con]!=' '){ //identificar numeros y numeros decimales.
				bool flotante =false;
				while((cad[con]!=' ') && (isdigit(cad[con]) || cad[con]=='.') && con<cad.size()){
					s+=cad[con];
					if(cad[con]=='.')flotante=true;
					con++;
				}
				if(flotante){
					estado=2;
				}else{
					estado=8;
				}
			}else if(cad[con]!=' ' && con<cad.size() && !isdigit(cad[con]) && !isalpha(cad[con]) ){ //Identificar Simbolos.
				s+=cad[con];
				con++;
			}else{
				con++;
			}
			
			vector<string>elementos;
			elementos.push_back(s);
	
			s.erase(remove(s.begin(), s.end(), '\t'), s.end()); //Eliminar espacios y tabuladores
			s.erase(remove(s.begin(), s.end(), ' '), s.end());	


				if(s!=""){
					if(estado==-1){
						if(dic.find(s)!=dic.end()){
							elementos.push_back(dic[s]);
						}else{
							if(s!="")cout<<"Error en "<<s<<"\n";
						}
						s ="";
						token.push_back(elementos);
					}else{
						string tok;
						switch(estado){
							case 0:	
								tok = "beta";
								break;
							case 1:
								tok = "delta";
								break;
							case 2:	
								tok = "gamma";
								break;
							case 7:	
								tok = "n_var";
								break;
							case 8:
								tok = "alfa";	
								break;
						}
						if(dic.find(tok)!=dic.end()){
							elementos.push_back(dic[tok]);
						}else{
							if(tok!="")cout<<"Error en"<<tok<<"\n";
						}
						s ="";
						token.push_back(elementos);
					}
				estado=-1;
				}
				s = "";
			}
		
		for(int i=0; i<token.size();i++){
			cout<<"Token "<<token[i][0]<<" Numero de Token "<<token[i][1]<<"\n";
		}
		
		return token;
	}

	
