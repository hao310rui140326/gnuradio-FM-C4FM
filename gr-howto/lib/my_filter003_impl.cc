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
#include "my_filter003_impl.h"

namespace gr {
  namespace howto {

    my_filter003::sptr
    my_filter003::make()
    {
      return gnuradio::get_initial_sptr
        (new my_filter003_impl());
    }


    /*
     * The private constructor
     */
    my_filter003_impl::my_filter003_impl()
      : gr::block("my_filter003",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    my_filter003_impl::~my_filter003_impl()
    {
    }

    void
    my_filter003_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
      ninput_items_required[0] = noutput_items ;
    }

    int
    my_filter003_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      //add
      int coef0_taps = 45;
      static float state[45] = {0};
      const float coef0[coef0_taps] =
	{
  -0.006352047578590,  
  -0.026672773118741,
  -0.035178537988811,
  -0.000748418484826,
   0.026363038772652,
  -0.009856895705774,
  -0.027218442714282,
   0.027396187518337,
   0.022120907252390,
  -0.049953796948842,
  -0.002743043357609,
   0.070816969332294,
  -0.036527856793421,
  -0.077761924537543,
   0.096428357034144,
   0.054251341148753,
  -0.171833218667313,
   0.020662656434014,
   0.256621724250457,
  -0.187242013238290,
  -0.378005942775776,
   0.650308103708118,
   1.455248997347319,
   0.650308103708118,
  -0.378005942775776,
  -0.187242013238290,
   0.256621724250457,
   0.020662656434014,
  -0.171833218667313,
   0.054251341148753,
   0.096428357034144,
  -0.077761924537543,
  -0.036527856793421,
   0.070816969332294,
  -0.002743043357609,
  -0.049953796948842,
   0.022120907252390,
   0.027396187518337,
  -0.027218442714282,
  -0.009856895705774,
   0.026363038772652,
  -0.000748418484826,
  -0.035178537988811,
  -0.026672773118741,
  -0.006352047578590
	};

	for(int i = 0; i<noutput_items; ++i) {
		for (int j = 0; j < coef0_taps - 1; j++)
		{
			state[j] = state[j + 1] ;
		}
		state[coef0_taps - 1] = in[i];
		out[i] = 0;
		for (int k = 0; k < coef0_taps; k++)
		{
			out[i] = out[i] + coef0[k] * state[k];
		}
      	}


      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace howto */
} /* namespace gr */

