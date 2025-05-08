#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "halamanutama.h"
#include <QMessageBox>
#include <QFile>
#include <QGraphicsOpacityEffect>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , userCount(0) // Inisialisasi jumlah user
{
    ui->setupUi(this);

    // Set password jadi bintang
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    // Menambahkan user "Dhimas" dengan password "user123" ke dalam array
    addUser("Dhimas", "user123");

    // Cek apakah gambar tersedia di resource



        // Tambahkan halaman informasi ke stack


    // Tambahkan background image



}

MainWindow::~MainWindow() {
    delete ui;
    delete halamanutama;  // Pastikan halamanutama dibersihkan dari memori
}

void MainWindow::on_pushButton_login_clicked() {
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    // Cek apakah login sebagai admin
    if (username == "admin" && password == "admin123") {
        QMessageBox::information(this, "Login Sukses", "Selamat datang di Perpustakaan Amba!");

        // Simpan user ke array
        addUser(username, password);

        // Buka halaman utama sebagai admin
        halamanutama = new HalamanUtama(nullptr, username);
        halamanutama->show();
        this->hide();  // Sembunyikan MainWindow
    }
    // Cek apakah username dan password ada dalam array users (untuk user biasa)
    else {
        int index = binarySearchUser(username);
        if (index != -1 && users[index].password == password) {
            QMessageBox::information(this, "Login Sukses", "Selamat datang, " + username + "!");

            // Buka halaman utama untuk user biasa
            halamanutama = new HalamanUtama(nullptr, username);
            halamanutama->show();
            this->hide();  // Sembunyikan MainWindow
        } else {
            QMessageBox::warning(this, "Login Gagal", "Username atau password salah.");
        }
    }
}

void MainWindow::addUser(const QString &username, const QString &password) {
    if (userCount >= maxUser) {
        QMessageBox::warning(this, "Peringatan", "Kapasitas penyimpanan user sudah penuh.");
        return;
    }

    // Sisipkan user secara terurut berdasarkan username (insertion sort logic)
    int pos = 0;
    while (pos < userCount && users[pos].username < username) {
        pos++;
    }

    // Geser elemen ke kanan
    for (int i = userCount; i > pos; --i) {
        users[i] = users[i - 1];
    }

    // Masukkan data di posisi yang tepat
    users[pos].username = username;
    users[pos].password = password;
    userCount++;
}

// Fungsi binary search untuk mencari username
int MainWindow::binarySearchUser(const QString &username) {
    int left = 0, right = userCount - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (users[mid].username == username) {
            return mid;
        } else if (users[mid].username < username) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // tidak ditemukan
}
