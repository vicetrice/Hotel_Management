#ifndef __VALORACION_HPP__
#define __VALORACION_HPP__

// INCLUIR LAS BIBLIOTECAS NECESARIAS
#include <string>

// DEFINIR LA CLASE Valoracion DENTRO DEL NAMESPACE bblProgII
namespace bblProgII
{
        class Valoracion
        {

                // ------- MÉTODOS PÚBLICOS DE LA CLASE Valoracion
        public:
                // Constructor por defecto.
                // Inicializa todos los atributos que son cadenas de caracteres con
                // la cadena vacía y los atributos que son números con cero
                Valoracion();

                // Constructor de copia
                Valoracion(const Valoracion &otra_valoracion);

                // Constructor específico.
                // Inicializa los atributos según los parámetros correspondientes.
                // Parámetros:
                //  - id_alo (E): identificador del alojamiento
                //  - id_val (E): identificador de la valoración
                //  - fec (E): fecha de la valoración (formato AAAA-MM-DD)
                //  - id_rev (E): identificador del revisor
                //  - nom_rev (E): nombre del revisor
                //  - comments (E): la valoración (comentarios)
                // PRECONDICIONES:
                //  - La fecha tiene formato correcto (AAAA-MM-DD)
                //  - 'nom_rev' no es una cadena vacía
                //  - 'comments' no es una cadena vacía
                Valoracion(unsigned id_alo,
                           unsigned id_val,
                           const std::string &fec,
                           unsigned id_rev,
                           const std::string &nom_rev,
                           const std::string &comments);

                // Destructor
                ~Valoracion();

                // ----------------- MÉTODOS DE ASIGNACIÓN

                // Asigna el identificador del alojamiento
                // Parámetros:
                //  - id_alo (E): identificador del alojamiento
                void asignar_id_alojamiento(unsigned id_alo);

                // Asigna el identificador de la valoración
                // Parámetros:
                //  - id_val (E): identificador de la valoración
                void asignar_id_valoracion(unsigned id_val);

                // Asigna fecha
                // Parámetros:
                //  - fec (E): fecha de la valoración
                // PRECONDICIÓN:
                //  - la fecha tiene formato correcto (AAAA-MM-DD)
                void asignar_fecha(const std::string &fec);

                // Asigna el identificador del revisor
                // Parámetros:
                //  - id_rev (E): identificador del revisor
                void asignar_id_revisor(unsigned id_rev);

                // Asigna el nombre del revisor
                // Parámetros:
                //  - nom_rev (E): nombre del revisor
                // PRECONDICIÓN:
                //  - la cadena no está vacía
                void asignar_nombre_revisor(const std::string &nom_rev);

                // Asigna la valoración (comentario) al alojamiento
                // Parámetros:
                //  - comment (E): valoración (comentario)
                void asignar_comentarios(const std::string &comments);

                // ----------------- MÉTODOS DE CONSULTA

                // Consulta el id del alojamiento
                unsigned consultar_id_alojamiento() const;

                // Consulta el id de la valoración
                unsigned consultar_id_valoracion() const;

                // Consulta el id del revisor
                unsigned consultar_id_revisor() const;

                // Consulta el nombre del revisor
                std::string consultar_nombre_revisor() const;

                // Consulta la fecha de la valoración
                std::string consultar_fecha() const;

                // Consulta la valoración (comentarios) del alojamiento
                std::string consultar_comentarios() const;

                // Escribe por pantalla los datos de la valoración,
                // en el siguiente formato (nótese que se
                // usan tabuladores para formatear la salida):
                //  ID alojamiento:      <id_alojamiento>
                //  ID valoración:       <id_valoracion>
                //  Fecha:               <fecha>
                //  ID revisor:          <id_revisor>
                //  Nombre revisor:      <nombre_revisor>
                //  --- COMENTARIO:
                //  <comentario>
                void escribir() const;

                // --------- OPERADORES SOBRECARGADOS

                // Operador de asignación de Valoracion.
                
                Valoracion &operator=(const Valoracion &otra_valoracion) = default;

                // Operador de comparación de igualdad (necesario para las pruebas unitarios).
                
                bool operator==(const Valoracion &otra_valoracion) const;

                // -------- PARTE PRIVADA DE LA CLASE Valoracion
        private:
                // ATRIBUTOS
                unsigned id_alojamiento;    // Identificador del alojamiento
                unsigned id_valoracion;     // Identificador (único) de la valoración
                std::string fecha;          // Fecha de la valoración
                unsigned id_revisor;        // Identificador del revisor de la valoración
                std::string nombre_revisor; // Nombre del revisor de la valoración
                std::string comentario;     // Valoración (comentario o revisión)
        };
}

#endif