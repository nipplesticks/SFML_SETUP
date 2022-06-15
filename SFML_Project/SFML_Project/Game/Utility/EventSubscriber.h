#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class EventSubscriber
{
public:
  static std::unordered_map<sf::Event::EventType, std::unordered_map<EventSubscriber*, bool>> SUBSCRIBERS;

  EventSubscriber() = default;
  EventSubscriber(const EventSubscriber& other);

  virtual ~EventSubscriber();
  void Subscribe(sf::Event::EventType eventType);
  void Unsubscribe(sf::Event::EventType eventType);
  void UnsubscribeAll();
  virtual void OnEvent(const sf::Event& e) = 0;
  EventSubscriber& operator=(const EventSubscriber& other);

protected:
  std::vector<sf::Event::EventType> mySubscriptions;
};