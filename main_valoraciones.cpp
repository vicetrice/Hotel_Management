#include "valoraciones.hpp"
#include "valoracion.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "alojamientos.hpp"
#include "alojamiento.hpp"

using namespace std;
using namespace bblProgII;

void menu();

int main()
{

    char x = '\0';
    Alojamientos alo;
    Alojamiento l;
    Valoraciones valo;
    Valoracion v;
    string nom_fic;
    unsigned m;
    double a;
    Resultado res;

    do
    {
        menu();
        cin >> x;
        if (x == 'a')
        {
            cin.ignore(9999, '\n');
            cout << "Introduzca el nombre del fichero de donde se cargaran los alojamiento: ";
            getline(cin, nom_fic, '\n');
            alo.leer_alojamientos(nom_fic, res);
            escribir_resultado(res);
        }
        else if (x == 'b')
        {
            cin.ignore(9999, '\n');
            cout << "Introduzca el nombre del fichero de donde se cargaran las palabras positivas: ";
            getline(cin, nom_fic, '\n');
            valo.cargar_palabras_positivas(nom_fic, res);
            escribir_resultado(res);
            cout << "Introduzca el nombre del fichero de donde se cargaran las palabras negativas: ";
            getline(cin, nom_fic, '\n');
            valo.cargar_palabras_negativas(nom_fic, res);
            escribir_resultado(res);
        }
        else if (x == 'c')
        {
            cin.ignore(9999, '\n');
            cout << "Introduzca el nombre del fichero de donde se cargaran las valoraciones: ";
            getline(cin, nom_fic, '\n');
            valo.cargar_valoraciones(nom_fic, res);
            escribir_resultado(res);
        }
        else if (x == 'd')
        {
            cin.ignore(9999, '\n');
            cout << "Introduzca el nombre del fichero donde se guardaran los alojamientos: ";
            getline(cin, nom_fic, '\n');
            alo.escribir_en_fichero(nom_fic, res);
            escribir_resultado(res);
        }
        else if (x == 'e')
        {
            cin.ignore(9999, '\n');
            cout << "Introduzca el nombre del fichero donde se guardaran las valoraciones: ";
            getline(cin, nom_fic, '\n');
            valo.guardar_valoraciones(nom_fic, res);
            escribir_resultado(res);
        }
        else if (x == 'f')
        {
            cin.ignore(9999, '\n');
            cout << "introuduce un barrio: ";
            getline(cin, nom_fic, '\n');
            l.asignar_barrio(nom_fic);
            cout << "introduce la disponibilidad: ";
            cin >> m;
            l.asignar_disponibilidad_365(m);
            cout << "introduce el id de alojamiento: ";
            cin >> m;
            l.asignar_id_alojamiento(m);
            cout << "introuduce el id de anfitrion: ";
            cin >> m;
            l.asignar_id_anfitrion(m);
            cout << "introduce la latitud: ";
            cin >> a;
            l.asignar_latitud(a);
            cout << "introduce la longitud: ";
            cin >> a;
            l.asignar_longitud(a);
            cout << "introduce el minimo de noches: ";
            cin >> m;
            l.asignar_minimo_noches(m);
            cout << "introduce el nombre del alojamiento: ";
            getline(cin, nom_fic, '\n');
            l.asignar_nombre(nom_fic);
            cin.ignore(9999, '\n');
            cout << "introduce el nombre del anfitrion: ";
            getline(cin, nom_fic, '\n');
            l.asignar_nombre_anfitrion(nom_fic);
            cout << "introduce el precio: ";
            cin >> a;
            l.asignar_precio(a);
            cin.ignore(9999, '\n');
            cout << "introduce el tipo de alojamiento: ";
            getline(cin, nom_fic, '\n');
            l.asignar_tipo_alojamiento(nom_fic);
            alo.insertar_alojamiento(l, res);
            escribir_resultado(res);
        }
        else if (x == 'g')
        {
            cout << "introduce el id del alojamiento a eliminar: ";
            cin >> m;
            alo.eliminar_alojamiento(m, res);
            escribir_resultado(res);
        }
        else if (x == 'h')
        {
            cin.ignore(9999, '\n');
            cout << "introuduce un barrio: ";
            getline(cin, nom_fic, '\n');
            l.asignar_barrio(nom_fic);
            cout << "introduce la disponibilidad: ";
            cin >> m;
            l.asignar_disponibilidad_365(m);
            cout << "introduce el id de alojamiento: ";
            cin >> m;
            l.asignar_id_alojamiento(m);
            cout << "introuduce el id de anfitrion: ";
            cin >> m;
            l.asignar_id_anfitrion(m);
            cout << "introduce la latitud: ";
            cin >> a;
            l.asignar_latitud(a);
            cout << "introduce la longitud: ";
            cin >> a;
            l.asignar_longitud(a);
            cout << "introduce el minimo de noches: ";
            cin >> m;
            l.asignar_minimo_noches(m);
            cout << "introduce el nombre del alojamiento: ";
            getline(cin, nom_fic, '\n');
            l.asignar_nombre(nom_fic);
            cin.ignore(9999, '\n');
            cout << "introduce el nombre del anfitrion: ";
            getline(cin, nom_fic, '\n');
            l.asignar_nombre_anfitrion(nom_fic);
            cout << "introduce el precio: ";
            cin >> a;
            l.asignar_precio(a);
            cin.ignore(9999, '\n');
            cout << "introduce el tipo de alojamiento: ";
            getline(cin, nom_fic, '\n');
            l.asignar_tipo_alojamiento(nom_fic);
            alo.modificar_alojamiento(l, res);
            escribir_resultado(res);
        }
        else if (x == 'i')
        {
            cout << "escribe el id del alojamiento a consultar: ";
            cin >> m;
            alo.consultar_alojamiento(m, l, res);
            if (res == OK)
            {
                escribir_resultado(res);
                l.escribir();
            }
            else
            {
                escribir_resultado(res);
            }
            cout << endl;
        }
        else if (x == 'j')
        {
            alo.escribir();
        }
        else if (x == 'k')
        {
            Ids id;
            cin.ignore(9999, '\n');
            string c;
            cout << "escribe el barrio: ";
            getline(cin, nom_fic, '\n');
            cout << "escribe el numero de noches: ";
            cin >> m;
            cout << "escribe el precio: ";
            cin >> a;
            cin.ignore(9999, '\n');
            cout << "escribe el tipo de alojamiento: ";
            getline(cin, c, '\n');
            alo.alojamientos_filtros(nom_fic, c, a, m, id);
            for (unsigned i = 0; i < id.num_ids; i++)
            {
                alo.consultar_alojamiento(id.ids[i], l, res);
                if (res == OK)
                {
                    escribir_resultado(res);
                    l.escribir();
                }
                else
                {
                    escribir_resultado(res);
                }
                cout << endl;
            }
        }
        else if (x == 'l')
        {
            cin.ignore(9999, '\n');
            cout << "escribe un comentario: ";
            getline(cin, nom_fic, '\n');
            v.asignar_comentarios(nom_fic);
            cout << "escribe la fecha(formato: aaaa-mm-dd): ";
            getline(cin, nom_fic, '\n');
            v.asignar_fecha(nom_fic);
            cout << "escribe un id de alojamiento: ";
            cin >> m;
            v.asignar_id_alojamiento(m);
            cout << "escribe un id de revisor: ";
            cin >> m;
            v.asignar_id_revisor(m);
            cout << "escribe un id de valoracion: ";
            cin >> m;
            v.asignar_id_valoracion(m);
            cin.ignore(9999, '\n');
            cout << "escribe el nombre del revisor: ";
            getline(cin, nom_fic, '\n');
            v.asignar_nombre_revisor(nom_fic);
            valo.insertar_valoracion(v, res);
            escribir_resultado(res);
        }
        else if (x == 'm')
        {
            bool esta, posi;
            cout << "escribe el id de la valoracion a eliminar: ";
            cin >> m;
            valo.buscar_valoracion(m, v, esta, posi);

            valo.eliminar_valoracion(v.consultar_id_valoracion(), posi, res);

            escribir_resultado(res);
        }
        else if (x == 'n')
        {
            cin.ignore(9999, '\n');
            cout << "escribe un comentario: ";
            getline(cin, nom_fic, '\n');
            v.asignar_comentarios(nom_fic);
            cout << "escribe la fecha(formato: aaaa-mm-dd): ";
            getline(cin, nom_fic, '\n');
            v.asignar_fecha(nom_fic);
            cout << "escribe un id de alojamiento: ";
            cin >> m;
            v.asignar_id_alojamiento(m);
            cout << "escribe un id de revisor: ";
            cin >> m;
            v.asignar_id_revisor(m);
            cout << "escribe un id de valoracion: ";
            cin >> m;
            v.asignar_id_valoracion(m);
            cin.ignore(9999, '\n');
            cout << "escribe el nombre del revisor: ";
            getline(cin, nom_fic, '\n');
            v.asignar_nombre_revisor(nom_fic);
            valo.modificar_valoracion(v, res);
            escribir_resultado(res);
        }
        else if (x == 'o')
        {
            bool esta, posi;
            cout << "introduce el id de la valoracion: ";
            cin >> m;
            valo.buscar_valoracion(m, v, esta, posi);
            if (esta)
            {
                v.escribir();
            }
            else
            {
                res = NO_EXISTE;
                escribir_resultado(res);
            }

            cout << endl;
        }
        else if (x == 'p')
        {
            valo.escribir();
        }
        else if (x == 'q')
        {
            bool l, a;
            cout
                << "escribe el id de alojamiento: ";
            cin >> m;
            Ids ap, d;
            valo.valoraciones_alojamiento(m, ap, d);
            for (unsigned i = 0; i < ap.num_ids; i++)
            {
                valo.buscar_valoracion(ap.ids[i], v, l, a);
                if (l)
                {
                    v.escribir();
                }
                else
                {
                    res = NO_EXISTE;
                    escribir_resultado(res);
                }

                cout << endl;
            }
            for (unsigned i = 0; i < d.num_ids; i++)
            {
                valo.buscar_valoracion(d.ids[i], v, l, a);
                if (l)
                {
                    v.escribir();
                }
                else
                {
                    res = NO_EXISTE;
                    escribir_resultado(res);
                }

                cout << endl;
            }
        }
        else if (x == 'r')
        {
            bool l, a;
            cout
                << "escribe el id del revisor: ";
            cin >> m;
            Ids ap, d;
            valo.valoraciones_revisor(m, ap, d);
            for (unsigned i = 0; i < ap.num_ids; i++)
            {
                valo.buscar_valoracion(ap.ids[i], v, l, a);
                if (l)
                {
                    v.escribir();
                }
                else
                {
                    res = NO_EXISTE;
                    escribir_resultado(res);
                }

                cout << endl;
            }
            for (unsigned i = 0; i < d.num_ids; i++)
            {
                valo.buscar_valoracion(d.ids[i], v, l, a);
                if (l)
                {
                    v.escribir();
                }
                else
                {
                    res = NO_EXISTE;
                    escribir_resultado(res);
                }

                cout << endl;
            }
        }
        else if (x < 'a' || x > 'x')
        {
            cout << "opcion no disponible, inserte una opcion disponible: " << endl;
        }

    } while (x != 'x');

    return 0;
}

