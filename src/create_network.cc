#include "network/network.hh"
#include <csignal>
#define ERROR 0.01

static bool stop = false;

void sig(int signal)
{
  if (signal == SIGINT)
    std::cout << "\nProgram received SIGINT";
  if (signal == SIGTSTP)
    std::cout << "\nProgram received SIGTSTP";
  stop = true;
}

void print(std::vector<std::vector<double>> v)
{
  for (size_t i = 0; i < v.size(); ++i)
  {
    for (size_t j = 0; j < v[i].size(); ++j)
      std::cout << v[i][j] << " ";
    std::cout << std::endl;
  }
}


bool ok(std::vector<double> v)
{
  for (size_t i = 0; i < v.size(); ++i)
    if (v[i] > ERROR)
      return false;
  return true;
}

template <typename T>
T max(std::vector<T> v)
{
  T ret = 0;
  for (T e : v)
  {
    if (e > ret)
      ret = e;
  }
  return ret;
}


int main(int argc, char **argv)
{
  // Usage Verification
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " config_file | -l" << std::endl;
    return 1;
  }

  if (argv[1][0] == '-')
  {
    if (argv[1][1] == 'l' && !argv[1][2])
    {
      system("ls /home/daniel/.ann/nets");
      return 0;
    }
    if (argv[1][1] == 'R')
    {
      char temp[256] = "rm -f /home/daniel/.ann/nets/";
      size_t i = 2;
      for (; argv[1][i]; ++i)
	temp[27+i] = argv[1][i];
      temp[27+i] = 0;
      system(temp);
      return 0;
    }
    std::cerr << argv[0] << ": Unknown option " << argv[1] << std::endl;
    return 1;
  }
  // Config file verification
  std::ifstream f(argv[1]);
  if (!f.is_open())
  {
    std::cerr << "Unable to find config file " << argv[1]
              << ". Stopping program" << std::endl;
    return 2;
  }
  // Consistency verification/Creation

  std::string ann;
  f >> ann;

  ann = "/home/daniel/.ann/nets/" + ann;

  std::vector<size_t> init;
  size_t i = 0;
  f >> i;
  while (i != 0)
  {
    init.push_back(i);
    f >> i;
  }

  std::ifstream t(ann);
  if (t.is_open())
  {
    t.close();
    auto N = NeuralNetwork::Network(ann);
    for (size_t x = 0; x < N.size(); ++x)
    {
      if (init[x] != N[x].size())
      {
	std::cerr << "File " << ann
	<< " already exists and is not consistent with the description provided"
	<< std::endl;
	return 3;
      }
    }
  }
  else
  {
    auto N = NeuralNetwork::Network(init);
    std::cout << ann << std::endl;
    N.save(ann);
  }

  auto N = NeuralNetwork::Network(ann);

  // Training data loading
  size_t first = init[0];
  size_t last = init[init.size() - 1];

  std::vector<std::vector<double>> in;
  std::vector<std::vector<double>> out;

  size_t cpt = 0;

  while (!f.eof())
  {
    std::vector<double> inp(first);
    for (size_t k = 0; k < first; ++k)
      f >> inp[k];
    in.push_back(inp);
    std::vector<double> outp(last);
    for (size_t k = 0; k < last; ++k)
      f >> outp[k];
    out.push_back(outp);
    ++cpt;
  }
  --cpt;
  f.close();


/* DEBUG PRINTING INPUT */
//  print(in);
//  std::cout << "----------" << std::endl;
//  print(out);


  // Training the network
  std::signal(SIGINT, sig);
  std::signal(SIGTSTP, sig);

  std::vector<double> errors(cpt);
  double err = 0;
  do
  {
    for (size_t k = 0; k < cpt; ++k)
    {
      N.learn(in[k], out[k]);
      errors[k] = N.error();
      err += N.error();
    }
    err /= (double)cpt;
    std::cout << "MID COST = " << err << " (" << max(errors)
              << " worst case error)" << std::endl;
    err = 0;
  } while (!ok(errors) && !stop);

  N.save(ann);
  std::cout << std::endl << "Network saved at " << ann << std::endl;
  return 0;
}
