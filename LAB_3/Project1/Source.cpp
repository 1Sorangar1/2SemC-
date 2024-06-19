#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<locale>
#include<sstream>
#include<iterator>
#include<Windows.h>
#include "Menu.h"
#include "Resource.h"

MainMenu primaryMenu;

BOOL CALLBACK dialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG:
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            EndDialog(hwndDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}

void renderDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    primaryMenu.Render();
    glutSwapBuffers();
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (primaryMenu.HandleLeftClick(x, y)) {
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), NULL, dialogProc);
        }
        renderDisplay();
    }
}

int main(int argc, char* argv[]) {
    std::locale::global(std::locale(""));

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];

    primaryMenu.LoadMenu(fileName);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    glutCreateWindow("Menu");
    glClearColor(0.0, 0.3, 0.4, 0.2);
    gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);
    glutMouseFunc(mouseCallback);
    glutDisplayFunc(renderDisplay);
    glutMainLoop();

    return 0;
}
