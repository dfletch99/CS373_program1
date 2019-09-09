#include "Machine.h"

using namespace std;

int main(int argc, char ** argv){
	if(argc != 4)
		cout << "Command line error: please enter proper arguemnts" << endl;
	Machine m(argv[1], argv[2], (int)(argv[3]));
	m.create();
	m.execute();
}
