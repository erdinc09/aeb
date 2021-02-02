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
#include <typeinfo>

#include "eventbus_impl.h"

namespace aeb {

template <typename Event>
class EventListener {
 public:
  EventListener() {
    internal::EventBus_Impl::addEventListener(typeid(Event).hash_code(), this);
  }
  ~EventListener() {
    internal::EventBus_Impl::removeEventListener(typeid(Event).hash_code(),
                                                 this);
  }

 private:
  virtual void handleEvent(const Event& event) = 0;

  /*friends*/
  template <typename T>
  friend class EventBus;

  template <typename Event_>
  friend void postEvent(const Event_& event);
};
}  // namespace aeb
