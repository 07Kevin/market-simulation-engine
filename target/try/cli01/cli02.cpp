#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <string>

int main()
{
    using namespace ftxui;

    struct Task
    {
        std::string stringDescription;
        bool bDone = false;
    };

    std::vector<Task> vectorTasks;
    std::string stringNewTaskInput;

    auto screenInteractive = ScreenInteractive::TerminalOutput();

    auto inputOption = InputOption{};
    auto inputNewTask = Input(&stringNewTaskInput, "What needs to be done?", inputOption);

    auto buttonAddTask = Button("Add Task", [&] {
        if( !stringNewTaskInput.empty() )
        {
            vectorTasks.push_back({stringNewTaskInput, false});
            stringNewTaskInput.clear();
        }
    });

    auto containerTasks = Container::Vertical({});

    std::function<void()> functionRebuildTasks;

    functionRebuildTasks = [&] {
        containerTasks->DetachAllChildren();

        for( size_t uIndex = 0; uIndex < vectorTasks.size(); ++uIndex )
        {
            auto& taskCurrent = vectorTasks[uIndex];

            auto checkboxTask = Checkbox(taskCurrent.stringDescription, &taskCurrent.bDone);

            auto buttonDelete = Button("Delete", [&, uIndex] {
                vectorTasks.erase(vectorTasks.begin() + uIndex);
                functionRebuildTasks();
            }) | color(Color::Red);

            auto componentTaskRow = Container::Horizontal({
                checkboxTask,
                buttonDelete,
            });

            containerTasks->Add(componentTaskRow);
        }
    };

    functionRebuildTasks();

    auto rendererMain = Renderer(containerTasks, [&] {
        unsigned uPending = 0;
        unsigned uCompleted = 0;

        for( const auto& taskCurrent : vectorTasks )
        {
            if( taskCurrent.bDone )
                ++uCompleted;
            else
                ++uPending;
        }

        return vbox({
            text("My To-Do List") | bold | center | color(Color::BlueLight),
            separator(),
            hbox({
                text("Tasks: ") | bold,
                text(std::to_string(uPending) + " pending, " + 
                     std::to_string(uCompleted) + " done") | color(Color::Green),
            }) | center,
            separator(),
            hbox({
                inputNewTask->Render() | flex | border,
                buttonAddTask->Render(),
            }) | center,
            separator(),
            containerTasks->Render() | frame | flex | border,
            separator(),
            text("↑↓ Navigate • Enter/Space toggle • q to quit") | dim | center,
        }) | border | center;
    });

    auto componentMain = CatchEvent(rendererMain, [&](Event event) {
        if( event == Event::Character('q') || event == Event::Escape )
        {
            screenInteractive.ExitLoopClosure()();
            return true;
        }

        if( event == Event::Return && !stringNewTaskInput.empty() )
        {
            vectorTasks.push_back({stringNewTaskInput, false});
            stringNewTaskInput.clear();
            functionRebuildTasks();
            return true;
        }

        return false;
    });

    screenInteractive.Loop(componentMain);

    return 0;
}