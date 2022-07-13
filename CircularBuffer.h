#pragma once
#include <vector>
#include "Topic.h"
#include <optional>

//My implementation of circular buffer with given size
class CircularBuffer
{
public:
	CircularBuffer(size_t bufferCapacity):_bufferCapacity(bufferCapacity){}
	
	void push(Topic t) {
		_buffer.emplace_back(t);
		if (_buffer.size() > _bufferCapacity) {
			_buffer.erase(_buffer.begin());
		}
	}
	std::optional<Topic> getElement(size_t n) {
		if (_buffer.size() < n) {
			return _buffer[n];
		}
		return {};
	}
	void printValues() {
		for (size_t i = 0; i < _buffer.size();i++) {
			std::cout<<"["<<i<<"]"<< _buffer[i].getMessage() << std::endl;
		}
	}
	std::vector<Topic> getAllData() {
		return _buffer;
	}
	void setBufferSize(size_t size){
	_bufferCapacity = size;
	}
private:
	std::vector<Topic> _buffer;
	size_t _bufferCapacity;
};

