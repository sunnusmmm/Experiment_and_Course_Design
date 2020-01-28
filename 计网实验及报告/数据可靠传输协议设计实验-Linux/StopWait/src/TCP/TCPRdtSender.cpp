#include "Global.h"
#include "TCPRdtSender.h"

using namespace std;
//令序号为0~7，窗口大小为4
TCPRdtSender::TCPRdtSender():acknum(0),revack(0),slide(new Packet[8]),expectSequenceNumberSend(0),waitingState(false)
{
	seqsize = 8;
	wndsize = 4;
	base = 0;
}

TCPRdtSender::~TCPRdtSender()
{
	delete[] slide;
}

bool TCPRdtSender::send(const Message & message)
{
	if (getWaitingState()){//窗口已满，无法继续发送数据
		std::cout << "窗口已满\n";
		return false;
	}
	else
	{
		slide[expectSequenceNumberSend].acknum = -1;//忽略该字段
		slide[expectSequenceNumberSend].seqnum = expectSequenceNumberSend;//序列号
		memcpy(slide[expectSequenceNumberSend].payload, message.data, sizeof(message.data));
		slide[expectSequenceNumberSend].checksum = pUtils->calculateCheckSum(slide[expectSequenceNumberSend]);
		pUtils->printPacket("发送方发送报文", slide[expectSequenceNumberSend]);
		cout << "发送前窗口："; 
		printSlide();
		if (base == expectSequenceNumberSend){								//窗口中所有包都没有发送
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
		pns->sendToNetworkLayer(RECEIVER, slide[expectSequenceNumberSend]);
		expectSequenceNumberSend = (expectSequenceNumberSend + 1) % seqsize;//计算下一个期望发送包的序号
		cout << "发送后窗口：";
		printSlide();
		return true;
	}
}

//返回是否处于等待状态，窗口满返回true，否则返回false
bool TCPRdtSender::getWaitingState()
{
	return (base + wndsize) % seqsize == (expectSequenceNumberSend) % seqsize;
}

void TCPRdtSender::receive(const Packet &ackPkt)
{
	int checkSum = pUtils->calculateCheckSum(ackPkt);
	if (checkSum == ackPkt.checksum){
		
        if(acknum == ackPkt.acknum){
            revack++;
			cout << "收到冗余确认ACK:" << acknum << "->" << revack <<endl;
            if(revack == 3){
				revack = 0;
				pUtils->printPacket("快速重传的分组:", slide[base]);
                pns->sendToNetworkLayer(RECEIVER, slide[base]);
            }
        }else{
            acknum = ackPkt.acknum;
            revack = 0;
        }
		if(isInWindow(ackPkt.acknum - 1)){
		base = (ackPkt.acknum) % seqsize;
		if (base == expectSequenceNumberSend){
			pns->stopTimer(SENDER, 0);
		}
        // else{
		// 	pns->stopTimer(SENDER, 0);
		// 	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		// }
		cout << "发送方正确收到确认,当前滑动窗口：";
		printSlide();
		cout << endl;
		}
	}else{
		cout << "发送方没有正确收到确认" <<endl;
	}
}

void TCPRdtSender::timeoutHandler(int seqNum)
{
	revack = 0;
	cout << "发送方定时器时间到，重发上次发送的报文:" << endl;
	pns->stopTimer(SENDER,seqNum);													//首先关闭定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);						//重启定时器，重新计时
	pns->sendToNetworkLayer(RECEIVER, slide[base]);
	pUtils->printPacket("重发超时重传的分组:", slide[base]);
}

bool TCPRdtSender::isInWindow(int seqnum){
	if (base < (base + wndsize) % seqsize){
		return seqnum >= base && seqnum < (base + wndsize) % seqsize;
	}
	else{
		return seqnum >= base || seqnum < (base + wndsize) % seqsize;
	}
}

void TCPRdtSender::printSlide()
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