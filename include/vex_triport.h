/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Robomatter 2017, All rights reserved.                     */
/*                                                                            */
/*    Module:     vex_triport.h                                               */
/*    Author:     James Pearman                                               */
/*    Created:    10 Jan 2018                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/** @file    vex_triport.h
  * @brief   Triport device class header
*//*---------------------------------------------------------------------------*/

#ifndef   VCS_TRIPORT_CLASS_H
#define   VCS_TRIPORT_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @brief Triport device class                                                */
/*-----------------------------------------------------------------------------*/
namespace vex {
  /** 
    * @prog_lang{none}
    * @brief Use this class to get and set information about devices on 3-wire ports.
  */
  class triport : public device {
    public:
      enum class tEventType {
        EVENT_DIN_HIGH        =  0,
        EVENT_DIN_LOW         =  1,
        EVENT_AIN_CHANGED     =  2
      };

    private:
      uint32_t _id = 0;

      void _setport() {};
      void _configPort( uint32_t id, triportType type );
    
      template <typename first, typename... Args>
      void _setport( first port, Args... args ) {
        _configPort( _id++, port );
        _setport( args... );
      }

      int32_t _getIndex();

      // conversion from vcs enum to C API
      V5_AdiPortConfiguration   _internalType( triportType type );
      triportType               _externalType( V5_AdiPortConfiguration type );
        
    public:
      triport( int32_t index );  
      ~triport();

      template <typename... Args>
      triport( int32_t index, Args... args) : triport(index) {
        _setport( args... );
      }
      /**
       * @prog_lang{none}
       * @drawer_cat{none}
       * @brief Gets the status of what is installed on the port.
       * @return Returns true if a 3-Wire Port device is installed in the port, otherwise false.
       */
      bool            installed();
     
      /** 
        * @prog_lang{none}
        * @brief Use this class to get access to port functions and members.
      */
      class port {
        friend class __tridevice;

        private:
          int32_t   _id;
          triportType _type;
          triport   *_parent;
          int32_t   _convertAnalog( analogUnits units );
          
        public:
          port() : _id( -1 ), _type(triportType::digitalInput), _parent(NULL) {};
          port( const int32_t id, triport *parent );
          port( const int32_t id, const triportType type, triport *parent );
          ~port() {};          
          
          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Sets the port to a specific port type.
           * @param type A type of port that you want to set it to.
           */
          void type( const triportType type );

          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Gets the current port type.
           * @return Returns the Port Type.
           */
          triportType type();

          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Sets the port's value to the specified integer in the parameter. 
           * @param value An integer number that will be set to the port's value.
           */
          void      value( int32_t value );

          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Gets the value of a port.
           * @return Returns an integer that represents the port's value.
           */
          int32_t   value();

          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Sets the value of the port to a Boolean value.
           * @param value A true or false Boolean value that the port will be set to.
           */
          void      set( bool value );


          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Calls back a function when the port is pressed.
           * @param callback A reference to a function.
           */
          void     pressed( void (* callback)(void) );

          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Calls back a function when the port is released.
           * @param callback A reference to a function.
           */
          void     released( void (* callback)(void) );

          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Calls back a function when the port has changed value.
           * @param callback A reference to a function.
           */
          void     changed( void (* callback)(void) );

               
          void operator()( const triportType type ) {
            this->type( type );
          }
          void operator=( const int32_t value )  {
            this->value( value );
          }
          operator int()  {
            return this->value();
          }          
          operator bool()  {
            return (this->value() > 0) ? true : false;
          }          

          // encoder specific
          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Resets the rotation of the encoder to zero.
           */
          void    resetRotation( void );

          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Sets the rotation of the encoder to a specific value.
           * @param val A double that represents the value to set the rotation to.
           * @param units The unit type that the previous value should be treated as.
           */
          void    setRotation( double val, rotationUnits units );

          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Gets the rotation value of the encoder.
           * @return Returns a double that represents the current rotation of the encoder.
           * @param units A unit type that defines what value of rotation that should be returned.
           */
          double  rotation( rotationUnits units );

          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Gets the velocity of the encoder.
           * @return Returns a double that represents the current velocity of the encoder.
           * @param units A unit type that defines what value of velocity that should be returned.
           */
          double  velocity( velocityUnits units );

