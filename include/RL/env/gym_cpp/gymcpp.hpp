#pragma once

#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include "RL/common/rl_config.hpp"
#include "RL/common/state_action.hpp"

using namespace pybind11::literals;
namespace rlcpp
{
    namespace
    {
        namespace py = pybind11;
    }

    template <typename State, typename Action>
    class Gym_cpp
    {
    public:
        Gym_cpp() {}

        ~Gym_cpp() {}

        void make(const string &game_name)
        {
            try
            {
                auto gym = py::module::import("gym");
                this->env = gym.attr("make")(game_name);
                auto mes = this->env.attr("_max_episode_steps");
                if (mes.is_none())
                {
                    this->max_episode_steps = -1;
                }
                else
                {
                    this->max_episode_steps = py::cast<size_t>(mes);
                }
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
                this->max_episode_steps = -1;
            }
        }

        Space action_space() const
        {
            Space ret;
            try
            {
                auto act_space = this->env.attr("action_space");
                if (py::len(act_space.attr("shape")) == 0)
                {
                    ret.bDiscrete = true;
                    ret.n = act_space.attr("n").cast<int>();
                }
                else
                {
                    ret.bDiscrete = false;
                    ret.high = py::cast<Vecf>(act_space.attr("high"));
                    ret.low = py::cast<Vecf>(act_space.attr("low"));
                    ret.shape = py::cast<Veci>(act_space.attr("shape"));
                }
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
            return ret;
        }

        Space obs_space() const
        {
            Space ret;
            try
            {
                auto obs_space = this->env.attr("observation_space");
                if (py::len(obs_space.attr("shape")) == 0)
                {
                    ret.bDiscrete = true;
                    ret.n = obs_space.attr("n").cast<int>();
                }
                else
                {
                    ret.bDiscrete = false;
                    ret.high = py::cast<Vecf>(obs_space.attr("high"));
                    ret.low = py::cast<Vecf>(obs_space.attr("low"));
                    ret.shape = py::cast<Veci>(obs_space.attr("shape"));
                }
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
            return ret;
        }

        template<typename T>
        State pyarray_to_vector(py::array_t<T> arr)
        {
            auto ptr = static_cast<T*>(arr.request().ptr);
            return State(ptr, ptr + arr.size());
        }

        // Return initial observation
        void reset(State *obs, int seed = 0)
        {
            try
            {
                py::tuple reset_obs_obj = this->env.attr("reset")();
                if (seed != 0)
                    reset_obs_obj = this->env.attr("reset")("seed"_a = seed);
                py::array reset_obs_arr = py::cast<py::array>(reset_obs_obj[0]);
                *obs = pyarray_to_vector<float>(reset_obs_arr);
                //*obs = py::cast<State>(reset_obs_obj);
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
        }

        void close()
        {
            try
            {
                this->env.attr("close")();
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
        }

        void step(const Action &action, State *next_obs, Real *reward, bool *done)
        {
            try
            {
                py::tuple res = this->env.attr("step")(action);
                *next_obs = py::cast<State>(res[0]);
                *reward = py::cast<Real>(res[1]);
                *done = py::cast<bool>(res[2]);
                // py::print(py::str("run step, action: {}, res: {}").format(action, res));
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
        }

        void render()
        {
            try
            {
                this->env.attr("render")();
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
        }

        py::object env;

        /**
         * @brief  最大回合数
         */
        size_t max_episode_steps;
    }; // !class PyGym
} // namespace rlcpp
