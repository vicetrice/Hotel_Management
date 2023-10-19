#ifndef __VALORACIONES_HPP__
#define __VALORACIONES_HPP__

// INCLUIR LAS BIBLIOTECAS NECESARIAS
#include "utilidades.hpp"
#include "valoracion.hpp"
#include <string>

// IMPLEMENTAR LA CLASE Valoraciones DENTRO DEL NAMESPACE bblProgII
namespace bblProgII
{
        class Valoraciones
        {

                // ---------------------- MÉTODOS PÚBLICOS DE LA CLASE Valoraciones
        public:
                // Constructor por defecto.
                // Inicializa todas las listas (valoraciones positivas,
                // valoraciones negativas, palabras positivas y palabras negativas)
                // a listas vacías
                Valoraciones();

                // Constructor de copia
                Valoraciones(const Valoraciones &otro_objeto);

                // Destructor
                ~Valoraciones();

                // Lee desde fichero la lista de palabras positivas
                // y la almacena en el objeto. Si el fichero ha podido abrirse
                // correctamente para lectura, devuelve OK a través de 'res'. Si no,
                // devuelve FIC_ERROR.
                //  - nombre_fic (E): nombre del fichero de palabras positivas
                void cargar_palabras_positivas(const std::string &nombre_fic, Resultado &res);

                // Lee desde fichero la lista de palabras negativas
                // y la almacena en el objeto. Si el fichero ha podido abrirse
                // correctamente para lectura, devuelve OK a través de 'res'. Si no,
                // devuelve FIC_ERROR.
                //  - nombre_fic (E): nombre del fichero de palabras negativas
                void cargar_palabras_negativas(const std::string &nombre_fic, Resultado &res);

                // Lee valoraciones de un fichero de valoraciones y las incorpora a las
                // incorpora (añadiéndolas a las ya existentes) a la lista de valoraciones
                // actual. Las valoraciones deben insertarse en la lista correspondiente
                // a la clasificación --positiva o negativa-- del comentario que incluyen.
                // No puede haber valoraciones repetidas, es decir, no puede haber
                // valoraciones en el objeto (ya sea en la lista de valoraciones positivas
                // o negativas) con el mismo identificador de valoración.
                // La valoraciones deben insertarse en orden creciente de identificador
                // de valoración dentro de la lista correspondiente a su clasificación
                // (positiva o negativa).
                // Si el fichero puede abrirse correctamente para lectura, se leen las valoraciones,
                // se incorporan al objeto actual y se devuelve OK a través de 'res'. Si no,
                // se devuelve FIC_ERROR  a través de 'res'.
                // FORMATO DEL FICHERO:
                //  - El fichero debe comenzar con la siguiente cabecera (véase 'valoraciones.csv'):
                //      id_alojamiento,id_valoracion,fecha,id_revisor,nombre_revisor,comentario
                //  - Los datos deben separarse con comas
                //  - Si el nombre del revisor incluye comas, aparecerá en el fichero entre comillas dobles.
                //    Por ejemplo: "Smith, John"
                //  - Si el nombre del revisor NO incluye comas, no aparecerá en el fichero entre comillas dobles.
                //    Por ejemplo: John Smith
                //  - Si el comentario incluye comas, aparecerá en el fichero entre comillas dobles.
                //    Por ejemplo: "Este comentario, como puede verse, incluye comas"
                //  - Si el comentario no incluye comas, no aparecerá entre comillas dobles.
                //    Por ejemplo: Este comentario no necesita comillas porque no incluye comas
                // PARÁMETROS:
                //  - nombre_fic (E): nombre del fichero de valoraciones
                //  - res (S): resultado de la operación
                void cargar_valoraciones(const std::string &nombre_fic, Resultado &res);

                // Guarda en el fichero cuyo nombre se pasa como parámetro todas las valoraciones
                // almacenadas en el objeto. Primero se guardan las valoraciones positivas, en orden,
                // y luego se guardan las valoraciones negativas, también en orden.
                // El formato del fichero es el mismo que para el método 'cargar_valoraciones'
                // (véase el fichero 'valoraciones.csv'). Si el fichero puede abrirse para escritura,
                // se guardan en él las valoraciones y se devuelve OK a través de 'res'. Si no,
                // se devuelve FIC_ERROR a través de 'res'.
                // PARÁMETROS:
                //  - nombre_fic (E): nombre del fichero de escritura
                //  - res (S): resultado de la operación
                void guardar_valoraciones(const std::string &nombre_fic, Resultado &res) const;

