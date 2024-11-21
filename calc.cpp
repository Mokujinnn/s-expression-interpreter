#include <iomanip>
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

        std::cout << std::fixed << std::setprecision(4) << "Result: " << abstaract_tree->eval() << '\n';
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
        throw std::runtime_error("Empty expression");

    Expressions_t expressions;
    std::vector<size_t> fold_indices;

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        const auto &token = tokens[i];

        if (token == "(")
        {
            fold_indices.push_back(expressions.size());
        }
        else if (token == ")")
        {
            if (fold_indices.empty())
                throw std::runtime_error("Mismatched parentheses");

            size_t start_idx = fold_indices.back();
            fold_indices.pop_back();

            if (expressions.size() <= start_idx + 1)
                throw std::runtime_error("Missing operands in parentheses");

            auto op = std::move(expressions[start_idx]);
            for (size_t j = start_idx + 1; j < expressions.size(); ++j)
            {
                op->add_operand(std::move(expressions[j]));
            }

            expressions.resize(start_idx);
            expressions.push_back(std::move(op));
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (fold_indices.empty() || fold_indices.back() + 1 != i)
                throw std::runtime_error("Operator outside parentheses");

            if (token == "+")
                expressions.push_back(std::make_unique<Add>());
            else if (token == "-")
                expressions.push_back(std::make_unique<Sub>());
            else if (token == "*")
                expressions.push_back(std::make_unique<Mul>());
            else if (token == "/")
                expressions.push_back(std::make_unique<Div>());
            else
                expressions.push_back(std::make_unique<Invalid>());
        }
        else
        {
            if (fold_indices.back() + 1 == i)
            {
                throw std::runtime_error("Missing operator");
            }

            try
            {
                double num = std::stod(token);
                expressions.push_back(std::make_unique<Number>(num));
            }
            catch (...)
            {
                throw std::runtime_error("Invalid number: " + token);
            }
        }
    }

    if (expressions.size() != 1)
        throw std::runtime_error("Malformed expression");

    return std::move(expressions[0]);
}