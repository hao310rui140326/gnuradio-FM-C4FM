/* -*- c++ -*- */
/*
 * Copyright 2020 gr-howto author.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "my_cos_phase_600hz_impl.h"


#define PI 3.141592653589793
#define freqdev 600

namespace gr {
  namespace howto {

    my_cos_phase_600hz::sptr
    my_cos_phase_600hz::make()
    {
      return gnuradio::get_initial_sptr
        (new my_cos_phase_600hz_impl());
    }


    /*
     * The private constructor
     */
    my_cos_phase_600hz_impl::my_cos_phase_600hz_impl()
      : gr::block("my_cos_phase_600hz",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    my_cos_phase_600hz_impl::~my_cos_phase_600hz_impl()
    {
    }

    void
    my_cos_phase_600hz_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
      ninput_items_required[0] = noutput_items ;
    }

    int
    my_cos_phase_600hz_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float  *in = (const float *) input_items[0];
      float  *out = (float *) output_items[0];

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      // add
     static float phase= 0;
     float phase_n ;
     for(int i = 0; i<noutput_items; ++i) {
      	phase = phase + in[i];
        phase_n = freqdev * phase  / 38400 ;
	if ( phase_n > 1 )
		phase = phase - 38400/freqdev ;
	else if(phase_n <-1)
		phase = phase + 38400/freqdev ;
	else
		phase = phase ;
      	out[i] = cos(2 *  PI * freqdev * phase  / 38400 );
     }

      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace howto */
} /* namespace gr */

