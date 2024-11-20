#include "Invalid.hpp"

#include <stdexcept>

double Invalid::eval()
{
    throw std::runtime_error("Unknown node type");
}