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

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <functional>
#include <mutex>
#include <vector>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <SDL2/SDL.h>

class ThreadPool {
private:
    static bool running;
    static uint32_t threadCount, queueCount, loopLockCount, activeTasksCount, maxThreads, delayTime;
    static std::mutex queueLock, queueCountLock, loopLockCountLock, activeTasksCountLock;

    static std::vector<std::thread> threads;
    static std::vector<std::tuple<std::function<void()>, bool>> tasks;

    static void TaskCheckLoop();
    static void StartNewThread();
public:
    static void Init();
    static void Init(uint32_t maxThreads, uint32_t delayTime);
    static void TerminateThreads();
    static void AddTask(const std::function<void()>& task, bool locksLoop);
    static bool LoopLocked();
};

#endif
