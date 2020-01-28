#ifndef SR_RDT_SENDER_H
#define SR_RDT_SENDER_H
#include "RdtSender.h"
#include<queue>

struct packet{
	Packet packet;
	bool flag;
};

class SRRdtSender :public RdtSender
{
private:
	int base;						//����ţ������δȷ�Ϸ�������
	int expectSequenceNumberSend;	// ��һ��������� 
	bool waitingState;				// �Ƿ��ڵȴ�Ack��״̬
	int size;						//���ڴ�С
	int numsize;					//�������
	packet *const slide;			//��������


public:
	void printSlide();									//��ӡ����
	bool getWaitingState();
	bool isInWindow(int seqnum);						//�ж�����Ƿ��ڴ�����
	bool send(const Message &message);					//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet &ackPkt);					//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	SRRdtSender();
	virtual ~SRRdtSender();
};

#endif