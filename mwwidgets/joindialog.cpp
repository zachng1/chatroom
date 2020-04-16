#include "joindialog.h"

JoinDialog::JoinDialog(QWidget * parent) : QDialog(parent),
    layout{new QFormLayout},
    acceptreject{new QDialogButtonBox}
{
    acceptreject->addButton("&Join", QDialogButtonBox::AcceptRole);
    acceptreject->addButton("&Cancel", QDialogButtonBox::RejectRole);
    connect(acceptreject, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
    connect(acceptreject, &QDialogButtonBox::accepted,
            this, &QDialog::accept);

    uname = new QLineEdit;
    address = new QLineEdit;
    portnum = new QLineEdit;

    layout->addRow("Username", uname);
    layout->addRow("Host Address", address);
    layout->addRow("Port Number", portnum);
    layout->addRow(acceptreject);

    setLayout(layout);
}

QString JoinDialog::username() {
    return uname->text();
}
QString JoinDialog::ipaddress() {
    return address->text();
}
QString JoinDialog::port() {
    return portnum->text();
}
