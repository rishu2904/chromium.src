# Copyright 2013 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from telemetry.core import forwarders
from telemetry.core.backends import browser_backend
from telemetry.core.backends.webdriver import webdriver_tab_list_backend


class WebDriverBrowserBackend(browser_backend.BrowserBackend):
  """The webdriver-based backend for controlling a locally-executed browser
  instance, on Linux, Mac, and Windows.
  """

  def __init__(self, driver_creator, supports_extensions, browser_options):
    super(WebDriverBrowserBackend, self).__init__(
        supports_extensions=supports_extensions,
        browser_options=browser_options,
        tab_list_backend=webdriver_tab_list_backend.WebDriverTabListBackend)

    self._driver_creator = driver_creator
    self._driver = None
    self.wpr_port_pairs = forwarders.PortPairs(
        http=forwarders.PortPair(80, 80),
        https=forwarders.PortPair(443, 443),
        dns=forwarders.PortPair(53, 53))

  def Start(self):
    assert not self._driver
    self._driver = self._driver_creator()

  @property
  def driver(self):
    assert self._driver
    return self._driver

  @property
  def supports_tab_control(self):
    # Based on webdriver protocol API, only closing a tab is supported while
    # activating or creating a tab is not. Thus, tab control is not supported.
    return False

  @property
  def supports_tracing(self):
    # Tracing is not available in IE/Firefox yet and not supported through
    # webdriver API.
    return False

  def GetProcessName(self, cmd_line):
    # Leave implementation details to subclass as process name depends on the
    # type of browser.
    raise NotImplementedError()

  def Close(self):
    if self._driver:
      self._driver.quit()
      self._driver = None

  def IsBrowserRunning(self):
    # Assume the browser is running if not explicitly closed.
    return self._driver is not None

  def __del__(self):
    self.Close()
