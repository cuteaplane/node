// Copyright 2012 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Platform-specific code for Haiku goes here. For the POSIX-compatible
// parts, the implementation is in platform-posix.cc.

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>

#include <errno.h>
#include <fcntl.h>
#include <OS.h>
#include <stdarg.h>
#include <strings.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cmath>

#undef MAP_TYPE

#include "src/base/macros.h"
#include "src/base/platform/platform-posix-time.h"
#include "src/base/platform/platform-posix.h"
#include "src/base/platform/platform.h"

namespace v8 {
namespace base {

TimezoneCache* OS::CreateTimezoneCache() {
  return new PosixDefaultTimezoneCache();
}

std::vector<OS::SharedLibraryAddress> OS::GetSharedLibraryAddresses() {
  return {};
}

void OS::SignalCodeMovingGC() {}

void OS::AdjustSchedulingParams() {}

std::vector<OS::MemoryRange> OS::GetFreeMemoryRangesWithin(
    OS::Address boundary_start, OS::Address boundary_end, size_t minimum_size,
    size_t alignment) {
  return {};
}

Stack::StackSlot Stack::ObtainCurrentThreadStackStart() {
  thread_info info;
  status_t status = get_thread_info(find_thread(nullptr), &info);
  if (status == B_OK) {
    return reinterpret_cast<uint8_t*>(info.stack_end);
  }
  return nullptr;
}

}  // namespace base
}  // namespace v8
