/*
 * Copyright © 2017 Mozilla Foundation
 *
 * This program is made available under an ISC-style license.  See the
 * accompanying file LICENSE for details.
 */

#include "gtest/gtest.h"
#include "cubeb/cubeb.h"  // for cubeb utils
#include "cubeb_utils.h"  // for owned_critical_section
#include "common.h"       // for current_thread_id
#include <iostream>       // for std::cerr, std::endl

owned_critical_section mutex;

void state_cb_audio(cubeb_stream * /*stream*/, void * /*user*/, cubeb_state /*state*/)
{
}

bool called = false;
template<typename T>
long data_cb(cubeb_stream * /*stream*/, void * /*user*/,
             const void * /*inputbuffer*/, void * /*outputbuffer*/, long nframes)
{
  std::cerr << "Thread " << current_thread_id() << ": Try locking mutex" << std::endl;
  mutex.lock();
  std::cerr << "Thread " << current_thread_id() << ": mutex is locked" << std::endl;
  mutex.unlock();
  std::cerr << "Thread " << current_thread_id() << ": mutex is unlocked" << std::endl;
  called = true;
  return nframes;
}

TEST(cubeb, run_late_callback_test)
{
  cubeb * ctx = NULL;
  int r = cubeb_init(&ctx, "Cubeb audio test", NULL);
  ASSERT_EQ(r, CUBEB_OK) << "Error initializing cubeb library";
  ASSERT_TRUE(!!ctx);

  std::unique_ptr<cubeb, decltype(&cubeb_destroy)>
    cleanup_cubeb_at_exit(ctx, cubeb_destroy);

  cubeb_stream_params params;
  params.format = CUBEB_SAMPLE_FLOAT32NE;
  params.rate = 44100;
  params.channels = 1;
  params.layout = CUBEB_LAYOUT_MONO;

  cubeb_stream * stream = NULL;
  r = cubeb_stream_init(ctx, &stream, "test late callback", NULL, NULL, NULL,
                        &params, 512, &data_cb<float>, state_cb_audio, NULL);
  ASSERT_EQ(r, CUBEB_OK);

  std::cerr << "Thread " << current_thread_id() << ": lock mutex" << std::endl;
  mutex.lock();
  cubeb_stream_start(stream);
  cubeb_stream_stop(stream);
  cubeb_stream_destroy(stream);
  mutex.unlock();
  std::cerr << "Thread " << current_thread_id() << ": mutex is unlocked" << std::endl;
  while (!called) {
    delay(10); // Force to switch to callback thread.
  }
  ASSERT_TRUE(called);
}