void menu()
{

    cout << "MENÚ DE OPCIONES (elija una opción y pulse <enter>):" << endl
         << endl;
    cout << "a -> CARGAR ALOJAMIENTOS desde fichero" << endl;
    cout << "b -> CARGAR PALABRAS positivas/negativas desde fichero" << endl;
    cout << "c -> CARGAR VALORACIONES desde fichero" << endl;
    cout << "d -> GUARDAR ALOJAMIENTOS en fichero" << endl;
    cout << "e -> GUARDAR VALORACIONES en fichero" << endl;
    cout << "f -> AÑADIR ALOJAMIENTO" << endl;
    cout << "g -> ELIMINAR ALOJAMIENTO" << endl;
    cout << "h -> MODIFICAR ALOJAMIENTO" << endl;
    cout << "i -> CONSULTAR UN ALOJAMIENTO" << endl;
    cout << "j -> ESCRIBIR TODOS LOS ALOJAMIENTOS por pantalla" << endl;
    cout << "k -> OBTENER Y ESCRIBIR LOS ALOJAMIENTOS QUE PASEN LOS FILTROS" << endl;
    cout << "l -> AÑADIR UNA VALORACIÓN para un alojamiento de la lista de alojamientos" << endl;
    cout << "m -> ELIMINAR UNA VALORACIÓN" << endl;
    cout << "n -> MODIFICAR UNA VALORACIÓN" << endl;
    cout << "o -> BUSCAR UNA VALORACIÓN" << endl;
    cout << "p -> ESCRIBIR TODAS LAS VALORACIONES por pantalla" << endl;
    cout << "q -> OBTENER Y ESCRIBIR LAS VALORACIONES DE UN ALOJAMIENTO por pantalla" << endl;
    cout << "r -> OBTENER Y ESCRIBIR LAS VALORACIONES DE UN REVISOR por pantalla" << endl;
    cout << "x -> SALIR DEL PROGRAMA" << endl;
}
