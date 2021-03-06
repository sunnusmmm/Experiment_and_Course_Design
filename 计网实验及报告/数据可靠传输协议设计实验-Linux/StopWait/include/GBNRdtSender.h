#ifndef GBN_RDT_SENDER_H
#define GBN_RDT_SENDER_H
#include "RdtSender.h"
#include<queue>
class GBNRdtSender :public RdtSender
{
private:
	int base;						//基序号，最早的�?�?认分组的序号
	int expectSequenceNumberSend;	// 下一�?发送序�? 
	int wndsize;					//窗口大小
	int seqsize;					//序号数量
	Packet *const slide;			//滑动窗口

public:
	void printSlide();									//打印窗口
	bool isInWindow(int seqnum);
	bool getWaitingState();
	bool send(const Message &message);					//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确�?认状态而拒绝发送Message，则返回false
	void receive(const Packet &ackPkt);					//接受�?�?Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	GBNRdtSender();
	virtual ~GBNRdtSender();
};

#endif