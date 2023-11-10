#include <iostream>  // Mengimpor pustaka input-output standar C++.
#include <string>    // Mengimpor pustaka string untuk bekerja dengan string.
#include <conio.h>   // Mengimpor pustaka conio.h untuk menggunakan fungsi getch().
#include <unistd.h>  // Mengimpor pustaka unistd.h (tidak umum digunakan dalam C++).
#include <fstream>   // Mengimpor pustaka file stream untuk bekerja dengan berkas.
#include <sstream>   // Mengimpor pustaka stringstream untuk mengolah string.
#include <string>    // Mengimpor pustaka string lagi (ganda).
#include <algorithm> // Mengimpor pustaka algoritma yang digunakan untuk pengolahan string.
#include <ctime>     // Mengimpor pustaka waktu untuk operasi terkait waktu.
#include <iomanip>   // Mengimpor pustaka untuk mengatur format keluaran.
#include <queue>     // Mengimpor pustaka untuk menggunakan struktur data antrian (queue).
#include <limits>    // Mengimpor pustaka untuk mengakses nilai maksimum tipe data (jarang digunakan).

using namespace std;

int adminLoginAttempts = 0; // Reset jumlah percobaan login gagal
int userLoginAttempts = 0;  // Reset jumlah percobaan login gagal

// kelas menyimpan informasi login admin
class Node
{
public:
    string username; // bertipe data string, untuk menyimpan username.
    string password; // bertipe data string, untuk menyimpan password.
    Node *next;

    Node(string user, string pass)
    {
        username = user; // inisialisasi variable username.
        password = pass; // inisialisasi variable password.
        next = nullptr;  // inisialisasi pointer next menjadi nullptr saat node baru dibuat.
    }
};

// kelas menyimpan informasi login user
class LinkedList
{
public:
    // pointer ke node pertama (head) dalam linkedlist
    Node *head;

    LinkedList()
    {
        // inisialisasi head linkedlist menjadi nullptr saat linked list dibuat
        head = nullptr;
    }

    void insertUser(string username, string password)
    {

        Node *newNode = new Node(username, password); // Membuat node baru dengan data username dan password.
        newNode->next = head;                         // Mengatur pointer next dari node baru ke node yang saat ini menjadi head.
        head = newNode;                               // Menjadikan node baru sebagai head (node pertama) dari linked list.
    }

