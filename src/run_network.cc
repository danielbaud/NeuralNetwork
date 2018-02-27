#include "network/network.hh"

int main(int argc, char **argv)
{
  argc++;
  auto N = NeuralNetwork::Network(argv[1]);
  std::vector<double> r;
  for (size_t i = 0; i < N[0].size(); ++i)
    r.push_back(atof(argv[i+2]));
  std::vector<double> res = N.result(r);
  for (size_t i = 0; i < res.size(); ++i)
    std::cout << res[i] << " ";
  std::cout << std::endl;
  return 0;
}
