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
#include "myfilter002_impl.h"

namespace gr {
  namespace howto {

    myfilter002::sptr
    myfilter002::make()
    {
      return gnuradio::get_initial_sptr
        (new myfilter002_impl());
    }


    /*
     * The private constructor
     */
    myfilter002_impl::myfilter002_impl()
      : gr::block("myfilter002",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    myfilter002_impl::~myfilter002_impl()
    {
    }

    void
    myfilter002_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
      ninput_items_required[0] = noutput_items ;
    }

    int
    myfilter002_impl::general_work (int noutput_items,
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
      int coef0_taps = 44;
      static float state[44] = {0};
      const float coef0[coef0_taps] =
	{
0.006896687032273,
   0.016322575741065,
   0.013825015233988,
  -0.008240454919430,
  -0.029069345001755,
  -0.019453667029668,
   0.011416133246436,
   0.017054846356230,
  -0.017912509809512,
  -0.040753691584303,
  -0.004209111893625,
   0.045309762133298,
   0.021485188545136,
  -0.056491552302914,
  -0.061830037600586,
   0.045059275324446,
   0.108786145004423,
  -0.015797791525203,
  -0.189639569222681,
  -0.086721547351088,
   0.372961664952440,
   0.823392346176033,
   0.823392346176033,
   0.372961664952440,
  -0.086721547351088,
  -0.189639569222681,
  -0.015797791525203,
   0.108786145004423,
   0.045059275324446,
  -0.061830037600586,
  -0.056491552302914,
   0.021485188545136,
   0.045309762133298,
  -0.004209111893625,
  -0.040753691584303,
  -0.017912509809512,
   0.017054846356230,
   0.011416133246436,
  -0.019453667029668,
  -0.029069345001755,
  -0.008240454919430,
   0.013825015233988,
   0.016322575741065,
   0.006896687032273
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

