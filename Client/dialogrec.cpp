#include "dialogrec.h"
#include "ui_dialogrec.h"

DialogRec::DialogRec(QString s_ip, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRec)
{
    ui->setupUi(this);
    sender_ip = s_ip;

    fDialog = new QFileDialog(this);
    fDialog->setFileMode(QFileDialog::Directory);
    QPixmap map;
    map.load(":/src/22.JPG");
    map = map.scaled(QSize(210,150));
//    ui->label_map->setPixmap(map);

    this->setWindowTitle(tr("文件传输！"));
    connect(fDialog,SIGNAL(fileSelected ( const QString & )),this,SLOT(fs(const QString & )));

    fDialog->hide();

    udpSocket = new QUdpSocket(this);

    ui->lineEdit_path->clear();
}

DialogRec::~DialogRec()
{
    delete ui;
}

void DialogRec::closeEvent(QCloseEvent* event)
{
    if(true)
    {

        this->hide();
    }
    else
    {
        event->accept();
    }
}


void DialogRec::fs(const QString & file_tmp){
    //选中文件点击open后会出发该信号 至在打开单一文件时出发
    qDebug() <<"fs";
    qDebug() << file_tmp;

    ui->lineEdit_path->setText(file_tmp);
    filee.append(file_tmp);
    filee.append("/");
    filee.append(file_name);
    qDebug()<<filee<<"成功选择";

}

void DialogRec::initSocket()
{
    qDebug() << "点击“是”， initSocket, 接收端到发送端" << filee;

    if(file == nullptr)
    {
        file = new QFile;
        qDebug() << "aaa";

        file->setFileName( filee );
    }
    else {
        file->close();
        //file = nullptr;
        file = new QFile;
        file->setFileName( filee );
        qDebug() << "bbb";

    }
    qDebug() << "重置file" << *file;

    if (!file->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Unbuffered))
    {
        qDebug()<<"open file error";
        return;
    }
    filee.clear();
    udpSocket->bind(QHostAddress::Any, 7755);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
    QHostAddress sender = QHostAddress(sender_ip);
    if(sender_ip == getIP())
    {
        qDebug() << "发现bug， ip冲突";
    }
    udpSocket->writeDatagram("1",1, sender ,7758);
    qDebug() << "重置之后发送同意, 发送端 = " << sender_ip << "接收端ip = " << getIP();
}

void DialogRec::readPendingDatagrams()
{
    qDebug() << "正在写入文件：" << *file;
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        if(datagram.size() == 1 && strcmp(datagram, "#") == 0)
        {
            file->close();
            qDebug() << "接受完毕，文件关闭";
            break;
        }

        qDebug() << *file;
        file->write(datagram.data(),datagram.size());
    }

    disconnect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
    udpSocket->close();

}

void DialogRec::fileName(QString a,QString b)
{
    filee.clear();
    file_name.clear();
    file_name.append(a);
    ui->lineEdit->setText(file_name);
    ui->label->setText(b + " 给您传文件，<br>是否接收？？？");
}

void DialogRec::on_pushButton_3_clicked()
{
    fDialog->show();
}

void DialogRec::on_pushButton_clicked()//点击“是”，返回1给sender
{
    initSocket();
}

void DialogRec::set_file_recever(QString rip)
{
    sender_ip = rip;
    qDebug() << "接收端成功设置recip" << sender_ip;
}

QString DialogRec::getIP()  //获取ip地址
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list){
       if(address.protocol() == QAbstractSocket::IPv4Protocol){
           if (address.toString().contains("127.0.")){
               continue;
           }
           return address.toString();
       }
    }
    return 0;
}
