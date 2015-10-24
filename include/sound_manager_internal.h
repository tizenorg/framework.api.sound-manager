/*
* Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef __TIZEN_MEDIA_SOUND_MANAGER_INTERNAL_H__
#define __TIZEN_MEDIA_SOUND_MANAGER_INTERNAL_H__

#include "sound_manager.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @file sound_manager_internal.h
 * @brief This file contains the Sound Manager Internal API.
 */

#define SOUND_TYPE_NUM                SOUND_TYPE_VOICE + 1

/**
 * @internal
 * @brief Enumeration for session type.
 * @since_tizen 2.4
 */
typedef enum
{
	SOUND_SESSION_TYPE_CALL = SOUND_SESSION_TYPE_VOIP + 1,    /**< Call type */
	SOUND_SESSION_TYPE_VIDEOCALL,                             /**< VideoCall type */
	SOUND_SESSION_TYPE_INTERNAL_NUM,
} sound_session_type_internal_e;

/**
 * @internal
 * @brief Enumeration for call session mode.
 * @since_tizen 2.3.1
 */
typedef enum {
	SOUND_SESSION_CALL_MODE_RINGTONE = 0,                /**< call mode for ringtone */
	SOUND_SESSION_CALL_MODE_VOICE_WITH_BUILTIN_RECEIVER, /**< call mode for during call with built-in receiver */
	SOUND_SESSION_CALL_MODE_VOICE_WITH_BUILTIN_SPEAKER,  /**< call mode for during call with built-in speaker */
	SOUND_SESSION_CALL_MODE_VOICE_WITH_AUDIO_JACK,       /**< call mode for during call with audio jack */
	SOUND_SESSION_CALL_MODE_VOICE_WITH_BLUETOOTH,        /**< call mode for during call with bluetooth */
} sound_session_call_mode_e;

/**
 * @brief Sets the application's sound session type for internal usage.
 * @since_tizen 2.4
 * @param[in] type The session type to set
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SOUND_MANAGER_ERROR_NOT_SUPPORTED Not supported
 * @retval #SOUND_MANAGER_ERROR_INTERNAL Internal error inside the sound system
 * @retval #SOUND_MANAGER_ERROR_POLICY Noncompliance with the sound system policy
 * @see sound_manager_get_session_type()
 * @see sound_manager_set_call_session_mode()
 * @see sound_manager_get_call_session_mode()
 */
int sound_manager_set_session_type_internal(sound_session_type_internal_e type);

/**
 * @internal
 * @brief Sets the mode of the call sound session.
 * @since_tizen 2.3.1
 * @param[in] mode The call session mode
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SOUND_MANAGER_ERROR_NOT_SUPPORTED Not supported
 * @retval #SOUND_MANAGER_ERROR_INTERNAL Internal error inside the sound system
 * @retval #SOUND_MANAGER_ERROR_POLICY Noncompliance with the sound system policy
 * @pre Call sound_manager_set_session_type(SOUND_SESSION_TYPE_CALL) before calling this function.
 * @see sound_manager_set_session_type()
 * @see sound_manager_get_session_type()
 * @see sound_manager_get_call_session_mode()
 */
int sound_manager_set_call_session_mode(sound_session_call_mode_e mode);

/**
 * @internal
 * @brief Gets the mode of the call sound session.
 * @since_tizen 2.3.1
 * @param[out] mode The call session mode
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SOUND_MANAGER_ERROR_NOT_SUPPORTED Not supported
 * @retval #SOUND_MANAGER_ERROR_INTERNAL Internal error inside the sound system
 * @retval #SOUND_MANAGER_ERROR_POLICY Noncompliance with the sound system policy
 * @pre Call sound_manager_set_session_type(SOUND_SESSION_TYPE_CALL) before calling this function.
 * @see sound_manager_set_session_type()
 * @see sound_manager_get_session_type()
 * @see sound_manager_set_call_session_mode()
 */
int sound_manager_get_call_session_mode(sound_session_call_mode_e *mode);

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_MEDIA_SOUND_MANAGER_INTERNAL_H__ */
