#include "pch.hpp"

#include "main.hpp"

#include "qlogicae_core/includes/all.hpp"

int main(int argc, char** argv)
{
    QLogicaeCore::QLOGICAE_APPLICATION.setup();

    CLI::App app{ "QLogicae KnightVision (" + QLogicaeCore::QLOGICAE_APPLICATION_UTILITIES.CONFIGURATIONS_APPLICATION_VERSION + ")" };

    auto* practice = app.add_subcommand("practice", "Practice mode commands");

    auto* square_color = practice->add_subcommand("square-color", "Identify the color of a square");
    square_color->callback([]()
    {
        std::cout << "A\n";
    }
    );

    auto* move_to_coordinate = practice->add_subcommand("move-to-coordinate", "Move to a given coordinate");
    move_to_coordinate->callback([]()
    {
        std::cout << "B\n";
    }
    );

    CLI11_PARSE(app, argc, argv);

    return 0;
}

namespace QLogicaeKnightVisionCLI
{

}


/*

knightvision practice square-color
knightvision practice move-to-coordinate

*/