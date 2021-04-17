#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <stdio.h>
#include <wait.h>

void createDir(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    char *token;
    char nama[612];
    char *str;
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            // printf("%s\n", dp->d_name);
            str = dp->d_name;
            snprintf(nama, sizeof nama, "%s", dp->d_name);
            token = strtok(str, ";_");
            int i=0;
            while(token != NULL){
                // printf("%s\n", token);
                if(i==0||i==3){
                    // printf("%s\n", token);
                    if(fork()==0){
                        char buf1[256];
                        snprintf(buf1, sizeof buf1, "petshop/%s", token);
                        char *argv[] = {"mkdir", "-p", buf1, NULL};
                        execv("/bin/mkdir", argv);
                    }
                        
                }
                token = strtok(NULL, ";_");
                i++;
            }
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            createDir(path);
        }
    }

    closedir(dir);
}
void copyFiles(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    char *token;
    char nama[612];
    char *str;
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            // printf("%s\n", dp->d_name);
            str = dp->d_name;
            snprintf(nama, sizeof nama, "%s", dp->d_name);
            token = strtok(str, ";_");
            int i=0;
            char info[1200][1200];
            while(token != NULL){
                // printf("%s\n", token);
                strcpy(info[i], token);
                // printf("%s\n", info[i]);
                if(i==2||i==4){
                    // printf("%s\n", info[i]);
                    char buf1[256];
                    char buf2[256];
                    if(i<3){
                        snprintf(buf1, sizeof buf1, "petshop/%s;", nama);
                        buf1[strlen(buf1)-1] = '\0';
                        snprintf(buf2, sizeof buf2, "petshop/%s/%s.jpg", info[0], info[1]);
                    }if(i>3){
                        snprintf(buf2, sizeof buf2, "petshop/%s/%s.jpg", info[3], info[4]);
                    }

                    if(fork()==0){
                        char *argv[] = {"cp", buf1, buf2, NULL};
                        execv("/bin/cp", argv);
                    }
                        
                }
                token = strtok(NULL, ";_");
                i++;
            }
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            copyFiles(path);
        }
    }

    closedir(dir);
}

int main()
{
    char path[100];

        id_t child_id;
        int status=0;

        child_id = fork();

        if (child_id < 0) {
            exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
        }

        if (child_id == 0) {
            char *argv[] = {"unzip", "pets.zip", "*.jpg", "-d", "petshop", NULL};
            execv("/bin/unzip", argv);
        } else {
            while(wait(&status) > 0);
            createDir("petshop");
            // // this is parent
            copyFiles("petshop");
        }

    // listFilesRecursively(path);

    return 0;
}
