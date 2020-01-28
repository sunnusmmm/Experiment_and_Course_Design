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
	Packet lastAckPkt;				//��???���͵�???�ϱ�???
	const int numsize;				//�����			
	int size;						//���ڴ�С
	int base;						//���ڳ�ʼ���
	receiverPacket *slide;

public:
	void printSlide();					//��ӡ��������
	bool isInWindow(int seqnum);		//�ж�����Ƿ��ڴ�����
	TCPRdtReceiver();
	virtual ~TCPRdtReceiver();

public:
	
	void receive(const Packet &packet);	//���ձ��ģ�����NetworkService����
};

#endif