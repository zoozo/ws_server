#ifndef ZOOZO_LOGGER_H
#define ZOOZO_LOGGER_H

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace trivial = logging::trivial;

namespace zoozo{
    class logger{
        public:
        logger(const std::string& filename);
        void write(trivial::severity_level level, const std::string& msg);
        
        private:
        src::severity_logger<trivial::severity_level> _lg;
    };
}
#endif
