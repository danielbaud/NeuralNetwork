#pragma once

// Used in implementation
#include <string>
#include <vector>

// Saving/Loading a network
#include <fstream>
#include <cstdio>

// Printing
#include <iostream>

// Random
#include <cstdlib>
#include <ctime>

// Exponential function for Sigmoid
#include <cmath>

#define SYN 1
#define SIG 1
#define ATOM 0.5

namespace NeuralNetwork
{
  class Neuron
  {
  public:

    Neuron(size_t nb_synapses);

    void activate();

    double get_delta() const;
    double get_val() const;
    double get_sum() const;

    void set_delta(double x);
    void set_val(double x);
    void set_sum(double x);

    void add_delta(double x);
    void add_sum(double x);
    double& operator[](size_t i) { return synapses[i]; }
    const double& operator[](size_t i ) const { return synapses[i]; }
    
    size_t size() const { return synapses.size(); }

    friend std::ostream& operator<<(std::ostream& out, Neuron n);

  private:

    double delta;
    double val;
    double sum;
    std::vector<double> synapses;
  };
  #include "neuron.hxx"
}
