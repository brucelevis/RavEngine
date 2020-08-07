//
//  WeakSharedObjectRef.cpp
//  RavEngine_Static
//
//  Copyright © 2020 Ravbug. All rights reserved.
//

#include "WeakRef.hpp"
#include "SharedObject.hpp"

using namespace std;

//static definitions
mutex WeakRefBase::mtx;
WeakRefBase::TrackedPtrStore WeakRefBase::WeakReferences;