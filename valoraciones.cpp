#include "valoracion.hpp"
#include "valoraciones.hpp"
#include "utilidades.hpp"
#include <string>
#include <fstream>
#include <cassert>
#include <cctype>

using namespace std;

// ------------------- FUNCIONES AUXILIARES
namespace
{
    // Limpia un comentario (cadena de caracteres):
    //  - elimina signos de puntuación
    //  - convierte todo a minúscula
    //  - elimina espacios repetidos
    //  - elimina todos los espacios iniciales y finales
    // PARÁMETROS:
    //  - comentario (E): comentario original
    //  - procesado (S): comentario procesado (limpio)
    void procesar_comentario(const string &comentario, string &procesado)
    {
        procesado = comentario;

        while (!procesado.empty() && procesado[0] == ' ')
        {
            procesado.erase(0, 1);
        }

        while (!procesado.empty() && procesado.back() == ' ')
        {
            procesado.pop_back();
        }

        unsigned i = 0;
        while (i < procesado.size())
        {
            if (!ispunct(procesado[i]))
            {
                if (procesado[i] == ' ')
                {
                    if (i > 0 && procesado[i - 1] == ' ')
                    {
                        procesado.erase(i, 1);
                    }
                    else
                    {
                        i++;
                    }
                }
                else
                {
                    procesado[i] = tolower(procesado[i]);
                    i++;
                }
            }
            else
            {
                procesado.erase(i, 1);
            }
        }
    }

} // namespace

// -------------------------------------------------------------

namespace bblProgII
{
    // --------------------- MÉTODOS PÚBLICOS

    // Operador de asignación de la clase Valoraciones
    Valoraciones &Valoraciones::operator=(const Valoraciones &otro_objeto)
    {
        if (this != &otro_objeto)
        {
            borrar_valoraciones(val_pos);
            borrar_valoraciones(val_neg);
            borrar_palabras(pal_pos);
            borrar_palabras(pal_neg);
            val_pos = copiar_valoraciones(otro_objeto.val_pos);
            val_neg = copiar_valoraciones(otro_objeto.val_neg);
            num_val_pos = otro_objeto.num_val_pos;
            num_val_neg = otro_objeto.num_val_neg;
            pal_pos = copiar_palabras(otro_objeto.pal_pos);
            pal_neg = copiar_palabras(otro_objeto.pal_neg);
            num_pal_pos = otro_objeto.num_pal_pos;
            num_pal_neg = otro_objeto.num_pal_neg;
        }

        return *this;
    }

    // Operador de comparación de igualdad de Valoraciones
    // (SOLO NECESARIO PARA LAS PRUEBAS UNITARIAS.)
    bool Valoraciones::operator==(const Valoraciones &otro_objeto) const
    {
        bool iguales = (num_val_pos == otro_objeto.num_val_pos &&
                        num_val_neg == otro_objeto.num_val_neg &&
                        num_pal_pos == otro_objeto.num_pal_pos &&
                        num_pal_neg == otro_objeto.num_pal_neg);

        PtrValoracion ptr1 = val_pos, ptr2 = otro_objeto.val_pos;

        while (iguales && ptr1 != nullptr)
        {
            iguales = ptr1->valoracion == ptr2->valoracion;
            ptr1 = ptr1->sig;
            ptr2 = ptr2->sig;
        }

        ptr1 = val_neg;
        ptr2 = otro_objeto.val_neg;

        while (iguales && ptr1 != nullptr)
        {
            iguales = ptr1->valoracion == ptr2->valoracion;
            ptr1 = ptr1->sig;
            ptr2 = ptr2->sig;
        }

        PtrPalabra ptr3 = pal_pos, ptr4 = otro_objeto.pal_pos;
        while (iguales && ptr3 != nullptr)
        {
            iguales = ptr3->palabra == ptr4->palabra;
            ptr3 = ptr3->sig;
            ptr4 = ptr4->sig;
        }

        ptr3 = pal_neg;
        ptr4 = otro_objeto.pal_neg;
        while (iguales && ptr3 != nullptr)
        {
            iguales = ptr3->palabra == ptr4->palabra;
            ptr3 = ptr3->sig;
            ptr4 = ptr4->sig;
        }

        return iguales;
    }

