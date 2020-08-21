#include "..\..\Anemone\utilities\Noise.h"

namespace ae
{

    void Noise::set(unsigned int _width, unsigned int _height)
    {
        if (noise != nullptr)
        {
            for (int i = 0; i < height; i++)
            {
                delete[] noise[i];
            }

            delete[] noise;
            noise = nullptr;
        }

        width = _width;
        height = _height;
        noise = new double* [height];
        for (int i = 0; i < height; i++)
        {
            noise[i] = new double[width];
            for (int j = 0; j < width; j++)
            {
                noise[i][j] = (rand() % 32768) / 32768.0;
            }
        }
    }

    void Noise::refresh()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                noise[i][j] = (rand() % 32768) / 32768.0;
            }
        }
    }

    double Noise::smoothNoise(double x, double y) const
    {
        //get fractional part of x and y
        double fractX = x - int(x);
        double fractY = y - int(y);

        //wrap around
        int x1 = (int(x) + width) % width;
        int y1 = (int(y) + height) % height;

        //neighbor values
        int x2 = (x1 + width - 1) % width;
        int y2 = (y1 + height - 1) % height;

        //smooth the noise with bilinear interpolation
        double value = 0.0;
        value += fractX * fractY * noise[y1][x1];
        value += (1 - fractX) * fractY * noise[y1][x2];
        value += fractX * (1 - fractY) * noise[y2][x1];
        value += (1 - fractX) * (1 - fractY) * noise[y2][x2];

        return value;
    }

    double Noise::turbulence(double x, double y, double size) const
    {
        double value = 0.0;
        double initialSize = size;
        while (size >= 1)
        {
            value += smoothNoise(x / size, y / size) * size;
            size /= 2.0;
        }

        return (128.0 * value / initialSize);
    }

    double** Noise::genTurbulenceTable()
    {
        double** table = new double*[height];
        for (int y = 0; y < height; y++)
        {
            table[y] = new double[width];
            for (int x = 0; x < width; x++)
            {
                table[y][x] = turbulence(x, y, 128.0f);
            }
        }

        return table;
    }

    Noise::~Noise()
    {
        for (int i = 0; i < height; i++)
        {
            delete[] noise[i];
        }

        delete[] noise;
        noise = nullptr;
    }

};