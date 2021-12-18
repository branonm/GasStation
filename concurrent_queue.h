// This implementation of a concurrent queue is taken from
// https://gist.github.com/vladimirgamalyan/9f24df88de7de6b242ab17e64688d897

#pragma once
#include <queue>
#include <boost/thread.hpp>

// simple thread-safe multiple producer, multiple consumer queue
template<typename T>
class concurrent_queue
{
public:
    void push(T const& v)
    {
        boost::mutex::scoped_lock lock(the_mutex);
        the_queue.push(v);
        lock.unlock();
        the_condition_variable.notify_one();
    }

    bool empty() const
    {
        boost::mutex::scoped_lock lock(the_mutex);
        return the_queue.empty();
    }

    bool try_pop(T& popped_value)
    {
        boost::mutex::scoped_lock lock(the_mutex);
        if (the_queue.empty())
            return false;
        popped_value = the_queue.front();
        the_queue.pop();
        return true;
    }

    void wait_and_pop(T& popped_value)
    {
        boost::mutex::scoped_lock lock(the_mutex);
        while (the_queue.empty())
            the_condition_variable.wait(lock);
        popped_value = the_queue.front();
        the_queue.pop();
    }
private:
    std::queue<T> the_queue;
    mutable boost::mutex the_mutex;
    boost::condition_variable the_condition_variable;
};