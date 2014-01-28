/**
 * @file Application.hpp
 * @brief Definition of the Application class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_FRAMEWORK_APPLICATION_HPP__
#define __EXENG_FRAMEWORK_APPLICATION_HPP__

#include <exeng/Config.hpp>

#include <string>
#include <vector>

namespace exeng { namespace framework {
    
    typedef std::vector< std::string > StringVector;
    
    /**
     * @brief The different status of an application.
     */
    enum class ApplicationStatus {
        Running,
        Terminated
    };
    
    /**
     * @brief Basic application framework.
     */
    class EXENGAPI Application {
    public:
        virtual ~Application();
        
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
         * @brief Procesa la entrada del usuario, actualizando 
         * adecuadamente los estados internos de la escena.
         */
        virtual void pollEvents() = 0;
        
        /**
         * @brief Devuelve el estado actual general de la aplicacion
         */
        virtual ApplicationStatus getStatus() const = 0;
        
        /**
         * @brief Actualiza, en base a los estados internos.
         */
        virtual void update(double seconds) = 0;
        
        /**
         *  @brief Presenta los resultados de la renderizacion al usuario
         */
        virtual void render() = 0;
        
        /**
         * @brief Devuelve el codigo de salida de la aplicacion.
         * 
         * El valor es valido siempre que el estado actual de 
         * la aplicacion sea ApplicationStatus::Stopped
         */
        virtual int getExitCode() const = 0;
        
        /**
         * @brief Libera los recursos alojados por la aplicacion.
         */
        virtual void terminate() = 0;
    
    public:
        /**
         * @brief Executes the specified application.
         */
        static int run(Application *app, const StringVector& cmdLine);
    };

}}

#endif  // __EXENG_FRAMEWORK_APPLICATION_HPP__
