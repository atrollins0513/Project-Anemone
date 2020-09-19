#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "Error.h"
#include "Utilities.h"
#include "Base.h"
#include "Window.h"

namespace ae
{
    /*
    struct Manager
    {
        friend class Window;
        static sptr<ae::Window> window;

        static void add(ae::sptr<Base> base);
        static void remove(ae::sptr<Base> base);
        static void Initiate(const std::string& title, unsigned int width, unsigned int height);
    protected:
        static void update(double dt);
        static void render();
    private:
        static std::vector<ae::sptr<Base>> bases;
    };
    */

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

    struct DefaultManager : public Window
    {
        DefaultManager() : Window() {}

        void update(double dt) override;
        
        void render() override;
        
        void add(ae::sptr<Base> base);
        
        void remove(ae::sptr<Base> base);

    private:
        std::vector<ae::sptr<Base>> bases;
    };

    ApplicationManager<DefaultManager>* ApplicationManager<DefaultManager>::instance = nullptr;

    extern ApplicationManager<DefaultManager>* Manager;

    extern void create(const std::string& _title, unsigned int _width, unsigned int _height, unsigned int hints = 0);
    extern void start();
    extern void addState(unsigned int id, State* state, bool set_current = false, bool initialize = false);
    extern void setState(unsigned int id, bool initialize = false);
};