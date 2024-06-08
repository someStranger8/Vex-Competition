/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Robomatter 2017, All rights reserved.                     */
/*                                                                            */
/*    Module:     vex_device.h                                                */
/*    Author:     James Pearman                                               */
/*    Created:    10 Oct 2017                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VCS_DEVICE_CLASS_H
#define   VCS_DEVICE_CLASS_H

#include "v5_apiprivate.h"

/*-----------------------------------------------------------------------------*/
/** @file    vex_device.h
  * @brief   Header for device class - this version for VCS
*//*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/** @brief device class                                                        */
/*-----------------------------------------------------------------------------*/
namespace vex {
  /** @brief Use the device class to get information about a vex device plugged into the V5.
  */
  class device  {
    private:
      V5_DeviceT      _ptr;
  
    protected:
      int32_t         _index;
      int32_t         _threadID;
      
    public:
      device();
      device( int32_t index );  
      ~device();

      V5_DeviceType   type();
      void            init( int32_t index );
      virtual bool    installed();
      virtual int32_t value();
  };
};

/*-----------------------------------------------------------------------------*/
/** @brief a safe array template                                               */
/*-----------------------------------------------------------------------------*/

namespace vex {
  template <class T, int len> class safearray {
    private:
      int length;
  
    protected:
      T arr[len];
      T outofbounds;
  
    public:
      safearray(){ length = len; outofbounds = 0;
      };
      ~safearray(){};
  
      T &operator[]( int i );
      int getLength() { return length; };
  };

  template <class T, int len> T &safearray<T, len>::operator[](int i)
  {
    // bounds check the array index
    if( i < 0 || i > (length-1) ) {
      return( outofbounds );
    }
    else {
      return( arr[i] );
    }
  }
};

/*-----------------------------------------------------------------------------*/
/** @brief All devices class                                                   */
/*-----------------------------------------------------------------------------*/
namespace vex {
  /** @brief Use the device class to get information about all of the vex devices plugged into the V5.
  */
  class devices {
    private:
      safearray<device, V5_MAX_DEVICE_PORTS> data;

    public:
      devices();  
      ~devices();

      device &operator[]( int i ) {
        return( data[i] );
      }
      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{Devices.type(1);}      
      * @brief Get the V5 device type plugged into a specific port.      
      * @return Returns a V5 device type.
      * @param index Specifies the index to look at for the device.
      */
      V5_DeviceType   type( int32_t index );

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{Devices.number();}
      * @brief Gets the number of VEX devices that are plugged in.    
      * @return Returns an integer that represent the number of vex devices
      */
      int32_t         number();

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @brief Gets the number of specified devices that are plugged into the V5.
      * @return Returns an integer that represents the number of a specific vex devices set by the parameter.
      * @param  type The type of device to look for on the V5.
      */
      int32_t         numberOf( V5_DeviceType type );
  };
};

#endif // VCS_DEVICE_CLASS_H