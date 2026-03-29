#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>

int main() {
    using namespace ftxui;

    // Create a simple component
    auto button = Button("Click Me!", [] { std::cout << "Button clicked!" << std::endl; });
    
    // Create a renderer for the component
    auto renderer = Renderer(button, [&] {
        return vbox({
            text("Simple CLI01 Application") | bold | center,
            separator(),
            button->Render() | center,
        }) | border | center;
    });

    // Create the screen and run the application
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);

    return 0;
}