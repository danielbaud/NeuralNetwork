#include "neuron.hh"

Neuron::Neuron(size_t nb_synapses) : delta(0), val(0), sum(0)
{
  synapses = std::vector<double>(nb_synapses);
  for (size_t i = 0; i < nb_synapses; ++i)
    synapses[i] = ((double)rand() / RAND_MAX) * 2 * SYN - SYN;
}


double sigmoid(double x)
{
  return (1 / (1 + exp(-x)));
}

void Neuron::activate()
{
  val = sigmoid(sum);
}

double Neuron::get_delta() const
{
  return delta;
}

double Neuron::get_val() const
{
  return val;
}

double Neuron::get_sum() const
{
  return sum;
}

void Neuron::set_delta(double x)
{
  delta = x;
}

void Neuron::set_val(double x)
{
  val = x;
}

void Neuron::add_syn(size_t i, double x)
{
  synapses[i] += x;
}

void Neuron::add_sum(double x)
{
  sum += x;
}

void Neuron::add_delta(double x)
{
  delta += x;
}
