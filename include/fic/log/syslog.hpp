#pragma once
#include <sstream>
#include <stdexcept>
#include <syslog.h>
#include <fic/log/level.hpp>

namespace fic
{
namespace log
{

class SyslogStream;
class SyslogStreamBuffer final : public std::basic_streambuf<char>
{
public:
    explicit SyslogStreamBuffer(Level level, const std::string& name)
        : std::basic_streambuf<char>()
        , level_(translateLevel(level))
    {
        openlog(name.empty() ? nullptr : name.data(), LOG_PID, LOG_USER);
    }

    ~SyslogStreamBuffer() override
    {
        closelog();
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
            syslog(level_, "%s", buffer_.c_str());
            buffer_.clear();
        }
        return 0;
    }

    friend class SyslogStream;
    void setLevel(Level level) noexcept
    {
        level_ = translateLevel(level);
    }

    static int translateLevel(Level level)
    {
        switch (level)
        {
            case Level::Emergency:
                return LOG_EMERG;
            case Level::Alert:
                return LOG_ALERT;
            case Level::Error:
                return LOG_ERR;
            case Level::Warning:
                return LOG_WARNING;
            case Level::Notice:
                return LOG_NOTICE;
            case Level::Info:
                return LOG_INFO;
            case Level::Debug:
                return LOG_DEBUG;
            default:
                throw std::invalid_argument("level");
        }
    }

private:
    std::string buffer_;
    int level_;
};

class SyslogStream : public std::basic_ostream<char>
{
public:
    explicit SyslogStream(Level level, const std::string& name = std::string())
        : std::basic_ostream<char>(&streambuf_)
        , streambuf_(level, name)
    {
    }

    SyslogStream& operator<<(Level level) noexcept
    {
        streambuf_.setLevel(level);
        return (*this);
    }

private:
    SyslogStreamBuffer streambuf_;
};

} // namespace log
} // namespace fic