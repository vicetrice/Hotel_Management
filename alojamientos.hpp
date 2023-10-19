#ifndef ___ALOJAMIENTOS_HPP__
#define ___ALOJAMIENTOS_HPP__

#include "utilidades.hpp"
#include "alojamiento.hpp"
#include <string>
#include <array>

// Definir la clase Alojamientos dentro del namespace bblProgII
namespace bblProgII
{
        // -------- MÉTODOS PÚBLICOS DE LA CLASE Alojamientos
        class Alojamientos
        {
        public:
                // Constructor por defecto.
                // Inicializa la lista de alojamientos a una lista vacía
                Alojamientos();

                // Constructor de copia
                Alojamientos(const Alojamientos &otro_objeto);

                // Destructor de la clase
                ~Alojamientos();

                // ------------------ MÉTODOS DE CONSULTA

                // Devuelve el alojamiento cuyo id se pasa como parámetro.
                // Si el alojamiento existe en la lista, se devuelve OK
                // a través del parámetro 'res'. Si no, se devuelve NO_EXISTE
                // PARÁMETROS:
                //  - id_alojamiento (E): id del alojamiento a consultar
                //  - alojamiento (S): el alojamiento consultado
                //  - res (S): resultado de la operación de consulta
                void consultar_alojamiento(unsigned id_alojamiento, Alojamiento &alojamiento, Resultado &res) const;

                // Devuelve el número de alojamientos turísticos almacenados en la lista
                unsigned numero_alojamientos() const;

                // Devuelve los identificadores de todos los alojamientos
                // PARÁMETROS:
                //  - ids_alojamientos (S): lista de ids de todos los alojamientos
                void lista_alojamientos(Ids &ids_alojamientos) const;

                // Devuelve la lista de los identificadores de alojamientos de un
                // determinado anfitrión cuyo identificador se pasa como parámetro.
                // Los identificadores deben devolverse en orden creciente.
                // PARÁMETROS:
                //  - id_anfitrion (E): identificador del anfitrión
                //  - ids_alojamientos (S): lista (array incompleto) con los identificadores
                //                          de los alojamientos pertenecientes a ese anfitrion
                //                          (en orden creciente).
                void alojamientos_anfitrion(unsigned id_anfitrion, Ids &ids_alojamientos) const;

                // Dada la latitud y la longitud de un punto y una distancia en kilómetros,
                // devuelve la lista con los ids de los alojamientos que están, como máximo
                // a esa distancia del punto dado.
                // PARÁMETROS:
                //  - latitud (E): latitud de un punto dado en el plano
                //  - longitud (E): longitud de un punto dado en el plano
                //  - kms (E): distancia máxima en kilómetros
                //  - ids_alojamientos (S): identificadores de los alojamientos
                //                          que están, como mucho, a esa distancia
                //                          del punto dado.
                void alojamientos_alrededor(double latitud, double longitud, double kms, Ids &ids_alojamientos) const;

                // Devuelve la lista con los identificadores de alojamientos de un
                // determinado barrio.
                // PARÁMETROS:
                //   - barrio (E): un barrio de la ciudad
                //   - ids_alojamientos (S): lista de los alojamientos de ese barrio
                void alojamientos_barrio(const std::string &barrio, Ids &ids_alojamientos) const;

                // Devuelve la lista con los identificadores de todos los
                // alojamientos de un tipo concreto de alojamiento.
                // PARÁMETROS:
                //  - tipo_alojamiento (E): tipo de alojamiento
                //  - ids_alojamientos (S): lista de alojamientos de ese tipo
                void alojamientos_tipo(const std::string &tipo_alojamiento, Ids &ids_alojamientos) const;

                // Dado un precio en euros, devuelve la lista de alojamientos cuyo precio
                // por noche es inferior o igual a ese precio.
                // PARÁMETROS:
                //  - precio (E): máximo precio por noche
                //  - ids_alojamientos (S): lista de alojamientos con precio igual o inferior
                //                          al precio dado
                void alojamientos_precio(double precio, Ids &ids_alojamientos) const;

                // Dado un número de noches, devuelve la lista con los identificadores
                // de los alojamientos cuyo mínimo número de noches de alquiler es menor
                // o igual que el número de noches dado.
                // PARÁMETROS:
                //  - num_noches (E): número de noches
                //  - ids_alojamientos (S): lista de alojamientos con mínimo número de noches
                //                          de alquiler menor o igual que el número de noches
                //                          dado.
                void alojamientos_noches(unsigned num_noches, Ids &ids_alojamientos) const;

