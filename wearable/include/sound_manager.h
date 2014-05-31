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




#ifndef __TIZEN_MEDIA_SOUND_MANAGER_H__
#define __TIZEN_MEDIA_SOUND_MANAGER_H__

#include <tizen.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define SOUND_MANAGER_ERROR_CLASS          TIZEN_ERROR_MULTIMEDIA_CLASS | 0x30

/**
 * @file sound_manager.h
 * @brief This file contains the Sound Manager API
 */

/**
 * @addtogroup CAPI_MEDIA_SOUND_MANAGER_MODULE
 * @{
 */

/**
 * @brief Enumerations of sound type
 */
typedef enum
{
    SOUND_TYPE_SYSTEM,          /**< Sound type for system */
    SOUND_TYPE_NOTIFICATION,    /**< Sound type for notifications */
    SOUND_TYPE_ALARM,           /**< Sound type for alarm */
    SOUND_TYPE_RINGTONE,        /**< Sound type for ringtones */
    SOUND_TYPE_MEDIA,           /**< Sound type for media */
    SOUND_TYPE_CALL,            /**< Sound type for call */
    SOUND_TYPE_VOIP,            /**< Sound type for voip */
    SOUND_TYPE_SVOICE,          /**< Sound type for svoice */
    SOUND_TYPE_FIXED,           /**< Sound type for fixed volume */
    SOUND_TYPE_FIXED_AF,        /**< Sound type for fixed volume for AF */
    SOUND_TYPE_FIXED_SHUTTER1,  /**< Sound type for fixed volume for Shutter1 */
    SOUND_TYPE_FIXED_SHUTTER2,  /**< Sound type for fixed volume for Shutter2 */
    SOUND_TYPE_FIXED_CAMCORDING,/**< Sound type for fixed volume for Camcording */
} sound_type_e;

/**
 * @brief Enumerations of volume key type
 */
typedef enum
{
    VOLUME_KEY_TYPE_NONE=-1,          /**< Volume key type for current played sound */
    VOLUME_KEY_TYPE_SYSTEM=0,          /**< Volume key type for system sound */
    VOLUME_KEY_TYPE_NOTIFICATION,    /**< Volume key type for notifications sound*/
    VOLUME_KEY_TYPE_ALARM,           /**< Volume key type for alarm sound */
    VOLUME_KEY_TYPE_RINGTONE,        /**< Volume key type for ringtones sound */
    VOLUME_KEY_TYPE_MEDIA,           /**< Volume key type for media sound */
    VOLUME_KEY_TYPE_CALL,            /**< Volume key type for call sound */
    VOLUME_KEY_TYPE_VOIP,            /**< Volume key type for voip sound */
    VOLUME_KEY_TYPE_SVOICE,          /**< Volume key type for svoice sound */
} volume_key_type_e;

/**
 * @brief error codes for sound manager
 */
typedef enum{
    SOUND_MANAGER_ERROR_NONE              = TIZEN_ERROR_NONE,                    /**< Successful */
    SOUND_MANAGER_ERROR_OUT_OF_MEMORY     = TIZEN_ERROR_OUT_OF_MEMORY,           /**< Out of memory */
    SOUND_MANAGER_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER,       /**< Invalid parameter */
    SOUND_MANAGER_ERROR_INVALID_OPERATION = TIZEN_ERROR_INVALID_OPERATION,       /**< Invalid operation */
    SOUND_MANAGER_ERROR_NO_PLAYING_SOUND  = SOUND_MANAGER_ERROR_CLASS | 01,      /**< No playing sound */
    SOUND_MANAGER_ERROR_NO_OPERATION      = SOUND_MANAGER_ERROR_CLASS | 02,      /**< No operation */
    SOUND_MANAGER_ERROR_INTERNAL          = SOUND_MANAGER_ERROR_CLASS | 03,      /**< Internal error*/
    SOUND_MANAGER_ERROR_POLICY            = SOUND_MANAGER_ERROR_CLASS | 04,      /**< Policy error*/
    SOUND_MANAGER_ERROR_POLICY_BLOCKED_BY_CALL  = SOUND_MANAGER_ERROR_CLASS | 05,   /**< Policy blocked by call error*/
    SOUND_MANAGER_ERROR_POLICY_BLOCKED_BY_ALARM = SOUND_MANAGER_ERROR_CLASS | 06,   /**< Policy blocked by alarm error*/
    SOUND_MANAGER_ERROR_CAPTURE_ONLY  = SOUND_MANAGER_ERROR_CLASS | 07,      /**< Capture Only */
} sound_manager_error_e;

