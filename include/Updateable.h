
#pragma once

class Updateable
{
public:
    virtual ~Updateable() {}
    virtual void update(unsigned long runtime);
};