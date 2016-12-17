//
// Created by 吴曰阳 on 16/12/16.
//
#include <jni.h>
#include "libmp3lame/lame.h"

lame_global_flags *lame = NULL;

JNIEXPORT void JNICALL
Java_com_lilyenglish_library_util_LameUtil_close(JNIEnv *env, jclass type) {
    lame_close(lame);
    lame = NULL;
}

JNIEXPORT jint JNICALL
Java_com_lilyenglish_library_util_LameUtil_flush(JNIEnv *env, jclass type, jbyteArray mp3buf_) {
    const jsize mp3buf_size = (*env)->GetArrayLength(env, mp3buf_);
    jbyte *mp3buf = (*env)->GetByteArrayElements(env, mp3buf_, NULL);

    int result = lame_encode_flush(lame, mp3buf, mp3buf_size);

    (*env)->ReleaseByteArrayElements(env, mp3buf_, mp3buf, 0);
    return result;
}

JNIEXPORT jint JNICALL
Java_com_lilyenglish_library_util_LameUtil_encode(JNIEnv *env, jclass type, jshortArray bufferLeft_,
                                                  jshortArray bufferRight_, jint samples,
                                                  jbyteArray mp3buf_) {
    jshort *bufferLeft = (*env)->GetShortArrayElements(env, bufferLeft_, NULL);
    jshort *bufferRight = (*env)->GetShortArrayElements(env, bufferRight_, NULL);
    jbyte *mp3buf = (*env)->GetByteArrayElements(env, mp3buf_, NULL);
    const jsize mp3buf_size = (*env)->GetArrayLength(env, mp3buf_);

    int result = lame_encode_buffer(lame, bufferLeft, bufferRight, samples, mp3buf, mp3buf_size);

    (*env)->ReleaseShortArrayElements(env, bufferLeft_, bufferLeft, 0);
    (*env)->ReleaseShortArrayElements(env, bufferRight_, bufferRight, 0);
    (*env)->ReleaseByteArrayElements(env, mp3buf_, mp3buf, 0);
    return result;
}

JNIEXPORT void JNICALL
Java_com_lilyenglish_library_util_LameUtil_init(JNIEnv *env, jclass type, jint inSamplerate,
                                                jint inChannel, jint outSamplerate, jint outBitrate,
                                                jint quality) {

    if (lame != NULL) {
        lame_close(lame);
        lame = NULL;
    }
    lame = lame_init();
    lame_set_num_channels(lame, inChannel);
    lame_set_in_samplerate(lame, inSamplerate);
    lame_set_out_samplerate(lame, outSamplerate);
    lame_set_brate(lame, outBitrate);
    lame_set_quality(lame, quality);
    lame_init_params(lame);

}
