#include "..\..\Anemone\utilities\Pathfinding.h"

namespace ae
{
    Pathfinding::Pathfinding(int row, int col)
    {
        rowNumber = row;
        colNumber = col;
        closedList = new bool* [row];
        cellDetails = new cell * [row];

        for (int y = 0; y < row; y++)
        {
            closedList[y] = new bool[col];
            cellDetails[y] = new cell[col];
            for (int x = 0; x < col; x++)
            {
                closedList[y][x] = false;
                cellDetails[y][x] = cell();
            }
        }
    }

    bool Pathfinding::isValid(int row, int col) const
    {
        return (row >= 0) && (row < rowNumber) && (col >= 0) && (col < colNumber);
    }

    bool Pathfinding::isUnBlocked(bool** grid, int row, int col) const
    {
        return grid[row][col];
    }

    bool Pathfinding::isDestination(int row, int col, const vec2& dest) const
    {
        return (dest.x == row && dest.y == col);
    }

    double Pathfinding::calculateHValue(int row, int col, const vec2& dest) const
    {
        return ((double)sqrt((row - dest.x) * (row - dest.x) + (col - dest.y) * (col - dest.y)));
    }

    void Pathfinding::tracePath(cell** cellDetails, const vec2& dest, std::vector<vec2>& result)
    {
        int row = dest.x;
        int col = dest.y;

        std::vector<vec2> path;

        while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
        {
            path.push_back({ (float)col, (float)row });
            int temp_row = cellDetails[row][col].parent_i;
            int temp_col = cellDetails[row][col].parent_j;
            row = temp_row;
            col = temp_col;
        }

        path.push_back({ (float)col, (float)row });
        result.insert(result.end(), path.rbegin(), path.rend());
    }

    bool Pathfinding::search(bool** grid, const vec2& src, const vec2& dest, std::vector<vec2>& final_path, bool include_diagnols)
    {
        ae::vec2 flippedSrc = ae::vec2(src.y, src.x);
        ae::vec2 flippedDest = ae::vec2(dest.y, dest.x);

        if (isValid(flippedSrc.x, flippedSrc.y) == false || isValid(flippedDest.x, flippedDest.y) == false)
        {
            printf("Invalid beginning or end tiles.\n");
            return false;
        }

        if (isUnBlocked(grid, flippedSrc.x, flippedSrc.y) == false || isUnBlocked(grid, flippedDest.x, flippedDest.y) == false)
        {
            printf("Source or the destination is blocked.\n");
            return false;
        }

        if (isDestination(flippedSrc.x, flippedSrc.y, flippedDest) == true)
        {
            printf("Already at the destination.\n");
            return false;
        }

        int i = flippedSrc.x;
        int j = flippedSrc.y;

        cellDetails[i][j].set(0.0f, 0.0f, 0.0f, i, j);

        std::vector<vec3> openList;

        openList.push_back({ 0.0f, (float)i, (float)j });

        double gNew, hNew, fNew;
        int x, y;

        while (!openList.empty())
        {
            i = openList[0].y;
            j = openList[0].z;
            closedList[i][j] = true;

            openList.erase(openList.begin());

            for (int t = 0; t < (include_diagnols ? 8 : 4); ++t)
            {
                x = offsets[t][0];
                y = offsets[t][1];
                cell& c = cellDetails[i + x][j + y];

                if (isValid(i + x, j + y) == true)
                {
                    if (t >= 4)
                    {
                        if (isValid(i + x, j) || isValid(i, j + y))
                        {
                            continue;
                        }
                    }

                    if (isDestination(i + x, j + y, flippedDest) == true)
                    {
                        c.parent_i = i;
                        c.parent_j = j;
                        tracePath(cellDetails, flippedDest, final_path);
                        return true;
                    }
                    else if (closedList[i + x][j + y] == false && isUnBlocked(grid, i + x, j + y) == true)
                    {
                        gNew = cellDetails[i][j].g + offsets[t][2];
                        hNew = calculateHValue(i + x, j + y, flippedDest);
                        fNew = gNew + hNew;

                        if (c.f == FLT_MAX || c.f > fNew)
                        {
                            openList.push_back({ (float)fNew, (float)(i + x), (float)(j + y) });

                            c.set(fNew, gNew, hNew, i, j);
                        }
                    }
                }
            }
        }

        return false;

    }

};