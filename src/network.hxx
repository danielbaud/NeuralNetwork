#include "network.hh"

Network::Network(std::vector<size_t> lsize)
{
  layers.push_back(Layer(lsize[0], 0));
  for (size_t i = 1; i < lsize.size(); ++i)
    layers.push_back(Layer(lsize[i], lsize[i-1]));
}

void Network::forward()
{
  for (size_t i = 1; i < layers.size(); ++i)
    layers[i].update(layers[i-1]);
}

void Network::backPropagate(std::vector<double> target)
{
  size_t l = layers.size() - 1;
  for (size_t i = 0; i < layers[l].size(); ++i)
    layers[l][i].set_delta(target[i] - layers[l][i].get_val());
  for (size_t i = l; i > 0; --i)
    layers[i-1].updateE(layers[i]);
  for (size_t i = 0; i < layers.size(); ++i)
    layers[i+1].updateS(layers[i]);
}

void Network::learn(std::vector<double> input, std::vector<double> target)
{
  for (size_t i = 0; i < layers[0].size(); ++i)
    layers[0][i].set_val(input[i]);
  forward();
  backPropagate(target);
}