    bool checkUser(string username, string password)
    {
        // Membuat pointer current yang awalnya menunjuk ke head linked list.
        Node *current = head;
        while (current != nullptr)
        {
            if (current->username == username && current->password == password)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

// struct penyimpanan untuk pasien
struct Pasien
{
    int noberobat;     // nomor berobat bertipe integer
    string namapasien; // namapasien bertipe string
    int umur;          // umur bertipe integer
    string status;     // status bertipe string
    string keluhan;    // keluhan bertipe string
    int tgl, bln, thn; // tanggal,bulan, dan tahun lahir pasien bertipe integer
    int registrationNumber;
    Pasien *next;      // Pointer yang menunjuk ke pasien selanjutnya dalam linked list.
};
// Global vector to store the queue of patients
queue<Pasien, deque<Pasien>> antrianKlinik;

// fungsi menampilkan data pasien
void showmenu()//prosedur untuk menampilkan tampilan menu
{
    system("cls");
    cout << "===================================================================" << endl;
    cout << "|                     Data Pasien Structure Farma                 |" << endl;
    cout << "|-----------------------------------------------------------------|" << endl;
    cout << "|          1. Tambah Data Pasien                                  |" << endl;
    cout << "|          2. Lihat Data Pasien                                   |" << endl;
    cout << "|          3. Sorting Data Pasien                                 |" << endl;
    cout << "|          4. Searching Data Pasien                               |" << endl;
    cout << "|          5. Update Data Pasien                                  |" << endl;
    cout << "|          6. Delete Data Pasien                                  |" << endl;
    cout << "|          7. Panggil Antrian Pasien                              |" << endl;
    cout << "|          8. Keluar                                              |" << endl;
    cout << "|-----------------------------------------------------------------|" << endl;
    cout << "===================================================================" << endl;
}

// membersihkan buffer
void clearInputBuffer()
{
    std::cin.clear();  // Membersihkan status error pada input stream.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Mengabaikan karakter yang tersisa dalam buffer hingga karakter newline ('\n') ditemukan.
}

void pause()//prosedur untuk jeda
{
    cout << endl;  // Mencetak baris kosong untuk tampilan yang lebih rapi.
    cout << "Tekan tombol apa pun untuk kembali ke menu..." << endl;  // Menampilkan pesan untuk memberi tahu pengguna untuk menekan tombol.
    getch();  // Menunggu hingga pengguna menekan tombol sebelum melanjutkan eksekusi program.
}


bool term(char c)//tipe data untuk cek character
{
    // Fungsi ini memeriksa apakah karakter c adalah huruf alfabet (a-z atau A-Z).
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool character(char c)//tipe data untuk cek character
{
    // Fungsi ini memeriksa apakah karakter c adalah spasi (whitespace).
    return c == ' ';
}

bool check(const string &str) //tipe data cek charcter
{
    // Fungsi ini memeriksa apakah string str hanya terdiri dari huruf alfabet atau spasi.
    for (char c : str)
    {
        // Menggunakan fungsi term() dan character() untuk validasi karakter.
        if (!term(c) && !character(c))
        {
            // Jika ditemukan karakter yang bukan huruf alfabet atau spasi, maka mengembalikan false.
            return false;
        }
    }
    // Jika semua karakter valid, maka mengembalikan true.
    return true;
}

bool cekTanggal(Pasien **datapasien)// tipe data untuk cek tanggal
{
   // Inisialisasi struktur tm (timeinfo) dengan semua nilai awalnya diatur ke nol.
struct tm tm = {0};

// Mengatur komponen 'tm_mday' (hari) dengan nilai yang diambil dari objek 'datapasien' yaitu 'tgl'.
tm.tm_mday = (*datapasien)->tgl;

// Mengatur komponen 'tm_mon' (bulan) dengan nilai yang diambil dari objek 'datapasien' yaitu 'bln' yang dikurangi 1.
// (Penjelasan: Bulan pada struktur tm dimulai dari 0 untuk Januari hingga 11 untuk Desember, sehingga perlu dikurangi 1).
tm.tm_mon = (*datapasien)->bln - 1;

// Mengatur komponen 'tm_year' (tahun) dengan nilai yang diambil dari objek 'datapasien' yaitu 'thn' yang dikurangi 1900.
// (Penjelasan: Struktur tm menyimpan tahun sebagai offset dari tahun 1900).
tm.tm_year = (*datapasien)->thn - 1900;


    // Mengatur komponen 'tm_hour' (jam) ke 0.
tm.tm_hour = 0;

// Mengatur komponen 'tm_min' (menit) ke 0.
tm.tm_min = 0;

// Mengatur komponen 'tm_sec' (detik) ke 0.
tm.tm_sec = 0;


    // Mengubah tanggal diinput agar sesuai dengan standar penanggalan
    time_t time = mktime(&tm);

    // Check if mktime changed the date components
    // For example, if you provide an invalid date like February 31st,
    // mktime will adjust it to a valid date (March 3rd).
   // Memeriksa apakah tanggal yang diambil dari objek 'datapasien' sesuai dengan standar penanggalan.
return (
    (*datapasien)->tgl == tm.tm_mday && // Membandingkan hari dengan komponen 'tm_mday' di struktur 'tm'.
    (*datapasien)->bln == tm.tm_mon + 1 && // Membandingkan bulan dengan komponen 'tm_mon' di struktur 'tm' (ditambahkan 1 karena bulan dimulai dari 0).
    (*datapasien)->thn == tm.tm_year + 1900); // Membandingkan tahun dengan komponen 'tm_year' di struktur 'tm' (ditambahkan 1900 karena struktur tm menyimpan tahun sebagai offset dari tahun 1900).

// Jika tanggal yang di-input sesuai dengan standar penanggalan, maka fungsi akan mengembalikan nilai True.

}

// menu utama
void menu()
{
    cout << "===================================================================" << endl;
    cout << "|                   Welcome To Structure Farma                    |" << endl;
    cout << "|-----------------------------------------------------------------|" << endl;
    cout << "|          [1] Admin                                              |" << endl;
    cout << "|          [2] Users                                              |" << endl;
    cout << "|          [3] Exit                                               |" << endl;
    cout << "===================================================================" << endl;
    cout << "Masukkan Pilihan Anda: ";
}

// login admin
void loginadmin()
{
    cout << "===================================================================" << endl;
    cout << "                    Welcome Admin Structure Farma                  " << endl;
    cout << "===================================================================" << endl;
}
void loginuser()//tampilan login user
{
    cout << "--------------------------------------------------------------------" << endl;
    cout << "                    Welcome To Structure Farma                      " << endl;
    cout << "--------------------------------------------------------------------" << endl;
}

// tabel end program
void end()
{
    system("cls");
    cout << "------------------------------------------------------------------" << endl;
    cout << "                    Thank you for trusting us                     " << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "                        Structure Farma                           " << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << endl;
}

// fungsi input data pasien
void inputdatapasien(Pasien *newdata)
{
    cin.ignore(); // Membersihkan buffer masukan sebelum mengambil input.

    while (true)
    {
        cout << "Nama pasien: ";
        // Mengambil input untuk nama pasien.
        getline(cin, newdata->namapasien);

        // Memeriksa apakah input nama pasien kosong atau tidak hanya berisi huruf.
        if (newdata->namapasien.empty() || !check(newdata->namapasien))
        {
            cout << "Inputan harus berupa huruf dan tidak boleh kosong" << endl;
            continue;
        }
        break; // Keluar dari loop jika input nama pasien valid.
    }

    while (true)
    {
        string input;
        cout << "Nomor berobat: ";
        getline(cin, input);

        // Memeriksa apakah input kosong atau tidak semua karakternya adalah angka
        if (input.empty() || !std::all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "Harus berupa angka" << endl;
            continue; // Melanjutkan loop jika input tidak valid
        }

        // Konversi string input menjadi integer dan simpan ke dalam newdata->noberobat
        newdata->noberobat = std::stoi(input);

        break; // Keluar dari loop jika input nomor berobat sudah valid

    }

    while (true)
    {
        string input;
        cout << "Umur: ";
        getline(cin, input);

        // Memeriksa apakah input kosong atau tidak semua karakternya adalah angka
        if (input.empty() || !std::all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "Harus berupa angka" << endl;
            continue; // Melanjutkan loop jika input tidak valid
        }

        // Konversi string input menjadi integer dan simpan ke dalam newdata->umur
        newdata->umur = std::stoi(input);

        break; // Keluar dari loop jika input umur sudah valid

    }

    while (true)
    {
        cout << "Status: ";
        // Membersihkan buffer masukan
        getline(cin, newdata->status);

        // Memeriksa apakah input status kosong atau tidak valid (harus huruf dan tidak kosong)
        if (newdata->status.empty() || !check(newdata->status))
        {
            cout << "Inputan harus berupa huruf dan tidak boleh kosong" << endl;
            continue; // Melanjutkan loop jika input tidak valid
        }
        // Memeriksa apakah inputan adalah "BPJS" atau "mandiri"
        if (newdata->status != "BPJS" && newdata->status != "Pembayaran Mandiri")
        {
            cout << "Status hanya bisa diisi dengan 'BPJS' atau 'Pembayaran Mandiri'" << endl;
            continue;
        }

        break; // Keluar dari loop jika input status sudah valid

    }

    while (true)
    {
        cout << "Keluhan: ";
        // Membersihkan buffer masukan
        getline(cin, newdata->keluhan);
    
        // Memeriksa apakah input keluhan kosong atau tidak valid (harus huruf dan tidak kosong)
        if (newdata->keluhan.empty() || !check(newdata->keluhan))
        {
            cout << "Inputan harus berupa huruf dan tidak boleh kosong" << endl;
            continue; // Melanjutkan loop jika input tidak valid
        }
    
        break; // Keluar dari loop jika input keluhan sudah valid
    }


    while (true)
    {
        string input;
        // Input Tanggal
        while (true)
        {
            cout << "Tanggal: ";
            getline(cin, input);
        
            // Memeriksa apakah input kosong atau bukan angka atau kurang dari 1 atau lebih dari 31
            if (input.empty() || !std::all_of(input.begin(), input.end(), ::isdigit) || stoi(input) < 1 || stoi(input) > 31)
            {
                cout << "Harus berupa angka, tidak kurang dari 1 atau lebih dari 31" << endl;
                continue; // Melanjutkan loop jika input tidak valid
            }
        
            // Konversi string ke integer
            newdata->tgl = std::stoi(input);
            break; // Keluar dari loop jika input sudah valid
        }
        
        // Input Bulan
        while (true)
        {
            cout << "Bulan: ";
            getline(cin, input);
        
            // Memeriksa apakah input kosong atau bukan angka atau kurang dari 1 atau lebih dari 12
            if (input.empty() || !std::all_of(input.begin(), input.end(), ::isdigit) || stoi(input) < 1 || stoi(input) > 12)
            {
                cout << "Harus berupa angka, tidak kurang dari 1 atau lebih dari 12" << endl;
                continue; // Melanjutkan loop jika input tidak valid
            }
        
            // Konversi string ke integer
            newdata->bln = std::stoi(input);
            break; // Keluar dari loop jika input sudah valid
        }
        
        // Input Tahun
        while (true)
        {
            cout << "Tahun: ";
            getline(cin, input);
        
            // Memeriksa apakah input kosong atau bukan angka atau kurang dari 2020 atau lebih dari 2023
            if (input.empty() || !std::all_of(input.begin(), input.end(), ::isdigit) || stoi(input) < 2020 || stoi(input) > 2023)
            {
                cout << "Harus berupa angka, tidak kurang dari 2020 atau lebih dari 2023" << endl;
                continue; // Melanjutkan loop jika input tidak valid
            }
        
            // Konversi string ke integer
            newdata->thn = std::stoi(input);
            break; // Keluar dari loop jika input sudah valid
        }
        
        // Memeriksa validitas tanggal dengan fungsi cekTanggal
        if (!cekTanggal(&newdata))
        {
            cout << "Tanggal tidak valid" << endl;
            continue; // Melanjutkan loop jika tanggal tidak valid
        }
        
        break; // Keluar dari loop input data pasien jika semua data sudah valid

    }
}

// tambah data awal
void tambahdata(Pasien *&head)
{
    // Membuat objek pointer Pasien yang baru
        Pasien *newdata = new Pasien;

        // Membersihkan layar konsol
        system("cls");

        // Menampilkan header untuk penambahan data pasien
        cout << "------------------------------------------------------------------\n";
        cout << "                         Tambah data pasien                         " << endl;
        cout << "------------------------------------------------------------------\n";

        // Memanggil fungsi inputdatapasien untuk mengisi data pada objek baru
        inputdatapasien(newdata);

        // Mengecek apakah linked list kosong
        if (head == NULL)
        {
            // Jika kosong, objek baru menjadi head dan tidak memiliki next
            head = newdata;
            newdata->next = NULL;
        }
        else
        {
            // Jika tidak kosong, mencari posisi terakhir dalam linked list
            Pasien *current = head;
            while (current->next != NULL)
                current = current->next;

            // Menambahkan objek baru sebagai elemen terakhir dalam linked list
            current->next = newdata;
            newdata->next = NULL;
        }

        // Menampilkan pesan bahwa data berhasil ditambahkan
        cout << "Data berhasil ditambahkan\n";
}

void showdata(Pasien *head)//prosedur menampilkan data pasien
{
        // Mengecek apakah linked list kosong
    if (!head)
    {
        // Jika kosong, tampilkan pesan dan keluar dari fungsi
        cout << "data kosong. \n";
        return;
    }
    
    // Membersihkan layar konsol
    system("cls");
    
    // Pointer untuk mengunjungi setiap elemen dalam linked list, dimulai dari head
    Pasien *current = head;
    
    // Menampilkan header untuk melihat data pasien
    cout << "------------------------------------------------------------------\n";
    cout << "                         Lihat data pasien                        " << endl;
    cout << "------------------------------------------------------------------\n";
    
    // Melakukan perulangan untuk menampilkan data setiap pasien
    while (current)
    {
        // Menampilkan detail informasi pasien
        cout << "Nama Pasien     : " << current->namapasien << endl;
        cout << "Nomor berobat   : " << current->noberobat << endl;
        cout << "Umur            : " << current->umur << endl;
        cout << "Status          : " << current->status << endl;
        cout << "Keluhan         : " << current->keluhan << endl;
        cout << "Tanggal         : " << current->tgl << "/" << setw(2) << setfill('0') << current->bln << "/" << current->thn << endl;
        cout << "------------------------------------------------------------------\n";
    
        // Pindah ke elemen berikutnya dalam linked list
        current = current->next;
    }
    
}

void updatedata(Pasien *head, int targetnomorberobat)//prosedur untuk mengupdate atau mengubah data yang sudah
{
    // Inisialisasi pointer 'current' dan atur ke kepala linked list
    Pasien *current = head;

    // Bersihkan layar konsol
    system("cls");

    // Iterasi melalui linked list
    while (current)
    {
    // Periksa apakah node saat ini tidak NULL dan memiliki nomor berobat target
    if (current != NULL && current->noberobat == targetnomorberobat)
    {
        // Tampilkan header pembaruan
        cout << "------------------------ Update data -----------------------------\n";
        
        // Tampilkan data pasien saat ini
        cout << "Nama pasien     : " << current->namapasien << endl;
        cout << "Nomor berobat   : " << current->noberobat << endl;
        cout << "Umur            : " << current->umur << endl;
        cout << "Status          : " << current->status << endl;
        cout << "Keluhan         : " << current->keluhan << endl;
        cout << "Tanggal         : " << current->tgl << "/" << setw(2) << setfill('0') << current->bln << "/" << current->thn << endl;
        cout << "------------------------------------------------------------------\n";
        cout << "Masukkan Data Baru! \n";
        // cin.ignore(); // Commented out, not currently in use

        // Loop untuk memastikan input nama pasien valid
        while (true)
        {
            // Meminta pengguna memasukkan nama pasien baru
            cout << "Nama Pasien   : ";
            getline(cin, current->namapasien);

            // Validasi input (tidak boleh kosong dan hanya huruf)
            if (current->namapasien.empty() || !check(current->namapasien))
            {
                cout << "Inputan harus berupa huruf dan tidak boleh kosong" << endl;
                continue;
            }
            break; // Keluar dari loop jika input valid
        }

            // Loop untuk memastikan input nomor berobat valid
        while (true)
        {
            string input;
            cout << "Nomor Berobat : ";
            getline(cin, input);

            // Cek jika input kosong atau bukan angka
            if (input.empty() || !all_of(input.begin(), input.end(), ::isdigit))
            {
                cout << "Harus berupa angka dan tidak boleh kosong" << endl;
                continue;
            }

            // Konversi string ke integer
            current->noberobat = stoi(input);
            break; // Keluar dari loop jika input valid
        }

        // Loop untuk memastikan input umur valid
        while (true)
        {
            string input;
            cout << "Umur          : ";
            getline(cin, input);

            // Cek jika input kosong atau bukan angka
            if (input.empty() || !all_of(input.begin(), input.end(), ::isdigit))
            {
                cout << "Harus berupa angka dan tidak boleh kosong" << endl;
                continue;
            }

            // Konversi string ke integer
            current->umur = stoi(input);
            break; // Keluar dari loop jika input valid
        }


            // Loop untuk memastikan input status valid
        while (true)
        {
            cout << "Status        : ";
            getline(cin, current->status);

            // Validasi input (tidak boleh kosong dan hanya huruf)
            if (current->status.empty() || !check(current->status))
            {
                cout << "Inputan harus berupa huruf dan tidak boleh kosong" << endl;
                continue;
            }

            // Memeriksa apakah inputan adalah "BPJS" atau "Pembayaran Mandiri"
            if (current->status != "BPJS" && current->status != "Pembayaran Mandiri")
            {
                cout << "Status hanya bisa diisi dengan 'BPJS' atau 'Pembayaran Mandiri'" << endl;
                continue;
            }

            break; // Keluar dari loop jika input valid
        }

        // Loop untuk memastikan input keluhan valid
        while (true)
        {
            cout << "Keluhan       : ";
            getline(cin, current->keluhan);

            // Validasi input (tidak boleh kosong dan hanya huruf)
            if (current->keluhan.empty() || !check(current->keluhan))
            {
                cout << "Inputan harus berupa huruf dan tidak boleh kosong" << endl;
                continue;
            }

            break; // Keluar dari loop jika input valid
        }

            // Loop utama untuk memastikan input tanggal, bulan, dan tahun valid
        while (true)
        {
            string input;

            // Input tanggal
            while (true)
            {
                cout << "Tanggal       : ";
                getline(cin, input);

                // Validasi input (harus berupa angka, tidak kurang dari 1 atau lebih dari 31)
                if (input.empty() || !all_of(input.begin(), input.end(), ::isdigit) || stoi(input) < 1 || stoi(input) > 31)
                {
                    cout << "Harus berupa angka, tidak kurang dari 1 atau lebih dari 31" << endl;
                    continue;
                }

                // Konversi string ke integer
                current->tgl = stoi(input);
                break; // Keluar dari loop jika input valid
            }

            // Input bulan
            while (true)
            {
                cout << "Bulan         : ";
                getline(cin, input);

                // Validasi input (harus berupa angka, tidak kurang dari 1 atau lebih dari 12)
                if (input.empty() || !all_of(input.begin(), input.end(), ::isdigit) || stoi(input) < 1 || stoi(input) > 12)
                {
                    cout << "Harus berupa angka, tidak kurang dari 1 atau lebih dari 12" << endl;
                    continue;
                }

                // Konversi string ke integer
                current->bln = stoi(input);
                break; // Keluar dari loop jika input valid
            }

            // Input tahun
            while (true)
            {
                cout << "Tahun         : ";
                getline(cin, input);

                // Validasi input (harus berupa angka, tidak kurang dari 2020 atau lebih dari 2023)
                if (input.empty() || !all_of(input.begin(), input.end(), ::isdigit) || stoi(input) < 2020 || stoi(input) > 2023)
                {
                    cout << "Harus berupa angka, tidak kurang dari 2020 atau lebih dari 2023" << endl;
                    continue;
                }

                // Konversi string ke integer
                current->thn = stoi(input);
                break; // Keluar dari loop jika input valid
            }

            // Validasi tanggal menggunakan fungsi cekTanggal
            if (!cekTanggal(&current))
            {
                cout << "Tanggal tidak valid" << endl;
                continue;
            }

            break; // Keluar dari loop utama jika semua input tanggal, bulan, dan tahun valid
        }

        // Menampilkan pesan bahwa data telah diperbarui
        cout << "Data Updated!\n";
        return;

        }
        current = current->next;// Pindah ke node berikutnya dalam linked list
    }
    cout << "Data with code" << targetnomorberobat << "not found\n";// Menampilkan pesan bahwa data dengan nomor berobat yang ditargetkan tidak ditemukan
}

// hapus data
void deletedata(Pasien *&head, int targetnomorberobat)
{
   // Memeriksa apakah linked list kosong
if (!head)
{
        // Menampilkan pesan bahwa data pasien kosong
        cout << "Data pasien kosong.\n";
        return;
    }

    // Inisialisasi pointer 'current' dan 'prev' untuk traversing linked list
    Pasien *current = head;
    Pasien *prev = nullptr;

    // Iterasi melalui linked list
    while (current)
    {
        // Memeriksa apakah nomor berobat pada node saat ini sama dengan target
        if (current->noberobat == targetnomorberobat)
        {
            // Memeriksa apakah node saat ini bukan node pertama
            if (prev)
            {
                // Menghubungkan node sebelumnya ke node setelahnya
                prev->next = current->next;
            }
            else
            {
                // Jika node pertama dihapus, mengubah 'head' ke node berikutnya
                head = current->next;
            }

            // Menghapus node yang ditemukan
            delete current;

            // Menampilkan pesan bahwa data pasien berhasil dihapus
            cout << "Data pasien dengan nomor berobat '" << targetnomorberobat << "' berhasil dihapus!\n";
            return;
        }

        // Memindahkan 'prev' dan 'current' ke node berikutnya
        prev = current;
        current = current->next;
    }

    // Menampilkan pesan bahwa data pasien dengan nomor berobat yang ditargetkan tidak ditemukan
    cout << "Data pasien dengan nomor berobat '" << targetnomorberobat << "' tidak ditemukan.\n";

}

// split data
void splitlist(Pasien *source, Pasien *&front, Pasien *&back)
{
        // Inisialisasi pointer 'slow' dan 'fast' pada node pertama dan node kedua dari linked list 'source'
    Pasien *slow = source;
    Pasien *fast = source->next;

    // Iterasi melalui linked list dengan 'fast' bergerak dua kali lipat kecepatan 'slow'
    while (fast)
    {
        // 'fast' bergerak satu langkah
        fast = fast->next;

        // Memeriksa apakah 'fast' tidak NULL
        if (fast)
        {
            // 'slow' bergerak satu langkah
            slow = slow->next;

            // 'fast' bergerak satu langkah lagi
            fast = fast->next;
        }
    }

    // Mengatur pointer 'front' ke awal linked list 'source'
    front = source;

    // Mengatur pointer 'back' ke node setelah 'slow', membagi linked list menjadi dua bagian
    back = slow->next;

    // Memutuskan koneksi antara 'slow' dan 'back', sehingga linked list terbagi menjadi dua
    slow->next = nullptr;

}

// Fungsi Mergelists untuk menggabungkan dua linked list yang terurut
Pasien *Mergelists(Pasien *a, Pasien *b)
{
        // Inisialisasi pointer 'result' sebagai NULL
    Pasien *result = nullptr;

    // Jika linked list 'a' kosong, kembalikan linked list 'b'
    if (!a)
        return b;

    // Jika linked list 'b' kosong, kembalikan linked list 'a'
    else if (!b)
        return a;

    // Membandingkan nilai 'namapasien' dari dua node dan menggabungkannya secara berurutan
    if (a->namapasien <= b->namapasien)
    {
        // Jika 'namapasien' pada 'a' lebih kecil atau sama dengan 'b', 'result' diatur ke 'a'
        result = a;

        // Rekursif untuk menggabungkan sisa linked list 'a' dengan 'b'
        result->next = Mergelists(a->next, b);
    }
    else
    {
        // Jika 'namapasien' pada 'b' lebih kecil, 'result' diatur ke 'b'
        result = b;

        // Rekursif untuk menggabungkan sisa linked list 'b' dengan 'a'
        result->next = Mergelists(a, b->next);
    }

    // Kembalikan pointer 'result' setelah proses penggabungan selesai
    return result;

}

// Fungsi MergeSort yang mengurutkan linked list
void MergeSort(Pasien *&head)
{
    // Inisialisasi pointer 'current', 'front', dan 'back'
    Pasien *current = head;
    Pasien *front = nullptr;
    Pasien *back = nullptr;

    // Jika linked list kosong atau hanya memiliki satu elemen, kembalikan
    if (!current || !current->next)
        return;

    // Memanggil fungsi splitlist untuk membagi linked list menjadi dua bagian hampir setara
    splitlist(current, front, back);

    // Memanggil fungsi MergeSort untuk mengurutkan setiap bagian linked list secara rekursif
    MergeSort(front);
    MergeSort(back);

    // Menggabungkan dua bagian yang sudah diurutkan kembali menjadi linked list utuh yang diurutkan
    head = Mergelists(front, back);

}
// sorting
void sorting(Pasien *&head)
{
    MergeSort(head);//memanggil fungsi Mergesort untuk melakukan sorting
}

// SEARCHING
// Mengembalikan pointer ke node pasien pada indeks tertentu dalam linked list
Pasien *getPasien(Pasien *head, int index)
{
    // Inisialisasi pointer 'current' ke head dan variabel 'count' ke 0
    Pasien *current = head;
    int count = 0;

    // Iterasi melalui linked list sampai mencapai indeks yang diinginkan atau akhir linked list
    while (current && count < index)
    {
        // Pindah ke node berikutnya
        current = current->next;

        // Increment count
        count++;
    }

    // Mengembalikan pointer ke node pasien pada indeks tertentu atau NULL jika indeks melebihi panjang linked list
    return current;
}

// Fungsi untuk mencari data Pasien berdasarkan merk
Pasien *fibonacciSearchnama(Pasien *head, const string &targetnama)
{
    // Menghitung panjang linked list
    int length = 0;
    Pasien *current = head;

    // Iterasi melalui linked list dan menghitung jumlah node
    while (current)
    {
        length++;
        current = current->next;
    }

    // Jika linked list kosong, tampilkan pesan dan kembalikan NULL
    if (length == 0)
    {
        cout << "No data here" << endl;
        return nullptr;
    }

    // Inisialisasi variabel untuk implementasi algoritma Fibonacci search
    int fibMMinus2 = 0;
    int fibMMinus1 = 1;
    int fibM = fibMMinus2 + fibMMinus1;

    // Menemukan nilai Fibonacci terbesar yang kurang dari atau sama dengan panjang linked list
    while (fibM < length)
    {
        fibMMinus2 = fibMMinus1;
        fibMMinus1 = fibM;
        fibM = fibMMinus2 + fibMMinus1;
    }

    // Inisialisasi variabel offset untuk menandai posisi awal pencarian
    int offset = -1;

    // Algoritma Fibonacci search untuk mencari targetnama dalam linked list
    while (fibM > 1)
    {
        // Menghitung indeks i dan mendapatkan namapasien pada indeks tersebut
        int i = min(offset + fibMMinus2, length - 1);
        string merkPasien = getPasien(head, i)->namapasien;

        // Membandingkan merkPasien dengan targetnama dan memperbarui variabel offset dan fibM
        if (merkPasien < targetnama)
        {
            fibM = fibMMinus1;
            fibMMinus1 = fibMMinus2;
            fibMMinus2 = fibM - fibMMinus1;
            offset = i;
        }
        else if (merkPasien > targetnama)
        {
            fibM = fibMMinus2;
            fibMMinus1 = fibMMinus1 - fibMMinus2;
            fibMMinus2 = fibM - fibMMinus1;
        }
        else
        {
            // Jika merkPasien sama dengan targetnama, kembalikan node pada indeks i
            return getPasien(head, i);
        }
    }

    // Memeriksa apakah elemen terakhir setelah offset + 1 memiliki targetnama
    if (fibMMinus1 && getPasien(head, offset + 1)->namapasien == targetnama)
    {
        return getPasien(head, offset + 1);
    }

    // Jika targetnama tidak ditemukan, kembalikan NULL
    return nullptr;

}

// struct to csv
void StructToCSV(Pasien *head)
{   
    // Membuka file "structurefarma.csv" untuk penulisan
    fstream fout;
    fout.open("A1_Kelompok4.csv", ios::out);

    // Inisialisasi pointer 'current' untuk iterasi melalui linked list
    Pasien *current = head;

    // Iterasi melalui linked list dan menulis data setiap node ke file CSV
    while (current != NULL)
    {
        fout << current->namapasien << ","  // Menulis nama pasien
             << current->noberobat << ","    // Menulis nomor berobat
             << current->umur << ","         // Menulis umur
             << current->status << ","       // Menulis status
             << current->keluhan << ","      // Menulis keluhan
             << current->tgl << "," << current->bln << "," << current->thn << "\n";  // Menulis tanggal, bulan, dan tahun

        // Pindah ke node berikutnya
        current = current->next;
}

        // Menutup file setelah selesai penulisan
        fout.close();

}

// struct csv to struct
void CSVToStruct(Pasien *&head)
{
    // Membuka file "structurefarma.csv" untuk membaca
    fstream fin;
    fin.open("A1_Kelompok4.csv", ios::in);

    // Inisialisasi variabel untuk menyimpan setiap baris dari file CSV
    string line;

    // Memeriksa apakah file berhasil dibuka
    if (fin.is_open())
    {
        // Iterasi melalui setiap baris dalam file CSV
        while (getline(fin, line))
        {
            // Membuat stringstream untuk memproses setiap nilai terpisah oleh koma
            stringstream ss(line);

            // Deklarasi variabel string untuk menyimpan nilai dari setiap kolom
            string nama_str, no_berobat_str, umur_str, status_str, keluhan_str, tgl_str, bln_str, thn_str;

            // Mendapatkan nilai dari setiap kolom menggunakan getline
            getline(ss, nama_str, ',');
            getline(ss, no_berobat_str, ',');
            getline(ss, umur_str, ',');
            getline(ss, status_str, ',');
            getline(ss, keluhan_str, ',');
            getline(ss, tgl_str, ',');
            getline(ss, bln_str, ',');
            getline(ss, thn_str, '\n');

            // Menggunakan stringstream untuk mengkonversi string ke tipe data yang sesuai
            int no_berobat_i, umur_i, tgl_i, bln_i, thn_i;
            stringstream ss_no(no_berobat_str);
            stringstream ss_umur(umur_str);
            stringstream ss_tgl(tgl_str);
            stringstream ss_bln(bln_str);
            stringstream ss_thn(thn_str);
            ss_no >> no_berobat_i;
            ss_umur >> umur_i;
            ss_tgl >> tgl_i;
            ss_bln >> bln_i;
            ss_thn >> thn_i;

            // Membuat node baru dengan nilai dari file CSV
            Pasien *newdata = new Pasien;
            newdata->namapasien = nama_str;
            newdata->noberobat = no_berobat_i;
            newdata->umur = umur_i;
            newdata->status = status_str;
            newdata->keluhan = keluhan_str;
            newdata->tgl = tgl_i;
            newdata->bln = bln_i;
            newdata->thn = thn_i;

            // Memasukkan node baru ke linked list
            if (!head)
            {
                head = newdata;
                newdata->next = NULL;
            }
            else
            {
                Pasien *current = head;
                while (current->next != NULL)
                    current = current->next;
                current->next = newdata;
            }
        }

        // Menampilkan pesan sukses jika proses selesai
        cout << "-----------------------------------------------------------" << endl;
        cout << "Succesfuly: Data dari CSV telah dimasukkan ke dalam Struct." << endl;
        cout << "-----------------------------------------------------------" << endl;

        // Menutup file setelah selesai membaca
        fin.close();
        system("pause");
    }
    else
    {
        // Menampilkan pesan error jika file tidak ditemukan
        cout << "ERROR: CSV tidak ditemukan." << endl;
        system("pause");
        return;
}

    }


// Fungsi untuk menambahkan pasien ke dalam antrian klinik
void tambahAntrian(const string &namapasien, int registrationNumber)
{
    // Memeriksa apakah antrian belum penuh (maksimal 5 pasien)
    if (antrianKlinik.size() < 5) {
        // Membuat objek Pasien baru
        Pasien patient;
        patient.namapasien = namapasien;
        patient.registrationNumber = registrationNumber;

        // Menambahkan pasien ke dalam antrian menggunakan queue
        antrianKlinik.push(patient);

        // Menampilkan nomor antrian pasien
        cout << "Nomor Antrian Anda Adalah: " << antrianKlinik.size() << endl;
    } else {
        // Menampilkan pesan jika antrian sudah penuh
        cout << "Antrian penuh. Mohon tunggu!" << endl;
    }
}


// Fungsi untuk memanggil pasien berikutnya dari antrian klinik
void panggilantrian(){
    // Memeriksa apakah antrian tidak kosong
    if (!antrianKlinik.empty())
    {
        // Mengambil data pasien berikutnya dari depan antrian
        Pasien patientSelanjutnya = antrianKlinik.front();
        antrianKlinik.pop();

        // Menampilkan informasi pasien yang baru saja dipanggil
        loginuser();  // Fungsi loginuser() digunakan untuk menampilkan informasi login user (tidak diberikan dalam kode yang diberikan)
        cout << "Nama          : " << patientSelanjutnya.namapasien << endl;
        cout << "Nomor berobat : " << patientSelanjutnya.registrationNumber << endl;

        // Menampilkan pesan untuk meminta pasien masuk ke klinik
        cout << "Antrian " << patientSelanjutnya.namapasien << " silakan masuk ke klinik." << endl;
    }
    else
    {
        // Menampilkan pesan jika antrian kosong
        cout << "Tidak Ada Antrian Yang Tersisa." << endl;
    }
}

int main()//program inti
{
    int length = 0; // Inisialisasi panjang awal data pasien
    Pasien *patientHead = nullptr; // Pointer ke awal linked list data pasien
    int targetnomorberobat; // Nomor berobat yang menjadi target operasi

    // Mengisi linked list data pasien dari file CSV
    CSVToStruct(patientHead);

    LinkedList users; // Objek dari kelas LinkedList untuk manajemen pengguna
    users.insertUser("admin", "admin"); // Menambahkan pengguna admin dengan username "admin" dan password "admin"

    int choice; // Variabel untuk menyimpan pilihan menu
    int noberobat; // Variabel untuk nomor berobat pasien
    string namapasien; // Variabel untuk nama pasien
    int umur; // Variabel untuk umur pasien
    string status; // Variabel untuk status pasien
    string keluhan; // Variabel untuk keluhan pasien

	
    do//loop
    {
        system("cls");//clear screen
        menu();//fungsi mennammpilkan menu

        if (!(cin >> choice))//pengondisian error handling inputan
        {
            cout << "Masukkan Opsi Lainnya" << endl;
            clearInputBuffer();//memanggil error handling
        }
        else//jika else maka masukk ke case
        {
            switch (choice)//case 
            {
            case 1://jika pilih 1
            {
                // Bagian login admin
                adminLoginAttempts++;//pemanggilan variabel percobaan login admin increment
                string username, password;//deklarasi username  dan pass
                system("cls");//clear screen
                loginadmin();//pemanggilan  fungsi  login admin
                cout << "Masukkan Username: ";
                cin >> username;//masukkan inputan username
                cout << "Masukkan Password: ";
                cin >> password;//masukkan  inputan pass

                if (users.checkUser(username, password))//pengondisian cek username dan pass
                {
                    cout << "Login Admin Berhasil!" << endl;//jika berhasil
                    adminLoginAttempts = 0;//reset jadi  0

                    int patientChoice;//deklrasi  inputan pilihan
                    do//loop
                    {
                        showmenu();//menu
                        cout << "Masukkan Pilihan : ";
                        if (!(cin >> patientChoice))//pengondisian error handling inputan
                        {
                            cout << "Pilihan tidak valid!" << endl;
                            clearInputBuffer();//jika tidak valid maka fungsi error  handling terpanggil
                        }
                        else//jika tidak  maka masuk  ke  switch  case
                        {
                            switch (patientChoice)//case
                            {
                            case 1://jika  pilih 1
                                tambahdata(patientHead);//maka tambah data
                                StructToCSV(patientHead);//pemanggilan fungsi csv agar data masuk
                                pause();//jeda
                                break;//kemudian break
                            case 2://jika  2
                                showdata(patientHead);//tampilkan  data pasien
                                pause();//jeda
                                break;//kemudian break
                            case 3:// jika  3
                                sorting(patientHead);//  maka panggil fungsi sorting
                                cout << "Data Pasien Diurutkan Berdasarkan Nama Pasien." << endl;
                                showdata(patientHead);//lalu  tampilkan lagi data pasien
                                StructToCSV(patientHead);//kemudian fungsi  csv terpanggil agar terurut juga data di dalamnya
                                pause();//jeda
                                break;//kemudian break
                            case 4://jika 4
                            {
                                showdata(patientHead);//tampilkan data pasien
                                cout << "Masukkan Nama Yang Akan Dicari: ";//lakukan searching berdasarkan nama
                                cin.ignore();
                                getline(cin, namapasien);//kemudian input
                                Pasien *result = fibonacciSearchnama(patientHead, namapasien);//jika di linkedlist sama  dengan nama di fungsi  pencarian maka  akan  ditemukan
                                if (result)
                                {
                                    system("cls");
                                    cout << "Data Ditemukan! "                                                     << endl;
                                    cout << "--------------------------------------------------------------------" << endl;
                                    cout << "Nomor Berobat : " << result->noberobat                                << endl;
                                    cout << "Nama Pasien   : " << result->namapasien                               << endl;
                                    cout << "Umur          : " << result->umur                                     << endl;
                                    cout << "Status        : " << result->status                                   << endl;
                                    cout << "Keluhan       : " << result->keluhan                                  << endl;
                                    cout << "Tanggal       : " << result->tgl << "/" << result->bln << "/" << result->thn << endl;
                                    cout << "--------------------------------------------------------------------" << endl;
                                    result = result->next;
                                }
                                else//jika tidak maka data tidak  di  temukan
                                {
                                    cout << "Data Tidak Ditemukan." << endl;
                                }
                                pause();//jeda
                                break;//kemudian break
                            }
                            case 5://jika 5
                                showdata(patientHead);//tampilkan  data
                                cout << "Masukkan Nomor Berobat: ";//input nomor
                                if (!(cin >> targetnomorberobat))//error handling jika salah  input
                                {
                                    cout << "Nomor berobat tidak valid. Harap masukkan angka." << endl;
                                    clearInputBuffer();//pemanggilan  fungsi  error handling
                                }
                                else//jika tidak maka  data  terupdate
                                {
                                    cin.ignore();
                                    system("cls");
                                    updatedata(patientHead, targetnomorberobat);//pemanggilan  fungsi update  data pasien
                                    StructToCSV(patientHead);// pemanggilan  fungsi csv agar terupdate juga di dalamnya
                                    pause();//jeda
                                }
                                break;//kemudian  break
                            case 6://jika  6
                                showdata(patientHead);//tampilkan  data  pasien
                                cout << "Masukkan nomor berobat yang ingin dihapus: ";//input nomor
                                if (!(cin >> targetnomorberobat))//error handling  jika  salah input nomor
                                {
                                    cout << "Nomor berobat tidak valid" << endl;
                                    clearInputBuffer();//fungsi  error handling
                                }
                                else//jika  tidak
                                {
                                    deletedata(patientHead, targetnomorberobat); // Hapus data pasien
                                    StructToCSV(patientHead);                    // Simpan perubahan ke file CSV
                                    pause();//jeda
                                }
                                break;//kemudian break

                            case 7://jika  7
                                    system("cls"); //clear screen
                                    panggilantrian();//panggil fungsi antrian untuk masuk
                                    pause();//jeda
                                    break;//kemudian break

                            case 8://keluar
                                break;
                            default://jika  tidak  ada dlam pilihan
                                cout << "Silakan pilih opsi yang valid." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                cout << "Tekan tombol apa pun untuk kembali ke menu..." << endl;
                                cin.get();
                                break;
                            }
                        }
                    } while (patientChoice != 8);//keluar
                }
                else//jika tidak  maka  login gagal
                {
                    cout << "Login Admin gagal, periksa username dan password." << endl;

                    if (adminLoginAttempts == 3)//jika percobaan lenih  dari 3  maka  otomatis keluar program
                    {
                        cout << "--- Anda telah melebihi batas percobaan login ---" << endl;
                        exit(0); // Keluar dari program
                    }
                }
                break;//break
            }

            case 2:
            {
                // Bagian login user
                system("cls"); //clear screen
                loginuser();//tabel tampilan user
                int userChoice;
                cout << "             [1] Login"                                               << endl;
                cout << "             [2] Registrasi"                                          << endl;
                cout << "--------------------------------------------------------------------" << endl;
                cout << "Pilihan: ";

                //kondisi jika inputan tidak valid
                if (!(cin >> userChoice))
                {
                    cout << "Pilihan tidak valid" << endl;
                    clearInputBuffer();
                }
                else //kondisi jika inputan valid maka akan masuk ke login user
                {
                    switch (userChoice)
                    {
                    case 1:
                    {
                        //login user
                        userLoginAttempts++;
                        string username, password; //deklarasi variabel username dan password
                        system("cls");// clear screen
                        loginuser(); //tabel tampilan user
                        cout << "Masukkan Username: ";
                        cin >> username;
                        cout << "Masukkan Password: ";
                        cin >> password;

                        if (users.checkUser(username, password))// memeriksa apakah username dan password yang dimasukkkan sesuai
                        {
                            cout << "Login User Berhasil!" << endl;
                            userLoginAttempts = 0; //mengatur ulang jumlah login menjadi 0

                            // Menampilkan menu antrian klinik
                            int userMenuChoice; //deklarasi variabel bertipe integer
                            do
                            {
                                system("cls"); //clear screen
                                loginuser(); //tabel tampilan user
                                cout << "---------------------- Sistem Antrian Klinik -----------------------" << endl;
                                cout << "        [1] Ambil Nomor Antrian                                      " << endl;
                                cout << "        [2] Cari data pasien                                         " << endl;
                                cout << "        [3] Exit                                                     " << endl;
                                cout << "--------------------------------------------------------------------" << endl;
                                cout << "Pilihan Anda: ";

                                //kondisi jika inputan tidak valid
                                if (!(cin >> userMenuChoice))
                                {
                                    cout << "Pilihan tidak valid" << endl;
                                    clearInputBuffer();
                                }
                                //jika inputan valid
                                else
                                {
                                    switch (userMenuChoice)// pilih menu yang diinginkan
                                    {
                                    case 1:
                                        system("cls"); //clear screen
                                        loginuser();//tabel tampilan user
                                        //perulangan akan terus dijalankan selama inputan benar
                                        while(true){
                                            cout << "Nama          : ";
                                            cin.ignore(); //mengabaikan karakter
                                            getline(cin, namapasien); //membaca namapasien
                                            // jika nama pasien kosong dan berupa angka 
                                            if (!namapasien.empty() && check(namapasien)) {
                                                break;  // keluar dari loop jika input valid
                                            } else { //jika input tidak valid
                                                cout << "Nama Anda tidak valid!" << endl;
                                            }
                                        }
                                        //perulangan akan terus dijalankan selama inputan benar
                                        while(true){
                                            string input; //deklarasi variabel input
                                            cout << "Nomor Berobat : ";
                                            getline(cin, input);// membaca inputan
                                            // jika nomor berobat tidak berupa angka dan kosong
                                            if (input.empty() || !all_of(input.begin(), input.end(), ::isdigit)) {
                                                cout << "Harus berupa angka dan tidak boleh kosong." << endl;
                                            } else { //jika inputan valid
                                                noberobat = stoi(input);  // konversi string ke integer
                                                break;//keluar dari loop
                                            }
                                        }
                                    	system("cls"); // clear screen
                                        tambahAntrian(namapasien,noberobat);// memanggil fungsi untuk menambah antrian dengan namapasien dan nomor berobat
                                        loginuser();// tabel tampilan user
                                        cout << "Nama          : " << namapasien << endl;
                                        cout << "Nomor berobat : " << noberobat << endl;
                                        cout << "--------------------------------------------------------------------" << endl;
                                        
                                        pause();// jeda
                                        break; //break

                                    case 2:
                                    {
                                        showdata(patientHead); //memanggil fungsi show data
                                        cout << "Masukkan Nama: ";
                                        cin.ignore();// mengabaikan karakter
                                        getline(cin, namapasien); //membaca namapasien
                                        //memanggil fungsi searching
                                        Pasien *result = fibonacciSearchnama(patientHead, namapasien);
                                        // jika data ditemukan
                                        if (result)
                                        {
                                            system("cls"); // clear screen
                                            cout << "Data ditemukan!" << endl;
                                            cout << "--------------------------------------------------------------------" << endl;
                                            cout << "Nomor berobat : " << result->noberobat << endl;
                                            cout << "Nama Pasien   : " << result->namapasien << endl;
                                            cout << "Umur          : " << result->umur << endl;
                                            cout << "Status        : " << result->status << endl;
                                            cout << "Keluhan       : " << result->keluhan << endl;
                                            cout << "Tanggal       : " << result->tgl << "/" << setw(2) << setfill('0') << result->bln << "/" << result->thn << endl;
                                            cout << "--------------------------------------------------------------------" << endl;
                                            result = result->next; //mengakses elemen berikutnya
                                        }
                                        // jika data tidak ditemukan
                                        else
                                        {
                                            cout << "Data Tidak Ditemukan." << endl;
                                        }
                                        pause(); //jeda
                                        break;// break
                                    }

                                    case 3:
                                        // Keluar dari menu user
                                        break;
                                    // jika inputan pilihan menu tidak valid
                                    default:
                                        cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                                    }
                                }
                            } while (userMenuChoice != 3);// loop akan berhenti jika inputan tidak valid
                        }
                        // jika username dan password tidak sesuai
                        else
                        {

                            cout << "Login User gagal. Periksa Username dan Password." << endl;

                            if (userLoginAttempts == 3) //kondisi dimana 3x login maka akan keluar progran
                            {
                                cout << "Anda telah melebihi batas percobaan login" << endl;
                                end();
                                exit(0); // Keluar dari program
                            }
                        }
                        break;
                    }
                    //register akun user
                    case 2:
                    {
                        string username, password; // deklarasi variabel username dan password
                        system("cls"); // clear screen
                        loginuser(); // tabel tampilan user
                        cout << "Masukkan Username Baru: ";
                        cin >> username;
                        cout << "Masukkan Password Baru: ";
                        cin >> password;
                        users.insertUser(username, password);// memanggil fungsi insertUser dan menyimpan informasi yang telah diinputkan
                        cout << "Registrasi berhasil!" << endl;
                        break; //break
                    }
                    // jika pilihan menu tidak valid
                    default:
                        cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                    }
                }
                break; //break
            }
            //exit
            case 3:
                // Keluar dari program
                end();
                break;
            //jika inputan tidak valid
            default:
                cout << "Pilihan tidak valid" << endl;
            }
        }
    } while (choice != 3); // loop akan berhenti jika inputan tidak valid

    return 0;// keluar program
}