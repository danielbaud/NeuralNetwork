#include "network.hh"

Network::Network(std::vector<size_t> lsize)
{
  layers.push_back(Layer(lsize[0], 0));
  for (size_t i = 1; i < lsize.size(); ++i)
    layers.push_back(Layer(lsize[i], lsize[i-1]));
}

Network::Network(const std::string& path)
{
  std::ifstream s(path);
  size_t l = 0;
  s >> l;
  layers.push_back(Layer(l, 0));
  size_t ll = l;
  s >> l;
  while (l > 0)
  {
    layers.push_back(Layer(l, ll));
    ll = l;
    s >> l;
  }
  for (size_t i = 1; i < layers.size(); ++i)
    for (size_t j = 0; j < layers[i].size(); ++j)
      for (size_t k = 0; k < layers[i][j].size(); ++k)
	s >> layers[i][j][k];
  s.close();
}

void Network::forward()
{
  for (size_t i = 1; i < layers.size(); ++i)
    layers[i].update(layers[i-1]);
}

std::vector<double> Network::result(std::vector<double> input)
{
  for (size_t i = 0; i < layers[0].size(); ++i)
    layers[0][i].set_val(input[i]);
  forward();
  std::vector<double> res;
  size_t t = layers.size()-1;
  for (size_t i = 0; i < layers[t].size(); ++i)
    res.push_back(layers[t][i].get_val());
  return res;
}

void Network::backPropagate(std::vector<double> target)
{
  size_t l = layers.size() - 1;
  for (size_t i = 0; i < layers[l].size(); ++i)
    layers[l][i].set_delta(target[i] - layers[l][i].get_val());
  for (size_t i = l; i > 0; --i)
    layers[i-1].updateE(layers[i]);
  for (size_t i = 0; i < layers.size() - 1 ; ++i)
    layers[i+1].updateS(layers[i]);
}

void Network::learn(std::vector<double> input, std::vector<double> target)
{
  for (size_t i = 0; i < layers[0].size(); ++i)
    layers[0][i].set_val(input[i]);
  forward();
  backPropagate(target);
}

void Network::print()
{
  for (size_t i = 0; i < layers.size(); ++i)
  {
    for (size_t j = 0; j < layers[i].size(); ++j)
    {
      std::cout << layers[i][j];
    }
    std::cout << std::endl;
  }
}

double Network::error()
{
  double er = 0;
  size_t t = layers.size() - 1;
  for (size_t i = 0; i < layers[t].size(); ++i)
  {
    if (layers[t][i].get_delta() > 0)
      er += layers[t][i].get_delta();
    else
      er -= layers[t][i].get_delta();
  }
  return er;
}

void Network::save(const std::string& path)
{
  std::ofstream s(path);
  for (size_t i = 0; i < layers.size(); ++i)
    s << layers[i].size() << std::endl;
  s << '0' << std::endl;
  for (size_t i = 1; i < layers.size(); ++i)
    for (size_t j = 0; j < layers[i].size(); ++j)
      for (size_t k = 0; k < layers[i][j].size(); ++k)
	s << layers[i][j][k] << std::endl;
  s.close();
}
