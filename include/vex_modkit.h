/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2018, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_modkit.h                                                */
/*    Author:     James Pearman                                               */
/*    Created:    28 March 2018                                               */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VCS_VEX_MODKIT_H
#define   VCS_VEX_MODKIT_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_modkit.h
  * @brief   Wrap some of the VCS classes to allow modkit events to work
*//*---------------------------------------------------------------------------*/

// private api needed by modkit build
#ifdef __cplusplus
extern "C" {
#endif
// callback on 1mS interrupt
void vexSystemTimerCallbackInstall( void (*callback)(void) );
// task sleep
void vexTaskSleep( uint32_t time );
#ifdef __cplusplus
}
#endif

//
// All VCS blocks related classes and variables are now in this single file
//
//

namespace vex { 
  namespace modkit {
    // Globals
    percentUnits        percent      = vex::percentUnits::pct;
    timeUnits           seconds      = vex::timeUnits::sec;
    timeUnits           milliseconds = vex::timeUnits::msec;
    currentUnits        amps         = vex::currentUnits::amp;
    powerUnits          watts        = vex::powerUnits::watt;
    torqueUnits         newtonMeters = vex::torqueUnits::Nm;
    torqueUnits         inchPounds   = vex::torqueUnits::InLb;
    rotationUnits       degrees      = vex::rotationUnits::deg;
    rotationUnits       revolutions  = vex::rotationUnits::rev;
    velocityUnits       rpm          = vex::velocityUnits::rpm;

    distanceUnits       milimeters   = vex::distanceUnits::mm;
    distanceUnits       inches       = vex::distanceUnits::in;
    distanceUnits       centimeters  = vex::distanceUnits::cm;

    directionType       forward      = vex::directionType::fwd;
    directionType       reverse      = vex::directionType::rev;
    brakeType           coast        = vex::brakeType::coast;
    brakeType           brake        = vex::brakeType::brake;
    brakeType           hold         = vex::brakeType::hold;

    const color         &black       = vex::black;
    const color         &white       = vex::white;
    const color         &red         = vex::red;
    const color         &green       = vex::green;
    const color         &blue        = vex::blue;
    const color         &yellow      = vex::yellow;
    const color         &orange      = vex::orange;
    const color         &purple      = vex::purple;
    const color         &cyan        = vex::cyan;
    const color         &transparent = vex::transparent;

    fontType            mono12       = vex::fontType::mono12;
    fontType            mono15       = vex::fontType::mono15;
    fontType            mono20       = vex::fontType::mono20;
    fontType            mono30       = vex::fontType::mono30;
    fontType            mono40       = vex::fontType::mono40;
    fontType            mono60       = vex::fontType::mono60;
    fontType            prop20       = vex::fontType::prop20;
    fontType            prop30       = vex::fontType::prop30;
    fontType            prop40       = vex::fontType::prop40;
    fontType            prop60       = vex::fontType::prop60;
    
    /**
     * @brief controller class
     */
    class controller : public ::vex::controller {
      private:
        static void eventHandler(void *arg) {
          if( arg == NULL)
            return;
          
          controller *instance = static_cast<controller *>(arg);
        
          instance->ButtonL1.eventHandler();
          instance->ButtonL2.eventHandler();
          instance->ButtonR1.eventHandler();
          instance->ButtonR2.eventHandler();
          instance->ButtonUp.eventHandler();
          instance->ButtonDown.eventHandler();
          instance->ButtonLeft.eventHandler();
          instance->ButtonRight.eventHandler();
          instance->ButtonA.eventHandler();
          instance->ButtonB.eventHandler();
          instance->ButtonX.eventHandler();
          instance->ButtonY.eventHandler();
          instance->Axis1.eventHandler();
          instance->Axis2.eventHandler();
          instance->Axis3.eventHandler();
          instance->Axis4.eventHandler();
        }
        
      public:
        controller() : controller( controllerType::primary ) {
        };
        controller( controllerType id ) : ::vex::controller(id) {
          vex::event::init( this->_getIndex(), 0xFFFFFFFF, eventHandler, static_cast<void *>(this) );
        };
        ~controller() {};

        class button {
          friend class controller;

          private:
            vex::controller::button  &_button;

            void eventHandler() {
              if( _button.PRESSED )
                PRESSED.triggerEvent();
              if( _button.RELEASED )
                RELEASED.triggerEvent();      
            }

            button( ::vex::controller::button& b ) : _button(b) {};
            ~button() {};
                              
          public:
            /*
             * @prog_lang{block}
             * @brief Event that fires when the button is pressed.
             */
            MODKIT_IO_Event PRESSED  = MODKIT_IO_Event();
            /*
             * @prog_lang{block}
             * @brief Event that fires when the button is released.
             */
            MODKIT_IO_Event RELEASED = MODKIT_IO_Event();

