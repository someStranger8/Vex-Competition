/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Robomatter 2016, All rights reserved.                     */
/*                                                                            */
/*    Module:     v5_options.h                                                */
/*    Author:     James Pearman                                               */
/*    Created:    26 Jan 2018                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef V5_VCS_OPTIONS_H_
#define V5_VCS_OPTIONS_H_

// Default user code options when building for vcs
//
#if !defined(V5_CODE_SIG_DEFINED)

#ifdef  VCS_WHITE_ON_BLACK
// White text on Black background
__attribute__((weak)) V5_CODE_SIG( V5_SIG_TYPE_USER, V5_SIG_OWNER_VEX, V5_SIG_OPTIONS_EXIT, 0  );
#else
// Black text on White background (default for VCS)
__attribute__((weak)) V5_CODE_SIG( V5_SIG_TYPE_USER, V5_SIG_OWNER_VEX, V5_SIG_OPTIONS_INDG | V5_SIG_OPTIONS_EXIT, 0  );
#endif  // VCS_WHITE_ON_BLACK

#endif  // V5_CODE_SIG_DEFINED

#endif  // V5_VCS_OPTIONS_H_