// Copyright 2021 kosirev <qw01w@yandex.ru>

#include <header.hpp>
#include <random>

void Cache::CacheSizes() {
  sizes[0] = min / 2;
  for (int n = 1, i = 1; n < max * 1.5; n *= 2, ++i) {
    sizes[i] = n;
  }
  sizes[5] = max * 1.5;
}

void Cache::Warming(int* arrayToWarm, size_t size) {
  [[maybe_unused]] int k;
  for (size_t i = 0; i < size; ++i) {
    k = arrayToWarm[i];
  }
}
int* Cache::GenerateArray(size_t bufferSize) {
  int* generatedArray = new int[bufferSize];
  for (size_t i = 0; i < bufferSize; ++i) {
    generatedArray[i] = rand() % 100;
  }
  return generatedArray;
}

void Cache::StraightExperiment() {
  double time[6];
  for (int i = 0; i < 6; i++) {
    size_t bufferSize = (sizes[i] * 1024 * 1024) / 4;
    int* array = GenerateArray(bufferSize);
    Warming(array, bufferSize);
    [[maybe_unused]] int k;
    auto start = std::chrono::system_clock::now();
    for (size_t j = 0; j < bufferSize * quantity; j += step) {
      k = array[j % 1000];
    }
    auto end = std::chrono::system_clock::now();
    time[i] = (static_cast<double>(
        std::chrono::nanoseconds((end - start) / quantity).count()));
    delete[] array;
  }
  for (int j = 0; j < 6; ++j) {
    straightTimes[j] = time[j];
  }
}

void Cache::BackExperiment() {
  double time[6];
  for (int i = 0; i < 6; i++) {
    size_t bufferSize = (sizes[i] * 1024 * 1024) / 4;
    int* array = GenerateArray(bufferSize);
    Warming(array, bufferSize);
    [[maybe_unused]] int k;
    auto start = std::chrono::system_clock::now();
    for (size_t j = bufferSize * quantity; j > 0; j -= step) {
      k = array[j % 1000];
    }
    auto end = std::chrono::system_clock::now();
    time[i] = (static_cast<double>(
        std::chrono::nanoseconds((end - start) / quantity).count()));
    delete[] array;
  }
  for (int j = 0; j < 6; ++j) {
    backTimes[j] = time[j];
  }
}

void Cache::RandomExperiment() {
  double time[6];
  for (int i = 0; i < 6; i++) {
    size_t bufferSize = (sizes[i] * 1024 * 1024) / 4;
    int* array = GenerateArray(bufferSize);
    std::vector<size_t>::iterator start, end;
    std::vector<size_t> arr;
    for (size_t j = 0; j < bufferSize; j += step) arr.emplace_back(j);
    start = arr.begin();
    end = arr.end();
    shuffle(start, end, std::mt19937(std::random_device()()));
    Warming(array, bufferSize);
    auto startTime = std::chrono::high_resolution_clock::now();
    [[maybe_unused]] int k;
    for (size_t j = 0; j < bufferSize * quantity; j += step) {
      k = array[j % 1000];
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    time[i] = (static_cast<double>(
        std::chrono::nanoseconds((endTime - startTime) / 1000).count()));
    delete[] array;
  }
  for (int j = 0; j < 6; ++j) {
    randomTimes[j] = time[j];
  }
}

void Cache::Print(std::ostream& os) {
  using std::endl;
  for (size_t i = 0; i < 3; ++i) {
    os << "Invistigations: " << endl
       << "     travel_variant: " << variant[i] << endl
       << "     experiments: " << std::endl;
    for (size_t j = 0, c = 0; j < 6; ++j, ++c) {
      os << "           -experiment:" << endl <<
         "           number: " << j + 1 << endl
         << "      input_data: " << endl
         << "            buffer_size: " << sizes[j] << " mb" << endl
         << "      results: " << endl
         << "            duration: ";
      WhatTimeCorrect(i, j);
      os << " nanoseconds" << std::endl;
    }
  }
}

void Cache::WhatTimeCorrect(int i, int j) {
  using std::cout;
  switch (i) {
    case 0:
      cout << straightTimes[j];
      break;
    case 1:
      cout << backTimes[j];
      break;
    case 2:
      cout << randomTimes[j];
      break;
  }
}
