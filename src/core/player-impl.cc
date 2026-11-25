module player;

std::vector<const Link *> Player::get_links() const {
    std::vector<const Link *> result;
    result.reserve(links.size());
    for (const auto &link : links) {
        result.push_back(link.get());
    }
    return result;
}
