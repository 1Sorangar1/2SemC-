#pragma once
#include <GL/glut.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MARGIN_WIDTH 50
#define MARGIN_HEIGHT 20
#define TEXT_HEIGHT 50
#define SUBMENU_MARGIN_WIDTH 70
#define SUBMENU_MARGIN_HEIGHT 10
#define SUBMENU_TEXT_HEIGHT 30

struct MenuItem {
    float posX;
    float posY; 
    std::string label;
    std::vector<MenuItem> subMenuItems;
    bool isSubMenuOpen = false;
};

class MainMenu {
    std::vector<MenuItem> menuItems;
public:
    void AddMenuItem(MenuItem newItem);
    void LoadMenu(const std::string& fileName);
    void PrintMenu();
    void ExpandSubMenu(int index);
    void CollapseSubMenu(int index);

    void Render();
    bool HandleLeftClick(int x, int y);
};
