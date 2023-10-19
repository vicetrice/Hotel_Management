#ifndef __UTILIDADES__
#define __UTILIDADES__

#include <array>
#include <iostream>

namespace bblProgII
{
    // Resultado de las operaciones
    // (los valores de las constantes simbólicas son
    //  arbitrarios).
    typedef unsigned Resultado;
    const Resultado OK = 0, // Okey
        VAL_ERROR = 1,      // Error en los valores de los parámetros
        FIC_ERROR = 2,      // Error en la apertura de fichero
        NO_EXISTE = 3,      // El dato a consultar no existe
        YA_EXISTE = 4,      // El dato a insertar ya existe
        LISTA_LLENA = 5;    // El dato no puede insertarse: lista llena

    // Escribe por pantalla la cadena de caracteres
    // correspondiente al error.
    // Parámetros:
    // 		- res (E): código de error
    void escribir_resultado(const Resultado &res);

    // Array incompleto de identificadores de alojamientos
    // (necesario para alguno de los métodos de la clase Alojamientos)
    const unsigned MAX_NUM_IDS = 3000;
    struct Ids
    {
        std::array<unsigned, MAX_NUM_IDS> ids;
        unsigned num_ids;
    };
} // namespace bblProgII
#endif