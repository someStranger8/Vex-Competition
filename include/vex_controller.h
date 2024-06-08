/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_controller.h                                            */
/*    Author:     James Pearman                                               */
/*    Created:    10 July 2017                                                */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VCS_CONTROLLER_CLASS_H
#define   VCS_CONTROLLER_CLASS_H

#include <functional>

/*-----------------------------------------------------------------------------*/
/** @file    vex_controller.h
  * @brief   V5 controller class header
*//*---------------------------------------------------------------------------*/

namespace vex {
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use the controller class to get values from the remote controller as well as write to the controller's screen.
  */
  class controller {
    private:
      // copy if the controller id when this class was instantiated
      controllerType		_controllerId;
      // internal device id for this controller
      int32_t           _index;
      
      int32_t value( V5_ControllerIndex channel );

    protected:
      int32_t _getIndex();
      
    public:

      /** 
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::controller Controller = vex::controller();}
        * @brief Creates a new controller object.
      */
      controller();
      /** 
        * @prog_lang{cpp|pro}
        * @drawer_cat{constructor}
        * @block_sig{vex::controller Controller = vex::controller(vex::controllerType::partner);}
        * @brief Creates a new controller object.
        * @param id The type of controller that is being created. This can be set to primary or partner.
      */
      controller( controllerType id );
      ~controller();

      bool installed();

      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Controller.rumble(".-.-");}
       * @brief Rumbles the controller by a pattern defined by the parameter. Dots equal short, dashes equal long and space equals pause.
       * @param str A string that consists of dots and dashes that represent the rumble pattern.
      */ 
      void     rumble( const char *str );

    private:
      // bit masks for events
      enum class tEventType {
        EVENT_5_UP_PRESSED     = 0,
        EVENT_5_UP_RELEASED    = 1,
        EVENT_5_DN_PRESSED     = 2,
        EVENT_5_DN_RELEASED    = 3,
        
        EVENT_6_UP_PRESSED     = 4,
        EVENT_6_UP_RELEASED    = 5,
        EVENT_6_DN_PRESSED     = 6,
        EVENT_6_DN_RELEASED    = 7,
        
        EVENT_7_UP_PRESSED     = 8,
        EVENT_7_UP_RELEASED    = 9,
        EVENT_7_DN_PRESSED     = 10,
        EVENT_7_DN_RELEASED    = 11,

        EVENT_7_L_PRESSED      = 12,
        EVENT_7_L_RELEASED     = 13,
        EVENT_7_R_PRESSED      = 14,
        EVENT_7_R_RELEASED     = 15,

        EVENT_8_UP_PRESSED     = 16,
        EVENT_8_UP_RELEASED    = 17,
        EVENT_8_DN_PRESSED     = 18,
        EVENT_8_DN_RELEASED    = 19,

        EVENT_8_L_PRESSED      = 20,
        EVENT_8_L_RELEASED     = 21,
        EVENT_8_R_PRESSED      = 22,
        EVENT_8_R_RELEASED     = 23,

        EVENT_A_CHANGED        = 24,
        EVENT_B_CHANGED        = 25,
        EVENT_C_CHANGED        = 26,
        EVENT_D_CHANGED        = 27
      };

      enum class tButtonType {
        kButton5Up = 0,
        kButton5Down,
        kButton6Up,
        kButton6Down,
        kButton7Up,
        kButton7Down,
        kButton7Left,
        kButton7Right,
        kButton8Up,
        kButton8Down,
        kButton8Left,
        kButton8Right,

        // Final V5 button names
        kButtonL1 = 0,
        kButtonL2,
        kButtonR1,
        kButtonR2,
        kButtonUp,
        kButtonDown,
        kButtonLeft,
        kButtonRight,
        kButtonX,
        kButtonB,
        kButtonY,
        kButtonA,

        kButtonUndefined
      };
      /** 
        * @prog_lang{block|cpp|pro}
        * @brief Use the button class to get values from the controller's buttons.
      */
    public:
      class button {
        private:
          tButtonType  _id;
          controller   *_parent;
          tEventType _buttonToPressedEvent();
          tEventType _buttonToReleasedEvent();
          
