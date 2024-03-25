#pragma once

namespace fic
{
namespace log
{

enum class Level
{
    Emergency = 0,
    Alert = 0x1,
    Critical = 0x2,
    Error = 0x3,
    Warning = 0x4,
    Notice = 0x5,
    Info = 0x6,
    Debug = 0x7,
};

} // namespace log
} // namespace fic