    // Función auxiliar
    // (SOLO NECESARIA PARA LAS PRUEBAS UNITARIAS.)
    void Valoraciones::__consultar_elemento_pos(unsigned pos, bool val_pal, bool pos_neg, Valoracion &valoracion, std::string &palabra) const
    {

        assert((val_pal && pos_neg && pos < num_val_pos) ||
               (val_pal && !pos_neg && pos < num_val_neg) ||
               (!val_pal && pos_neg && pos < num_pal_pos) ||
               (!val_pal && !pos_neg && pos < num_pal_neg));

        if (val_pal) // Consulto valoración
        {
            if (pos_neg) // Consulto valoración positiva
            {
                PtrValoracion ptr = val_pos;
                unsigned i = 0;
                while (i < pos)
                {
                    i++;
                    ptr = ptr->sig;
                }
                valoracion = ptr->valoracion;
            }
            else // Consulto valoración negativa
            {
                PtrValoracion ptr = val_neg;
                unsigned i = 0;
                while (i < pos)
                {
                    i++;
                    ptr = ptr->sig;
                }
                valoracion = ptr->valoracion;
            }
        }
        else // Consulto palabra
        {
            if (pos_neg) // Consulto palabra positiva
            {
                PtrPalabra ptr = pal_pos;
                unsigned i = 0;
                while (i < pos)
                {
                    i++;
                    ptr = ptr->sig;
                }
                palabra = ptr->palabra;
            }
            else // Consulto palabra negativa
            {
                PtrPalabra ptr = pal_neg;
                unsigned i = 0;
                while (i < pos)
                {
                    i++;
                    ptr = ptr->sig;
                }
                palabra = ptr->palabra;
            }
        }
    }

    // -----------------------------------------------------------------

    // IMPLEMENTACIÓN DE LOS MÉTODOS PÚBLICOS Y PRIVADOS
    Valoraciones::Valoraciones() : val_pos{}, val_neg{},
                                   num_val_pos{}, num_val_neg{}, pal_pos{}, pal_neg{}, num_pal_pos{}, num_pal_neg{} {}

    // Constructor de copia
    Valoraciones::Valoraciones(const Valoraciones &otro_objeto) : val_pos{copiar_valoraciones(otro_objeto.val_pos)}, val_neg{copiar_valoraciones(otro_objeto.val_neg)},
                                                                  num_val_pos{otro_objeto.num_val_pos}, num_val_neg{otro_objeto.num_val_neg}, pal_pos{copiar_palabras(otro_objeto.pal_pos)}, pal_neg{copiar_palabras(otro_objeto.pal_neg)}, num_pal_pos{otro_objeto.num_pal_pos}, num_pal_neg{otro_objeto.num_pal_neg} {}

    // Destructor
    Valoraciones::~Valoraciones()
    {
        borrar_palabras(pal_pos);
        borrar_palabras(pal_neg);
        borrar_valoraciones(val_pos);
        borrar_valoraciones(val_neg);
    }

    // Lee desde fichero la lista de palabras positivas
    // y la almacena en el objeto. Si el fichero ha podido abrirse
    // correctamente para lectura, devuelve OK a través de 'res'. Si no,
    // devuelve FIC_ERROR.
    //  - nombre_fic (E): nombre del fichero de palabras positivas
    void Valoraciones::cargar_palabras_positivas(const std::string &nombre_fic, Resultado &res)
    {
        leer_palabras(nombre_fic, pal_pos, num_pal_pos, res);
    }

