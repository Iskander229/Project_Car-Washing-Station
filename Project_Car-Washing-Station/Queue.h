#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <list>

template <typename T>
class Queue {
private:
    std::list<T> data;

public:
    void enqueue(const T& value) {
        data.push_back(value);
    }

    void dequeue() {
        if (!data.empty()) {
            data.pop_front();
        }
    }

    T front() const {
        if (!data.empty()) {
            return data.front();
        }
        throw std::out_of_range("Queue is empty");
    }

    bool isEmpty() const {
        return data.empty();
    }
};

#endif