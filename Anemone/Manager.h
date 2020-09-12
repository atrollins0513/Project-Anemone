#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

//#include "Font.h"
#include "Utilities.h"
#include "Base.h"
#include "Window.h"

namespace ae
{
    struct Manager
    {
        friend class Window;
        static sptr<Window> window;

        static void add(ae::sptr<Base> base);
        static void remove(ae::sptr<Base> base);
        static void Initiate(const std::string& title, unsigned int width, unsigned int height);
    protected:
        static void update(double dt);
        static void render();
    private:
        static std::vector<ae::sptr<Base>> bases;
    };

    /*
    template<typename T>
    class ApplicationManager : public T
    {
    public:

        ApplicationManager() : T() { }

        static ApplicationManager<T>* getInstance()
        {
            if (!instance) { instance = new ApplicationManager(); }
            return instance;
        }

        ApplicationManager(const ApplicationManager& other) = delete;

        void operator=(const ApplicationManager&) = delete;

    private:

        static ApplicationManager<T>* instance;

    };

    class Window;

    struct DefaultManager : public Window
    {
        DefaultManager();

        void initialization() override;

        void update(double dt) override;

        void render() override;

        // Text Manager Functions

        void updateText(TextRef text);

        void updateText(std::initializer_list<TextRef> text_list);

        TextRef addText(const std::string& _str, const vec2& _pos, const vec4& _color, float _scale, bool _visible, const std::string& font_name, const TextOffset offset = TextOffset::center);

        void removeText(TextRef text);

        void addFont(const std::string& name, const std::string& font_file, const std::string& font_texture);

        bool textExists(TextRef text);

        unsigned int stringWidth(const std::string& str, float scale, const std::string& font_name);

        unsigned int stringHeight(const std::string& str, float scale, const std::string& font_name);

        // Event Queue Functions

        void addEvent(double delay, double duration, bool repeat, std::function<bool()> callback);

        // Task Manager Functions

        void addTask(FuncPtr func);

        TextManager* getTextManager()
        {
            return textManager;
        }

        EventQueue* getEventQueue()
        {
            return eventQueue;
        }

        TaskManager* getTaskManager()
        {
            return taskManager;
        }

    private:

        TextManager* textManager;

        EventQueue* eventQueue;

        TaskManager* taskManager;

    };

    ApplicationManager<DefaultManager>* ApplicationManager<DefaultManager>::instance = nullptr;

    extern ApplicationManager<DefaultManager>* Manager;// = ApplicationManager<DefaultManager>::getInstance();
    */

};