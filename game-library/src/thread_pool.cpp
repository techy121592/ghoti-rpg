#include "thread_pool.h"

bool ThreadPool::running = false;

uint32_t ThreadPool::threadCount = 0;
uint32_t ThreadPool::queueCount = 0;
uint32_t ThreadPool::activeTasksCount = 0;
uint32_t ThreadPool::maxThreads = 1;
uint32_t ThreadPool::delayTime = 2;

std::mutex ThreadPool::queueLock, ThreadPool::queueCountLock, ThreadPool::activeTasksCountLock, ThreadPool::runningLock;

std::list<std::thread> ThreadPool::threads = {};
std::list<std::function<void()>> ThreadPool::tasks = {};

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
    runningLock.lock();
    running = false;
    runningLock.unlock();
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
    runningLock.lock();
    while(running) {
        runningLock.unlock();
        queueCountLock.lock();
        if(queueCount == 0) {
            queueCountLock.unlock();
            SDL_Delay(delayTime);
        } else {
            queueCount--;
            queueLock.lock();
            queueCountLock.unlock();
            std::function<void()> task = tasks.front();
            tasks.pop_front();
            activeTasksCountLock.lock();
            queueLock.unlock();
            activeTasksCount++;
            activeTasksCountLock.unlock();

            task();

            activeTasksCountLock.lock();
            activeTasksCount--;
            activeTasksCountLock.unlock();
        }
        runningLock.lock();
    }
    runningLock.unlock();
}

void ThreadPool::AddTask(std::function<void()> task) {
    queueLock.lock();
    tasks.push_back(task);
    queueLock.unlock();

    queueCountLock.lock();
    queueCount++;
    queueCountLock.unlock();

    if(!running) {
        Init();
    }
}

bool ThreadPool::TasksRunning() {
    activeTasksCountLock.lock();
    queueCountLock.lock();
    bool tasksRunning = activeTasksCount > 0 || queueCount > 0;
    activeTasksCountLock.unlock();
    queueCountLock.unlock();
    return tasksRunning;
}
