#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

int main() {
    pid_t pid, sid;        // Variabel untuk menyimpan PID
    pid_t child_pid,child_pid2;
    int status=0;
    pid = fork();     // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    //kode template untuk proses daemon
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/ianfelix/sisop/module2")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    time_t now = time(NULL);
    int batas = 1;
    while(1){
        // Tulis program kalian di sini
        now = time(NULL);
        //melakukan timecheck apakah sudah kurang dari 6 jam
        if(now >= 1617960120 && batas == 1){
            batas++;
            //membuat directory
            char *argv[][6] = {{"mkdir","Fylm",NULL},{"mkdir","Musyik",NULL},{"mkdir","Pyoto",NULL}};
            for(int capek=0; capek<3;capek++){
                if(fork()==0) continue;
                execv("/bin/mkdir", argv[capek]); 
            }
            //membuat  proses baru
            child_pid = fork();
            if(child_pid == 0){
                sleep(10);
                char *argv1[][10] = {
                    { "wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O","Film_for_Stevany.zip",NULL},
                    { "wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O","Musik_for_Stevany.zip",NULL},
                    { "wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O","Foto_for_Stevany.zip",NULL}};
                //melakukan download
                for(int mulaiCapek=0;mulaiCapek<3;mulaiCapek++){
                    if(fork()==0) continue;
                    sleep(10);
                    execv("/bin/wget", argv1[mulaiCapek]); 
                }
            }else{
                while ((wait(&status)) > 0);
                sleep(10);
                //setelah download di unzip
                char *argv3[][10]= {
                    {"unzip","-j","Film_for_Stevany.zip","-d","./Fylm",NULL},
                    {"unzip","-j","Musik_for_Stevany.zip","-d","./Musyik",NULL},        
                    {"unzip","-j","Foto_for_Stevany.zip","*.jpg","-d","./Pyoto",NULL}
                };
                for(int sangatCapek=0; sangatCapek<3;sangatCapek++){
                    if(fork()==0) continue;
                    sleep(10);
                    execv("/bin/unzip", argv3[sangatCapek]); 
                }   
            }
        }else if(now >= 16171985320){
            //kode setelah jam d-day
            child_pid2 = fork();
            if(child_pid2 == 0){
                char *zipAkhir[]= {"zip","-r","Lopyu_Stevany.zip","Fylm","Musyik","Pyoto",NULL};
                execv("/bin/zip", zipAkhir); 
            }else{
                while ((wait(&status)) > 0);
                char *hapus[]= {"rm","-r","Fylm","Musyik","Pyoto",NULL};
                execv("/bin/rm", hapus); 
                exit(1);
            }
        }
        sleep(30);
    }
}

// sudo date +%Y%m%d -s "202104^C"
// sudo date +%T -s "18:26"