    // Lee desde fichero la lista de palabras negativas
    // y la almacena en el objeto. Si el fichero ha podido abrirse
    // correctamente para lectura, devuelve OK a través de 'res'. Si no,
    // devuelve FIC_ERROR.
    //  - nombre_fic (E): nombre del fichero de palabras negativas
    void Valoraciones::cargar_palabras_negativas(const std::string &nombre_fic, Resultado &res)
    {
        leer_palabras(nombre_fic, pal_neg, num_pal_neg, res);
    }

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
    void Valoraciones::cargar_valoraciones(const std::string &nombre_fic, Resultado &res)
    {
        ifstream f;
        f.open(nombre_fic);
        if (!f.fail())
        {
            f.ignore(9999, '\n');
            std::string nom, fec, com;
            unsigned idrev, idalo, idval;
            char car;
            f >> idalo;
            while (!f.eof())
            {
                f.ignore();
                f >> idval;
                f.ignore();
                getline(f, fec, ',');
                f >> idrev;
                f.ignore();
                getline(f, nom, ',');
                f >> car;
                if (car == '"')
                {
                    getline(f, com, '"');
                    com = com;
                }
                else
                {
                    getline(f, com, '\n');
                    com = car + com;
                }
                insertar_valoracion(Valoracion(idalo, idval, fec, idrev, nom, com), res);
                f >> idalo;
                res = OK;
            }
            f.close();
        }
        else
        {
            res = FIC_ERROR;
        }
        // cout << val_pos->valoracion.consultar_id_alojamiento() << "," << val_pos->valoracion.consultar_id_valoracion() << "," << val_pos->valoracion.consultar_fecha() << "," << val_pos->valoracion.consultar_id_revisor() << "," << val_pos->valoracion.consultar_nombre_revisor() << "," << val_pos->valoracion.consultar_comentarios() << endl;
    }

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
    void Valoraciones::guardar_valoraciones(const std::string &nombre_fic, Resultado &res) const
    {
        std::ofstream f;
        PtrValoracion aux = val_pos;
        f.open(nombre_fic);
        if (!f.fail())
        {
            f << "id_alojamiento,id_valoracion,fecha,id_revisor,nombre_revisor,comentario" << endl;
            while (aux != nullptr)
            {
                f << aux->valoracion.consultar_id_alojamiento() << "," << aux->valoracion.consultar_id_valoracion() << "," << aux->valoracion.consultar_fecha() << ","
                  << aux->valoracion.consultar_id_revisor() << "," << aux->valoracion.consultar_nombre_revisor() << "," << '"' << aux->valoracion.consultar_comentarios() << '"' << endl;
                aux = aux->sig;
            }
            aux = val_neg;
            while (aux != nullptr)
            {
                f << aux->valoracion.consultar_id_alojamiento() << "," << aux->valoracion.consultar_id_valoracion() << "," << aux->valoracion.consultar_fecha() << ","
                  << aux->valoracion.consultar_id_revisor() << "," << aux->valoracion.consultar_nombre_revisor() << "," << '"' << aux->valoracion.consultar_comentarios() << '"' << endl;
                aux = aux->sig;
            }
            f.close();
            res = OK;
        }
        else
        {
            res = FIC_ERROR;
        }
    }

    // Devuelve el número de valoraciones positivas y negativas almacenadas
    // PARÁMETROS:
    //  - positivas (S): número de valoraciones positivas
    //  - negativas (S): número de valoraciones negativas
    void Valoraciones::numero_valoraciones(unsigned &positivas, unsigned &negativas) const
    {
        positivas = 0;
        negativas = 0;
        PtrValoracion ptr = val_pos;
        while (ptr != nullptr)
        {
            if (ptr->valoracion.consultar_nombre_revisor() != "")
            {
                ++positivas;
            }

            ptr = ptr->sig;
        }
        ptr = val_neg;
        while (ptr != nullptr)
        {
            if (ptr->valoracion.consultar_nombre_revisor() != "")
            {
                ++negativas;
            }
            ptr = ptr->sig;
        }
    }

    // Devuelve la lista de los identificadores de todas las valoraciones
    // almacenadas, positivas y negativas.
    // PARÁMETROS:
    //  - ids_positivas (S): ids de todas las valoraciones positivas
    //  - ids_negativas (S): ids de todas las valoraciones negativas
    void Valoraciones::lista_valoraciones(Ids &ids_positivas, Ids &ids_negativas) const
    {
        PtrValoracion aux = val_pos;
        ids_positivas.num_ids = 0;
        ids_negativas.num_ids = 0;
        while (aux != nullptr)
        {
            ids_positivas.ids[ids_positivas.num_ids] = aux->valoracion.consultar_id_valoracion();
            aux = aux->sig;
            ids_positivas.num_ids++;
        }
        aux = val_neg;
        while (aux != nullptr)
        {
            ids_negativas.ids[ids_negativas.num_ids] = aux->valoracion.consultar_id_valoracion();
            aux = aux->sig;
            ids_negativas.num_ids++;
        }
    }

