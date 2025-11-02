#pragma once

#include "qlogicae_knight_vision_cli/includes/application.hpp"

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

namespace QLogicaeKnightVisionCLI
{

}
