/* =========================================================================
 * This file is part of cli-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2010, General Dynamics - Advanced Information Systems
 *
 * cli-c++ is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not,
 * see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __CLI_ARGUMENT_PARSER_H__
#define __CLI_ARGUMENT_PARSER_H__

#include <iostream>
#include <import/str.h>
#include "cli/Argument.h"
#include "cli/Results.h"

namespace cli
{

enum
{
    EXIT_USAGE = 1, EXIT_VERSION = 2
};

class ArgumentParser
{
public:
    ArgumentParser();
    ~ArgumentParser();

    /**
     * Shortcut for adding an argument. Returns the newly created argument.
     */
    Argument* addArgument(std::string nameOrFlags, std::string help = "",
                          cli::Action action = cli::STORE,
                          std::string destination = "",
                          std::string metavar = "",
                          int minArgs = -1, int maxArgs = -1,
                          bool required = false);

    /**
     * Text to display before the argument help
     */
    ArgumentParser& setDescription(const std::string description);

    /**
     * Text to display before the usage
     */
    ArgumentParser& setProlog(const std::string prolog);

    /**
     * Text to display after the argument help
     */
    ArgumentParser& setEpilog(const std::string epilog);

    /**
     * The program usage. This is generated by default.
     */
    ArgumentParser& setUsage(const std::string usage);

    /**
     * Enable the help option (on by default)
     */
    ArgumentParser& enableHelp(bool flag);

    /**
     * Set the name of the program (default is argv[0]
     */
    ArgumentParser& setProgram(const std::string program);

    /**
     * Prints the help and optionally exits.
     */
    void printHelp(std::ostream& out = std::cerr, bool andExit = false) const;

    /**
     * Prints the usage and optionally exits.
     */
    void printUsage(std::ostream& out = std::cerr, bool andExit = false,
                    const std::string message = "") const;

    /**
     * Parses the given arguments
     */
    Results* parse(int argc, const char** argv);

    /**
     * Parses the given arguments
     */
    Results* parse(int argc, char** argv)
    {
        return parse(argc, reinterpret_cast<const char**>(argv));
    }

    /**
     * Parses the arguments. args[0] is NOT used as the program name, so you
     * will need to specify it explicitly using setProgramName().
     */
    Results* parse(const std::vector<std::string>& args);

protected:
    friend class Argument;

    std::vector<Argument*> mArgs;
    std::string mDescription;
    std::string mProlog;
    std::string mEpilog;
    std::string mUsage;
    std::string mProgram;
    bool mHelpEnabled;
    char mPrefixChar;

    void parseError(const std::string& msg);
    void processFlags(std::vector<std::string>& posFlags, std::vector<
            std::string>& opFlags, std::vector<std::string>&posHelps,
                      std::vector<std::string>&opHelps,
                      std::vector<std::string>&opUsage,
                      std::vector<std::string>&posUsage,
                      size_t& maxFlagsWidth) const;
};

}
#endif
