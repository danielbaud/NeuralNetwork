#pragma once
#include <vector>
#include <iostream>
#include "neuron.hh"

namespace NeuralNetwork
{

  class Layer
  {
  public:

    Layer(size_t size, size_t syn);

    void update(const Layer& prev);

    void updateE(const Layer& next);

    void updateS(const Layer& prev);

    size_t size() const { return neurons.size(); }
  
    Neuron operator[](size_t i) const { return neurons[i]; }

  private:

    std::vector<Neuron> neurons;

  };

  #include "layer.hxx"
}
