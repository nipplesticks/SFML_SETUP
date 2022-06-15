#include "EventSubscriber.h"

std::unordered_map<sf::Event::EventType, std::unordered_map<EventSubscriber*, bool>> EventSubscriber::SUBSCRIBERS;

EventSubscriber::EventSubscriber(const EventSubscriber& other)
{
  for (auto& s : other.mySubscriptions)
    Subscribe(s);
}

EventSubscriber::~EventSubscriber()
{
  UnsubscribeAll();
}

void EventSubscriber::Subscribe(sf::Event::EventType eventType)
{
  SUBSCRIBERS[eventType][this] = true;
  mySubscriptions.push_back(eventType);
}

void EventSubscriber::Unsubscribe(sf::Event::EventType eventType)
{
  SUBSCRIBERS[eventType][this] = false;
  SUBSCRIBERS[eventType].erase(this);
}

void EventSubscriber::UnsubscribeAll()
{
  for (auto& e : mySubscriptions)
    Unsubscribe(e);
  mySubscriptions.clear();
}

EventSubscriber& EventSubscriber::operator=(const EventSubscriber& other)
{
  if (this != &other)
  {
    UnsubscribeAll();
    for (auto& s : other.mySubscriptions)
      Subscribe(s);
  }
  return *this;
}
