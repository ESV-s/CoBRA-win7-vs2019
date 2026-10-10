#pragma once

#include <tl/expected.hpp>
#include <string>
#include <utility>

namespace cobra {

    enum class CobraError {
        kParseError,
        kNonLinearInput,
        kTooManyVariables,
        kNoReduction,
        kVerificationFailed,
        kInvalidArgument,
    };

    struct ErrorInfo
    {
        CobraError code;
        std::string message;
    };

    template< typename T >
    using Result = tl::expected< T, ErrorInfo >;

    template< typename T >
    Result< T > Ok(T value) {
        return Result< T >(std::move(value));
    }

    template< typename T >
    Result< T > Err(CobraError code, std::string message) {
        return tl::make_unexpected(ErrorInfo{ .code = code, .message = std::move(message) });
    }

} // namespace cobra