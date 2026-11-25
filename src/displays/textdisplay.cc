export module textdisplay;

import <iostream>;

import types;
import gamedisplay;
import subject;


export class TextDisplay : public GameDisplay {
protected:
    Subject *game;
    std::ostream &out;
    
public:
    TextDisplay(Subject *game, std::ostream &out);

    // Pull data from the Subject
    void notify() override;

    // Writes the current board and player information to the stream.
    friend std::ostream &operator<<(std::ostream &os, const TextDisplay &td);
};
