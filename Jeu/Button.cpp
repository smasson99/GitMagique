#include "Button.h"

using namespace spaceShooter;

Button::Button()
{
}

Button::~Button()
{
}

/// <summary>
/// Initiation d'un Textbox.  Le choix ne rien mettre dans le constructeur vient du fait
/// Qu'il est inutile d'initialiser quoi que ce soit tant qu'on a pas une font valide.
/// Où alors on serait obligé de l'utiliser comme pointeur.
/// La méthode init règle la question
///
/// Certains éléments sont délibéréments hardcodés; on ne veut pas une textbox hyper-flexible
/// Juste de quoi qui fera le travail pour ce TP
///
/// </summary>
/// <param name="longueur">Longueur du Textbox</param>
/// <param name="limite">Limite de caractères; devrait être 1 pour 20 pixels de longueur du textbox</param>
/// <param name="position">Position à l'écran.  Le Textbox est centrée sur cette position.</param>
/// <param name="font">La font utilisée</param>
void Button::init(const int longueur, const int limite, const Vector2f position, const Font& font)
{
    int hauteur = 30;
    this->limite = limite;

    boite.setSize(Vector2f(longueur, hauteur));
    boite.setFillColor(Color::Black);
    boite.setOutlineColor(Color::White);
    boite.setOutlineThickness(2);
    boite.setOrigin(Vector2f(longueur / 2, hauteur / 2));
    boite.setPosition(position);

    texte.setFont(font);
    texte.setCharacterSize(20);
    texte.setFillColor(Color::White);

    //Backup des dimensions pour un éventuel setSize
    lastWidth = longueur;
    lastHeight = hauteur;
}


/// <summary>
/// Voir précédent, mais utilisé comme Label
/// La boite est toujours présente (pas le choix), mais carrément invisible
///
/// Si le texte notifie une erreur, on le mettra de couleur rouge
/// </summary>
void Button::initInfo(const Vector2f position, const Font& font, const bool estErreur)
{
    int hauteur = 30;
    this->limite = 60;// pas de graphique associé, on peut mettre un long texte par défaut.

    boite.setSize(Vector2f(0, 0));
    boite.setFillColor(Color::Transparent);
    boite.setOutlineColor(Color::Transparent);
    boite.setOutlineThickness(0);
    boite.setOrigin(Vector2f(0, 0));
    boite.setPosition(position);

    texte.setFont(font);
    texte.setCharacterSize(20);

    if (estErreur)
    {
        texte.setFillColor(Color::Red);
    }
    else
    {
        texte.setFillColor(Color::White);
    }
}

/// <summary>
/// Fait juste changer la couleur du cadre.
/// </summary>
void Button::selectionner(Color color)
{
    boite.setOutlineColor(color);
}

void Button::deSelectionner()
{
    boite.setOutlineColor(Color::White);
}

/// <summary>
/// Vérifie si une position touche au textbox
/// </summary>
bool Button::touche(const Vector2i& position)
{
    FloatRect coord = boite.getGlobalBounds();

    if (position.x > coord.left && position.x < coord.left + coord.width &&
        position.y > coord.top && position.y < coord.top + coord.height)
    {
        return true;
    }

    return false;
}

void spaceShooter::Button::SetFontColor(Color color)
{
    texte.setFillColor(color);
}

float Button::getTailleTexte()
{
    return texte.getCharacterSize();
}

void spaceShooter::Button::SetSize(int longueur, int hauteur)
{
    //<smasson>
    //Initialisation des variables
    int totalLast = lastWidth + lastHeight;
    int totalNew = longueur + hauteur;
    float percent = totalNew / totalLast;
    bool isHigher = totalNew > totalLast;
    int newFontSize = texte.getCharacterSize();
    //Si nous avons une taille moyennement plus grande que la précédente
    if (isHigher)
    {
        //On agrandit la size de la font
        percent = percent - 1;
        newFontSize = texte.getCharacterSize()*percent + texte.getCharacterSize();
    }
    //Sinon, si nous avons une size moyennement plus petite que la précédente
    else if (totalNew != totalLast)
    {
        //On réduit la size de la font
        newFontSize = texte.getCharacterSize() - texte.getCharacterSize()*percent;
    }
    //Appliquer les changements
    texte.setCharacterSize(newFontSize);
    boite.setSize(Vector2f(longueur, hauteur));
    boite.setOrigin(Vector2f(longueur / 2, hauteur / 2));
    //</smasson>
}

String Button::getTexte() const
{
    return texte.getString();
}

/// <summary>
/// Le texte est inséré et remplace le précédent.
/// </summary>
/// <param name="leTexte">The le texte.</param>
void Button::insererTexte(String leTexte)
{
    //Si trop long on concatène
    if (leTexte.getSize() > limite)
    {
        leTexte = leTexte.substring(0, limite);
    }

    texte.setString(leTexte);
    ajustementsVisuels();
}
/// <summary>
/// On ajoute un caractère à la string, si on est pas à la longueur maximale
/// </summary>
void Button::ajouterChar(const char leChar)
{
    if (texte.getString().getSize() >= limite) return;

    texte.setString(texte.getString() + leChar);
    ajustementsVisuels();
}

/// <summary>
/// On retire un caractère à la string, si on est pas à la longueur 0
/// </summary>
void Button::retirerChar()
{
    if (texte.getString().getSize() == 0) return;

    texte.setString(texte.getString().substring(0, texte.getString().getSize() - 1));
    ajustementsVisuels();
}

/// <summary>
/// Ajustements visuels: le texte est toujours centré sur la position de la boite.
/// </summary>
void Button::ajustementsVisuels()
{
    FloatRect coord = texte.getGlobalBounds();
    texte.setOrigin(Vector2f(coord.width / 2, coord.height / 2));
    texte.setPosition(boite.getPosition().x, boite.getPosition().y - (texte.getCharacterSize() / 10 * 2 + 1)/*-5*/);
}

void Button::dessiner(RenderWindow* const window)
{
    window->draw(boite);
    window->draw(texte);
}
