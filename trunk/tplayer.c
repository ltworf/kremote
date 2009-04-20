#include "tplayer.h"


int tpid;//Pid of the remote daemon process
int tpipe[2];//Descriptors for pipe

int mpid;//Pid of the mplayer process
int mpipe[2];//Descriptors for pipe


int main(int argc, char * argv[]) {
	//Start the daemon
	pipe(tpipe);//Creates the pipe
	tpid=fork();//Forks
	if (tpid<0) exit(1); //An error occured
	if (tpid==0) {//Child
		
		fclose (stdout); //Closing the stdout
		close (tpipe[0]); //Closes unused end of the pipe
		dup(tpipe[1]); //Redirects the stdout
		execl("remoteDaemon","remoteDaemon", "/dev/ttyS0",(char *)0);//Exec the daemon
	}

	//Start mplayer
	pipe(mpipe);
	mpid=fork();
	if (mpid<0) {
		kill(tpid, SIGINT);//Closes the daemon
		exit(1); //An error occured
	}
	if (mpid==0) {//Child process
		fclose(stdin);//Close the standard input
		close(mpipe[1]);//Close unused end of the pipe
		dup(mpipe[0]);//Redirects the stdin

		char* params[argc+1];
		params[0]="mplayer";
		int i;
		for (i=1;i<argc;i++) {
			params[i]=argv[i];
		}
		params[argc]=(char *)0;

		//char * params[]= {"mplayer","/var/Media/mp3/Cisco/01 - La lunga notte/05 - Venite A Vedere.MP3","/var/Media/mp3/Cisco/01 - La lunga notte/09 - Diamanti E Carbone.MP3",(char *)0};
		execv("/usr/bin/mplayer",params);//Exec mplayer
	}

	int cpid=fork();
	if (cpid!=0){//Parent process
		int status;
		waitpid(mpid, &status, 0);//Waits for mplayer to terminate
		kill(cpid, SIGINT);//Kills the child process
		exit(0);
	}

	signal(SIGINT, &terminate);//Adds a signal handler.


	//Reading chars from the daemon and sending control chars to mplayer
	char buf;//Buffer containing the remote command issued
	char * cmd;//Buffer containing the command to issue
	int shift=FALSE;
	while (read(tpipe[0], &buf, 1) > 0) {
		printf("Letto un carattere: %c\n",buf);
		cmd='\0';
		if (buf=='p'|| buf =='P'|| buf=='S') cmd=" ";//Pause/play

		else if (buf=='+') cmd="*";//Vol up
		else if (buf=='-') cmd="/";//Vol down
		else if (buf=='M') cmd="m";//mute

		else if (buf=='F') cmd="f";//fullscreen
		else if (buf=='J') cmd="q";//eject
		else if (buf=='O') cmd="o";//OSD
		else if (buf=='K') cmd="T";//TOP

		else if (buf=='»' && shift==FALSE) cmd="]";//fast
		else if (buf=='»' && shift==TRUE) cmd="}";//fast
		else if (buf=='«' && shift==FALSE)  cmd="[";//slow
		else if (buf=='«' && shift==TRUE)  cmd="{";//slow

		else if (buf=='>' && shift==FALSE) cmd=">";//next item in playlist
		//else if (buf=='>' && shift==TRUE) cmd="\x1B[A";
		else if (buf=='<' && shift==FALSE)  cmd="<";//prev item in playlist
		//else if (buf=='<' && shift==TRUE)  cmd="\00\04B";//slow

		else if (buf=='s') {//shift
			shift= !shift; //=FALSE ? shift=TRUE : shift=FALSE;
			printf("Shift mode %d",shift);
		}

		//Issues the command to mplayer
		write(mpipe[1],cmd,1);
	}
}

void terminate(int signum) {
	
	closeDaemon();

	close(mpipe[0]);//Closing writing end of the pipe
	printf("Closing mplayer...\n");	
	kill(mpid, SIGINT);//Sending a SIGINT to the daemon, so it will exit

	exit (0);
}

void closeDaemon() {
	close(tpipe[1]);//Closing reading end of the pipe
	printf("Closing remote control daemon...\n"); 
	kill(tpid, SIGINT);//Sending a SIGINT to the daemon, so it will exit
}
