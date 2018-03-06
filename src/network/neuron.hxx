#include "neuron.hh"

Neuron::Neuron(size_t nb_synapses) : delta(0), val(0), sum(0)
{
  srand(time(NULL));
  synapses = std::vector<double>(nb_synapses);
  for (size_t i = 0; i < nb_synapses; ++i)
  {
    synapses[i] = ((double)rand() / RAND_MAX) * SYN;
    if (i%2 == 0)
      synapses[i] *= -1;
  }
}

/* MATHS FUNCTIONS */
double sigmoid(double x)
{
  return (1 / (1 + exp(-x * SIG)));
}

double sigmoid_d(double x)
{
  double y = SIG * x;
  return ((SIG * exp(-y)) / ((1 + exp(-y)) * (1 + exp(-y))));
}

double gauss(double x)
{
  return exp(-x*x);
}

double gauss_d(double x)
{
  return -2*x*exp(-x*x);
}

double nsin(double x)
{
  return 0.5*sin(x) + 0.5;
}

double nsin_d(double x)
{
  return 0.5*cos(x);
}
/* !MATHS FUNCTION */

double activation(double x)
{
  return nsin(x);
}

double activation_d(double x)
{
  return nsin_d(x);
}

void Neuron::activate()
{
  this->val = activation(sum);
}

double Neuron::get_delta() const
{
  return this->delta;
}

double Neuron::get_val() const
{
  return this->val;
}

double Neuron::get_sum() const
{
  return this->sum;
}

void Neuron::set_delta(double x)
{
  this->delta = x;
}

void Neuron::set_val(double x)
{
  this->val = x;
}

void Neuron::set_sum(double x)
{
  this->sum = x;
}

void Neuron::add_sum(double x)
{
  this->sum += x;
}

void Neuron::add_delta(double x)
{
  this->delta += x;
}

std::ostream& operator<<(std::ostream& out, Neuron n)
{
  out << "[[sum: "<< n.sum << ", val: " << n.val << ", delta: " 
    << n.delta << "]] ";
  return out;
}
