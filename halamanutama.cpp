#include "halamanutama.h"
#include "ui_halamanutama.h"
#include <QMessageBox>


HalamanUtama::HalamanUtama(QWidget *parent, const QString &username) :
    QWidget(parent),
    ui(new Ui::HalamanUtama),
    currentUser(username)
{
    ui->setupUi(this);

    // Inisialisasi table
    ui->tableWidget->setColumnCount(4);
    QStringList header = {"Judul", "Pengarang", "Tahun", "Kategori"};
    ui->tableWidget->setHorizontalHeaderLabels(header);

    // Inisialisasi jumlah buku
    jumlahBuku = 0;

    // Tampilkan tampilan sesuai role
    if (currentUser == "admin") {
        tampilkanTampilanAdmin();
    } else {
        tampilkanTampilanUser();
    }
}

HalamanUtama::~HalamanUtama()
{
    delete ui;
}



void HalamanUtama::tampilkanTampilanAdmin() {
    ui->label_tampilan->setText("Selamat datang Admin!");
    ui->button_tambahBuku->setVisible(true);
    ui->button_hapusBuku->setVisible(true);
}

void HalamanUtama::tampilkanTampilanUser() {
    ui->label_tampilan->setText("Selamat datang " + currentUser + "!");
    // Menyembunyikan tombol tambah dan hapus buku untuk user
    ui->button_tambahBuku->setVisible(false);
    ui->button_hapusBuku->setVisible(false);
    ui->tableView_buku->setVisible(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->lineEdit_judul->setVisible(false);
    ui->lineEdit__pengarang->setVisible(false);
    ui->lineEdit_tahun->setVisible(false);
    ui->lineEdit_kategori->setVisible(false);
    ui->pushButton_ubah->setVisible(false);
    ui->label->setVisible(false);
    ui->label->setVisible(false);


    // Menampilkan hanya tableWidget
    ui->tableWidget->setVisible(true);
}

void HalamanUtama::muatDataKeTabel(int index) {
    ui->tableWidget->insertRow(index);
    ui->tableWidget->setItem(index, 0, new QTableWidgetItem(daftarBuku[index].judul));
    ui->tableWidget->setItem(index, 1, new QTableWidgetItem(daftarBuku[index].pengarang));
    ui->tableWidget->setItem(index, 2, new QTableWidgetItem(daftarBuku[index].tahun));
    ui->tableWidget->setItem(index, 3, new QTableWidgetItem(daftarBuku[index].kategori));
}

// Fungsi untuk menambah buku (hanya untuk admin)
void HalamanUtama::on_button_tambahBuku_clicked() {
    QString judul = ui->lineEdit_judul->text();
    QString pengarang = ui->lineEdit__pengarang->text(); // sudah diganti
    QString tahun = ui->lineEdit_tahun->text();
    QString kategori = ui->lineEdit_kategori->text();

    if (judul.isEmpty() || pengarang.isEmpty() || tahun.isEmpty() || kategori.isEmpty()) {
        QMessageBox::warning(this, "Input Salah", "Semua field harus diisi!");
        return;
    }

    // Validasi angka pada tahun
    bool isAngka;
    tahun.toInt(&isAngka);
    if (!isAngka) {
        QMessageBox::warning(this, "Input Salah", "Tahun harus berupa angka!");
        return;
    }

    if (jumlahBuku < maxBuku) {
        daftarBuku[jumlahBuku].judul = judul;
        daftarBuku[jumlahBuku].pengarang = pengarang;
        daftarBuku[jumlahBuku].tahun = tahun;
        daftarBuku[jumlahBuku].kategori = kategori;
        muatDataKeTabel(jumlahBuku);
        jumlahBuku++;

        ui->lineEdit_judul->clear();
        ui->lineEdit__pengarang->clear();
        ui->lineEdit_tahun->clear();
        ui->lineEdit_kategori->clear();

        QMessageBox::information(this, "Sukses", "Buku berhasil ditambahkan!");
    } else {
        QMessageBox::warning(this, "Peringatan", "Batas maksimum buku telah tercapai!");
    }
}

// Fungsi untuk menghapus buku (hanya untuk admin)
void HalamanUtama::on_button_hapusBuku_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row >= 0 && row < jumlahBuku) {
        ui->tableWidget->removeRow(row);

        for (int i = row; i < jumlahBuku - 1; i++) {
            daftarBuku[i] = daftarBuku[i + 1];
        }

        jumlahBuku--;
        QMessageBox::information(this, "Sukses", "Buku berhasil dihapus!");
    } else {
        QMessageBox::warning(this, "Peringatan", "Silakan pilih baris buku yang ingin dihapus!");
    }
}


void HalamanUtama::on_pushButton_informasi_clicked() {
    emit kelolaData();  // Panggil sinyal saat tombol diklik
}

