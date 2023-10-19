#include "alojamiento.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

namespace bblProgII
{
    // ---------------- OPERADORES SOBRECARGADOS

    // Operador de comparación de igualdad
    bool Alojamiento::operator==(const Alojamiento &otro_alojamiento) const
    {
        bool iguales = false;
        if (id_alojamiento == otro_alojamiento.id_alojamiento &&
            nombre == otro_alojamiento.nombre &&
            id_anfitrion == otro_alojamiento.id_anfitrion &&
            nombre_anfitrion == otro_alojamiento.nombre_anfitrion &&
            barrio == otro_alojamiento.barrio &&
            latitud == otro_alojamiento.latitud &&
            longitud == otro_alojamiento.longitud &&
            tipo_alojamiento == otro_alojamiento.tipo_alojamiento &&
            precio == otro_alojamiento.precio &&
            minimo_noches == otro_alojamiento.minimo_noches &&
            disponibilidad_365 == otro_alojamiento.disponibilidad_365)
        {
            iguales = true;
        }

        return iguales;
    }

    // ---------------------------------------------------------------------

    // -------------- IMPLEMENTACIÓN DE LOS MÉTODOS PRIVADOS Y PÚBLICOS
    // Constructor por defecto.
    // Inicializa todos los atributos que son cadenas de caracteres con
    // la cadena vacía y los atributos que son números con cero
    Alojamiento::Alojamiento() : id_alojamiento{},
                                 nombre{},
                                 id_anfitrion{},
                                 nombre_anfitrion{},
                                 barrio{},
                                 latitud{},
                                 longitud{},
                                 tipo_alojamiento{},
                                 precio{},
                                 minimo_noches{},
                                 disponibilidad_365{} {}

    // Constructor de copia
    Alojamiento::Alojamiento(const Alojamiento &otro_alojamiento) : id_alojamiento{otro_alojamiento.id_alojamiento},
                                                                    nombre{otro_alojamiento.nombre},
                                                                    id_anfitrion{otro_alojamiento.id_anfitrion},
                                                                    nombre_anfitrion{otro_alojamiento.nombre_anfitrion},
                                                                    barrio{otro_alojamiento.barrio},
                                                                    latitud{otro_alojamiento.latitud},
                                                                    longitud{otro_alojamiento.longitud},
                                                                    tipo_alojamiento{otro_alojamiento.tipo_alojamiento},
                                                                    precio{otro_alojamiento.precio},
                                                                    minimo_noches{otro_alojamiento.minimo_noches},
                                                                    disponibilidad_365{otro_alojamiento.disponibilidad_365} {}

    // Constructor específico.
    // Inicializa los atributos según los parámetros correspondientes.
    // Parámetros:
    //  - id_alo (E): identificador del alojamiento
    //  - nom (E): nombre del alojamiento
    //  - id_anf (E): identificador del anfitrión
    //  - nom_anf (E): nombre del anfitrión
    //  - barr (E): barrio del alojamiento
    //  - lat (E): latitud de la ubicación del alojamiento
    //  - lon (E): longitud de la ubicación del alojamiento
    //  - tipo_alo (E): tipo del alojamiento
    //  - prec (E): precio del alojamiento
    //  - min_noch (E): mínimo de noches
    //  - dis_365 (E): número de días al año disponible
    // PRECONDICIÓN:
    //  - prec >= 0
    //  - dis_365 <= 365
    //  - las cadenas de caracteres no son vacías
    Alojamiento::Alojamiento(unsigned id_alo,
                             const std::string &nom,
                             unsigned id_anf,
                             const std::string &nom_afn,
                             const std::string &barr,
                             double lat,
                             double lon,
                             const std::string &tipo_alo,
                             double prec,
                             unsigned min_noch,
                             unsigned dis_365) : id_alojamiento{id_alo},
                                                 nombre{nom},
                                                 id_anfitrion{id_anf},
                                                 nombre_anfitrion{nom_afn},
                                                 barrio{barr},
                                                 latitud{lat},
                                                 longitud{lon},
                                                 tipo_alojamiento{tipo_alo},
                                                 precio{prec},
                                                 minimo_noches{min_noch},
                                                 disponibilidad_365{dis_365} {}

    // Destructor
    Alojamiento::~Alojamiento() {}

    // ----------------- MÉTODOS DE ASIGNACIÓN

