#include "..\Anemone\Manager.h"

namespace ae
{
    /*
    std::vector<ae::sptr<Base>> Manager::bases;
    sptr<ae::Window> Manager::window = nullptr;

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
    */

    
    ApplicationManager<DefaultManager>* Manager = ApplicationManager<DefaultManager>::getInstance();

    void DefaultManager::update(double dt)
    {
        for (auto& b : bases)
        {
            b->update(dt);
        }
    }

    void DefaultManager::render()
    {
        for (auto& b : bases)
        {
            b->render();
        }
    }

    void DefaultManager::add(ae::sptr<Base> base)
    {
        toss(std::find(bases.begin(), bases.end(), base) != bases.end(), "This class has already been added to the Manager.");
        bases.push_back(base);
    }

    void DefaultManager::remove(ae::sptr<Base> base)
    {
        auto itr = std::find(bases.begin(), bases.end(), base);
        if (itr != bases.end()) {
            bases.erase(itr);
        }
    }

    void create(const std::string& _title, unsigned int _width, unsigned int _height, unsigned int hints)
    {
        Manager->create(_title, _width, _height, hints);
    }

    void start()
    {
        Manager->start();
    }

    void addState(unsigned int id, State* state, bool set_current, bool initialize)
    {
        Manager->addState(id, state, set_current, initialize);
    }

    void setState(unsigned int id, bool initialize)
    {
        Manager->setState(id, initialize);
    }

};