#include "Global.h"
#include "TCPRdtReceiver.h"

TCPRdtReceiver::TCPRdtReceiver():base(0),size(4),slide(new receiverPacket[8]),numsize(8)
{
	for(int i = 0 ; i < 8 ;i++){
		slide[i].flag = false;
	}
	lastAckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//忽略该字段
	for(int i = 0; i < Configuration::PAYLOAD_SIZE;i++){
		lastAckPkt.payload[i] = '.';
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

TCPRdtReceiver::~TCPRdtReceiver()
{
	delete[] slide;
}

void TCPRdtReceiver::receive(const Packet &packet) {
int checksum = pUtils->calculateCheckSum(packet);
	if (checksum == packet.checksum){
		if(isInWindow(packet.seqnum)){
			slide[packet.seqnum].packet = packet;
			slide[packet.seqnum].flag = true;
			while (slide[base].flag == true){
				//取出Message，向上递交给应用层
				Message msg;
				memcpy(msg.data, slide[base].packet.payload, sizeof(slide[base].packet.payload));
				pns->delivertoAppLayer(RECEIVER, msg);
				slide[base].flag = false;
				base = (base + 1) % numsize;
			}
			lastAckPkt.acknum = base;
			lastAckPkt.seqnum = packet.acknum;
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("接收方发送确认报文", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
			cout << "\n接收后当前窗口：";
			printSlide();
			cout << endl;
		}else{
			pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
			lastAckPkt.acknum = base;
			lastAckPkt.seqnum = -1;
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
		}
	}else{
		pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		lastAckPkt.acknum = base;
		lastAckPkt.seqnum = -1;
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
	}
}

bool TCPRdtReceiver::isInWindow(int seqnum){
	if (base < (base + size) % numsize){
		return seqnum >= base && seqnum < (base + size) % numsize;
	}
	else{
		return seqnum >= base || seqnum < (base + size) % numsize;
	}
}

void TCPRdtReceiver::printSlide(){
	cout << "接收方窗口：";
	for (int i = 0; i < numsize; i++){
		if (i == base) cout << "[" ;
		cout << i;
		if(slide[i].flag) cout << "*";
		if (i == (base + size - 1) % numsize) cout << "]";
		cout << " ";
	}
	cout << endl;
}