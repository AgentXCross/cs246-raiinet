export module textdisplay;
import <iostream>;
import types;
import gamedisplay;
import subject;

export class TextDisplay : public GameDisplay {
  protected:
    Subject *game;
    std::ostream &out;
    void print_player(std::ostream &os, PlayerID who, PlayerID viewer) const;
  public:
    TextDisplay(Subject *game, std::ostream &out);
    void notify() override;
    friend std::ostream &operator<<(std::ostream &os, const TextDisplay &td);
};