#include "loginform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm form;
    form.resize(420, 280);
    form.show();
    return QApplication::exec();
}