/**
 * @brief Enumerations of session type
 */
typedef enum{
	SOUND_SESSION_TYPE_SHARE = 0,			/**< Share type : shares it's session with other share type application. */
	SOUND_SESSION_TYPE_EXCLUSIVE,			/**< Exclusive type : make previous session stop.*/
	SOUND_SESSION_TYPE_ALARM,			/**< Alarm type */
	SOUND_SESSION_TYPE_EMERGENCY,			/**< Emergency type */
	SOUND_SESSION_TYPE_NOTIFICATION,		/**< Notification type */
} sound_session_type_e;

/**
 * @brief Enumerations of session watch type
 */
typedef enum{
	SOUND_SESSION_WATCH_TYPE_CALL = 0,    /**< Call type */
	SOUND_SESSION_WATCH_TYPE_VIDEO_CALL,  /**< Video Call type */
	SOUND_SESSION_WATCH_TYPE_ALARM,       /**< Alarm type */
	SOUND_SESSION_WATCH_TYPE_AV_RECORD,   /**< Audio/Video Record type */
	SOUND_SESSION_WATCH_TYPE_NUM
} sound_session_watch_type_e;

/**
 * @brief Enumerations of session watch state
 */
typedef enum{
	SOUND_SESSION_WATCH_STATE_STOP = 0,   /**< Stop */
	SOUND_SESSION_WATCH_STATE_START,      /**< Start */
	SOUND_SESSION_WATCH_STATE_NUM
} sound_session_watch_state_e;

/**
 * @brief Enumerations of session notification
 */
typedef enum{
	SOUND_SESSION_NOTIFY_STOP = 0, 			/**< Stop : session of application has interrupted by policy. */
	SOUND_SESSION_NOTIFY_RESUME, 		   /**< Resume : session interrupt of application has ended. */
} sound_session_notify_e;

/**
 * @brief Enumerations of audio input device type.
 */
typedef enum{
	SOUND_DEVICE_IN_MIC = 0x01, /**< Device builtin mic. */
	SOUND_DEVICE_IN_WIRED_ACCESSORY = 0x02,  	/**< Wired input devices */
	SOUND_DEVICE_IN_BT_SCO = 0x04,  	/**< Bluetooth SCO device */
} sound_device_in_e;

/**
 * @brief Enumerations of audio output device type.
 */
typedef enum{
	SOUND_DEVICE_OUT_SPEAKER = 0x01<<8, /**< Device builtin speaker */
	SOUND_DEVICE_OUT_RECEIVER = 0x02<<8, /**< Device builtin receiver */
	SOUND_DEVICE_OUT_WIRED_ACCESSORY = 0x04<<8,  	/**< Wired output devices such as headphone, headset, and so on. */
	SOUND_DEVICE_OUT_BT_SCO = 0x08<<8, /**< Bluetooth SCO device */
	SOUND_DEVICE_OUT_BT_A2DP = 0x10<<8,	/**< Bluetooth A2DP device */
	SOUND_DEVICE_OUT_DOCK = 0x020<<8,	/**< DOCK device */
	SOUND_DEVICE_OUT_HDMI = 0x040<<8,	/**< HDMI device */
	SOUND_DEVICE_OUT_MIRRORING = 0x080<<8,	/**< MIRRORING device */
	SOUND_DEVICE_OUT_WFD = SOUND_DEVICE_OUT_MIRRORING,	/**< WFD device : Will be deprecated */
	SOUND_DEVICE_OUT_USB_AUDIO = 0x100<<8,	/**< USB Audio device */
	SOUND_DEVICE_OUT_MULTIMEDIA_DOCK = 0x200<<8,	/**< Multimedia DOCK device */
} sound_device_out_e;

/**
 * @brief Enumerations of route type.
 */
