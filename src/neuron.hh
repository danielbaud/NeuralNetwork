#include <vector>
#include <stdlib.h>

namespace NeuralNetwork
{
  class Neuron
  {
  public:

    Neuron(size_t nb_synapses)
    { 
      synapses = std::vector<double>(nb_synapses);
    }


  private:

    double delta;
    double sum;
    double val;
    std::vector<double> synapses;
  };
}
