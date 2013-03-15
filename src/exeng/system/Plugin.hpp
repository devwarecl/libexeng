/**
 * @brief Documentacion pendiente
 */


#ifndef __EXENG_SYSTEM_PLUGIN_HPP__
#define __EXENG_SYSTEM_PLUGIN_HPP__

#include "../Object.hpp"
#include "../Version.hpp"

namespace exeng
{
    class EXENGAPI Root;

    namespace system
    {
        class EXENGAPI Library;
        
        /**
         * @brief Clase abstracta de plugins. Esta clase debe ser implementada por cada
         * plugin que desee extender ciertas interfaces del engine. Con esto, 
         * es posible tener un engine con un minimo de dependencias y dejar al usuario
         * decidir como quiere "extenderlo".
         */
        class EXENGAPI Plugin : public Object
        {
        public:
            virtual ~Plugin();
            
            
            /**
             * @brief Devuelve el nombre caracteristico del plugin. Es una cadena de caracteres, 
             * sin espacios, que lo identifica del resto.
             * @return 
             */
            virtual std::string getName() const = 0;

            
            /**
             * @brief Devuelve la descripcion del plugin. Debe ser una descripcion diseniada para que la puedan
             * leer los desarrolladores del cliente del engine.
             * @return 
             */
            virtual std::string getDescription() const = 0;
            
            
            /**
             * @brief Devuelve el numero de version del plugin.
             * @return 
             */
            virtual Version getVersion() const = 0;

            
            /**
             * @brief Inicializa el plugin, extendiendo un cierto conjunto de interfaces
             * disponibles en el objeto Root.
             * @param root
             */
            virtual void initialize(Root &root) = 0;
            
            
            /**
             * @brief Termina la ejecucion del plugin. Durante la operacion, el plugin
             * remueve todas las interfaces que implementó, dejando al engine en la misma situacion
             * en la que estaba antes de la operacion.
             */
            virtual void terminate() = 0;
        };
        
        
        /**
         * @brief La firma que debe poseer la funcion que aplique como un plugin.
         */
        typedef Plugin* (* ExengGetPluginObjectProc)(); 
    }
}


/**
 * @brief El nombre de la funcion que debe exportar
 */
#define EXENG_STR(value)  #value

#define EXENG_GET_PLUGIN_OBJECT_NAME ExengGetPluginObject
#define EXENG_GET_PLUGIN_OBJECT_NAME_STR EXENG_STR(EXENG_GET_PLUGIN_OBJECT_NAME)

/**
 * @brief Macro usada para facilitar la implementacion de plugins
 * 
 * Macro usada para facilitar la implementacion de plugins.
 * El engine se hace responsable por el tiempo de vida del objeto devuelto, 
 * el cual siempre sera el mismo. En caso de que el objeto sea destruido, 
 * el objeto devuelto no volvera a ser valido.
 */
#define EXENG_EXPORT_PLUGIN(PluginImpl)                                                         \
    extern "C"  Exeng::System::Plugin* EXENG_CALLCONV EXENG_GET_PLUGIN_OBJECT_NAME() EXENGAPI   \
    {                                                                                           \
        static PluginImpl *plugin = NULL;                                                       \
                                                                                                \
        if (plugin == NULL)                                                                     \
            plugin = new PluginImpl();                                                          \
                                                                                                \
        return plugin;                                                                          \
    }

#endif //__EXENG_SYSTEM_PLUGIN_HPP____
