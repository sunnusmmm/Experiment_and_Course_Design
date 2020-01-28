#include "Global.h"
#include "GBNRdtSender.h"

using namespace std;
//令序号为0~7，窗口大小为4
GBNRdtSender::GBNRdtSender():slide(new Packet[8]),expectSequenceNumberSend(0)
{
	seqsize = 8;
	wndsize = 4;
	base = 0;
}

GBNRdtSender::~GBNRdtSender()
{
	delete[] slide;
}

bool GBNRdtSender::send(const Message & message)
{
	if (getWaitingState()){//窗口已满，无法继�?发送数�?
		std::cout << "窗口已满\n";
		return false;
	}
	else
	{
		slide[expectSequenceNumberSend].acknum = -1;//忽略该字�?
		slide[expectSequenceNumberSend].seqnum = expectSequenceNumberSend;//序列�?
		memcpy(slide[expectSequenceNumberSend].payload, message.data, sizeof(message.data));
		slide[expectSequenceNumberSend].checksum = pUtils->calculateCheckSum(slide[expectSequenceNumberSend]);
		pUtils->printPacket("发送方发送报文：", slide[expectSequenceNumberSend]);
		cout << "发送前窗口："; 
		printSlide();
		if (base == expectSequenceNumberSend){								//窗口�?所有包都没有发�?
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
		pns->sendToNetworkLayer(RECEIVER, slide[expectSequenceNumberSend]);
		expectSequenceNumberSend = (expectSequenceNumberSend + 1) % seqsize;//计算下一�?期望发送包的序�?
		cout << "发送后窗口：";
		printSlide();
		return true;
	}
}

//返回�?否�?�于等待状态，窗口满返回true，否则返回false
bool GBNRdtSender::getWaitingState()
{
	return (base + wndsize) % seqsize == (expectSequenceNumberSend) % seqsize;
}

void GBNRdtSender::receive(const Packet &ackPkt)
{
	int checkSum = pUtils->calculateCheckSum(ackPkt);
	if (checkSum == ackPkt.checksum){
		if(isInWindow(ackPkt.acknum)){
			base = (ackPkt.acknum + 1) % seqsize;
			if (base == expectSequenceNumberSend){
				pns->stopTimer(SENDER, 0);
			}else{
				pns->stopTimer(SENDER, 0);
				pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
			}
			cout << "发送方正确收到确认,当前滑动窗口：";
			printSlide();
			cout << endl;
		}else{
			cout<<"确认不在窗口内"<<endl;
		}
	}else{
		cout << "发送方没有正确收到确认" <<endl;
	}
}

bool GBNRdtSender::isInWindow(int seqnum){
	if (base < (base + wndsize) % seqsize){
		return seqnum >= base && seqnum < (base + wndsize) % seqsize;
	}
	else{
		return seqnum >= base || seqnum < (base + wndsize) % seqsize;
	}
}

void GBNRdtSender::timeoutHandler(int seqNum)
{
	cout << "发送方定时器时间到，重发上次发送的报文:" << endl;
	pns->stopTimer(SENDER,seqNum);													//首先关闭定时�?
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);						//重启定时�?，重新�?�时
	for (int i = base; i != expectSequenceNumberSend; i = (i + 1) % seqsize){		//重新发送已发送的所有包
		pns->sendToNetworkLayer(RECEIVER, slide[i]);
		pUtils->printPacket("重发超时重传的分组：", slide[i]);
	}
}

void GBNRdtSender::printSlide()
{
	for (int i = 0; i < seqsize; i++){
		if (i == base) cout << "[" ;
		cout << i;
		if (i == expectSequenceNumberSend) cout << "*";
		if (i == (base + wndsize - 1) % seqsize) cout << "]";
		cout << " ";
	}
	cout << endl;
}