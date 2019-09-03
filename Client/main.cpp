#include "chatchat.h"
#include <QApplication>
#include "chatroom.h"
#include "main_weight.h"
#include "chatroom_plus.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Main_Weight *m = new Main_Weight();

    m->setWindowTitle("QQ");
    m->show();
//    Chatroom *p_tmp = new Chatroom();
//    p_tmp->setWindowTitle("Chatroom");
//    p_tmp->resize(1600, 1200);
//    p_tmp->show();
//    Chatroom_Plus *tmp = new Chatroom_Plus();
//    tmp->show();


    return a.exec();
}