          /**
           * @prog_lang{none}
           * @drawer_cat{none}
           * @brief Gets the value of the distance sensor.
           * @return Returns a double that represents the current distance of the sensor.
           * @param units A distance unit type that defines what value of distance that should be returned. 
           */
          double  distance( distanceUnits units );

          mevent  PRESSED   = { (uint32_t)_parent->_getIndex(), ((uint32_t)tEventType::EVENT_DIN_HIGH    + (_id<<2)) };
          mevent  RELEASED  = { (uint32_t)_parent->_getIndex(), ((uint32_t)tEventType::EVENT_DIN_LOW     + (_id<<2)) };
          mevent  CHANGED   = { (uint32_t)_parent->_getIndex(), ((uint32_t)tEventType::EVENT_AIN_CHANGED + (_id<<2)) };
          
          mevent  &HIGH     = PRESSED;
          mevent  &LOW      = RELEASED;
      };

      // A triport device has 8 ports
      // This creates those instances and associates them with this triport
      port Port[8] = { {0, this},
                       {1, this},
                       {2, this},
                       {3, this},
                       {4, this},
                       {5, this},
                       {6, this},
                       {7, this}
                     };  
      
      // These are the public named references to those ports

      /**
       * @prog_lang{none}
       * @drawer_cat{none}
       * @brief Port type that represents Port[0].
      */               
      port  &A = Port[0];
      /**
       * @prog_lang{none}
       * @drawer_cat{none}
       * @brief Port type that represents Port[1].
      */
      port  &B = Port[1];
      /**
       * @prog_lang{none}
       * @drawer_cat{none}
       * @brief Port type that represents Port[2].
      */
      port  &C = Port[2];
      /**
       * @prog_lang{none}
       * @drawer_cat{none}
       * @brief Port type that represents Port[3].
      */
      port  &D = Port[3];
      /**
       * @prog_lang{none}
       * @drawer_cat{none}
       * @brief Port type that represents Port[4].
      */
      port  &E = Port[4];
      /**
       * @prog_lang{none}
       * @drawer_cat{none}
       * @brief Port type that represents Port[5].
      */
      port  &F = Port[5];
      /**
       * @prog_lang{none}
       * @drawer_cat{none}
       * @brief Port type that represents Port[6].
      */
      port  &G = Port[6];
      /**
       * @prog_lang{none}
       * @drawer_cat{none}
       * @brief Port type that represents Port[7].
      */
      port  &H = Port[7];
  };
  /** 
    * @prog_lang{none}
    * @brief Use this class to get access to Three Wire Port functions and members.
  */
  class __tridevice {
      friend class limit;
      friend class bumper;
      friend class digital_in;
      friend class digital_out;

      friend class pot;
      friend class line;
      friend class light;
      friend class gyro;
      friend class accelerometer;
      friend class analog_in;

      friend class encoder;
      friend class sonar;
      friend class pwm_out;
      friend class servo;
      friend class motor29;
      friend class motor_victor;

      private:
        triport::port   &_port;

        int32_t   _convertAnalog( analogUnits units );

        mevent &_PRESSED   = _port.PRESSED;
        mevent &_RELEASED  = _port.RELEASED;
        mevent &_CHANGED   = _port.CHANGED;
        mevent &_HIGH      = _port.HIGH;
        mevent &_LOW       = _port.LOW;
                
      public:
        __tridevice( triport::port &port, triportType type );
        ~__tridevice();

  };
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with the limit switch
  */
  class limit : private __tridevice {
      public:

       /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::limit Limit = vex::limit(Brain.ThreeWirePort.A);}
        * @brief Creates a new limit object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        limit( triport::port &port );
        ~limit();
        