    // Devuelve el número de palabras positivas y negativas almacenadas
    // PARÁMETROS:
    //  - positivas (S): número de palabras positivas
    //  - negativas (S): número de palabras negativas
    void Valoraciones::numero_palabras(unsigned &positivas, unsigned &negativas) const
    {
        positivas = 0;
        negativas = 0;
        PtrPalabra ptr = pal_pos;
        while (ptr != nullptr)
        {
            if (ptr->palabra != "")
            {
                ++positivas;
            }
            ptr = ptr->sig;
        }
        ptr = pal_neg;
        while (ptr != nullptr)
        {
            if (ptr->palabra != "")
            {
                ++negativas;
            }
            ptr = ptr->sig;
        }
    }

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
    void Valoraciones::buscar_valoracion(unsigned id_valoracion, Valoracion &valoracion, bool &encontrada, bool &positiva) const
    {
        PtrValoracion pos, ant;

        buscar_valoracion(id_valoracion, val_neg, pos, ant, encontrada);

        if (encontrada)
        {
            positiva = false;
            valoracion = pos->valoracion;
        }
        else
        {
            buscar_valoracion(id_valoracion, val_pos, pos, ant, encontrada);
            if (encontrada)
            {
                positiva = true;
                valoracion = pos->valoracion;
            }
        }
    }

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
    void Valoraciones::insertar_valoracion(const Valoracion &valoracion, Resultado &res)
    {

        if (analisis_de_sentimientos(valoracion.consultar_comentarios()))
        {
            insertar_valoracion(valoracion, val_pos, res);
            num_val_pos++;
        }
        else
        {
            insertar_valoracion(valoracion, val_neg, res);
            num_val_neg++;
        }
    }

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
    void Valoraciones::eliminar_valoracion(unsigned id_valoracion, bool &positiva, Resultado &res)
    {
        bool encontrada;
        Valoracion v;
        buscar_valoracion(id_valoracion, v, encontrada, positiva);
        if (encontrada)
        {
            if (positiva)
            {
                eliminar_valoracion(v.consultar_id_valoracion(), val_pos, res);
                num_val_pos--;
            }
            else
            {
                eliminar_valoracion(v.consultar_id_valoracion(), val_neg, res);
                num_val_neg--;
            }
        }
        else
        {
            res = NO_EXISTE;
        }
    }

    // Modificar una valoración existente con los nuevos datos de la misma que se pasan
    // a través del parámetro 'valoracion'. Si el nuevo comentario de la valoración
    // es diferente al actual y su clasificación cambia (pasa de positiva a negativa,
    // o viceversa) debe moverse a la lista de valoraciones correspondiente a la clasificación
    // del nuevo comentario. Si la valoración existe (existe ese id de valoración) se modifica
    // y se devuelve OK a través de 'res'. Si no, se devuelve NO_EXISTE.
    void Valoraciones::modificar_valoracion(const Valoracion &valoracion, Resultado &res)
    {
        Valoracion v;
        bool encontrado, det;
        buscar_valoracion(valoracion.consultar_id_valoracion(), v, encontrado, det);
        if (encontrado)
        {

            v.asignar_comentarios(valoracion.consultar_comentarios());
            v.asignar_fecha(valoracion.consultar_fecha());
            v.asignar_id_alojamiento(valoracion.consultar_id_alojamiento());
            v.asignar_id_revisor(valoracion.consultar_id_revisor());
            v.asignar_nombre_revisor(valoracion.consultar_nombre_revisor());
            v.asignar_id_valoracion(valoracion.consultar_id_valoracion());
            eliminar_valoracion(valoracion.consultar_id_valoracion(), det, res);
            insertar_valoracion(v, res);
            res = OK;
        }
        else
        {
            res = NO_EXISTE;
        }
    }

