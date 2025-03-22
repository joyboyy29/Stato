#pragma once

#include <string_view>
#include <string>
#include <optional>
#include <array>
#include <ostream>
#include <format>

namespace Stato {
    enum class status : int {
        unknown = 0,
        success,
        failure,
        invalid_parameter,
        not_supported,
        non_aligned
    };

    constexpr std::string_view to_string(status s) {
        switch (s) {
            case status::unknown:           return "unknown";
            case status::success:           return "success";
            case status::failure:           return "failure";
            case status::invalid_parameter: return "invalid_parameter";
            case status::not_supported:     return "not_supported";
            case status::non_aligned:       return "non_aligned";
            default:                        return "invalid_status";
        }
    }

    inline std::ostream& operator<<(std::ostream& os, status s) {
        return os << to_string(s);
    }

    inline bool is_success(status s) {
        return s == status::success;
    }

    inline bool is_error(status s) {
        return s != status::success;
    }

    inline std::optional<status> status_from_string(std::string_view str) {
        struct mapping { status st; std::string_view name; };
        constexpr std::array<mapping, 6> mappings{{
            { status::unknown,           "unknown" },
            { status::success,           "success" },
            { status::failure,           "failure" },
            { status::invalid_parameter, "invalid_parameter" },
            { status::not_supported,     "not_supported" },
            { status::non_aligned,       "non_aligned" }
        }};

        for (const auto& m : mappings) {
            if (m.name == str) {
                return m.st;
            }
        }
        return std::nullopt;
    }

    inline std::string_view error_description(status s) {
        switch (s) {
            case status::success:           return "Operation success";
            case status::failure:           return "Operation failure";
            case status::invalid_parameter: return "Invalid parameter provided";
            case status::not_supported:     return "Operation not supported";
            case status::non_aligned:       return "Address or size is non-aligned";
            case status::unknown:
            default:                        return "Unknown status";
        }
    }

    inline bool is_valid_status(int code) {
        switch (static_cast<status>(code)) {
            case status::unknown:
            case status::success:
            case status::failure:
            case status::invalid_parameter:
            case status::not_supported:
            case status::non_aligned:
                return true;
            default:
                return false;
        }
    }

    inline status safe_status(int code) {
        return is_valid_status(code) ? static_cast<status>(code) : status::unknown;
    }
}

// support for std::format, std::print, std::println
namespace std {
    template <>
    struct formatter<Stato::status, char> {
        constexpr auto parse(basic_format_parse_context<char>& ctx) -> decltype(ctx.begin()) {
            return ctx.begin();
        }
        
        auto format(const Stato::status& s, format_context& ctx) const -> decltype(ctx.out()) {
            return format_to(ctx.out(), "{}", Stato::to_string(s));
        }
    };
}
