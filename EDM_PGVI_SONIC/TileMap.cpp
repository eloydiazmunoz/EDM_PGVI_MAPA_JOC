#include <SFML/Graphics.hpp>  // Incloc la biblioteca gràfica SFML per gestionar gràfics i finestres.
#include <vector>             // Incloc la biblioteca de vectors per emmagatzemar múltiples dades en un array dinàmic.
#include <fstream>            // Incloc la biblioteca per treballar amb fitxers, per llegir i escriure.
#include <iostream>           // Incloc la biblioteca d'entrada/sortida per imprimir missatges al terminal.

class TileMap : public sf::Drawable, public sf::Transformable
{
    // Definició de la classe TileMap que hereta de sf::Drawable (per poder dibuixar-la) i sf::Transformable (per aplicar transformacions).
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // Aquest mètode carrega el tileset (imatge amb les textures) i configura el mapa de tiles.

        // Carrego la textura del tileset des d'un fitxer.
        if (!m_tileset.loadFromFile(tileset))
            return false; // Si falla la càrrega, retorno fals.

        // Redimensiono el VertexArray per contenir tots els tiles en forma de quads (quadrats).
        m_vertices.setPrimitiveType(sf::Quads); // Defineixo el tipus de primitiva com a Quads.
        m_vertices.resize(width * height * 4);  // Cada tile té 4 vèrtexs, per tant, multiplico ample * alt * 4.

        // Recorro el mapa de tiles (ample i alt) i assigno els vèrtexs correctes per a cada tile.
        for (unsigned int i = 0; i < width; ++i) // Recorro les columnes del mapa.
            for (unsigned int j = 0; j < height; ++j) // Recorro les files del mapa.
            {
                // Obtenim el número del tile actual en la posició (i, j).
                int tileNumber = tiles[i + j * width]; // El número del tile es troba a l'índex i + j * ample.

                // Trobo la posició corresponent dins la textura del tileset.
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x); // Columna del tile dins el tileset.
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x); // Fila del tile dins el tileset.

                // Obtenim un punter al quad (el quadrat) actual del tile.
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4]; // Cada tile té 4 vèrtexs.

                // Defineixo les 4 cantonades del quad (posicions en píxels).
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);        // Cantonada superior esquerra.
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);  // Cantonada superior dreta.
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y); // Cantonada inferior dreta.
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);  // Cantonada inferior esquerra.

                // Defineixo les coordenades de textura (quina part del tileset es fa servir).
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);        // Coordenades de textura per la cantonada superior esquerra.
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);  // Coordenades de textura per la cantonada superior dreta.
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y); // Coordenades de textura per la cantonada inferior dreta.
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);  // Coordenades de textura per la cantonada inferior esquerra.
            }

        return true; // Retorno cert si tot ha anat bé.
    }

    bool loadFromFile(const std::string& filename, sf::Vector2u tileSize)
    {
        // Aquest mètode carrega un mapa des d'un fitxer de text.

        std::ifstream file(filename); // Obro el fitxer per llegir-lo.
        if (!file.is_open()) { // Si el fitxer no es pot obrir, retorno fals.
            return false;
        }

        // Llegeixo les dimensions del mapa (ample i alt).
        unsigned int width, height;
        file >> width >> height; // Llegeixo l'ample i l'alt des del fitxer.

        std::vector<int> tiles(width * height); // Creo un vector per emmagatzemar els números dels tiles.

        // Llegeixo el contingut del mapa (els números dels tiles).
        for (unsigned int i = 0; i < width * height; ++i) {
            file >> tiles[i]; // Assigno cada valor llegit al vector de tiles.
        }

        // Carrego el mapa utilitzant el tileset predeterminat "tileset1.png".
        return load("tileset1.png", tileSize, tiles.data(), width, height);
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Aquest mètode dibuixa el mapa a la pantalla.

        // Aplico la transformació actual.
        states.transform *= getTransform();

        // Assigno la textura del tileset als estats de dibuix.
        states.texture = &m_tileset;

        // Dibuixo el VertexArray amb el mapa de tiles.
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices; // VertexArray per emmagatzemar els quads dels tiles.
    sf::Texture m_tileset;      // Texture per emmagatzemar la textura del tileset.
};
