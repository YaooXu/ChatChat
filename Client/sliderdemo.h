#ifndef SLIDERDEMO_H
#define SLIDERDEMO_H

#include "my_include.h"

namespace Ui {
class SliderDemo;
}

class SliderDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit SliderDemo(QWidget *parent = nullptr);
    ~SliderDemo();

    void setprocess(int value);
    void init_precess(int t_num);
    int maxnum = 0;

public slots:
    void slotStart();
    void slotStop();
    void slotProcessBar();




private:
//	Ui::SliderDemoClass ui;
    QTimer *m_timer;


private:
    Ui::SliderDemo *ui;
};

#endif // SLIDERDEMO_H


