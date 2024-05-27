/* Copyright [2023] <Sudhir Gunaseelan> */

#include <iostream>
#include <string>
#include "Checkers.hpp"

Checkers::Checkers() {
    // Load textures
    m_blackKingTexture.loadFromFile("blackking.png");
    m_blackPawnTexture.loadFromFile("blackpawn.png");
    m_redKingTexture.loadFromFile("redking.png");
    m_redPawnTexture.loadFromFile("redpawn.png");
    m_whiteKingTexture.loadFromFile("whiteking.png");
    m_whitePawnTexture.loadFromFile("whitepawn.png");
    m_congratsTexture.loadFromFile("congrats.png");

    // Initialize the board
    m_board.resize(8);
    for (int i = 0; i < 8; i++) {
        m_board[i].resize(8);
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                if (i < 3) {
                    m_board[i][j] = BLACK_PAWN;
                } else if (i > 4) {
                    m_board[i][j] = RED_PAWN;
                } else {
                    m_board[i][j] = EMPTY;
                }
            } else {
                m_board[i][j] = EMPTY;
            }
        }
    }

    // Set up the initial game state
    m_selectedX = -1;
    m_selectedY = -1;
    m_currentPlayer = BLACK_PAWN;
}

void Checkers::selectPiece(int x, int y) {
    // Select the piece at the given tile coordinates
    if (m_board[y][x] != 0 && (m_board[y][x] == m_currentPlayer ||
        m_board[y][x] == BLACK_KING || m_board[y][x] == RED_KING)) {
        m_selectedX = x;
        m_selectedY = y;
    }
}

