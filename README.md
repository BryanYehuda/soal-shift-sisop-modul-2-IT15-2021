# soal-shift-sisop-modul-2-IT13-2021
## Laporan Pengerjaan Modul 2 Praktikum Sistem Operasi    

### Nama Anggota Kelompok:  
1. Bryan Yehuda Mannuel
2. Calvin Mannuel Simatupang
2. Ian Felix Jonathan Simanjuntak
3. Muhammad Nur Fauzan

---

## Soal 1

Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton [Video Youtube ini](https://www.youtube.com/watch?v=568DH_9CMKI)  untuk menghilangkan kesedihannya.

Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany.

Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi.

A. Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah **Musyik** untuk mp3, **Fylm** untuk mp4, dan **Pyoto** untuk jpg.

B. untuk musik Steven **mendownloadnya** dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :).

C. Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu **meng-extract-nya** setelah didownload serta

D. **memindahkannya** ke dalam folder yang telah dibuat (hanya file yang dimasukkan).

E.  Untuk memudahkan Steven, ia ingin semua hal di atas berjalan **otomatis** 6 jam sebelum waktu ulang tahun Stevany). 

F.  Setelah itu pada **waktu** ulang tahunnya Stevany, semua folder akan di zip dengan nama **Lopyu_Stevany.zip** dan semua folder akan di **delete** (sehingga hanya menyisakan .zip). Kemudian Steven meminta bantuanmu yang memang sudah jago sisop untuk membantunya mendapatkan hati Stevany. Bantu Woy!!

### Notes Soal 1

* Ulang Tahun Stevany : 09 April Pukul 22.22 WIB
* Semua poin dijalankan oleh 1 script di latar belakang, termasuk mendownload file zip-nya. Jadi cukup jalankan script 1x serta ubah time dan date untuk check hasilnya.
* Tidak boleh menggunakan fungsi `system(`), `mkdir()`, dan `rename()`
* Tidak boleh pake `cron` !!!
* Menggunakan `fork` dan `exec`.

### Link Soal 1
* Preview: https://drive.google.com/drive/folders/1NzRiPPoVlR_H8P51cxN4jaceeFQGk4un
* Foto: https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view
* Musik: https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
* Film: https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view

### Tips Soal 1
* Gunakan fungsi `wait()` dan `sleep()` untuk memperlancar
* untuk mendownload zip yang dibutuhkan bisa menggunakan command :
```c
wget --no-check-certificate "https://drive.google.com/uc?id=ID-FILE&export=download" -O Nama_untuk_filenya.ext
```
* contoh penggunaan command :
```c
Wget --no-check-certificate "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download" -O Musik_for_Stevany.zip
```

### Code Soal 1
```c
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
```

### Penjelasan Code Soal 1
### a. Membuat folder fylm, musyik, dan juga pyoto
untuk membuat folder tersebut, kami menggunakan kode sebagai berikut
```
char *argv[][6] = {{"mkdir","Fylm",NULL},{"mkdir","Musyik",NULL},{"mkdir","Pyoto",NULL}};
for(int capek=0; capek<3;capek++){
    if(fork()==0) continue;
	execv("/bin/mkdir", argv[capek]); 
}
```
kami membuat perulangan for sebanyak 3 kali, dimana disetiap perulangan kami akan melakukan "execv("/bin/mkdir", argv[capek]); " untuk setiap argv[capek] akan mengambil nilai dari variabel *argv. setelah kode dijalankan, maka akan terbentuk 3 folder

### b dan c dan d. Mendownload dan melakukan ekstrak dan memindahkan ke folder yang sudah dibuat.
untuk melakukan kedua tugas ini, kami menggunakan fungsi fork() untuk spawning proses baru. pada child kami akan melakukan download, lalu pada parent kami akan wait sampai proses di child selesai, lalu kami lakukan ekstrak setelahnya ke masing masing folder yang sudah dibuat pada soal a

