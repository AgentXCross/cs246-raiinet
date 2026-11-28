module controller;

import <iostream>;
import <string>;
import <sstream>;
import <fstream>;
import <vector>;

import link;


bool Controller::valid_link(char link) const {
    return (link >= 'a' && link <= 'h') || (link >= 'A' && link <= 'H');
}

bool Controller::valid_dir(const std::string &dir) const {
    return dir == "up" || dir == "down" || dir == "left" || dir == "right";
}

bool Controller::valid_ability_id(int id) const {
    return (id >= 1) && (id <= 5);
}

Direction Controller::map_dir(std::string dir_str) const {
    if (dir_str == "up") return Direction::NORTH;
    if (dir_str == "down") return Direction::SOUTH;
    if (dir_str == "left") return Direction::WEST;
    return Direction::EAST;
}

Controller::Controller(Game &game): game{game} {}

void Controller::run() {
    std::string command{};

    while (running && !game.is_game_over()) {
        if (!std::getline(std::cin, command)) {
            break;
        }

        execute_command(command);
    }
}

void Controller::execute_command(const std::string &command) {
    std::istringstream iss{command};
    std::string action{};

    if (!(iss >> action)) return;

    if (action == "move") {
        char link{};
        std::string dir{};

        if (!(iss >> link >> dir)) {
            std::cerr << "Invalid move operands\n";
            return;
        }

        // Reject extra args (Ex: move a NORTH hello bye)
        std::string extra{};

        if (iss >> extra) {
            std::cerr << "Too many operands\n";
            return;
        }

        if (!valid_link(link) || !valid_dir(dir)) {
            std::cerr << "Invalid move operands\n";
            return;
        } 
        
        PlayerID curr_player{game.get_current_player()};

        if (!is_own_link(curr_player, link)) {
            std::cerr << "You can only move your own links\n";
            return;
        }

        if (!game.move(link, map_dir(dir))) {
            std::cerr << "Invalid move\n";
            return;
        }
        // game moves state into next turn

    } else if (action == "abilities") {
        PlayerID curr_player{game.get_current_player()};
        const int num_abilities{5};

        std::cout << "\n";
        
        for (int i{1}; i <= num_abilities; ++i) {
            std::cout << std::boolalpha << "\t" << i << ". " 
                << game.get_ability_name(curr_player, i) 
                << " | Used: " << game.is_ability_used(curr_player, i) << "\n";
        }

        std::cout << "\n";

    } else if (action == "ability") {
        int ability_id{0};
        PlayerID curr_player{game.get_current_player()};

        if (!(iss >> ability_id)) {
            std::cerr << "Invalid ability operand\n";
            return;
        }

        if (!valid_ability_id(ability_id)) {
            std::cerr << "Ability ID operand must be between 1 and 5 inclusive\n";
            return;
        }

        if (game.is_ability_used_this_turn()) {
            std::cerr << "Ability has already been applied this turn\n";
            return;
        }

        if (game.is_ability_used(curr_player, ability_id)) {
            std::cerr << "Abilities can only be applied once\n";
            return;
        }

        // Need to check how many args there are
        // 2 args -> Firewall
        //  and the argument is a Position
        // 1 args: 
        //      LinkBoost (targets own link)
        //      Download (targets opponent link)
        //      Polarize (targets any link)
        //      Scan (targets opponent link)
        //      Shield (targets own link)
        //      Strength (targets own link)
        //      Disguise (targets own link)
        //  and the argument is a Link id char
        std::vector<std::string> ability_operands{};
        std::string operand{};

        while (iss >> operand) {
            ability_operands.push_back(operand);
        }

        std::string ability_name{game.get_ability_name(curr_player, ability_id)};

        if (ability_operands.size() == 1) {
            // the operand should be one character a-h A-H
            if (ability_operands[0].size() != 1) {
                std::cerr << "Invalid ability operands\n";
                return;
            }

            char target{ability_operands[0][0]};

            if (!valid_link(target)) {
                std::cerr << "Invalid ability link operand\n";
                return;
            }

            // If ability can only be applied to own links
            if (ability_name == "LinkBoost" || ability_name == "Shield" 
                || ability_name == "Strength" || ability_name == "Disguise") 
            {
                if (!is_own_link(curr_player, target)) {
                    std::cerr << "This ability can only be applied to your own links\n";
                    return;
                }
            } else if (ability_name == "Scan" || ability_name == "Download") {
                if (is_own_link(curr_player, target)) {
                    std::cerr << "This ability can only be applied to your opponents links\n";
                    return;
                }
            } else if (ability_name == "Polarize") {
                // Do nothing takes any link
            } else {
                std::cerr << "Invalid ability operands\n";
                return;
            }

            if (!game.use_ability(ability_id, target)) {
                std::cerr << "Unable to apply ability\n";
            }

        } else if (ability_operands.size() == 2) {
            if (ability_name != "Firewall") {
                std::cerr << "Invalid ability operands\n";
                return;
            }

            std::istringstream row_stream{ability_operands[0]};
            std::istringstream col_stream{ability_operands[1]};

            int target_row{0};
            int target_col{0};
            char extra{};

            if (!(row_stream >> target_row) || (row_stream >> extra) ||
                !(col_stream >> target_col) || (col_stream >> extra)) {
                std::cerr << "Invalid position operands\n";
                return;
            }

            if (target_row < 0 || target_row > 7 ||
                target_col < 0 || target_col > 7) {
                std::cerr << "Position elements must be between 0 and 7\n";
                return;
            }

            Position target{target_row, target_col};

            if (!game.use_ability(ability_id, target)) {
                std::cerr << "Unable to apply ability\n";
            }
        } else {
            std::cerr << "Invalid number of ability operands\n";
            return;
        }

    } else if (action == "board") {
        game.notify_displays(); // notifying invokes a print
    } else if (action == "sequence") {
        std::string file{};

        if (!(iss >> file)) {
            std::cerr << "Must provide file name\n";
            return;
        }

        execute_sequence(file);

    } else if (action == "quit") {
        running = false;
    } else {
        std::cerr << "Invalid action";
    }
}

void Controller::execute_sequence(const std::string &file) {
    std::ifstream ifs{file};

    if (!ifs) {
        std::cerr << "Cannot open file: " << file << '\n';
        return;
    }

    std::string input_line{};

    while (running && !game.is_game_over() && std::getline(ifs, input_line)) {
        execute_command(input_line);
    }
}
