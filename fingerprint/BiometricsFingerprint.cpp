/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "android.hardware.biometrics.fingerprint@2.3-service.dubai"
#define LOG_VERBOSE "android.hardware.biometrics.fingerprint@2.3-service.dubai"

#include <android-base/logging.h>
#include <android-base/properties.h>
#include <hardware/hardware.h>
#include <hardware/fingerprint.h>
#include "BiometricsFingerprint.h"
#include <fstream>
#include <cmath>
#include <inttypes.h>
#include <unistd.h>
#include <thread>

namespace android {
namespace hardware {
namespace biometrics {
namespace fingerprint {
namespace V2_3 {
namespace implementation {

template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
    LOG(INFO) << "wrote path: " << path << ", value: " << value << "\n";
}

template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    LOG(INFO) << "read path: " << path << ", value: " << result << "\n";
    return file.fail() ? def : result;
}

static std::string get(const std::string& path, const std::string& def) {
    std::ifstream file(path);
    std::string result;
    file >> result;
    LOG(INFO) << "read path: " << path << ", value: " << result << "\n";
    return file.fail() ? def : result;
}

BiometricsFingerprint::BiometricsFingerprint() {
    mBiometricsFingerprint = android::hardware::biometrics::fingerprint::V2_1::IBiometricsFingerprint::getService();
}

Return<uint64_t> BiometricsFingerprint::setNotify(
        const sp<IBiometricsFingerprintClientCallback>& clientCallback) {
    return mBiometricsFingerprint->setNotify(clientCallback);
}

Return<uint64_t> BiometricsFingerprint::preEnroll()  {
    return mBiometricsFingerprint->preEnroll();
}

Return<RequestStatus> BiometricsFingerprint::enroll(const hidl_array<uint8_t, 69>& hat,
    uint32_t gid, uint32_t timeoutSec)  {
    return mBiometricsFingerprint->enroll(hat, gid, timeoutSec);
}

Return<RequestStatus> BiometricsFingerprint::postEnroll()  {
    return mBiometricsFingerprint->postEnroll();
}

Return<uint64_t> BiometricsFingerprint::getAuthenticatorId()  {
    return mBiometricsFingerprint->getAuthenticatorId();
}

Return<RequestStatus> BiometricsFingerprint::cancel()  {
    return mBiometricsFingerprint->cancel();
}

Return<RequestStatus> BiometricsFingerprint::enumerate()  {
    return mBiometricsFingerprint->enumerate();
}

Return<RequestStatus> BiometricsFingerprint::remove(uint32_t gid, uint32_t fid)  {
    return mBiometricsFingerprint->remove(gid, fid);
}

Return<RequestStatus> BiometricsFingerprint::setActiveGroup(uint32_t gid,
    const hidl_string& storePath)  {
    return mBiometricsFingerprint->setActiveGroup(gid, storePath);
}

Return<RequestStatus> BiometricsFingerprint::authenticate(uint64_t operationId, uint32_t gid)  {
    return mBiometricsFingerprint->authenticate(operationId, gid);
}

Return<bool> BiometricsFingerprint::isUdfps(uint32_t) {
    return true;
}

Return<void> BiometricsFingerprint::onShowUdfpsOverlay() {
    return Void();
}

Return<void> BiometricsFingerprint::onFingerUp() {
    return Void();
}

Return<void> BiometricsFingerprint::onFingerDown(uint32_t, uint32_t, float, float) {
    return Void();
}

Return<void> BiometricsFingerprint::onHideUdfpsOverlay() {
    return Void();
}

}  // namespace implementation
}  // namespace V2_3
}  // namespace fingerprint
}  // namespace biometrics
}  // namespace hardware
}  // namespace android