typedef enum{
	SOUND_ROUTE_OUT_SPEAKER = SOUND_DEVICE_OUT_SPEAKER, /**< Routing audio output to builtin device such as internal speaker. */
	SOUND_ROUTE_OUT_RECEIVER = SOUND_DEVICE_OUT_RECEIVER, /**< Routing audio output to builtin device such as internal receiver. */
	SOUND_ROUTE_OUT_WIRED_ACCESSORY = SOUND_DEVICE_OUT_WIRED_ACCESSORY,/**< Routing audio output to wired accessory such as headphone, headset, and so on. */
	SOUND_ROUTE_OUT_BLUETOOTH = SOUND_DEVICE_OUT_BT_A2DP, /**< Routing audio output to bluetooth A2DP. */
	SOUND_ROUTE_OUT_DOCK = SOUND_DEVICE_OUT_DOCK, /**< Routing audio output to DOCK */
	SOUND_ROUTE_OUT_HDMI = SOUND_DEVICE_OUT_HDMI, /**< Routing audio output to HDMI */
	SOUND_ROUTE_OUT_MIRRORING = SOUND_DEVICE_OUT_MIRRORING, /**< Routing audio output to MIRRORING */
	SOUND_ROUTE_OUT_WFD = SOUND_ROUTE_OUT_MIRRORING, /**< Routing audio output to WFD : Will be deprecated  */
	SOUND_ROUTE_OUT_USB_AUDIO = SOUND_DEVICE_OUT_USB_AUDIO, /**< Routing audio output to USB Audio */
	SOUND_ROUTE_OUT_MULTIMEDIA_DOCK = SOUND_DEVICE_OUT_MULTIMEDIA_DOCK, /**< Routing audio output to Multimedia DOCK */
	SOUND_ROUTE_IN_MIC = SOUND_DEVICE_IN_MIC, /**< Routing audio input to device builtin mic. */
	SOUND_ROUTE_IN_WIRED_ACCESSORY = SOUND_DEVICE_IN_WIRED_ACCESSORY, /**< Routing audio input to wired accessory. */
	SOUND_ROUTE_IN_MIC_OUT_RECEIVER = SOUND_DEVICE_IN_MIC |SOUND_DEVICE_OUT_RECEIVER, /**< Routing audio input to device builtin mic and routing audio output to builtin receiver*/
	SOUND_ROUTE_IN_MIC_OUT_SPEAKER = SOUND_DEVICE_IN_MIC |SOUND_DEVICE_OUT_SPEAKER , /**< Routing audio input to device builtin mic and routing audio output to builtin speaker */
	SOUND_ROUTE_IN_MIC_OUT_HEADPHONE = SOUND_DEVICE_IN_MIC | SOUND_DEVICE_OUT_WIRED_ACCESSORY,/**< Routing audio input to device builtin mic and routing audio output to headphone */
	SOUND_ROUTE_INOUT_HEADSET = SOUND_DEVICE_IN_WIRED_ACCESSORY | SOUND_DEVICE_OUT_WIRED_ACCESSORY,	/**< Routing audio input and output to headset*/
	SOUND_ROUTE_INOUT_BLUETOOTH = SOUND_DEVICE_IN_BT_SCO |SOUND_DEVICE_OUT_BT_SCO /**< Routing audio input and output to bluetooth SCO */
} sound_route_e;

/**
 * @brief Enumerations of call session type
 */
typedef enum{
	SOUND_CALL_SESSION_TYPE_CALL = 0,	/**< call type */
	SOUND_CALL_SESSION_TYPE_VOIP = 1,	/**<  voip type */
	SOUND_SESSION_TYPE_CALL = 0,
	SOUND_SESSION_TYPE_VOIP = 1,
	SOUND_SESSION_TYPE_VIDEOCALL = 2,
} sound_call_session_type_e;

/**
 * @brief Enumerations of communication session type
 */
