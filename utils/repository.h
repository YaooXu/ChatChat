#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QDialog>

namespace Ui {
class repository;
}

class repository : public QDialog
{
    Q_OBJECT

public:
    explicit repository(QWidget *parent = nullptr);
    ~repository();

private:
    Ui::repository *ui;
};

#endif // REPOSITORY_H
