#include "chatroom.h"



//Chatroom::Chatroom(Main_Weight *w, QWidget *parent):
//    QWidget(parent)
//{

//}


Chatroom::Chatroom(QTcpSocket *p_sock, QString tmp1, QString tmp2, QWidget *parent) :
    QWidget(parent)
{

    ip = getIP();
    qDebug() << "获取ip = " << ip;

    p_chat_socket = p_sock;
    uID1 = tmp1;
    uID2 = tmp2;
    setWindowTitle("Chatroom:" + tmp1 + " to " + tmp2);
    setWindowIcon(QPixmap(":/src/img/Chat_Icon.png"));

    //设置最大化最小化按钮无效
//    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);

    setWindowFlags(windowFlags() | Qt::Tool);//设置不在任务栏出现


    //设置背景颜色
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(Qt::lightGray));
    setPalette(palette);

//                tmp = new SliderDemo();
//                tmp->setWindowFlags(Qt::WindowStaysOnTopHint);
//                tmp->show();
//                tmp->slotStart();

    init_widget();//初始化相关的控件
}

Chatroom::~Chatroom()
{

}


//保存历史消息，不关闭chatroom
void Chatroom::closeEvent(QCloseEvent* event)
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


void Chatroom::init_widget()//初始化相关的控件
{
    textBrowser = new QTextBrowser;

    //设置textBrowser背景颜色或图片
  textBrowser->setStyleSheet("background-image: url(:/src/24.JPG);");//背景设置为2.jpg
    textBrowser->setMinimumSize(QSize(400, 300));

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(textBrowser);

    fontComboBox = new QFontComboBox;
    fontComboBox->setToolTip(tr("字体"));

    comboBox = new QComboBox;
    comboBox->setToolTip(tr("字号"));
    comboBox->setEditable(true);
    comboBox->addItem(QString::number(8));
    comboBox->addItem(QString::number(9));
    comboBox->addItem(QString::number(10));
    comboBox->addItem(QString::number(11));
    comboBox->addItem(QString::number(12));
    comboBox->addItem(QString::number(13));
    comboBox->addItem(QString::number(14));
    comboBox->addItem(QString::number(15));
    comboBox->addItem(QString::number(16));
    comboBox->addItem(QString::number(17));
    comboBox->addItem(QString::number(18));
    comboBox->addItem(QString::number(19));
    comboBox->addItem(QString::number(20));
    comboBox->addItem(QString::number(21));
    comboBox->addItem(QString::number(22));
    comboBox->setCurrentIndex(4);

    toolButton_1 = new QToolButton;
    toolButton_1->setToolTip(tr("加粗"));
    toolButton_1->setText(tr("加粗"));
    toolButton_1->setCheckable(true);
    toolButton_1->setAutoRaise(true);
    toolButton_1->setIcon(QPixmap(":/src/img/bold.png"));

    toolButton_2 = new QToolButton;
    toolButton_2->setToolTip(tr("倾斜"));
    toolButton_2->setText(tr("倾斜"));
    toolButton_2->setCheckable(true);
    toolButton_2->setAutoRaise(true);
    toolButton_2->setIcon(QPixmap(":/src/img/italic.png"));

    toolButton_3 = new QToolButton;
    toolButton_3->setToolTip(tr("下划线"));
    toolButton_3->setText(tr("下划线"));
    toolButton_3->setCheckable(true);
    toolButton_3->setAutoRaise(true);
    toolButton_3->setIcon(QPixmap(":/src/img/under.png"));

    toolButton_4 = new QToolButton;
    toolButton_4->setToolTip(tr("颜色"));
    toolButton_4->setText(tr("颜色"));
    toolButton_4->setAutoRaise(true);
    toolButton_4->setIcon(QPixmap(":/src/img/color.png"));

    send_file_Button = new QToolButton;
    send_file_Button->setText(tr("发送文件"));
    send_file_Button->setAutoRaise(true);

    //初始化文件相关组件
    fDialog = new QFileDialog(this);
    fDialog->setFileMode(QFileDialog::ExistingFiles);
    connect(fDialog,SIGNAL(fileSelected ( const QString & )),this,SLOT(requser_send_files(const QString &)));
    fDialog->hide();
    udpSocket = new QUdpSocket(this);



    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(fontComboBox);
    layout2->addWidget(comboBox);
    layout2->addWidget(toolButton_1);
    layout2->addWidget(toolButton_2);
    layout2->addWidget(toolButton_3);
    layout2->addWidget(toolButton_4);
    layout2->addWidget(send_file_Button);

    lineEdit = new QLineEdit;

    pushButton = new QPushButton;
    pushButton->setText(tr("发送"));

   QHBoxLayout *layout3 = new QHBoxLayout;
    layout3->addWidget(lineEdit);
    layout3->addWidget(pushButton);

    QVBoxLayout *mainlayout = new QVBoxLayout;

    mainlayout->addLayout(layout1);
    mainlayout->addLayout(layout2);
    mainlayout->addLayout(layout3);
    //mainlayout->setSizeConstraint(QLayout::SetFixedSize);//设置窗口大小不能改变
    setLayout(mainlayout);

    textBrowser->setCurrentFont(fontComboBox->font());//设置textBrowser的默认字体
    textBrowser->setFontPointSize(comboBox->currentText().toDouble());//设置textBrowser的默认字号
    lineEdit->setFocus();

    connect(fontComboBox, SIGNAL(currentFontChanged(const QFont &)), this, SLOT(on_fontComboBox_currentFontChanged(const QFont &)));
    connect(comboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(on_comboBox_currentIndexChanged(const QString &)));
    connect(toolButton_1, SIGNAL(clicked(bool)), this, SLOT(on_toolButton_1_clicked(bool)));
    connect(toolButton_2, SIGNAL(clicked(bool)), this, SLOT(on_toolButton_2_clicked(bool)));
    connect(toolButton_3, SIGNAL(clicked(bool)), this, SLOT(on_toolButton_3_clicked(bool)));
    connect(toolButton_4, SIGNAL(clicked()), this, SLOT(on_toolButton_4_clicked()));
    connect(send_file_Button, SIGNAL(clicked()), this, SLOT(on_send_file_Button_clicked()));
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_returnPressed()));
    connect(pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

}

