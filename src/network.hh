#pragma once
#include "layer.hh"
#include <iostream>
#include <cmath>

namespace NeuralNetwork
{

  class Network
  {
  public:

    Network(std::vector<size_t> lsize);

    void forward();

    void backPropagate(std::vector<double> target);

    void learn(std::vector<double> input, std::vector<double> target);

    void print();

    double error();

    Layer operator[](size_t i) { return layers[i]; }

  private:

    std::vector<Layer> layers;
  };

  #include "network.hxx"
}
