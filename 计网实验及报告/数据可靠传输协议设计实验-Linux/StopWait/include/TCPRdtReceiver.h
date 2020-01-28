#ifndef TCP_RDT_RECEIVER_H
#define TCP_RDT_RECEIVER_H
#include "RdtReceiver.h"

struct receiverPacket{
	Packet packet;
	bool flag;
};

class TCPRdtReceiver :public RdtReceiver
{
private:
	Packet lastAckPkt;				//上???发送的???认报???
	const int numsize;				//序号数			
	int size;						//窗口大小
	int base;						//窗口初始序号
	receiverPacket *slide;

public:
	void printSlide();					//打印滑动窗口
	bool isInWindow(int seqnum);		//判断序号是否在窗口中
	TCPRdtReceiver();
	virtual ~TCPRdtReceiver();

public:
	
	void receive(const Packet &packet);	//接收报文，将被NetworkService调用
};

#endif