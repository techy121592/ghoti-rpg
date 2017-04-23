#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <list>
#include <mutex>
#include <iostream>
#include <SDL.h>

class ThreadPool {
private:
    static bool running;
    static uint32_t threadCount, queueCount, activeTasksCount, maxThreads, delayTime;
    static std::mutex queueLock, queueCountLock, activeTasksCountLock, runningLock;

    static std::list<std::thread> threads;
    static std::list<std::function<void()>> tasks;

    static void TaskCheckLoop();
    static void StartNewThread();
public:
    static void Init();
    static void Init(uint32_t maxThreads, uint32_t delayTime);
    static void TerminateThreads();
    static void AddTask(std::function<void()> task);
    static bool TasksRunning();
};

#endif
