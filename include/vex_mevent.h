/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_mevent.h                                                */
/*    Author:     James Pearman                                               */
/*    Created:    25 Jan 2018                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VCS_MEVENT_CLASS_H
#define   VCS_MEVENT_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_mevent.h
  * @brief   V5 modlang event class header
*//*---------------------------------------------------------------------------*/

namespace vex {
    class mevent {
        private:
          int   _event_id;
          int   _index;
          
        public:
          mevent() : _event_id(-1) {};
          mevent( uint32_t index, uint32_t id );
          ~mevent() {};
                    
          operator int();
          operator bool();
    };
}

#endif // VCS_MEVENT_CLASS_H