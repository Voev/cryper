#include <fic/log/print.hpp>
#include <fic/log/format.hpp>

using namespace fic::log;

int main()
{
    Manager::Instance().SetMaxLevel(Level::Warning);
    Manager::Instance().EnableConsole();
    Print(Level::Warning) << Format("{} Fucked {}!", "Hello", "World") << std::endl;
}