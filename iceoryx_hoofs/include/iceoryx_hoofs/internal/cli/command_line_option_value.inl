// Copyright (c) 2022 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0
#ifndef IOX_HOOFS_CLI_COMMAND_LINE_OPTION_VALUE_INL
#define IOX_HOOFS_CLI_COMMAND_LINE_OPTION_VALUE_INL

#include "iceoryx_hoofs/internal/cli/command_line_option_value.hpp"

namespace iox
{
namespace cli
{
namespace internal
{
template <typename T>
inline cxx::expected<T, CommandLineOptionValue::Error>
CommandLineOptionValue::convertFromString(const Argument_t& stringValue) const noexcept
{
    T value;
    if (!cxx::convert::fromString(stringValue.c_str(), value))
    {
        std::cout << "\"" << stringValue.c_str() << "\" could not be converted to the requested type" << std::endl;
        return cxx::error<Error>(Error::UNABLE_TO_CONVERT_VALUE);
    }
    return cxx::success<T>(value);
}

template <>
inline cxx::expected<bool, CommandLineOptionValue::Error>
CommandLineOptionValue::convertFromString(const Argument_t& stringValue) const noexcept
{
    bool doesContainTrueAsString = (strncmp(stringValue.c_str(), "true", 5) == 0);
    if (!doesContainTrueAsString && (strncmp(stringValue.c_str(), "false", 6) != 0))
    {
        std::cout << "\"" << stringValue.c_str() << "\" could not be converted to the requested type" << std::endl;
        return cxx::error<Error>(Error::UNABLE_TO_CONVERT_VALUE);
    }
    return cxx::success<bool>(doesContainTrueAsString);
}

template <typename T>
inline cxx::expected<T, CommandLineOptionValue::Error>
CommandLineOptionValue::get(const OptionName_t& optionName) const noexcept
{
    for (const auto& a : m_arguments)
    {
        if (a.hasOptionName(optionName))
        {
            return convertFromString<T>(a.value);
        }
    }

    return cxx::error<Error>(Error::NO_SUCH_VALUE);
}
} // namespace internal
} // namespace cli
} // namespace iox

#endif
