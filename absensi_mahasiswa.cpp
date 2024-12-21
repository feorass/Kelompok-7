#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Mahasiswa {
public:
    char nama[50];
    char kehadiran[10]; // Array untuk menyimpan kehadiran
    char nim[12]; // Menggunakan char untuk menyimpan NIM
    float persen; // Persentase kehadiran

    // Konstruktor untuk menginisialisasi anggota data
    Mahasiswa() : persen(100) {} // Inisialisasi persen ke 100
};

Mahasiswa mhs[100]; // Array untuk menyimpan data mahasiswa
int jumlahMahasiswa = 0;

// Fungsi untuk memasukkan data mahasiswa
void dataMasuk() {
    cout << "Input Data Mahasiswa Ke-" << (jumlahMahasiswa + 1) << endl;
    
    // Input NIM dengan format H1A024XXX
    cout << "NIM (format H1A024XXX): ";
    cin >> mhs[jumlahMahasiswa].nim;
    
    cout << "Nama: "; 
    cin >> ws; // Mengabaikan whitespace sebelum input nama
    cin.getline(mhs[jumlahMahasiswa].nama, 50); // Menggunakan getline untuk nama
    
    jumlahMahasiswa++;
}

// Fungsi untuk melakukan presensi mahasiswa
void dataPresensi(int minggu) {
    if (jumlahMahasiswa == 0) {
        cout << "Belum ada data mahasiswa! Silakan masukkan data terlebih dahulu." << endl;
        return;
    }

    for (int i = 0; i < jumlahMahasiswa; i++) {
        // Menampilkan informasi mahasiswa
        cout << mhs[i].nim << "\t" << mhs[i].nama << "\t";
        cout << "Kehadiran [H/A/I/S]: "; 
        cin >> mhs[i].kehadiran[minggu];

        // Validasi input kehadiran
        while (mhs[i].kehadiran[minggu] != 'H' &&
               mhs[i].kehadiran[minggu] != 'A' &&
               mhs[i].kehadiran[minggu] != 'I' &&
               mhs[i].kehadiran[minggu] != 'S') {
            cout << "Input tidak valid! Masukkan [H/A/I/S]: ";
            cin >> mhs[i].kehadiran[minggu];
        }

        // Menghitung persentase berdasarkan jenis kehadiran
        if (mhs[i].kehadiran[minggu] == 'H') {
            // Kehadiran penuh, tetap 100%
            mhs[i].persen = 100;
        } else if (mhs[i].kehadiran[minggu] == 'A') {
            // Alfa, kurangi 30%
            mhs[i].persen -= 30;
            if (mhs[i].persen < 0) mhs[i].persen = 0; // Pastikan tidak negatif
        } else if (mhs[i].kehadiran[minggu] == 'I' || mhs[i].kehadiran[minggu] == 'S') {
            // Sakit atau Izin, kurangi 15%
            mhs[i].persen -= 15;
            if (mhs[i].persen < 0) mhs[i].persen = 0; // Pastikan tidak negatif
        }
    }
}

// Fungsi untuk merekap data kehadiran dan menyimpannya dalam file CSV
void rekapData() {
    if (jumlahMahasiswa == 0) {
        cout << "Belum ada data mahasiswa!" << endl;
        return;
    }

    ofstream csvFile("absensiswa.csv");
    
    csvFile << "NIM,Nama,Persentase Kehadiran\n"; // Header CSV

    for (int i = 0; i < jumlahMahasiswa; i++) {
        csvFile << mhs[i].nim << "," << mhs[i].nama << "," << mhs[i].persen << "%\n"; // Tambahkan persentase ke CSV
    }

    csvFile.close();
    
    cout << "Data telah disimpan ke absensiswa.csv" << endl;
}

int main() {
    int pilihan, minggu = 0;
    
    do {
        cout << "Pilih Opsi:\n1. Masukkan Data Mahasiswa\n2. Presensi Mahasiswa\n3. Rekap Data\n4. Keluar\nPilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                dataMasuk();
                break;
            case 2:
                if (minggu < 10) { // Maksimal 10 minggu presensi
                    dataPresensi(minggu);
                    minggu++;
                } else {
                    cout << "Presensi sudah penuh untuk 10 minggu." << endl;
                }
                break;
            case 3:
                rekapData();
                break;
            case 4:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan salah." << endl;
        }
        
    } while (pilihan != 4);

    return 0;
}
