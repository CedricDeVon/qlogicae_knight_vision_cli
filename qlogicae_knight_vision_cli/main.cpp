#include "pch.hpp"

#include "main.hpp"

#include "qlogicae_core/includes/all.hpp"

int to_file(const std::string& value)
{
    return value[0] - 'a';
}

int to_rank(const std::string& value)
{
    return value[1] - '1';
}

std::string to_square(
    const int& file,
    const int& rank
)
{
    return std::string(1, 'a' + file) + std::to_string(rank + 1);
}

int main(int argc, char** argv)
{    
    QLogicaeCore::QLOGICAE_APPLICATION.setup();

    std::random_device randomizer;

    std::mt19937 random_generator(
        randomizer()
    );

    CLI::App app{ QLogicaeCore::QLOGICAE_APPLICATION_UTILITIES.CONFIGURATIONS_APPLICATION_NAME + " (" + QLogicaeCore::QLOGICAE_APPLICATION_UTILITIES.CONFIGURATIONS_APPLICATION_VERSION + ")" };
    
    auto practice = app.add_subcommand("practice", "guess-the-color, move-to-coordinate");

    auto find_square_color = practice->add_subcommand(
        "guess-the-color",
        "Guess the color of a given Chess board coordinate, Black or White?"
    );

    int find_square_color__attempt_count = 10;
    find_square_color
        ->add_option("--attempt-count", find_square_color__attempt_count, "Total attempt count")
        ->default_val(find_square_color__attempt_count);

    std::string find_square_color__top_left = "a8";
    find_square_color
        ->add_option("--top-left", find_square_color__top_left, "Top-left Chess board limit coordinate (a1, e6, h8, etc.)")
        ->default_val(find_square_color__top_left);

    std::string find_square_color__top_right = "h8";
    find_square_color
        ->add_option("--top-right", find_square_color__top_right, "Top-right Chess board limit coordinate (a1, e6, h8, etc.)")
        ->default_val(find_square_color__top_right);

    std::string find_square_color__bottom_right = "h1";
    find_square_color
        ->add_option("--bottom-right", find_square_color__bottom_right, "Bottom-right Chess board limit coordinate (a1, e6, h8, etc.)")
        ->default_val(find_square_color__bottom_right);

    std::string find_square_color__bottom_left = "a1";
    find_square_color
        ->add_option("--bottom-left", find_square_color__bottom_left, "Bottom-left Chess board limit coordinate (a1, e6, h8, etc.)")
        ->default_val(find_square_color__bottom_left);

    find_square_color->callback([&]()
        {            
            int to_file_top_left = to_file(find_square_color__top_left);
            
            int to_file_top_right = to_file(find_square_color__top_right);
            
            int to_file_bottom_right = to_file(find_square_color__bottom_right);
            
            int to_file_bottom_left = to_file(find_square_color__bottom_left);
            
            int to_rank_top_left = to_rank(find_square_color__top_left);
            
            int to_rank_top_right = to_rank(find_square_color__top_right);
            
            int to_rank_bottom_right = to_rank(find_square_color__bottom_right);
            
            int to_rank_bottom_left = to_rank(find_square_color__bottom_left);

            int min_file = std::min(
                {
                    to_file_top_left,
                    to_file_top_right,
                    to_file_bottom_right,
                    to_file_bottom_left
                }
            );
            
            int max_file = std::max(
                {
                    to_file_top_left,
                    to_file_top_right,
                    to_file_bottom_right,
                    to_file_bottom_left
                }
            );
            
            int min_rank = std::min(
                {
                    to_rank_top_left,
                    to_rank_top_right,
                    to_rank_bottom_right,
                    to_rank_bottom_left
                }
            );
            
            int max_rank = std::max(
                {
                    to_rank_top_left,
                    to_rank_top_right,
                    to_rank_bottom_right,
                    to_rank_bottom_left
                }
            );
            
            std::uniform_int_distribution<int> file_dist(
                min_file,
                max_file
            );
            
            std::uniform_int_distribution<int> rank_dist(
                min_rank,
                max_rank
            );

            std::string input;
            
            std::cout << "> Guess the color of a given Chess board coordinate, black or white? \n\n";
            while (find_square_color__attempt_count)
            {
                input = std::string(
                    1,
                    static_cast<char>('A' + file_dist(randomizer))) +
                    std::to_string(rank_dist(randomizer) + 1
                );
                std::cout << "[ " << find_square_color__attempt_count << " ]\t" << input << " ";

                std::cin >> input;

                std::cout << "\n";

                --find_square_color__attempt_count;
            }

            std::cout << "\n";
        }
    );



    



    auto move_to_coordinates = practice->add_subcommand(
        "move-to-coordinate",
        "Move a Chess piece towards a set of coordinates. Avoid occupied enemy squares, if enabled"
    );

    int move_to_coordinates__attempt_count = 10;
    move_to_coordinates->add_option("--attempt-count", move_to_coordinates__attempt_count, "Total attempt count")
        ->default_val(move_to_coordinates__attempt_count);

    std::string move_to_coordinates__top_left = "a8";
    move_to_coordinates->add_option("--top-left", move_to_coordinates__top_left, "Top-left Chess board limit coordinate (a1, e6, h8, etc.)")
        ->default_val(move_to_coordinates__top_left);

    std::string move_to_coordinates__top_right = "h8";
    move_to_coordinates->add_option("--top-right", move_to_coordinates__top_right, "Top-right Chess board limit coordinate (a1, e6, h8, etc.)")
        ->default_val(move_to_coordinates__top_right);

    std::string move_to_coordinates__bottom_right = "h1";
    move_to_coordinates->add_option("--bottom-right", move_to_coordinates__bottom_right, "Bottom-right Chess board limit coordinate (a1, e6, h8, etc.)")
        ->default_val(move_to_coordinates__bottom_right);

    std::string move_to_coordinates__bottom_left = "a1";
    move_to_coordinates->add_option("--bottom-left", move_to_coordinates__bottom_left, "Bottom-left Chess board limit coordinate (a1, e6, h8, etc.)")
        ->default_val(move_to_coordinates__bottom_left);

    std::string move_to_coordinates__player_piece = "R";
    move_to_coordinates->add_option("--player-piece", move_to_coordinates__player_piece, "Player Chess piece (N, B, R, Q, K)")
        ->default_val(move_to_coordinates__player_piece);

    std::vector<std::string> move_to_coordinates__player_pieces = { "N", "B", "R", "Q", "K" };
    move_to_coordinates->add_option("--player-pieces", move_to_coordinates__player_pieces, "Player Chess pieces (N, B, R, Q, K)")
        ->delimiter(',')
        ->default_val(move_to_coordinates__player_pieces);

    std::string move_to_coordinates__player_coordinate = "a1";
    move_to_coordinates->add_option("--player-coordinate", move_to_coordinates__player_coordinate, "Player Chess board starting coordinate (a1, e6, h8, etc.)")
        ->default_val(move_to_coordinates__player_coordinate);

    bool move_to_coordinates__is_player_piece_random = true;
    move_to_coordinates->add_option("--is-player-piece-random", move_to_coordinates__is_player_piece_random, "Is player Chess piece randomized>")
        ->default_val(move_to_coordinates__is_player_piece_random);

    bool move_to_coordinates__is_player_coordinate_random = true;
    move_to_coordinates->add_option("--is-player-coordinate-random", move_to_coordinates__is_player_coordinate_random, "Is player Chess board coordinate randomized?")
        ->default_val(move_to_coordinates__is_player_coordinate_random);

    int move_to_coordinates__enemy_coordinate_count = 1;
    move_to_coordinates->add_option("--enemy-coordinate-count", move_to_coordinates__enemy_coordinate_count, "Enemy Chess board coordinate count")
        ->default_val(move_to_coordinates__enemy_coordinate_count);

    std::vector<std::string> move_to_coordinates__enemies = { "Re6" };
    move_to_coordinates->add_option("--enemies", move_to_coordinates__enemies, "Enemy Chess pieces and board coordinates (a1, Re6, Qh8, etc.)")
        ->delimiter(',')
        ->default_val(move_to_coordinates__enemies);

    std::vector<std::string> move_to_coordinates__enemy_pieces = { "", "N", "B", "R", "Q", "K" };
    move_to_coordinates->add_option("--enemy-pieces", move_to_coordinates__enemy_pieces, "Enemy Chess pieces")
        ->delimiter(',')
        ->default_val(move_to_coordinates__enemy_pieces);

    bool move_to_coordinates__is_enemy_enabled = false;
    move_to_coordinates->add_option("--is-enemy-enabled", move_to_coordinates__is_enemy_enabled, "Is enemy enabled?")
        ->default_val(move_to_coordinates__is_enemy_enabled);

    bool move_to_coordinates__is_enemy_random = true;
    move_to_coordinates->add_option("--is-enemy-random", move_to_coordinates__is_enemy_random, "Is enemy randomized?")
        ->default_val(move_to_coordinates__is_enemy_random);

    move_to_coordinates->callback([&]()
        {            
            int to_file_top_left = to_file(move_to_coordinates__top_left);

            int to_file_top_right = to_file(move_to_coordinates__top_right);

            int to_file_bottom_right = to_file(move_to_coordinates__bottom_right);

            int to_file_bottom_left = to_file(move_to_coordinates__bottom_left);

            int to_rank_top_left = to_rank(move_to_coordinates__top_left);

            int to_rank_top_right = to_rank(move_to_coordinates__top_right);

            int to_rank_bottom_right = to_rank(move_to_coordinates__bottom_right);

            int to_rank_bottom_left = to_rank(move_to_coordinates__bottom_left);

            int min_file = std::min(
                {
                    to_file_top_left,
                    to_file_top_right,
                    to_file_bottom_right,
                    to_file_bottom_left
                }
            );

            int max_file = std::max(
                {
                    to_file_top_left,
                    to_file_top_right,
                    to_file_bottom_right,
                    to_file_bottom_left
                }
            );

            int min_rank = std::min(
                {
                    to_rank_top_left,
                    to_rank_top_right,
                    to_rank_bottom_right,
                    to_rank_bottom_left
                }
            );

            int max_rank = std::max(
                {
                    to_rank_top_left,
                    to_rank_top_right,
                    to_rank_bottom_right,
                    to_rank_bottom_left
                }
            );

            std::uniform_int_distribution<int> file_dist(
                min_file,
                max_file
            );

            std::uniform_int_distribution<int> rank_dist(
                min_rank,
                max_rank
            );

            std::uniform_int_distribution<int> player_piece_dist(
                0,
                static_cast<int>(move_to_coordinates__player_pieces.size() - 1)
            );

            std::uniform_int_distribution<int> enemy_piece_dist(
                0,
                static_cast<int>(move_to_coordinates__enemy_pieces.size() - 1)
            );


            std::string current_player;

            if (move_to_coordinates__is_player_piece_random)
            {
                current_player = move_to_coordinates__player_pieces[player_piece_dist(random_generator)];
            }
            else
            {
                current_player = move_to_coordinates__player_piece;
            }

            if (move_to_coordinates__is_player_coordinate_random)
            {
                current_player += to_square(file_dist(random_generator), rank_dist(random_generator));
            }
            else
            {
                current_player += move_to_coordinates__player_coordinate;
            }

            std::string input;

            std::cout << "> Move a Chess piece towards a set of coordinates. Avoid occupied enemy squares, if enabled\n";            
            std::cout << "> Initial Position: " << current_player << "\n";            
            if (move_to_coordinates__is_enemy_enabled)
            {
                std::cout << "> Enemy Piece(s): ";
                if (move_to_coordinates__is_enemy_random)
                {
                    while (move_to_coordinates__enemy_coordinate_count)
                    {
                        std::cout << move_to_coordinates__enemy_pieces[enemy_piece_dist(random_generator)] << to_square(file_dist(random_generator), rank_dist(random_generator)) << " ";

                        --move_to_coordinates__enemy_coordinate_count;
                    }
                }
                else
                {
                    for (const auto& value : move_to_coordinates__enemies)
                    {
                        std::cout << value << " ";
                    }
                }
            }
            std::cout << "\n";

            while (move_to_coordinates__attempt_count)
            {
                std::string square = std::string(
                    1,
                    static_cast<char>('A' + file_dist(random_generator))) +
                    std::to_string(rank_dist(random_generator) + 1
                    );
                std::cout << "[ " << move_to_coordinates__attempt_count << " ]\t" << square << " ";

                std::cin >> input;

                std::cout << "\n";

                --move_to_coordinates__attempt_count;
            }

            std::cout << "\n";
        }
    );

    CLI11_PARSE(app, argc, argv);

    return 0;
}

namespace QLogicaeKnightVisionCLI
{

}
