export module graphicaldisplay;
import types;
import gamedisplay;
import subject;
import xwindow;

export class GraphicsDisplay : public GameDisplay {
  protected:
    Subject *game;
    // Xwindow window;
    // previous-frame cache (e.g. std::array<char, 64> lastSymbols) for partial redraws
    void drawBoard();
    void drawLink(int x, int y, char symbol, bool visible /*, LinkType type */);
    void drawPlayerInfo(PlayerID who);
  public:
    explicit GraphicsDisplay(Subject *game);
    void notify() override;
};