    // Devuelve la lista de identificadores de valoraciones positivas y
    // negativas para un determinado alojamiento.
    // PARÁMETROS:
    //  - id_alojamiento (E): identificador de un alojamiento
    //  - ids_valoraciones_positivas (S): lista de ids de valoraciones positivas del alojamiento
    //  - ids_valoraciones_negativas (S): lista de ids de valoraciones negativas del alojamiento
    void Valoraciones::valoraciones_alojamiento(unsigned id_alojamiento, Ids &ids_valoraciones_positivas, Ids &ids_valoraciones_negativas) const
    {
        PtrValoracion aux = val_pos;
        ids_valoraciones_positivas.num_ids = 0;
        ids_valoraciones_negativas.num_ids = 0;
        while (aux != nullptr)
        {
            if (aux->valoracion.consultar_id_alojamiento() == id_alojamiento)
            {
                ids_valoraciones_positivas.ids[ids_valoraciones_positivas.num_ids] = aux->valoracion.consultar_id_valoracion();
                ids_valoraciones_positivas.num_ids++;
            }

            aux = aux->sig;
        }
        aux = val_neg;
        while (aux != nullptr)
        {
            if (aux->valoracion.consultar_id_alojamiento() == id_alojamiento)
            {
                ids_valoraciones_negativas.ids[ids_valoraciones_negativas.num_ids] = aux->valoracion.consultar_id_valoracion();
                ids_valoraciones_negativas.num_ids++;
            }

            aux = aux->sig;
        }
    }

    // Devuelve la lista de identificadores de valoraciones positivas y
    // negativas para un determinado revisor.
    // PARÁMETROS:
    //  - id_revisor (E): identificador de un revisor
    //  - ids_valoraciones_positivas (S): lista de ids de valoraciones positivas del revisor
    //  - ids_valoraciones_negativas (S): lista de ids de valoraciones negativas del revisor
    void Valoraciones::valoraciones_revisor(unsigned id_revisor, Ids &ids_valoraciones_positivas, Ids &ids_valoraciones_negativas) const
    {
        PtrValoracion aux = val_pos;
        ids_valoraciones_positivas.num_ids = 0;
        ids_valoraciones_negativas.num_ids = 0;
        while (aux != nullptr)
        {
            if (aux->valoracion.consultar_id_revisor() == id_revisor)
            {
                ids_valoraciones_positivas.ids[ids_valoraciones_positivas.num_ids] = aux->valoracion.consultar_id_valoracion();
                ids_valoraciones_positivas.num_ids++;
            }

            aux = aux->sig;
        }
        aux = val_neg;
        while (aux != nullptr)
        {
            if (aux->valoracion.consultar_id_revisor() == id_revisor)
            {
                ids_valoraciones_negativas.ids[ids_valoraciones_negativas.num_ids] = aux->valoracion.consultar_id_valoracion();
                ids_valoraciones_negativas.num_ids++;
            }

            aux = aux->sig;
        }
    }

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
    void Valoraciones::escribir() const
    {
        PtrValoracion ptr = val_pos;
        while (ptr != nullptr)
        {
            std::cout << "-- -ID alojamiento : " << ptr->valoracion.consultar_id_alojamiento() << endl;
            std::cout << "ID valoración:       " << ptr->valoracion.consultar_id_valoracion() << endl;
            std::cout << "Fecha:               " << ptr->valoracion.consultar_fecha() << endl;
            std::cout << "ID revisor:          " << ptr->valoracion.consultar_id_revisor() << endl;
            std::cout << "Nombre revisor:      " << ptr->valoracion.consultar_nombre_revisor() << endl;
            std::cout << "--- COMENTARIO:      " << ptr->valoracion.consultar_comentarios() << endl;
            std::cout << "*** VALORACIÓN:      "
                      << "POSITIVA" << endl;
            ptr = ptr->sig;
        }
        ptr = val_neg;
        while (ptr != nullptr)
        {
            std::cout << "-- -ID alojamiento : " << ptr->valoracion.consultar_id_alojamiento() << endl;
            std::cout << "ID valoración:       " << ptr->valoracion.consultar_id_valoracion() << endl;
            std::cout << "Fecha:               " << ptr->valoracion.consultar_fecha() << endl;
            std::cout << "ID revisor:          " << ptr->valoracion.consultar_id_revisor() << endl;
            std::cout << "Nombre revisor:      " << ptr->valoracion.consultar_nombre_revisor() << endl;
            std::cout << "--- COMENTARIO:      " << ptr->valoracion.consultar_comentarios() << endl;
            std::cout << "*** VALORACIÓN:      " << endl
                      << "NEGATIVA" << endl;
            ptr = ptr->sig;
        }
    }

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
    void Valoraciones::leer_palabras(const std::string &fic, PtrPalabra &palabras, unsigned &num, Resultado &res) const
    {

        std::ifstream f;
        num = 0;
        PtrPalabra nuevo;
        f.open(fic);
        if (!f.fail())
        {

            std::string pal;
            getline(f, pal, '\n');
            while (pal[0] == ';')
            {
                getline(f, pal, '\n');
            }
            nuevo = new NodoPalabra;
            nuevo->palabra = pal;
            nuevo->sig = palabras;
            palabras = nuevo;
            while (!f.eof())
            {

                getline(f, pal, '\n');

                nuevo = palabras;
                while (nuevo->sig != nullptr)
                {
                    nuevo = nuevo->sig;
                }
                nuevo->sig = new NodoPalabra;
                nuevo->sig->palabra = pal;
                nuevo->sig->sig = nullptr;
                num++;
            }
            res = OK;
        }
        else
        {
            res = FIC_ERROR;
        }
    }

