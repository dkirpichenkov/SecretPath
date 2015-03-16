/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef THREADCALLSTACKPROFILER_H
#define THREADCALLSTACKPROFILER_H

#include "abstracttracingprofiler.h"
#include <unordered_map>

#include <string>

using namespace std;

struct ThreadControl final {
  unordered_map<unsigned long, CallStatistics *> roots;
  CallStatistics *current;
  
  ThreadControl():current(nullptr){};
};

class ThreadCallStackProfiler : public AbstractTracingProfiler
{
public:
  ThreadCallStackProfiler();
  
  virtual void setData(AgentRuntime *runtime, JavaClassesInfo *classes, JavaThreadsInfo *threads) final;
  
  virtual void methodEntry(int cnum, int mnum, jobject thread) override;
  virtual void methodExit(int cnum, int mnum, jobject thread) override;
  virtual void printOnExit() override;
  
  virtual void methodInstrumented(JavaMethodInfo *info) override;
  virtual void threadStarted(jobject thread);
  virtual void threadStopped(jobject thread);
  
  virtual void reset() override final;
  virtual string printCsv() override final;
  
private:
  int maxDepth;
  unordered_map<pthread_t, ThreadControl*> statByThread;
};

#endif // THREADCALLSTACKPROFILER_H
