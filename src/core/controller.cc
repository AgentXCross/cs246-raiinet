export module controller;

import <string>;

import game;
import types;


// Controller is the interface the user interacts with 
// Reads commands from standard input or from an input file
//      move <a> <dir>: moves the link <a> (a-h, A-H) in a direction NORTH, EAST, SOUTH, WEST
//      abilities: lists the abilities of the player who's turn it is currently, and an 
//          indication of whether the ability has been used yet
//      ability <N>: applies the ability id <N> (1-5)
//      board: displays the board 
//      sequence <file>: executes the sequence of commands found in file
//      quit: exits the game
// Invalid inputs will do nothing and allow the user to continue entering inputs
export class Controller {
private:
    Game &game;
    bool running{true};

    // Reads in a command from standard input, validates input
    void execute_command(const std::string &command);

    // Reads in commands from an input file
    void execute_sequence(const std::string &file);

    // input helpers
    bool valid_link(char link) const; // a-h, A-H
    bool valid_dir(const std::string &dir) const; // NORTH, EAST, SOUTH, WEST
    bool valid_ability_id(int id) const; // 1-5

    Direction map_dir(std::string dir_str) const; // maps string to Direction

public:
    explicit Controller(Game &game);

    // Main game loop
    // If the user chooses to input using a text file, calls execute_sequence
    // Otherwise, reads in commands one at a time, calls execute_command each time
    void run();
};
