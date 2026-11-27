module ability;

import <string>;

import abilitycontext;

bool Ability::is_used() const {
    return used;
}

void Ability::mark_used() {
    used = true;
}

bool LinkBoost::apply(AbilityContext &ctx, const AbilityTarget &target) {
    return ctx.boost_link(target);
}

std::string LinkBoost::get_name() const {
    return "LinkBoost";
}

bool Firewall::apply(AbilityContext &ctx, const AbilityTarget &target) {
    return ctx.place_firewall(target);
}

std::string Firewall::get_name() const {
    return "Firewall";
}

bool Download::apply(AbilityContext &ctx, const AbilityTarget &target) {
    return ctx.download_opponent_link(target);
}

std::string Download::get_name() const {
    return "Download";
}

bool Scan::apply(AbilityContext &ctx, const AbilityTarget &target) {
    return ctx.scan_link(target);
}

std::string Scan::get_name() const {
    return "Scan";
}

bool Polarize::apply(AbilityContext &ctx, const AbilityTarget &target) {
    return ctx.polarize_link(target);
}

std::string Polarize::get_name() const {
    return "Polarize";
}

bool Shield::apply(AbilityContext &ctx, const AbilityTarget &target) {
    return ctx.shield_link(target);
}

std::string Shield::get_name() const {
    return "Shield";
}

bool Disguise::apply(AbilityContext &ctx, const AbilityTarget &target) {
    return ctx.disguise_link(target);
}

std::string Disguise::get_name() const {
    return "Disguise";
}

bool Strengthen::apply(AbilityContext &ctx, const AbilityTarget &target) {
    return ctx.strengthen_link(target);
}

std::string Strengthen::get_name() const {
    return "Strength";
}
