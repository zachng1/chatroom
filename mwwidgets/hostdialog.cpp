#include "hostdialog.h"

HostDialog::HostDialog(QWidget * parent) : QDialog(parent),
    layout{new QFormLayout},
    portedit{new QLineEdit},
    acceptreject{new QDialogButtonBox}
{

    acceptreject->addButton("&Host", QDialogButtonBox::AcceptRole);
    acceptreject->addButton("&Cancel", QDialogButtonBox::RejectRole);

    connect(acceptreject, &QDialogButtonBox::accepted,
            this, &QDialog::accept);

    connect(acceptreject, &QDialogButtonBox::rejected,
            this, &QDialog::reject);

    layout->addRow("Port Number", portedit);
    layout->addRow(acceptreject);

    setLayout(layout);

}

QString HostDialog::getPort() {
    return portedit->text();
}
