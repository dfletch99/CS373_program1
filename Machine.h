#ifndef MACHINE_H
#define MACHINE_H
#include <string>
#include <iostream>
#include <fstream>
#include "State.h"

using namespace std;

class Machine{
	char * inFile;
	char * input;
	int maxTransitions;
	State[1000] states;
	State start;
	public:
		Machine(char * inFile, char * input, int maxTransitions){
			this.inFile = inFile;
			this.input = input;
			this.maxTransitions = maxTransitions;
		}

		void create(){
			ifstream file;
			file.open(inFile, ios::in);
			string stateOrTransition;
			int specialState;
			string specialName;

			int begin;
			char letter;
			int end;
			char replace;
			char leftRight;
			while(file >> stateOrTransition){
				if(stateOrTransition == "state"){
					while(file >> specialState >> specialName){
						switch specialName{
							case "accept":
								states[specialState].special = 'a';
								break;
							case "reject":
								states[specialState].special = 'r';
								break;
							case "start":
								states[specialState].special = 's';
								start = states[specialState];
								break;
							default:
								break;	
						}
					}
				}
				else{
					while(file >> begin >> letter >> end >> replace >> leftRight){
						
					}
				}
			}
		}
}

#endif
