// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FAVICON_CORE_LARGE_ICON_SERVICE_H_
#define COMPONENTS_FAVICON_CORE_LARGE_ICON_SERVICE_H_

#include <vector>

#include "base/task/cancelable_task_tracker.h"
#include "components/favicon_base/favicon_callback.h"
#include "components/keyed_service/core/keyed_service.h"

class GURL;

namespace favicon_base {
struct FaviconRawBitmapResult;
}

namespace favicon {

class FaviconService;

// The large icon service provides methods to access large icons. It relies on
// the favicon service.
class LargeIconService : public KeyedService {
 public:
  explicit LargeIconService(FaviconService* favicon_service);

  ~LargeIconService() override;

  // Requests the best large icon for the page at |page_url|.
  // Case 1. An icon exists whose size is >= |min_source_size_in_pixel|:
  // - If |desired_size_in_pixel| == 0: returns icon as is.
  // - Else: returns the icon resized to |desired_size_in_pixel|.
  // Case 2. An icon exists whose size is < |min_source_size_in_pixel|:
  // - Extracts dominant color of smaller image, returns a fallback icon style
  //   that has a matching background.
  // Case 3. No icon exists.
  // - Returns the default fallback icon style.
  // For cases 2 and 3, this function returns the style of the fallback icon
  // instead of rendering an icon so clients can render the icon themselves.
  base::CancelableTaskTracker::TaskId GetLargeIconOrFallbackStyle(
    const GURL& page_url,
    int min_source_size_in_pixel,
    int desired_size_in_pixel,
    const favicon_base::LargeIconCallback& callback,
    base::CancelableTaskTracker* tracker);

 private:
  // Resizes |bitmap_result| to |desired_size_in_pixel|x|desired_size_in_pixel|.
  // Stores the resized bitmap data in |resized_bitmap_result| and returns true
  // if successful.
  bool ResizeLargeIconIfValid(
      int min_source_size_in_pixel,
      int desired_size_in_pixel,
      const favicon_base::FaviconRawBitmapResult& bitmap_result,
      favicon_base::FaviconRawBitmapResult* resized_bitmap_result);

  // Intermediate callback for GetLargeIconOrFallbackStyle(). Tries to resize
  // |bitmap_result| and pass the output to |callback|. If that does not work,
  // computes the icon fallback style and uses it to invoke |callback|.
  void RunLargeIconCallback(
      const favicon_base::LargeIconCallback& callback,
      int min_source_size_in_pixel,
      int desired_size_in_pixel,
      const favicon_base::FaviconRawBitmapResult& bitmap_result);

  FaviconService* favicon_service_;

  // A pre-populated list of the types of icon files to consider when looking
  // for large icons. This is an optimization over populating an icon type
  // vector on each request.
  std::vector<int> large_icon_types_;

  DISALLOW_COPY_AND_ASSIGN(LargeIconService);
};

}  // namespace favicon

#endif  // COMPONENTS_FAVICON_CORE_LARGE_ICON_SERVICE_H_