        public:
          button() : _id( tButtonType::kButtonUndefined), _parent(NULL) {};
          button( const tButtonType id, controller *parent ) : _id( id ), _parent(parent) {};
          ~button() {};
          /**
           * @prog_lang{cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{pressed(pressedFunction);}
           * @brief Sets the function to be called when the button is pressed.
           * @param callback A reference to a function.
          */
          void     pressed( void (* callback)(void) );

          /**
           * @prog_lang{cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{released(releasedFunction);}
           * @brief Sets the function to be called when the button is released.
           * @param callback A reference to a function.
          */
          void     released( void (* callback)(void) );

          /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{pressing()}
           * @brief Gets the status of a button.
           * @return Returns a Boolean value based on the pressed states of the button. If the button is pressed it will return true.
          */
          bool     pressing( void );        

          mevent  PRESSED   = { (uint32_t)_parent->_getIndex(), (uint32_t)_buttonToPressedEvent()  };
          mevent  RELEASED  = { (uint32_t)_parent->_getIndex(), (uint32_t)_buttonToReleasedEvent()  };
      };
      
    private:
      button       button5Up    = button( tButtonType::kButton5Up   , this );
      button       button5Down  = button( tButtonType::kButton5Down , this );
      button       button6Up    = button( tButtonType::kButton6Up   , this );
      button       button6Down  = button( tButtonType::kButton6Down , this );
      button       button7Up    = button( tButtonType::kButton7Up   , this );
      button       button7Down  = button( tButtonType::kButton7Down , this );
      button       button7Left  = button( tButtonType::kButton7Left , this );
      button       button7Right = button( tButtonType::kButton7Right, this );
      button       button8Up    = button( tButtonType::kButton8Up   , this );
      button       button8Down  = button( tButtonType::kButton8Down , this );      
      button       button8Left  = button( tButtonType::kButton8Left , this );
      button       button8Right = button( tButtonType::kButton8Right, this );      

