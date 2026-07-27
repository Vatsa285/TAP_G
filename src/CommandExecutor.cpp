#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>

#include <unistd.h>

#include "CommandExecutor.h"

CommandExecutor::CommandExecutor() {}



bool CommandExecutor::execute(const std::vector<std::string>& command)
{
    std::vector<const char*> argv;
    for (const auto& arg : command) {
        argv.push_back(arg.c_str());
    }
    argv.push_back(nullptr);

    if (argv.empty() || argv[0] == nullptr) {
        return false;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return false;
    } else if (pid == 0) {
        execvp(argv[0], const_cast<char* const*>(argv.data()));
        perror("execvp");
        std::exit(EXIT_FAILURE);
    } 

    return true;
}