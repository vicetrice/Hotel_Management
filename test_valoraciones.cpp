#include "utilidades.hpp"
#include "valoracion.hpp"
#include "valoraciones.hpp"

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace bblProgII;

const string FIC_VALORACIONES = "_valoraciones_test.csv";
const string FIC_PALABRAS_POSITIVAS = "positive-words.txt";
const string FIC_PALABRAS_NEGATIVAS = "negative-words.txt";

// Prueba del constructor por defecto
void test_constructor()
{
    Valoraciones valoraciones;
    unsigned pos, neg;

    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 0 && neg == 0);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 0 && neg == 0);
}

// Prueba del constructor de copia
void test_constructor_de_copia()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargar_valoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);

    // Llamada al constructor de copia
    Valoraciones copia{valoraciones};
    assert(valoraciones == copia);
}

// Prueba de cargar palabras positivas
void test_cargar_palabras_positivas()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    Valoracion valoracion;
    string palabra;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);

    assert(res == OK);

    valoraciones.numero_palabras(pos, neg);

    assert(pos == 2006);
    assert(neg == 0);

    valoraciones.__consultar_elemento_pos(0, false, true, valoracion, palabra);
    assert(palabra == "a+");
    valoraciones.__consultar_elemento_pos(999, false, true, valoracion, palabra);
    assert(palabra == "insightful");
    valoraciones.__consultar_elemento_pos(1999, false, true, valoracion, palabra);
    assert(palabra == "wows");
    valoraciones.__consultar_elemento_pos(2005, false, true, valoracion, palabra);
    assert(palabra == "zippy");
}

// Prueba de cargar palabras positivas
void test_cargar_palabras_negativas()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    Valoracion valoracion;
    string palabra;

    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);

    assert(res == OK);

    valoraciones.numero_palabras(pos, neg);

    assert(pos == 0);
    assert(neg == 4783);

    valoraciones.__consultar_elemento_pos(0, false, false, valoracion, palabra);
    assert(palabra == "2-faced");
    valoraciones.__consultar_elemento_pos(999, false, false, valoracion, palabra);
    assert(palabra == "despicably");
    valoraciones.__consultar_elemento_pos(1999, false, false, valoracion, palabra);
    assert(palabra == "head-aches");
    valoraciones.__consultar_elemento_pos(4782, false, false, valoracion, palabra);
    assert(palabra == "zombie");
}

// Prueba de cargar_valoraciones
void test_cargar_valoraciones()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    string palabra;
    Valoracion valoracion_aux;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargar_valoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);

    // Comprobamos las valoraciones cargadas
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! "}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}));

    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! "}));
    valoraciones.__consultar_elemento_pos(2, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    // Si intento volver a cargar, no se añade nada (ya existen todas las valoraciones)
    valoraciones.cargar_valoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);

    // Comprobamos las valoraciones cargadas
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! "}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}));

    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! "}));
    valoraciones.__consultar_elemento_pos(2, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));
}

void test_guardar_valoraciones()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    string palabra;
    Valoracion valoracion_aux;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargar_valoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);

    // Guardamos en fichero
    valoraciones.guardar_valoraciones("_valoraciones_test_copia_orden.csv", res);
    assert(res == OK);

    Valoraciones aux;
    aux.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    aux.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    aux.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);
    aux.cargar_valoraciones("_valoraciones_test_copia_orden.csv", res);
    assert(res == OK);
    aux.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);

    assert(aux == valoraciones);
}

// Prueba de numero_valoraciones
void test_numero_valoraciones()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);

    valoraciones.cargar_valoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);
}

// Prueba de lista_valoraciones
void test_lista_valoraciones()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);

    valoraciones.cargar_valoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);

    Ids ids_positivas, ids_negativas;
    valoraciones.lista_valoraciones(ids_positivas, ids_negativas);
    assert(ids_positivas.num_ids == 8);
    assert(ids_negativas.num_ids == 3);
    assert(ids_positivas.ids[0] == 85246);
    assert(ids_positivas.ids[7] == 449750278);
    assert(ids_negativas.ids[0] == 87545);
    assert(ids_negativas.ids[2] == 418091157);
}

// Prueba de numero_palabras
void test_numero_palabras()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);
}

// Prueba de buscar_valoracion
void test_buscar_valoracion()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    Valoracion valoracion_aux;
    bool encontrada, positiva;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);
    valoraciones.insertar_valoracion(Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}, res);
    assert(res == OK);
    valoraciones.insertar_valoracion(Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}, res);
    assert(res == OK);
    valoraciones.insertar_valoracion(Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}, res);
    assert(res == OK);
    valoraciones.insertar_valoracion(Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}, res);
    assert(res == OK);
    valoraciones.insertar_valoracion(Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 3);
    assert(neg == 2);

    // Buscamos valoraciones
    valoraciones.buscar_valoracion(85246, valoracion_aux, encontrada, positiva);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}));
    assert(encontrada);
    assert(positiva);

    valoraciones.buscar_valoracion(156423122, valoracion_aux, encontrada, positiva);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    assert(encontrada);
    assert(positiva);

    valoraciones.buscar_valoracion(449750278, valoracion_aux, encontrada, positiva);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}));
    assert(encontrada);
    assert(positiva);

    valoraciones.buscar_valoracion(87545, valoracion_aux, encontrada, positiva);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}));
    assert(encontrada);
    assert(!positiva);

    valoraciones.buscar_valoracion(418091157, valoracion_aux, encontrada, positiva);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));
    assert(encontrada);
    assert(!positiva);

    valoraciones.buscar_valoracion(5555555, valoracion_aux, encontrada, positiva);
    assert(!encontrada);
}

