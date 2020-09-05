#include "..\..\Anemone\utilities\Pathfinding.h"

namespace ae
{
    namespace Pathfinding
    {
        // BoolGrid

        BoolGrid::BoolGrid(unsigned int _width, unsigned int _height, bool default_value)
        {
            width = _width;
            height = _height;
            grid = new bool* [height];
            for (int y = 0; y < height; ++y)
            {
                grid[y] = new bool[width];
                for (int x = 0; x < width; ++x)
                {
                    grid[y][x] = default_value;
                }
            }
        }

        void BoolGrid::set(unsigned int x, unsigned int y, bool value)
        {
            if (isValid(x, (height - 1) - y))
            {
                std::lock_guard<std::mutex> guard(m);
                grid[(height - 1) - y][x] = value;
            }
        }

        const bool BoolGrid::check(unsigned int x, unsigned int y) const
        {
            return grid[y][x];
        }

        const bool BoolGrid::isValid(unsigned int x, unsigned int y) const
        {
            return (x >= 0) && (x < width) && (y >= 0) && (y < height);
        }

        BoolGrid::BoolGrid(const BoolGrid& copy)
        {
            width = copy.width;
            height = copy.height;
            grid = new bool* [height];
            for (int y = 0; y < height; ++y)
            {
                grid[y] = new bool[width];
                for (int x = 0; x < width; ++x)
                {
                    grid[y][x] = copy.grid[y][x];
                }
            }
        }

        BoolGrid::~BoolGrid()
        {
            for (int y = 0; y < height; ++y)
            {
                delete[] grid[y];
            }
            delete[] grid;
        }

        void tracePath(cell** cellDetails, const vec2& dest, Path& result, unsigned int height)
        {
            int row = (float)dest.y;
            int col = (float)dest.x;

            cell& c = cellDetails[row][col];

            while (!(c.parent_i == col && c.parent_j == row))
            {
                result.push_front({ (float)col, (float)(height - row) });
                row = c.parent_j;
                col = c.parent_i;
                c = cellDetails[c.parent_j][c.parent_i];
            }

            result.push_front({ (float)col, (float)(height - row) });
        }

        bool search(const BoolGrid& grid, const vec2& src, const vec2& dest, Path& final_path, bool include_diagnols)
        {
            double gNew, hNew, fNew;
            int x, y, i, i2, j, j2;
            std::vector<vec3> openList;

            vec2 modSrc = { src.x, (grid.getHeight() - 1) - src.y };
            vec2 modDest = { dest.x, (grid.getHeight() - 1) - dest.y };

            i = modSrc.x;
            j = modSrc.y;

            bool** closedList = new bool* [grid.getHeight()];
            cell** cellDetails = new cell * [grid.getHeight()];
            for (int y = 0; y < grid.getHeight(); ++y)
            {
                closedList[y] = new bool[grid.getWidth()]();
                cellDetails[y] = new cell[grid.getWidth()]();
            }

            cellDetails[j][i].set(0.0f, 0.0f, 0.0f, i, j);
            openList.push_back({ 0.0f, (float)i, (float)j });

            bool success = false;
            bool run = true;

            if (grid.isValid(modSrc.x, modSrc.y) == false || grid.isValid(modDest.x, modDest.y) == false)
            {
                printf("Invalid beginning or end tiles.\n");
                success = false;
                run = false;
            }

            if (grid.check(modSrc.x, modSrc.y) == false || grid.check(modDest.x, modDest.y) == false)
            {
                printf("Source or the Destination is blocked.\n");
                success = false;
                run = false;
            }

            if (modSrc == modDest)
            {
                printf("Already at the Destination.\n");
                success = false;
                run = false;
            }

            while (!openList.empty() && (success == false) && run)
            {
                i = openList[0].y;
                j = openList[0].z;
                closedList[j][i] = true;

                openList.erase(openList.begin());

                for (int t = 0; t < (include_diagnols ? 8 : 4); ++t)
                {
                    x = (int)offsets[t][0];
                    y = (int)offsets[t][1];
                    i2 = i + x;
                    j2 = j + y;
                    cell& c = cellDetails[j2][i2];

                    if (grid.isValid(i2, j2) == true)
                    {
                        if (t >= 4) { if (grid.isValid(i2, j) || grid.isValid(i, j2)) { continue; } }

                        if (modDest.x == i2 && modDest.y == j2)
                        {
                            c.parent_i = i;
                            c.parent_j = j;
                            tracePath(cellDetails, modDest, final_path, grid.getHeight() - 1);
                            success = true;
                        }
                        else if (closedList[j2][i2] == false && grid.check(i2, j2) == true)
                        {
                            gNew = cellDetails[j][i].g + offsets[t][2];
                            hNew = ((double)sqrt((j2 - modDest.x) * (j2 - modDest.x) + (i2 - modDest.y) * (i2 - modDest.y)));
                            fNew = gNew + hNew;

                            if (c.f == FLT_MAX || c.f > fNew)
                            {
                                openList.push_back({ (float)fNew, (float)(i2), (float)(j2) });
                                c.set(fNew, gNew, hNew, i, j);
                            }
                        }
                    }
                }
            }

            for (int y = 0; y < grid.getHeight(); ++y)
            {
                delete[] closedList[y];
                delete[] cellDetails[y];
            }

            delete[] closedList;
            delete[] cellDetails;

            return success;
        }
    };
};