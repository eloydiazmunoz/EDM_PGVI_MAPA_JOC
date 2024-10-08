#include <SFML/Graphics.hpp>  // Incloc la biblioteca gr�fica SFML per gestionar gr�fics i finestres.
#include "TileMap.cpp"        // Incloc la implementaci� de la classe TileMap per carregar i dibuixar el mapa de tiles.
#include <iostream>           // Incloc la biblioteca per fer servir entrada/sortida per consola.
#include <fstream>            // Incloc la biblioteca per treballar amb fitxers, ja que carregar� el mapa des de fitxers.
#include <string>             // Incloc la biblioteca per treballar amb cadenes de text.

int main()
{
    // Crear la finestra de la pantalla on es mostrar� el joc o el mapa.
    sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap"); // Definim la finestra amb una mida de 512x256 p�xels.

    // Variable per a la selecci� del fitxer del mapa.
    std::string mapaFitxer; // Aqu� guardar� el nom del fitxer del mapa que l'usuari seleccionar�.

    // Preguntar a l'usuari quin mapa vol carregar.
    while (true) { // Bucle infinit fins que l'usuari seleccioni una opci� v�lida.
        std::cout << "Selecciona el mapa (1 o 2):" << std::endl; // Imprimeixo el missatge de selecci� del mapa.
        std::cout << "1. mapa.txt" << std::endl; // Opci� 1: mapa.txt
        std::cout << "2. mapa1.txt" << std::endl; // Opci� 2: mapa1.txt

        int opcio; // Variable per guardar l'opci� seleccionada per l'usuari.
        std::cin >> opcio; // Llegeixo l'opci� seleccionada per l'usuari des de la consola.

        // Verifico quina opci� ha seleccionat l'usuari.
        if (opcio == 1) { // Si l'opci� �s 1:
            mapaFitxer = "mapa.txt"; // Selecciono el fitxer "mapa.txt".
            break; // Surto del bucle perqu� ja s'ha seleccionat el mapa.
        }
        else if (opcio == 2) { // Si l'opci� �s 2:
            mapaFitxer = "mapa1.txt"; // Selecciono el fitxer "mapa1.txt".
            break; // Surto del bucle perqu� ja s'ha seleccionat el mapa.
        }
        else {
            // Si l'opci� �s inv�lida, imprimeixo un missatge d'error i torno a preguntar.
            std::cout << "Opci� inv�lida. Torna a provar." << std::endl;
        }
    }

    // Crear el TileMap a partir del fitxer seleccionat.
    TileMap map; // Creo una inst�ncia de la classe TileMap per manejar el mapa.
    if (!map.loadFromFile(mapaFitxer, sf::Vector2u(32, 32))) { // Carrego el mapa amb tiles de 32x32 p�xels.
        return -1; // Si no es pot carregar el mapa (error), retorno -1 per indicar un error i sortir.
    }

    // Executar el bucle principal del programa.
    while (window.isOpen()) // Bucle principal que continuar� mentre la finestra estigui oberta.
    {
        // Manejar esdeveniments (com el tancament de la finestra).
        sf::Event event;
        while (window.pollEvent(event)) // Processar tots els esdeveniments que han passat.
        {
            if (event.type == sf::Event::Closed) // Si l'usuari tanca la finestra:
                window.close(); // Tanco la finestra i finalitzo el bucle.
        }

        // Dibuixar el mapa a la finestra.
        window.clear(); // Esborro el contingut de la finestra abans de redibuixar.
        window.draw(map); // Dibuixo el mapa a la finestra utilitzant el TileMap carregat.
        window.display(); // Mostro el contingut recentment dibuixat a la finestra.
    }

    return 0; // Finalitzo el programa correctament.
}
