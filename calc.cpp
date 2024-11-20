#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Expressions.hpp"

std::string read_expression();
std::vector<std::string> tokenize(const std::string &input);
Expression_ptr get_abstract_tree(const std::vector<std::string> &tokens);

int main()
{
    auto expr = read_expression();
    const auto tokens = tokenize(expr);

    try
    {
        auto abstaract_tree = get_abstract_tree(tokens);

        std::cout << "Result: " << abstaract_tree->eval() << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

std::string read_expression()
{
    std::string expr;
    std::getline(std::cin, expr);

    return expr;
}

std::vector<std::string> tokenize(const std::string &input)
{
    std::vector<std::string> tokens;
    std::string token;

    for (char ch : input)
    {
        if (std::isspace(ch))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else if (ch == '(' || ch == ')')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, ch));
        }
        else
        {
            token += ch;
        }
    }

    if (!token.empty())
    {
        tokens.push_back(token);
    }

    return tokens;
}

Expression_ptr get_abstract_tree(const std::vector<std::string> &tokens)
{
    if (tokens.empty())
    {
        throw std::runtime_error("Empty expressioin");
    }

    Expressions_t expressions;
    std::vector<size_t> fold_indices;
    bool prev_is_openbracker = false;

    int open_bracket_counter = 0;

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        auto &token = tokens[i];

        if (prev_is_openbracker)
        {
            prev_is_openbracker = false;
            if (token == "+")
            {
                expressions.push_back(std::make_unique<Add>());
            }
            else if (token == "-")
            {
                expressions.push_back(std::make_unique<Sub>());
            }
            else if (token == "*")
            {
                expressions.push_back(std::make_unique<Mul>());
            }
            else if (token == "/")
            {
                expressions.push_back(std::make_unique<Div>());
            }
            else
            {
                throw std::runtime_error("Expected operator after open bracket");
            }
        }
        else if (token == "(")
        {
            ++open_bracket_counter;
            fold_indices.push_back(i);
            prev_is_openbracker = true;
        }
        else if (token == ")")
        {
            if (fold_indices.empty() && tokens.size() != i)
            {
                throw std::runtime_error("Close bracker before open bracket");
            }

            auto op_index = fold_indices.back() + 1;
            auto &op = expressions[op_index];

            fold_indices.pop_back();
            for (size_t j = op_index + 1; j < expressions.size() + open_bracket_counter; ++j)
            {
                op->add_operand(std::move(expressions[j]));
            }

            std::cout << expressions.size() << '\n';
            // expressions.erase(expressions.end() - (expressions.size() + open_bracket_counter - (op_index + 1)), expressions.end());
            expressions.resize(expressions.size() + open_bracket_counter - (op_index + 1));

            --open_bracket_counter;
        }
        else if (double num = std::stod(token))
        {
            expressions.push_back(std::make_unique<Number>(num));
        }
        else
        {
            expressions.push_back(std::make_unique<Invalid>());
        }
    }

    if (expressions.size() != 1)
    {
        throw std::runtime_error("Expected close bracket");
    }

    Expression_ptr main_expr = std::move(expressions[0]);
    return main_expr;
}