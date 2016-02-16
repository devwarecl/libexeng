/**
 * @file Locker.hpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "Locker.hpp"
#include <stdexcept>

namespace xe { namespace gfx { namespace gl3 {

    Locker::Locker() : locked(false) {}
    
    void Locker::lock() {
        if (this->locked == true) {
            throw std::logic_error("Locker::lock: Resource already locked.");
        }
        
        this->locked = true;
    }


    void Locker::unlock() {
        if (this->locked == false) {
            throw std::logic_error("Locker::unlock: The resource isn't locked.");
        }
        
        this->locked = false;
    }


    bool Locker::tryLock() const {
        return !this->locked;
    }

}}}
