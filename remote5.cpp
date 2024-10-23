#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

// Struktur untuk menyimpan mata kuliah
struct Matkul {
    string nama;
    int startTime;
    int endTime;
};

// Fungsi untuk menghitung waktu dalam format "hari, jam:menit"
string convertTime(int minutes) {
    int hari = minutes / (24 * 60);
    minutes %= 24 * 60;
    int jam = minutes / 60;
    int menit = minutes % 60;

    string hariStr;
    switch (hari) {
        case 0: hariStr = "Senin"; break;
        case 1: hariStr = "Selasa"; break;
        case 2: hariStr = "Rabu"; break;
        case 3: hariStr = "Kamis"; break;
        case 4: hariStr = "Jumat"; break;
        default: hariStr = "Invalid"; break;
    }

    return hariStr + ", " + to_string(jam) + ":" + (menit < 10 ? "0" : "") + to_string(menit);
}

// Fungsi untuk mencari bentrok jadwal
void cekBentrok(vector<Matkul> &jadwal) {
    bool adaBentrok = false;
    for (size_t i = 0; i < jadwal.size(); i++) {
        for (size_t j = i + 1; j < jadwal.size(); j++) {
            if ((jadwal[i].startTime < jadwal[j].endTime && jadwal[i].endTime > jadwal[j].startTime) ||
                (jadwal[j].startTime < jadwal[i].endTime && jadwal[j].endTime > jadwal[i].startTime)) {
                cout << "Bentrok: " << jadwal[i].nama << " dan " << jadwal[j].nama << endl;
                adaBentrok = true;
            }
        }
    }
    if (!adaBentrok) {
        cout << "Tidak ada mata kuliah yang bentrok." << endl;
    }
}

// Fungsi untuk menampilkan daftar mata kuliah
void lihatDaftarMatkul(vector<Matkul> &daftar) {
    sort(daftar.begin(), daftar.end(), [](Matkul &a, Matkul &b) {
        return a.startTime < b.startTime;
    });

    cout << "Daftar Mata Kuliah Tersedia:" << endl;
    for (auto &mk : daftar) {
        cout << mk.nama << " - " << convertTime(mk.startTime) << " s/d " << convertTime(mk.endTime) << endl;
    }
}

// Fungsi untuk menambahkan mata kuliah
void tambahMatkul(vector<Matkul> &jadwal, vector<Matkul> &daftar) {
    string nama;
    cout << "Masukkan nama mata kuliah yang ingin ditambahkan: ";
    cin.ignore();
    getline(cin, nama);

    bool ditemukan = false;
    for (auto &mk : daftar) {
        if (mk.nama == nama) {
            jadwal.push_back(mk);
            cout << "Mata kuliah " << mk.nama << " berhasil ditambahkan." << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Matkul tidak ditemukan." << endl;
    }
}

// Fungsi untuk menghapus mata kuliah
void dropMatkul(vector<Matkul> &jadwal) {
    string nama;
    cout << "Masukkan nama mata kuliah yang ingin dihapus: ";
    cin.ignore();
    getline(cin, nama);

    bool ditemukan = false;
    for (size_t i = 0; i < jadwal.size(); i++) {
        if (jadwal[i].nama == nama) {
            jadwal.erase(jadwal.begin() + i);
            cout << "Mata kuliah " << nama << " berhasil dihapus." << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Matkul tidak ditemukan." << endl;
    }
}

// Fungsi untuk menampilkan jadwal yang diambil
void cekRingkasan(vector<Matkul> &jadwal) {
    if (jadwal.empty()) {
        cout << "Anda belum mengambil mata kuliah apapun." << endl;
    } else {
        cout << "Jadwal Mata Kuliah Anda:" << endl;
        for (auto &mk : jadwal) {
            cout << mk.nama << " - " << convertTime(mk.startTime) << " s/d " << convertTime(mk.endTime) << endl;
        }
        cekBentrok(jadwal);
    }
}

int main() {
    // Daftar mata kuliah yang tersedia
    vector<Matkul> daftarMatkul = {
        {"Struktur Data", 3451, 3577}, // Rabu 09:31 - 11:37
        {"Algoritma", 1500, 1700},     // Senin 09:00 - 11:20
        {"Jaringan Komputer", 5000, 5180}  // Jumat 09:00 - 11:00
    };

    // Jadwal mata kuliah yang diambil
    vector<Matkul> jadwal;

    int pilihan;
    do {
        // Tampilkan menu
        cout << "\nMenu:" << endl;
        cout << "1. Tambah Matkul" << endl;
        cout << "2. Drop Matkul" << endl;
        cout << "3. Cek Ringkasan" << endl;
        cout << "4. Lihat Daftar Matkul" << endl;
        cout << "5. Selesai" << endl;
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahMatkul(jadwal, daftarMatkul);
                break;
            case 2:
                dropMatkul(jadwal);
                break;
            case 3:
                cekRingkasan(jadwal);
                break;
            case 4:
                lihatDaftarMatkul(daftarMatkul);
                break;
            case 5:
                cout << "Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 5);

    return 0;
}

