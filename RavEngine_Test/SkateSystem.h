//
//  SkateSystem.h
//  MacFramework
//
//  Copyright © 2020 Ravbug. All rights reserved.
//

#pragma once
#include "System.hpp"

/**
 This system simply moves an entity along one axis
 */
class Skate : public System{
public:
    virtual ~Skate(){}
    
    virtual void Tick(float fpsScale, Ref<Entity> e) const{
        auto newPos = e->transform()->GetLocalPosition();
        newPos += 5 * fpsScale;
        e->transform()->SetLocalPosition(newPos);
    }
};