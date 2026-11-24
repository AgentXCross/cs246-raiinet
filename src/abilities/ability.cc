export module ability;

import abilitycontext;

export class Ability {
private:
    bool used{false};

public:
    virtual bool apply(ability_context &ctx, const ability_target &target) = 0;
    bool used() const;
    void mark_used();
    virtual const char *getName() const = 0;
    virtual ~Ability() = default;
};

