#include "../src/network/network.hh"
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


bool ok(std::vector<double> v)
{
  for (size_t i = 0; i < v.size(); ++i)
    if (v[i] > ERROR)
      return false;
  return true;
}


int main(int argc, char **argv)
{
  // Usage Verification
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " config_file step" << std::endl;
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


  // step obtention

  size_t step = atoi(argv[2]);
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

  if (init[0] != 1 || init[init.size()-1] != 1)
  {
    std::cerr << argv[0] << ": ANN is not of form x -> f(x). Stopping program"
              << std::endl;
    return 2;
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
  size_t bcl = 0;
  do
  {
    for (size_t k = 0; k < cpt; ++k)
    {
      N.learn(in[k], out[k]);
      errors[k] = N.error();
    }
    if (bcl % step == 0)
    {
      std::ofstream fx("/home/daniel/.ann/func");
      for (double x = 0; x <= 1; x += 0.01)
        fx << N.result(std::vector<double>{x})[0] << std::endl;
      fx.close();
      std::ofstream crs("/home/daniel/.ann/crs");
      for (size_t x = 0; x < cpt; ++x)
	crs << in[x][0] << " " << out[x][0] << std::endl;
      crs.close();
      system("python3 /home/daniel/.ann/graph_h.py");
    }

    bcl++;
  } while (!ok(errors) && !stop);

  N.save(ann);
  std::cout << std::endl << "Network saved at " << ann << std::endl;
  return 0;
}
