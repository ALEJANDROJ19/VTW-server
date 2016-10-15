// MainCore.cpp: define el punto de entrada de la aplicación de consola.
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>
//boost
#include <boost\atomic.hpp>
#include <boost\lockfree\spsc_queue.hpp>
#include <boost\thread\thread.hpp>
//threads
#include "..\UdpReceiver\UDPReceiveServer.h"
//coder
//catcher

#pragma once
#define _BUFFERSIZE 1024
boost::atomic<bool> _Finish(false);
boost::lockfree::spsc_queue<int, boost::lockfree::capacity<_BUFFERSIZE> > _Buffer;

/*START of DEBUG Functions*/
//#######################//
int producer_count = 0;
boost::atomic_int consumer_count(0);
const int iterations = 10000000;

void producer(void)
{
	for (int i = 0; i != iterations; ++i) {
		int value = ++producer_count;
		while (!_Buffer.push(value))
			;
	}
}

boost::atomic<bool> done(false);

void consumer(void)
{
	int value;
	while (!done) {
		while (_Buffer.pop(value))
			++consumer_count;
	}

	while (_Buffer.pop(value))
		++consumer_count;
}
//#######################//
/*END of DEBUG Functions*/

//UDP main thread
void UdpReceiverThread(void) {
	//create classes
	char* argv_UDP[1];
	int argc_UDP = 1;
	//init argv
	UDPReceiveServer _UdpReceiver(argc_UDP, argv_UDP);
	_UdpReceiver.StartServer();
}

//VPX main thread
void VpxCoderThread() {
	char* argv_DX[1];
	int argc_DX = 1;
	//init argv
	//new DX
}

//DX main thread
void DXCatcherThread(void) {
	char* argv_VPX[1];
	int argc_VPX = 1;
	//init argv
	//new vpc
}

int main()
{
	/*DEBUG funtions
	using namespace std;
	cout << "boost::lockfree::queue is ";
	if (!_Buffer.is_lock_free())
		cout << "not ";
	cout << "lockfree" << endl;

	boost::thread producer_thread(producer);
	boost::thread consumer_thread(consumer);

	producer_thread.join();
	done = true;
	consumer_thread.join();

	cout << "produced " << producer_count << " objects." << endl;
	cout << "consumed " << consumer_count << " objects." << endl;
	/**/

	/*RELEASE*/
	//DEBUG test is Buffer is lock free
	std::cout << "boost::lockfree::queue is ";
	if (!_Buffer.is_lock_free())
	std::cout << "not ";
	std::cout << "lockfree" << std::endl;

	//create threads
	boost::thread UdpReceiver(UdpReceiverThread);
	boost::thread DXCatcher(VpxCoderThread);
	boost::thread VpxCoder(DXCatcherThread);

	//join threads
	UdpReceiver.join();
	DXCatcher.join();
	VpxCoder.join();

	//DEBUG test end
	std::cout << "Done" << std::endl;
	int pause;
	std::cin >> pause;
	/**/
}

