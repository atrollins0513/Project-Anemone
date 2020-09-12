#include "..\Anemone\Manager.h"

namespace ae
{
    std::vector<ae::sptr<Base>> Manager::bases;
    sptr<Window> Manager::window = nullptr;

    void Manager::add(ae::sptr<Base> base)
    {
        toss(std::find(bases.begin(), bases.end(), base) != bases.end(), "This class has already been added to the Manager.");
        bases.push_back(base);
    }

    void Manager::remove(ae::sptr<Base> base)
    {
        auto itr = std::find(bases.begin(), bases.end(), base);
        if (itr != bases.end()) {
            bases.erase(itr);
        }
    }

    void Manager::Initiate(const std::string& title, unsigned int width, unsigned int height)
    {
        toss(window != nullptr, "Window has already been initialized.");
        window = makes<Window>(title, width, height);
    }

    void Manager::update(double dt)
    {
        for (auto& b : bases)
        {
            b->update(dt);
        }
    }

    void Manager::render()
    {
        for (auto& b : bases)
        {
            b->render();
        }
    }

    /*
    ApplicationManager<DefaultManager>* Manager = ApplicationManager<DefaultManager>::getInstance();

    DefaultManager::DefaultManager() : Window()
    {
        textManager = new TextManager();
        eventQueue = new EventQueue();
        taskManager = new TaskManager(4);
    }

    void DefaultManager::initialization()
    {
        textManager->init();
    }

    void DefaultManager::update(double dt)
    {
        eventQueue->update(dt);
    }

    void DefaultManager::render()
    {
        textManager->render();
    }

    // Text Manager Functions

    void DefaultManager::updateText(TextRef text)
    {
        textManager->updateText(text);
    }

    void DefaultManager::updateText(std::initializer_list<TextRef> text_list)
    {
        textManager->updateText(text_list);
    }

    TextRef DefaultManager::addText(const std::string& _str, const vec2& _pos, const vec4& _color, float _scale, bool _visible, const std::string& font_name, const TextOffset offset)
    {
        return textManager->addText(_str, _pos, _color, _scale, _visible, font_name, offset);
    }

    void DefaultManager::removeText(TextRef text)
    {
        textManager->removeText(text);
    }

    void DefaultManager::addFont(const std::string& name, const std::string& font_file, const std::string& font_texture)
    {
        textManager->addFont(name, font_file, font_texture);
    }

    bool DefaultManager::textExists(TextRef text)
    {
        return textManager->textExists(text);
    }

    unsigned int DefaultManager::stringWidth(const std::string& str, float scale, const std::string& font_name)
    {
        return textManager->stringWidth(str, scale, font_name);
    }

    unsigned int DefaultManager::stringHeight(const std::string& str, float scale, const std::string& font_name)
    {
        return textManager->stringHeight(str, scale, font_name);
    }

    // Event Queue Functions

    void DefaultManager::addEvent(double delay, double duration, bool repeat, std::function<bool()> callback)
    {
        eventQueue->addEvent(delay, duration, repeat, callback);
    }

    // Task Manager Functions

    void DefaultManager::addTask(FuncPtr func)
    {
        taskManager->addTask(func);
    }
    */
};