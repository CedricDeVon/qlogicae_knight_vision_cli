#pragma once

#include "qlogicae_vs2022_nanobench_benchmark/includes/application.hpp"

int main(int, char**);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int
)
{
    return main(__argc, __argv);
}

namespace QLogicaeKnightVisionCoreBenchmark
{

}
