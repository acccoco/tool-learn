#include <cmath>
#include <iostream>
#include <algorithm>


int main()
{

    auto cal = [](int i, int j, int k) -> double {
        auto res = std::pow(std::pow(i, j), k);
        return res;
    };

#pragma openmp parallel for
    for (int i = 0; i < 1024; ++i)
    {
        for (int j = 0; j < 1024 * 1024; ++j)
        {
            for (int k = 0; k < 1024 * 1024; ++k)
            {
                cal(i, j, k);
            }
        }
    }
}
