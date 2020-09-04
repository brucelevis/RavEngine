
#include "InputSystem.hpp"
#include "GameplayStatics.hpp"
#include <SDL_events.h>

using namespace std;
using namespace RavEngine;


InputSystem::InputSystem() {
    
}

/**
 * Initialize game controller inputs
 */
void InputSystem::InitGameControllers() {
    //setup game controllers
    int numControllers = 0;

    //determine which are controllers
    int numJoysticks = SDL_NumJoysticks();
    for (int i = 0; i < numJoysticks; ++i) {
        if (SDL_IsGameController(i)) {
            ++numControllers;
        }
    }

    //register all the controllers
    for (int i = 0; i < numControllers; ++i) {
        SDL_GameController* controller = SDL_GameControllerOpen(i);
        if (SDL_GameControllerGetAttached(controller) == 1) {
            connectedControllers.insert(controller);
        }
    }
    SDL_GameControllerEventState(SDL_ENABLE);
}

void InputSystem::tick() {
    //action mappings
    for (Event& evt : actionValues){
        //get the list of functions to invoke
        for (auto& a : codeToAction[evt.ID]) {
            if (actionMappings.find(a) != actionMappings.end()) {
                auto toInvoke = actionMappings.at(a);

                //determine which to invoke
                for (auto& pair : toInvoke) {
                    if (pair.second == evt.value) {
                        pair.first.first();
                    }
                }
            }
        }
    }
    actionValues.clear();
    
    //call all axis mappings
    for (auto& pair : codeToAxis){
        for (auto& a : pair.second) {
            if (axisMappings.find(a) != axisMappings.end()) {
                auto scale = axisScalars[pair.first];
                auto val = scale * axisValues[pair.first];
                //cout << pair.second << " -> " << val << endl;
                for (auto& f : axisMappings.at(a)) {
                    f.first(val);
                }
            }
        }
    }

    //mouse velocity needs to be cleared
    reg_axis(static_cast<int>(Special::MOUSEMOVE_XVEL), 0);
    reg_axis(static_cast<int>(Special::MOUSEMOVE_YVEL), 0);
}

/**
 * Add a key event
 * @param state true = pressed, false = released
 * @param charcode the keycode of the key central to the event
 */
void InputSystem::SDL_key(bool state, int charcode)
{
    //axis mapping?
    if (axisScalars.find(charcode) != axisScalars.end()){
        axisValues[charcode] = state;
    }
    
    //action mapping?
    if (awareActionValues.find(charcode) != awareActionValues.end()){
        actionValues.push_back({charcode,static_cast<ActionState>(state)});
    }
}

/**
 * Add a mouse movement event
 * @param x the x coordinate of the cursor (top-left origin)
 * @param y the y coordinate of the cursor (top-left origin)
 * @param xvel the x velocity of the cursor
 * @param yvel the y velocity of the cursor
 */
void InputSystem::SDL_mousemove(float x, float y, int xvel, int yvel)
{
    //mouse movements are axis events only
    reg_axis(static_cast<int>(Special::MOUSEMOVE_X),x);
    reg_axis(static_cast<int>(Special::MOUSEMOVE_Y),y);
    reg_axis(static_cast<int>(Special::MOUSEMOVE_XVEL), xvel);
    reg_axis(static_cast<int>(Special::MOUSEMOVE_YVEL), yvel);
}

void InputSystem::SDL_mousekey(bool state, int charcode)
{
    //clicks are treated the same as keyboard input
    SDL_key(state, charcode);
}

void InputSystem::SDL_ControllerAxis(int axisID, float value)
{
    reg_axis(axisID, value);
}

//need to remove dynamic mapping
InputSystem::~InputSystem() {
    
}

/**
 Define an axis mapping by name. If the mapping already exists, an additonal input is created for the mapping. Axis maps are called every frame regardless of value.
 @param name the string identifier for the mapping
 @param Id the input ID (scancode, etc) for the mapping
 @param scale the scalar to multiply against the axis value
 */
void InputSystem::AddAxisMap(const std::string& name, int Id, float scale){
    
    //add so that tick is aware of it
    axisScalars[Id] = scale;
    codeToAxis[Id].push_back(name);
}

/**
Define an action mapping by name. If the mapping already exists, an additonal input is created for the mapping. The values of an action map may be 0 (off / released), or 1 (on / pressed). Action maps are called when they occur.
  @param name the string identifier for the mapping
 @param Id the input ID (scancode, etc) for the mapping
 */
void InputSystem::AddActionMap(const std::string& name, int Id){
    
    //add so that tick is aware of this
    awareActionValues.insert(Id);
    codeToAction[Id].push_back(name);
}

void InputSystem::RemoveActionMap(const std::string& name, int Id)
{
    //remove from ID tracking lists
    awareActionValues.erase(Id);
    codeToAction.erase(Id);
}

void InputSystem::RemoveAxisMap(const std::string& name, int Id)
{
    //remove from ID tracking lists
    axisValues.erase(Id);
    axisScalars.erase(Id);
    codeToAction.erase(Id);
}

void RavEngine::InputSystem::UnbindAllFor(IInputListener* act)
{
	//unbind axis maps
	for(const auto& p : axisMappings){
		auto key = p.second;
		key.remove_if([&act](std::pair<axisCallback, RavEngine::IInputListener*>& v) -> bool {
			return v.second == act;
		});
	}
	//unbind action maps
	for(const auto& p : actionMappings){
		auto key = p.second;
		//key.remove_if(
	}
}

