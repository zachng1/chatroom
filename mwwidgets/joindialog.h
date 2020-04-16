#ifndef JOINDIALOG_H
#define JOINDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QHostAddress>
#include <QLineEdit>
#include <QDialogButtonBox>

class JoinDialog : public QDialog
{
    Q_OBJECT
public:
    JoinDialog(QWidget * parent=nullptr);
    QString username();
    QString ipaddress();
    QString port();
private:
    QFormLayout * layout;
    QDialogButtonBox * acceptreject;

    QLineEdit * uname;
    QLineEdit * address;
    QLineEdit * portnum;
};

#endif // JOINDIALOG_H
