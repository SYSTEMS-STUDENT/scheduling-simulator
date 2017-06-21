#pragma once
#include "../scheduler.hh"
#include <map>
#include <list>
#include <utility>
#include <memory>

namespace scheduler_simulator {

class Options;

class SchedulerRM : public Scheduler {
  public:
    SchedulerRM (Options*);
    virtual ~SchedulerRM () override = default;

    //! Schedule the next process or check violation of deadline
    virtual bool schedule() override;

    //! Wether there is any proccess to be executed or end time
    //! reached.
    virtual bool is_next() override;

  private:
    void initialize();
    void schedule_proc();

    //! Process abstraction
    struct Proc {
      int id = 0;
      int period = 0;
      int cpu_time = 0;
      int last_scheduled_time = 0;
      int consumed_cpu = 0;
    };

    //! Process ready list
    std::list<std::shared_ptr<Proc>> ready_list;

    //! Process list (Where the go after termination)
    std::list<std::shared_ptr<Proc>> proc_list;

    //! Current scheduled process
    std::shared_ptr<Proc> scheduled_proc;

    uint32_t end_time = 0;
    bool deadly_end = false;
};

}
