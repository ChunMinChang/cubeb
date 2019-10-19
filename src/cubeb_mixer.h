/*
 * Copyright © 2016 Mozilla Foundation
 *
 * This program is made available under an ISC-style license.  See the
 * accompanying file LICENSE for details.
 */

#ifndef CUBEB_MIXER
#define CUBEB_MIXER

#include "cubeb/cubeb.h" // for cubeb_channel_layout and cubeb_stream_params.

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct cubeb_mixer cubeb_mixer;
// output_channel_order is a nullable pointer to an array whose size is out_channels,
// containing channel order of the output buffer.
// If output_channel_order is null, then the channel data in the output buffer
// will be filled in a predefined order of the out_layout.
// If output_channel_order is set, then the output buffer will be filled by the
// order defined in output_channel_order and the output layout will be calculated by
// output_channel_order rather than out_layout. That is, out_layout will be ignored.
cubeb_mixer * cubeb_mixer_create(cubeb_sample_format format,
                                 uint32_t in_channels,
                                 cubeb_channel_layout in_layout,
                                 uint32_t out_channels,
                                 cubeb_channel_layout out_layout,
                                 const cubeb_channel * output_channel_order);
void cubeb_mixer_destroy(cubeb_mixer * mixer);
int cubeb_mixer_mix(cubeb_mixer * mixer,
                    size_t frames,
                    const void * input_buffer,
                    size_t input_buffer_size,
                    void * output_buffer,
                    size_t output_buffer_size);

unsigned int cubeb_channel_layout_nb_channels(cubeb_channel_layout channel_layout);

#if defined(__cplusplus)
}
#endif

#endif // CUBEB_MIXER
