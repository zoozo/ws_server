#include "logger.h"
namespace zoozo{
    logger::logger(const std::string& filename){//{{{
        logging::add_file_log
            (
             keywords::file_name = filename,
             // This makes the sink to write log records that look like this:
             // YYYY-MM-DD HH:MI:SS [normal] A normal severity message
             // YYYY-MM-DD HH:MI:SS [error] An error severity message
             keywords::open_mode = (std::ios::out | std::ios::app),
             keywords::auto_flush = true,
             keywords::format =
             (
              expr::stream
              << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
              << " [" << logging::trivial::severity
              << "] " << expr::smessage
             )
            );
        logging::add_common_attributes();
    }//}}}

    void logger::write(trivial::severity_level level, const std::string& msg){//{{{
        BOOST_LOG_SEV(_lg, level) << msg;
    }//}}}
}
