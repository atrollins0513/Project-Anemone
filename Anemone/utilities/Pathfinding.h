#pragma once

#include <iostream>
#include <vector>

#include "..\Math.h"

namespace ae
{

    class Pathfinding
    {
    private:

        struct cell
        {

            double f;

            double g;

            double h;

            int parent_i;

            int parent_j;

            cell() : f(FLT_MAX), g(FLT_MAX), h(FLT_MAX), parent_i(-1), parent_j(-1)
            {

            }

            void set(double _f, double _g, double _h, int _parent_i, int _parent_j)
            {
                f = _f;
                g = _g;
                h = _h;
                parent_i = _parent_i;
                parent_j = _parent_j;
            }

        };

    public:

        Pathfinding(int row, int col);

        bool search(bool** grid, const vec2& src, const vec2& dest, std::vector<vec2>& final_path, bool include_diagnols = true);

    private:

        bool isValid(int row, int col) const;

        bool isUnBlocked(bool** grid, int row, int col) const;

        bool isDestination(int row, int col, const vec2& dest) const;

        double calculateHValue(int row, int col, const vec2& dest) const;

        void tracePath(cell** cellDetails, const vec2& dest, std::vector<vec2>& result);

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

        bool** closedList;
        
        cell** cellDetails;
        
        int rowNumber;

        int colNumber;

    };

};