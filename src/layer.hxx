#include "layer.hh"

Layer::Layer(size_t size, size_t syn)
{
  neurons = std::vector<Neuron>(size, Neuron(syn));
}

void Layer::update(const Layer& prev)
{
  for (size_t i = 0; i < neurons.size(); ++i)
  {
    neurons[i].set_val(0);
    for (size_t j = 0; j < prev.size(); ++j)
      neurons[i].add_sum(prev[j].get_val()*neurons[i][j]);
    neurons[i].activate();
  }
}

void Layer::updateE(const Layer& next)
{
  for (size_t i = 0; i < neurons.size(); ++i)
  {
    neurons[i].set_delta(0);
    for (size_t j = 0; j < next.size(); ++j)
      neurons[i].add_delta(next[j][i] * next[j].get_delta());
  }
}

void Layer::updateS(const Layer& prev)
{
  for (size_t i = 0; i < neurons.size(); ++i)
    for (size_t j = 0; j < prev.size(); ++j)
      neurons[i][j] += neurons[i].get_delta() * ATOM * prev[j].get_val()
        * sigmoid_d(neurons[i].get_sum());
}