    // Asigna el identificador del alojamiento
    // Parámetros:
    //  - id_alo (E): identificador del alojamiento
    void Alojamiento::asignar_id_alojamiento(unsigned id_alo) { id_alojamiento = id_alo; }

    // Asigna el nombre del alojamiento
    // Parámetros:
    //  - nom (E): nombre del alojamiento
    // PRECONDICIÓN:
    //  - 'nom' no es cadena vacía
    void Alojamiento::asignar_nombre(const std::string &nom) { nombre = nom; }

    // Asigna el identificador del anfitrion
    // Parámetros:
    //  - id_anf (E): identificador del anfitrión
    void Alojamiento::asignar_id_anfitrion(unsigned id_anf) { id_anfitrion = id_anf; }

    // Asigna el nombre del anfitrión
    // Parámetros:
    //  - nom_anf (E): nombre del anfitrión
    // PRECONDICIÓN:
    //  - 'nom_anf' no es cadena vacía
    void Alojamiento::asignar_nombre_anfitrion(const std::string &nom_anf) { nombre_anfitrion = nom_anf; }

    // Asigna el barrio (zona) donde se ubica el alojamiento
    // Parámetros:
    //  - barr (E): nombre del barrio
    // PRECONDICIÓN:
    //  - 'barr' no es cadena vacía
    void Alojamiento::asignar_barrio(const std::string &barr) { barrio = barr; }

    // Asigna la latitud de la ubicación del alojamiento
    // Parámetros:
    //  - lat (E): latitud de la ubicación
    void Alojamiento::asignar_latitud(double lat) { latitud = lat; }

    // Asigna la longitud de la ubicación del alojamiento
    // Parámetros:
    //  - lon (E): longitud de la ubicación
    void Alojamiento::asignar_longitud(double lon) { longitud = lon; }

    // Asigna el tipo de alojamiento
    // Parámetros:
    //  - tipo_alo (E): tipo de alojamiento
    // PRECONDICIÓN:
    //  - 'tipo_alo' no es cadena vacía
    void Alojamiento::asignar_tipo_alojamiento(const std::string &tipo_alo) { tipo_alojamiento = tipo_alo; }

    // Asigna el precio del alojamiento
    // Parámetros:
    //  - prec (E): precio del alojamiento
    // PRECONDICIÓN: precio >= 0
    void Alojamiento::asignar_precio(double prec) { precio = prec; }

    // Asigna el mínimo número de noches que puede alquilarse el alojamiento
    // Parámetros:
    //  - min_noch (E): mínimo número de noches
    void Alojamiento::asignar_minimo_noches(unsigned min_noch) { minimo_noches = min_noch; }

    // Asignar el número de días al año de disponibilidad del alojamiento
    // Parámetros:
    //  - dis_365 (E): número de días al año disponible
    // PRECONDICIÓN: dis_365 <= 365
    void Alojamiento::asignar_disponibilidad_365(unsigned dis_365) { disponibilidad_365 = dis_365; }

    // ----------------- MÉTODOS DE CONSULTA

    // Consulta el id del alojamiento
    unsigned Alojamiento::consultar_id_alojamiento() const { return id_alojamiento; }

    // Consulta el nombre del alojamiento
    std::string Alojamiento::consultar_nombre() const { return nombre; }

    // Consulta el id del anfitrión del alojamiento
    unsigned Alojamiento::consultar_id_anfitrion() const { return id_anfitrion; }

    // Consulta el nombre del anfitrión del alojamiento
    std::string Alojamiento::consulta_nombre_anfitrion() const { return nombre_anfitrion; }

    // Consulta el barrio (zona) donde se ubica el alojamiento
    std::string Alojamiento::consultar_barrio() const { return barrio; }

    // Consulta la latitud de la localización del alojamiento
    double Alojamiento::consultar_latitud() const { return latitud; }

    // Consulta la longitud de la localización del alojamiento
    double Alojamiento::consultar_longitud() const { return longitud; }

    // Consulta el tipo de alojamiento
    std::string Alojamiento::consultar_tipo_alojamiento() const { return tipo_alojamiento; }

    // Consulta el precio del alojamiento
    double Alojamiento::consultar_precio() const { return precio; }

    // Consulta el mínimo número de noches que puede alquilarse
    unsigned Alojamiento::consultar_minimo_noches() const { return minimo_noches; }

