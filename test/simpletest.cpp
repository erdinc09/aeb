#include <gtest/gtest.h>

#include "eventbus.h"
#include "eventlistener.h"

class Event {
 public:
  Event(const int& dummy_) : dummy{dummy_} {}
  int getDummy() const { return dummy; }

 private:
  int dummy;
};

class Class1 final : public aeb::EventListener<Event> {
 public:
  Class1(int* changeWithEvent_) : changeWithEvent{changeWithEvent_} {}

 private:
  void handleEvent(const Event& event) override {
    *changeWithEvent = event.getDummy();
  }

  int* changeWithEvent;
};

TEST(SimpleTests, Test1) {
  int changeWithEvent{};
  Class1 class1{&changeWithEvent};
  aeb::postEvent(Event{2});
  ASSERT_TRUE(changeWithEvent == 2);
}

TEST(SimpleTests, Test2) {
  int changeWithEvent1{};
  int changeWithEvent2{};
  Class1 class1{&changeWithEvent1};
  Class1 class2{&changeWithEvent2};
  aeb::postEvent(Event{3});
  ASSERT_TRUE(changeWithEvent1 == 3);
  ASSERT_TRUE(changeWithEvent2 == 3);
}
