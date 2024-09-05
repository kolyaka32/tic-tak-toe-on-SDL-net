


// Names of all images with related numbers
enum IMG_names{
    // Base part
    // Graphic interface sprites
    IMG_GUI_PAUSE_BUTTON,
    IMG_GUI_QUIT_BUTTON,
    IMG_GUI_SLIDER_BUTTON,
    IMG_GUI_SLIDER_LINE,
    IMG_GUI_TYPE_BOX,

    // Base flags in settings
    IMG_GUI_FLAG_USA,
    IMG_GUI_FLAG_RUS,
    IMG_GUI_FLAG_GER,
    IMG_GUI_FLAG_BEL,

    // Main game part
    // Green (current player) figures
    IMG_GREEN_CROSS,
    IMG_GREEN_CIRCLE,

    // Red (opponent player) figures
    IMG_RED_CROSS,
    IMG_RED_CIRCLE,

    // Empty cell
    IMG_CELL,

    // Global counter of all textures
    IMG_count,
};


// File names of the corresponding textures
const char* texturesFilesNames[IMG_count] = {
    // GUI
    "GUI/esc_button.png",
    "GUI/quit_button.png",
    "GUI/slider_button.png",
    "GUI/slider_line.png",
    "GUI/type_box.png",
    // Flags
    "GUI/Flag_USA.png",
    "GUI/Flag_RUS.png",
    "GUI/Flag_GER.png",
    "GUI/Flag_BEL.png",
    // Game part
    "game/green_circle.png",
    "game/green_cross.png",
    "game/red_circle.png",
    "game/red_cross.png",
    "game/cell.png",
};
