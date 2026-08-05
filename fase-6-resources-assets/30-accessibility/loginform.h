#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

class LoginForm: public QWidget {
    Q_OBJECT;

public:
    LoginForm(QWidget* parent = nullptr): QWidget(parent)
    {
        setWindowTitle("Login - Accesibility Demo");

        auto* root = new QVBoxLayout(this);

        // Heading
        auto* heading = new QLabel("Masuk ke sistem");
        QFont headingFont = heading->font();
        headingFont.setPointSize(18);
        headingFont.setBold(true);
        heading->setFont(headingFont);
        heading->setAccessibleName("Heading: Masuk ke sistem");
        root->addWidget(heading);

        // Form fields
        auto* form = new QFormLayout;

        usernameField = new QLineEdit;
        usernameField->setPlaceholderText("contoh: galih@example.com");
        usernameField->setAccessibleName("Username atau email");
        usernameField->setAccessibleDescription("Masukan username atau alamat email anda");
        auto* lblUser = new QLabel("&Username:");
        lblUser->setBuddy(usernameField); // accelerator Alt+U -> focus ke field

        passwordField = new QLineEdit;
        passwordField->setEchoMode(QLineEdit::Password);
        passwordField->setAccessibleName("Password");
        passwordField->setAccessibleDescription("Masukan password, minimal 8 karakter");
        auto* lblPass = new QLabel("&Password:");
        lblPass->setBuddy(passwordField); // accelerator Alt+P -> focus ke field

        form->addRow(lblUser, usernameField);
        form->addRow(lblPass, passwordField);
        root->addLayout(form);

        // checkbox remember + visual icon (anti color-only signaling)
        rememberCheckbox = new QCheckBox("&Ingat saya selama 30 hari");
        rememberCheckbox->setAccessibleDescription("Centang untuk simpan sesi login di komputer ini");
        root->addWidget(rememberCheckbox);

        // Status label (kosong awal)
        statusLabel = new QLabel;
        statusLabel->setAccessibleName("Status pesan");
        root->addWidget(statusLabel);

        // Buttons
        auto* btnRow = new QHBoxLayout;
        loginBtn = new QPushButton("&Masuk");
        loginBtn->setAccessibleName("Tombol Masuk Login!");
        loginBtn->setAccessibleDescription("Klik untuk login dengan kredensial");
        loginBtn->setDefault(true);

        cancelBtn = new QPushButton("&Batal");
        cancelBtn->setAccessibleName("Tombol Batal");
        cancelBtn->setAccessibleDescription("Batalkan login dan tutup form");

        btnRow->addStretch();
        btnRow->addWidget(cancelBtn);
        btnRow->addWidget(loginBtn);
        root->addLayout(btnRow);

        // Tab order explicit
        setTabOrder(usernameField, passwordField);
        setTabOrder(passwordField, rememberCheckbox);
        setTabOrder(rememberCheckbox, loginBtn);
        setTabOrder(loginBtn, cancelBtn);

        // signal/slot
        connect(loginBtn, &QPushButton::clicked, this, &LoginForm::onLogin);
        connect(cancelBtn, &QPushButton::clicked, this, &QWidget::close);
    }

private slots:
    void onLogin()
    {
        if(usernameField->text().isEmpty()){
            // Bukan cuma merah - ada text + icon symbol
            statusLabel->setText("⚠ Username tidak boleh kosong");
            statusLabel->setStyleSheet("color: #c0392b; font-weight: bold;");
            usernameField->setFocus();
            return;
        }

        if(passwordField->text().length() < 8)
        {
            statusLabel->setText("⚠ Password minimal 8 karakter");
            statusLabel->setStyleSheet("color: #c0392b; font-weight: bold;");
            passwordField->setFocus();
            return;
        }

        statusLabel->setText("✓ Login berhasil");
        statusLabel->setStyleSheet("color: #27ae60; font-weight: bold;");
    }

private:
    QLineEdit *usernameField, *passwordField;
    QCheckBox* rememberCheckbox;
    QLabel* statusLabel;
    QPushButton *loginBtn, *cancelBtn;
};

#endif // LOGINFORM_H
