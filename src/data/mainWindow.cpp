#include "mainWindow.hpp"

#include "../define.hpp"

// Main window class
MainWindow::MainWindow(unsigned fieldWidth)
: Window(CELL_SIDE * fieldWidth + (fieldWidth - 1) * SEPARATOR,
    CELL_SIDE * fieldWidth + (fieldWidth - 1) * SEPARATOR) {}
