
#ifndef __RAYTRACER_FPSCOUNTER_HPP__
#define __RAYTRACER_FPSCOUNTER_HPP__


#include <cstdint>

namespace raytracer {
    class FpsCounter {
    public:
        FpsCounter();
        
        // Reinicia el contador de Fps
        void reset();
        
        // Marca el termino de un cuadro
        void endFrame();
        
        bool isDone() const;
        
        // Devuelve la cuenta actual de cuadros por segundo
        int getCount() const;
        
    private:
        mutable ::uint32_t lastTime;
        int current;
    };
}

#endif
