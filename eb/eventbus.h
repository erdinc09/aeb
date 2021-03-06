/*
 * Copyright (c) 2020-2021 Ahmet Erdinç Yılmaz -- <ahmeterdinc09@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the  Apache License Version 2.0. Please see the LICENSE
 * file.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 */

#pragma once

#include <algorithm>

#include "eventbus_impl.h"
#include "eventlistener.h"

namespace aeb {

template <typename Event>
void postEvent(const Event& event) {
  auto hash = typeid(Event).hash_code();
  auto listenersit =
      internal::EventBus_Impl::globalEventBus.instances.find(hash);
  if (listenersit != internal::EventBus_Impl::globalEventBus.instances.end()) {
    // listenersit->second => std::shared_ptr<std::vector<void*>>
    auto& listenerListForEvent = *listenersit->second;
    for (auto& listener : listenerListForEvent) {
      static_cast<EventListener<Event>*>(listener)->handleEvent(event);
    }
  }
}

}  // namespace aeb