                // Devuelve el número de valoraciones positivas y negativas almacenadas
                // PARÁMETROS:
                //  - positivas (S): número de valoraciones positivas
                //  - negativas (S): número de valoraciones negativas
                void numero_valoraciones(unsigned &positivas, unsigned &negativas) const;

                // Devuelve la lista de los identificadores de todas las valoraciones
                // almacenadas, positivas y negativas.
                // PARÁMETROS:
                //  - ids_positivas (S): ids de todas las valoraciones positivas
                //  - ids_negativas (S): ids de todas las valoraciones negativas
                void lista_valoraciones(Ids &ids_positivas, Ids &ids_negativas) const;

                // Devuelve el número de palabras positivas y negativas almacenadas
                // PARÁMETROS:
                //  - positivas (S): número de palabras positivas
                //  - negativas (S): número de palabras negativas
                void numero_palabras(unsigned &positivas, unsigned &negativas) const;

                // Indica si una valoración, cuyo id se pasa como parámetro,
                // está en alguna de las listas de valoraciones (positivas o negativas).
                // Si está, se devuelve a través de 'valoracion', se pone 'encontrada' a true
                // y se indica si está clasificada como positiva o negativa a través del parámetro
                // 'positiva'.
                // PARAMETROS:
                //  - id_valoracion (E): identificador de la valoración a buscar
                //  - valoracion (S): valoración
                //  - encontrada (S): indica si se ha encontrado (true) o no (false) la valoración
                //  - positiva (S): indica si la valoración está en la lista de valoraciones positivas (true)
                //                  o negativas (false)
                void buscar_valoracion(unsigned id_valoracion, Valoracion &valoracion, bool &encontrada, bool &positiva) const;

                // Inserta una valoración en la lista de valoraciones positivas o negativas,
                // en función de si el comentario que contiene es clasificado como positivo
                // o negativo, respectivamente. La valoración debe insertarse, en la lista
                // de valoraciones correspondiente a su clasificación, en orden creciente
                // de identificador de valoración. No puede haber dos valoraciones repetidas
                // (es decir, con el mismo id de valoración) en el objeto. Si la valoración
                // se ha insertado con éxito, se devuelve OK a través de 'res'. Si la valoración
                // ya existía, se devuelve YA_EXISTE.
                // PARÁMETROS:
                //  - valoracion (E): valoración a insertar
                //  - res (S): resultado de la operación
                void insertar_valoracion(const Valoracion &valoracion, Resultado &res);

                // Elimina una valoración cuyo id se pasa como parámetro.
                // Si la valoración se encuentra (puede estar en la lista de
                // valoraciones positivas o negativas), se devuelve OK a través de
                // res. Si no, se devuelve NO_EXISTE. Si se ha eliminado,
                // debe indicarse también, a través del parámetro 'positiva', si se
                // ha eliminado de la lista de valoraciones positivas (true) o
                // negativas (false).
                // PARÁMETROS:
                //  - id_valoracion (E): valoración que quiere elminarse
                //  - positiva (S): la valoración se ha eliminado de la lista de
                //                  valoraciones positivas (true) o negativas (false)
                //  - res (S): resultado de la operación
                void eliminar_valoracion(unsigned id_valoracion, bool &positiva, Resultado &res);

                // Modificar una valoración existente con los nuevos datos de la misma que se pasan
                // a través del parámetro 'valoracion'. Si el nuevo comentario de la valoración
                // es diferente al actual y su clasificación cambia (pasa de positiva a negativa,
                // o viceversa) debe moverse a la lista de valoraciones correspondiente a la clasificación
                // del nuevo comentario. Si la valoración existe (existe ese id de valoración) se modifica
                // y se devuelve OK a través de 'res'. Si no, se devuelve NO_EXISTE.
                void modificar_valoracion(const Valoracion &valoracion, Resultado &res);

                // Devuelve la lista de identificadores de valoraciones positivas y
                // negativas para un determinado alojamiento.
                // PARÁMETROS:
                //  - id_alojamiento (E): identificador de un alojamiento
                //  - ids_valoraciones_positivas (S): lista de ids de valoraciones positivas del alojamiento
                //  - ids_valoraciones_negativas (S): lista de ids de valoraciones negativas del alojamiento
                void valoraciones_alojamiento(unsigned id_alojamiento, Ids &ids_valoraciones_positivas, Ids &ids_valoraciones_negativas) const;

