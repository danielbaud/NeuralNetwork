#include "network/network.hh"

void print(std::vector<double> v)
{
  for (size_t i = 0; i < v.size(); ++i)
    std::cout << v[i] << " ";
}

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    std::cerr << "Usage: " << argv[0]
              << " runfile  OR  " << argv[0] << " network x1 x2 .. xn"
              << std::endl;
    return 2;
  }
  if (argc == 2)
  {
    std::ifstream f(argv[1]);
    if (!f.is_open())
    {
      std::cerr << "File " << argv[1] << " could not be opened" << std::endl;
      return 1;
    }
    std::string ann;
    f >> ann;
    ann = "/home/daniel/.ann/" + ann;
    auto N = NeuralNetwork::Network(ann);
    std::vector<double> r(N[0].size());
    for (size_t i = 0; i < N[0].size(); ++i)
      f >> r[i];
    while (!f.eof())
    {
      print(r);
      std::vector<double> res = N.result(r);
      std::cout << " ->  ";
      print(res);
      std::cout << std::endl;
      for (size_t i = 0; i < N[0].size(); ++i)
        f >> r[i];
    }
    return 0;
  }
  std::string path = "/home/daniel/.ann/";
  for (size_t i = 0; argv[1][i]; ++i)
    path += argv[1][i];
  auto N = NeuralNetwork::Network(path);
  if (argc != (int)N[0].size() + 2)
  {
    std::cerr << "Number of arguments is not correct" << std::endl;
    return 2;
  }
  std::vector<double> r;
  for (size_t i = 0; i < N[0].size(); ++i)
    r.push_back(atof(argv[i+2]));
  std::vector<double> res = N.result(r);
  print(r);
  std::cout << " ->  ";
  print(res);
  std::cout << std::endl;
  return 0;
}
