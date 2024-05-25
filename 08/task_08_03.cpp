#include <iostream>
#include <vector>
#include <string>

#define SCREEN_MAX_WIDTH 80
#define SCREEN_MAX_HEIGHT 50

using namespace std;

class Window {
private:
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;

public:
    Window() {
        this->x = 0;
        this->y = 0;
        this->width = 0;
        this->height = 0;
    }

    Window(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    void move(pair<uint32_t, uint32_t> delta) {
        this->x += delta.first;
        this->y += delta.second;
    }

    void resize(pair<uint32_t, uint32_t> newSize) {
        this->width = newSize.first;
        this->height = newSize.second;
    }

    pair<uint32_t, uint32_t> getPosition() const {
        return {this->x, this->y};
    }

    pair<uint32_t, uint32_t> getSize() const {
        return {this->width, this->height};
    }
};

class Screen {
private:
    vector<vector<uint32_t>> pixels;
    uint32_t screenWidth;
    uint32_t screenHeight;

public:
    Screen(uint32_t width, uint32_t height) {
        this->screenWidth = width;
        this->screenHeight = height;

        this->pixels = vector<vector<uint32_t>>(height,
                                                vector<uint32_t>(width, 0));
    }

    void display() {
        for (vector<uint32_t> row : this->pixels) {
            for (uint32_t pixel : row)
                cout << pixel;

            cout << endl;
        }
    }

    bool isInside(const Window *window, uint32_t x, uint32_t y) {
        return x >= window->getPosition().first && 
               x < window->getPosition().first + window->getSize().first &&
               y >= window->getPosition().second &&
               y < window->getPosition().second + window->getSize().second;
    }

    void update(const Window *window) {
        for (uint32_t y = 0; y < this->screenHeight; ++y) {
            for (uint32_t x = 0; x < this->screenWidth; ++x) {
                if (isInside(window, x, y))
                    this->pixels[y][x] = 1;
                else
                    this->pixels[y][x] = 0;
            }
        }
    }
};

class WindowManager {
private:
    Window *window;
    Screen *screen;

public:
    WindowManager(uint32_t defaultX, uint32_t defaultY, uint32_t defaultWidth,
                  uint32_t defaultHeight) {
        this->window = new Window (defaultX, defaultY, defaultWidth,
                                   defaultHeight);
        this->screen = new Screen (SCREEN_MAX_WIDTH, SCREEN_MAX_HEIGHT);

        this->screen->update(this->window);
    }

    ~WindowManager() {
        delete this->window;
        delete this->screen;
    }

    void processCommand(string command) {
        uint32_t dx;
        uint32_t dy;
        uint32_t w;
        uint32_t h;

        if (command == "move") {
            cout << "X offset: ";
            cin >> dx;
            cout << "Y offset: ";
            cin >> dy;

            this->window->move({dx, dy});

            cin.clear();
            cin.ignore();

        } else if (command == "resize") {
            cout << "New width: ";
            cin >> w;
            cout << "New height: ";
            cin >> h;

            this->window->resize({w, h});

            cin.clear();
            cin.ignore();

        } else if (command == "display") {
            this->screen->display();

        } else {
            cout << "Unknown command." << endl;
        }

        this->screen->update(this->window);
    }
};

int main() {
    string command;
    WindowManager manager(13, 13, 13, 13);

    while (true) {
        command.clear();

        cout << "Enter command: ";
        getline(cin, command);

        if (command == "close") {
            break;
        }

        cin.clear();

        manager.processCommand(command);
    }

    return 0;
}