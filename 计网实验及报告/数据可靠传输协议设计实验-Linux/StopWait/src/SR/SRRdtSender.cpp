
#include "Global.h"
#include "SRRdtSender.h"

using namespace std;
//令序号为0~7，窗口大小为4
SRRdtSender::SRRdtSender():base(0),size(4),numsize(8),slide(new packet[8]),expectSequenceNumberSend(0),waitingState(false)
{
	for(int i = 0 ; i < 8 ;i++){
		slide[i].flag = false;
	}
}

SRRdtSender::~SRRdtSender()
{
	delete[] slide;
}


bool SRRdtSender::send(const Message & message)
{
	if (getWaitingState()){//窗口已满，无法继续发送数据
		std::cout << "窗口已满\n";
		return false;
	}
	else
	{
		slide[expectSequenceNumberSend].packet.acknum = -1;//忽略该字段
		slide[expectSequenceNumberSend].packet.seqnum = expectSequenceNumberSend;//序列号
		memcpy(slide[expectSequenceNumberSend].packet.payload, message.data, sizeof(message.data));
		slide[expectSequenceNumberSend].packet.checksum = pUtils->calculateCheckSum(slide[expectSequenceNumberSend].packet);
		pUtils->printPacket("发送方发送报文", slide[expectSequenceNumberSend].packet);
		cout << "发送前窗口：";
		printSlide();
		pns->startTimer(SENDER, Configuration::TIME_OUT, expectSequenceNumberSend);
		pns->sendToNetworkLayer(RECEIVER, slide[expectSequenceNumberSend].packet);
		expectSequenceNumberSend = (expectSequenceNumberSend + 1) % numsize;//计算下一个期望发送包的序号
		cout << "发送后窗口：";
		printSlide();
		return true;
	}
}

//返回是否处于等待状态，窗口满返回true，否则返回false
bool SRRdtSender::getWaitingState()
{
	return (base + size) % numsize == (expectSequenceNumberSend) % numsize;
}

void SRRdtSender::receive(const Packet &ackPkt)
{
	int checksum = pUtils->calculateCheckSum(ackPkt);
	if(checksum == ackPkt.checksum){
		pns->stopTimer(SENDER,ackPkt.acknum);
		if (isInWindow(ackPkt.acknum)){
			slide[ackPkt.acknum].flag = true;
			while (slide[base].flag == true){
				slide[base].flag = false;
				base = (base + 1) % numsize;
			}
			cout << "\n发送方正确收到确认,当前滑动窗口：";
			printSlide();
			cout << endl;
		}
	}else{
		cout << "发送方没有正确收到确认" <<endl;
	}
}

void SRRdtSender::timeoutHandler(int seqNum)
{
	cout << "发送方定时器时间到，重发上次发送的报文:" << endl;
	pns->stopTimer(SENDER,seqNum);													//首先关闭定时器
	pns->startTimer(SENDER, (Configuration::TIME_OUT), seqNum);						//重启定时器，重新计时
	pns->sendToNetworkLayer(RECEIVER,slide[seqNum].packet);
	pUtils->printPacket("重发超时重传的分组:", slide[seqNum].packet);
}

bool SRRdtSender::isInWindow(int seqnum){
	if (base < (base + size) % numsize){
		return seqnum >= base && seqnum < (base + size) % numsize;
	}
	else{
		return seqnum >= base || seqnum < (base + size) % numsize;
	}
}

void SRRdtSender::printSlide()
{
	cout <<"发送方窗口：";
	for (int i = 0; i < numsize; i++){
		if (i == base) cout << "[" ;
		cout << i;
		if(slide[i].flag == true) cout << "_";
		if (i == expectSequenceNumberSend) cout << "*";
		if (i == (base + size - 1) % numsize) cout << "]";
		cout << " ";
	}
	cout << endl;
}