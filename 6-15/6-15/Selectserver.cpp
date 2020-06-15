#define _CRT_SECURE_NO_WARNINGS
#include "selectServer.hpp"

void usage(string proc){
	cout << "Usage: " << proc << " port" << endl;
}

//./selectServer port
int main(int argc, char *argv[]){
	if (argc != 2){
		usage(argv[0]);
		exit(1);
	}
	selectServer *ss = new selectServer(atoi(argv[1]));
	ss->initServer();
	ss->start();

	//    cout << sizeof(fd_set)*8 << endl;
	return 0;
}

