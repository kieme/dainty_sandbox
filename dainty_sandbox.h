/******************************************************************************

 MIT License

 Copyright (c) 2018 kieme, frits.germs@gmx.net

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

******************************************************************************/

#ifndef _DAINTY_SANDBOX_H_
#define _DAINTY_SANDBOX_H_

#include "dainty_named.h"
#include "dainty_named_string.h"
#include "dainty_os_clock.h"
#include "dainty_os_threading_thread.h"
#include "dainty_tracing_tracer.h"
#include "dainty_messaging_messenger.h"
#include "dainty_sandbox_err.h"

///////////////////////////////////////////////////////////////////////////////

#define SB_DEBUG(...) \
  TRACE_0(get_trace(), trace::level_debug, ( __VA_ARGS__ ))
#define SB_NOTICE(...) \
  TRACE_0(get_trace(), trace::level_notice, ( __VA_ARGS__ ))
#define SB_WARNING(...) \
  TRACE_0(get_trace(), trace::level_warning, ( __VA_ARGS__ ))
#define SB_ERROR(...) \
  TRACE_0(get_trace(), trace::level_error, ( __VA_ARGS__ ))

///////////////////////////////////////////////////////////////////////////////

namespace dainty
{
namespace sandbox
{
  using named::t_prefix;
  using named::t_void;
  using named::t_bool;
  using named::t_n;
  using named::t_fd;
  using named::t_nsec;
  using named::string::t_string;

  using mt::detached_thread::t_thread;
  using t_thread_logic = t_thread::t_logic;

  enum  t_label_tag_ { };
  using t_label = t_string<t_label_tag_>;
  using R_label = t_prefix<t_label>::R_;

///////////////////////////////////////////////////////////////////////////////

  class t_message_logic {
  public:
    const t_label label;

    t_message_logic(R_label _label) : label(_label) { }

    virtual ~t_message_logic() { }
    virtual t_bool process(r_message) = 0;
  };

///////////////////////////////////////////////////////////////////////////////

  class t_stats {
  public:
  };

///////////////////////////////////////////////////////////////////////////////

  class t_impl_;
  using p_impl_ = t_prefix<t_impl_>::p_;

///////////////////////////////////////////////////////////////////////////////

  class t_logic;
  using r_logic = t_prefix<t_logic>::r_;
  using x_logic = t_prefix<t_logic>::x_;
  using R_logic = t_prefix<t_logic>::R_;

  class t_logic : public t_thread_logic {
  public:
    using t_err                     = sandbox::err::t_err;
    using t_multiple_of_1ms         = sandbox::t_multiple_of_1ms;
    using t_fd                      = sandbox::t_fd;
    using t_stats                   = sandbox::t_stats;
    using t_label                   = sandbox::t_label;
    using t_nsec                    = sandbox::t_nsec;
    using t_message_logic           = sandbox::t_message_logic;

    using R_password                = messaging::R_password;
    using t_message                 = messaging::t_message;
    using t_messages                = messaging::t_messages;
    using t_message_id              = messaging::t_message_id;
    using t_multiple_of_100ms       = messaging::t_multiple_of_100ms;
    using t_messenger_scope         = messaging::t_messenger_scope;
    using R_messenger_password      = messaging::R_messenger_password;
    using t_messenger_prio          = messaging::t_messenger_prio;
    using t_messenger_user          = messaging::t_messenger_user;
    using t_messenger_name          = messaging::t_messenger_name;
    using t_messenger_key           = messaging::t_messenger_key;
    using t_messenger_state         = messaging::t_messenger_state;
    using t_messenger_params        = messaging::t_messenger_params;
    using r_messenger_timer_params  = messaging::r_messenger_timer_params;
    using R_messenger_timer_params  = messaging::R_messenger_timer_params;
    using R_messenger_create_params = messaging::R_messenger_create_params;

    t_logic(R_messenger_name, R_messenger_create_params);
    virtual ~t_logic();

    t_logic(R_logic)           = delete;
    t_logic(x_logic)           = delete;
    r_logic operator=(R_logic) = delete;
    r_logic operator=(x_logic) = delete;

    operator t_validity() const;

    t_tracer&        get_trace (t_err) const;
    t_messenger_name get_name  (t_err) const;
    t_key            get_key   () const;
    t_bool           get_params(t_err, r_messenger_params) const;
    t_void           get_stats (t_err, r_stats, t_bool reset = false);

///////////////////////////////////////////////////////////////////////////////

    t_void post_message(t_err, R_messenger_key, r_message) const;

///////////////////////////////////////////////////////////////////////////////

    t_void update_scope       (t_err, t_messenger_scope);
    t_void update_alive_period(t_err, t_multiple_of_100ms);

///////////////////////////////////////////////////////////////////////////////

