#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>

class Image
{
      private:
            int width;
            int height;
            int **grid;
            std::ofstream file;
      public:
            Image(std::string filename) : width(100), height(100) {
                  grid = new int*[height];
                  for (int i = 0; i < height; i++)
                  {
                        grid[i] = new int[width];
                  }
                  file.open(filename);
            }
            Image(int width, int height, std::string filename) :
                  width(width), height(height) {
                        grid = new int*[height];
                        for (int i = 0; i < height; i++)
                        {
                              grid[i] = new int[width];
                        }
                        file.open(filename);
                  }

            ~Image()
            {
                for (int i = 0; i < height; i++) {
                    delete[] grid[i];
              }
                delete[] grid;
                file.close();
            }

            void dot(int x, int y)
            {
                  for (int i = -1; i <= 1; i++)
                  {
                        for (int j = -1; j <= 1; j++)
                        {
                              if (x + i >= 0 && x + i < height &&
                                  y + j >= 0 && y + j < width)
                              {
                                    grid[x + i][y + j] = 1;
                              }
                        }
                  }
            }

            void line(std::pair <int ,int > from, std::pair<int, int> to)
            {
                  double x_speed = to.first - from.first;
                  double y_speed = to.second - from.second;
                  x_speed /= 1000;
                  y_speed /= 1000;
                  double x, y;

                  x = from.first;
                  y = from.second;

                  while (x != to.second || y != to.second)
                  {
                        grid[(int)x][(int)y] = 1;
                        double dist1 = (to.second-y)*(to.second-y)  + (to.first - x)*(to.first - x);
                        x += x_speed;
                        y += y_speed;
                        double dist2 = (to.second-y)*(to.second-y) + (to.first - x)*(to.first - x);

                        if (dist1 < dist2) break;
                  }
            }

            void save()
            {
                  file << "P1" << std::endl;
                  file << width << " " << height << std::endl;

                  for (int x = 0; x < height; x++)
                  {
                        for (int y = 0; y < width; y++)
                        {
                              file << grid[x][y];
                        }
                        file << std::endl;
                  }
                  file.close();
            }


};

#endif // IMAGE_H
