#include "service.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <winsock2.h>
#include <unistd.h>
#include <ctype.h>
#include <map>
#include <fstream>
#include <QString>
#include <QDebug>
#define printf qDebug

#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
using namespace std;
#define MAXLINE 4096u

Service::Service()
{
    //初始化
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。
    sockAddr.sin_port = htons(Port);
}

void *Service::start(void *args){
    int *a = nullptr;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, nullptr);
    Service *service = static_cast<Service *> (args);
    SOCKET servSockd = service->getservSockd();
    sockaddr_in sockAddr = service->sockAddr;
//    sockaddr_in clntAddr = service->clntAddr;
    if ((servSockd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        //printf("creat socket error: %s(errno: %d)\n", strerror(errno), errno);
        service->sendMessage(QString("creat socket error: %1(errno: %2)\n").arg(strerror(errno)).arg(errno));
//        service->sendStop();
        return a;
    }
    service->setservSockd(servSockd);
    if (bind(servSockd, (struct sockaddr *) &sockAddr, sizeof(sockAddr)) == -1) {
        //printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        service->sendMessage(QString("bind socket error: %1(errno: %2)\n").arg(strerror(errno)).arg(errno));
//        service->sendStop();
        return a;
    }
    //开始监听是否有客户端连接
    if (listen(servSockd, 20) == -1) {
        //printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        service->sendMessage(QString("listen socket error: %1(errno: %2)\n").arg(strerror(errno)).arg(errno));
//        service->sendStop();
        return a;
    }
    printf("======waiting for client's request======\n");
    while (true) {
        //阻塞直到有客户端连接
        sockaddr_in *clntAddr = new sockaddr_in();
        int clntAddrLen =  sizeof (*clntAddr);
        auto *clntSock = new SOCKET();
        if ((*clntSock = accept(servSockd, (struct sockaddr *)clntAddr, &clntAddrLen)) == -1) {
            //printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
            service->sendMessage(QString("accept socket error: %1(errno: %2)\n").arg(strerror(errno)).arg(errno));
            continue;
        }
        pthread_t *t = new pthread_t();
        Information *information = new Information{clntSock,service,inet_ntoa(clntAddr->sin_addr),ntohs(clntAddr->sin_port)};
        pthread_create(t, nullptr, Service::service, information);
    }
}

void *Service::service(void *args){
//    printf("线程开启");
    char buff[4096];
    int n;
    Information *information = static_cast<Information *> (args);
    SOCKET *clntSock = information->clntSock;
    Service *service = information->service;
    string *VirtualAddr = &(information->service->VirtualAddr);
    //接受客户端传过来的数据
    n = recv(*clntSock, buff, MAXLINE, 0);
    buff[n] = '\0';
    //    printf("recv msg: %s\n", buff);
    QString str;
    QString listeningIP = QString::fromStdString(information->listeningIp);
    str = QString("listen address = %1 : %2\n\n%3").arg(listeningIP).arg(information->listeningPort).arg(buff);
    fflush(stdout);
    string index = DealBuff(buff);
    string data;
    int flag = 0;
    //向客户端发送回应数据
    string file = *VirtualAddr + index;
    ifstream f(file, ios::binary);
    if (f.is_open()) {
//        data = "HTTP/1.1 200 OK\n"
//               "Connection: Keep-Alive\n\n";
        data = Header(1,buff);
    } else {
//        service->sendMessage(QString("404 not find！"));
        flag = 1;
        str += "404 not find!\n\n";
//        data = "HTTP/1.1 404 NOT_FIND\n"
//               "Connection: Keep-Alive\n\n";
        data = Header(0,buff);
        f.open(R"(C:\Users\Administrator\Desktop\Study\error.html)",ios::binary);
    }
//    service->sendMessage(QString::fromStdString(data));
    if (send(*clntSock, data.data(),data.size(), 0) == -1) {
        //perror("send error1");
//        service->sendMessage(QString("send error-1!"));
        //continue;
    }
    char html[4096];
    while (true) {
        f.read(html, 4096);
        int num = static_cast<int>(f.gcount());
        if (send(*clntSock, html, num, 0) == -1) {
            //perror("send error2");
//            service->sendMessage(QString("send error-2!"));
            str += "send error!\n\n";
        }
        if (num < 4096) {
            if(flag == 0) str += "send successfully!\n\n";
            break;
        }
    }
    service->sendMessage(str);
    f.close();
    closesocket(*clntSock);
    return nullptr;
}

string Service::DealBuff(char buff[]) {//处理请求响应
    string info = buff;
    string index;
    int m = 0, h = 0;
    m = info.find('/');
    h = info.find(' ', static_cast<unsigned int> (m));
    if (m < 0 || h < 0) index = "";
    else index = info.substr(  (m), (h - m));
    if (index == "/") index = "/index.html";
    return index;
}

string Service::Header(int staus,char buff[]){//组装响应报文
    string data,connection;
    string info = buff;
    int m = 0,h = 0;
    if(staus == 0) data += "HTTP/1.1 404 not_find\n";
    else data += "HTTP/1.1 200 OK\n";
    data += "Connection: keep-alive\n\n";
//    m = info.find("Connection");
//    h = info.length();
//    connection = info.substr(static_cast<unsigned long long> (m),static_cast<unsigned long long> (h-m));
//    data += connection;
    return data;
}
