// Copyright 2021 kosirev <qw01w@yandex.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <chrono>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::ostream;
using std::string;
using std::stringstream;

class Cache {
  double straightTimes[6];
  double backTimes[6];
  double randomTimes[6];

  string variant[3] = {"straight", "back", "random"};

 public:
  void CacheSizes();
  void Warming(int* arrayToWarm, size_t size);
  void StraightExperiment();
  void BackExperiment();
  void RandomExperiment();
  int* GenerateArray(size_t bufferSize);
  void Print(std::ostream& os);
  void WhatTimeCorrect(int i, int j);

 private:
  double sizes[6];

  const double min = 0.256;
  const double max = 8;
  const int step = 16;
  const int quantity = 1000;
};

#endif // INCLUDE_HEADER_HPP_
