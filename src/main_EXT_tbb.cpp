/*
      This file is part of EXT_tbb
      Copyright (C) 2020  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include <cinttypes>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>
#include <string>
#if __GNUC__ >= 9
#include <execution>
#endif // __GNUC__ >= 9

template <class EXECUTION_POLICY>
void perform(EXECUTION_POLICY && p_policy
            ,const std::vector<uint32_t> & p_vector1
            ,const std::vector<uint32_t> & p_vector2
	    ,std::vector<uint32_t> & p_result
	    )
{
    auto l_start = std::chrono::steady_clock::now();
    for(unsigned int l_index = 0; l_index < 1000; ++l_index)
    {
        if constexpr(!std::is_same_v<EXECUTION_POLICY, std::string>)
        {
            std::transform(p_policy, p_vector1.begin(), p_vector1.end(), p_vector2.begin(), p_result.begin(), [=](uint32_t p_a, uint32_t p_b){return p_a + p_b;});
        }
        else
        {
            std::transform(p_vector1.begin(), p_vector1.end(), p_vector2.begin(), p_result.begin(), [=](uint32_t p_a, uint32_t p_b){return p_a + p_b;});
        }
    }
    auto l_end = std::chrono::steady_clock::now();
    std::chrono::duration<double> l_elapsed_seconds = l_end - l_start;
    std::cout << "CPU elapsed time: " << l_elapsed_seconds.count() << "s" << std::endl;
    std::cout << std::endl;
}

int main(void)
{
    uint32_t l_nb = 0x1000000;
    std::mt19937 l_rand_generator{(unsigned int)std::chrono::system_clock::now().time_since_epoch().count()};
    for(unsigned int l_policy_index = 0; l_policy_index < 5; ++l_policy_index)
    {
        std::vector<uint32_t> l_vector1;
        std::vector<uint32_t> l_vector2;
        std::vector<uint32_t> l_result(l_nb);
	for(unsigned int l_index = 0; l_index < l_nb; ++l_index)
	{
            l_vector1.emplace_back(l_rand_generator());
            l_vector2.emplace_back(l_rand_generator());
	}
	switch(l_policy_index)
	{
            case 0:
                std::cout << "No policy:" << std::endl;
		perform(std::string("no policy"), l_vector1, l_vector2, l_result);
                break;
#if __GNUC__ >= 9
            case 1:
                std::cout << "Sequenced policy:" << std::endl;
		perform(std::execution::seq, l_vector1, l_vector2, l_result);
                break;
            case 2:
                std::cout << "Parallel policy:" << std::endl;
		perform(std::execution::par, l_vector1, l_vector2, l_result);
                break;
            case 3:
                std::cout << "Parallel unsequenced policy:" << std::endl;
		perform(std::execution::par_unseq, l_vector1, l_vector2, l_result);
                break;
            case 4:
                std::cout << "Unsequenced policy:" << std::endl;
		perform(std::execution::unseq, l_vector1, l_vector2, l_result);
                break;
#endif // __GNUC__ >= 9
	}
    }
}
//EOF
