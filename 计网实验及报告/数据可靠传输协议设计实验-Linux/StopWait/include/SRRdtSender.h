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
	int base;						//基序号，最早的未确认分组的序号
	int expectSequenceNumberSend;	// 下一个发送序号 
	bool waitingState;				// 是否处于等待Ack的状态
	int size;						//窗口大小
	int numsize;					//序号数量
	packet *const slide;			//滑动窗口


public:
	void printSlide();									//打印窗口
	bool getWaitingState();
	bool isInWindow(int seqnum);						//判断序号是否在窗口中
	bool send(const Message &message);					//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet &ackPkt);					//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	SRRdtSender();
	virtual ~SRRdtSender();
};

#endif