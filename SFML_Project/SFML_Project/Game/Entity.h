#pragma once
#include "RenderObject.h"

class Entity : public RenderObject
{
public:
  Entity();
  ~Entity();

  void Update(float dt);

};