#pragma once
#include <sstream>
#include <iostream>
#include <fic/log/level.hpp>

namespace fic
{

namespace log
{

#define COLOR_L_BLACK "\x1B[0;30m"
#define COLOR_L_RED "\x1B[0;31m"
#define COLOR_L_GREEN "\x1B[0;32m"
#define COLOR_L_ORANGE "\x1B[0;33m"
#define COLOR_L_BLUE "\x1B[0;34m"
#define COLOR_L_PURPLE "\x1B[0;35m"
#define COLOR_L_CYAN "\x1B[0;36m"
#define COLOR_L_GRAY "\x1B[0;37m"

#define COLOR_B_GRAY "\x1B[1;30m"
#define COLOR_B_RED "\x1B[1;31m"
#define COLOR_B_GREEN "\x1B[1;32m"
#define COLOR_B_YELLOW "\x1B[1;33m"
#define COLOR_B_BLUE "\x1B[1;34m"
#define COLOR_B_PURPLE "\x1B[1;35m"
#define COLOR_B_CYAN "\x1B[1;36m"
#define COLOR_B_WHITE "\x1B[1;37m"

#define COLOR_RESET "\x1B[0m"

class ConsoleStream;
class ConsoleStreamBuffer : public std::basic_streambuf<char>
{
public:
    explicit ConsoleStreamBuffer(Level level)
        : std::basic_streambuf<char>()
        , level_(level)
    {
    }

    ~ConsoleStreamBuffer() override
    {
    }

protected:
    int_type overflow(int_type c = traits_type::eof()) override
    {
        if (traits_type::eq_int_type(c, traits_type::eof()))
        {
            sync();
        }
        else
        {
            buffer_ += traits_type::to_char_type(c);
        }

        return c;
    }

    int sync() override
    {
        if (!buffer_.empty())
        {
            if (level_ <= Level::Error)
            {
                std::cerr << COLOR_B_RED << "[ERR] " << COLOR_RESET << buffer_;
            }
            else if (level_ == Level::Warning)
            {
                std::cout << COLOR_B_YELLOW << "[WARN] " << COLOR_RESET
                          << buffer_;
            }
            else
            {
                std::cout << COLOR_B_WHITE << "[INFO] " << COLOR_RESET
                          << buffer_;
            }
            buffer_.clear();
        }
        return 0;
    }

    friend class ConsoleStream;
    void setLevel(Level level) noexcept
    {
        level_ = level;
    }

private:
    std::string buffer_;
    Level level_;
};

class ConsoleStream : public std::basic_ostream<char>
{
public:
    explicit ConsoleStream(Level level)
        : std::basic_ostream<char>(&streambuf_)
        , streambuf_(level)
    {
    }

    ConsoleStream& operator<<(Level level) noexcept
    {
        streambuf_.setLevel(level);
        return (*this);
    }

private:
    ConsoleStreamBuffer streambuf_;
};

} // namespace log
} // namespace fic