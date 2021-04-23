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

void createFolder(char *nameFolder){
    int status = 0;
    if(fork()==0){
        char buf1[256];
        snprintf(buf1, sizeof buf1, "petshop/%s", nameFolder);
        char *argv[] = {"mkdir", "-p", buf1, NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(&status)>0);
}

void copyFiles(char *namaFolder, char *nama, char *namaFile){
    int status = 0;
    char buf1[256];
    char buf2[256];
    snprintf(buf1, sizeof buf1, "petshop/%s", namaFile);
    snprintf(buf2, sizeof buf2, "petshop/%s/%s.jpg", namaFolder, nama);
    printf("%s\n", buf1);
    printf("%s\n", buf2);
    if(fork()==0){
        char *argv[] = {"cp", buf1, buf2, NULL};
        execv("/bin/cp", argv);
    }
    while(wait(&status)>0);
}

void createKeterangan(char *folder, char *namaHewan, char *umurHewan, int pembantu, int banyak){
    char *umur;
    int status = 0;
    umur = strtok(umurHewan, ".jpg");
    char umurReal[100];
    strcpy(umurReal, umur);
    // printf("umurReal = %s\n", umurReal);
    if(strcmp(umurReal, "0") == 0){
        umur = "0.6";
    }
    char buf1[10000];
    snprintf(buf1, sizeof buf1, "petshop/%s/keterangan.txt", folder);
    printf("%s\n", buf1);
    FILE *keterangan;
    keterangan = fopen(buf1, "a+");
    fprintf(keterangan, "nama : %s", namaHewan);
    fprintf(keterangan, "\n");
    fprintf(keterangan, "umur : %s tahun", umur);
    fprintf(keterangan, "\n\n");
    fclose(keterangan);
    // printf("jumlah = %d\n", jumlah);
    // printf("print %s umur = %s\n",umurHewan, umur);
    
}

void deleteFiles(char *namaFiles){
    if(fork()==0){
        chdir("/home/ianfelix/sisop/module2/petshop");
        char *argv[] = {"rm", namaFiles, NULL};
        execv("/bin/rm", argv);
    }
}
void checkFiles(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    char *token;

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            char nama[656];
            char *str;
            str = dp->d_name;
            // printf("%s\n", dp->d_name);
            snprintf(nama, sizeof nama, "%s", dp->d_name);
            token  = strtok(nama, ";_");

            
            char kind[1600], name[1600], age[1600];
            char *info[2][3];
            int banyak=0;
            while(token != NULL){
                int data = 0;
                while(data<3){
                    info[banyak][data] = token;
                    token = strtok(NULL, ";_");
                    data++;
                }
                banyak++;
            }
            char *usia;
            for (int i = 0; i < banyak; i++) {
                createFolder(info[i][0]);
                copyFiles(info[i][0], info[i][1], str);
                createKeterangan(info[i][0], info[i][1], info[i][2], i, banyak);
            }
            deleteFiles(str);
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            checkFiles(path);
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
            checkFiles("petshop");
        }
    return 0;
}