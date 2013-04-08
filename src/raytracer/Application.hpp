
#ifndef __RAYTRACER_APPLICATION_HPP__
#define __RAYTRACER_APPLICATION_HPP__

#include <vector>
#include <string>

namespace raytracer {
    typedef std::vector<std::string> StringVector;

    /**
     * @brief Describe los posibles estados en los que se puede encontrar una aplicacion de renderizacion determinada.
     */
    namespace ApplicationStatus {
        enum Enum {
            Running,
            Stopped
        };
    }


    /**
     * @brief Interfaz a una aplicacion grafica de tiempo real.
     */
    class Application {
    public:
        inline virtual ~Application() {}
        
        /**
         * @brief Inicializa una aplicacion.
         * 
         * Carga y genera todos los recursos necesarios
         * para su ejecucion.
         */
        virtual void initialize(const StringVector& cmdLine) = 0;

        /**
         * @brief Devuelve el tiempo, en segundos, que tardo en completarse el ultimo cuadro.
         */
        virtual double getFrameTime() const = 0;
        
        /**
         * @brief Procesa la entrada del usuario, actualizando adecuadamente los estados internos de la escena.
         */
        virtual void processInput() = 0;
        
        /**
         * @brief Devuelve el estado actual general de la aplicacion
         */
        virtual ApplicationStatus::Enum getStatus() = 0;
        
        /**
         * @brief Actualiza, en base a los estados internos, los
         */
        virtual void update(double seconds) = 0;
        
        /**
         *  @brief Presenta los resultados de la renderizacion al usuario
         */
        virtual void present() = 0;
        
        /**
         * @brief Devuelve el codigo de salida de la aplicacion.
         * 
         * El valor es valido siempre que el estado actual de la aplicacion sea ApplicationStatus::Stopped
         */
        virtual int getExitCode() const = 0;
        
        /**
         * @brief Libera los recursos alojados por la aplicacion.
         */
        virtual void terminate() = 0;
        
        /**
         * @brief Ejecuta la aplicacion actual.
         */
        static int run(const StringVector& cmdLine);
        
        /**
         * @brief Establece la aplicacion actual a ejecutar
         */
        static bool set(Application *app);
        
    private:
        
        /**
         * @brief La instancia actual de la aplicacion
         */
        static Application *instance;
    };
}

#endif  //__RAYTRACER_APPLICATION_HPP__