// Prueba de insertar_valoracion
void test_insertar_valoracion()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    string palabra;
    Valoracion valoracion_aux;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    Valoracion valoracion = Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"};
    valoraciones.insertar_valoracion(valoracion, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 1);
    assert(neg == 0);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));

    valoracion = Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"};
    valoraciones.insertar_valoracion(valoracion, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 1);
    assert(neg == 1);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    valoracion = Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "};
    valoraciones.insertar_valoracion(valoracion, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 2);
    assert(neg == 1);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    valoracion = Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."};
    valoraciones.insertar_valoracion(valoracion, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 3);
    assert(neg == 1);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}));
    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    valoracion = Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "};
    valoraciones.insertar_valoracion(valoracion, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 3);
    assert(neg == 2);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}));
    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    valoraciones.insertar_valoracion(Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}, res);
    assert(res == YA_EXISTE);
    valoraciones.insertar_valoracion(Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}, res);
    assert(res == YA_EXISTE);
    valoraciones.insertar_valoracion(Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}, res);
    assert(res == YA_EXISTE);
    valoraciones.insertar_valoracion(Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}, res);
    assert(res == YA_EXISTE);
    valoraciones.insertar_valoracion(Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}, res);
    assert(res == YA_EXISTE);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 3);
    assert(neg == 2);
}

void test_eliminar_valoracion()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    string palabra;
    Valoracion valoracion_aux;
    bool positiva;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargar_valoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);

    valoraciones.eliminar_valoracion(85246, positiva, res);
    assert(positiva);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 7);
    assert(neg == 3);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! "}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}));
    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! "}));
    valoraciones.__consultar_elemento_pos(2, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    valoraciones.eliminar_valoracion(404219448, positiva, res);
    assert(positiva);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 6);
    assert(neg == 3);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}));
    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! "}));
    valoraciones.__consultar_elemento_pos(2, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    valoraciones.eliminar_valoracion(449750278, positiva, res);
    assert(positiva);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 5);
    assert(neg == 3);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! "}));
    valoraciones.__consultar_elemento_pos(2, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    valoraciones.eliminar_valoracion(87545, positiva, res);
    assert(!positiva);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 5);
    assert(neg == 2);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! "}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    valoraciones.eliminar_valoracion(418091157, positiva, res);
    assert(!positiva);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 5);
    assert(neg == 1);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! "}));

    valoraciones.eliminar_valoracion(170211906, positiva, res);
    assert(!positiva);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 5);
    assert(neg == 0);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));

    valoraciones.eliminar_valoracion(170211906, positiva, res);
    assert(res == NO_EXISTE);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 5);
    assert(neg == 0);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
}

// Prueba de modificar_valoracion
void test_modificar_valoracion()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    string palabra;
    Valoracion valoracion_aux;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargar_valoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);

    // ******** Modificamos valoraciones

    valoraciones.modificar_valoracion(Valoracion{145320, 156423122, "2017-05-20", 45732, "Cassi Na", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment."}, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);
    // Comprobamos las valoraciones
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-20", 45732, "Cassi Na", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment."}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! "}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}));

    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! "}));
    valoraciones.__consultar_elemento_pos(2, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    valoraciones.modificar_valoracion(Valoracion{145320, 156423122, "2017-05-20", 45732, "Cassi Na", "Horrible and awful place, unpleasant and dissapointing. I am very disgusted"}, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 7);
    assert(neg == 4);
    // Comprobamos las valoraciones
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! "}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}));

    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-20", 45732, "Cassi Na", "Horrible and awful place, unpleasant and dissapointing. I am very disgusted"}));
    valoraciones.__consultar_elemento_pos(2, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! "}));
    valoraciones.__consultar_elemento_pos(3, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));

    valoraciones.modificar_valoracion(Valoracion(145320, 170211906, "2017-07-30", 212295, "Eva", "Very nice and wonderful place, I love it"), res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);
    // Comprobamos las valoraciones
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! "}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. "}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!"}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-30", 212295, "Eva", "Very nice and wonderful place, I love it"}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! "}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest"}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!"}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip."}));

    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. "}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-20", 45732, "Cassi Na", "Horrible and awful place, unpleasant and dissapointing. I am very disgusted"}));
    valoraciones.__consultar_elemento_pos(2, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!"}));
}