void Chatroom::on_lineEdit_returnPressed()
{
    if (pushButton->isEnabled())//如果pushButton没有变灰，那么就可以调用on_pushButton_clicked()函数
        on_pushButton_clicked();
}

void Chatroom::on_pushButton_clicked()
{
    if( lineEdit->text().isEmpty())//如果lineEdit控件内容为空，提示用户不能发送空消息
    {
        QMessageBox::information(this, tr("注意"), tr("不能发送空消息"));
    }
    else
    {
        add_msg(tr("我的消息"), lineEdit->text());//将要发送的消息内容加入textBrowser控件中
//        main_w->send_Msg(userID, lineEdit->text().toStdString().data());//调用主窗口的send_Msg方法，向服务器提交send消息
//        Todo:发送消息

        uint32_t len = 0;
        Json::Value message;
        message["ID1"] = uID1.toStdString().c_str();
        message["ID2"] = uID2.toStdString().c_str();
        message["content"] = lineEdit->text().toStdString().c_str();
        uint8_t *pData = encode(MESSAGE_SEND, message, len);

        qDebug() << "给服务器发送消息, length : " << len;
        p_chat_socket->write((char *)pData, len);


        qDebug() << "向服务器发送消息";

        lineEdit->clear();//发送完成后，将lineEdit控件内容清空
    }
    lineEdit->setFocus();
}

void Chatroom::add_msg(QString delivername, QString msg)//向textBrowser添加消息
{
    //得到当前时间，并把时间格式化为"yyyy-MM-dd hh:ss:ss"形式的字符串
    QString sTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:ss:ss");
    textBrowser->append("[" + delivername + "]" + sTime);
    textBrowser->append(msg);

    //当消息textBrowser中消息过多出现滚动条时，自动滚动到最下方
//    textBrowser->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->maximum());
}

void Chatroom::on_fontComboBox_currentFontChanged(const QFont &f)//修改textBrowser字体
{
    textBrowser->setCurrentFont(f);
    textBrowser->setFontPointSize(comboBox->currentText().toDouble());

    if(toolButton_1->isChecked())
    {
        textBrowser->setFontWeight(QFont::Bold);
    }
    else
    {
        textBrowser->setFontWeight(QFont::Normal);
    }

    if(toolButton_2->isChecked())
    {
        textBrowser->setFontItalic(true);
    }
    else
    {
        textBrowser->setFontItalic(false);
    }

    if(toolButton_3->isChecked())
    {
        textBrowser->setFontUnderline(true);
    }
    else
    {
        textBrowser->setFontUnderline(false);
    }

    textBrowser->setTextColor(color);
    lineEdit->setFocus();

}

