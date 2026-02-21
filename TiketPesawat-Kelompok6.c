/*
KELOMPOK 6
Pembelian Tiket Pesawat
Anggota 1 : Arya Rayi Ananta
Anggota 2 : Azmi Muhammad Rizki
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int max_tiket = 30;

struct tiketPesawat {
    int kodeTiket;
    char nama[20];
    int harga;
    char destinasi[20];
    char jenisPesawat[10];
    int kursi;
    struct tm tanggal;
    char jadwalPenerbangan[10];
};

/*Catatan: Setiap penerbangan memiliki kursi yang sama Reguler 20 Kursi dan VIP 10 kursi*/
int kursiBaliReguler[20] = {0}; //Destinasi Bali Jenis Reguler 20 Kursi
int kursiBaliVIP[10] = {0}; //Destinasi Bali Jenis VIP 10 kursi
int kursiBantenReguler[20] = {0}; //Destinasi Banten Jenis Reguler 20 Kursi
int kursiBantenVIP[10] = {0}; //Destinasi Banten Jenis VIP 10 Kursi

int kursiBaliRegulerPagi[20] = {0}; //Bali-Reguler-Pagi (8.00)
int kursiBaliRegulerSore[20] = {0}; //Bali-Reguler-Sore (16.00)
int kursiBaliVIPPagi[10] = {0}; //Bali-VIP-Pagi (8.00)
int kursiBaliVIPSore[10] = {0}; //Bali VIP-Sore (16.00)

int kursiBantenRegulerPagi[20] = {0}; //Banten-Reguler-Pagi (10.00)
int kursiBantenRegulerMalam[20] = {0}; //Banten-Reguler-Malam (19.00)
int kursiBantenVIPPagi[10] = {0}; //Banten-VIP-Pagi (10.00)
int kursiBantenVIPMalam[10] = {0}; //Banten-VIP-Malam (19.00)


struct tiketPesawat tiket[30]; //Total Tiket 30
int jumlahTiket = 0;
int kodeTiketBerikut = 0; // Inisialisasi kode tiket berikutnya

void TampilanHarga(){
    printf("\n========================================================\n");
    printf("           LIST HARGA TIKET PESAWAT LION AIR                  \n");
    printf("========================================================\n");
    printf(" DESTINASI             |     REGULER     |      VIP     \n");
    printf("--------------------------------------------------------\n");
    printf(" Bandung - Bali        | Rp.1.500.000    | Rp.2.000.000 \n");
    printf(" Bandung - Banten      | Rp.500.000      | Rp.1.000.000 \n");
    printf("========================================================\n");
}