void Checkers::movePiece(int x, int y, std::function<void(int, int)> onPieceMoved) {
    // Move the selected piece to the given tile coordinates
    if (m_selectedX >= 0 && m_selectedX < 8 && m_selectedY >= 0 && m_selectedY < 8) {
        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            if (m_board[y][x] == 0) {
                // Check if this move is valid
                int dx = x - m_selectedX;
                int dy = y - m_selectedY;
                if (m_board[m_selectedY][m_selectedX] == BLACK_PAWN) {
                    if ((dy == 1) && abs(dx) == 1) {
                        // Move the piece to the empty tile
                        m_board[y][x] = m_board[m_selectedY][m_selectedX];
                        m_board[m_selectedY][m_selectedX] = 0;
                        if (y == 7) {
                            m_board[y][x] = BLACK_KING;
                        }
                        // Switch control to the other player
                        if (m_currentPlayer == RED_PAWN) {
                            m_currentPlayer = BLACK_PAWN;
                        } else {
                            m_currentPlayer = RED_PAWN;
                        }
                        onPieceMoved(m_selectedX, m_selectedY);
                    } else if ((dy == 2) && abs(dx) == 2) {
                        int midx = (m_selectedX + x) / 2;
                        int midy = (m_selectedY + y) / 2;
                        if (m_board[midy][midx] == RED_PAWN || m_board[midy][midx] == RED_KING) {
                            // Move the piece to the empty tile and remove the jumped pawn
                            m_board[y][x] = m_board[m_selectedY][m_selectedX];
                            m_board[m_selectedY][m_selectedX] = 0;
                            m_board[midy][midx] = 0;
                            if (y == 7) {
                                m_board[y][x] = BLACK_KING;
                            }
                            // Switch control to the other player
                            if (m_currentPlayer == RED_PAWN) {
                                m_currentPlayer = BLACK_PAWN;
                            } else {
                                m_currentPlayer = RED_PAWN;
                            }
                            onPieceMoved(m_selectedX, m_selectedY);
                        }
                        onPieceMoved(midx, midy);
                    }
                } else if (m_board[m_selectedY][m_selectedX] == RED_PAWN) {
                    if (dy == -1 && abs(dx) == 1) {
                        // Move the piece to the empty tile
                        m_board[y][x] = m_board[m_selectedY][m_selectedX];
                        m_board[m_selectedY][m_selectedX] = 0;
                        if (y == 0) {
                            m_board[y][x] = RED_KING;
                        }
                        // Switch control to the other player
                        if (m_currentPlayer == BLACK_PAWN) {
                            m_currentPlayer = RED_PAWN;
                        } else {
                            m_currentPlayer = BLACK_PAWN;
                        }
                        onPieceMoved(m_selectedX, m_selectedY);
                    } else if (dy == -2 && abs(dx) == 2) {
                        int midx = (m_selectedX + x) / 2;
                        int midy = (m_selectedY + y) / 2;
                        if (m_board[midy][midx] == BLACK_PAWN ||
                            m_board[midy][midx] == BLACK_KING) {
                            // Move the piece to the empty tile and remove the jumped pawn
                            m_board[y][x] = m_board[m_selectedY][m_selectedX];
                            m_board[m_selectedY][m_selectedX] = 0;
                            m_board[midy][midx] = 0;
                            if (y == 0) {
                                m_board[y][x] = RED_KING;
                            }
                            // Switch control to the other player
                            if (m_currentPlayer == BLACK_PAWN) {
                                m_currentPlayer = RED_PAWN;
                            } else {
                                m_currentPlayer = BLACK_PAWN;
                            }
                            onPieceMoved(m_selectedX, m_selectedY);
                        }
                        onPieceMoved(midx, midy);
                    }
                } else if (m_board[m_selectedY][m_selectedX] == BLACK_KING) {
                    if ((dy == 1 || dy == -1) && abs(dx) == 1) {
                        // Move the piece to the empty tile
                        m_board[y][x] = m_board[m_selectedY][m_selectedX];
                        m_board[m_selectedY][m_selectedX] = 0;
                        // Switch control to the other player
                        if (m_currentPlayer == BLACK_PAWN) {
                            m_currentPlayer = RED_PAWN;
                        } else {
                            m_currentPlayer = BLACK_PAWN;
                        }
                    } else if ((dy == 2 || dy == -2) && abs(dx) == 2) {
                        int midx = (m_selectedX + x) / 2;
                        int midy = (m_selectedY + y) / 2;
                        if (m_board[midy][midx] == RED_PAWN
                                || m_board[midy][midx] == RED_KING) {
                            // Move the piece to the empty tile and remove the jumped pawn
                            m_board[y][x] = m_board[m_selectedY][m_selectedX];
                            m_board[m_selectedY][m_selectedX] = 0;
                            m_board[midy][midx] = 0;
                            // Switch control to the other player
                            if (m_currentPlayer == BLACK_PAWN) {
                                m_currentPlayer = RED_PAWN;
                            } else {
                                m_currentPlayer = BLACK_PAWN;
                            }
                            onPieceMoved(m_selectedX, m_selectedY);
                        }
                        onPieceMoved(midx, midy);
                    }
                } else if (m_board[m_selectedY][m_selectedX] == RED_KING) {
                    if ((dy == 1 || dy == -1) && abs(dx) == 1) {
                        // Move the piece to the empty tile
                        m_board[y][x] = m_board[m_selectedY][m_selectedX];
                        m_board[m_selectedY][m_selectedX] = 0;
                        // Switch control to the other player
                        if (m_currentPlayer == BLACK_PAWN) {
                            m_currentPlayer = RED_PAWN;
                        } else {
                            m_currentPlayer = BLACK_PAWN;
                        }
                        onPieceMoved(m_selectedX, m_selectedY);
                    } else if ((dy == 2 || dy == -2) && abs(dx) == 2) {
                        int midx = (m_selectedX + x) / 2;
                        int midy = (m_selectedY + y) / 2;
                        if (m_board[midy][midx] == BLACK_PAWN ||
                                m_board[midy][midx] == BLACK_KING) {
                            // Move the piece to the empty tile and remove the jumped pawn
                            m_board[y][x] = m_board[m_selectedY][m_selectedX];
                            m_board[m_selectedY][m_selectedX] = 0;
                            m_board[midy][midx] = 0;
                            // Switch control to the other player
                            if (m_currentPlayer == BLACK_PAWN) {
                                m_currentPlayer = RED_PAWN;
                            } else {
                                m_currentPlayer = BLACK_PAWN;
                            }
                            onPieceMoved(m_selectedX, m_selectedY);
                        }
                        onPieceMoved(midx, midy);
                    }
                }
            }
        }
        m_selectedX = -1;
        m_selectedY = -1;
    }
}

