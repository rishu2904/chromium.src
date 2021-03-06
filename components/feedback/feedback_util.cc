// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "components/feedback/feedback_util.h"

#include <string>

#include "base/bind.h"
#include "base/files/file_util.h"
#include "components/feedback/feedback_data.h"
#include "components/feedback/feedback_uploader.h"
#include "components/feedback/feedback_uploader_factory.h"
#include "components/feedback/proto/common.pb.h"
#include "components/feedback/proto/dom.pb.h"
#include "components/feedback/proto/extension.pb.h"
#include "components/feedback/proto/math.pb.h"
#include "third_party/zlib/google/zip.h"

using feedback::FeedbackData;

namespace {

#if defined(OS_CHROMEOS)
const int kChromeOSProductId = 208;
#else
const int kChromeBrowserProductId = 237;
#endif

}  // namespace

namespace feedback_util {

void SendReport(scoped_refptr<FeedbackData> data) {
  if (!data.get()) {
    LOG(ERROR) << "SendReport called with NULL data!";
    NOTREACHED();
    return;
  }

  userfeedback::ExtensionSubmit feedback_data;
  data->PrepareReport(&feedback_data);

  // Set whether we're reporting from ChromeOS or Chrome on another platform.
  userfeedback::ChromeData chrome_data;
#if defined(OS_CHROMEOS)
  chrome_data.set_chrome_platform(
      userfeedback::ChromeData_ChromePlatform_CHROME_OS);
  userfeedback::ChromeOsData chrome_os_data;
  chrome_os_data.set_category(
      userfeedback::ChromeOsData_ChromeOsCategory_OTHER);
  *(chrome_data.mutable_chrome_os_data()) = chrome_os_data;
  feedback_data.set_product_id(kChromeOSProductId);
#else
  chrome_data.set_chrome_platform(
      userfeedback::ChromeData_ChromePlatform_CHROME_BROWSER);
  userfeedback::ChromeBrowserData chrome_browser_data;
  chrome_browser_data.set_category(
      userfeedback::ChromeBrowserData_ChromeBrowserCategory_OTHER);
  *(chrome_data.mutable_chrome_browser_data()) = chrome_browser_data;
  feedback_data.set_product_id(kChromeBrowserProductId);
#endif

  *(feedback_data.mutable_chrome_data()) = chrome_data;

  // This pointer will eventually get deleted by the PostCleanup class, after
  // we've either managed to successfully upload the report or died trying.
  std::string post_body;
  feedback_data.SerializeToString(&post_body);

  feedback::FeedbackUploader *uploader =
      feedback::FeedbackUploaderFactory::GetForBrowserContext(data->context());
  uploader->QueueReport(post_body);
}

bool ZipString(const base::FilePath& filename,
               const std::string& data, std::string* compressed_logs) {
  base::FilePath temp_path;
  base::FilePath zip_file;

  // Create a temporary directory, put the logs into a file in it. Create
  // another temporary file to receive the zip file in.
  if (!base::CreateNewTempDirectory(base::FilePath::StringType(), &temp_path))
    return false;
  if (base::WriteFile(temp_path.Append(filename), data.c_str(), data.size()) ==
      -1)
    return false;

  bool succeed = base::CreateTemporaryFile(&zip_file) &&
      zip::Zip(temp_path, zip_file, false) &&
      base::ReadFileToString(zip_file, compressed_logs);

  base::DeleteFile(temp_path, true);
  base::DeleteFile(zip_file, false);

  return succeed;
}

}  // namespace feedback_util
