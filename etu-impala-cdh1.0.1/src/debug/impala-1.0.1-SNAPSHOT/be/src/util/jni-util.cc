// Copyright 2012 Cloudera Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "util/jni-util.h"
#include <hdfs.h>
#include "common/status.h"

using namespace std;

namespace impala {

jclass JniUtil::jni_util_cl_ = NULL;
jclass JniUtil::internal_exc_cl_ = NULL;
jmethodID JniUtil::throwable_to_string_id_ = NULL;
jmethodID JniUtil::throwable_to_stack_trace_id_ = NULL;
vector<jobject> JniUtil::global_refs_;

Status JniLocalFrame::push(JNIEnv* env, int max_local_ref) {
  DCHECK(env_ == NULL);
  DCHECK_GT(max_local_ref, 0);
  if (env->PushLocalFrame(max_local_ref) < 0) {
    env->ExceptionClear();
    return Status("failed to push frame");
  }
  env_ = env;
  return Status::OK;
}

Status JniUtil::GetGlobalClassRef(JNIEnv* env, const char* class_str, jclass* class_ref) {
  *class_ref = NULL;
  jclass local_cl = env->FindClass(class_str);
  RETURN_ERROR_IF_EXC(env);
  RETURN_IF_ERROR(LocalToGlobalRef(env, reinterpret_cast<jobject>(local_cl),
      reinterpret_cast<jobject*>(class_ref)));
  env->DeleteLocalRef(local_cl);
  RETURN_ERROR_IF_EXC(env);
  return Status::OK;
}

Status JniUtil::LocalToGlobalRef(JNIEnv* env, jobject local_ref, jobject* global_ref) {
  *global_ref = env->NewGlobalRef(local_ref);
  RETURN_ERROR_IF_EXC(env);
  global_refs_.push_back(*global_ref);
  return Status::OK;
}

Status JniUtil::Init() {
  // Get the JNIEnv* corresponding to current thread.
  JNIEnv* env = getJNIEnv();
  if (env == NULL) {
    return Status("Failed to get/create JVM");
  }

  // Find JniUtil class and create a global ref.
  jclass local_jni_util_cl = env->FindClass("com/cloudera/impala/common/JniUtil");
  if (local_jni_util_cl == NULL) {
    if (env->ExceptionOccurred()) env->ExceptionDescribe();
    return Status("Failed to find JniUtil class.");
  }
  jni_util_cl_ = reinterpret_cast<jclass>(env->NewGlobalRef(local_jni_util_cl));
  if (jni_util_cl_ == NULL) {
    if (env->ExceptionOccurred()) env->ExceptionDescribe();
    return Status("Failed to create global reference to JniUtil class.");
  }
  env->DeleteLocalRef(local_jni_util_cl);
  if (env->ExceptionOccurred()) {
    return Status("Failed to delete local reference to JniUtil class.");
  }

  // Find InternalException class and create a global ref.
  jclass local_internal_exc_cl =
      env->FindClass("com/cloudera/impala/common/InternalException");
  if (local_internal_exc_cl == NULL) {
    if (env->ExceptionOccurred()) env->ExceptionDescribe();
    return Status("Failed to find JniUtil class.");
  }
  internal_exc_cl_ = reinterpret_cast<jclass>(env->NewGlobalRef(local_internal_exc_cl));
  if (internal_exc_cl_ == NULL) {
    if (env->ExceptionOccurred()) env->ExceptionDescribe();
    return Status("Failed to create global reference to JniUtil class.");
  }
  env->DeleteLocalRef(local_internal_exc_cl);
  if (env->ExceptionOccurred()) {
    return Status("Failed to delete local reference to JniUtil class.");
  }

  // Throwable toString()
  throwable_to_string_id_ =
      env->GetStaticMethodID(jni_util_cl_, "throwableToString", 
          "(Ljava/lang/Throwable;)Ljava/lang/String;");
  if (throwable_to_string_id_ == NULL) {
    if (env->ExceptionOccurred()) env->ExceptionDescribe();
    return Status("Failed to find JniUtil.throwableToString method.");
  }

  // throwableToStackTrace()
  throwable_to_stack_trace_id_ =
      env->GetStaticMethodID(jni_util_cl_, "throwableToStackTrace",
          "(Ljava/lang/Throwable;)Ljava/lang/String;");
  if (throwable_to_stack_trace_id_ == NULL) {
    if (env->ExceptionOccurred()) env->ExceptionDescribe();
    return Status("Failed to find JniUtil.throwableToFullStackTrace method.");
  }
  return Status::OK;
}

void JniUtil::InitLibhdfs() {
  // make random libhdfs calls to make sure that the context class loader isn't
  // null; see xxx for an explanation
  hdfsFS fs = hdfsConnect("default", 0);
  hdfsDisconnect(fs);
}

Status JniUtil::Cleanup() {
  // Get the JNIEnv* corresponding to current thread.
  JNIEnv* env = getJNIEnv();
  if (env == NULL) {
    return Status("Failed to get/create JVM");
  }
  vector<jobject>::iterator it;
  for (it = global_refs_.begin(); it != global_refs_.end(); ++it) {
    env->DeleteGlobalRef(*it);
  }
  global_refs_.clear();
  return Status::OK;
}

}
