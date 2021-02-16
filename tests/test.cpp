// Copyright 2021 kosirev <qw01w@yandex.ru>
#include <header.hpp>
#include <gtest/gtest.h>

TEST(Example, EmptyTest) {
    Cache experiments;
  experiments.CacheSizes();
  experiments.StraightExperiment();
  experiments.BackExperiment();
  experiments.RandomExperiment();
  experiments.Print(std::cout);
}
