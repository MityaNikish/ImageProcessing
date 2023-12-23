#pragma once
#include <exception>

class User_exception : public std::exception {};

class not_selected_strategy : public User_exception {
    const char* what() const noexcept override
    {
        return "No strategy selected";
    }
};