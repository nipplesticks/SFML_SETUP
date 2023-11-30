#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class EventSubscriber
{
public:
  static std::unordered_map<sf::Event::EventType, std::unordered_map<uint64_t, EventSubscriber*>> SUBSCRIBERS;
  
  EventSubscriber();
  EventSubscriber(const EventSubscriber& other);

  virtual ~EventSubscriber();
  void Subscribe(sf::Event::EventType eventType);
  void Unsubscribe(sf::Event::EventType eventType);
  void UnsubscribeAll();
  virtual void OnEvent(const sf::Event& e) = 0;
  EventSubscriber& operator=(const EventSubscriber& other);

protected:
  std::unordered_map<sf::Event::EventType, bool> mySubscriptions;

private:
  static uint64_t _generateId();
  uint64_t myId = 0;
};