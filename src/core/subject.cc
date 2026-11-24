export module subject;

import gamedisplay;


export class Subject {
public:
    virtual void attack(std::unique_ptr<GameDisplay>) = 0
    virtual void notify_displays() = 0
};

