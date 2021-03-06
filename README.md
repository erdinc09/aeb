# aeb
Another C++ Eventbus implementation.

# Usage

* To register for  event type `Event` just inherit from `public aeb::EventListener<Event>` and implement  `void handleEvent(const Event& event) override ` private.
* To post event type `Event` call `aeb::postEvent<>(Event{1});`.

```cpp
#include <iostream>

#include "eventbus.h"
#include "eventlistener.h"

class Event {
 public:
  Event(const int& dummy_) : dummy{dummy_} {}
  friend std::ostream& operator<<(std::ostream& out, const Event& event) {
    out << event.dummy;
    return out;
  };

 private:
  int dummy;
};

class Class1 final : public aeb::EventListener<Event> {
 private:
  void handleEvent(const Event& event) override {
    std::cout << "called = handleEvent(const Event& event),event= " << event
              << std::endl;
  }
};

int main() {
  auto class1 = new Class1{};
  Class1 class2{};

  aeb::postEvent<>(Event{1});
  aeb::postEvent<>(Event{2});

  delete class1;
  std::cout << std::endl << "after delete class1;" << std::endl << std::endl;

  aeb::postEvent<>(Event{1});
  aeb::postEvent<>(Event{2});
}

```

# Notes:
* Not thread safe!
* Single context is created (static).
* Polymorphic events are __NOT__ supported (yet?).
* Synchronous dispatch only. 
