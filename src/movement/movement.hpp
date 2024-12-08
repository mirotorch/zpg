#pragma once

#include "../transformation.h"
#include <memory>

class Movement 
{
public:
    virtual std::unique_ptr<Transformation> GetNextPosition() = 0;
};