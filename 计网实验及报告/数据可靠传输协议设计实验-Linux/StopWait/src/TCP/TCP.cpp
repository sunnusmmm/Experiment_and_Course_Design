// TCP.cpp : 定义控制台应用程序的入口点�?
//


#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "TCPRdtReceiver.h"
#include "TCPRdtSender.h"


int main(int argc, char* argv[])
{
	RdtSender *ps = new TCPRdtSender();
	RdtReceiver * pr = new TCPRdtReceiver();
	// pns->setRunMode(0);  //VERBOS模式
	pns->setRunMode(1);  //安静模式
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("/mnt/hgfs/ubuntn/Ubuntu_18.04.3_64_Desktop/input.txt");
	pns->setOutputFile("/mnt/hgfs/ubuntn/Ubuntu_18.04.3_64_Desktop/output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;									//指向�??一的工具类实例，只在main函数结束前delete
	delete pns;										//指向�??一的模拟网络环境类实例，只在main函数结束前delete
	
	return 0;
}

