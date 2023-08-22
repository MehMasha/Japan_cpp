#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::RectangleShape shape(sf::Vector2f(70.f, 70.f));

    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\mariy\\Downloads\\arial-cufonfonts\\ARIAL.TTF"))
    {
        std::cout << "error";
    }


    float size = 70.f;

    vector<vector<int>> image = 
    {
        {0, 0, 0, 1, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 1},
        {0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0},
        {1, 1, 0, 1, 0, 1, 0},
    };

    const int rows = image.size();
    const int cols = image[0].size();
    const int n = rows * cols;
    int hint_rows = (cols + 1) / 2;
    int hint_cols = (rows + 1) / 2;

    vector<sf::RectangleShape> arr(n);
    //sf::RectangleShape arr[n];
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            sf::RectangleShape shape(sf::Vector2f(size, size));
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(-5.f);
            shape.setFillColor(sf::Color::White);
            shape.setPosition(hint_rows * size + j * size, hint_cols * size + i * size);
            arr[i * cols + j] = shape;
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    if (
                        (localPosition.x < size * cols + hint_rows * size) 
                        && (localPosition.y < size * rows + hint_cols * size)
                        && (localPosition.x > hint_rows * size)
                        && (localPosition.y > hint_cols * size)
                        ) 
                    {
                        int index = ((localPosition.x - hint_rows * int(size)) / static_cast<int>(size)) 
                            + ((localPosition.y - hint_cols * int(size)) / static_cast<int>(size)) * cols;

                        sf::Color color = arr[index].getFillColor();
                        if (color == sf::Color::White) {
                            arr[index].setFillColor(sf::Color::Green);
                        }
                        else if (color == sf::Color::Green)
                        {
                            arr[index].setFillColor(sf::Color::Red);
                        }
                        else
                        {
                            arr[index].setFillColor(sf::Color::White);
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Cyan);

        for (size_t i = 0; i < n; i++)
        {
            window.draw(arr[i]);
        }

        std::vector<std::vector <int>> cols_sums(cols);

        for (size_t i = 0; i < cols; i++)
        {
            int summa = 0;
            int hint_num = hint_cols - 1;

            for (int j = rows - 1; j > -1; j--)
            {
                if ((image[j][i] == 0) && (summa != 0)) {
                    //std::cout << summa << " ";
                    cols_sums[i].push_back(summa);

                    sf::Text text;
                    text.setFont(font);
                    text.setString(to_string(summa));
                    text.setCharacterSize(size / 3);
                    text.setFillColor(sf::Color::Red);
                    text.setPosition(hint_rows * size + i * size + size / 3, hint_num * size + size / 3);
                    window.draw(text);
                    hint_num -= 1;

                    summa = 0;
                }
                if (image[j][i] == 1) {
                    summa += 1;
                }

            }
            if (summa != 0) {
                //std::cout << summa << "";
                cols_sums[i].push_back(summa);
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(summa));
                text.setCharacterSize(size / 3);
                text.setFillColor(sf::Color::Red);
                text.setPosition(hint_rows * size + i * size + size / 3, hint_num * size + size / 3);
                window.draw(text);
            }

            //std::cout << std::endl;
        }

        std::vector<std::vector <int>> rows_sums(rows);

        for (size_t i = 0; i < rows; i++)
        {
            int summa = 0;
            int hint_num = hint_rows - 1;

            for (int j = cols - 1; j > -1; j--)
            {
                if ((image[i][j] == 0) && (summa != 0)) {
                    rows_sums[i].push_back(summa);

                    sf::Text text;
                    text.setFont(font);
                    text.setString(to_string(summa));
                    text.setCharacterSize(size / 3);
                    text.setFillColor(sf::Color::Red);
                    text.setPosition(hint_num * size + size / 3, hint_cols * size + i * size + size / 3);
                    window.draw(text);
                    hint_num -= 1;
                    summa = 0;
                }
                if (image[i][j] == 1) {
                    summa += 1;
                }

            }
            if (summa != 0) {
                rows_sums[i].push_back(summa);
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(summa));
                text.setCharacterSize(size / 3);
                text.setFillColor(sf::Color::Red);
                text.setPosition(hint_num * size + size / 3, hint_cols * size + i * size + size / 3);
                window.draw(text);
            }


        }

        window.display();
    }

    return 0;
}