// Prueba de valoraciones_alojamiento
void test_valoraciones_alojamiento()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    Valoracion valoracion_aux;
    Ids positivas, negativas;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargar_valoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);

    // Consultamos las valoraciones de un alojamiento
    valoraciones.valoraciones_alojamiento(42808, positivas, negativas);
    assert(positivas.num_ids == 2);
    assert(negativas.num_ids == 1);
    assert(positivas.ids[0] == 85246);
    assert(positivas.ids[1] == 90227);
    assert(negativas.ids[0] == 87545);
}

// Prueba de valoraciones_revisor
void test_valoraciones_revisor()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    Valoracion valoracion_aux;
    Ids positivas, negativas;

    valoraciones.cargar_palabras_positivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargar_palabras_negativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numero_palabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargar_valoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numero_valoraciones(pos, neg);
    assert(pos == 8);
    assert(neg == 3);

    // Consultamos las valoraciones de un revisor
    valoraciones.valoraciones_revisor(45732, positivas, negativas);
    assert(positivas.num_ids == 4);
    assert(negativas.num_ids == 0);
    assert(positivas.ids[0] == 85246);
    assert(positivas.ids[1] == 989514);
    assert(positivas.ids[2] == 156423122);
    assert(positivas.ids[3] == 411097466);

    // Consultamos las valoraciones de un revisor
    valoraciones.valoraciones_revisor(212295, positivas, negativas);
    assert(positivas.num_ids == 0);
    assert(negativas.num_ids == 3);
    assert(negativas.ids[0] == 87545);
    assert(negativas.ids[1] == 170211906);
    assert(negativas.ids[2] == 418091157);
}
//***************************
int main()
{
    // Prueba del constructor por defecto
    cout << "testing... 'Valoraciones()'" << endl;
    test_constructor();
    cout << "   --- OK." << endl;

    // Prueba de cargar_palabras_positivas
    cout << "testing... 'void cargar_palabras_positivas(const std::string &, Resultado &)'" << endl;
    test_cargar_palabras_positivas();
    cout << "   --- OK." << endl;

    // Prueba de cargar_palabras_negativas
    cout << "testing... 'void cargar_palabras_negativas(const std::string &, Resultado &)'" << endl;
    test_cargar_palabras_negativas();
    cout << "   --- OK." << endl;

    // Prueba de insertar_valoracion
    cout << "testing... 'void insertar_valoracion(const Valoracion &, Resultado &)'" << endl;
    test_insertar_valoracion();
    cout << "   --- OK." << endl;

    // Prueba de buscar_valoracion
    cout << "testing... 'void buscar_valoracion(unsigned, Valoracion &, bool &, bool &) const'" << endl;
    test_buscar_valoracion();
    cout << "   --- OK." << endl;

    // Prueba de cargar_valoraciones
    cout << "testing... 'void cargar_valoraciones(const std::string &, Resultado &)'" << endl;
    test_cargar_valoraciones();
    cout << "   --- OK." << endl;

    // Prueba de guardar_valoraciones
    cout << "testing... 'void guardar_valoraciones(const std::string &, Resultado &)'" << endl;
    test_guardar_valoraciones();
    cout << "   --- OK." << endl;

    // Prueba de numero_valoraciones
    cout << "testing... 'void numero_valoraciones(unsigned &, unsigned &) const'" << endl;
    test_numero_valoraciones();
    cout << "   --- OK." << endl;

    // Prueba de lista_valoraciones
    cout << "testing... 'void lista_valoraciones(Ids &, Ids &) const'" << endl;
    test_lista_valoraciones();
    cout << "   --- OK." << endl;

    // Prueba de numero_palabras
    cout << "testing... 'void numero_palabras(unsigned &, unsigned &) const'" << endl;
    test_numero_palabras();
    cout << "   --- OK." << endl;

    // Prueba del constructor de copia
    cout << "testing... 'Valoraciones(const Valoraciones &)'" << endl;
    test_constructor_de_copia();
    cout << "   --- OK." << endl;

    // Prueba del eliminar_valoracion
    cout << "testing... 'void eliminar_valoracion(unsigned, bool &, Resultado &)'" << endl;
    test_eliminar_valoracion();
    cout << "   --- OK." << endl;

    // Prueba del modidicar_valoracion
    cout << "testing... 'void modificar_valoracion(const Valoracion &, Resultado &)'" << endl;
    test_modificar_valoracion();
    cout << "   --- OK." << endl;

    // Prueba del valoraciones_alojamiento
    cout << "testing... 'void valoraciones_alojamiento(unsigned, Ids &, Ids &) const'" << endl;
    test_valoraciones_alojamiento();
    cout << "   --- OK." << endl;

    // Prueba del valoraciones_revisor
    cout << "testing... 'void valoraciones_revisor(unsigned, Ids &, Ids &) const'" << endl;
    test_valoraciones_revisor();
    cout << "   --- OK." << endl;

    cout << endl
         << "--- TEST OK." << endl;

    return 0;
}
