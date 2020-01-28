
#include "Global.h"
#include "StopWaitRdtSender.h"


StopWaitRdtSender::StopWaitRdtSender():expectSequenceNumberSend(0),waitingState(false)
{
}


StopWaitRdtSender::~StopWaitRdtSender()
{
}



bool StopWaitRdtSender::getWaitingState() {
	return waitingState;
}




bool StopWaitRdtSender::send(const Message &message) {
	if (this->waitingState) { //发送方处于等待�?认状�?
		return false;
	}

	this->packetWaitingAck.acknum = -1; //忽略该字�?
	this->packetWaitingAck.seqnum = this->expectSequenceNumberSend;
	this->packetWaitingAck.checksum = 0;
	memcpy(this->packetWaitingAck.payload, message.data, sizeof(message.data));
	this->packetWaitingAck.checksum = pUtils->calculateCheckSum(this->packetWaitingAck);
	pUtils->printPacket("发送方发送报�?", this->packetWaitingAck);
	pns->startTimer(SENDER, Configuration::TIME_OUT,this->packetWaitingAck.seqnum);			//�?动发送方定时�?
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck);								//调用模拟网络�?境的sendToNetworkLayer，通过网络层发送到对方

	this->waitingState = true;																					//进入等待状�?
	return true;
}

void StopWaitRdtSender::receive(const Packet &ackPkt) {
	if (this->waitingState == true) {//如果发送方处于等待ack的状态，作�?�下处理；否则什么都不做
		//检查校验和�?否�?�确
		int checkSum = pUtils->calculateCheckSum(ackPkt);

		//如果校验和�?�确，并且确认序�?=发送方已发送并等待�?认的数据包序�?
		if (checkSum == ackPkt.checksum && ackPkt.acknum == this->packetWaitingAck.seqnum) {
			this->expectSequenceNumberSend = 1 - this->expectSequenceNumberSend;			//下一�?发送序号在0-1之间切换
			this->waitingState = false;
			pUtils->printPacket("发送方正确收到�?�?", ackPkt);
			pns->stopTimer(SENDER, this->packetWaitingAck.seqnum);		//关闭定时�?
		}
		else {
			pUtils->printPacket("发送方没有正确收到�?认，重发上�?�发送的报文", this->packetWaitingAck);
			pns->stopTimer(SENDER, this->packetWaitingAck.seqnum);									//首先关闭定时�?
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck.seqnum);			//重新�?动发送方定时�?
			pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck);								//重新发送数�?�?

		}
	}	
}

void StopWaitRdtSender::timeoutHandler(int seqNum) {
	//�?一一�?定时�?,无需考虑seqNum
	pUtils->printPacket("发送方定时器时间到，重发上次发送的报文", this->packetWaitingAck);
	pns->stopTimer(SENDER,seqNum);										//首先关闭定时�?
	pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);			//重新�?动发送方定时�?
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck);			//重新发送数�?�?

}
