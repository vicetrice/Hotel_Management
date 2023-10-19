#include "valoracion.hpp"
#include <string>
#include <cctype>
#include <iostream>

using namespace std;

// ------- FUNCIONES AUXILIARES PARA LA IMPLEMENTACIÓN DE LOS MÉTODOS

namespace
{
    bool fecha_correcta(const string &fec)
    {
        bool correcta = fec.size() == 10;

        correcta = isdigit(fec[0]) &&
                   isdigit(fec[1]) &&
                   isdigit(fec[2]) &&
                   isdigit(fec[3]) &&
                   isdigit(fec[5]) &&
                   isdigit(fec[6]) &&
                   isdigit(fec[8]) &&
                   isdigit(fec[9]) &&
                   fec[4] == '-' &&
                   fec[7] == '-';

        return correcta;
    }
} // namespace

// ----------------------------------------------

namespace bblProgII
{
    // ---------- OPERADORES SOBRECARGADOS

    // Operador de comparación de igualdad (necesario para las pruebas unitarios)
    bool Valoracion::operator==(const Valoracion &otra_valoracion) const
    {
        return (id_alojamiento == otra_valoracion.id_alojamiento &&
                id_valoracion == otra_valoracion.id_valoracion &&
                fecha == otra_valoracion.fecha &&
                id_revisor == otra_valoracion.id_revisor &&
                nombre_revisor == otra_valoracion.nombre_revisor &&
                comentario == otra_valoracion.comentario);
    }

    // -------------------------------------------------------------------

    // IMPLEMENTACIÓN DE LOS MÉTODOS PÚBLICOS Y PRIVADOS

    // Constructor por defecto.
    // Inicializa todos los atributos que son cadenas de caracteres con
    // la cadena vacía y los atributos que son números con cero
    Valoracion::Valoracion() : id_alojamiento{}, id_valoracion{}, fecha{}, id_revisor{}, nombre_revisor{}, comentario{} {}

    // Constructor de copia
    Valoracion::Valoracion(const Valoracion &otra_valoracion) : id_alojamiento{otra_valoracion.id_alojamiento}, id_valoracion{otra_valoracion.id_valoracion}, fecha{otra_valoracion.fecha}, id_revisor{otra_valoracion.id_revisor}, nombre_revisor{otra_valoracion.nombre_revisor}, comentario{otra_valoracion.comentario} {}

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
    Valoracion::Valoracion(unsigned id_alo,
                           unsigned id_val,
                           const std::string &fec,
                           unsigned id_rev,
                           const std::string &nom_rev,
                           const std::string &comments) : id_alojamiento{id_alo}, id_valoracion{id_val}, fecha{fec}, id_revisor{id_rev}, nombre_revisor{nom_rev}, comentario{comments} {}

    // Destructor
    Valoracion::~Valoracion() {}

    // ----------------- MÉTODOS DE ASIGNACIÓN

    // Asigna el identificador del alojamiento
    // Parámetros:
    //  - id_alo (E): identificador del alojamiento
    void Valoracion::asignar_id_alojamiento(unsigned id_alo) { id_alojamiento = id_alo; }

    // Asigna el identificador de la valoración
    // Parámetros:
    //  - id_val (E): identificador de la valoración
    void Valoracion::asignar_id_valoracion(unsigned id_val) { id_valoracion = id_val; }

    // Asigna fecha
    // Parámetros:
    //  - fec (E): fecha de la valoración
    // PRECONDICIÓN:
    //  - la fecha tiene formato correcto (AAAA-MM-DD)
    void Valoracion::asignar_fecha(const std::string &fec)
    {
        if (fecha_correcta(fec))
        {
            fecha = fec;
        }
    }

    // Asigna el identificador del revisor
    // Parámetros:
    //  - id_rev (E): identificador del revisor
    void Valoracion::asignar_id_revisor(unsigned id_rev) { id_revisor = id_rev; }

    // Asigna el nombre del revisor
    // Parámetros:
    //  - nom_rev (E): nombre del revisor
    // PRECONDICIÓN:
    //  - la cadena no está vacía
    void Valoracion::asignar_nombre_revisor(const std::string &nom_rev) { nombre_revisor = nom_rev; }

    // Asigna la valoración (comentario) al alojamiento
    // Parámetros:
    //  - comment (E): valoración (comentario)
    void Valoracion::asignar_comentarios(const std::string &comments) { comentario = comments; }

    // ----------------- MÉTODOS DE CONSULTA

    // Consulta el id del alojamiento
    unsigned Valoracion::consultar_id_alojamiento() const { return id_alojamiento; }

    // Consulta el id de la valoración
    unsigned Valoracion::consultar_id_valoracion() const { return id_valoracion; }

    // Consulta el id del revisor
    unsigned Valoracion::consultar_id_revisor() const { return id_revisor; }

    // Consulta el nombre del revisor
    std::string Valoracion::consultar_nombre_revisor() const { return nombre_revisor; }

    // Consulta la fecha de la valoración
    std::string Valoracion::consultar_fecha() const { return fecha; }

    // Consulta la valoración (comentarios) del alojamiento
    std::string Valoracion::consultar_comentarios() const { return comentario; }

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
    void Valoracion::escribir() const
    {
        cout << "ID alojamiento:      " << id_alojamiento << endl;
        cout << "ID valoración:       " << id_valoracion << endl;
        cout << "Fecha:               " << fecha << endl;
        cout << "ID revisor:          " << id_revisor << endl;
        cout << "Nombre revisor:      " << nombre_revisor << endl;
        cout << "--- COMENTARIO:" << endl;
        cout << comentario;
    }

} // namespace bblProgII
