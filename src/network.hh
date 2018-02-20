#pragma once
#include "layer.hh"

namespace NeuralNetwork
{

  class Network
  {
  public:

    Network(std::vector<size_t> lsize);
    Network(const std::string& path);

    void forward();

    void backPropagate(std::vector<double> target);

    void learn(std::vector<double> input, std::vector<double> target);

    void print();

    double error();

    size_t size() { return layers.size(); }

    void save(const std::string& path);

    Layer operator[](size_t i) { return layers[i]; }

  private:

    std::vector<Layer> layers;
  };

  #include "network.hxx"
}
