# GameCaro

GameCaro is a console-based Gomoku (Caro) game written in C++.

The game features an 11×11 board, keyboard controls, five-in-a-row win detection, and score tracking for two players.

## Features

- 11×11 game board
- Two-player gameplay: X and O
- Keyboard-controlled cursor movement
- Five-in-a-row win detection
- Score tracking for both players
- Reset the board and continue playing
- Console-based interface

## Controls

| Key | Action |
|---|---|
| Arrow Keys | Move the cursor |
| Space | Place a piece |
| R | Reset the board |
| E | Exit the game |

## How to Play

1. Run the game from Visual Studio.
2. Use the arrow keys to move the cursor around the board.
3. Press `Space` to place your piece.
4. Players take turns placing X and O.
5. The first player to get five pieces in a row wins.
6. Press `R` to reset the board.
7. Press `E` to exit the game.

## Technologies

- C++
- Visual Studio
- Windows Console API

## Project Structure


GameCaro/
+-- GameCaro.cpp
+-- GameCaro.vcxproj
+-- GameCaro.vcxproj.filters
+-- Screen.cpp
+-- Screen.h
+-- GameCaro.sln