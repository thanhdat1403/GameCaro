// GameCaro.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Screen.h"
Screen scr;

int X0 = 4, Y0 = 3;
int _size = 11;

const char space = '.';

void draw_line(int index, int left, int mid, int right) {
    scr.SetCursorPos(X0 - 1, Y0 + index);
    scr.Write(char(left));
    for (int i = 0; i < _size * 2 + 1; i++)
        scr.Write(char(mid));
    scr.Write(char(right));
}
void draw_frame() {
    draw_line(-1, 201, 205, 187);
    for (int i = 0; i < _size; i++)
        draw_line(i, 186, space, 186);
    draw_line(_size, 200, 205, 188);
}

class Game {
    int row, column;
    char player;
    char data[11][11]; // Mảng lưu trạng thái của bảng caro
    int scoreX, scoreO; // Biến lưu trữ tỷ số

public:
    Game() {
        row = column = _size / 2;
        player = 'x';
        memset(data, 0, sizeof(data)); // Khởi tạo tất cả phần tử của mảng data bằng 0
        scoreX = 0;
        scoreO = 0;
    }

private:
    void change(int& i, int d) {
        i += d;
        if (i < 0)
            i = _size - 1;
        else if (i >= _size)
            i = 0;
    }
    bool checkWin(int r, int c, char p) {
        // Kiểm tra các hàng, cột và đường chéo
        int count;

        // Kiểm tra hàng
        count = 0;
        for (int i = 0; i < _size; i++) {
            if (data[r][i] == p) {
                count++;
                if (count == 5) return true;
            }
            else {
                count = 0;
            }
        }

        // Kiểm tra cột
        count = 0;
        for (int i = 0; i < _size; i++) {
            if (data[i][c] == p) {
                count++;
                if (count == 5) return true;
            }
            else {
                count = 0;
            }
        }

        // Kiểm tra đường chéo chính
        count = 0;
        for (int i = -4; i <= 4; i++) {
            int nr = r + i, nc = c + i;
            if (nr >= 0 && nr < _size && nc >= 0 && nc < _size) {
                if (data[nr][nc] == p) {
                    count++;
                    if (count == 5) return true;
                }
                else {
                    count = 0;
                }
            }
        }

        // Kiểm tra đường chéo phụ
        count = 0;
        for (int i = -4; i <= 4; i++) {
            int nr = r + i, nc = c - i;
            if (nr >= 0 && nr < _size && nc >= 0 && nc < _size) {
                if (data[nr][nc] == p) {
                    count++;
                    if (count == 5) return true;
                }
                else {
                    count = 0;
                }
            }
        }

        return false;
    }

public:
    void ShowCursor() {
        int x = X0 + 2 * column;
        int y = row + Y0;
        scr.SetColor(7);
        scr.SetCursorPos(x, y).Write('[');
        scr.SetCursorPos(x + 2, y).Write(']');
    }
    void Move(int r, int c) {
        int x = X0 + 2 * column;
        int y = row + Y0;
        scr.SetCursorPos(x, y).Write(char(space));
        scr.SetCursorPos(x + 2, y).Write(char(space));

        change(row, r);
        change(column, c);

        ShowCursor();
    }
    void DrawPiece(int p, int r, int c) {
        int x = X0 + c * 2 + 1;
        int y = Y0 + r;

        scr.SetColor(p == 'x' ? 10 : 12)
            .SetCursorPos(x, y)
            .Write(char(p));
    }
    void DrawPiece() {
        DrawPiece(player, row, column);
    }
    bool Put() {
        if (data[row][column]) {
            return false;
        }
        data[row][column] = player;
        DrawPiece();
        if (checkWin(row, column, player)) {
            if (player == 'x') scoreX++;
            else scoreO++;
            DisplayScore();
            DisplayEndGameMessage();
            ResetBoard();
        }
        else {
            SwitchPlayer();
        }
        return true;
    }
    void SwitchPlayer() {
        player = player == 'x' ? 'o' : 'x';
    }
    void DisplayScore() {
        scr.SetCursorPos(X0, Y0 + _size + 2);
        scr.SetColor(7).Write("Score - X: ").Write(scoreX).Write(" | O: ").Write(scoreO);
    }
    void DisplayEndGameMessage() {
        scr.SetCursorPos(X0, Y0 + _size + 3);
        scr.SetColor(14).Write("Player ").Write(player == 'x' ? 'X' : 'O').Write(" wins! Press 'R' to reset or 'E' to exit.");
    }
    void ResetBoard() {
        memset(data, 0, sizeof(data));
        draw_frame();
        row = column = _size / 2;
        ShowCursor();
    }
};

int main()
{
    scr.ShowCursor(false);
    draw_frame();
    Game game;

    game.Put();
    game.ShowCursor();

    int keys[] = { 32, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 'R', 'E' };
    while (true) {
        for (int i = 0; i < sizeof(keys) / sizeof(int); i++) {
            int v = GetAsyncKeyState(keys[i]);
            if (v & 1) { // key down
                switch (keys[i]) {
                case 32:
                    game.Put();
                    break;
                case VK_LEFT: game.Move(0, -1); break;
                case VK_RIGHT: game.Move(0, 1); break;
                case VK_UP: game.Move(-1, 0); break;
                case VK_DOWN: game.Move(1, 0); break;
                case 'R': game.ResetBoard(); break;
                case 'E': return 0;
                default:
                    break;
                }
            }
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
