clang++ -pg -O0 -ggdb3 -std=c++17 -Wextra -Wall -Wpedantic -o run example.cpp dainty_sandbox.cpp dainty_sandbox_err.cpp ../library/oops/dainty_oops.cpp ../library/container/dainty_container_err.cpp ../library/container/dainty_container_bytebuf_impl.cpp ../library/container/dainty_container_any.cpp ../library/named/dainty_named_assert.cpp ../library/named/dainty_named_string_impl.cpp ../library/named/dainty_named_range.cpp ../library/os/dainty_os_call.cpp ../library/os/dainty_os_networking.cpp ../library/os/dainty_os_err.cpp ../library/os/dainty_os_threading.cpp ../library/os/dainty_os_clock.cpp ../library/os/dainty_os.cpp ../library/os/dainty_os_scheduling.cpp ../library/os/dainty_os_fdbased.cpp ../library/mt/dainty_mt_waitable_chained_queue.cpp ../library/mt/dainty_mt_condvar_command.cpp ../library/mt/dainty_mt_condvar_timed_event.cpp ../library/mt/dainty_mt_condvar_chained_queue.cpp ../library/mt/dainty_mt_thread.cpp ../library/mt/dainty_mt_event_dispatcher.cpp ../library/mt/dainty_mt_chained_queue.cpp ../library/mt/dainty_mt_condvar_notify_change.cpp ../library/mt/dainty_mt_detached_thread.cpp ../library/mt/dainty_mt_event.cpp ../library/mt/dainty_mt_command.cpp ../library/mt/dainty_mt_notify_change.cpp ../library/mt/dainty_mt_err.cpp ../library/mt/dainty_mt_condvar_event.cpp  ../service/tracing/dainty_tracing_err.cpp ../service/tracing/dainty_tracing.cpp ../service/messaging/dainty_messaging_err.cpp ../service/messaging/dainty_messaging.cpp -I../library/named -I../library/oops/ -I../library/os -I../library/container -I../library/mt -I../library/os -I../library/state -I../library/dacli -I../service/messaging -I../service/tracing -pthread
