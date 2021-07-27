#ifndef BOOTSERV_BELNET_CRON_HPP
#define BOOTSERV_BELNET_CRON_HPP

#include "handler.hpp"

namespace belnet
{
  namespace bootserv
  {
    struct CronHandler final : public Handler
    {
      CronHandler(std::ostream& o);
      ~CronHandler();

      int
      Exec(const Config& conf) override;

      int
      ReportError(const char* err) override;
    };

  }  // namespace bootserv
}  // namespace belnet

#endif
