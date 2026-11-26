module game;


Game::Game(
    const std::vector<LinkSetup> &p1_links,
    const std::vector<LinkSetup> &p2_links,
    const std::string &ability1,
    const std::string &ability2
): 
    board{Board()}, player_1{PlayerID::P1}, player_2{PlayerID::P2}
{
    // set the link positions, players have already constructed them
}

std::vector<const Link *> Game::get_player_links(PlayerID id) const {
    return id == PlayerID::P1 ? player_1.get_links() : player_2.get_links();
}
