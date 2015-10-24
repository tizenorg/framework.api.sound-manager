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

#include <sound_manager.h>
#include <sound_manager_private.h>

extern _session_interrupt_info_s g_session_interrupt_cb_table;
extern _session_mode_e g_cached_session_mode;

int sound_manager_set_session_type_internal(sound_session_type_internal_e type)
{
	int ret = MM_ERROR_NONE;
	int cur_session = -1;
	int new_session = MM_SESSION_TYPE_MEDIA;

	LOGI(">> enter : type=%d", type);

	if(type < SOUND_SESSION_TYPE_CALL || type >= SOUND_SESSION_TYPE_INTERNAL_NUM)
		return __convert_sound_manager_error_code(__func__, __LINE__, MM_ERROR_INVALID_ARGUMENT);

	switch(type) {
	case SOUND_SESSION_TYPE_CALL:
		new_session = MM_SESSION_TYPE_CALL;
		break;
	case SOUND_SESSION_TYPE_VIDEOCALL:
		new_session = MM_SESSION_TYPE_VIDEOCALL;
		break;
	default:
		return __convert_sound_manager_error_code(__func__, __LINE__, MM_ERROR_INVALID_ARGUMENT);
	}

	/* valid session check */
	ret = mm_session_get_current_type(&cur_session);
	if(ret == 0) {
		if (cur_session == MM_SESSION_TYPE_VIDEOCALL ||
			cur_session == MM_SESSION_TYPE_CALL ) {
			return __convert_sound_manager_error_code(__func__, __LINE__, MM_ERROR_POLICY_INTERNAL);
		}
	}

	if(g_session_interrupt_cb_table.is_registered) {
		ret = mm_session_finish();
		if (ret != MM_ERROR_NONE) {
			return __convert_sound_manager_error_code(__func__, __LINE__, ret);
		}
		g_session_interrupt_cb_table.is_registered = 0;
	}
	ret = mm_session_init_ex(new_session , __session_interrupt_cb, NULL);
	if(ret == 0){
		g_session_interrupt_cb_table.is_registered = 1;
	}

	g_cached_session_mode = _SESSION_MODE_NONE;

	LOGI("<< leave : type=%d, ret=0x%x", type, ret);

	return __convert_sound_manager_error_code(__func__, __LINE__, ret);
}

int sound_manager_set_call_session_mode(sound_session_call_mode_e mode)
{
	int ret = MM_ERROR_NONE;
	int session = 0;
	int session_options = 0;

	LOGI(">> enter : mode=%d", mode);

	ret = mm_session_get_current_information(&session, &session_options);
	if( ret != MM_ERROR_NONE ) {
		return __convert_sound_manager_error_code(__func__, __LINE__, ret);
	} else if (session != MM_SESSION_TYPE_CALL && session != MM_SESSION_TYPE_VIDEOCALL) {
		return __convert_sound_manager_error_code(__func__, __LINE__, MM_ERROR_POLICY_INTERNAL);
	}
	if(mode < SOUND_SESSION_CALL_MODE_RINGTONE || mode > SOUND_SESSION_CALL_MODE_VOICE_WITH_BLUETOOTH) {
		ret = MM_ERROR_INVALID_ARGUMENT;
		return __convert_sound_manager_error_code(__func__, __LINE__, ret);
	}
	ret = __set_session_mode ((_session_mode_e)mode);

	LOGI("<< leave : session=%p, mode=%d, ret=0x%x", session, mode, ret);

	return __convert_sound_manager_error_code(__func__, __LINE__, ret);
}

int sound_manager_get_call_session_mode(sound_session_call_mode_e *mode)
{
	int ret = MM_ERROR_NONE;
	int session = 0;
	int session_options = 0;
	_session_mode_e _mode = 0;

	if(mode == NULL) {
		return __convert_sound_manager_error_code(__func__, __LINE__, MM_ERROR_INVALID_ARGUMENT);
	}

	ret = mm_session_get_current_information(&session, &session_options);
	if( ret != MM_ERROR_NONE ) {
		return __convert_sound_manager_error_code(__func__, __LINE__, ret);
	} else if (session != MM_SESSION_TYPE_CALL && session != MM_SESSION_TYPE_VIDEOCALL) {
		return __convert_sound_manager_error_code(__func__, __LINE__, MM_ERROR_POLICY_INTERNAL);
	}
	ret = __get_session_mode(&_mode);
	if (ret == MM_ERROR_NONE)
		*mode = (sound_session_call_mode_e)_mode;

	LOGI("returns : session=%p, mode=%d, ret=0x%x", session, *mode, ret);

	return __convert_sound_manager_error_code(__func__, __LINE__, ret);
}
