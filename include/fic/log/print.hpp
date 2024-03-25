#pragma once
#include <ostream>
#include <memory>
#include <fic/log/level.hpp>
#include <fic/log/syslog.hpp>
#include <fic/log/console.hpp>

namespace fic
{
namespace log
{

class Print;
class Manager
{
public:
    static Manager& Instance()
    {
        static Manager instance;
        return instance;
    }

    friend class Print;

    void EnableSyslog()
    {
        syslog_ = std::make_unique<SyslogStream>(maxLevel_);
    }

    void EnableConsole()
    {
        console_ = std::make_unique<ConsoleStream>(maxLevel_);
    }

    void SetMaxLevel(Level level)
    {
        maxLevel_ = level;
    }

    Level GetMaxLevel() const
    {
        return maxLevel_;
    }

private:
    Manager()
        : maxLevel_(Level::Warning)
    {
    }

private:
    std::unique_ptr<ConsoleStream> console_;
    std::unique_ptr<SyslogStream> syslog_;
    Level maxLevel_;
};

class Print
{
public:
    Print(Level level)
        : level_(level)
    {
    }

    template <typename T> Print& operator<<(const T& x)
    {
        if (Enabled())
        {
            if (Manager::Instance().console_.get())
            {
                (*Manager::Instance().console_.get()) << level_ << x;
            }

            if (Manager::Instance().syslog_.get())
            {
                (*Manager::Instance().syslog_.get()) << level_ << x;
            }
        }
        return *this;
    }

    typedef std::ostream& (*EndLine)(std::ostream&);
    Print& operator<<(EndLine manip)
    {
        if (Enabled() && manip)
        {
            if (Manager::Instance().console_.get())
            {
                manip(*Manager::Instance().console_.get());
            }
        }
        return *this;
    }

private:
    inline bool Enabled() const
    {
        return (level_ <= Manager::Instance().GetMaxLevel());
    }

private:
    Level level_;
};

} // namespace log
} // namespace fic