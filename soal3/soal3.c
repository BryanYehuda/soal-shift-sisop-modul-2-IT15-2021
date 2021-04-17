#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<syslog.h>
#include<string.h>
#include<time.h>
#include<wait.h>
#include<sys/prctl.h>
#include<stdbool.h>

void makedaemon()
{
	pid_t pid, sid;
    pid = fork();
    if(pid < 0) exit(EXIT_FAILURE);
    if(pid > 0) exit(EXIT_SUCCESS);
    umask(0);
    sid = setsid();
    if(sid < 0) exit(EXIT_FAILURE);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char* argv[])
{
    if(argc != 2 || (argv[1][1] != 'z' && argv[1][1] != 'x')) 
    {
        printf("pilih salah satu : \nmode 1 : -z \nmode 2 : -x\n");
        exit(0);
    }

    char message[]="Download Success", cipher;
	int j;
	
	for(j = 0; message[j] != '\0'; ++j){
		cipher = message[j];
		
		if(cipher >= 'a' && cipher <= 'z'){
			cipher = cipher + 5;
			
			if(cipher > 'z'){
				cipher = cipher - 'z' + 'a' - 1;
			}
			
			message[j] = cipher;
		}
		else if(cipher >= 'A' && cipher <= 'Z'){
			cipher = cipher + 5;
			
			if(cipher > 'Z'){
				cipher = cipher - 'Z' + 'A' - 1;
			}
			
			message[j] = cipher;
		}
	}
    
    int stat;
    FILE* turnoff;
    turnoff = fopen("turnoff.sh", "w");
    fprintf(turnoff, "#!/bin/bash\nkill %d\nkill %d\necho \'Program Terminated.\'\nrm \"$0\"", getpid() + 2,getpid() + 3);
    fclose(turnoff);

    pid_t cid;
    cid = fork();
    if(cid < 0) exit(0);
    if(cid = 0)
    {
        char *command[] = {"chmod", "u+x", "kill.sh", NULL};
        execv("/bin/chmod", command);
    }
    while(wait(&stat) > 0);

    makedaemon();

    char waktu[30], waktu2[30], waktu3[30], link[50];
    int stat1, stat2, stat3;

    while(1)
    {
    	int i;
        pid_t cid, cid2, cid3, cid4, cid5, pid_before_fork = getpid() + 2;
        time_t t1 = time(NULL);
        struct tm* p1 = localtime(&t1);
        strftime(waktu, 30, "%Y-%m-%d_%H:%M:%S", p1);

        cid = fork();
        if(cid < 0) exit(0);
        if(cid == 0)
        {
            char *command[] = {"mkdir", waktu, NULL};
            execv("/bin/mkdir", command);
        }

        while(wait(&stat1) > 0);
        cid2 = fork();
        if(cid2 < 0) exit(0);
        if(cid2 == 0)
        {
            if(argv[1][1] == 'z') prctl(PR_SET_PDEATHSIG, SIGHUP);
            chdir(waktu);
            for(i = 0; i < 10; i++)
            {
                time_t n = time(NULL);
                struct tm* local = localtime(&n);
                strftime(waktu2, 30, "%Y-%m-%d_%H:%M:%S", local);
                sprintf(link, "https://picsum.photos/%ld", (n % 1000) + 50);

                cid3 = fork();
                if(cid3 < 0) exit(0);
                if(cid3 == 0)
                {
                    char *command[] = {"wget", link, "-O", waktu2, "-o", "/dev/null", NULL};
                    execv("/usr/bin/wget", command);
                }
                sleep(5);
            }

            while(wait(&stat2) > 0);

            FILE * fptr;
            fptr = fopen("status.txt", "w+");
            fputs(message, fptr);
            fclose(fptr);

            chdir("..");
            strcpy(waktu3, waktu);
            strcat(waktu3, ".zip");

            cid4 = fork();
            if(cid4 < 0) exit(0);
            if(cid4 == 0)
            {
                char *command[] = {"zip", "-r", waktu3, waktu, NULL};
                execv("/usr/bin/zip", command);
            }
		
            while(wait(&stat3) > 0);
            sleep(1);
            cid5 = fork();
	        if(cid5 < 0) exit(0);
            if(cid5 == 0)
            {
                char *command[] = {"rm", "-r", waktu, NULL};
            	execv("/bin/rm", command);
            }
            if (getppid() != pid_before_fork) exit(1);
        }
        sleep(40);
    }
}