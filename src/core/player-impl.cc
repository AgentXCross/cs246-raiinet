module player;


Player(
    PlayerID id,
    const std::vector<LinkSetup> &link_setup,
    const std::string &ability_setup
);

std::vector<const Link *> Player::get_links() const {
    std::vector<const Link *> result;
    result.reserve(links.size());
    for (const auto &link : links) {
        result.push_back(link.get());
    }
    return result;
}