            bool     pressing() { return( _button.pressing() ); };        
        };
              
        button  ButtonL1    = button( ::vex::controller::ButtonL1    );
        button  ButtonL2    = button( ::vex::controller::ButtonL2    );
        button  ButtonR1    = button( ::vex::controller::ButtonR1    );
        button  ButtonR2    = button( ::vex::controller::ButtonR2    );
        button  ButtonUp    = button( ::vex::controller::ButtonUp    );
        button  ButtonDown  = button( ::vex::controller::ButtonDown  );
        button  ButtonLeft  = button( ::vex::controller::ButtonLeft  );
        button  ButtonRight = button( ::vex::controller::ButtonRight );
        button  ButtonA     = button( ::vex::controller::ButtonA     );
        button  ButtonB     = button( ::vex::controller::ButtonB     );
        button  ButtonX     = button( ::vex::controller::ButtonX     );
        button  ButtonY     = button( ::vex::controller::ButtonY     );      
      
        class axis  {
          friend class controller;

          private:
            vex::controller::axis  &_axis;
          
            void eventHandler() {
              if( _axis.CHANGED )
                CHANGED.triggerEvent();
            }

            axis( ::vex::controller::axis& j ) : _axis(j) {};
            ~axis() {};
          
          public:
            /*
             * @prog_lang{block}
             * @brief Event that fires when the axis value changes.
             */
            MODKIT_IO_Event CHANGED  = MODKIT_IO_Event();        

            int32_t  value() { return( _axis.value() ); };        
            int32_t  position( percentUnits units ) { return( _axis.position(units) ); };       
        };      

        axis     Axis1      = axis( ::vex::controller::Axis1 );
        axis     Axis2      = axis( ::vex::controller::Axis2 );
        axis     Axis3      = axis( ::vex::controller::Axis3 );
        axis     Axis4      = axis( ::vex::controller::Axis4 );
    };

/*-----------------------------------------------------------------------------*/

    /**
     * @brief triport class
     */
    class triport : public ::vex::triport {
      private:
        // Something changed on the triport
        static void eventHandler(void *arg) {
          if( arg == NULL)
            return;
          
          triport *instance = static_cast<triport *>(arg);
        
          instance->A.eventHandler();
          instance->B.eventHandler();
          instance->C.eventHandler();
          instance->D.eventHandler();
          instance->E.eventHandler();
          instance->F.eventHandler();
          instance->G.eventHandler();
          instance->H.eventHandler();
        }
    
      public:
        triport( int32_t index ) : ::vex::triport( index ) {
          vex::event::init( index, 0xFFFFFFFF, eventHandler, static_cast<void *>(this) );
        };
        ~triport() {};

        template <typename... Args>
        triport( int32_t index, Args... args) : ::vex::triport( index, args... ) {}

        class port : public ::vex::triport::port {
          friend class triport;

          private:
            void eventHandler() {
              if( ::vex::triport::port::PRESSED )
                PRESSED.triggerEvent();
              if( ::vex::triport::port::RELEASED )
                RELEASED.triggerEvent();
              if( ::vex::triport::port::CHANGED )
                CHANGED.triggerEvent();
            }
                    
          public:
            port( const int32_t id, triport *parent ) : ::vex::triport::port( id, parent ) {};
            ~port() {};
           /*
             * @prog_lang{block}
             * @brief Event that fires when the port is pressed.
             */
            MODKIT_IO_Event PRESSED  = MODKIT_IO_Event();
             /*
             * @prog_lang{block}
             * @brief Event that fires when the port is released.
             */
            MODKIT_IO_Event RELEASED = MODKIT_IO_Event();
             /*
             * @prog_lang{block}
             * @brief Event that fires when the port has changed.
             */
            MODKIT_IO_Event CHANGED  = MODKIT_IO_Event();
             /*
             * @prog_lang{block}
             * @brief Event that fires when the port is high.
             */
            MODKIT_IO_Event &HIGH    = PRESSED;
             /*
             * @prog_lang{block}
             * @brief Event that fires when the port is low.
             */
            MODKIT_IO_Event &LOW     = RELEASED;
        };
      
        port  A = port(0, this);
        port  B = port(1, this);
        port  C = port(2, this);
        port  D = port(3, this);
        port  E = port(4, this);
        port  F = port(5, this);
        port  G = port(6, this);
        port  H = port(7, this);
    };

/*-----------------------------------------------------------------------------*/
  
