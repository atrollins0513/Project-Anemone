#pragma once

#include <random>

namespace ae
{
    class Noise
    {
    public:

        Noise() : width(0), height(0), noise(nullptr) { }

        Noise(unsigned int _width, unsigned int _height) : Noise()
        {
            set(_width, _height);
        }

        void set(unsigned int _width, unsigned int _height);

        void refresh();

        double smoothNoise(double x, double y) const;

        double turbulence(double x, double y, double size) const;

        double** genTurbulenceTable();

        ~Noise();

    private:

        unsigned int width;

        unsigned int height;

        double** noise;

    };

};