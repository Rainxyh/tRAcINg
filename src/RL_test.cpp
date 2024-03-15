#include "dynet/training.h"
#include "dynet/timing.h"
#include "dynet/lstm.h"
#include "dynet/dict.h"
#include "dynet/expr.h"
#include "dynet/globals.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cassert>

#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

using namespace std;
using namespace dynet;
namespace py = pybind11;

int main(int argc, char** argv) {
    py::scoped_interpreter guard{}; // start the interpreter and keep it alive

    py::print("Hello, World!"); // use the Python API

    auto gym = py::module::import("gym");
    auto env = gym.attr("make")("CartPole-v1");
    int max_episode_steps = 0;
    try {
        auto mes = env.attr("_max_episode_steps");
        if (mes.is_none()) {
            max_episode_steps = -1;
        }
        else {
            max_episode_steps = py::cast<size_t>(mes);
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        max_episode_steps = -1;
    }
    cout << max_episode_steps << endl;
    return 0;
}