                // Devuelve la lista de ids de los alojamientos que cumplen con TODOS los
                // criterios de filtrado siguientes:
                //  - Si 'barrio' no es una cadena vacía, devuelve solo los alojamientos de ese barrio.
                //    Si es una cadena vacía, no tiene en cuenta el barrio como criterio de filtrado.
                //  - Y, además, si 'tipo_alojamiento' no es una cadena vacía, devuelve solo los alojamientos de ese
                //    tipo. Si es una cadena vacía, no tienen en cuenta el tipo de alojamiento como
                //    criterio de filtrado.
                //  - Y, además, si 'precio' > 0, devuelve solo los alojamientos de ese precio como máximo. Si
                //    'precio' es cero, no tiene en cuenta el precio como criterio de filtrado.
                //  - Y, además, si 'num_noches' > 0, devuelve solo los alojamientos cuyo mínimo número de noches
                //    de alquiler es menor o igual que 'num_noches'. Si 'num_noches' es cero, no se tiene
                //    en cuenta como criterio de filtrado.
                // PARÁMETROS:
                //  - barrio (E): barrio donde deben estar los alojamientos
                //  - tipo_alojamiento (E): tipo de alojamiento
                //  - precio (E): precio máximo por noche que se desea
                //  - num_noches (E): número mínimo de noches que exige el alojamiento
                //  - ids_alojamientos (S): lista de los ids de los alojamientos que
                //                          cumplen con todos los criterios.
                void alojamientos_filtros(const std::string &barrio,
                                          const std::string &tipo_alojamiento,
                                          double precio,
                                          unsigned num_noches,
                                          Ids &ids_alojamientos) const;

                // Escribe en fichero los datos correspondientes a los
                // alojamientos existentes en la lista actual de alojamientos.
                // Si el fichero puede abrirse para escritura con éxito, se guardan en él
                // todos los alojamientos actuales y se devuelve OK a través de 'res'.
                // Si el fichero no puede abrirse para escritura, se devuelve FIC_ERROR
                // a través de 'res'.
                // FORMATO DEL FICHERO:
                //  - El fichero debe comenzar con la siguiente cabecera (véase 'alojamientos.csv'):
                //      id_alojamiento,nombre,id_anfitrion,nombre_anfitrion,barrio,latitud,longitud,tipo_alojamiento,precio,minimo_noches,disponibilidad_365
                //  - Los datos deben separarse con comas
                //  - Si el nombre del alojamiento incluye comas, debe guardarse en el fichero entre comillas dobles.
                //    Por ejemplo: "Design, style & vintage by Odenplan"
                // PARÁMETROS:
                //  - nombre_fichero (E): nombre del fichero de datos de alojamientos
                //  - res (S): resultado de la operación.
                void escribir_en_fichero(const std::string &nombre_fichero, Resultado &res) const;

                // Escribe por pantalla los datos de todos los alojamientos,
                // en el siguiente formato para cada alojamiento (nótese que se
                // usan tabuladores para formatear la salida):
                //  --- ID alojamiento:  <id_alojamiento>
                //  Nombre alojamiento:  <nombre>
                //  ID anfitrión:        <id_anfitrion>
                //  Nombre anfitrión:    <nombre_anfitrion>
                //  Barrio (área):       <barrio>
                //  Localización:        <latitud>, <longitud>
                //  Tipo de alojamiento: <tipo_alojamiento>
                //  Precio por noche:    <precio>
                //  Mínimo de noches:    <minimo_noches>
                //  Disponibilidad/año:  <disponibilidad_365>
                void escribir() const;

                // ----------------- MÉTODOS DE MODIFICACIÓN

                // Inserta un alojamiento en la lista de alojamientos, en
                // ORDEN CRECIENTE de identificador del alojamiento. Si ya
                // existía un alojamiento con ese identificador, no se inserta
                // y se devuelve YA_EXISTE a través de 'res' (no puede haber
                // alojamientos con identificadores repetidos). Si no, si el
                // array está lleno, se devuelve LISTA_LLENA a través de 'res'.
                // Si no, se inserta el alojamiento en orden y se devuelve OK
                // a través de 'res'.
                // PARÁMETROS:
                //  - alojamiento (E): alojamiento a insertar
                //  - res (S): resultado de la operación
                void insertar_alojamiento(const Alojamiento &alojamiento, Resultado &res);