typedef enum{
	SOUND_CALL_SESSION_MODE_VOICE = 0,		/**< normal talking mode */
	SOUND_CALL_SESSION_MODE_RINGTONE,		/**< ringtone mode */
	SOUND_CALL_SESSION_MODE_MEDIA,			/**< notification sound in call*/
	SOUND_CALL_SESSION_MODE_VOICE_ANSWER_PLAY,	/**< play audio over voice call(for Answer memo) */
	SOUND_CALL_SESSION_MODE_VOICE_ANSWER_REC,	/**< record audio over voice call(for Answer memo) */
} sound_call_session_mode_e;

/**
 * @brief Enumerations of multiple session type
 */
typedef enum{
	SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION = 0,  /**< voice recognition */
	SOUND_MULTI_SESSION_TYPE_RECORD_AUDIO,           /**< record audio */
	SOUND_MULTI_SESSION_TYPE_RECORD_VIDEO,           /**< record video */
} sound_multi_session_type_e;

/**
 * @brief Enumerations of multiple session option
 */
typedef enum{
	SOUND_MULTI_SESSION_OPT_RESUME_OTHERS = 0,       /**< resume others paused by it */
	SOUND_MULTI_SESSION_OPT_MIX_WITH_OTHERS,         /**< mix with other share type session (share) */
	SOUND_MULTI_SESSION_OPT_PAUSE_OTHERS,            /**< pause other share type session (exclusive) */
	SOUND_MULTI_SESSION_OPT_RESET_OTHERS_RESUME_INFO /**< reset resumption information of others paused by it */
} sound_multi_session_option_e;

/**
 * @brief Enumerations of multiple session mode
 */
typedef enum{
	SOUND_MULTI_SESSION_MODE_INIT = 5,        /**< initial mode */
	SOUND_MULTI_SESSION_MODE_VR_NORMAL,       /**< normal mode for voice recognition */
	SOUND_MULTI_SESSION_MODE_VR_DRIVE,        /**< drive mode for voice recognition */
	SOUND_MULTI_SESSION_MODE_RECORD_STEREO,   /**< stereo audio recording mode for AV recording */
	SOUND_MULTI_SESSION_MODE_RECORD_STEREO_FOR_INTERVIEW,      /**< directional stereo audio recording mode for interview */
	SOUND_MULTI_SESSION_MODE_RECORD_STEREO_FOR_CONVERSATION,   /**< directional stereo audio recording mode for conversation */
	SOUND_MULTI_SESSION_MODE_RECORD_MONO,   /**< mono audio recording mode for voicerecording */
} sound_multi_session_mode_e;

/**
 * @brief Enumerations of sound interrupted type
 */
typedef enum
{
       SOUND_INTERRUPTED_COMPLETED = 0, 				/**< Interrupt completed*/
       SOUND_INTERRUPTED_BY_MEDIA, 				/**< Interrupted by non-resumable media application*/
       SOUND_INTERRUPTED_BY_CALL,						/**< Interrupted by incoming call*/
       SOUND_INTERRUPTED_BY_EARJACK_UNPLUG,			/**< Interrupted by unplugging headphone*/
       SOUND_INTERRUPTED_BY_RESOURCE_CONFLICT,		/**< Interrupted by resource conflict*/
       SOUND_INTERRUPTED_BY_ALARM,					/**< Interrupted by alarm*/
       SOUND_INTERRUPTED_BY_EMERGENCY,					/**< Interrupted by emergency*/
       SOUND_INTERRUPTED_BY_RESUMABLE_MEDIA, 				/**< Interrupted by resumable media application*/
       SOUND_INTERRUPTED_BY_NOTIFICATION,					/**< Interrupted by notification*/
} sound_interrupted_code_e;

/**
 * @brief Sound call session handle type.
 */
typedef struct sound_call_session_s *sound_call_session_h;

/**
 * @brief Sound multiple session handle type.
 */
typedef struct sound_multi_session_s *sound_multi_session_h;

/**
 * @brief Called when the sound session notification has occured.
 * @param[in]   notify	The sound session notification
 * @param[in]   user_data	The user data passed from the callback registration function
 * @pre You should register this callback by sound_manager_set_session_notify_cb()
 * @see sound_manager_set_session_notify_cb()
 */
typedef void (*sound_session_notify_cb) (sound_session_notify_e notify, void *user_data);

