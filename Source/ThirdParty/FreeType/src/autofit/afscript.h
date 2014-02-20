/***************************************************************************/
/*                                                                         */
/*  afscript.h                                                             */
/*                                                                         */
/*    Auto-fitter scripts (specification only).                            */
/*                                                                         */
/*  Copyright 2013 by                                                      */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/


  /* The following part can be included multiple times. */
  /* Define `SCRIPT' as needed.                         */


  /* Add new scripts here. */

  SCRIPT( cyrl, CYRL )
  SCRIPT( deva, DEVA )
  SCRIPT( dflt, DFLT )
  SCRIPT( grek, GREK )
  SCRIPT( hani, HANI )
  SCRIPT( hebr, HEBR )
  SCRIPT( latn, LATN )
#ifdef FT_OPTION_AUTOFIT2
  SCRIPT( ltn2, LTN2 )
#endif


/* END */
