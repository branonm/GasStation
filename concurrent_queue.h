// This implementation of a concurrent queue is heavily influenced by
// https://gist.github.com/vladimirgamalyan/9f24df88de7de6b242ab17e64688d897

#pragma once
#include <queue>
#include <mutex>

// simple thread-safe multiple producer, multiple consumer queue
template<typename T>
class concurrent_queue
{
public:
    void push(T const& v)
    {
        the_mutex.lock();
        the_queue.push(v);
        the_mutex.unlock();
        the_condition_variable.notify_one();
    }

    bool empty()
    {
        bool the_return = false;
        the_mutex.lock();
        the_return = the_queue.empty();
        the_mutex.unlock();
        return the_return;
    }

    bool try_pop(T& popped_value)
    {
        bool the_return = false;
        the_mutex.lock();
        if (!the_queue.empty()) {
            the_return = true;
            popped_value = the_queue.front();
            the_queue.pop();
        }
        the_mutex.unlock();

        return the_return;
    }

private:
    std::queue<T> the_queue;
    std::mutex the_mutex;
    std::condition_variable the_condition_variable;
};