    public:
      // Final V5 button names
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonL1}
       * @brief A button that represents the L1 button on the controller
       */
      button &ButtonL1          = button5Up;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonL2}
       * @brief A button that represents the L2 button on the controller
       */
      button &ButtonL2          = button5Down;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonR1}
       * @brief A button that represents the R1 button on the controller
       */
      button &ButtonR1          = button6Up;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonR2}
       * @brief A button that represents the R2 button on the controller.
       */
      button &ButtonR2          = button6Down;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonUp}
       * @brief A button that represents the up button on the controller.
       */
      button &ButtonUp          = button7Up;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonDown}
       * @brief A button that represents the down button on the controller.
       */
      button &ButtonDown        = button7Down;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonLeft}
       * @brief A button that represents the left button on the controller.
       */
      button &ButtonLeft        = button7Left;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonRight}
       * @brief A button that represents the right button on the controller.
       */
      button &ButtonRight       = button7Right;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonX}
       * @brief A button that represents the x button on the controller.
       */
      button &ButtonX           = button8Up;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonB}
       * @brief A button that represents the B button on the controller.
       */
      button &ButtonB           = button8Down;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonY}
       * @brief A button that represents the Y button on the controller.
       */
      button &ButtonY           = button8Left;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.ButtonA}
       * @brief A button that represents the A button on the controller.
       */
      button &ButtonA           = button8Right;

    private:
      enum class tAxisType {
        kAxisA = 0,
        kAxisB,
        kAxisC,
        kAxisD,
        
        kAxisUndefined
      };
      
      
    public:
      /** 
        * @prog_lang{block|cpp|pro}
        * @brief Use the axis class to get values from one of the controller's joysticks
      */
      class axis {
        private:
          tAxisType  _id;
          controller   *_parent;
          tEventType _joystickToChangedEvent();
          
        public:
          axis() : _id( tAxisType::kAxisUndefined), _parent(NULL) {};
          axis( const tAxisType id, controller *parent ) : _id( id ), _parent(parent) {};
          ~axis() {};
          
          /**
           * @prog_lang{cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{changed(changedFunction);}
           * @brief Sets the function to be called when the joystick axis value changes.
           * @param callback A reference to a function.
          */
          void     changed( void (* callback)(void) );

          /**
           * @prog_lang{cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{value()}
           * @brief Gets the value of the joystick axis.
           * @return Returns an integer that represents the value of the joystick axis.
          */
          int32_t  value( void );

          /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{position(percent)}
           * @cpp_sig{position(vex::percentUnits::pct)}
           * @brief Gets the position of the joystick axis.
           * @return Returns an integer that represents the position of the joystick axis as defined by the unit in the parameter.
           * @param units The type of unit that will be returned.
          */        
          int32_t  position( percentUnits units );        

          mevent  CHANGED   = { (uint32_t)_parent->_getIndex(), (uint32_t)_joystickToChangedEvent()  };
      };
      
     
    private:
      axis     AxisA = axis( tAxisType::kAxisA, this );
      axis     AxisB = axis( tAxisType::kAxisB, this );
      axis     AxisC = axis( tAxisType::kAxisC, this );
      axis     AxisD = axis( tAxisType::kAxisD, this );
      
    public:
      // Final V5 joystick names
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.Axis1}
       * @brief An axis of a joystick that represents axis 1 on the controller.
       */
      axis     &Axis1          = AxisC;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.Axis2}
       * @brief An axis of a joystick that represents axis 2 on the controller.
       */
      axis     &Axis2          = AxisD;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.Axis3}
       * @brief An axis of a joystick that represents axis 3 on the controller.
       */
      axis     &Axis3          = AxisA;
      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Controller.Axis4}
       * @brief An axis of a joystick that represents axis 4 on the controller.
       */
      axis     &Axis4          = AxisB;
      
      /** 
        * @prog_lang{block|cpp|pro}
        * @brief Use this class to write to the controller's LCD screen.
      */
      class lcd {
        private:
          controller   *_parent;
          int32_t   _row;
          int32_t   _maxrows;
          int32_t   _col;
          int32_t   _maxcols;

          char      _textStr[32];
          
          controllerType  getControllerId();
          
        public:
          lcd();
          lcd(controller *parent);
          ~lcd() {};

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{setting}
         * @block_sig{setCursor(1,1);}
         * @brief Sets the cursor to the row and column number set in the parameters.
         * @param row Sets the row number for where the cursor is placed.
         * @param col Sets the column number for where the cursor is placed.
        */
        void     setCursor( int32_t row, int32_t col );

        /** 
         * @prog_lang{block}
         * @drawer_cat{action}
         * @block_sig{print("Hello");}
         * @brief Prints a number, string, or Boolean.
         * @param value Information to display on the screen.
         * @parameter_defaults_overrides{"Hello"|1|true}
         * @parameter_type_overrides{string|number|boolean}
         * @parameter_identifier_overrides{value|value|value}
         */
        template <class T>
        void     print( T value ) {
          if( std::is_same< T, int >::value )
            print( "%d", (int)value );
          else
          if( std::is_same< T, double >::value )
            print( "%.2f", (double)value );
          else {
            // primarily to handle modkit number
            if( (int)value == value )
              print( "%d", (int)value );
            else
              print( "%.2f", (double)value );
          }
        }
        /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{action}
           * @block_sig{print("Hello");}
           * @brief Prints a number, string, or Boolean.
           * @param format This is a reference to a char format that prints the value of variables.
           * @param ... A variable list of parameters to insert into format string.  
          */           
        void     print( const char *format, ... );
        
        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{action}
         * @block_sig{clearScreen();}
         * @brief Clears the controller's LCD screen.
        */
        void     clearScreen( void );

        /**
         * @prog_lang{cpp|pro}
         * @drawer_cat{action}
         * @block_sig{clearLine(1);}
         * @brief Clears the line specified by the parameter.
         * @param number The line number to be cleared.
        */
        void     clearLine( int number );

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{action}
         * @block_sig{clearLine();}
         * @brief Clears the current line.
        */
        void     clearLine( void );

        /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{action}
         * @block_sig{newLine();}
         * @brief Moves the cursor to the next line.
        */
        void     newLine( void );      
      };

      // Controller has an instance of an lcd
      /**
         * @prog_lang{block|cpp|pro}
         * @drawer_cat{instance}
         * @block_sig{Controller.Screen}
         * @brief Controller's instance of LCD.
      */
      lcd     Screen = lcd(this);
      // backwards compatibility

      lcd     &LCD = Screen;
  };
};

#endif  // VCS_CONTROLLER_CLASS_H