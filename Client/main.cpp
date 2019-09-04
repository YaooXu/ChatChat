#include "my_include.h"
#include <QApplication>
#include "chatroom.h"
#include "main_weight.h"
#include "chatroom_plus.h"
#include "sliderdemo.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Main_Weight *p_main_weight = new Main_Weight();

    p_main_weight->setWindowTitle("QQ");

//    SliderDemo *tmp = new SliderDemo();

//    tmp->show();
//    tmp->init_precess(1000);
//    tmp->setprocess(400);



    return a.exec();
}