/**
 * @brief Called when the playing sound was interrupted.
 * @param[in]   code	The interrupted code
 * @param[in]   user_data	The user data passed from the callback registration function
 * @pre You should register this callback by sound_manager_set_interrupted_cb()
 * @see sound_manager_set_interrupted_cb()
 */
typedef void(* sound_interrupted_cb)(sound_interrupted_code_e code, void *user_data);

/**
 * @brief Called when the interest session state was changed.
 * @param[in]   type	The type of the interest session
 * @param[in]   state	The state of the interest session
 * @param[in]   user_data	The user data passed from the callback registration function
 * @pre You should register this callback by sound_manager_set_watch_session_cb()
 * @see sound_manager_set_watch_session_cb()
 */
typedef void(* sound_session_watch_cb)(sound_session_watch_type_e type, sound_session_watch_state_e state, void *user_data);

/**
 * @brief Called when the system volume has changed.
 * @param[in]   type	The sound type of changed volume
 * @param[in]   volume	The new volume value
 * @param[in]   user_data	The user data passed from the callback registration function
 * @pre sound_manager_set_volume() will invoke this callback if you register it using sound_manager_set_volume_changed_cb()
 * @see sound_manager_set_volume_changed_cb()
 * @see sound_manager_unset_volume_changed_cb()
 */
typedef void (*sound_manager_volume_changed_cb)(sound_type_e type, unsigned int volume, void *user_data);

/**
 * @brief Called when the turn off all sounds state has changed.
 * @param[in]   user_data	The user data passed from the callback registration function
 * @param[in]   muteall	The new muteall value
 * @pre sound_manager_set_muteall() will invoke this callback if you register it using sound_manager_set_muteall_changed_cb()
 * @see sound_manager_set_muteall_changed_cb()
 * @see sound_manager_unset_muteall_changed_cb()
 */
typedef void (*sound_manager_muteall_changed_cb)(bool muteall, void *user_data);

/**
 * @brief Gets the maximum volume level supported for a particular sound type
 * @param[in]		type The sound type
 * @param[out]	max	The maximum volume level
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_set_volume()
 */
int sound_manager_get_max_volume(sound_type_e type, int *max);

/**
 * @brief Sets the volume level specified for a particular sound type
 * @param[in]		type The sound type
 * @param[out]	volume	The volume level to be set
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_get_max_volume()
 * @see sound_manager_get_volume()
 */
int sound_manager_set_volume(sound_type_e type, int volume);

/**
 * @brief Gets the volume level specified for a particular sound type
 * @param[in]		type The sound type
 * @param[out]	volume	The current volume level
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_get_max_volume()
 * @see sound_manager_set_volume()
 */
int sound_manager_get_volume(sound_type_e type, int *volume);

/**
 * @brief Gets the current playing sound type
 * @param[out]		type The current sound type
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SOUND_MANAGER_ERROR_NO_PLAYING_SOUND No playing sound
 * @see player_set_sound_type()
 * @see audio_out_create()
 * @see wav_player_start()
 */
int sound_manager_get_current_sound_type(sound_type_e *type);

/**
 * @brief Sets the volume balance value. The balance value controls Left/right channel volume.
 * @param[in]		The balance value to be set. The balance range is [-1,1].
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_get_balance()
 */
int sound_manager_set_balance(float balance);

/**
 * @brief Gets the volume balance value. The balance value controls Left/right channel volume.
 * @param[out]		The current balance value. The balance range is [-1,1].
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see ound_manager_set_balance)
 */
int sound_manager_get_balance(float *balance);

/**
 * @brief Sets the muteall value. The muteall value controls all sounds turn on/off.
 * @param[in]		The muteall value to be set. False means  all sounds turn on , true means all sounds turn off
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_set_muteall()
 */
int sound_manager_set_muteall(bool onoff);

/**
 * @brief Gets the muteall value. The muteall value controls all sounds turn on/off .
 * @param[out]		The current muteall value.False  means  all sounds turn on , ture means all sounds turn off
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_get_muteall)
 */
int sound_manager_get_muteall(bool *onoff);

/**
 * @brief Registers a callback function to be invoked when the volume level is changed.
 * @param[in]	callback	Callback function to indicate change in volume
 * @param[in]	user_data	The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @post  sound_manager_volume_changed_cb() will be invoked
 * @see sound_manager_unset_volume_changed_cb()
 * @see sound_manager_volume_changed_cb()
 */
