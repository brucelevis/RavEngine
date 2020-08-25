//
//  RenderEngine.cpp
//  RavEngine_Static
//
//  Copyright © 2020 Ravbug. All rights reserved.
//

#include "RenderEngine.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "GameplayStatics.hpp"
#include "CameraComponent.hpp"
#include "World.hpp"
#include "SDLSurface.hpp"
#include <memory>
#include "LLGL/RenderSystem.h"

#include <SDL_syswm.h>
#include <SDL.h>
#include <SDL_video.h>

#ifdef __APPLE_
#include <Cocoa/Cocoa.h>
#endif

using namespace std;
using namespace RavEngine;

std::shared_ptr<SDLSurface> RenderEngine::surface;

/**
Construct a render engine instance
@param w the owning world for this engine instance
*/
RenderEngine::RenderEngine(const WeakRef<World>& w) : world(w) {
	//call Init()
	Init();
}


RavEngine::RenderEngine::~RenderEngine()
{
}

/**
 Make the rendering system aware of an object
 @param e the entity to load
 */
void RenderEngine::Spawn(Ref<Entity> e){
	
}

/**
 Remove an entity from the system. This does NOT destroy the entity from the world.
 @param e the entity to remove
 */
void RenderEngine::Destroy(Ref<Entity> e){
	
}

/**
 Render one frame using the current state of every object in the world
 */
void RenderEngine::Draw(){
	//get the active camera
	auto components = Ref<World>(world.get())->Components();
	auto allcams = components.GetAllComponentsOfType<CameraComponent>();

	//set the view transform - all entities drawn will use this matrix
	for (auto& cam : allcams) {
		auto owning = Ref<CameraComponent>(cam);
		if (owning->isActive()) {
			//TODO: set projection
			auto size = surface->GetDrawableArea();
			owning->SetTargetSize(size.width, size.height);
			break;
		}
	}

    //draw each entity (TODO: multithread, skip statics)
	auto worldOwning = Ref<World>(world);
	auto entitylist = worldOwning->getEntities();
	for (auto& entity : entitylist) {
		entity->transform()->Apply();

    }

	//draw
}

/**
@return the name of the current rendering API
*/
const string RenderEngine::currentBackend(){
	
	return "Unknown";
}

SDL_Window* const RavEngine::RenderEngine::GetWindow()
{
	return surface->getWindowPtr();
}

/**
Update the viewport to the correct size of the container window
*/
void RenderEngine::resize() {
	//fix the window size
	auto size = surface->GetDrawableArea();

	//TOOD: update renderer size

#ifdef __APPLE__
	//resizeMetalLayer(getNativeWindow(window));
#endif
}

/**
Initialize static singletons. Invoked automatically if needed.
*/
void RenderEngine::Init()
{
	// don't initialize again if already initialized
	if (surface != nullptr)
	{
		return;
	}

	//create instance of surface
	surface = std::make_shared<RavEngine::SDLSurface>(LLGL::Extent2D{ 800, 480 }, "RavEngine");

#ifdef _WIN32
	const string backend = "Direct3D11";
#elif defined __APPLE__
	const string backend = "Metal";
#endif
	std::unique_ptr<LLGL::RenderSystem> renderer = LLGL::RenderSystem::Load(backend);

	LLGL::RenderContextDescriptor contextDesc;
	contextDesc.videoMode.resolution = surface->GetContentSize();
	LLGL::RenderContext* context = renderer->CreateRenderContext(contextDesc, surface);
	
#ifdef __APPLE__
    //need to make a metal layer on Mac
    //nativeWindow = setUpMetalLayer(nativeWindow);
#else
#endif
	
	//SDL_SetWindowTitle(window, (string("RavEngine - ") + currentBackend()).c_str());
}