    /**
     * @brief brain class
     */
    class brain : public ::vex::brain {
      private:
        // Something changed on the brain
        static void eventHandler(void *arg) {
          if( arg == NULL)
            return;
          
          brain *instance = static_cast<brain *>(arg);
        
          instance->Screen.eventHandler();
        }
 
      public:
        brain() : ::vex::brain() {
          vex::event::init( this->_getIndex(), 0xFFFFFFFF, eventHandler, static_cast<void *>(this) );
        };
        ~brain() {};


        class lcd : public ::vex::brain::lcd {
          friend class brain;

          private:
            void eventHandler() {
              if( ::vex::brain::lcd::PRESSED )
                PRESSED.triggerEvent();
              if( ::vex::brain::lcd::RELEASED )
                RELEASED.triggerEvent();
            }
          
          public:
            lcd() {};
            ~lcd() {};
            /*
             * @prog_lang{block}
             * @brief Event that fires when the screen is pressed.
             */
            MODKIT_IO_Event PRESSED  = MODKIT_IO_Event();
            /*
             * @prog_lang{block}
             * @brief Event that fires when the screen is released.
             */
            MODKIT_IO_Event RELEASED = MODKIT_IO_Event();
        };
      
        public:
          // Brain has an instance of the lcd
          lcd         Screen;
          // backwards compatibility
          lcd         &LCD = Screen;      
  
          // Brain has an instance of the internal triport
          triport     ThreeWirePort = vex::modkit::triport( PORT22 );
    };

/*-----------------------------------------------------------------------------*/

    /**
     * @brief competition class
     */
    class competition : public ::vex::competition {
      private:
        static void eventHandler(void *arg) {
          if( arg == NULL)
            return;
          
          competition *instance = static_cast<competition *>(arg);
        
          instance->eventHandler();
        }

        void eventHandler() {
          if( ::vex::competition::PRE_AUTONOMOUS )
            STARTED_PRE_AUTONOMOUS.triggerEvent();
          if( ::vex::competition::AUTONOMOUS )
            STARTED_AUTONOMOUS.triggerEvent();
          if( ::vex::competition::DRIVER_CONTROL )
            STARTED_DRIVER_CONTROL.triggerEvent();
          if( ::vex::competition::DISABLED )
            DISABLED.triggerEvent();
        }
                  
      public:
        competition() : ::vex::competition() {
          vex::event::init( this->_getIndex(), 0xFFFFFFFF, eventHandler, static_cast<void *>(this) );
        };
        ~competition() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the pre autonomous period starts.
         */
        MODKIT_IO_Event   STARTED_PRE_AUTONOMOUS = MODKIT_IO_Event();
        /*
         * @prog_lang{block}
         * @brief Event that fires when the autonomous period starts.
         */      
        MODKIT_IO_Event   STARTED_AUTONOMOUS     = MODKIT_IO_Event();
        /*
         * @prog_lang{block}
         * @brief Event that fires when the driver control period starts.
         */
        MODKIT_IO_Event   STARTED_DRIVER_CONTROL = MODKIT_IO_Event();
        /*
         * @prog_lang{block}
         * @brief Event that fires when the control system is disabled.
         */
        MODKIT_IO_Event   DISABLED               = MODKIT_IO_Event();
    };
       
    /**
     * @brief limit switch class
     */
    class limit : public ::vex::limit {
      private:
        modkit::triport::port &_port;
      
      public:
        limit( modkit::triport::port &port ) : ::vex::limit( port ), _port(port) {};
        ~limit() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the limit switch is pressed.
         */
        MODKIT_IO_Event &PRESSED  = _port.PRESSED;
        /*
         * @prog_lang{block}
         * @brief Event that fires when the limit switch is released.
         */
        MODKIT_IO_Event &RELEASED = _port.RELEASED;
    };

    /**
     * @brief bumper switch class
     */
    class bumper : public ::vex::bumper {
      private:
        modkit::triport::port &_port;
      
      public:
        bumper( modkit::triport::port &port ) : ::vex::bumper( port ), _port(port) {};
        ~bumper() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the bumper switch is pressed.
         */
        MODKIT_IO_Event &PRESSED  = _port.PRESSED;
        /*
         * @prog_lang{block}
         * @brief Event that fires when the bumper switch is released.
         */
        MODKIT_IO_Event &RELEASED = _port.RELEASED;
    };  

/*-----------------------------------------------------------------------------*/
  
    /**
     * @brief digital input class
     */
    class digital_in : public ::vex::digital_in {
      private:
        modkit::triport::port &_port;
      
