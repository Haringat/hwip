/*
 * Copyright (c) 2016 Marcel Mundl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "com_github_haringat_hwip_clp_Parser.h"
#include "../../../src/libclp/clp.h"

/*
 * Class:     com_github_haringat_hwip_clp_Parser
 * Method:    parseCLI
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_github_haringat_hwip_clp_Parser_parseCLI
        (JNIEnv *env, jclass Parser) {
    env->Throw((jthrowable) env->AllocObject(env->FindClass("java.lang.Throwable")));
}

/*
 * Class:     com_github_haringat_hwip_clp_Parser
 * Method:    addArg
 * Signature: ([Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_haringat_hwip_clp_Parser_addArg___3Ljava_lang_String_2Ljava_lang_String_2
        (JNIEnv *env, jclass Parser, jobjectArray , jstring) {
}

/*
 * Class:     com_github_haringat_hwip_clp_Parser
 * Method:    addArg
 * Signature: ([Ljava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_github_haringat_hwip_clp_Parser_addArg___3Ljava_lang_String_2Ljava_lang_String_2I
        (JNIEnv *, jclass, jobjectArray, jstring, jint) {
}

/*
 * Class:     com_github_haringat_hwip_clp_Parser
 * Method:    addArg
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_haringat_hwip_clp_Parser_addArg__Ljava_lang_String_2Ljava_lang_String_2
        (JNIEnv *, jclass, jstring, jstring) {
}

/*
 * Class:     com_github_haringat_hwip_clp_Parser
 * Method:    addArg
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_github_haringat_hwip_clp_Parser_addArg__Ljava_lang_String_2Ljava_lang_String_2I
        (JNIEnv *, jclass, jstring, jstring, jint) {
}
