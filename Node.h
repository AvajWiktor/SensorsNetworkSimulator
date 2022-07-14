#pragma once
#include "Topic.h"
#include "CircularBuffer.h"
#include <shared_mutex>
#include <mutex>
#include <thread>

//Main node
class Node
{
public:
	Node(size_t bufferSize):_bufferSize(bufferSize){
		_buffer.setBufferSize(_bufferSize);
	};
	~Node() {};
	//Publishing sensor values to circular buffer
	void publishValue(Topic topic) {
		std::unique_lock lock(_mutex);
		_buffer.push(topic);
	}
	std::vector<Topic> getCollectedData() {
		std::unique_lock lock(_mutex);
		// for testing purposes std::cout << "Test" << _buffer[_bufferSize].getMessage()<<std::endl;
		return _buffer.getAllData();
	}

private:
	mutable std::shared_mutex _mutex;
	size_t _bufferSize{};
	CircularBuffer _buffer{0};
};

