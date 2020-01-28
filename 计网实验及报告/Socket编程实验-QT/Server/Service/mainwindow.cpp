#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "service.h"
#include <pthread.h>
#include <QPainter>
#include <QDir>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QFileDialog>
#include <sstream>
#include <service.h>




using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    int nListSize = ipAddressesList.size();
    ui->comboBox->addItem("0.0.0.0");
    for (int i = 0; i < nListSize; ++i){
        if (ipAddressesList.at(i).toIPv4Address()) {
            ui->comboBox->addItem(ipAddressesList[i].toString());
        }
    }

    QObject::connect(service,&Service::sendMessage,this,&MainWindow::receiveMeaage);
//    QObject::connect(service,&Service::sendStop,this,&MainWindow::on_pushButton_2_clicked);
    setAutoFillBackground(true);
    QPalette pal = this->palette();
    //    pal.setColor(QPalette::Background, QColor(19, 54, 118));
    pal.setBrush(backgroundRole(), QPixmap("C:\\Users\\Administrator\\Pictures\\1.png"));
    setPalette(pal);
    //    ui->textEdit->setPlainText(inet_ntoa(service->getsockAddr().sin_addr));
    ui->textEdit_2->setPlainText(QString::number(service->getport()));
    ui->textEdit_3->setPlainText(QString::fromStdString(service->getVirtualAddr()));
    ui->pushButton_2->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    service->sendMessage("Start the service!\n\n");
    QString IP = ui->comboBox->currentText();
    QString port = ui->textEdit_2->toPlainText();
    QString VA = ui->textEdit_3->toPlainText();
    service->t = new pthread_t();
    service->setport(port.toUShort());
    char* str = IP.toLatin1().data();
    service->sockAddr.sin_addr.s_addr = inet_addr(str);
    service->sockAddr.sin_port = htons(port.toUShort());
    service->setVirtualAddr(VA.toStdString());
    pthread_create((service->t), nullptr, Service::start, MainWindow::service);
    //    ui->textEdit->setReadOnly(true);
    ui->comboBox->setDisabled(true);
    ui->textEdit_2->setReadOnly(true);
    ui->textEdit_3->setReadOnly(true);
    ui->pushButton->setText("正在运行");
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(false);
}

void MainWindow::on_pushButton_2_clicked()
{
    service->sendMessage("Stop the service!\n\n");
    pthread_cancel(*service->t);
    closesocket(service->getservSockd());
    ui->pushButton->setText("启动");
    ui->comboBox->setDisabled(false);
    //    ui->textEdit->setReadOnly(false);
    ui->textEdit_2->setReadOnly(false);
    ui->textEdit_3->setReadOnly(false);
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(true);
}

void MainWindow::receiveMeaage(QString msg){
    ui->textEdit_4->append(msg);
}

void MainWindow::on_toolButton_clicked()
{
    QString directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("Save path"),QDir::currentPath()));
    if(!directory.isEmpty()){
        ui->textEdit_3->setPlainText(directory);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit_4->clear();
}
