#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#define account_max 10
#define panjang_max_karakter 100
#define panjang_max_password 100
#define proteksi_login 3

void loadingbar(int panjang) //loading bar ygy
{
    int i;
    printf("\n\n\n\n\n\n\t\t\t\t\t");
    printf("Loading: ");
    for (i = 0; i < panjang; i++){
        printf("%c", 219);//ascii kode 219
        fflush(stdout);//membersihkan (flush) buffer output pada stream stdout (standard output).
        usleep(90000);//menunda eksekusi program
    }
    printf("\n");
}

//STRUCT untuk menyimpan akun nasabah maze bank
struct bankaccount{//struct bankaccount
    char username[panjang_max_karakter];//membuat char username
    char password[panjang_max_password];//membuat char untuk password
    char email[100];//membuat char untuk email
    char gender[20];//membuat char untuk gender
    char alamat[100];//membuat char untuk alamat
};

// Fungsi untuk membuat akun baru
struct bankaccount create_account() {
    struct bankaccount account;
    char email[100];
    char gender[20];
    char alamat[100];
    char name[panjang_max_karakter];
    char password[panjang_max_password];

    printf("\n\t\t\t\t\tEmail : ");
    fgets(email, 100, stdin);//fgets untuk membaca string dan memasukkannya kedalam array
    printf("\n\t\t\t\t\tGender : ");
    fgets(gender, 100, stdin);//fgets untuk membaca string dan memasukkannya kedalam array
    printf("\n\t\t\t\t\tAlamat : ");
    fgets(alamat, 100, stdin);//fgets untuk membaca string dan memasukkannya kedalam array
    printf("\n\t\t\t\t\tMasukkan nama lengkap: ");
    fgets(name, panjang_max_karakter, stdin);//fgets untuk membaca string dan memasukkannya kedalam array
    printf("\n\t\t\t\t\tMasukkan password: ");
    int i = 0;
    while (1) {//while 1 adalah loop akan berjalan selama kondisi 1 (true)
        char c = getch();
        if (c == '\r') {
            password[i] = '\0';
            break;
        }
        else if (c == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else {
            password[i] = c;
            i++;
            printf("*");
        }
    }
    printf("\n");

    // Menghilangkan karakter newline dari input username dan password
    name[strcspn(name, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    strcpy(account.email, email);
    strcpy(account.gender, gender);
    strcpy(account.alamat, alamat);
    strcpy(account.username, name);
    strcpy(account.password, password);

    return account;
}

//fungsi untuk menambahkan akun baru kedalam array accounts
void add_account(struct bankaccount account[], int *num_accounts){
    if (*num_accounts >= account_max){
        printf("\t\t\t\t\tJumlah akun sudah mencapai maksimum\n");
        return;
    }
    account[*num_accounts] = create_account();
    (*num_accounts)++;
    printf("\t\t\t\t\tAkun Berhasil Ditambahkan");
    getchar();
    system("cls");
}

//fungsi untuk mencari index dari akun dengan username dan password tertentu
int find_account(struct bankaccount accounts[], int num_accounts, char *username, char *password){
    for (int i = 0; i < num_accounts; i++){
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0){
                return i;
        }
    }
return -1;
}

//fungsi untuk melakukan login dan mengembalikan index akun yang berhasil login
int login(struct bankaccount accounts[], int num_accounts){
    char username[panjang_max_karakter];
    char password[panjang_max_password];
    int attempts = 0;
    int index;

    while (attempts < proteksi_login) {
        printf("\t\t\t\t\tMasukkan Username: ");
        fgets(username, panjang_max_karakter, stdin);
        printf("\t\t\t\t\tMasukkan Password: ");
        int i = 0;
    while (1) {
        char c = getch();
        if (c == '\r') {
            password[i] = '\0';
            break;
        }
        else if (c == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else {
            password[i] = c;
            i++;
            printf("*");
        }
    }
    printf("\n");

    //menghilangkan karakter newline dari input username dan password
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    index = find_account(accounts, num_accounts, username, password);
    if (index >= 0){
        printf("\t\t\t\t\tLogin Berhasil\n");
        loadingbar(30);
        system("cls");
        ATM(accounts[index]);
        return index;
    }else {
        attempts++;
        printf("\t\t\t\t\tUsername atau Password salah!!!, Anda memiliki %d percobaan lagi\n", proteksi_login - attempts);
        getch();
        system("cls");
        }
    }
    printf("\t\t\t\t\tTerlalu banyak Percobaan!!! Akun diblokir\n");
    printf("\t\t\t\t\tMAAF AKUN ANDA KAMI BLOKIR\n");
    loadingbar(30);
    system("cls");
    return -1;
}
//Fungsi cek saldo
void ceksaldo(float a){
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\t\t\t\t _________________________________________");
    printf("\n\t\t\t\t|                                         |");
    printf("\n\t\t\t\t| Total saldo anda adalah $%.2f           |", a);
    printf("\n\t\t\t\t|                                         |");
    printf("\n\t\t\t\t|_________________________________________|");
    printf("\n\t\t\t\tTekan Enter Untuk Kembali Ke Menu\n");
    getch();
}
//Fungsi setor uang
int setor(){
    system("cls");
    float uang;
    //Input jumlah uang yang akan disetorkan
    printf("\n\t\t\t\tMasukkan jumlah uang yang akan disetorkan : $");
    scanf("%f", &uang);
    return uang;
}
//fungsi tarik uang
int tarik(){
    system("cls");
    float uang;
    printf("\n\t\t\t\tMasukkan Jumlah uang yang akan ditarik : $");
    scanf("%f", &uang);
    return uang;
}

//fungsi transfer uang
int transfer(float a){
    system("cls");
    int tujuan;
    float tf;
    char yt;
    printf("\n\t\t\t\t\tMasukkan nomor tujuan     : ");scanf("%d", &tujuan);
    //Input jumlah transfer
    printf("\n\t\t\t\t\tMasukkan nominal transfer : $");scanf("%f", &tf);
    //Memastikan
    printf("\n\t\t\t\t\tApakah anda yakin untuk melakukan transfer (y/t)?");scanf(" %c", &yt);
    printf("\n\t\t\t\t\t");
    //Kalau yakin
    if(yt=='y'){
        //Kalau saldo cukup
        if(tf<a){
            printf("Transfer ke %d berhasil",tujuan);
            return tf;
        }
        //Kalau saldo kurang
        else if(tf>a){
            printf("TRANSFER KE %d GAGAL!!!",tujuan);
            printf("\n\t\t\t\t\tSALDO ANDA TIDAK CUKUP!!!");
            return 0;
        }
        //Kalau saldo sama dengan jumlah transfer
        else{
            printf("Transfer ke %d berhasil",tujuan);
            printf("\n\t\t\t\t\tSALDO ANDA HABIS!!!");
            return tf;
        }
    }
    //Kalau tidak yakin
    else if(yt=='t'){
        printf("\n\t\t\t\t\tTransfer ke%d dibatalkan",tujuan);
        return 0;
    }
    //Kalau input diluar y dan t
    else{
        printf("\n\t\t\t\t\t\tTRANSFER KE %d GAGAL!!!",tujuan);
        printf("\n\n\t\t\t\t\tINPUT SALAH!!!");
        return 0;
    }
}

//Fungsi kredit
int kredit(){
    system("cls");
    char yt;
    float kredit, cicilan;
    int lama;
    //Input jumlah kredit
    printf("\n\t\t\t\t\tMasukkan jumlah uang yang akan dipinjam : $");scanf("%f", &kredit);
    //Input lama cicilan kredit
    printf("\n\t\t\t\t\tMasukkan lama cicilan (bulan)           : ");scanf("%d", &lama);
    cicilan=(kredit/lama);
    //Menampilkan cicilan per bulan
    printf("\n\t\t\t\t\tCicilan anda per bulan adalah $%.2f", cicilan);
    //Protection kredit
    printf("\n\t\t\t\t\tApakah anda setuju dengan cicilan diatas (y/t)?");scanf(" %c", &yt);
    //Kalau setuju
    if(yt=='y'){
        printf("\n\t\t\t\t\tKREDIT SEBESAR %.2f BERHASIL!!!", kredit);
        printf("\n\t\t\t\t\tLama cicilan %d bulan dengan cicilan $%.2f per bulan", lama, cicilan);
        return kredit;
    }
    //Kalau tidak setuju
    else if(yt=='t'){
        printf("\n\t\t\t\t\tKREDIT DIBATALKAN!!!");
        return 0;
    }
    //Kalau input diluar y dan t
    else{
        printf("\n\t\t\t\t\tINPUT SALAH!!!");
        printf("\n\t\t\t\t\tKREDIT GAGAL!!!");
        return 0;
    }
}

void ATM(struct bankaccount account){
    system("cls");
    int pilihan;
    float saldo=0;
    do{
        system("COLOR 03");
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t _________________________________");
        printf("\n\t\t\t\t\t|            MAZE BANK            |");
        printf("\n\t\t\t\t\t|---------------------------------|");
        printf("\n\t\t\t\t\t|1. Cek Saldo                     |");
        printf("\n\t\t\t\t\t|2. Setor Uang                    |");
        printf("\n\t\t\t\t\t|3. Tarik Uang                    |");
        printf("\n\t\t\t\t\t|4. Transfer                      |");
        printf("\n\t\t\t\t\t|5. Kredit                        |");
        printf("\n\t\t\t\t\t|6. Kembali                       |");
        printf("\n\t\t\t\t\t|_________________________________|");
        printf("\n\t\t\t\t\t Masukkan Pilihan Anda : ");scanf("%d", &pilihan);
        switch(pilihan){
            //Program Cek Saldo
            case 1:
                ceksaldo(saldo);
                break;
            //Program setor uang
            case 2:
                saldo+=setor();
                printf("\n\t\t\t\tTotal saldo anda sekarang adalah $%.2f", saldo);
                printf("\n\n\t\t\t\tTekan Enter Untuk Kembali Ke Menu\n");
                getch();
                break;
            case 3:
                saldo-=tarik(saldo);
                printf("\n\t\t\t\t\tTotal Saldo anda sekarang adalah $%.2f", saldo);
                printf("\n\t\t\t\t\tTekan Enter Untuk Kembali Ke Menu\n");
                getch();
                break;
            //Program Transfer
            case 4:
                saldo-=transfer(saldo);
                printf("\n\n\t\t\t\t\tTotal saldo anda sekarang adalah $%.2f", saldo);
                printf("\n\n\t\t\t\t\tTekan Enter Untuk Kembali Ke Menu\n");
                getch();
                break;
            //Program Kredit
            case 5:
                saldo+=kredit();
                printf("\n\t\t\t\t\tTotal saldo anda sekarang adalah $%.2f", saldo);
                printf("\n\n\t\t\t\tTekan Enter Untuk Kembali Ke Menu\n");
                getch();
                break;
            case 6:
                system("cls");
                printf("\n\n\n\n\n\n\n\t\t\t\t\tTerimakasih telah menggunakan MAZE BANK ATM");
                printf("\n\n\t\t\t\t\tTekan Enter Untuk Kembali Ke Menu Utama\n");
                getch();
                break;
            //Jika Angka Yang Dimasukkan Diluar Pilihan/Case
            default:
                //Menampilkan Kata Kata
                printf("\n\t\t\t\t\t\t\tTolong Masukkan Angka Yang Sesuai Pilihan\n\n\t\t\t\t\tJangan Ngadi Ngadi Ente\n");
                printf("\n\n\t\t\t\t\tTekan Enter Untuk Kembali Ke Menu\n");
                getch();
                break;
        }
            system("cls");
    }while(pilihan!=6);//Program Untuk EXIT Jika User Memilih
}

// Fungsi utama
int main() {
    int i,j,k;
    printf("\n\n\n\n\n\n\n");
    for (i=0; i<=100000; i++)
    {
        printf("\r\t\t\t\t\t\tLoading%d%%", i/1000);
    }
    {
        system ("cls");
    }
    struct bankaccount accounts[account_max];
    int num_accounts = 0;
    int choice = 0;
    int current_account_index = -1;

    while (true) {
        // Menampilkan menu
    printf("\t\t\t\t\t==================================\n");
    printf("\t\t\t\t\t            MAZE BANK\n");
    printf("\t\t\t\t\t==================================\n");
    printf("\t\t\t\t\t       Silakan pilih menu:\n\n");
    printf("\t\t\t\t\t       1. Buat akun\n");
    printf("\t\t\t\t\t       2. Login\n");
    printf("\t\t\t\t\t       3. Tambah akun\n");
    printf("\t\t\t\t\t       4. Tampil nama Nasabah\n");
    printf("\t\t\t\t\t       5. Keluar\n");


    printf("\t\t\t\t\t       Pilihan: ");
    scanf("%d", &choice);
    getchar();  // Menghilangkan karakter newline dari buffer input
    system("cls");
    int panjang = 20;
    loadingbar(panjang);
    system("cls");

    switch (choice) {
        case 1:
            // Membuat akun baru
            add_account(accounts, &num_accounts);
            break;
        case 2://login
            current_account_index = login(accounts, num_accounts);
            break;
        case 3://tambah akun
            add_account(accounts, &num_accounts);
            break;
        case 4:
            if (num_accounts == 0) {
                    printf("\t\t\t\t\tTidak ada akun yang tersedia.\n");
                } else {
                    printf("\t\t\t\t\tDAFTAR AKUN NASABAH MAZE BANK:\n");
                    for (int i = 0; i < num_accounts; i++) {
                        printf("\t\t\t\t\t%d. %s\n", i+1, accounts[i].username);
                        printf("\t\t\t\t\tEmail : %s\n", accounts[i].email);
                        printf("\t\t\t\t\tGender : %s\n", accounts[i].gender);
                        printf("\t\t\t\t\tAlamat : %s\n", accounts[i].alamat);
                        printf("\t\t\t\t\t========================================\n");
                    }
                }
                printf("\n\n\n\n\t\t\t\t\tTekan Enter Untuk Kembali!");
                getchar();
                system("cls");
                break;

        case 5:
            // Keluar dari program
            printf("\t\t\t\t\tTerima kasih telah menggunakan program ini.\n");
            printf("\n\n\n");
            printf("\t\t\t\t\t\t  DEVELOPER:\n\n");
            printf("\t\t\t\t\t1. JEFFRY SANJAYA NAIBAHO (672022142)\n");
            printf("\t\t\t\t\t2. REVA ADITYA (672022054)\n");
            printf("\t\t\t\t\t3. JORDAN JEFFERSEN (672022114)\n");
            printf("\t\t\t\t\t4. WAPERMAN JULI FIFE ZAI (672022239)\n");
            printf("\t\t\t\t\t5. VALENTINO MARTUA HUTAGALUNG (672022201)\n\n\n");
            exit(0);
            break;
        default:
            printf("\n\n\n");
            printf("\t\t\t\t\t     PILIHAN TIDAK VALID !!!\n");
            printf("\t\t\t\t\tMOHON MASUKKAN INPUT DENGAN BENAR");
            getchar();
            system("cls");
            break;
    }
}

return 0;
}
