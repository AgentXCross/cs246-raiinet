module linkdecorator;

LinkDecorator::LinkDecorator(std::unique_ptr<Link> component):
    Link{
        component->get_id(),
        component->get_type(),
        component->get_strength(),
        component->get_position()
    },
    component{std::move(component)} {}

char LinkDecorator::get_id() const {
    return component->get_id();
}

LinkType LinkDecorator::get_visible_type() const {
    return component->get_visible_type();
}

LinkType LinkDecorator::get_type() const {
    return component->get_type();
}

int LinkDecorator::get_strength() const {
    return component->get_strength();
}

Position LinkDecorator::get_position() const {
    return component->get_position();
}

bool LinkDecorator::is_revealed() const {
    return component->is_revealed();
}

bool LinkDecorator::is_shielded() const {
    return component->is_shielded();
}

void LinkDecorator::consume_shield() {
    component->consume_shield();
}

int LinkDecorator::movement_distance() const {
    return component->movement_distance();
}

void LinkDecorator::move_to(Position p) {
    component->move_to(p);
}

void LinkDecorator::reveal() {
    component->reveal();
}

void LinkDecorator::set_type(LinkType t) {
    component->set_type(t);
}

BoostedLink::BoostedLink(std::unique_ptr<Link> component):
    LinkDecorator{std::move(component)} {}

int BoostedLink::movement_distance() const {
    return component->movement_distance() + 1;
}

StrengthenedLink::StrengthenedLink(std::unique_ptr<Link> component):
    LinkDecorator{std::move(component)} {}

int StrengthenedLink::get_strength() const {
    const int strength{component->get_strength()};
    return strength < 4 ? strength + 1 : 4;
}

ShieldedLink::ShieldedLink(std::unique_ptr<Link> component):
    LinkDecorator{std::move(component)} {}

bool ShieldedLink::is_shielded() const {
    return shield_active || component->is_shielded();
}

void ShieldedLink::consume_shield() {
    if (shield_active) {
        shield_active = false;
    } else {
        component->consume_shield();
    }
}

DisguisedLink::DisguisedLink(std::unique_ptr<Link> component):
    LinkDecorator{std::move(component)} {}

LinkType DisguisedLink::get_visible_type() const {
    if (!component->is_revealed()) {
        return component->get_visible_type();
    }

    return component->get_visible_type() == LinkType::DATA
        ? LinkType::VIRUS
        : LinkType::DATA;
}