void display() {
    system("cls");
    if (jumlahTiket == 0) { //Jika tidak ada data/Belum ada pemesanan
        printf("Belum ada data tiket yang dipesan . . . \n");
        return;
    }

    int pilihDestinasi, pilihJenis, pilihJam;

    // Menanyakan destinasi yang akan di display
    do {
        printf("Pilih Destinasi Penerbangan yang ingin ditampilkan: \n");
        printf("[1] Bali\n");
        printf("[2] Banten\n");
        printf("Masukkan pilihan (1/2): ");
        scanf("%d", &pilihDestinasi);

        if (pilihDestinasi != 1 && pilihDestinasi != 2) {
            printf("Pilihan tidak valid. Silakan coba lagi...\n");
        }
    } while (pilihDestinasi != 1 && pilihDestinasi != 2);

    // Menanyakan jenis pesawat yang akan di display
    do {
        printf("Pilih Jenis Pesawat yang ingin ditampilkan: \n");
        printf("[1] Reguler\n");
        printf("[2] VIP\n");
        printf("Masukkan pilihan (1/2): ");
        scanf("%d", &pilihJenis);

        if (pilihJenis != 1 && pilihJenis != 2) {
            printf("Pilihan tidak valid. Silakan coba lagi...\n");
        }
    } while (pilihJenis != 1 && pilihJenis != 2);

    // Menanyakan jadwal penerbangan yang akan di display
    do {
        printf("Pilih Jadwal Penerbangan yang ingin ditampilkan: \n");
        if (pilihDestinasi == 1) { // Memunculkan Jam Penerbangan Bali
            printf("[1] 08:00\n");
            printf("[2] 16:00\n");
        } else { // Memunculkan Jam Penerbangan Banten
            printf("[1] 10:00\n");
            printf("[2] 19:00\n");
        }
        printf("Masukkan pilihan (1/2): ");
        scanf("%d", &pilihJam);

        if (pilihJam != 1 && pilihJam != 2) {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihJam != 1 && pilihJam != 2);

    // Mengurutkan data tiket berdasarkan nomor kursi
    // Pengurutan menggunakan buble short
    for (int i = 0; i < jumlahTiket - 1; i++) {
        for (int j = i + 1; j < jumlahTiket; j++) {
            if (tiket[i].kursi > tiket[j].kursi) {
                struct tiketPesawat temp = tiket[i];
                tiket[i] = tiket[j];
                tiket[j] = temp;
            }
        }
    }

    system("cls");

    int ketemu = 0; // Untuk mengecek apakah ada data sesuai 
    printf("\n========================================================\n");
    printf("             Data Tiket Pesawat Lion Air \n");
    printf("===========================================================\n");

    char jadwalFilter[10];
    if (pilihDestinasi == 1) { // Jika memilih Destinasi Bali maka akan mengcompare sesuai pilihan jam penerbangan
        if (pilihJam == 1) {
            strcpy(jadwalFilter, "08:00");
        } else {
            strcpy(jadwalFilter, "16:00");
        }
    } else { // Jika memilih Destinasi Banten maka akan mengcompare sesuai pilihan jam penerbangan
        if (pilihJam == 1) {
            strcpy(jadwalFilter, "10:00");
        } else {
            strcpy(jadwalFilter, "19:00");
        }
    }

    //Pengecekan destinasi, jenis, dan jam penerbangan sesuai dengan pilihan
    for (int i = 0; i < jumlahTiket; i++) {
        if (((pilihDestinasi == 1 && strcmp(tiket[i].destinasi, "Bali") == 0) || (pilihDestinasi == 2 && strcmp(tiket[i].destinasi, "Banten") == 0)) &&
            ((pilihJenis == 1 && strcmp(tiket[i].jenisPesawat, "Reguler") == 0) || (pilihJenis == 2 && strcmp(tiket[i].jenisPesawat, "VIP") == 0)) &&
            strcmp(tiket[i].jadwalPenerbangan, jadwalFilter) == 0) {

            ketemu = 1; // Data dite=mukan
            printf("=========================================================\n");
            printf("| %-15s: LIONAIR%-30d|\n", "Nomor Pemesanan", tiket[i].kodeTiket);
            printf("| %-15s: %-30s       |\n", "Nama", tiket[i].nama);
            printf("| %-15s: %-30s       |\n", "Jenis Pesawat", tiket[i].jenisPesawat);
            printf("| %-15s: %-30s       |\n", "Destinasi", tiket[i].destinasi);
            printf("| %-15s: %-30d       |\n", "Nomor Kursi", tiket[i].kursi);
            printf("| %-15s: Rp%-30d     |\n", "Harga", tiket[i].harga);
            printf("| %-15s: %-30s       |\n", "Jadwal", tiket[i].jadwalPenerbangan);
            char buffer[20]; //Pencetakan tanggal pemesanan
            strftime(buffer, 20, "%d-%m-%Y %H:%M", &tiket[i].tanggal);
            printf("| %-15s: %-30s       |\n", "Tanggal Beli", buffer);
            printf("=========================================================\n");
        }
    }

    //Jika tidak ada data yang sesuai kriteria pencarian maka akan mengulang
    if (!ketemu) {
        printf("\nTidak ada data yang sesuai dengan kriteria pencarian.\n");
        printf("Detail Pencarian:\n");
        if (pilihDestinasi == 1) {
            printf("  Destinasi     : Bali\n");
        } else {
            printf("  Destinasi     : Banten\n");
        }
        if (pilihJenis == 1) {
            printf("  Jenis Pesawat : Reguler\n");
        } else {
            printf("  Jenis Pesawat : VIP\n");
        }
        printf("  Jadwal        : %s\n", jadwalFilter);
    }

}


void tampilkanKursiTersedia(int *kursi, int jumlahKursi) {
    printf("Kursi Tersedia: ");
    for (int i = 0; i < jumlahKursi; i++) {
        if (kursi[i] == 0) { // Menampilkan Kursi kosong karena tidak ada yang menempati
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}


void pemesananTiket() {
    system("cls");
    
    int n;
    printf("\nMasukkan banyaknya tiket yang ingin dipesan: ");
    scanf("%d", &n);

    if (jumlahTiket + n > max_tiket) { //Jika pemesanan tiket melebihi dari jumlah tiket (30) maka kapasitas tidak cukup
        printf("Maaf, tidak cukup kapasitas untuk menambahkan %d tiket.\n", n);
        return; //Kembalikan
    }

    for (int i = 0; i < n; i++) {
        TampilanHarga();
        printf("\n=========================================================\n");
        printf("     Anda memesan dengan pemesanan tiket ke #%d\n", jumlahTiket + 1);
        printf("=========================================================\n");
        tiket[jumlahTiket].kodeTiket = kodeTiketBerikut + 1; //Untuk mencetak Kode Tiket 
        printf("Masukkan Nama: ");
        scanf(" %[^\n]", tiket[jumlahTiket].nama);

        int pilihDestinasi, pilihJenis, pilihJadwal, kursiTerpilih;
        int *kursiArray = NULL; //Kursi dimulai dari 0
        int jumlahKursi = 0; //Jumlah kursi akan di set dari 0

        // Pilih Destinasi
        do {
            printf("Pilih Destinasi Penerbangan yang ingin dituju: \n");
            printf("[1] Bandung - Bali\n");
            printf("[2] Bandung - Banten\n");
            printf("Masukkan pilihan (1/2): ");
            scanf("%d", &pilihDestinasi);

            if (pilihDestinasi == 1) { 
                strcpy(tiket[jumlahTiket].destinasi, "Bali"); //Memilih Bali
            } else if (pilihDestinasi == 2) {
                strcpy(tiket[jumlahTiket].destinasi, "Banten"); //Memilih Banten
            } else {
                printf("Pilihan anda tidak valid.\n");
            }
        } while (pilihDestinasi != 1 && pilihDestinasi != 2);

        // Pilih Jenis Pesawat
        do {
            printf("Pilih Jenis Pesawat yang akan dipesan: \n");
            printf("[1] Reguler\n");
            printf("[2] VIP\n");
            printf("Masukkan pilihan (1/2): ");
            scanf("%d", &pilihJenis);

            if (pilihJenis == 1) {
                strcpy(tiket[jumlahTiket].jenisPesawat, "Reguler"); //Memilih Reguler
            } else if (pilihJenis == 2) {
                strcpy(tiket[jumlahTiket].jenisPesawat, "VIP"); //Memilih VIP
            } else {
                printf("Pilihan anda tidak valid.\n");
            }
        } while (pilihJenis != 1 && pilihJenis != 2);

        // Pilih Jadwal Penerbangan
        do {
            printf("Pilih Jadwal Penerbangan yang diinginkan: \n");
            if (pilihDestinasi == 1) { // Jika memilih Bali
                printf("[1] 08:00\n");
                printf("[2] 16:00\n");
            } else { // Jika memilih Banten
                printf("[1] 10:00\n");
                printf("[2] 19:00\n");
            }
            printf("Masukkan pilihan (1/2): ");
            scanf("%d", &pilihJadwal);

            if (pilihDestinasi == 1) { // Memilih Bali
                if (pilihJadwal == 1) {
                    strcpy(tiket[jumlahTiket].jadwalPenerbangan, "08:00"); //Jam Pagi (8.00)
                    if (pilihJenis == 1) {
                        kursiArray = kursiBaliRegulerPagi;
                        jumlahKursi = 20;
                    } else {
                        kursiArray = kursiBaliVIPPagi;
                        jumlahKursi = 10;
                    }
                } else if (pilihJadwal == 2) {
                    strcpy(tiket[jumlahTiket].jadwalPenerbangan, "16:00"); //Jam Sore (16.00)
                    if (pilihJenis == 1) {
                        kursiArray = kursiBaliRegulerSore;
                        jumlahKursi = 20;
                    } else {
                        kursiArray = kursiBaliVIPSore;
                        jumlahKursi = 10;
                    }
                }
            } else { // Memilih Banten
                if (pilihJadwal == 1) {
                    strcpy(tiket[jumlahTiket].jadwalPenerbangan, "10:00"); //Jam Pagi (10.00)
                    if (pilihJenis == 1) {
                        kursiArray = kursiBantenRegulerPagi;
                        jumlahKursi = 20;
                    } else {
                        kursiArray = kursiBantenVIPPagi;
                        jumlahKursi = 10;
                    }
                } else if (pilihJadwal == 2) {
                    strcpy(tiket[jumlahTiket].jadwalPenerbangan, "19:00"); //Jam Malam (19.00)
                    if (pilihJenis == 1) {
                        kursiArray = kursiBantenRegulerMalam;
                        jumlahKursi = 20;
                    } else {
                        kursiArray = kursiBantenVIPMalam;
                        jumlahKursi = 10;
                    }
                }
            }
            if (!kursiArray) {
                printf("Pilihan anda tidak valid.\n");
            }
        } while (!kursiArray); 

        // Mendapatkan tanggal pemesanan
        time_t now = time(NULL);
        tiket[jumlahTiket].tanggal = *localtime(&now);  // Menyimpan tanggal saat ini ke dalam tiket

        // Tampilkan Kursi Tersedia dan Pilih Kursi
        system("cls");
        int kursiValid = 0;
        while (!kursiValid) {
            printf("Daftar kursi tersedia untuk %s - %s (%s):\n", tiket[jumlahTiket].destinasi, tiket[jumlahTiket].jenisPesawat, tiket[jumlahTiket].jadwalPenerbangan);
            tampilkanKursiTersedia(kursiArray, jumlahKursi);

            printf("Masukkan nomor kursi yang ingin dipesan: ");
            scanf("%d", &kursiTerpilih);

            if (kursiTerpilih < 1 || kursiTerpilih > jumlahKursi) {
                printf("Nomor kursi tidak valid, pilih kembali.\n");
            } else if (kursiArray[kursiTerpilih - 1] == 1) {
                printf("Kursi sudah dipesan, pilih kursi lain.\n");
            } else {
                kursiArray[kursiTerpilih - 1] = 1; // Tandai kursi sebagai terisi
                tiket[jumlahTiket].kursi = kursiTerpilih;
                kursiValid = 1;
            }
        }

        // Menentukan Harga Berdasarkan Destinasi dan Jenis Pesawat yang dipilih
        if (strcmp(tiket[jumlahTiket].destinasi, "Bali") == 0) {
            if (strcmp(tiket[jumlahTiket].jenisPesawat, "Reguler") == 0) {
                tiket[jumlahTiket].harga = 1500000;
            } else {
                tiket[jumlahTiket].harga = 2000000;
            }
        } else {
            if (strcmp(tiket[jumlahTiket].jenisPesawat, "Reguler") == 0) {
                tiket[jumlahTiket].harga = 500000;
            } else {
                tiket[jumlahTiket].harga = 1000000;
            }
        }

        jumlahTiket++;
        kodeTiketBerikut++; // Menambah kode tiket berikutnya
        system("cls");
    }
    printf("\n========================================================\n");
    printf("                  Tiket berhasil dipesan.\n");
    printf("\n========================================================\n");
    printf("  Silahkan cek pemesanan tiket pesawat pada menu NO.1\n");
    printf("          Terimakasih dan happy travelling :)\n");
}


void editPemesanan() {
    system("cls");
    if (jumlahTiket == 0) {
        printf("Belum ada data tiket yang bisa diedit . . . \n");
        return;
    }

    int kodeTiketInput, pilihDestinasi, pilihJenis, kursiTerpilih;
    int *kursiArray = NULL;
    int jumlahKursi = 0;

    // Masukkan kode tiket untuk mengedit pemesanan
    printf("Masukkan kode tiket untuk mengubah pemesanan: LIONAIR");
    scanf("%d", &kodeTiketInput);

    // Cari tiket berdasarkan kodeTiket
    int index = -1;
    for (int i = 0; i < jumlahTiket; i++) {
        if (tiket[i].kodeTiket == kodeTiketInput) {
            index = i;  //Jika data sudah ketemu melalui serching maka index = i
            break;
        }
    }

    if (index == -1) {
        printf("Kode tiket tidak ditemukan.\n");
        return;
    }
    
    //Mengosongkan Kursi
    if (strcmp(tiket[index].jadwalPenerbangan, "08:00") == 0 || strcmp(tiket[index].jadwalPenerbangan, "10:00") == 0) {
        if (strcmp(tiket[index].jenisPesawat, "Reguler") == 0) {
            kursiArray = kursiBaliRegulerPagi;
        } else {
            kursiArray = kursiBantenRegulerPagi;
        }
    } else if (strcmp(tiket[index].jadwalPenerbangan, "16:00") == 0 || strcmp(tiket[index].jadwalPenerbangan, "19:00") == 0) {
        if (strcmp(tiket[index].jenisPesawat, "Reguler") == 0) {
            kursiArray = kursiBaliRegulerSore;
        } else {
            kursiArray = kursiBantenVIPMalam;
        }
    }

    if (kursiArray) {
        kursiArray[tiket[index].kursi - 1] = 0; // Kosongkan kursi
    }

    // Tampilkan detail tiket sebelum mengubah pemesanan tiket
    printf("=========================================================\n");
    printf("| %-15s: LIONAIR%-30d|\n", "Kode Tiket", tiket[index].kodeTiket);
    printf("| %-15s: %-30s       |\n", "Nama", tiket[index].nama);
    printf("| %-15s: %-30s       |\n", "Jenis Pesawat", tiket[index].jenisPesawat);
    printf("| %-15s: %-30s       |\n", "Destinasi", tiket[index].destinasi);
    printf("| %-15s: %-30d       |\n", "Nomor Kursi", tiket[index].kursi);
    printf("| %-15s: Rp%-30d     |\n", "Harga", tiket[index].harga);
    printf("| %-15s: %-30s       |\n", "Jadwal", tiket[index].jadwalPenerbangan);
    printf("=========================================================\n");

    // Membatalkan kursi lama agar dapat diisi kembali
    if (strcmp(tiket[index].jenisPesawat, "Reguler") == 0) {
        if (strcmp(tiket[index].destinasi, "Bali") == 0) {
            kursiBaliReguler[tiket[index].kursi - 1] = 0; // Kosongkan kursi
        } else {
            kursiBantenReguler[tiket[index].kursi - 1] = 0; // Kosongkan kursi
        }
    } else if (strcmp(tiket[index].jenisPesawat, "VIP") == 0) {
        if (strcmp(tiket[index].destinasi, "Bali") == 0) {
            kursiBaliVIP[tiket[index].kursi - 1] = 0; // Kosongkan kursi
        } else {
            kursiBantenVIP[tiket[index].kursi - 1] = 0; // Kosongkan kursi
        }
    }

    // Pilih destinasi baru
    do {
        printf("\nPilih Destinasi Penerbangan:\n");
        printf("[1] Bandung - Bali\n");
        printf("[2] Bandung - Banten\n");
        printf("Masukkan pilihan (1/2): ");
        scanf("%d", &pilihDestinasi);

        if (pilihDestinasi == 1) {
            strcpy(tiket[index].destinasi, "Bali"); //Memilih Bali
        } else if (pilihDestinasi == 2) {
            strcpy(tiket[index].destinasi, "Banten"); //Memilih Banten
        } else {
            printf("Pilihan Anda tidak valid.\n");
        }
    } while (pilihDestinasi != 1 && pilihDestinasi != 2);

    // Pilih jenis pesawat baru
    do {
        printf("Pilih Jenis Pesawat:\n");
        printf("[1] Reguler\n");
        printf("[2] VIP\n");
        printf("Masukkan pilihan (1/2): ");
        scanf("%d", &pilihJenis);

        if (pilihJenis == 1) {
            strcpy(tiket[index].jenisPesawat, "Reguler"); //Memilih Reguler
            if (pilihDestinasi == 1) {  //Bali
                kursiArray = kursiBaliReguler; 
                jumlahKursi = 20;
            } else { //Banten
                kursiArray = kursiBantenReguler;
                jumlahKursi = 20;
            }
        } else if (pilihJenis == 2) {
            strcpy(tiket[index].jenisPesawat, "VIP"); //Memilih VIP
            if (pilihDestinasi == 1) { // Bali
                kursiArray = kursiBaliVIP;
                jumlahKursi = 10;
            } else { // Banten
                kursiArray = kursiBantenVIP;
                jumlahKursi = 10;
            }
        } else {
            printf("Pilihan Anda tidak valid.\n");
        }
    } while (pilihJenis != 1 && pilihJenis != 2);

    // Pilih jadwal penerbangan baru
    char jadwalBaru[30];
    int pilihJadwal;
    do {
            printf("Pilih Jadwal Penerbangan yang diinginkan: \n");
            if (pilihDestinasi == 1) { // Jika memilih Bali
                printf("[1] 08:00\n");
                printf("[2] 16:00\n");
            } else { // Jika memilih Banten
                printf("[1] 10:00\n");
                printf("[2] 19:00\n");
            }
            printf("Masukkan pilihan (1/2): ");
            scanf("%d", &pilihJadwal);

            if (pilihDestinasi == 1) { // Memilih Bali
                if (pilihJadwal == 1) {
                    strcpy(jadwalBaru, "08:00"); //Jam Pagi (8.00)
                    if (pilihJenis == 1) {
                        kursiArray = kursiBaliRegulerPagi;
                        jumlahKursi = 20;
                    } else {
                        kursiArray = kursiBaliVIPPagi;
                        jumlahKursi = 10;
                    }
                } else if (pilihJadwal == 2) {
                    strcpy(jadwalBaru, "16:00"); //Jam Sore (16.00)
                    if (pilihJenis == 1) {
                        kursiArray = kursiBaliRegulerSore;
                        jumlahKursi = 20;
                    } else {
                        kursiArray = kursiBaliVIPSore;
                        jumlahKursi = 10;
                    }
                }
            } else { // Memilih Banten
                if (pilihJadwal == 1) {
                    strcpy(jadwalBaru, "10:00"); //Jam Pagi (10.00)
                    if (pilihJenis == 1) {
                        kursiArray = kursiBantenRegulerPagi;
                        jumlahKursi = 20;
                    } else {
                        kursiArray = kursiBantenVIPPagi;
                        jumlahKursi = 10;
                    }
                } else if (pilihJadwal == 2) {
                    strcpy(jadwalBaru, "19:00"); //Jam Malam (19.00)
                    if (pilihJenis == 1) {
                        kursiArray = kursiBantenRegulerMalam;
                        jumlahKursi = 20;
                    } else {
                        kursiArray = kursiBantenVIPMalam;
                        jumlahKursi = 10;
                    }
                }
            }
            if (!kursiArray) {
                printf("Pilihan anda tidak valid.\n");
            }
        } while (!kursiArray);

    strcpy(tiket[index].jadwalPenerbangan, jadwalBaru); // Update jadwal baru

    system("cls");

    // Tampilkan kursi yang tersedia dan pilih kursi
    int kursiValid = 0;
    while (!kursiValid) {
        printf("\nDaftar kursi tersedia untuk %s - %s:\n", tiket[index].destinasi, tiket[index].jenisPesawat);
        tampilkanKursiTersedia(kursiArray, jumlahKursi);

        printf("Masukkan nomor kursi yang ingin dipesan: ");
        scanf("%d", &kursiTerpilih);

        if (kursiTerpilih < 1 || kursiTerpilih > jumlahKursi) {
            printf("Nomor kursi tidak valid, pilih kembali.\n");
        } else if (kursiArray[kursiTerpilih - 1] == 1) {
            printf("Kursi sudah dipesan, pilih kursi lain.\n");
        } else {
            kursiArray[kursiTerpilih - 1] = 1; // Tandai kursi sebagai terisi
            tiket[index].kursi = kursiTerpilih;
            kursiValid = 1;
        }
    }

    // Update harga tiket berdasarkan pilihan
    if (strcmp(tiket[index].destinasi, "Bali") == 0) {
            if (strcmp(tiket[index].jenisPesawat, "Reguler") == 0) {
                tiket[index].harga = 1500000;
            } else {
                tiket[index].harga = 2000000;
            }
        } else {
            if (strcmp(tiket[index].jenisPesawat, "Reguler") == 0) {
                tiket[index].harga = 500000;
            } else {
                tiket[index].harga = 1000000;
            }
        }

    printf("\n========================================================\n");
    printf("                  Tiket berhasil diperbarui.\n");
    printf("\n========================================================\n");
    printf("  Silahkan cek perubahan tiket pesawat pada menu NO.1\n");
    printf("          Terimakasih dan happy travelling :)\n");
}


void pencarianTiket() {
    system("cls");
    if (jumlahTiket == 0) {
        printf("Belum ada data tiket yang bisa diedit . . . \n");
        return;
    }
    
    int kodeTiketInput;

    // Masukkan kode tiket untuk dicari
    printf("Masukkan kode tiket yang ingin diedit: LIONAIR");
    scanf("%d", &kodeTiketInput);

    // Cari tiket berdasarkan kodeTiket
    int index = -1;
    for (int i = 0; i < jumlahTiket; i++) {
        if (tiket[i].kodeTiket == kodeTiketInput) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Kode tiket tidak ditemukan...\n");
        return;
    }

    // Tampilkan detail tiket sesuai kodeTiket
    printf("=========================================================\n");
    printf("| %-15s: LIONAIR%-30d|\n", "Kode Tiket", tiket[index].kodeTiket);
    printf("| %-15s: %-30s       |\n", "Nama", tiket[index].nama);
    printf("| %-15s: %-30s       |\n", "Jenis Pesawat", tiket[index].jenisPesawat);
    printf("| %-15s: %-30s       |\n", "Destinasi", tiket[index].destinasi);
    printf("| %-15s: %-30d       |\n", "Nomor Kursi", tiket[index].kursi);
    printf("| %-15s: Rp%-30d     |\n", "Harga", tiket[index].harga);
    printf("| %-15s: %-30s       |\n", "Jadwal", tiket[index].jadwalPenerbangan);
    char buffer[20]; //Pencetakan tanggal pemesanan
    strftime(buffer, 20, "%d-%m-%Y %H:%M", &tiket[index].tanggal);
    printf("| %-15s: %-30s       |\n", "Tanggal Beli", buffer);
    printf("=========================================================\n");
}


void pembatalanTiket() {
    system("cls");
    if (jumlahTiket == 0) {
        printf("Tidak ada tiket yang dapat dihapus...\n");
        return;
    }

    int kodeTiketInput;
    printf("Masukkan kode tiket yang ingin dibatalkan: LIONAIR");
    scanf("%d", &kodeTiketInput);

    // Cari tiket berdasarkan kodeTiket
    int index = -1;
    for (int i = 0; i < jumlahTiket; i++) {
        if (tiket[i].kodeTiket == kodeTiketInput) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Kode Tiket Pesawat tidak ditemukan.\n");
        return;
    }

    // Kosongkan kursi yang telah dipesan
    int *kursiArray = NULL;
    if (strcmp(tiket[index].jadwalPenerbangan, "08:00") == 0 || strcmp(tiket[index].jadwalPenerbangan, "10:00") == 0) {
        if (strcmp(tiket[index].jenisPesawat, "Reguler") == 0) {
            kursiArray = kursiBaliRegulerPagi;
        } else {
            kursiArray = kursiBantenRegulerPagi;
        }
    } else if (strcmp(tiket[index].jadwalPenerbangan, "16:00") == 0 || strcmp(tiket[index].jadwalPenerbangan, "19:00") == 0) {
        if (strcmp(tiket[index].jenisPesawat, "Reguler") == 0) {
            kursiArray = kursiBaliRegulerSore;
        } else {
            kursiArray = kursiBantenVIPMalam;
        }
    }

    if (kursiArray) {
        kursiArray[tiket[index].kursi - 1] = 0; // Kosongkan kursi
    }

    // Geser semua tiket setelahnya untuk menghapus tiket
    for (int i = index; i < jumlahTiket - 1; i++) {
        tiket[i] = tiket[i + 1];
    }

    // Kurangi jumlah tiket
    jumlahTiket--;

    // Memberikan konfirmasi penghapusan

    printf("\n========================================================\n");
    printf("     Tiket dengan kode LIONAIR%d berhasil dibatalkan.\n", kodeTiketInput);
    printf("\n========================================================\n");
    printf("           Terimakasih dan happy travelling :)\n");
}


void menu() {
    int pilih;
    do {
        system("cls");
        // Menampilkan Menu Pemilihan
        printf("\n========================================================\n");
        printf("|              Pemesanan Tiket Pesawat                 |\n"); 
        printf("|           Lion Air 34567  | Lion Air 89101           |");
        printf("\n========================================================\n");
        printf("|              Dengan tujuan Penerbangan:              |\n"); 
        printf("|                   Bandung - Bali                     |\n");                
        printf("|                   Bandung - Banten                   |");
        printf("\n========================================================\n");
        printf("       [1] Display Data Pemesanan Tiket Pesawat\n");
        printf("       [2] Pemesanan Tiket Pesawat\n");
        printf("       [3] Mengubah Tiket Pemesanan Pesawat\n");
        printf("       [4] Pencarian Tiket Pemesanan Pesawat\n");
        printf("       [5] Pembatalan Tiket Pemesanan Pesawat\n");
        printf("       [0] Keluar\n");
        printf("       Masukkan pilihan Anda: ");

        scanf("%d", &pilih);

        // Menginput didalam menu
        switch (pilih) {
        case 1:
            display();
            system("pause");
            break;
        case 2:
            pemesananTiket();
            system("pause");
            break;
        case 3:
            editPemesanan();
            system("pause");
            break;
        case 4:
            pencarianTiket();
            system("pause");
            break;
        case 5:
            pembatalanTiket();
            system("pause");
            break;
        case 0:
            printf("Keluar dari program...\n");
            break;
        default:
            printf("Pilihan tidak valid, coba lagi.\n");
            system("pause");
        }
    } while (pilih != 0);
}


int main() {
    menu(); // memanggil prosedur menu
    system("PAUSE");
    return 0;
}