int sound_manager_set_volume_changed_cb(sound_manager_volume_changed_cb callback, void *user_data);

/**
 * @brief Unregisters the volume change callback
 * @see sound_manager_set_volume_changed_cb()
 */
void sound_manager_unset_volume_changed_cb(void);

/**
 * @brief Registers a callback function to be invoked when the all sounds turn on/off is changed.
 * @param[in]	callback	Callback function to indicate change in all sounds turn on/off
 * @param[in]	user_data	The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @post  sound_manager_muteall_changed_cb() will be invoked
 * @see sound_manager_unset_muteall_changed_cb()
 * @see sound_manager_muteall_changed_cb()
 */
int sound_manager_set_muteall_changed_cb(sound_manager_muteall_changed_cb callback, void* user_data);

/**
 * @brief Unregisters the state of all sounds turn on/off change callback
 * @see sound_manager_set_muteall_changed_cb()
 */
void sound_manager_unset_muteall_changed_cb(void);

/**
 * @brief Gets the A2DP activation information.
 * @remarks If @a connected is @c true,  @a bt_name must be released with free() by you. If @a connected is @c false, @a bt_name is set to NULL.
 * @param[out] connected The Bluetooth A2DP connection status (@c true = connected, @c false = disconnected)
 * @param[out] bt_name The Bluetooth A2DP connected device name
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SOUND_MANAGER_ERROR_INVALID_OPERATION Invalid operation
 */
int sound_manager_get_a2dp_status(bool *connected, char **bt_name);

/**
 * @brief Sets the application's sound session type
 * @param[in] type The session type to set
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 */
int sound_manager_set_session_type(sound_session_type_e type);

/**
 * @brief Gets the application's sound session type
 * @param[in] type The session type
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 */
int sound_manager_get_session_type(sound_session_type_e *type);

/**
 * @brief Registers a callback function to be invoked when the sound session notification is occured.
 * @param[in]	callback	The session notify callback function
 * @param[in]	user_data	The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @post  sound_session_notify_cb() will be invoked
 * @see sound_manager_unset_session_notify_cb()
 * @see sound_session_notify_cb()
 */
int sound_manager_set_session_notify_cb(sound_session_notify_cb callback, void *user_data);

/**
 * @brief Unregisters the callback function which is called when the session notification is occured
 * @see sound_manager_set_session_notify_cb()
 */
void sound_manager_unset_session_notify_cb(void);

/**
 * @brief Registers a callback function to be invoked when the playing sound was interrupted.
 * @param[in]	callback	The interrupted callback function
 * @param[in]	user_data	The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @post  sound_interrupted_cb() will be invoked
 * @see sound_manager_unset_interrupted_cb()
 * @see sound_interrupted_cb()
 */
int sound_manager_set_interrupted_cb(sound_interrupted_cb callback, void *user_data);

/**
 * @brief Unregisters the callback function which is called when the playing sound was interrupted
 * @see sound_manager_set_interrupted_cb()
 */
void sound_manager_unset_interrupted_cb(void);

/**
 * @brief Registers a callback function to be invoked when the watched session was activated.
 * @param[in]   type	The session type to be watched
 * @param[in]   callback The watch callback function
 * @param[in]   user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SOUND_MANAGER_ERROR_INVALID_OPERATION Invalid operation
 * @post  sound_session_watch_cb() will be invoked
 * @see sound_manager_unset_watch_cb()
 * @see sound_session_watch_cb()
 */
int sound_manager_set_watch_cb(sound_session_watch_type_e type, sound_session_watch_cb callback, void *user_data);

/**
 * @brief Unregisters the callback function which is called when the watched session was activated
 * @param[in]   type	The watched session type to be removed
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SOUND_MANAGER_ERROR_INVALID_OPERATION Invalid operation
 * @see sound_manager_set_watch_cb()
 */
int sound_manager_unset_watch_cb(sound_session_watch_type_e type);

/**
 * @brief Sets the volume key type
 * @param[in] type The volume key type to set
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 */
int sound_manager_set_volume_key_type(volume_key_type_e type);