    // Indica si una palabra está en la lista de palabras.
    // PARÁMETROS:
    //  - palabra (E): palabra que se busca
    //  - palabras (E): lista de palabras en la que se busca la palabra
    bool Valoraciones::esta_en_lista(const std::string &palabra, PtrPalabra palabras) const
    {
        while (palabras != nullptr && palabras->palabra != palabra)
        {
            palabras = palabras->sig;
        }

        return (palabras != nullptr && palabras->palabra == palabra);
    }

    // Devuelve el número de palabras positivas y negativas de un comentario
    // PARÁMETROS:
    //  - comentario (E): cadena de caracteres correspondiente a un comentario, consistente
    //                    en una secuencia de palabras en minúscula (es decir, el comentario
    //                    debe estar preprocesado).
    //  - positivas (S): número de palabras del comentario clasificadas como positivas
    //                   (es decir, que están en la lista de palabras positivas del objeto)
    //  - negativas (S): número de palabras del comentario clasificadas como negativas
    //                   (es decir, que están en la lista de palabras negativas del objeto)
    void Valoraciones::frecuencia_palabras_pos_neg(const std::string &comentario, unsigned &positivas, unsigned &negativas) const
    {
        std::string com = "";
        positivas = 0;
        negativas = 0;
        unsigned h = 0;

        while (h < comentario.size())
        {

            if (comentario[h] != ' ')
            {
                com += comentario[h];
            }
            else
            {
                com.clear();
            }
            if (comentario[h] != ' ' && esta_en_lista(com, pal_pos))
            {
                positivas++;
                com.clear();
            }
            else if (comentario[h] != ' ' && esta_en_lista(com, pal_neg))
            {
                negativas++;
                com.clear();
            }
            h++;
        }
    }

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
    bool Valoraciones::analisis_de_sentimientos(const std::string &comentario) const
    {
        std::string procesado;
        unsigned pos, neg;
        bool c = false;
        procesar_comentario(comentario, procesado);
        frecuencia_palabras_pos_neg(procesado, pos, neg);
        if (pos >= neg)
        {
            c = true;
        }
        return c;
    }

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
    void Valoraciones::buscar_valoracion(unsigned id_valoracion,
                                         PtrValoracion lista,
                                         PtrValoracion &ptr,
                                         PtrValoracion &ant,
                                         bool &encontrada) const
    {
        ptr = lista;
        ant = nullptr;
        while (ptr != nullptr && ptr->valoracion.consultar_id_valoracion() < id_valoracion)
        {
            ant = ptr;
            ptr = ptr->sig;
        }

        encontrada = ((ptr != nullptr) && (ptr->valoracion.consultar_id_valoracion() == id_valoracion));
    }

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
    void Valoraciones::insertar_valoracion(const Valoracion &valoracion, PtrValoracion &lista, Resultado &res) const
    {
        PtrValoracion pos, ant, nuevo;
        bool esta;
        buscar_valoracion(valoracion.consultar_id_valoracion(), lista, pos, ant, esta);
        if (!esta)
        {
            nuevo = new NodoValoracion;
            nuevo->valoracion = valoracion;
            if (ant == nullptr)
            {
                lista = nuevo;
            }
            else
            {
                ant->sig = nuevo;
            }
            nuevo->sig = pos;

            res = OK;
        }
        else
        {
            res = YA_EXISTE;
        }
    }

