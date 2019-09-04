#include "group_chat.h"
#include "ui_group_chat.h"

group_chat::group_chat(QTcpSocket *p_socket,QString temp,QString p_name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::group_chat)
{
    ui->setupUi(this);
    uID1=temp;
    name=p_name;
    ui->lineEdit_3->setText(name);
    //qDebug()<<p_name<<name<<"3333333333333333";
    this->ptr_socket = p_socket;
    setWindowTitle("多人聊天室");
    setWindowIcon(QPixmap(":/src/img/Chat_Icon.png"));
}

group_chat::~group_chat()
{
    delete ui;

}
void group_chat::on_pushButton_2_clicked()//将我的消息传给服务器
{
    if( ui->pre_text->text().isEmpty())//如果lineEdit控件内容为空，提示用户不能发送空消息
    {
        QMessageBox::information(this, tr("注意"), tr("不能发送空消息"));
    }
    else
    {
        add_msg1(tr("我的消息"), ui->pre_text->text());//将要发送的消息内容加入textBrowser控件中
//        main_w->send_Msg(userID, lineEdit->text().toStdString().data());//调用主窗口的send_Msg方法，向服务器提交send消息
//        Todo:发送消息

        uint32_t len = 0;
        Json::Value message;
        message["ID1"] = uID1.toStdString().c_str();
        //qDebug()<<name<<"4444444444444444";
        message["name"]=name.toStdString().c_str();
        message["content"] = ui->pre_text->text().toStdString().c_str();
        message["time"]=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:ss:ss").toStdString().c_str();
        uint8_t *pData = encode(MESSAGE_GROUP_SEND, message, len);

        qDebug() << "给服务器发送消息, length : " << len;
        ptr_socket->write((char *)pData, len);


        qDebug() << "向服务器发送消息";

        ui->pre_text->clear();//发送完成后，将lineEdit控件内容清空
    }

}

void group_chat:: add_msg1(QString delivername, QString msg)//向textBrowser添加消息
{
    //得到当前时间，并把时间格式化为"yyyy-MM-dd hh:ss:ss"形式的字符串
    QString sTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:ss:ss");
    ui->text_Browser->append("[" + delivername + "]" + sTime);
    ui->text_Browser->append(msg);

    //当消息textBrowser中消息过多出现滚动条时，自动滚动到最下方
//    textBrowser->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->maximum());
}
void group_chat::add_info(QString ID, QString IP){
    ui->p_textBrowser->append("IP："+IP+" ID："+ID);
}
void group_chat::input_info(int n){
        ui->p_textBrowser->clear();
        QString d=QString::number(n);
     ui->p_textBrowser->append("当前在线人数为："+d);
}

void group_chat::on_pushButton_clicked()
{
    this->close();
}
