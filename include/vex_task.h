/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Robomatter 2016, All rights reserved.                     */
/*                                                                            */
/*    Module:     task.h                                                      */
/*    Author:     James Pearman                                               */
/*    Created:    22 Nov 2016                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VCS_TASK_CLASS_H
#define   VCS_TASK_CLASS_H

// In case we have ROBOTC definitions
#ifdef task
#undef task
#endif

/*-----------------------------------------------------------------------------*/
/** @file    task.h
  * @brief   Header for task control class
*//*---------------------------------------------------------------------------*/

namespace vex {
  /** 
    * @prog_lang{cpp|pro}
    * @brief Use this class to create and control tasks.
  */
  class task  {
    private:
      static  int   _labelId;
      int          (* _callback)(void);
        
    protected:
    
    public:
      task();
      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::task Task = vex::task(callbackFunction);}
      * @brief Constructs a task with a function callback.
      * @param callback A reference to a function.
      */
      task( int (* callback)(void) );
      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::task Task = vex::task(callbackFunction, 1);}
      * @brief Constructs a task with a function callback and a priority.
      * @param callback A reference to a function.
      * @param priority Sets the priority of the task.
      */
      task( int (* callback)(void), int32_t priority );
      ~task();

      // act on another task
      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{Task.stop(task1);}
      * @brief Stops the specified task.
      * @param t The task to be stopped.
      */
      void        stop( task &t );

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{Task.suspend(task1);}
      * @brief Suspends the specified task for later use.
      * @param t The task to be suspended.
      */
      void        suspend( task &t );

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{Task.resume(task1);}
      * @brief Resumes a specified task that has been suspended or stopped.
      * @param t The task to be resumed.
      */
      void        resume( task &t );

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{Task.priority(task1)}
      * @brief Gets the priority of a task.
      * @return Returns an integer that represents the current priority of the specified task.
      * @param t The task to get priority of.
      */
      int32_t     priority( task &t ) ;

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{Task.setPriority(task1,priority);}
      * @brief Sets the priority of the specified task to the specified priority.
      * @param t The task to set the priority on.
      * @param priority The priority level of a task.
      */
      void        setPriority( task &t, int32_t priority ) ;

      // these act on this task
      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{action}
      * @block_sig{Task.stop();}
      * @brief Stops the task.
      */
      void        stop();

      /**
      * @prog_lang{pro}
      * @drawer_cat{action}
      * @block_sig{Task.suspend();}
      * @brief Suspends the task until the task is told to resume.
      */
      void        suspend();

      /**
      * @prog_lang{pro}
      * @drawer_cat{action}
      * @block_sig{Task.resume();}
      * @brief Resumes the previously suspended task.
      */
      void        resume();

      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{sensing}
      * @block_sig{Task.priority()}
      * @brief Gets the priority of the task.
      * @return Returns an integer that represents the priority of the task.
      */
      int32_t     priority();

      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{action}
      * @block_sig{Task.setPriority(1);}
      * @brief Sets the priority of the task specified by the parameter.
      * @param priority The priority level of the task.
      */
      void        setPriority( int32_t priority );

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{Task.index()}
      * @brief Gets the task's index.
      * @return Returns an integer that represents the index of the task.
      */
      int32_t     index( void );


      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{action}
      * @block_sig{vex::task::sleep(1000);}
      * @brief Sets the task to sleep for the specified amount of time (in milliseconds).
      * @param time The number of milliseconds for the task to sleep.
      */
      static void sleep( uint32_t time );

      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{action}
      * @block_sig{vex::task::yield();}
      * @brief Suspends the enumerator and gives up control to the enumerating method. A breaking point in a task.
      */
      static void yield();

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      */
      static void dump();


      // also on another task
      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{action}
      * @block_sig{vex::task::stop(callbackFunction);}
      * @brief Stops the task of the passed in function.
      * @param callback A reference to a function. 
      */
      static void stop( int (* callback)(void) );      
  };
};

namespace vex {
  /**
    * @prog_lang{pro} 
    * @brief Use this class to synchronize access to resources.
  */
  class semaphore  {
    private:
      static  bool   _initialized;
      uint32_t       _sem;
        
    protected:
    
    public:
      semaphore();
      ~semaphore();
      

      /**
      * @prog_lang{pro}
      * @drawer_cat{none}
      * @block_sig{Semaphore.lock();}
      * @brief Attempts to lock the semaphore. If the semaphore is previously locked, it will block until the semaphore is unlocked.
      */
      void        lock();

      /**
      * @prog_lang{pro}
      * @drawer_cat{none}
      * @block_sig{Semaphore.lock(300);}
      * @brief Attempts to lock the semaphore. If the semaphore is previously locked, it will block until the timeout has expired or the semaphore is unlocked.
      * @param time The amount of time to wait for the semaphore to be unlocked in milliseconds.
      */
      void        lock( uint32_t time );

      /**
      * @prog_lang{pro}
      * @drawer_cat{none}
      * @block_sig{Semaphore.unlock();}
      * @brief Unlocks a locked semaphore.
      */
      void        unlock();

      /**
      * @prog_lang{pro}
      * @drawer_cat{none}
      * @block_sig{Semaphore.owner()}
      * @brief Checks to see if the semaphore is locked by the current task.
      * @return Returns a true Boolean if the semaphore is locked by the current task.
      */
      bool        owner();      
  };
};

#endif // VCS_TASK_CLASS_H
