#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <mutex>

#include "..\Math.h"

namespace ae
{
    namespace Pathfinding
    {
        using Path = std::deque<vec2>;

        class BoolGrid
        {
        public:

            BoolGrid() : width(0), height(0), grid(nullptr) { }

            BoolGrid(unsigned int _width, unsigned int _height, bool default_value = true);

            void set(unsigned int x, unsigned int y, bool value);

            const bool check(unsigned int x, unsigned int y) const;

            const bool isValid(unsigned int x, unsigned int y) const;

            unsigned int getWidth() const { return width; }

            unsigned int getHeight() const { return height; }

            BoolGrid(const BoolGrid& copy);

            ~BoolGrid();

        private:

            unsigned int width;

            unsigned int height;

            bool** grid;

            std::mutex m;

        };

        const double offsets[8][3] = {
                    {-1.0, 0.0, 1.0}, // North
                    {1.0, 0.0, 1.0}, // South
                    {0.0, 1.0, 1.0}, // East
                    {0.0, -1.0, 1.0}, // West
                    {-1.0, 1.0, 1.414}, // North-East
                    {-1.0, -1.0, 1.414}, // North-West
                    {1.0, 1.0, 1.414}, // South-East
                    {1.0, -1.0, 1.414}, // South-West
        };

        struct cell
        {
            double f, g, h;
            int parent_i, parent_j;

            cell() : f(FLT_MAX), g(FLT_MAX), h(FLT_MAX), parent_i(-1), parent_j(-1) { }

            void set(double _f, double _g, double _h, int _parent_i, int _parent_j)
            {
                f = _f;
                g = _g;
                h = _h;
                parent_i = _parent_i;
                parent_j = _parent_j;
            }
        };

        // Functions

        extern void tracePath(cell** cellDetails, const vec2& dest, Path& result, unsigned int height);

        extern bool search(const BoolGrid& grid, const vec2& src, const vec2& dest, Path& final_path, bool include_diagnols);

    };
};