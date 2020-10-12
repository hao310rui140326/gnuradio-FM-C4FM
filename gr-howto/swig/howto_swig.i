/* -*- c++ -*- */

#define HOWTO_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "howto_swig_doc.i"

%{
#include "howto/square_ff.h"
#include "howto/my_filter001.h"
#include "howto/myfilter002.h"
#include "howto/my_cos_phase.h"
#include "howto/my_sin_phase.h"
#include "howto/my_fm_cphase.h"
#include "howto/my_fm_sphase.h"
#include "howto/my_cos_phase_600hz.h"
#include "howto/my_sin_phase_600hz.h"
#include "howto/my_filter003.h"
%}

%include "howto/square_ff.h"
GR_SWIG_BLOCK_MAGIC2(howto, square_ff);
%include "howto/my_filter001.h"
GR_SWIG_BLOCK_MAGIC2(howto, my_filter001);
%include "howto/myfilter002.h"
GR_SWIG_BLOCK_MAGIC2(howto, myfilter002);
%include "howto/my_cos_phase.h"
GR_SWIG_BLOCK_MAGIC2(howto, my_cos_phase);
%include "howto/my_sin_phase.h"
GR_SWIG_BLOCK_MAGIC2(howto, my_sin_phase);
%include "howto/my_fm_cphase.h"
GR_SWIG_BLOCK_MAGIC2(howto, my_fm_cphase);
%include "howto/my_fm_sphase.h"
GR_SWIG_BLOCK_MAGIC2(howto, my_fm_sphase);
%include "howto/my_cos_phase_600hz.h"
GR_SWIG_BLOCK_MAGIC2(howto, my_cos_phase_600hz);
%include "howto/my_sin_phase_600hz.h"
GR_SWIG_BLOCK_MAGIC2(howto, my_sin_phase_600hz);
%include "howto/my_filter003.h"
GR_SWIG_BLOCK_MAGIC2(howto, my_filter003);
