// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/accelerometer/accelerometer_controller.h"

#include "ash/accelerometer/accelerometer_observer.h"

namespace ash {

AccelerometerController::AccelerometerController() {
}

AccelerometerController::~AccelerometerController() {
}

void AccelerometerController::Initialize(
    scoped_refptr<base::TaskRunner> blocking_task_runner) {
#if defined(OS_CHROMEOS)
  reader_.reset(new chromeos::AccelerometerReader(blocking_task_runner, this));
#endif
}

void AccelerometerController::AddObserver(AccelerometerObserver* observer) {
  observers_.AddObserver(observer);
}

void AccelerometerController::RemoveObserver(AccelerometerObserver* observer) {
  observers_.RemoveObserver(observer);
}

#if defined(OS_CHROMEOS)
void AccelerometerController::HandleAccelerometerUpdate(
    const ui::AccelerometerUpdate& update) {
  FOR_EACH_OBSERVER(AccelerometerObserver, observers_,
      OnAccelerometerUpdated(update));
}
#endif

}  // namespace ash
