#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QWidget>

namespace Ui {
class repository;
}

class repository : public QWidget
{
    Q_OBJECT

public:
    explicit repository(QWidget *parent = nullptr);
    ~repository();

private slots:
    void on_two_clicked();

    void on_one_clicked();

    void on_three_clicked();

    void on_four_clicked();

    void on_five_clicked();

    void on_six_triggered(QAction *arg1);

    void on_seven_clicked();

    void on_eight_clicked();

    void on_nine_triggered(QAction *arg1);

    void on_nine_clicked();

    void on_ten_clicked();

    void on_eleven_clicked();

    void on_twelve_clicked();

    void on_thirteen_clicked();

    void on_six_clicked();

    void on_fourteen_clicked();

    void on_fifteen_clicked();

    void on_sixteen_clicked();

    void on_seventeen_clicked();

    void on_toolButton_5_clicked();

    void on_eighteen_clicked();

    void on_nineteen_clicked();

    void on_twenty_clicked();

signals:

    void sendsignal(int);

private:
    Ui::repository *ui;
};

#endif // REPOSITORY_H
