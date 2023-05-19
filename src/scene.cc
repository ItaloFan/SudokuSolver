#include <iostream>
#include "scene.h"
#include "pos.h"
#include "color.h"
#include "platform.inl"
#include "common.inl"

Scene::Scene()
{
}

bool Scene::set_val(Pos pos, int val)
{
    if (val > 0 && val < 10)
    {
        board_[pos.idx] = val;
        return true;
    }
    else if (val == 0)
    {
        clear_val(pos);
    }
    return false;
}

bool Scene::clear_val(Pos pos)
{
    board_[pos.idx] = 0;
    return true;
}

void Scene::show()
{
    cls_();
    std::cout << std::endl;

    print_underline_();
    for (int row = 0; row < 9; row++)
    {
        std::cout << Color::Modifier(OUTLINE_COLOR) << VERTICAL_LINE << Color::Modifier(Color::RESET);
        for (int col = 0; col < 9; col++)
        {
            std::cout << " ";
            int num = board_[row * 9 + col];
            if (num == 0)
            {
                std::cout << " ";
            }
            else
            {
                std::cout << num;
            }
            std::cout << " ";
            if (col % 3 == 2)
            {
                std::cout << Color::Modifier(OUTLINE_COLOR) << VERTICAL_LINE << Color::Modifier(Color::RESET);
            }
            else
            {
                std::cout << VERTICAL_LINE;
            }
        }
        std::cout << std::endl;
        print_underline_(row);
    }

    std::cout << std::endl;
}

void Scene::reset()
{
    for (int i = 0; i < 81; i++)
    {
        board_[i] = 0;
    }
    show();
}

void Scene::input()
{
    show();

    char key = '\0';
    while (1)
    {
        key = getch();
        if (key >= '0' && key <= '9')
        {
            set_val(Pos(cur_cell_.row, cur_cell_.col), key - '0');
            show();
        }
        else if (keymap_.up(key))
        {
            int cur_row = cur_cell_.row;
            if (cur_row > 0)
            {
                cur_cell_.row--;
                show();
            }
        }
        else if (keymap_.down(key))
        {
            int cur_row = cur_cell_.row;
            if (cur_row < 8)
            {
                cur_cell_.row++;
                show();
            }
        }
        else if (keymap_.left(key))
        {
            int cur_col = cur_cell_.col;
            if (cur_col > 0)
            {
                cur_cell_.col--;
                show();
            }
        }
        else if (keymap_.right(key))
        {
            int cur_col = cur_cell_.col;
            if (cur_col < 8)
            {
                cur_cell_.col++;
                show();
            }
        }
        else if (keymap_.reset(key))
        {
            reset();
            show();
        }
        else if (keymap_.quit(key))
        {
            break;
        }
        else if (keymap_.confirm(key))
        {
            confirm = true;
            break;
        }
    }
}

std::string Scene::get_puzzle()
{
    std::string puzzle;
    for (int i = 0; i < 81; i++)
    {
        puzzle += std::to_string(board_[i]);
    }
    return puzzle;
}

void Scene::cls_()
{
    clear();
}

void Scene::print_underline_(int row)
{
    bool change_all_color = false;
    if (row == -1 || row % 3 == 2)
    {
        change_all_color = true;
        std::cout << Color::Modifier(OUTLINE_COLOR);
    }
    for (int col = 0; col < 9; col++)
    {
        if (!change_all_color && col % 3 == 0)
        {

            std::cout << Color::Modifier(OUTLINE_COLOR) << CROSS_LINE << Color::Modifier(Color::RESET) << HORIZONTAL_LINE << ((cur_cell_.row == row && cur_cell_.col == col) ? "^" : HORIZONTAL_LINE) << HORIZONTAL_LINE;
        }
        else
        {
            std::cout << CROSS_LINE << HORIZONTAL_LINE << ((cur_cell_.row == row && cur_cell_.col == col) ? "^" : HORIZONTAL_LINE) << HORIZONTAL_LINE;
        }
    }
    std::cout << Color::Modifier(OUTLINE_COLOR) << CROSS_LINE << std::endl;
    if (row == -1 || row % 3 == 2)
    {
        std::cout << Color::Modifier(Color::RESET);
    }
}
