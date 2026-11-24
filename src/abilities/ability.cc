export module ability;

import abilitycontext;

export class Ability {
private:
    bool used{false};

public:
    virtual bool apply(AbilityContext &ctx, const AbilityTarget &target) = 0;
    bool is_used() const;
    void mark_used();
    virtual const char *get_name() const = 0;
    virtual ~Ability() = default;
};