void Chatroom::on_comboBox_currentIndexChanged(const QString &arg1)//修改textBrowser字号
{
    textBrowser->setFontPointSize(arg1.toDouble());
    lineEdit->setFocus();
}

void Chatroom::on_toolButton_1_clicked(bool checked)//修改textBrowser字体是否加粗
{
    if(checked)
    {
        textBrowser->setFontWeight(QFont::Bold);
    }
    else
    {
        textBrowser->setFontWeight(QFont::Normal);
    }
    lineEdit->setFocus();
}

void Chatroom::on_toolButton_2_clicked(bool checked)//修改textBrowser字体是否斜体
{
    textBrowser->setFontItalic(checked);
    lineEdit->setFocus();
}

void Chatroom::on_toolButton_3_clicked(bool checked)//修改textBrowser字体是否下划线
{
    textBrowser->setFontUnderline(checked);
    lineEdit->setFocus();
}

void Chatroom::on_toolButton_4_clicked()//修改textBrowser字体颜色
{
    color = QColorDialog::getColor(color,this);
    if(color.isValid())
    {
        textBrowser->setTextColor(color);
        lineEdit->setFocus();
    }
}

void Chatroom::on_send_file_Button_clicked()
{
    fDialog->show();
}

void Chatroom::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        qDebug() << datagram;
        if(datagram == "1"){
            recip = sender;
            qDebug() << "接收端同意, 设置发送端的recip =" << recip;
//            tmp = new SliderDemo();
//            tmp->setWindowFlags(Qt::WindowStaysOnTopHint);
//            tmp->show();
//            tmp->slotStart();
            sendData();
            break;
        }
        else {
            qDebug() << "接收端拒绝， 关闭文件";
            file->close();
            break;
        }
    }
}

void Chatroom::sendData()
{



    int maxnum = int(file->size() / 8);

    qDebug() << "file size : " << file->size() << "maxnum = " << maxnum;


    int i = 0;
    int current = 0;
    while(!file->atEnd())
    {

//        qDebug() << "正在发送文件" << *file;
        QByteArray line = file->read(8);
        udpSocket->writeDatagram(line, line.length(), recip, 7755);
        i++;
//        if(i*100/maxnum>current)
//        {
//            current=i*100/maxnum;
//            qDebug() << "刷新进度条：" << current;

//            tmp->setprocess(current);


//        }

    }
    tmp->close();

    qDebug() << "sendData()：文件发送完成!然后关闭文件";
    udpSocket->writeDatagram("#", 1, recip, 7755);
    file->close();
    QMessageBox::warning(this,tr("通知"),tr("发送成功！"),QMessageBox::Yes);
    disconnect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    udpSocket->close();

}

void Chatroom::requser_send_files(const QString & fs){
    //选中文件点击open后会出发该信号 至在打开单一文件时出发

    qDebug() <<"发送端选择：fs"<<fs;
    files_name.clear();
    files_name.append(fs);
    qDebug() << "设置文件name：" << files_name;

    if(file == nullptr)
    {
        file = new QFile;
    }
    file->setFileName(files_name);

    qDebug() << "file" << *file;
    if (!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "发送端打开文件失败";
        return;
    }
    else{
        qDebug() << "发送端打开文件成功" << *file;
    }
    //向服务器发送文件申请

    QStringList list = files_name.split("/");
    uint32_t len = 0;
    Json::Value message;
    message["ID1"] = uID1.toStdString().c_str();
    message["ID2"] = uID2.toStdString().c_str();
    message["file_name"] = list.last().toStdString().c_str();
    uint8_t *pData = encode(FILE_TRANS_REQ, message, len);
    udpSocket->bind(QHostAddress::Any, 7758);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    qDebug() << "设置connect, 并且向服务器发送文件请求, files_name: " << list.last();
    qDebug() << "发送段的ip = " << getIP();

    p_chat_socket->write((char *)pData, len);

}

QString Chatroom::getIP()  //获取ip地址
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

//void Chatroom::set_file_recever(QString rip)
//{
//    recip = QHostAddress(rip);
//    qDebug() << "接收端成功设置recip" << recip;
//}

