#include "EventSubscriber.h"
#include <iostream>

std::unordered_map<sf::Event::EventType, std::unordered_map<uint64_t, EventSubscriber*>> EventSubscriber::SUBSCRIBERS;

EventSubscriber::EventSubscriber()
{
  myId = _generateId();
}

EventSubscriber::EventSubscriber(const EventSubscriber& other)
{
  myId = _generateId();
  for (auto& s : other.mySubscriptions)
    if (s.second) Subscribe(s.first);
}

EventSubscriber::~EventSubscriber()
{
  UnsubscribeAll();
}

void EventSubscriber::Subscribe(sf::Event::EventType eventType)
{
  SUBSCRIBERS[eventType][myId] = this;
  mySubscriptions[eventType] = true;
}

void EventSubscriber::Unsubscribe(sf::Event::EventType eventType)
{
  SUBSCRIBERS[eventType][myId] = nullptr;
  mySubscriptions[eventType] = false;
}

void EventSubscriber::UnsubscribeAll()
{
  for (auto& e : mySubscriptions)
    if (e.second) Unsubscribe(e.first);

  mySubscriptions.clear();
}

EventSubscriber& EventSubscriber::operator=(const EventSubscriber& other)
{
  if (this != &other)
  {
    UnsubscribeAll();
    myId = _generateId();
    for (auto& s : other.mySubscriptions)
      if (s.second) Subscribe(s.first);
  }
  return *this;
}

uint64_t EventSubscriber::_generateId()
{
  static uint64_t currentId = 0;
  return currentId++;
}
