/* Copyright [2023] <Sudhir Gunaseelan> */

#ifndef _HOME_VBOXUSER_PS4B_CHECKERS_HPP_
#define _HOME_VBOXUSER_PS4B_CHECKERS_HPP_

#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>

class Checkers : public sf::Drawable {
 public:
    static constexpr int EMPTY = 0;
    static constexpr int RED_PAWN = 1;
    static constexpr int RED_KING = 2;
    static constexpr int BLACK_PAWN = 3;
    static constexpr int BLACK_KING = 4;

    Checkers();
    int getSelectedX() const { return m_selectedX; }
    int getSelectedY() const { return m_selectedY; }
    int getBorderSize() const { return BORDER_SIZE; }

    void selectPiece(int x, int y);
    void movePiece(int x, int y, std::function<void(int, int)> onPieceMoved);

 private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Texture m_blackKingTexture;
    sf::Texture m_blackPawnTexture;
    sf::Texture m_redKingTexture;
    sf::Texture m_redPawnTexture;
    sf::Texture m_whiteKingTexture;
    sf::Texture m_whitePawnTexture;
    sf::Texture m_congratsTexture;

    std::vector<std::vector<int>> m_board;
    int m_selectedX;
    int m_selectedY;
    int m_currentPlayer;
    const int BORDER_SIZE = 32;
};

#endif  // _HOME_VBOXUSER_PS4B_CHECKERS_HPP_
