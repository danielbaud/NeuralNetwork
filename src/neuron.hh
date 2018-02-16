#pragma once
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>

#define SYN 10

namespace NeuralNetwork
{
  class Neuron
  {
  public:

    Neuron(size_t nb_synapses);

    void activate();

    double get_delta() const;
    double get_val() const;

    void set_delta(double x);
    void set_val(double x);

    void add_delta(double x);
    void add_val(double x);
    void add_syn(size_t i, double x);
    double operator[](size_t i) { return synapses[i]; }
    
    size_t size() const { return synapses.size(); }

  private:

    double delta;
    double val;
    std::vector<double> synapses;
  };
  #include "neuron.hxx"
}
