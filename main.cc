import <iostream>;
import <string>;
import <vector>;
import <cstdlib>;
import <ctime>;
import <fstream>;
import <exception>;

import game;
import controller;
import types;
import setup;

/*
Ability Letters:
    L: LinkBoost
    F: Firewall
    D: Download
    S: Scan
    P: Polarize
    H: Shield
    I: Disguise
    R: Strengthen

If the user enters arguments though the command line we need to do the following checks:
    Links: Must have all of D1-D4 and V1-V4 in any order
    Abilities: 5 of any of the letters above with a max of 2 of the same ability
*/

int main(int argc, char *argv[]) {
    std::string ability1{"LFDSP"};
    std::string ability2{"LFDSP"};

    std::string link1_file{};
    std::string link2_file{};

    bool graphics{false};

    std::srand(std::time(nullptr)); // seed randomness

    for (int i{1}; i < argc; ++i) {
        std::string arg{argv[i]};

        if (arg == "-graphics") {
            graphics = true;
        } else if (
            arg == "-link1" || arg == "-link2" || arg == "-ability1" || arg == "-ability2"
        ) {
            if (i + 1 >= argc) {
                std::cerr << "Missing argument for " << arg << '\n';
                return 1;
            }

            std::string value{argv[i + 1]};
            ++i;

            if (arg == "-ability1") ability1 = value;
            else if (arg == "-ability2") ability2 = value;
            else if (arg == "-link1") link1_file = value;
            else if (arg == "-link2") link2_file = value;

        } else {
            std::cerr << "Unknown command line argument: " << arg << "\n";
            return 1;
        }
    } 

    // ============= Ability Validation ==============
    if (!valid_ability_setup(ability1)) {
        std::cerr << "Invalid ability setup for Player 1\n";
        return 1;
    }

    if (!valid_ability_setup(ability2)) {
        std::cerr << "Invalid ability setup for Player 2\n";
        return 1;
    }

    // ============= Link Setup =====================
    std::vector<LinkSetup> p1_links{};
    std::vector<LinkSetup> p2_links{};

    if (!make_link_setup(link1_file, p1_links)) {
        return 1;
    }

    if (!make_link_setup(link2_file, p2_links)) {
        return 1;
    }

    // ================= Game Construction and Game Run =============
    try {
        Game game{p1_links, p2_links, ability1, ability2};
        Controller controller{game};

        controller.run();

    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Unexpected error. Check implementation.\n";
        return 1;
    }

    return 0;
}
