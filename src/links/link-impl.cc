module link;

Link::Link(char id, LinkType type, int strength, Position position):
    id{id},
    type{type},
    strength{strength},
    position{position},
    revealed{false} {}

char Link::get_id() const {
    return id;
}

LinkType Link::get_visible_type() const {
    return type;
}

LinkType Link::get_type() const {
    return type;
}

int Link::get_strength() const {
    return strength;
}

Position Link::get_position() const {
    return position;
}

bool Link::is_revealed() const {
    return revealed;
}

bool Link::is_shielded() const {
    return false;
}

void Link::consume_shield() {}

int Link::movement_distance() const {
    return 1;
}

void Link::move_to(Position p) {
    position = p;
}

void Link::reveal() {
    revealed = true;
}

void Link::set_type(LinkType t) {
    type = t;
}
