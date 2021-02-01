/*
 * Copyright (c) 2020-2021 Ahmet Erdinç Yılmaz -- <ahmeterdinc09@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the  Apache License Version 2.0. Please see the LICENSE file.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 */

#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

using EventListenerList = std::vector<void*>;

namespace aeb {

/*forward decalerations for friends*/
template <class T>
class EventListener;

template <class T>
class EventBus;

template <typename Event>
void postEvent(const Event& event);

namespace internal {
class EventBus_Impl {
 private:
  EventBus_Impl() = default;
  std::unordered_map<int, std::shared_ptr<EventListenerList>> instances;
  static EventBus_Impl globalEventBus;
  static void addEventListener(int id, void* listener);
  static void removeEventListener(int id, void* listener);

  /*friends*/

  template <class T>
  friend class ::aeb::EventListener;

  template <class T>
  friend class ::aeb::EventBus;

  template <typename Event>
  friend void ::aeb::postEvent(const Event& event);
};
}  // namespace internal
}  // namespace aeb