      public:
        digital_in( modkit::triport::port &port ) : ::vex::digital_in( port ), _port(port) {};
        ~digital_in() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the digital in device is high.
         */
        MODKIT_IO_Event &HIGH  = _port.HIGH;
        /*
         * @prog_lang{block}
         * @brief Event that fires when the digital in device is low.
         */
        MODKIT_IO_Event &LOW   = _port.LOW;
    };


    /**
     * @brief digital output class
     */
    class digital_out : public ::vex::digital_out {
      public:
        digital_out( modkit::triport::port &port ) : ::vex::digital_out( port ) {};
        ~digital_out() {};
    };

    /**
     * @brief potentiometer class
     */
    class pot : public ::vex::pot {
      private:
        modkit::triport::port &_port;
      
      public:
        pot( modkit::triport::port &port ) : ::vex::pot( port ), _port(port) {};
        ~pot() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the pot device's value has changed.
         */
        MODKIT_IO_Event &CHANGED  = _port.CHANGED;
    };
    
    /**
     * @brief line sensor class
     */
    class line : public ::vex::line {
      private:
        modkit::triport::port &_port;
    
      public:
        line( modkit::triport::port &port ) : ::vex::line( port ), _port(port) {};
        ~line() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the line value has changed.
         */
        MODKIT_IO_Event &CHANGED  = _port.CHANGED;
    };

    /**
     * @brief light sensor class
     */
    class light : public ::vex::light {
      private:
        modkit::triport::port &_port;
  
      public:
        light( modkit::triport::port &port ) : ::vex::light( port ), _port(port) {};
        ~light() {};

        /*
         * @prog_lang{block}
         * @brief Event that fires when the light value has changed.
         */
        MODKIT_IO_Event &CHANGED  = _port.CHANGED;
    };  
    
    /**
     * @brief gyro class
     */
    class gyro : public ::vex::gyro {
      private:
        modkit::triport::port &_port;
  
      public:
        gyro( modkit::triport::port &port ) : ::vex::gyro( port ), _port(port) {};
        ~gyro() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the gyro value has changed.
         */
        MODKIT_IO_Event &CHANGED  = _port.CHANGED;
    };    

    /**
     * @brief accelerometer class
     */
    class accelerometer : public ::vex::accelerometer {
      private:
        modkit::triport::port &_port;
  
      public:
        accelerometer( modkit::triport::port &port ) : ::vex::accelerometer( port ), _port(port) {};
        ~accelerometer() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the accelerometer value has changed.
         */
        MODKIT_IO_Event &CHANGED  = _port.CHANGED;
    };
  
    /**
     * @brief analog input class
     */
    class analog_in : public ::vex::analog_in {
      private:
        modkit::triport::port &_port;
  
      public:
        analog_in( modkit::triport::port &port ) : ::vex::analog_in( port ), _port(port) {};
        ~analog_in() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the analog in device's value has changed.
         */
        MODKIT_IO_Event &CHANGED  = _port.CHANGED;
    };

    /**
     * @brief encoder class
     */
    class encoder : public ::vex::encoder {
      private:
        modkit::triport::port &_port;
  
      public:
        encoder( modkit::triport::port &port ) : ::vex::encoder( port ), _port(port) {};
        ~encoder() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the encoder value has changed.
         */
        MODKIT_IO_Event &CHANGED  = _port.CHANGED;
    };

    /**
     * @brief sonar class
     */
    class sonar : public ::vex::sonar {
      private:
        modkit::triport::port &_port;
  
      public:
        sonar( modkit::triport::port &port ) : ::vex::sonar( port ), _port(port) {};
        ~sonar() {};
        /*
         * @prog_lang{block}
         * @brief Event that fires when the sonar value has changed.
         */
        MODKIT_IO_Event &CHANGED  = _port.CHANGED;
    };

    /**
     * @brief pwm output class
     */
    class pwm_out : public ::vex::pwm_out {
      public:
        pwm_out( modkit::triport::port &port ) : ::vex::pwm_out( port ) {};
        ~pwm_out() {};
    };

    /**
     * @brief servo class
     */
    class servo : public ::vex::servo {
      public:
        servo( modkit::triport::port &port ) : ::vex::servo( port ) {};
        ~servo() {};
    };
  
    /**
     * @brief mc29 motor class
     */
    class motor29 : public ::vex::motor29 {
      public:
        motor29( modkit::triport::port &port ) : ::vex::motor29( port ) {};
        ~motor29() {};
    };

    /**
     * @brief victor controller motor class
     */
    class motor_victor : public ::vex::motor_victor {
      public:
        motor_victor( modkit::triport::port &port ) : ::vex::motor_victor( port ) {};
        ~motor_victor() {};
    };
  
  
  };  // END modkit namespace
};  // END vex namespace

#endif // VCS_VEX_MODKIT_H