/**
 * @brief Gets called iteratively to notify you of available route.
 * @param[in]   route The available route
 * @param[in]   user_data The user data passed from the foreach function
 * @return @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @pre  sound_manager_foreach_available_route() will invoke this callback.
 * @see sound_manager_foreach_available_route()
 */
typedef bool(* sound_available_route_cb)(sound_route_e route, void *user_data);

/**
 * @brief Called when the available audio route is changed.
 * @param[in]   route The audio route
 * @param[in]   available The status of given route
 * @param[in]   user_data The user data passed from the foreach function
 * @pre  sound_manager_foreach_available_route() will invoke this callback.
 * @see sound_manager_foreach_available_route()
 */
typedef void(* sound_available_route_changed_cb)(sound_route_e route, bool available, void *user_data);

/**
 * @brief Called when the audio route is changed.
 * @param[in]   route The audio route
 * @param[in]   user_data The user data passed from the callback registration function
 * @pre  You should register this callback by sound_manager_set_active_device_changed_cb()
 * @see sound_manager_set_active_device_changed_cb()
 */
typedef void(* sound_active_device_changed_cb)(sound_device_in_e in, sound_device_out_e out, void *user_data);

/**
 * @brief Retrieves all available audio routes by invoking a specific callback for each valid route.
 * @param[in]	callback	The session notify callback function
 * @param[in]	user_data	The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @post  sound_available_route_cb() will be invoked
 * @see sound_available_route_cb()
 */
int sound_manager_foreach_available_route (sound_available_route_cb callback, void *user_data);

/**
 * @brief Changes the audio routes.
 * @param[in] route The route to set
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_get_active_device()
 */
int sound_manager_set_active_route (sound_route_e route);

/**
 * @brief Changes the audio routes.
 * @param[in] void
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 */
int sound_manager_set_active_route_auto (void);

/**
 * @brief Changes the audio route.
 * @param[out] in The current sound input device
 * @param[out] in The current sound output device
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_set_active_route()
 */
int sound_manager_get_active_device (sound_device_in_e *in, sound_device_out_e *out);

/**
 * @brief Check if given audio route is available or not.
 * @param[in] route The route to set
 * @return 0 on success, otherwise a negative error value.
 * @return @c true if the specified route is supported, \n else @c false
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 */
bool sound_manager_is_route_available (sound_route_e route);

/**
 * @brief Registers a callback function to be invoked when the available status is changed.
 * @param[in]	callback	The available status changed callback function
 * @param[in]	user_data	The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @post  sound_available_route_changed_cb() will be invoked
 * @see sound_manager_unset_available_route_changed_cb()
 * @see sound_available_route_changed_cb()
 */
int sound_manager_set_available_route_changed_cb (sound_available_route_changed_cb callback, void *user_data);

/**
 * @brief Unregisters the callback function.
 * @see sound_manager_set_available_route_changed_cb()
 */
void sound_manager_unset_available_route_changed_cb (void);

/**
 * @brief Registers a callback function to be invoked when the audio device is changed.
 * @param[in]	callback	The session notify callback function
 * @param[in]	user_data	The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Success
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @post  sound_active_device_changed_cb() will be invoked
 * @see sound_manager_unset_active_device_changed_cb()
 * @see sound_active_device_changed_cb()
 */
int sound_manager_set_active_device_changed_cb (sound_active_device_changed_cb callback, void *user_data);

/**
 * @brief Unregisters the callback function which is called when the route notification is occured.
 * @see sound_manager_set_active_device_changed_cb()
 */
void sound_manager_unset_active_device_changed_cb (void);

/**
 * @brief Creates a call session handle.
 * @remarks @a session must be released sound_manager_call_session_destroy() by you.
 * @param[out]  session  A new handle to call session
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SOUND_MANAGER_OUT_OF_MEMORY Out of memory
 * @see sound_manager_call_session_destroy()
 */
int sound_manager_call_session_create(sound_call_session_type_e type, sound_call_session_h *session);

/**
 * @brief Sets the call session mode.
 *
 * @param[in]   session The handle to call session
 * @param[in]   mode  The call session mode
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_call_session_get_mode()
 */
