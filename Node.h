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
		_buffer = CircularBuffer(bufferSize);
	};
	~Node() {};
	//Publishing sensor values to circular buffer
	void publishValue(Topic topic) {
		std::unique_lock lock(_mutex);
		_buffer.push(topic);
	}
	std::vector<Topic> getCollectedData() {
		return _buffer.getAllData();
	}

private:
	mutable std::shared_mutex _mutex;
	size_t _bufferSize;
	CircularBuffer _buffer;
};
