#pragma once

class BaseFunction
{
public:
  virtual ~BaseFunction() = default;
  virtual void Run() = 0;
  virtual size_t ByteSize() = 0;
};

template <typename F>
class Function : public BaseFunction
{
public:
  Function(F function) : myFunction(function) {}
  virtual void Run() { myFunction();}
  virtual size_t ByteSize() { return sizeof(*this); }
  
  F myFunction;
};

template <typename F, typename A>
class FunctionWithArgs : public BaseFunction
{
public:
  FunctionWithArgs(F function, A arguments) : myFunction(function), myArgs(arguments) {}
  virtual void Run() { myFunction(myArgs); }
  virtual size_t ByteSize() { return sizeof(*this); }
  
  F myFunction;
  A myArgs;
};

template <typename C>
class MemberFunction : public BaseFunction
{
public:
  MemberFunction(void(C::* function)(), C* object) : myFunction(function), myObject(object) {}
  virtual void Run() { (myObject->*myFunction)(); }
  virtual size_t ByteSize() { return sizeof(*this); }

  void(C::* myFunction)();
  C* myObject;
};

template <typename C, typename A>
class MemberFunctionWithArgs : public BaseFunction
{
public:
  MemberFunctionWithArgs(void(C::* function)(A), C* object, A arguments) : myFunction(function), myObject(object), myArgs(arguments) {}
  virtual void Run() { (myObject->*myFunction)(myArgs); }
  virtual size_t ByteSize() { return sizeof(*this); }

  void(C::* myFunction)(A);
  C* myObject;
  A myArgs;
};