    // Elimina una valoración cuyo identificador se pasa como parámetro
    // de la lista de valoraciones que se pasa también como parámetro.
    // Si se encuentra la valoración en la lista, se elimina y se
    // devuelve OK a través de 'res'. Si no, se devuelve NO_EXISTE
    // a través de 'res'.
    // PARÁMETROS:
    //  - id_valoracion (E): id de la valoración a eliminar
    //  - lista (ES): lista de valoraciones
    //  - res (S): resultado de la operación
    void Valoraciones::eliminar_valoracion(unsigned id_valoracion, PtrValoracion &lista, Resultado &res) const
    {
        PtrValoracion pos, ant;
        bool esta;
        buscar_valoracion(id_valoracion, lista, pos, ant, esta);
        if (esta)
        {
            if (ant == nullptr)
            {
                lista = lista->sig;
            }
            else
            {
                ant->sig = pos->sig;
            }

            delete pos;
            res = OK;
        }
        else
        {
            res = NO_EXISTE;
        }
    }
    // Borra completamente una lista de valoraciones
    // PARÁMETROS:
    //  - lista (ES): lista de valoraciones a borrar
    void Valoraciones::borrar_valoraciones(PtrValoracion &lista) const
    {
        while (lista != nullptr)
        {
            PtrValoracion ptr = lista;
            lista = lista->sig;
            delete ptr;
        }
    }

    // Borra completamente una lista de palabras
    // PARÁMETROS:
    //  - lista (ES): lista de palabras a borrar
    void Valoraciones::borrar_palabras(PtrPalabra &lista) const
    {
        while (lista != nullptr)
        {
            PtrPalabra ptr = lista;
            lista = lista->sig;
            delete ptr;
        }
    }

    // Devuelve una copia de la lista de valoraciones que se pasa
    // como parámetro.
    // PARÁMETROS:
    //  - lista (E): lista de valoraciones original
    Valoraciones::PtrValoracion Valoraciones::copiar_valoraciones(PtrValoracion lista) const
    {
        PtrValoracion copia = nullptr;

        PtrValoracion fin;
        while (lista != nullptr)
        {
            if (copia == nullptr)
            {
                copia = fin = new NodoValoracion;
            }
            else
            {
                fin->sig = new NodoValoracion;
                fin = fin->sig;
            }
            fin->valoracion = lista->valoracion;
            fin->sig = nullptr;
            lista = lista->sig;
        }

        return copia;
    }

    // Devuelve una copia de la lista de palabras que se pasa
    // como parámetro.
    // PARÁMETROS:
    //  - lista (E): lista de palabras original
    Valoraciones::PtrPalabra Valoraciones::copiar_palabras(PtrPalabra lista) const
    {
        PtrPalabra copia = nullptr;

        PtrPalabra fin;
        while (lista != nullptr)
        {
            if (copia == nullptr)
            {
                copia = fin = new NodoPalabra;
            }
            else
            {
                fin->sig = new NodoPalabra;
                fin = fin->sig;
            }
            fin->palabra = lista->palabra;
            fin->sig = nullptr;
            lista = lista->sig;
        }

        return copia;
    }

} // namespace bblProgII