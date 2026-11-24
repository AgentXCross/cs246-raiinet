export module abilitycontext;

import <variant>;

import types;

export using AbilityTarget = std::variant<char, Position>;

export class AbilityContext {
public:
    virtual bool boost_link(AbilityTarget target) = 0;
    virtual bool place_firewall(AbilityTarget target) = 0;
    virtual bool download_opponent_link(AbilityTarget target) = 0;
    virtual bool scan_link(AbilityTarget target) = 0;
    virtual bool polarize_link(AbilityTarget target) = 0;
    virtual ~AbilityContext() = default;
};
