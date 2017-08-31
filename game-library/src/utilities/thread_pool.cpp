#include "utilities/thread_pool.h"

bool ThreadPool::running = false;

uint32_t ThreadPool::threadCount = 0;
uint32_t ThreadPool::queueCount = 0;
uint32_t ThreadPool::loopLockCount = 0;
uint32_t ThreadPool::activeTasksCount = 0;
uint32_t ThreadPool::maxThreads = 1;
uint32_t ThreadPool::delayTime = 2;

std::mutex ThreadPool::queueLock, ThreadPool::queueCountLock, ThreadPool::loopLockCountLock, ThreadPool::activeTasksCountLock;

std::list<std::thread> ThreadPool::threads = {};
std::list<std::tuple<std::function<void()>, bool>> ThreadPool::tasks = {};

void ThreadPool::Init() {
    ThreadPool::running = true;
    while(threadCount < maxThreads) {
        StartNewThread();
    }
}

void ThreadPool::Init(uint32_t maxThreads, uint32_t delayTime) {
    ThreadPool::maxThreads = maxThreads;
    ThreadPool::delayTime = delayTime;

    Init();
}

void ThreadPool::TerminateThreads() {
    running = false;
    for(int i = threadCount; i > 0; i--) {
        std::cout << "Killing a thread" << std::endl;
        std::thread* threadWaitingOn = &threads.front();
        threadWaitingOn->join();
        threads.pop_front();
        std::cout << "Thread killed" << std::endl;
    }
}

void ThreadPool::StartNewThread() {
    if(threadCount < maxThreads) {
        threadCount++;
        std::cout << "creating new thread" << std::endl;
        threads.push_back(std::thread(TaskCheckLoop));
    }
}

void ThreadPool::TaskCheckLoop() {
    while(running) {
        queueCountLock.lock();
        if(queueCount == 0) {
            queueCountLock.unlock();
            SDL_Delay(delayTime);
        } else {
            queueCount--;
            queueLock.lock();
            queueCountLock.unlock();
            std::tuple<std::function<void()>, bool> task = tasks.front();
            tasks.pop_front();
            queueLock.unlock();

            bool locksLoop = std::get<1>(task);
            std::function<void()> tasksFunction = std::get<0>(task);

            if(locksLoop) {
                loopLockCountLock.lock();
                loopLockCount--;
                activeTasksCountLock.lock();
                loopLockCountLock.unlock();
                activeTasksCount++;
                activeTasksCountLock.unlock();
            }

            tasksFunction();

            if(locksLoop) {
                activeTasksCountLock.lock();
                activeTasksCount--;
                activeTasksCountLock.unlock();
            }
        }
    }
}

void ThreadPool::AddTask(std::function<void()> task, bool locksLoop) {
    queueCountLock.lock();
    queueCount++;
    queueLock.lock();
    queueCountLock.unlock();

    if(locksLoop) {
        loopLockCountLock.lock();
        loopLockCount++;
        loopLockCountLock.unlock();
        tasks.push_front(std::make_tuple(task, true));
    } else {
        tasks.push_back(std::make_tuple(task, false));
    }

    queueLock.unlock();

    if(!running) {
        Init();
    }
}

bool ThreadPool::LoopLocked() {
    activeTasksCountLock.lock();
    loopLockCountLock.lock();
    bool tasksRunning = activeTasksCount > 0 || loopLockCount > 0;
    activeTasksCountLock.unlock();
    loopLockCountLock.unlock();
    return tasksRunning;
}
