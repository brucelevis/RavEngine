//
//  RenderEngine.hpp
//  RavEngine_Static
//
//  Copyright © 2020 Ravbug. All rights reserved.
//

#pragma once
#include "SharedObject.hpp"
#include "Entity.hpp"
#include <list>
#include "WeakRef.hpp"

class View;
class Engine;
class Renderer;

class RenderEngine : public SharedObject{
public:
    virtual ~RenderEngine(){};
    void Spawn(Ref<Entity> e);
    void Destroy(Ref<Entity> e);
    RenderEngine(const WeakRef<World>& w);
    void Draw();
	
	static const std::string currentBackend();
    WeakRef<World> world;

protected:
    View* filamentView;
    Engine* filamentEngine;
    Renderer* filamentRenderer;
};
