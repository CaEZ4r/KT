#include "actor.h"
bool launch(const char* path, char * const * arg)
{
    int pid = fork();
    if (pid < 0)
    {
       return false;     
    }
    else if (pid == 0)
    {
        //Дочерний процесс
        execvp(path, arg);
        _exit(72);
    }
    return true;
}

int main(int argc, char ** argv){
	int n ;
	if( argc > 1)
		sscanf(argv[1], "%d", &n);
	int t[n];
	int T = 20;
	int max = 6;
	for (int i = 0; i < n; i ++) {
		t[i] = rand() % 5;
		cout << t[i] << endl;
	}
	int j = 0;
	while( j < n) {
		int chel = 0;
		int sumt = 0;
		while ((sumt < T) && (chel < max) && (j < n)) {
			chel += 1;
			sumt += t[j];
			j += 1;
		}
		for (int i = 0; i < 5; i ++) {
		int status;
			char buf[20] = {0};
    			sprintf(buf,"%d",t[i]);
    			char * const o = &t[i];
    			launch("./chel", o);
    	}
    	cout << "Лифт готов." << endl;
}
}