untuk proses mendownload zip kami menggunakan wget dan kami simpan di variabel argv1 dan dilakukan dalam proses child:
```
char *argv1[][10] = 
    {
        { "wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O","Film_for_Stevany.zip",NULL},
        { "wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O","Musik_for_Stevany.zip",NULL},
        { "wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O","Foto_for_Stevany.zip",NULL}
    };
```
untuk melakukan proses download, kami menggunakan perulangan for sebanyak 3, dan untuk setiap perulangan akan menjalankan 1 argumen dari variabel argv1
```
for(int mulaiCapek=0;mulaiCapek<3;mulaiCapek++){
    if(fork()==0) continue;
    sleep(10);
    execv("/bin/wget", argv1[mulaiCapek]); 
}
```
Untuk melakukan ekstrak dari setiap zip yang sudah di download kami menggunakan perintah unzip yang kami simpan di variabel argv2
```
char *argv3[][10]= 
{
    {"unzip","-j","Film_for_Stevany.zip","-d","./Fylm",NULL},
    {"unzip","-j","Musik_for_Stevany.zip","-d","./Musyik",NULL},        
    {"unzip","-j","Foto_for_Stevany.zip","*.jpg","-d","./Pyoto",NULL}
};
```
tag "-j" diperlukan supaya tidak membentuk sebuah folder baru jika di ektrak. Tag "-d" digunakan untuk menentukan zip yang akan diunzip akan diekstrak ke folder yang mana. dapat dilihat juga pada argv[2], bahwa kami menggunakan "*.jpg" hal ini digunakan agar program hanya mengekstrak file yang berekstensi jpg saja.
Untuk menjalankan perintah tersebut, kami menggunakan perulangan for kembali sebanyak tiga kali
```
for(int sangatCapek=0; sangatCapek<3;sangatCapek++){
    if(fork()==0) continue;
    sleep(10);
    execv("/bin/unzip", argv3[sangatCapek]); 
}
```
untuk setiap for yang dilakukan, maka akan menjalankan perintah execv yang berisi perintah yang sudah kita simpan di argv3 sebelumnya.   
### Kendala Yang Dihadapi Soal 1

### Screenshot Hasil Run Soal 1

---

## Soal 2

Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.

A. Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder `“/home/[user]/modul2/petshop”`. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.

B. Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip. Contoh: Jenis peliharaan kucing akan disimpan dalam `“/petshop/cat”`, jenis peliharaan kura-kura akan disimpan dalam `“/petshop/turtle”`.

C. Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan. Contoh: `“/petshop/cat/joni.jpg”`.

D. Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama `“dog;baro;1_cat;joni;2.jpg”` dipindah ke folder `“/petshop/cat/joni.jpg”` dan `“/petshop/dog/baro.jpg”`

E. Di setiap folder buatlah sebuah file `"keterangan.txt"` yang berisi nama dan umur semua peliharaan dalam folder tersebut. **Format harus sesuai contoh**.
```sh
nama : joni
umur : 3 tahun
nama : miko
umur : 2 tahun
```
Loba sangat mengapresiasi bantuanmu, minggu depan ia akan mentraktir makan malam!

### Note Soal 2
* Setiap data peliharaan disimpan sebagai nama foto dengan format `[jenis peliharaan]:[nama peliharaan]:[umur peliharaan dalam tahun]`. Jika terdapat lebih dari satu peliharaan, data dipisahkan menggunakan `underscore(_)`.
* Tidak boleh menggunakan fungsi `system()`, `mkdir()`, dan `rename()`.
* Menggunakan `fork` dan `exec`.

### Code Soal 2
```c
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
```

### Penjelasan Code Soal 2

### Kendala Yang Dihadapi Soal 2

### Screenshot Hasil Run Soal 2

---

## Soal 3

Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program.

A. Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai **timestamp [YYYY-mm-dd_HH:ii:ss]**.

B. Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format **timestamp [YYYY-mm-dd_HH:ii:ss]** dan gambar tersebut berbentuk persegi dengan ukuran `(n%1000) + 50 pixel` dimana n adalah detik **Epoch Unix**.

C. Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file `“status.txt”`, dimana didalamnya berisi pesan `“Download Success”` yang terenkripsi dengan teknik **Caesar Cipher** dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

D. Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan **program bash**.

E. Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan **argumen -z**, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan **argumen -x**, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

Ranora meminta bantuanmu untuk membantunya dalam membuat program tersebut. Karena kamu anak baik dan rajin menabung, bantulah Ranora dalam membuat program tersebut!

### Note Soal 3

* Tidak boleh menggunakan `system()` dan `mkdir()`
* Program utama merupakan `SEBUAH PROGRAM C`
* Wajib memuat algoritma `Caesar Cipher` pada program utama yang dibuat


### Code Soal 3
```c
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
        char *command[] = {"chmod", "u+x", "turnoff.sh", NULL};
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
```

### Penjelasan Code Soal 3

### Kendala Yang Dihadapai Soal 3

### Screenshot Hasil Run Soal 3