                // Modifica los datos de un alojamiento de la lista de alojamientos
                // Si no existe un alojamiento con ese identificador,
                // se devuelve NO_EXISTE a través de 'res'. Si existe,
                // se modifican todos los datos del alojamiento y se devuelve OK
                // a través de 'res'.
                // PARÁMETROS:
                //  - alojamiento (E): alojamiento a modificar
                //  - res (S): resultado de la operación
                void modificar_alojamiento(const Alojamiento &alojamiento, Resultado &res);

                // Elimina de la lista de alojamientos el alojamiento cuyo id
                // se pasa como parámetro. Si no existe un alojamiento con ese id,
                // se devuelve NO_EXISTE a través de 'res'. Si existe un alojamiento
                // con ese id, se elimina de la lista y se devuelve OK a través de
                // 'res'.
                // PARÁMETROS:
                //  - id_alojamiento (E): id del alojamiento a eliminar
                //  - res (S): resultado de la operación
                void eliminar_alojamiento(unsigned id_alojamiento, Resultado &res);

                // Lee de fichero los datos correspondientes a una serie de alojamientos y los
                // incorpora a los alojamientos existentes en la lista actual de alojamientos.
                // No puede haber alojamientos repetidos, esto es, alojamientos con el mismo
                // identificador de alojamiento. Si el fichero existe, se abre y se leen todos
                // los alojamientos almacenados en él, incorporándose a la lista de alojamientos
                // actual y devolviéndose OK a través de 'res'. Si el fichero no existe o no
                // puede abrirse para lectura, se devuelve FIC_ERROR a través de 'res'.
                // (VÉASE EL FORMATO DEL FICHERO EN escribir_alojamientos).
                // PARÁMETROS:
                //  - nombre_fichero (E): nombre del fichero de datos de alojamientos
                //  - res (S): resultado de la operación.
                void leer_alojamientos(const std::string &nombre_fichero, Resultado &res);

                // OPERADORES SOBRECARGADOS

                // Operador de asignación de Alojamientos
                
                Alojamientos &operator=(const Alojamientos &otro_objeto) = default;

                // Operador de comparación de Alojamientos
                // (NECESARIO PARA LAS PRUEBAS UNITARIAS)
                bool operator==(const Alojamientos &otro_objeto) const;

                // Operador [] de acceso mediante índice
                // (NECESARIO PARA LAS PRUEBAS UNITARIAS)

                Alojamiento operator[](unsigned indice) const;

                // ------------------- PARTE PRIVADA DE LA CLASE Alojamientos
        private:
                // --- DEFINICIÓN DE CONSTANTES Y ATRIBUTOS

                static const unsigned MAX_ALOJAMIENTOS = 3000;

                // Atributos
                std::array<Alojamiento, MAX_ALOJAMIENTOS> alojamientos; // array de alojamientos
                unsigned num_alojamientos;                              // Número de alojamientos almacenados en la lista

                // -------------------------- MÉTODOS PRIVADOS

                // Busca un alojamiento por su identificador.
                // Devuelve la posición del array donde hay un alojamiento
                // cuyo identificador es mayor o igual que el que se está
                // buscando. Devuelve verdadero a través de 'encontrado' si
                // encuentra el alojamiento; devuelve falso en otro caso.
                // PARÁMETROS:
                //  - id_alojamiento (E): id del alojamiento a buscar
                //  - posicion (S): posición en el array donde hay un alojamiento
                //                  con identificador mayor o igual.
                //  - encontrado (S): indica si se ha encontrado el id buscado
                void buscar_alojamiento(unsigned id_alojamiento, unsigned &posicion, bool &encontrado) const;

                // Abre hueco en el array, desplazando "a la derecha" todos
                // los alojamientos a partir de la posición que se pasa
                // como parámetro (incluida esta).
                // PARÁMETROS:
                //  - posicion (E): posición a partir de cual se abre hueco
                // PRECONDICIÓN: posicion <= num_alojamientos
                void abrir_hueco(unsigned posicion);

                // Cierra hueco en el array, desplazando "a la izquierda" todos
                // los alojamientos a partir de la posición + 1 que se pasa
                // como parámetro, eliminando, por tanto, el alojamiento de la
                // posición dada.
                // PARÁMETROS:
                //  - posicion (E): posición a partir de cual se cierra hueco
                // PRECONDICIÓN: posicion < num_alojamientos
                void cerrar_hueco(unsigned posicion);
                };
}

#endif