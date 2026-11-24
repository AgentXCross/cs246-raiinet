export module abilitycontext;

import <variant>;

import types;

export using AbilityTarget = std::variant<char, Position>;

export class AbilityContext {
public:
    virtual bool boost_link(AbilityTarget target) = 0;
    virtual bool placeFirewall(AbilityTarget target) = 0;
    virtual bool downloadOpponentLink(AbilityTarget target) = 0;
    virtual bool scanLink(AbilityTarget target) = 0;
    virtual bool polarizeLink(AbilityTarget target) = 0;
    virtual ~ability_context() = default;
};
