/**
 * Copyright (C) 2018 David Welch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; only version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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
        std::thread* threadWaitingOn = &threads.front();
        threadWaitingOn->join();
        threads.pop_front();
    }
}

void ThreadPool::StartNewThread() {
    if(threadCount < maxThreads) {
        threadCount++;
        threads.emplace_back(std::thread(TaskCheckLoop));
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
        tasks.emplace_back(std::make_tuple(task, false));
    }

    queueLock.unlock();

    if(!running) {
        Init();
    }
}

bool ThreadPool::LoopLocked() {
    return activeTasksCount > 0 || loopLockCount > 0;
}
