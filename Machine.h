#ifndef MACHINE_H
#define MACHINE_H
#include <string>
#include <iostream>
#include <fstream>
#include <tuple>
#include "State.h"

using namespace std;

class Machine{
	public:

		char * inFile;
		char * input;
		int maxTransitions;
		State states[1000];
		State start;
		int inputTracker;

		Machine(char * inFile, char * input, int maxTransitions){
			this->inFile = inFile;
			this->input = input;
			this->maxTransitions = maxTransitions;

			/*int a = 0;
			while(input[a] != '\0'){
				if(input[a] == '\'' || input[a] == '\\') continue;
				this->input[a] = '\0';
				a++;
			}
			this->input[a] = '\0';
			*/

			for(int i = 0; i < 1000; i++){
				states[i].name = i;
				states[i].special = 'n';
			}
		}

		void create(){
			ifstream file;
			file.open(inFile, ios::in);
			string stateOrTransition;
			int specialState;
			string specialName;

			while(file >> stateOrTransition){
				if(stateOrTransition == "state"){
					file >> specialState >> specialName;
					if(specialName == "accept") states[specialState].special = 'a';
					else if(specialName == "reject")states[specialState].special = 'r';
					else{
						states[specialState].special = 's';
						start = states[specialState];
					}
				}
				else break;
			}
			file.close();
			return;
		}

		void execute(){
			State currentState = start;
			int transitionCount = 0;
			char symbol = input[0];
			inputTracker = 0;
			cout << start.name;
			while(transitionCount < maxTransitions){
				if(currentState.special == 'a'){
					cout << " accept" << endl;
					return;
				}
				if(currentState.special == 'r'){
					cout << " reject" << endl;
					return;
				}

				tuple<State, char> tempTuple = lookup(currentState, symbol);
				//input string will be properly overwritten in here ^
				State newState = get<0>(tempTuple);
				char leftOrRight = get<1>(tempTuple);
	
				switch (leftOrRight){
					case 'L':
						symbol = input[inputTracker-1]; // POTENTIAL DANGER
						inputTracker--;
						break;
					case 'R':
						symbol = input[inputTracker+1]; // POTENTIAL DANGER
						inputTracker++;
						break;
					default:
						break;
				}
				cout << "->" << newState.name;
				transitionCount++;
				currentState = newState;
			}
			cout << " quit" << endl;
			return;
		}

		tuple<State, char> lookup(State currentState, char symbol){
			tuple<State, char> ret;
			ifstream file;
			file.open(inFile, ios::in);
			file.seekg(0, ios::beg);

			string first;
			//int dump1;
			//nstring dump2;

			int begin;
			char letter;
			int end;
			char replace;
			char leftRight;

			while(file >> first){
				if(first == "transition"){
					file >> begin >> letter >> end >> replace >> leftRight;
					if(begin != currentState.name) continue;
					else if(letter != symbol) continue;
					else{
						ret = make_tuple(states[end], leftRight);
						input[inputTracker] = replace;
						return ret;
					}
				}
				else{
					char dump[256];
					file.getline(dump, 256, '\n');
				}
			}
			cout << "AAAAH";
			return make_tuple(states[end], leftRight); //this should never happen
		}
};

#endif
