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

#ifndef __EXENG_GRAPHICS_GL3_LOCKER_HPP__
#define __EXENG_GRAPHICS_GL3_LOCKER_HPP__

namespace exeng {
namespace graphics {
namespace gl3 {

/**
 * @brief The Locker class
 */
class Locker {
public:
    Locker();
    
    /**
     * @brief lock
     */
    void lock();
    
    /**
     * @brief unlock
     */
    void unlock();
    
    /**
     * @brief tryLock
     * @return 
     */
    bool tryLock() const;
    
private:
    bool locked;
};
}
}
}


#endif // LOCKER_HPP
