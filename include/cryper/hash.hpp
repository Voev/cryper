#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>

namespace cryper
{

class Hash
{
public:
    enum Status
    {
        NotStarted = 0,
        InProgress,
    };

    Hash()
        : status_(NotStarted)
    {
    }

    virtual ~Hash()
    {
    }

    virtual bool hashInit()
    {
        if (status_ != NotStarted)
        {
            return false;
        }
        status_ = InProgress;
        return true;
    }

    virtual bool checkUpdate()
    {
        if (status_ != InProgress)
        {
            return false;
        }
        return true;
    }

    virtual bool checkFinal()
    {
        if (status_ != InProgress)
        {
            return false;
        }
        status_ = NotStarted;
        return true;
    }

    virtual bool doInit() = 0;
    virtual bool doUpdate(const std::vector<uint8_t>& data) = 0;
    virtual bool doFinal(std::vector<uint8_t>& hash) = 0;

protected:
    Status status_;
};

} // namespace cryper
