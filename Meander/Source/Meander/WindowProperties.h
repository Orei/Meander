#pragma once

// enum class WindowDisplayMode
// {
//     Window,
//     Borderless,
//     Exclusive
// };

struct WindowProperties
{
    const char* Title;
    uint32_t Width;
    uint32_t Height;
    bool VerticalSync;
    // bool Maximized;
    // WindowDisplayMode DisplayMode;

    WindowProperties(
        const char* title = "Meander", 
        uint32_t width = 1280,
        uint32_t height = 720,
        bool verticalSync = true)
        // bool maximized = true,
        // const WindowDisplayMode& displayMode = WindowDisplayMode::Window)
        : Title(title),
        Width(width),
        Height(height),
        VerticalSync(verticalSync)
        // Maximized(maximized),
        // DisplayMode(displayMode)
    {
    }
};