                // Devuelve la lista de identificadores de valoraciones positivas y
                // negativas para un determinado revisor.
                // PARÁMETROS:
                //  - id_revisor (E): identificador de un revisor
                //  - ids_valoraciones_positivas (S): lista de ids de valoraciones positivas del revisor
                //  - ids_valoraciones_negativas (S): lista de ids de valoraciones negativas del revisor
                void valoraciones_revisor(unsigned id_revisor, Ids &ids_valoraciones_positivas, Ids &ids_valoraciones_negativas) const;

                // Escribe por pantalla los datos de todas las valoraciones,
                // en el siguiente formato (nótese que se
                // usan tabuladores para formatear la salida):
                //  --- ID alojamiento:  <id_alojamiento>
                //  ID valoración:       <id_valoracion>
                //  Fecha:               <fecha>
                //  ID revisor:          <id_revisor>
                //  Nombre revisor:      <nombre_revisor>
                //  --- COMENTARIO:
                //  <comentario>
                //  *** VALORACIÓN: POSITIVA/NEGATIVA
                //
                // Deben salir primero las valoraciones positivas y luego las negativas.
                void escribir() const;

                // -------- MÉTODOS PÚBLICOS -----------------

                // Operador de asignación de la clase Valoraciones
                Valoraciones &operator=(const Valoraciones &otro_objeto);

                // Operador de comparación de igualdad de Valoraciones
                // (SOLO NECESARIO PARA LAS PRUEBAS UNITARIAS.)
                bool operator==(const Valoraciones &otro_objeto) const;

                // Función auxiliar
                // (SOLO NECESARIA PARA LAS PRUEBAS UNITARIAS.)
                void __consultar_elemento_pos(unsigned pos, bool val_pal, bool pos_neg, Valoracion &valoracion, std::string &palabra) const;

                // -------------------- PARTE PRIVADA DE LA CLASE Valoraciones
        private:
                // TIPOS NECESARIOS PARA LA DEFINICIÓN DE LOS ATRIBUTOS

                // Nodo para almacenar la información de una valoración
                struct NodoValoracion
                {
                        Valoracion valoracion;
                        NodoValoracion *sig;
                };

                // Tipo puntero a NodoValoracion
                typedef NodoValoracion *PtrValoracion; // Puntero nodo (lista de valoraciones)

                // Nodo para almacenar una palabra (cadena de caracteres)
                struct NodoPalabra
                {
                        std::string palabra;
                        NodoPalabra *sig;
                };

                // Tipo puntero a NodoPalabra
                typedef NodoPalabra *PtrPalabra; // Puntero a nodo (lista de palabras)

                // ------------ Atributos
                PtrValoracion val_pos, val_neg;    // Valoraciones positivas y negativas
                unsigned num_val_pos, num_val_neg; // Número de valoraciones positivas y negativas
                PtrPalabra pal_pos, pal_neg;       // Palabras positivas y negativas
                unsigned num_pal_pos, num_pal_neg; // Número de palabras positivas y negativas

                // ----------- MÉTODOS PRIVADOS

                // Lee del fichero cuyo nombre se pasa como parámetro una lista
                // de palabras y la devuelve a través del puntero 'palabras'.
                // El fichero comienza con una serie de líneas de comentarios, que
                // comienzan todas con el carácter ';'. A continuación, aparece la lista
                // de palabras ordenadas (en orden creciente) y separadas por saltos de línea.
                // (Véase el fichero 'positive-words.txt' como ejemplo.)
                // Si el fichero existe y ha podido abrirse para lectura, se leen las
                // palabras y se devuelve OK a través de 'res'. Si no, se devuelve
                // FIC_ERROR  a través de 'res'. Devuelve el número de palabras leídas
                // a través de 'num'
                //
                // PARÁMETROS:
                //  - fic (E): nombre del fichero de lectura
                //  - palabras (S): puntero para la lista de palabras
                //  - num (S): número de palabras leídas
                //  - res (S): resultado de la operación
                void leer_palabras(const std::string &fic, PtrPalabra &palabras, unsigned &num, Resultado &res) const;

                // Indica si una palabra está en la lista de palabras.
                // PARÁMETROS:
                //  - palabra (E): palabra que se busca
                //  - palabras (E): lista de palabras en la que se busca la palabra
                bool esta_en_lista(const std::string &palabra, PtrPalabra palabras) const;

