# PS4a: Checkers

## Contact
Name: Sudhir Gunaseelan
Section: 202
Time to Complete: 6-7 hrs

## Description
Explain what the project does.
This project is based on to implement the gameplay mechanics of the checkers game from part (a) where we created the environment for the game.

### Features
Describe what your major decisions were and why you did things that way.
The Checkers class is defined with several public methods and private data members. The public methods include getSelectedX() and getSelectedY() which return the currently selected tile coordinates, selectPiece(int x, int y) which highlights a piece at the given tile coordinates, and movePiece(int x, int y) which moves the selected piece to the given tile coordinates. The private data members include textures for the various pieces, a two-dimensional vector representing the state of the game board, and the currently selected tile coordinates.

The Checkers() constructor initializes the textures and the game board to its initial state. The selectPiece(int x, int y) method selects the piece at the given tile coordinates if it exists. The movePiece(int x, int y) method moves the currently selected piece to the given tile coordinates if they are empty. I have implemented this function with 4 case where the piece being the red pawn, black pawn, red king and black king. For this I identified which piece could be in the middle to jump over that piece and capture or remove it from the gameplay. Finally, the draw(sf::RenderTarget& target, sf::RenderStates states) const method is an overridden function from the SFML Drawable interface which renders the game board and pieces.

In the main() function, I have drawn the checkers game board that is used to highlight the selected piece and move the piece to the respective position.

### Memory
Describe how you stored the game board including if you used smart pointers.
I stored the game board using the 2d vector with a nested for loop having 8 as the row and column since the game board must have 8 rows and 8 columns.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.
I have used the lambda expression in my movePiece() function by adding a new parameter std::function<void(int, int)> that allows to pass any callable object that takes two integers as arguments and returns void. For this, I used the <functional> library.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
I had trouble with invoking function from <algorithm> library.
fully works

### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.
TA
Congratulatory Image - https://www.freepik.com/premium-vector/comic-speech-bubbles-with-text-you-win-cloud-balloon-pop-art-style-explosion-blast-with-text-stars-jackpot-congratulation-message-vintage-banner-cartoon-vector-illustration_17578118.htm
