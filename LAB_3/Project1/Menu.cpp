#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <locale>
#include <sstream>
#include <iterator>
#include <Windows.h>
#include "Menu.h"

//MAIN MENU

void MainMenu::AddMenuItem(MenuItem newItem) {
    menuItems.push_back(newItem);
}

void MainMenu::LoadMenu(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return;
    }
    std::string line;
    MenuItem currentItem;
    while (std::getline(file, line)) {
        if (line.empty()) {
            menuItems.push_back(currentItem);
            MenuItem currentItem;
        }
        else {
            currentItem.subMenuItems.clear();
            if (line.find("SUB_MENU") != std::string::npos) {
                std::getline(file, line);
                while (line.find("END_SUB_MENU") == std::string::npos) {
                    MenuItem subMenuItem;
                    subMenuItem.label = line;
                    currentItem.subMenuItems.push_back(subMenuItem);
                    std::getline(file, line);
                }
            }
            else {
                currentItem.label = line;
            }
        }
    }
    menuItems.push_back(currentItem);

    file.close();

    for (int i = 0; i < (int)menuItems.size(); i++) {
        menuItems[i].posX = MARGIN_WIDTH;
        menuItems[i].posY = MARGIN_HEIGHT * (1 + i) + TEXT_HEIGHT * i;
        if (!menuItems[i].subMenuItems.empty()) {
            for (int j = 0; j < (int)menuItems[i].subMenuItems.size(); j++) {
                menuItems[i].subMenuItems[j].posX = SUBMENU_MARGIN_WIDTH;
                menuItems[i].subMenuItems[j].posY = menuItems[i].posY + SUBMENU_MARGIN_HEIGHT * (1 + j) + TEXT_HEIGHT + j * SUBMENU_TEXT_HEIGHT;
            }
        }
    }
}

//SUBMENU

void PrintSubMenuItems(const std::vector<MenuItem>& menu) {
    for (const auto& item : menu) {
        std::cout << " - " << item.label << std::endl;
    }
}

void MainMenu::ExpandSubMenu(int index) {
    int count = menuItems[index].subMenuItems.size();
    menuItems[index].isSubMenuOpen = true;
    int height = count * SUBMENU_TEXT_HEIGHT + (count + 1) * SUBMENU_MARGIN_HEIGHT - MARGIN_HEIGHT;
    for (int j = index + 1; j < (int)menuItems.size(); j++) {
        menuItems[j].posY += height;
        if (!menuItems[j].subMenuItems.empty()) {
            for (auto& k : menuItems[j].subMenuItems) {
                k.posY += height;
            }
        }
    }
}

void MainMenu::CollapseSubMenu(int index) {
    int count = menuItems[index].subMenuItems.size();
    menuItems[index].isSubMenuOpen = false;
    int height = -count * SUBMENU_TEXT_HEIGHT - (count + 1) * SUBMENU_MARGIN_HEIGHT + MARGIN_HEIGHT;
    for (int j = index + 1; j < (int)menuItems.size(); j++) {
        menuItems[j].posY += height;
        if (!menuItems[j].subMenuItems.empty()) {
            for (auto& k : menuItems[j].subMenuItems) {
                k.posY += height;
            }
        }
    }
}


void DrawSubMenuItems(const std::vector<MenuItem>& menu) {
    for (const auto& item : menu) {
        glColor3f(1, 0, 0);
        glRasterPos2i(item.posX + 1.12f * SUBMENU_MARGIN_WIDTH, item.posY + 0.6f * SUBMENU_TEXT_HEIGHT);
        for (const auto& c : item.label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
    }
}


void DrawArrowUp(float x, float y) {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 40, y + 10);
    glVertex2f(x + 40, y + 40);
    glVertex2f(x + 10, y + 40);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 25, y + 20);
    glVertex2f(x + 15, y + 30);
    glVertex2f(x + 35, y + 30);
    glEnd();
}

void DrawArrowDown(float x, float y) {
    glColor3f(0.1, 0.8, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 40, y + 10);
    glVertex2f(x + 40, y + 40);
    glVertex2f(x + 10, y + 40);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 15, y + 20);
    glVertex2f(x + 35, y + 20);
    glVertex2f(x + 25, y + 30);
    glEnd();
}


void DrawMenuItem(const MenuItem& item, float width) {
    glColor3f(0.1, 0.1, 0.8);
    glBegin(GL_QUADS);
    glVertex2f(item.posX, item.posY);
    glVertex2f(item.posX + width, item.posY);
    glVertex2f(item.posX + width, item.posY + TEXT_HEIGHT);
    glVertex2f(item.posX, item.posY + TEXT_HEIGHT);
    glEnd();
    if (!item.subMenuItems.empty()) {
        if (!item.isSubMenuOpen) {
            DrawArrowDown(item.posX, item.posY);
        }
        else {
            DrawArrowUp(item.posX, item.posY);
            DrawSubMenuItems(item.subMenuItems);
        }
    }
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(item.posX + 1.12f * MARGIN_WIDTH, item.posY + 0.6f * TEXT_HEIGHT);
    for (const auto& c : item.label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
}

void MainMenu::Render() {
    float maxWidth = 0;
    for (const auto& item : menuItems) {
        int length = glutBitmapLength(GLUT_BITMAP_HELVETICA_10, (const unsigned char*)item.label.c_str());
        if (length > maxWidth) {
            maxWidth = length;
        }
    }
    maxWidth *= 3;

    for (const auto& item : menuItems) {
        DrawMenuItem(item, maxWidth);
    }
}

//Mouse operations

bool MainMenu::HandleLeftClick(int x, int y) {
    for (int i = 0; i < (int)menuItems.size(); i++) {
        if (x >= menuItems[i].posX + 10 && x <= menuItems[i].posX + 40 && y >= menuItems[i].posY + 10 && y <= menuItems[i].posY + 40 && !menuItems[i].subMenuItems.empty()) {
            if (!menuItems[i].isSubMenuOpen) {
                ExpandSubMenu(i);
                return true;
            }
            else {
                CollapseSubMenu(i);
            }
        }
    }
    return false;
}
