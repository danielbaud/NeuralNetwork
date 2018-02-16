#pragma once
#include <vector>
#include <cstdlib>
#include <cmath>

#define SYN 10

namespace NeuralNetwork
{
  class Neuron
  {
  public:

    Neuron(size_t nb_synapses)
    : delta(0)
    , sum(0)
    , val(0)
    { 
      synapses = std::vector<double>(nb_synapses);
      for (size_t i = 0; i < nb_synapses; ++i)
	synapses[i] = ((double)rand() / RAND_MAX) * 2 * SYN - SYN;
    }

    void activate() { val = (1 / (1 + exp(-sum))); }

    double get_delta() { return delta; }

    double get_val() { return val; }

    void reset_sum() { sum = 0; }

    void add_sum(double f) { sum += f; }

    double get_synapses(size_t i) { return synapses[i]; }


  private:

    double delta;
    double sum;
    double val;
    std::vector<double> synapses;
  };
}