        /**
         * @prog_lang{none}
         * @drawer_cat{none}
         * @block_sig{Limit.value()}
         * @brief Gets the value of the limit switch
         * @return Returns an integer that represents the value of the limit device.
        */
        int32_t   value();

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Limit.pressing()}
         * @brief Gets the state of the limit device.
         * @return Returns the state of the limit device. 
        */
        int32_t   pressing() { return value(); };

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Limit.pressed(pressedFunction);}
         * @brief Calls a function when the limit switch is pressed.
         * @param callback A reference to a function.
         */
        void      pressed( void (* callback)(void) );

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Limit.released(releasedFunction);}
         * @brief Calls a function when the limit switch is released.
         * @param callback A reference to a function.
         */
        void      released( void (* callback)(void) );

        operator int();
        operator bool();
        
        mevent &PRESSED   = _PRESSED;
        mevent &RELEASED  = _RELEASED;
  };
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with the bumper device
  */
  class bumper : private __tridevice {
      public:
       /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::bumper Bumper = vex::bumper(Brain.ThreeWirePort.A);}
        * @brief Creates a new bumper object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        bumper( triport::port &port );
        ~bumper();
        
        /**
         * @prog_lang{none}
         * @drawer_cat{none}
         * @block_sig{Bumper.value()}
         * @brief Gets the value of the bumper device.
         * @return Returns an integer that represents the value of the bumper device. 
         */
        int32_t   value();

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Bumper.pressing()}
         * @brief Get the pressed status of the bumper device.
         * @return Returns the state of the bumper device. If it is pressed it will return a one. If unpressed, it will return a zero.
         */
        int32_t   pressing() { return value(); };

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Bumper.pressed(pressedFunction);}
         * @brief Calls a function when the bumper switch is pressed.
         * @param callback A reference to a function.
         */
        void      pressed( void (* callback)(void) );

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Bumper.released(releasedFunction);}
         * @brief Calls a function when the bumper switch is released.
         * @param callback A reference to a function.
         */
        void      released( void (* callback)(void) );

        operator int();
        operator bool();

        mevent &PRESSED   = _PRESSED;
        mevent &RELEASED  = _RELEASED;
  };  
  /**
    * @prog_lang{block|cpp|pro} 
    * @brief Use this class when programming with a digital-in device
  */
  class digital_in : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::digital_in Digital_in = vex::digital_in(Brain.ThreeWirePort.A);}
        * @brief Creates a new digital-in object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        digital_in( triport::port &port );
        ~digital_in();
        
        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{DigitalIn.value()}
         * @brief Gets the value of the digital-in device.
         * @return Returns an integer that represents the value of the digital-in device.
         */
        int32_t   value();

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{DigitalIn.high(pressedFunction);}
         * @brief Calls a function when the digital input goes high.
         * @param callback A reference to a function.
         */
        void      high( void (* callback)(void) );

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{DigitalIn.low(releasedFunction);}
         * @brief Calls a function when the digital input goes low.
         * @param callback A reference to a function.
         */
        void      low( void (* callback)(void) );

        operator int();
        operator bool();

        // digital in needs inversion
        // ADI inverts digital inputs so switch press is seen as high
        mevent  &HIGH     = _LOW;
        mevent  &LOW      = _HIGH;
  };
  /**
    * @prog_lang{block|cpp|pro} 
    * @brief Use this class when programming with a digital-out device.
  */
  class digital_out : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::digital_out Digital_out = vex::digital_out(Brain.ThreeWirePort.A);}
        * @brief Creates a new digital-out object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        digital_out( triport::port &port );
        ~digital_out();
        
        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{DigitalOut.value()}
         * @brief Gets the value of the digital-out device.
         * @return Returns an integer that represents the value of the digital-out device.
         */
        int32_t   value();

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{action}
         * @block_sig{DigitalOut.set(true);}
         * @brief Sets the digital-out device to a Boolean value.
         * @param value A true or false Boolean value.
         */
        void      set( bool value );
        operator int();
        operator bool();

        /**
         * @prog_lang{none}
         * @drawer_cat{none}
         * @block_sig{DigitalOut.operator(1);}
         * @brief Sets the output value of the digital-out device.
         * @param value The value to set the digital-out device. Typically 1 or 0.
         */
        void operator=( const int32_t value );
  };

  // Analog sensors
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with a potentiometer.
  */
  class pot : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::pot Pot = vex::pot(Brain.ThreeWirePort.A);}
        * @brief Creates a new pot object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        pot( triport::port &port );
        ~pot();
        
        /**
         * @prog_lang{cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Pot.value(vex::analogUnits::range8bit)}
         * @brief Gets the value of the potentiometer in the units defined in the parameter.
         * @return Returns an integer that represents the unit value specified by the parameter of the potentiometer device.
         * @param units The measurement unit for the potentiometer device. 
         */
        int32_t   value( analogUnits units );

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Pot.value(percent)}
         * @cpp_sig{Pot.value(vex::percentUnit::pct)}
         * @brief Gets the value of the potentiometer in the units defined in the parameter.
         * @return Returns an integer that represents the unit value specified by the parameter of the potentiometer device.
         * @param units The measurement unit for the potentiometer device. 
         */
        int32_t   value( percentUnits units ) {
          return value( analogUnits::pct );
        };

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Pot.value(degrees)}
         * @cpp_sig{Pot.value(vex::rotationUnits::deg)}
         * @brief Gets the value of the potentiometer in the units defined in the parameter.
         * @return Returns an integer that represents the unit value specified by the parameter of the potentiometer device.
         * @param units The measurement unit for the potentiometer device.
         */
        double    value( rotationUnits units );

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Pot.changed(changedFunction);}
         * @brief Calls a function when the potentiometer value changes.
         * @param callback A reference to a function.
         */
        void      changed( void (* callback)(void) );

        mevent &CHANGED   = _CHANGED;
  };
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with a line follower.
  */  
  class line : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::line Line = vex::line(Brain.ThreeWirePort.A);}
        * @brief Creates a new line object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        line( triport::port &port );
        ~line();
        /**
         * @prog_lang{cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Line.value(vex::analogUnits::range8bit)}
         * @brief Gets the value of the line follower.
         * @return Returns an integer that represents the unit value specified by the parameter of the line follower.
         * @param units The measurement unit for the line device. 
         */
        int32_t   value( analogUnits units );

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Line.value(percent)}
         * @cpp_sig{Line.value(vex::percentUnits::pct)}
         * @brief Gets the value of the line follower.
         * @return Returns an integer that represents the unit value specified by the parameter of the line follower.
         * @param units The measurement unit for the line device. 
         */
        int32_t   value( percentUnits units ) {
          return value( analogUnits::pct );
        };

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Line.changed(changedFunction);}
         * @brief Calls a function when the line sensor value changes.
         * @param callback A reference to a function.
         */
        void      changed( void (* callback)(void) );

        mevent &CHANGED   = _CHANGED;
  };
  /**
    * @prog_lang{block|cpp|pro} 
    * @brief Use this class when programming with a light sensor.
  */  
  class light : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::light Light = vex::light(Brain.ThreeWirePort.A);}
        * @brief Creates a new light object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        light( triport::port &port );
        ~light();

        /**
         * @prog_lang{cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Light.value(vex::analogUnits::range8bit)}
         * @brief Gets the value of the light sensor.
         * @return Returns an integer that represents the unit value specified by the parameter of the light sensor.
         * @param units The measurement unit for the light device.
         */
        int32_t   value( analogUnits units );

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Light.value(percent)}
         * @cpp_sig{Light.value(vex::percentUnits::pct)}
         * @brief Gets the value of the light sensor.
         * @return Returns an integer that represents the unit value specified by the parameter of the light sensor.
         * @param units The measurement unit for the light device.
         */
        int32_t   value( percentUnits units ) {
          return value( analogUnits::pct );
        };

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Light.changed(changedFunction);}
         * @brief Calls a function when the light sensor value changes.
         * @param callback A reference to a function.
         */
        void      changed( void (* callback)(void) );

        mevent &CHANGED   = _CHANGED;
  };
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with a gyro sensor.
  */
  class gyro : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::gyro Gyro = vex::gyro(Brain.ThreeWirePort.A);}
        * @brief Creates a new gyro object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        gyro( triport::port &port );
        ~gyro();
        
        /**
         * @prog_lang{cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Gyro.value(vex::analogUnits::range8bit)}
         * @brief Gets the value of the gyro sensor.
         * @return Returns an integer that represents the unit value specified by the parameter of the gyro sensor.
         * @param units The measurement unit for the gyro device.
         */
        int32_t   value( analogUnits units );

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Gyro.value(degrees)}
         * @cpp_sig{Gyro.value(vex::rotationUnits::deg)}
         * @brief Gets the value of the gyro sensor.
         * @return Returns an integer that represents the unit value specified by the parameter of the gyro sensor.
         * @param units The measurement unit for the gyro device.
         */
        double    value( rotationUnits units );

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Gyro.value(percent)}
         * @cpp_sig{Gyro.value(vex::percentUnits::pct)}
         * @brief Gets the value of the gyro sensor.
         * @return Returns an integer that represents the unit value specified by the parameter of the gyro sensor.
         * @param units The measurement unit for the gyro device.
         */
        int32_t   value( percentUnits units ) {
          return value( analogUnits::pct );
        };

        /**
         * @prog_lang{pro}
         * @drawer_cat{action}
         * @block_sig{Gyro.startCalibration()}
         * @brief Starts recalibration of the gyro.
         * @param value (Optional) Sets the amount of calibration time.
         */
        void      startCalibration( int32_t value = 0 );

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Gyro.isCalibrating()}
         * @brief Returns true while the gyro sensor is performing a requested recalibration, changing to false once recalibration has completed.
         * @return Returns true if gyro is still calibrating.
         */
        bool      isCalibrating();
                
        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Gyro.changed(changedFunction);}
         * @brief Calls a function when the gyro sensor value changes.
         * @param callback A reference to a function.
         */
        void      changed( void (* callback)(void) );

        mevent &CHANGED   = _CHANGED;
  };
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with an accelerometer sensor.
  */  
  class accelerometer : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::accelerometer Accelerometer = vex::accelerometer(Brain.ThreeWirePort.A);}
        * @brief Creates a new accelerometer object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        accelerometer( triport::port &port );
        ~accelerometer();
        /**
         * @prog_lang{cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Accelerometer.value(vex::analogUnits::range8bit)}
         * @brief Gets the value of the accelerometer.
         * @return Returns an integer that represents the unit value specified by the parameter of the accelerometer sensor.
         * @param units The measurement unit for the accelerometer device.
         */
        int32_t   value( analogUnits units );

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Accelerometer.value(percent)}
         * @cpp_sig{Accelerometer.value(vex::percentUnits::pct)}
         * @brief Gets the value of the accelerometer.
         * @return Returns an integer that represents the unit value specified by the parameter of the accelerometer sensor.
         * @param units The measurement unit for the accelerometer device. 
         */
        int32_t   value( percentUnits units ) {
          return value( analogUnits::pct );
        };

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Accelerometer.changed(changedFunction);}
         * @brief Calls a function when the accelerometer value changes.
         * @param callback A reference to a function.
         */
        void      changed( void (* callback)(void) );

        mevent &CHANGED   = _CHANGED;
  };
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with an analog-in device.
  */    
  class analog_in : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::analog_in Analog_in = vex::analog_in(Brain.ThreeWirePort.A);}
        * @brief Creates a new analog-in object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        analog_in( triport::port &port );
        ~analog_in();
        
        /**
         * @prog_lang{cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Analog.value(vex::analogUnits::range8bit)}
         * @brief Gets the value of the analog-in device.
         * @return Returns an integer that represents the unit value specified by the parameter of the analog-in device.
         * @param units The measurement unit for the analog-in device. 
         */
        int32_t   value( analogUnits units );
        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Analog.value(percent)}
         * @cpp_sig{Analog.value(vex::percentUnits::pct)}
         * @brief Gets the value of the analog-in device.
         * @return Returns an integer that represents the unit value specified by the parameter of the analog-in device.
         * @param units The measurement unit for the analog-in device.
         */
        int32_t   value( percentUnits units ) {
          return value( analogUnits::pct );
        };

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Analog.changed(changedFunction);}
         * @brief Calls a function when the analog input value changes.
         * @param callback A reference to a function.
         */
        void      changed( void (* callback)(void) );

        mevent &CHANGED   = _CHANGED;
  };  
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with an encoder.
  */   
  class encoder : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::encoder Encoder = vex::encoder(Brain.ThreeWirePort.A);}
        * @brief Creates a new encoder object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        encoder( triport::port &port );
        ~encoder();
        
        /**
         * @prog_lang{none}
         * @drawer_cat{none}
         * @block_sig{Encoder.value()}
         * @brief Gets the value of the encoder.
         * @return Returns an integer that represents the value of the encoder device.
         */
        int32_t   value();
        operator int();
        
         /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{Encoder.resetRotation();}
           * @brief Resets the rotation of the encoder to zero.
           */
        void    resetRotation( void );

        /**
          * @prog_lang{block|cpp|pro}
          * @drawer_cat{setting}
          * @block_sig{Encoder.setRotation(90, degrees);}
          * @cpp_sig{Encoder.setRotation(90, vex::rotationUnits::deg);}
          * @brief Sets the rotation of the encoder to a specific value.
          * @param val Sets the amount of rotation.
          * @param units The measurement unit for the rotation value.
          */
        void    setRotation( double val, rotationUnits units );

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Encoder.rotation(degrees)}
         * @cpp_sig{Encoder.rotation(vex::rotationUnits::deg)}
         * @brief Gets the rotation value of the encoder.
         * @return Returns a double that represents the current rotation of the encoder.
         * @param units The measurement unit for the encoder device.
         */
        double  rotation( rotationUnits units );

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Encoder.velocity(percent)}
         * @cpp_sig{Encoder.velocity(vex::velocityUnits::rpm)}
         * @brief Gets the velocity of the encoder.
         * @return Returns a double that represents the current velocity of the encoder.
         * @param units The measurement unit for the encoder device.
         */
        double  velocity( velocityUnits units );

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Encoder.changed(changedFunction);}
         * @brief Calls a function when the encoder value changes.
         * @param callback A reference to a function.
         */
        void      changed( void (* callback)(void) );

        mevent &CHANGED   = _CHANGED;
  };
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with a sonar sensor.
  */     
  class sonar : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::sonar Sonar = vex::sonar(Brain.ThreeWirePort.A);}
        * @brief Creates a new sonar object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        sonar( triport::port &port );
        ~sonar();
        
        /**
         * @prog_lang{none}
         * @drawer_cat{none}
         * @block_sig{Sonar.value();}
         * @brief Gets the value of the distance sensor.
         * @return Returns an integer that represents the value of the sonar sensor.  
         */
        int32_t   value();
        operator int();

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{sensing}
         * @block_sig{Sonar.distance(millimeters)}
         * @cpp_sig{Sonar.distance(vex::distanceUnits::mm)}
         * @brief Gets the value of the distance sensor.
         * @return Returns an integer that represents the unit value specified by the parameter of the sonar sensor. 
         * @param units The measurement unit for the sonar device.
         */
        double  distance( distanceUnits units );

        /**
         * @prog_lang{pro}
         * @drawer_cat{sensing}
         * @block_sig{Sonar.changed(changedFunction);}
         * @brief Calls a function when the sonar value changes.
         * @param callback A reference to a function.
         */
        void      changed( void (* callback)(void) );

        mevent &CHANGED   = _CHANGED;        
  };  
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with a pwm-out device.
  */
  class pwm_out : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::pwm_out Pwm_out = pwm_out(Brain.ThreeWirePort.A);}
        * @brief Creates a new pwm-out object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        pwm_out( triport::port &port );
        ~pwm_out();
        
        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{action}
         * @block_sig{PWM.state(10, percent);}
         * @cpp_sig{PWM.state(10, vex::percentUnits::pct);}
         * @brief Sets the state of the pwm device.
         * @param value Sets the length of the pulse width.
         * @param units The measurement unit for the state value.
         */
        void state( int32_t value, percentUnits units );
  };
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with a servo device.
  */
  class servo : private __tridevice {
      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::servo Servo = vex::servo(Brain.ThreeWirePort.A);}
        * @brief Creates a new servo object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        servo( triport::port &port );
        ~servo();
        
        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{action}
         * @block_sig{Servo.position(10, percent);}
         * @cpp_sig{Servo.position(10, vex::percentUnits::pct);}
         * @brief Sets the position of the servo device.
         * @param value Sets the amount of rotation.
         * @param units The measurement unit for the rotation value.
         */
        void position( int32_t value, percentUnits units );

        /**
         * @prog_lang{cpp|pro}
         * @drawer_cat{action}
         * @block_sig{Servo.position(45, vex::rotationUnits::deg);}
         * @brief Sets the position of the servo device.
         * @param value Sets the amount of rotation.
         * @param units The measurement unit for the rotation value.
         */
        void position( double value, rotationUnits units );
  };
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming a motor connected to a motor controller 29.
  */
  class motor29 : private __tridevice {
      private:
        bool    _reversed;
        int32_t _velocity;
        bool    _spinMode;

      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::motor29 Motor = vex::motor29(Brain.ThreeWirePort.A);}
        * @brief Creates a new motor29 object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        motor29( triport::port &port );

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::motor29 Motor = vex::motor29(Brain.ThreeWirePort.A, true);}
        * @brief Creates a new motor29 object on the port specified in the parameter.
        * @param port A reference to a three wire port.
        * @param reverse Sets the reverse flag for the new motor29 object.
       */
        motor29( triport::port &port, bool reverse );
        ~motor29();
        
        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{setting}
         * @block_sig{Motor.setVelocity(50, percent);}
         * @cpp_sig{Motor.setVelocity(50, vex::percentUnits::pct);}
         * @brief Sets the velocity of the motor based on the parameters set in the command. This command will not run the motor.  Any subsequent call that does not contain a specified motor velocity will use this value.
         * @param velocity Sets the amount of velocity.
         * @param units The measurement unit of the velocity value. 
         */
        void setVelocity( double velocity, percentUnits units );

        /** 
         * @prog_lang{cpp|pro}
         * @drawer_cat{setting}
         * @block_sig{Motor.setReversed(true);}
         * @brief Sets the motor mode to "reverse", which will make motor commands spin the motor in the opposite direction.
         * @param value If set to true, the motor will spin in the reversed direction.
         */
        void setReversed( bool value );
        
        /** 
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{action}
         * @block_sig{Motor.spin(forward);}
         * @cpp_sig{Motor.spin(vex::directionType::fwd);}
         * @brief Turns the motor on, and spins it in the specified direction.
         * @param dir The direction to spin the motor.
         */
        void spin( directionType dir );

        /**
         * @prog_lang{cpp|pro}
         * @drawer_cat{action}
         * @block_sig{Motor.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm);}
         * @brief Turns on the motor and spins it in a specified direction and a specified velocity.
         * @param dir The direction to spin the motor. 
         * @param velocity Sets the amount of velocity.
         * @param units The measurement unit of the velocity value. 
        */
        void spin( directionType dir, double velocity, velocityUnits units );

        void spin( directionType dir, double velocity, percentUnits units ){
            spin( dir, velocity, static_cast<velocityUnits>(units) );
        };
        
        /** 
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{action}
         * @block_sig{Motor.stop();}
         * @brief Stops the motor using the default brake mode.
         */
        void stop( void );
  };
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming with a motor connected to a victor motor controller.
  */
  class motor_victor : private __tridevice {
      private:
        bool    _reversed;
        int32_t _velocity;
        bool    _spinMode;

      public:

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::motor_victor Motor = vex::motor_victor(Brain.ThreeWirePort.A);}
        * @brief Creates a new motor victor object on the port specified in the parameter.
        * @param port A reference to a three wire port.
       */
        motor_victor( triport::port &port );

        /**
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::motor_victor Motor = vex::motor_victor(Brain.ThreeWirePort.A);}
        * @brief Creates a new motor victor object on the port specified in the parameter.
        * @param port A reference to a three wire port.
        * @param reverse Sets the reverse flag for the new motor_victor object.
       */
        motor_victor( triport::port &port, bool reverse );
        ~motor_victor();
        
        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{setting}
         * @block_sig{Motor.setVelocity(50, percent);}
         * @cpp_sig{Motor.setVelocity(50, vex::percentUnits::pct);}
         * @brief Sets the velocity of the motor based on the parameters set in the command. This command will not run the motor.  Any subsequent call that does not contain a specified motor velocity will use this value.
         * @param velocity Sets the amount of velocity.
         * @param units The measurement unit of the velocity value. 
         */
        void setVelocity( double velocity, percentUnits units );

        /** 
         * @prog_lang{cpp|pro}
         * @drawer_cat{setting}
         * @block_sig{Motor.setReversed(true);}
         * @brief Sets the motor mode to "reverse", which will make motor commands spin the motor in the opposite direction.
         * @param value If set to true, the motor will spin in the reversed direction.
         */
        void setReversed( bool value );
        
        /** 
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{action}
         * @block_sig{Motor.spin(forward);}
         * @cpp_sig{Motor.spin(vex::directionType::fwd);}
         * @brief Turns the motor on, and spins it in the specified direction.
         * @param dir The direction to spin the motor.
         */
        void spin( directionType dir );

        /**
         * @prog_lang{cpp|pro}
         * @drawer_cat{action}
         * @block_sig{Motor.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm);}
         * @brief Turns on the motor and spins it in a specified direction and a specified velocity.
         * @param dir The direction to spin the motor. 
         * @param velocity Sets the amount of velocity.
         * @param units The measurement unit of the velocity value. 
        */
        void spin( directionType dir, double velocity, velocityUnits units );

        void spin( directionType dir, double velocity, percentUnits units ){
            spin( dir, velocity, static_cast<velocityUnits>(units) );
        };
        
        /** 
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{action}
         * @block_sig{Motor.stop();}
         * @brief Stops the motor using the default brake mode.
         */
        void stop( void );
    };

};

#endif  // VCS_TRIPORT_CLASS_H
