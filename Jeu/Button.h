#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace spaceShooter
{
    /// <summary>
    /// Textbox de base, pleine de flaws, mais qui fera la job pour ce TP
    /// Notez que on peut l'utiliser aussi comme texte d'information.  Idéalement,
    /// On aurait une structure TexteDeBase comme superclasse avec Label et Textbox
    /// Comme sous-classe.  Ceci dit je suis très serré dans le temps, alors je livre
    /// vite quelque chose qui marche.
    /// </summary>
    class Button
    {
        //DOC DES MÉTHODES DANS LE .CPP
    public:
        Button();
        ~Button();
        void init(const int longueur, const int limite, const Vector2f position, const Font& font);
        void initInfo(const Vector2f position, const Font& font, const bool estErreur);
        void insererTexte(String leTexte);
        void ajouterChar(const char leChar);
        void retirerChar();
        void dessiner(RenderWindow* const window);
        void selectionner(Color color);
        void deSelectionner();
        bool touche(const Vector2i& position);
        // <smasson>
        void SetFontColor(Color color);
        float getTailleTexte();
        void SetSize(int longueur, int hauteur);
        // </smasson>
        String getTexte() const;

    private:
        void ajustementsVisuels();

        /// <summary>
        /// Limite de caractères que notre textbox tolère.  Mettez 1 de limite par 20 pixels de largeur de votre boite
        /// Ainsi si vous entrez que des caractères larges (comme W par exemple), tout va entrer
        /// </summary>
        int limite;

        /// <summary>
        /// Graphiquement, la textbox est un simple rectangle.
        /// </summary>
        RectangleShape boite;

        /// <summary>
        /// Le texte à afficher.
        /// </summary>
        Text texte;

        //<smasson>
        int lastWidth;
        int lastHeight;
        //</smasson>

    };
}