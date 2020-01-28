#ifndef SERVICE_H
#define SERVICE_H

#include <winsock2.h>
#include <string>
#include <QObject>
#include <pthread.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

using namespace std;

class Service : public QObject
{
    Q_OBJECT
    unsigned short Port = 8080;
    string VirtualAddr = "C:\\Users\\Administrator\\Desktop\\Study";
    SOCKET servSockd;
signals:
    void sendMessage(QString msg);
    void sendStop();
public:
    sockaddr_in sockAddr;
    sockaddr_in clntAddr;
    pthread_t *t;
    Service();
    static void *start(void *args);
    static void *service(void *args);
    static string DealBuff(char buff[]);
    static string Header(int staus,char buff[]);
    int setport(unsigned short port){
        this->Port = port;
        return true;
    }
    unsigned short getport(){
        return this->Port;
    }
    int setVirtualAddr(string VirtualAddr){
        this->VirtualAddr = VirtualAddr;
        return true;
    }
    string getVirtualAddr(){
        return VirtualAddr;
    }
    int setsockAddr(sockaddr_in sockAddr){
        this->sockAddr = sockAddr;
        return true;
    }
    sockaddr_in getsockAddr(){
        return sockAddr;
    }
    SOCKET getservSockd(){
        return servSockd;
    }
    int setservSockd(SOCKET servSockd){
        this->servSockd = servSockd;
        return true;
    }
//    int setlisteningport(unsigned short listeningPort){
//        this->listeningPort = listeningPort;
//        return true;
//    }
//    unsigned short getlisteningport(){
//        return this->listeningPort;
//    }
//    int setlisteningIp(string listeningIp){
//        this->listeningIp = listeningIp;
//        return true;
//    }
//    string getlisteningIp(){
//        return listeningIp;
//    }
};

struct Information{
    SOCKET *clntSock;
    Service *service;
    string listeningIp;
    unsigned short listeningPort;
};

#endif // SERVICE_H
