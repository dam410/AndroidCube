#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <sstream>
#include "android/log.h"

#define APP_NAME "MyApp"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, APP_NAME, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , APP_NAME, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , APP_NAME, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , APP_NAME, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , APP_NAME, __VA_ARGS__)

namespace logger
{

// My endl
class endl_t {};
extern endl_t endl;

namespace priv
{

    template<std::size_t L>
    class clogger_t
    {
        public:
            clogger_t& operator<<(endl_t endl);

            template <typename T>
            clogger_t& operator<<(T const& toLog);

        private:
            std::stringstream stream;
    };

    template<std::size_t L>
    clogger_t<L>& clogger_t<L>::operator<<(endl_t endl)
    {
        std::string str = stream.str();
        __android_log_print(L, APP_NAME, "%s", str.c_str());
        stream.str("");
        stream.clear();
        return *this;
    }

    template<std::size_t L>
    template<typename T>
    clogger_t<L>& clogger_t<L>::operator<<(T const& toLog)
    {
        stream << toLog;
        return *this;
    }

}

using cverbose_t = priv::clogger_t<ANDROID_LOG_VERBOSE>;
using cdebug_t = priv::clogger_t<ANDROID_LOG_DEBUG>;
using cinfo_t = priv::clogger_t<ANDROID_LOG_INFO>;
using cwarn_t = priv::clogger_t<ANDROID_LOG_WARN>;
using cerror_t = priv::clogger_t<ANDROID_LOG_ERROR>;

extern cverbose_t cverbose;
extern cdebug_t   cdebug;
extern cinfo_t    cinfo;
extern cwarn_t    cwarn;
extern cerror_t   cerror;

}

#undef LOGV
#undef LOGD
#undef LOGI
#undef LOGW
#undef LOGE

#endif // LOG_HPP
