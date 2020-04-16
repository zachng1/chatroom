#ifndef HOSTDIALOG_H
#define HOSTDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>


class HostDialog : public QDialog
{
    Q_OBJECT
public:
    HostDialog(QWidget * parent=nullptr);
    QString getPort();

private:
    QFormLayout * layout;
    QLineEdit * portedit;
    QDialogButtonBox * acceptreject;
};

#endif // HOSTDIALOG_H
