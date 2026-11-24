export module ability;

import abilitycontext;

export class Ability {

    bool used = false;

  public:
    
    virtual bool apply(ability_context &ctx, const ability_target &target) = 0;
    bool isUsed() const {
        return used;
    }
    void markUsed() {
        used = true;
    }
    virtual const char *getName() const = 0;
    
    virtual ~Ability() = default;
}

