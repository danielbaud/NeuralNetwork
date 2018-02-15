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

    activate() { val = (1 / (1 + exp(-sum))); }


  private:

    double delta;
    double sum;
    double val;
    std::vector<double> synapses;
  };
}
