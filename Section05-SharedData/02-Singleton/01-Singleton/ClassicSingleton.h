/*
  Singleton class definition
  It has the error of being initializing multiple times
*/ 
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton
{
private:
  // Pointer to unique instance
  static Singleton* single;

  // Private default constructor
  Singleton() 
  {
    std::cout << "Initializing Singleton" << "\n";
  }
public:
  // Deep copy constructor and copy assignment operator are deleted
  Singleton(const Singleton &) = delete;
  Singleton& operator=(const Singleton &) = delete;

  // Move constructor and move assignment operator are deleted
  Singleton(Singleton &&) = delete;
  Singleton& operator=(Singleton &&) = delete;

  // Static member function to obtain the Singleton object
  static Singleton* getSingleton();
};
#endif