    t_void start_message_timer(t_errr, R_message_timer_params);
    t_void stop_message_timer (t_err);
    t_void query_message_timer(t_err, r_message_timer_params) const;

///////////////////////////////////////////////////////////////////////////////

    t_void add_monitor(t_err, R_messenger_name,
                              t_messenger_prio = t_messenger_prio(0),
                              t_messenger_user = t_messenger_user());
    t_void remove_monitor(t_err, R_messenger_name, p_messenger_user = nullptr);
    t_messenger_key is_monitored(t_err, R_messenger_name,
                                        p_messenger_user = nullptr) const;
    t_void get_monitored(t_err, r_messenger_memberkeylist) const;

///////////////////////////////////////////////////////////////////////////////

    t_void add_to_group(t_err, R_password, R_messenger_name group,
                               t_messenger_prio = t_messenger_prio(0),
                               t_messenger_user = t_messenger_user());
    t_void remove_from_group(t_err, R_password, R_messenger_name,
                                    p_messenger_user = nullptr);
    t_bool is_in_group(t_err, R_messenger_name,
                              p_messenger_user = nullptr) const;
    t_void get_groups(t_err, r_messenger_memberlist) const;

///////////////////////////////////////////////////////////////////////////////

    t_void create_group (t_err, R_password, R_messenger_name,
                                t_messenger_scope);
    t_void destroy_group(t_err, R_password, R_messenger_name);
    t_void fetch_group  (t_err, R_messenger_name, r_messenger_scope,
                                messenger_memberlist_t* = 0);

///////////////////////////////////////////////////////////////////////////////

    t_bool add_another_to_group(t_err, R_password,
                                       R_messenger_name name,
                                       R_messenger_name group,
                                       t_messenger_prio = t_messenger_prio(0),
                                       t_messenger_user = t_messenger_user());
    t_bool remove_another_from_group(t_err, R_password,
                                            R_messenger_name,
                                            R_messenger_name group,
                                            p_messenger_user = nullptr);
    t_bool is_another_in_group(t_err, R_messenger_name,
                                      R_messenger_name group,
                                      p_messenger_user = nullptr);

///////////////////////////////////////////////////////////////////////////////

    t_multiple_of_1ms get_max_wait() const;
    t_void            set_max_wait(t_multiple_of_1ms);

///////////////////////////////////////////////////////////////////////////////

    t_void   register_message_logic(t_err, R_message_id, R_label,
                                           p_message_logic);
    p_message_logic unregister_message_logic(t_err, R_label);
    p_message_logic is_message_logic_registered(t_err, R_label) const;

///////////////////////////////////////////////////////////////////////////////

    t_bool add_event_monitor   (t_err, t_fd, R_label, t_messenger_user);
    t_bool remove_event_monitor(t_err, t_fd, p_label = nullptr,
                                       p_messenger_user = nullptr);
    t_bool is_event_monitored  (t_err, t_fd, p_label = nullptr,
                                       p_messenger_user = nullptr);

///////////////////////////////////////////////////////////////////////////////

   // timer services
   // name

///////////////////////////////////////////////////////////////////////////////

    virtual t_void process_wakeup(t_nsec elapsed, t_bool maxwait) = 0;
    virtual t_void process_notify(t_messenger_state,
                                  R_messenger_name,
                                  R_messenger_key,
                                  t_messenger_prio,
                                  t_messenger_user) = 0;
    virtual t_void process_user(x_message) = 0;
    virtual t_void process_bad (x_message) = 0;
    virtual t_void process_timeout(t_bool periodic,
                                   t_multiple_of_100ms,
                                   R_messenger_key,
                                   t_messenger_prio,
                                   t_messenger_user) = 0;
    virtual t_void process_failed(errorid_t, x_message) = 0;
    virtual t_void process_event(t_fd, R_label, t_messenger_user) = 0;

///////////////////////////////////////////////////////////////////////////////

  private:
    friend class t_impl_;
    p_impl_ impl_;
  };

///////////////////////////////////////////////////////////////////////////////

  class t_sandbox;
  using r_sandbox = t_prefix<t_sandbox>::r_;
  using x_sandbox = t_prefix<t_sandbox>::x_;
  using R_sandbox = t_prefix<t_sandbox>::R_;

  class t_sandbox {
  public:
     t_sandbox(R_name, t_passable_ptr<t_logic>);
     t_sandbox(R_sandbox) = delete;
     t_sandbox(x_sandbox) = delete;

     r_sandbox operator=(R_sandbox) = delete;
     r_sandbox operator=(x_sandbox) = delete;

  private:
     t_thread thread_;
  };

///////////////////////////////////////////////////////////////////////////////
}
}

#endif
