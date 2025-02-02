//
// Created by frank on 2021/8/28.
//

#include <jni.h>
#include "frank_visualizer.h"

#define VISUALIZER_FUNC(RETURN_TYPE, NAME, ...) \
  extern "C" { \
  JNIEXPORT RETURN_TYPE \
    Java_com_frank_ffmpeg_effect_FrankVisualizer_ ## NAME \
      (JNIEnv* env, jobject thiz, ##__VA_ARGS__);\
  } \
  JNIEXPORT RETURN_TYPE \
    Java_com_frank_ffmpeg_effect_FrankVisualizer_ ## NAME \
      (JNIEnv* env, jobject thiz, ##__VA_ARGS__)\

struct fields_t {
    jfieldID context;
};

static fields_t fields;
static const char *className = "com/frank/ffmpeg/effect/FrankVisualizer";

void setCustomVisualizer(JNIEnv *env, jobject thiz) {
    auto *customVisualizer = new FrankVisualizer();
    jclass clazz = env->FindClass(className);
    if (!clazz) {
        return;
    }
    fields.context = env->GetFieldID(clazz, "mNativeVisualizer", "J");
    if (!fields.context) {
        return;
    }
    env->SetLongField(thiz, fields.context, (jlong) customVisualizer);
}

FrankVisualizer *getCustomVisualizer(JNIEnv *env, jobject thiz) {
    if (!fields.context) return nullptr;
    return (FrankVisualizer *) env->GetLongField(thiz, fields.context);
}

void fft_callback(JNIEnv *jniEnv, int8_t * arg, int samples) {
    jclass visual_class = jniEnv->FindClass(className);
    jmethodID fft_method = jniEnv->GetStaticMethodID(visual_class, "onFftCallback", "([B)V");
    jbyteArray dataArray = jniEnv->NewByteArray(samples);
    jniEnv->SetByteArrayRegion(dataArray, 0, samples, arg);
    jniEnv->CallStaticVoidMethod(visual_class, fft_method, dataArray);
    jniEnv->DeleteLocalRef(dataArray);
}

VISUALIZER_FUNC(int, nativeInitVisualizer) {
    setCustomVisualizer(env, thiz);
    FrankVisualizer *mVisualizer = getCustomVisualizer(env, thiz);
    if (!mVisualizer) return -2;
    return mVisualizer->init_visualizer();
}

VISUALIZER_FUNC(int, nativeCaptureData, jobject buffer, jint size) {
    if (!buffer) return -1;
    FrankVisualizer *mVisualizer = getCustomVisualizer(env, thiz);
    if (!mVisualizer || !mVisualizer->fft_context) return -2;
    int nb_samples = size < MAX_FFT_SIZE ? size : MAX_FFT_SIZE;
    if (nb_samples >= MIN_FFT_SIZE) {
        mVisualizer->fft_context->nb_samples = nb_samples;
        auto *direct_buffer = static_cast<uint8_t *>(env->GetDirectBufferAddress(buffer));
        memcpy(mVisualizer->fft_context->data, direct_buffer, static_cast<size_t>(nb_samples));
        mVisualizer->fft_run();
        fft_callback(env, mVisualizer->fft_context->output, mVisualizer->fft_context->out_samples);
    }
    return 0;
}

VISUALIZER_FUNC(void, nativeReleaseVisualizer) {
    FrankVisualizer *mVisualizer = getCustomVisualizer(env, thiz);
    if (!mVisualizer) return;
    mVisualizer->release_visualizer();
    delete mVisualizer;
    env->SetLongField(thiz, fields.context, 0);
}