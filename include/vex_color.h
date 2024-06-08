/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_color.h                                                 */
/*    Author:     James Pearman                                               */
/*    Created:    21 May 2018                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VCS_COLOR_CLASS_H
#define   VCS_COLOR_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_color.h
  * @brief   V5 color class header
*//*---------------------------------------------------------------------------*/

namespace vex {
    /**
      * @prog_lang{cpp|pro}
      * @brief Use the color class to create Color objects.
    */
    class color {
        private:
          uint32_t  _argb;
          bool      _transparent;

          // special constructor only used to create a transparent color
          color( int value, bool transparent );            
          
        public:
          color();          
          /**
          * @prog_lang{cpp|pro}
          * @drawer_cat{none}
          * @brief Creates a color. 
          * @param value The value of the color. 
          */          
          color( int value );
          /**
          * @prog_lang{cpp|pro}
          * @drawer_cat{none}
          * @brief Creates a color using red, green, and blue values. 
          * @param r the color of red on a scale of 0 to 255.
          * @param g the color of green on a scale of 0 to 255.
          * @param b the color of blue on a scale of 0 to 255.
          */
          color( uint8_t r, uint8_t g, uint8_t b );            
          ~color();

          // Assignment
          uint32_t  rgb( uint32_t value );
          uint32_t  rgb( uint8_t r, uint8_t g, uint8_t b );
          void operator=( uint32_t value );

          // Get value
          uint32_t  rgb() const;                        
          operator uint32_t() const;
          
         /**
          * @prog_lang{cpp|pro}
          * @drawer_cat{none}
          * @brief Gets the state of the color's transparency.
          * @return Returns true if the color is transparent.
          */
          bool isTransparent() const;

         /**
          * @prog_lang{pro}
          * @drawer_cat{none}
          * @brief Creates a color using hue, saturation, and brightness values.         
          * @return Returns a reference to a color.
          * @param hue An integer from 0 to 360 that represents the hue of the color.
          * @param sat A double from 0.0 to 1.0 that represents the saturation of the color.
          * @param value A double from 0.0 to 1.0 that represents the brightness of the color.
          */
          color& hsv( uint32_t hue, double sat, double value );
          
         /**
          * @prog_lang{pro}
          * @drawer_cat{none}
          * @brief Creates a color using a hexadecimal value.
          * @return Returns a reference to a color.
          * @param color A hexadecimal or web color value that defines a specific color.
          */
          color& web( const char *color );

          // predefined colors
          
          /**
           *@prog_lang{cpp|pro}
           *@brief Represents the color black.
           *@return Returns the color black
           */
          static const color    black;
          /**
           *@prog_lang{cpp|pro}
           *@brief Represents the color white.
           *@return Returns the color white
           */
          static const color    white;
          /**
           *@prog_lang{cpp|pro}
           *@brief Represents the color red.
           *@return Returns the color red
           */
          static const color    red;
          /**
           *@prog_lang{cpp|pro}
           *@brief Represents the color green.
           *@return Returns the color green
           */
          static const color    green;
          /**
           *@prog_lang{cpp|pro}
           *@brief Represents the color blue.
           *@return Returns the color blue
           */
          static const color    blue;
          /**
           *@prog_lang{cpp|pro}
           *@brief Represents the color yellow.
           *@return Returns the color yellow
           */
          static const color    yellow;
          /**
           *@prog_lang{cpp|pro}
           *@brief Represents the color orange.
           *@return Returns the color orange
           */
          static const color    orange;
          /**
           *@prog_lang{cpp|pro}
           *@brief Represents the color purple.
           *@return Returns the color purple
           */
          static const color    purple;
          /**
           *@prog_lang{cpp|pro}
           *@brief Represents the color cyan.
           *@return Returns the color cyan
           */
          static const color    cyan;
          /**
           *@prog_lang{cpp|pro}
           *@brief Represents the color transparent.
           *@return Returns the color transparent
           */
          static const color    transparent;          
    };
}

#endif // VCS_COLOR_CLASS_H