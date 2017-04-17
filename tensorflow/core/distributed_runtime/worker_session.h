/* Copyright 2016 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef THIRD_PARTY_TENSORFLOW_CORE_DISTRIBUTED_RUNTIME_WORKER_SESSION_H_
#define THIRD_PARTY_TENSORFLOW_CORE_DISTRIBUTED_RUNTIME_WORKER_SESSION_H_

#include <string>

#include "tensorflow/core/distributed_runtime/graph_mgr.h"
#include "tensorflow/core/distributed_runtime/rendezvous_mgr_interface.h"
#include "tensorflow/core/distributed_runtime/worker_cache.h"

namespace tensorflow {

class GraphMgr;
class RendezvousMgrInterface;
class WorkerCacheInterface;

// WorkerSession encapsulates all of the state relating to a given session.
struct WorkerSession {
  // The name of the worker. E.g., /job:mnist/replica:0/task:1.
  const string worker_name;

  // Object from which WorkerInterface instances can be obtained.
  const std::unique_ptr<WorkerCacheInterface> worker_cache;

  // A set of rendezvous keyed by step ids.
  const std::unique_ptr<RendezvousMgrInterface> rendezvous_mgr;

  // graph_mgr keeps track of the registered graphs of this session.
  //
  // Note: graph_mgr must be deleted before rendezvous_mgr!
  const std::unique_ptr<GraphMgr> graph_mgr;

  WorkerSession(const string& worker_name,
                std::unique_ptr<WorkerCacheInterface> worker_cache,
                std::unique_ptr<RendezvousMgrInterface> rendezvous_mgr,
                std::unique_ptr<GraphMgr> graph_mgr);
};

}  // namespace tensorflow

#endif  // THIRD_PARTY_TENSORFLOW_CORE_DISTRIBUTED_RUNTIME_WORKER_SESSION_H_
