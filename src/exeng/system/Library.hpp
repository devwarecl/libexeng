/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SYSTEM_LIBRARY_HPP__
#define __EXENG_SYSTEM_LIBRARY_HPP__

#include <string>
#include <exeng/Object.hpp>

namespace exeng {
    namespace system  {
        typedef void* FunctionPtr;

        class EXENGAPI Library : public Object {
        public:
            Library();
            
            explicit Library(const std::string &libraryName);
            
            virtual ~Library();
            
            /**
             * @brief Carga la biblioteca dinamica indicada. Si no se puede cargar por alguna 
             * razon, lanza una excepcion en tiempo de ejecucion.
             * @param libraryName
             */
            void load(const std::string &libraryName);
            
            /**
             * @brief Descarga la biblioteca dinamica de la memoria.
             */
            void unload();
            
            /**
             * @brief Comprueba si la biblioteca dinamica ya esta cargada.
             * @return 
             */
            bool isValid() const;
            
            /**
             * @brief Devuelve la ruta completa del archivo de la biblioteca que fue cargada.
             * @return 
             */
            std::string getFileName() const;

            /**
             * @brief Devuelve el nombre de la libreria.
             * @return 
             */
            std::string getName() const;
            
            /**
             * @brief Devuelve un puntero con la direccion de memoria hacia la funcion con el nombre indicado.
             * @param name Una cadena std::string con el nombre de la biblioteca en tiempo de ejecucion.
             * @return 
             */
            FunctionPtr getFunctionPtr(const std::string& name);
            
            /**
             * @brief Devuelve la representacion en cadena de la biblioteca en tiempo de ejecucion.
             * @return 
             */
            virtual std::string toString() const;

        private:
            struct Private;
            Private* impl;

		private:
			Library(const Library& lib);
            Library& operator=(const Library& lib);
        };
    }
}

#endif	//__EXENG_SYSTEM_LIBRARY_HPP__