                // Devuelve el número de palabras positivas y negativas de un comentario
                // PARÁMETROS:
                //  - comentario (E): cadena de caracteres correspondiente a un comentario, consistente
                //                    en una secuencia de palabras en minúscula (es decir, el comentario
                //                    debe estar preprocesado).
                //  - positivas (S): número de palabras del comentario clasificadas como positivas
                //                   (es decir, que están en la lista de palabras positivas del objeto)
                //  - negativas (S): número de palabras del comentario clasificadas como negativas
                //                   (es decir, que están en la lista de palabras negativas del objeto)
                void frecuencia_palabras_pos_neg(const std::string &comentario, unsigned &positivas, unsigned &negativas) const;

                // Dado un comentario, indica si es positivo (true) o negativo (false),
                // en función de si el número de palabras positivas que contiene es mayor
                // o igual al de palabras negativas, respectivamente.
                // El comentario debe preprocesarse antes de ser clasificado, para 1) eliminar
                // los signos de puntuación que contiene, 2) eliminar espacios repetidos, eliminar
                // todos los espacios que haya al principio o al final del comentario, y
                // 3) convertir todas las letras en minúsculas. Para ello, puede usarse la
                // función auxiliar 'preprocesar_comentario' disponible en valoraciones.cpp.
                // PARÁMETROS:
                //  - comentario (E): comentario (original, sin preprocesar) correspondiente a la
                //                    valoración de un alojamiento.
                bool analisis_de_sentimientos(const std::string &comentario) const;

                // Busca una valoración por su id_valoracion en una lista de valoraciones.
                // Devuelve un puntero 'ptr' apuntando a un nodo que contiene un id de valoración
                // mayor o igual que el que estoy buscando (o a nullptr, si no existe tal nodo),
                // y un puntero 'ant' apuntando al nodo anterior a ese nodo al que apunta 'ptr'
                // (o a nullptr, si 'ptr' apunta al primer nodo de la lista o la lista está vacía).
                // PARÁMETROS:
                //  - id_valoracion (E) : id de la valoración que estoy buscando
                //  - lista (E): lita de valoraciones en la que buscar la valoración
                //  - ptr (S): puntero que apunta a un nodo con id_valoracion mayor o igual que
                //             'id_valoracion'
                //  - ant (S): puntero que apunta al nodo anterior al que apunta 'ptr'
                //  - encontrada (S): indica si ha encontrado ese id de valoración o no
                void buscar_valoracion(unsigned id_valoracion,
                                       PtrValoracion lista,
                                       PtrValoracion &ptr,
                                       PtrValoracion &ant,
                                       bool &encontrada) const;

                // Inserta una valoración en la lista de valoraciones que
                // se pasa como parámetro. Si la valoración se ha podido
                // insertar correctamente, se devuelve OK a través de 'res'.
                // Si la valoración ya existía, se devuelve YA_EXISTE a
                // través de 'res'. La valoración debe insertarse en
                // orden creciente de id de valoración.
                // PARÁMETROS:
                //  - valoracion (E): valoración a insertar
                //  - lista (ES): lista de valoraciones donde se inserta
                //  - res (S): resultado de la operación
                void insertar_valoracion(const Valoracion &valoracion, PtrValoracion &lista, Resultado &res) const;

                // Elimina una valoración cuyo identificador se pasa como parámetro
                // de la lista de valoraciones que se pasa también como parámetro.
                // Si se encuentra la valoración en la lista, se elimina y se
                // devuelve OK a través de 'res'. Si no, se devuelve NO_EXISTE
                // a través de 'res'.
                // PARÁMETROS:
                //  - id_valoracion (E): id de la valoración a eliminar
                //  - lista (ES): lista de valoraciones
                //  - res (S): resultado de la operación
                void eliminar_valoracion(unsigned id_valoracion, PtrValoracion &lista, Resultado &res) const;

                // Borra completamente una lista de valoraciones
                // PARÁMETROS:
                //  - lista (ES): lista de valoraciones a borrar
                void borrar_valoraciones(PtrValoracion &lista) const;

                // Borra completamente una lista de palabras
                // PARÁMETROS:
                //  - lista (ES): lista de palabras a borrar
                void borrar_palabras(PtrPalabra &lista) const;

                // Devuelve una copia de la lista de valoraciones que se pasa
                // como parámetro.
                // PARÁMETROS:
                //  - lista (E): lista de valoraciones original
                PtrValoracion copiar_valoraciones(PtrValoracion lista) const;

                // Devuelve una copia de la lista de palabras que se pasa
                // como parámetro.
                // PARÁMETROS:
                //  - lista (E): lista de palabras original
                PtrPalabra copiar_palabras(PtrPalabra lista) const;
        };
}

#endif