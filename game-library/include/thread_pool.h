#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <list>
#include <mutex>
#include <iostream>
#include <SDL.h>

class ThreadPool {
private:
    const static uint32_t maxThreads = 4;
    const static uint32_t delayTime = 1;

    static bool running;
    static uint32_t threadCount, queueCount, activeTasksCount;
    static std::mutex queueLock, queueCountLock, activeTasksCountLock, runningLock;

    static std::list<std::thread> threads;
    static std::list<std::function<void()>> tasks;

    static void TaskCheckLoop();
    static void StartNewThread();
public:
    static void Init();
    static void TerminateThreads();
    static void AddTask(std::function<void()> task);
    static bool TasksRunning();
};

#endif