    // Consulta el número de días al año que está disponible
    unsigned Alojamiento::consultar_disponibilidad_365() const { return disponibilidad_365; }

    // ----------------- MÉTODOS DE ENTRADA/SALIDA

    // Escribe por pantalla los datos del alojamiento,
    // en el siguiente formato (nótese que se
    // usan tabuladores para formatear la salida):
    //  ID alojamiento:      <id_alojamiento>
    //  Nombre alojamiento:  <nombre>
    //  ID anfitrión:        <id_anfitrion>
    //  Nombre anfitrión:    <nombre_anfitrion>
    //  Barrio (área):       <barrio>
    //  Localización:        <latitud>, <longitud>
    //  Tipo de alojamiento: <tipo_alojamiento>
    //  Precio por noche:    <precio>
    //  Mínimo de noches:    <minimo_noches>
    //  Disponibilidad/año:  <disponibilidad_365>
    void Alojamiento::escribir() const
    {
        cout << "--- ID alojamiento:  " << id_alojamiento << endl;              // Identificador (único) del alojamiento
        cout << "Nombre alojamiento:  " << nombre << endl;                      // Nombre del alojamiento
        cout << "ID anfitrión:        " << id_anfitrion << endl;                // Identificador (único) del anfitrión/a
        cout << "Nombre anfitrión:    " << nombre_anfitrion << endl;            // Nombre del anfitrión/a
        cout << "Barrio (área):       " << barrio << endl;                      // Barrio (zona) donde se ubica el apartamento
        cout << "Localización:        " << latitud << ", " << longitud << endl; // Latitud y longitud de la ubicación del apartamento
        cout << "Tipo de alojamiento: " << tipo_alojamiento << endl;            // Tipo de alojamiento
        cout << "Precio por noche:    " << precio << endl;                      // Precio del alojamiento por cada día de estancia
        cout << "Mínimo de noches:    " << minimo_noches << endl;               // Mínimo número de noches que se puede alquilar
        cout << "Disponibilidad/año:  " << disponibilidad_365;
    }

    // Lee de fichero los datos correspondientes a un alojamiento.
    // (VÉASE EL FORMATO DEL FICHERO EN escribir).
    // PARÁMETROS:
    //  - fic (ES): flujo de entrada desde fichero
    // PRECONDICIÓN: el fichero está correctamente abierto para lectura
    void Alojamiento::leer(std::ifstream &fic)
    {
        char car;

        fic >> id_alojamiento;
        fic.ignore();
        fic >> car;
        if (car == '"')
        {
            getline(fic, nombre, '"');
            nombre = car + nombre + '"';
            fic.ignore();
        }
        else
        {
            getline(fic, nombre, ',');
            nombre = car + nombre;
        }
        fic >> id_anfitrion;
        fic.ignore();
        getline(fic, nombre_anfitrion, ',');
        getline(fic, barrio, ',');
        fic >> latitud;
        fic.ignore();
        fic >> longitud;
        fic.ignore();
        getline(fic, tipo_alojamiento, ',');
        fic >> precio;
        fic.ignore();
        fic >> minimo_noches;
        fic.ignore();
        fic >> disponibilidad_365;
    }

    // Escribe en fichero los datos correspondientes a un alojamiento.
    // (Véase alojamientos.csv como ejemplo de formato de salida.)
    // FORMATO DEL FICHERO:
    //  - Los datos deben separarse con comas
    //  - Si el nombre del alojamiento incluye comas, debe guardarse en el fichero entre comillas dobles.
    //    Por ejemplo: "Design, style & vintage by Odenplan"
    // PARÁMETROS:
    //  - fic (ES): flujo de salida hacia fichero
    // PRECONDICIÓN: el fichero está correctamente abierto para escritura
    void Alojamiento::escribir(std::ofstream &fic) const
    {
        fic << id_alojamiento << ',';
        fic << nombre << ',';
        fic << id_anfitrion << ',';
        fic << nombre_anfitrion << ',';
        fic << barrio << ',';
        fic << (setprecision(15)) << latitud << ',';
        fic << (setprecision(15)) << longitud << ',';
        fic << tipo_alojamiento << ',';
        fic << precio << ',';
        fic << minimo_noches << ',';
        fic << disponibilidad_365 << endl;
    }

} // namespace bblProgII