int sound_manager_call_session_set_mode(sound_call_session_h session, sound_call_session_mode_e mode);

/**
 * @brief Gets the call session mode.
 *
 * @param[in]   session The handle to call session
 * @param[out]   mode  The call session mode
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_call_session_set_mode()
 */
int sound_manager_call_session_get_mode(sound_call_session_h session, sound_call_session_mode_e *mode);

/**
 * @brief Destroys the call session handle.
 *
 * @param[in]		session The handle to call session to be destroyed
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_call_session_create()
 */
int sound_manager_call_session_destroy(sound_call_session_h session);

/**
 * @brief Creates a multiple session handle.
 * @remarks @a session must be released sound_manager_multi_session_destroy() by you.
 * @param[out]   session  A new handle to multiple session
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SOUND_MANAGER_OUT_OF_MEMORY Out of memory
 * @see sound_manager_multi_session_destroy()
 */
int sound_manager_multi_session_create(sound_multi_session_type_e type, sound_multi_session_h *session);

/**
 * @brief Queries whether if the multiple session mode is available
 *
 * @param[in]   session  The handle to multiple session
 * @param[in]   mode  The multiple session mode
 * @param[out]   available  The result of this API (true or false)
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see  sound_manager_multiple_session_set_mode()
 */
int sound_manager_multi_session_mode_is_available(sound_multi_session_h session, sound_multi_session_mode_e mode, bool *available);

/**
 * @brief Sets the multiple session mode.
 *
 * @param[in]   session  The handle to multiple session
 * @param[in]   mode     The multiple session mode
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_multi_session_get_mode()
 * @see sound_manager_multi_session_mode_is_available()
 */
int sound_manager_multi_session_set_mode(sound_multi_session_h session, sound_multi_session_mode_e mode);

/**
 * @brief Gets the multiple session mode.
 *
 * @param[in]   session The handle to multiple session
 * @param[out]  mode    The multiple session mode
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_multiple_session_set_mode()
 */
int sound_manager_multi_session_get_mode(sound_multi_session_h session, sound_multi_session_mode_e *mode);

/**
 * @brief Sets the multiple session option.
 *
 * @param[in]   session  The handle to multiple session
 * @param[in]   type     The multiple session option type
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SOUND_MANAGER_ERROR_INTERNAL Internal
 * @retval #SOUND_MANAGER_ERROR_POLICY Policy
 * @retval #SOUND_MANAGER_ERROR_POLICY_BLOCKED_BY_CALL Policy blocked by call
 * @retval #SOUND_MANAGER_ERROR_POLICY_BLOCKED_BY_ALARM Policy blocked by alarm
 * @see sound_manager_multi_session_get_option()
 */
int sound_manager_multi_session_set_option(sound_multi_session_h session, sound_multi_session_option_e type);

/**
 * @brief Gets the multiple session option.
 *
 * @param[in]   session The handle to multiple session
 * @param[out]  option  The multiple session option type
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_multiple_session_set_option()
 */
int sound_manager_multi_session_get_option(sound_multi_session_h session, sound_multi_session_option_e *option);

/**
 * @brief Destroys the multiple session handle.
 *
 * @param[in]   session The handle to multiple session to be destroyed
 * @return 0 on success, otherwise a negative error value.
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @see sound_manager_multi_session_create()
 */
int sound_manager_multi_session_destroy(sound_multi_session_h session);

/**
 * @brief set microphone mute during call
 *
 * @param[in] sound type. Supported sound types are SOUND_TYPE_CALL, SOUND_TYPE_VOIP
 * @param[in] TRUE to mute, FALSE to unmute
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 */
int sound_manager_set_call_mute(sound_type_e type, int mute);

/**
 * @brief get mute status of the microphone during call
 *
 * @param[in] sound type. Supported sound types are SOUND_TYPE_CALL, SOUND_TYPE_VOIP
 * @param[out] mute
 * @retval #SOUND_MANAGER_ERROR_NONE Successful
 * @retval #SOUND_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 */
int sound_manager_get_call_mute(sound_type_e type, int *mute);


#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_MEDIA_SOUND_MANAGER_H__ */