void Checkers::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the frame
    sf::RectangleShape frame(sf::Vector2f(8 * 56 + getBorderSize() * 2,
        8 * 56 + getBorderSize() * 2));
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(8.f);
    frame.setOutlineColor(sf::Color::Green);
    frame.setPosition(sf::Vector2f(getBorderSize(), getBorderSize()));
    target.draw(frame);

    // Draw the board
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            // Calculate the color of the current square
            sf::Color squareColor;
            if ((x + y) % 2 == 0) {
                squareColor = sf::Color::Red;
            } else {
                squareColor = sf::Color::Black;
            }
            // Draw the square
            sf::RectangleShape square(sf::Vector2f(64.f, 64.f));
            square.setFillColor(squareColor);
            square.setPosition(x * 64.f + getBorderSize(), y * 64.f + getBorderSize());
            target.draw(square, states);
        }
    }

    // Draw the pieces
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (m_board[y][x] != EMPTY) {
                sf::Texture texture;
                std::string filename;
                switch (m_board[y][x]) {
                    case BLACK_PAWN:
                        filename = "blackpawn.png";
                        break;
                    case BLACK_KING:
                        filename = "blackking.png";
                        break;
                    case RED_PAWN:
                        filename = "redpawn.png";
                        break;
                    case RED_KING:
                        filename = "redking.png";
                        break;
                }
                texture.loadFromFile(filename);
                sf::Sprite sprite(texture);
                sprite.setPosition(x * 64.f + getBorderSize(), y * 64.f + getBorderSize());
                target.draw(sprite, states);
            }
        }
    }

    // Draw the selected piece
    if (m_selectedX != -1 && m_selectedY != -1) {
        sf::CircleShape selection(32.f);
        selection.setFillColor(sf::Color::Transparent);
        selection.setOutlineThickness(4.f);
        selection.setOutlineColor(sf::Color::Yellow);
        selection.setPosition(m_selectedX * 64.f + getBorderSize(),
            m_selectedY * 64.f + getBorderSize());
        target.draw(selection, states);
    }

    // Check if the game is over
    bool blackCanMove = false;
    bool redCanMove = false;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (m_board[y][x] == BLACK_PAWN || m_board[y][x] == BLACK_KING) {
                if (y < 7) {
                    if (x > 0 && m_board[y+1][x-1] == EMPTY) {
                        blackCanMove = true;
                    }
                    if (x < 7 && m_board[y+1][x+1] == EMPTY) {
                        blackCanMove = true;
                    }
                    if (y < 6) {
                        if (x > 1 && m_board[y+2][x-2] == EMPTY && (m_board[y+1][x-1] == RED_PAWN ||
                            m_board[y+1][x-1] == RED_KING)) {
                            blackCanMove = true;
                        }
                        if (x < 6 && m_board[y+2][x+2] == EMPTY && (m_board[y+1][x+1] == RED_PAWN ||
                            m_board[y+1][x+1] == RED_KING)) {
                            blackCanMove = true;
                        }
                    }
                }
            } else if (m_board[y][x] == RED_PAWN || m_board[y][x] == RED_KING) {
                if (y > 0) {
                    if (x > 0 && m_board[y-1][x-1] == EMPTY) {
                        redCanMove = true;
                    }
                    if (x < 7 && m_board[y-1][x+1] == EMPTY) {
                        redCanMove = true;
                    }
                    if (y > 1) {
                        if (x > 1 && m_board[y-2][x-2] == EMPTY &&
                            (m_board[y-1][x-1] == BLACK_PAWN || m_board[y-1][x-1] == BLACK_KING)) {
                            redCanMove = true;
                        }
                        if (x < 6 && m_board[y-2][x+2] == EMPTY &&
                            (m_board[y-1][x+1] == BLACK_PAWN || m_board[y-1][x+1] == BLACK_KING)) {
                            redCanMove = true;
                        }
                    }
                }
            }
        }
    }
    if (!blackCanMove) {
        sf::Sprite congratsSprite(m_congratsTexture);
        congratsSprite.setPosition(sf::Vector2f(100, 100));
        target.draw(congratsSprite, states);
    } else if (!redCanMove) {
        sf::Sprite congratsSprite(m_congratsTexture);
        congratsSprite.setPosition(sf::Vector2f(100, 100));
        target.draw(congratsSprite, states);
    }
}
