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




#include <tet_api.h>
#include <media/sound_manager.h>

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_media_sound_manager_get_max_volume_p(void);
static void utc_media_sound_manager_get_max_volume_n(void);
static void utc_media_sound_manager_set_volume_p(void);
static void utc_media_sound_manager_set_volume_n(void);
static void utc_media_sound_manager_get_volume_p(void);
static void utc_media_sound_manager_get_volume_n(void);
static void utc_media_sound_manager_get_current_sound_type_p(void);
static void utc_media_sound_manager_get_current_sound_type_n(void);
static void utc_media_sound_manager_set_session_type_p(void);
static void utc_media_sound_manager_set_session_type_n(void);
static void utc_media_sound_manager_get_a2dp_status_p(void);
static void utc_media_sound_manager_get_a2dp_status_n(void);

static void utc_media_sound_manager_foreach_available_route_p(void);
static void utc_media_sound_manager_foreach_available_route_n(void);
static void utc_media_sound_manager_set_active_route_p(void);
static void utc_media_sound_manager_set_active_route_n(void);
static void utc_media_sound_manager_get_active_device_p(void);
static void utc_media_sound_manager_get_active_device_n(void);
static void utc_media_sound_manager_is_route_available_p(void);
static void utc_media_sound_manager_is_route_available_n(void);

static void utc_media_sound_manager_call_session_create_p(void);
static void utc_media_sound_manager_call_session_create_n(void);
static void utc_media_sound_manager_call_session_set_mode_p(void);
static void utc_media_sound_manager_call_session_set_mode_n(void);
static void utc_media_sound_manager_call_session_get_mode_p(void);
static void utc_media_sound_manager_call_session_get_mode_n(void);
static void utc_media_sound_manager_call_session_destroy_p(void);
static void utc_media_sound_manager_call_session_destroy_n(void);

static void utc_media_sound_manager_get_call_mute_p(void);
static void utc_media_sound_manager_get_call_mute_n(void);
static void utc_media_sound_manager_set_call_mute_p(void);
static void utc_media_sound_manager_set_call_mute_n(void);
static void utc_media_sound_manager_get_balance_p(void);
static void utc_media_sound_manager_get_balance_n(void);
static void utc_media_sound_manager_get_muteall_p(void);
static void utc_media_sound_manager_get_muteall_n(void);
static void utc_media_sound_manager_get_session_type_p(void);
static void utc_media_sound_manager_get_session_type_n(void);
static void utc_media_sound_manager_multi_session_create_p(void);
static void utc_media_sound_manager_multi_session_create_n(void);
static void utc_media_sound_manager_multi_session_destroy_p(void);
static void utc_media_sound_manager_multi_session_destroy_n(void);
static void utc_media_sound_manager_multi_session_get_mode_p(void);
static void utc_media_sound_manager_multi_session_get_mode_n(void);
static void utc_media_sound_manager_multi_session_get_option_p(void);
static void utc_media_sound_manager_multi_session_get_option_n(void);
static void utc_media_sound_manager_multi_session_set_mode_p(void);
static void utc_media_sound_manager_multi_session_set_mode_n(void);
static void utc_media_sound_manager_multi_session_set_option_p(void);
static void utc_media_sound_manager_multi_session_set_option_n(void);
static void utc_media_sound_manager_set_balance_p(void);
static void utc_media_sound_manager_set_balance_n(void);
static void utc_media_sound_manager_set_muteall_p(void);
//static void utc_media_sound_manager_set_muteall_n(void);
static void utc_media_sound_manager_set_volume_key_type_p(void);
static void utc_media_sound_manager_set_volume_key_type_n(void);

struct tet_testlist tet_testlist[] = {
	{ utc_media_sound_manager_get_max_volume_p , POSITIVE_TC_IDX },
	{ utc_media_sound_manager_get_max_volume_n , NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_volume_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_volume_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_get_volume_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_get_volume_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_get_current_sound_type_p , POSITIVE_TC_IDX },
	{ utc_media_sound_manager_get_current_sound_type_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_get_a2dp_status_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_get_a2dp_status_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_foreach_available_route_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_foreach_available_route_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_active_route_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_active_route_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_get_active_device_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_get_active_device_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_is_route_available_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_is_route_available_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_call_session_create_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_call_session_create_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_call_session_set_mode_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_call_session_set_mode_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_call_session_get_mode_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_call_session_get_mode_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_call_session_destroy_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_call_session_destroy_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_session_type_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_session_type_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_get_call_mute_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_get_call_mute_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_call_mute_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_call_mute_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_get_balance_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_get_balance_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_get_muteall_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_get_muteall_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_get_session_type_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_get_session_type_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_create_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_create_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_destroy_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_destroy_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_get_mode_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_get_mode_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_get_option_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_get_option_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_set_mode_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_set_mode_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_set_option_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_multi_session_set_option_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_balance_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_balance_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_muteall_p, POSITIVE_TC_IDX },
//	{ utc_media_sound_manager_set_muteall_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_volume_key_type_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_volume_key_type_n, NEGATIVE_TC_IDX },
	{ NULL, 0 },
};

static void startup(void)
{
	/* start of TC */
}

static void cleanup(void)
{
	/* end of TC */
}

static void utc_media_sound_manager_get_max_volume_p(void)
{
	int ret, max;
	char* api_name = "sound_manager_get_max_volume";
	if ((ret = sound_manager_get_max_volume(SOUND_TYPE_SYSTEM, &max)) == SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_get_max_volume_n(void)
{
	int ret, max;
	char* api_name = "sound_manager_get_max_volume";
	if ((ret = sound_manager_get_max_volume(-1, &max)) != SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_set_volume_p(void)
{
	int ret, max;
	char* api_name = "sound_manager_set_volume";
	if ((ret = sound_manager_get_max_volume(SOUND_TYPE_SYSTEM, &max)) == SOUND_MANAGER_ERROR_NONE)
	{
		if ((ret = sound_manager_set_volume(SOUND_TYPE_NOTIFICATION, max/2)) == SOUND_MANAGER_ERROR_NONE)
		{
			dts_pass(api_name);
		}
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_set_volume_n(void)
{
	int ret;
	char* api_name = "sound_manager_set_volume";
	if ((ret = sound_manager_set_volume(-1, 10)) != SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_get_volume_p(void)
{
	int ret, vol;
	char* api_name = "sound_manager_get_volume";
	if ((ret = sound_manager_get_volume(SOUND_TYPE_ALARM , &vol)) == SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_get_volume_n(void)
{
	int ret;
	char* api_name = "sound_manager_get_volume";
	if ((ret = sound_manager_get_volume(SOUND_TYPE_ALARM , NULL)) != SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_get_current_sound_type_p(void)
{
	sound_type_e type;
	int ret;
	char* api_name = "sound_manager_get_current_sound_type";
	ret = sound_manager_get_current_sound_type(&type);
	if (ret == SOUND_MANAGER_ERROR_NONE || ret == SOUND_MANAGER_ERROR_NO_PLAYING_SOUND)
	{
		dts_pass(api_name);
	}

	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_get_current_sound_type_n(void)
{
	int ret;
	char* api_name = "sound_manager_get_current_sound_type";
	if ((ret = sound_manager_get_current_sound_type(NULL)) != SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_set_session_type_p(void)
{
	int ret;
	char* api_name = "sound_manager_set_session_type";
	if ((ret = sound_manager_set_session_type(SOUND_SESSION_TYPE_SHARE)) == SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}
static void utc_media_sound_manager_set_session_type_n(void)
{
	int ret;
	char* api_name = "sound_manager_set_session_type";
	if ((ret = sound_manager_set_session_type(-1)) != SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_get_a2dp_status_p(void)
{
	bool connected;
	char *name;
	int ret;
	char* api_name = "sound_manager_get_a2dp_status";
	if ((ret = sound_manager_get_a2dp_status(&connected, &name)) == SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);	
}
static void utc_media_sound_manager_get_a2dp_status_n(void)
{
	int ret;
	char* api_name = "sound_manager_get_a2dp_status";
	if ((ret = sound_manager_get_a2dp_status(NULL, NULL)) != SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);	
}

static bool _sound_available_route_cb (sound_route_e route, void *user_data)
{
	return false;
}

static void utc_media_sound_manager_foreach_available_route_p(void)
{
	int ret;
	char* api_name = "sound_manager_foreach_available_route";
	ret = sound_manager_foreach_available_route(_sound_available_route_cb, NULL);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_foreach_available_route_n(void)
{
	int ret;
	char* api_name = "sound_manager_foreach_available_route";
	ret = sound_manager_foreach_available_route(NULL, NULL);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_active_route_p(void)
{
	int ret;
	char* api_name = "sound_manager_set_active_route";
	ret = sound_manager_set_active_route(SOUND_ROUTE_OUT_SPEAKER);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_active_route_n(void)
{
	int ret;
	char* api_name = "sound_manager_set_active_route";
	ret = sound_manager_set_active_route(SOUND_ROUTE_INOUT_BLUETOOTH+1);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_get_active_device_p(void)
{
	int ret;
	char* api_name = "sound_manager_get_active_device";
	sound_device_in_e in;
	sound_device_out_e out;
	ret = sound_manager_get_active_device(&in, &out);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_get_active_device_n(void)
{
	int ret;
	char* api_name = "sound_manager_get_active_device";
	ret = sound_manager_get_active_device(NULL, NULL);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}
static void utc_media_sound_manager_is_route_available_p(void)
{
	int ret;
	char* api_name = "sound_manager_is_route_availiable";
	ret = sound_manager_is_route_available(SOUND_ROUTE_OUT_SPEAKER);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, true);
}
static void utc_media_sound_manager_is_route_available_n(void)
{
	int ret;
	char* api_name = "sound_manager_is_route_availiable";
	ret = sound_manager_is_route_available(SOUND_ROUTE_INOUT_BLUETOOTH+1);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, true);
}

static void utc_media_sound_manager_call_session_create_p(void)
{
	int ret;
	char* api_name = "sound_manager_call_session_create";
	sound_call_session_h session;
	ret = sound_manager_call_session_create(SOUND_SESSION_TYPE_CALL, &session);
	if (ret == SOUND_MANAGER_ERROR_NONE)
		sound_manager_call_session_destroy(session);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_call_session_create_n(void)
{
	int ret;
	char* api_name = "sound_manager_call_session_create";
	ret = sound_manager_call_session_create(SOUND_SESSION_TYPE_CALL, NULL);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}
static void utc_media_sound_manager_call_session_set_mode_p(void)
{
	int ret;
	char* api_name = "sound_manager_call_session_set_mode";
	sound_call_session_h session;
	ret = sound_manager_call_session_create(SOUND_SESSION_TYPE_CALL, &session);
	if (ret != SOUND_MANAGER_ERROR_NONE) {
		dts_fail(api_name);
	}
	ret = sound_manager_call_session_set_mode (session, SOUND_CALL_SESSION_MODE_RINGTONE);
	sound_manager_call_session_destroy(session);

	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_call_session_set_mode_n(void)
{
	int ret;
	char* api_name = "sound_manager_call_session_set_mode";
	sound_call_session_h session;
	ret = sound_manager_call_session_create(SOUND_SESSION_TYPE_CALL, &session);
	if (ret != SOUND_MANAGER_ERROR_NONE) {
		dts_fail(api_name);
	}
	ret = sound_manager_call_session_set_mode (NULL, SOUND_CALL_SESSION_MODE_RINGTONE);
	sound_manager_call_session_destroy(session);

	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}
static void utc_media_sound_manager_call_session_get_mode_p(void)
{
	int ret;
	char* api_name = "sound_manager_call_session_get_mode";
	sound_call_session_h session;
	sound_call_session_mode_e mode;
	ret = sound_manager_call_session_create(SOUND_SESSION_TYPE_CALL, &session);
	if (ret != SOUND_MANAGER_ERROR_NONE) {
		dts_fail(api_name);
	}
	ret = sound_manager_call_session_get_mode (session, &mode);
	sound_manager_call_session_destroy(session);

	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_call_session_get_mode_n(void)
{
	int ret;
	char* api_name = "sound_manager_call_session_get_mode";
	sound_call_session_h session;
	ret = sound_manager_call_session_create(SOUND_SESSION_TYPE_CALL, &session);
	if (ret != SOUND_MANAGER_ERROR_NONE) {
		dts_fail(api_name);
	}
	ret = sound_manager_call_session_get_mode (NULL, NULL);
	sound_manager_call_session_destroy(session);

	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_call_session_destroy_p(void)
{
	int ret;
	char* api_name = "sound_manager_call_sessioin_destroy";
	sound_call_session_h session;
	ret = sound_manager_call_session_create(SOUND_SESSION_TYPE_CALL, &session);
	if (ret != SOUND_MANAGER_ERROR_NONE) {
		dts_fail(api_name);
	}
	ret = sound_manager_call_session_destroy(session);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_call_session_destroy_n(void)
{
	int ret;
	char* api_name = "sound_manager_call_sessioin_destroy";
	ret = sound_manager_call_session_destroy(NULL);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_get_call_mute_p(void)
{
	int ret;
	char* api_name = "sound_manager_get_call_mute";
	int mute;
	sound_type_e type=SOUND_TYPE_CALL;
	ret = sound_manager_get_call_mute(type, &mute);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_get_call_mute_n(void)
{
	int ret;
	char* api_name = "sound_manager_get_call_mute";
	sound_type_e type=SOUND_TYPE_ALARM;
	ret = sound_manager_get_call_mute(type, NULL);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_call_mute_p(void)
{
	int ret;
	char* api_name = "sound_manager_set_call_mute";
	sound_type_e type=SOUND_TYPE_CALL;
	ret = sound_manager_set_call_mute(type, true);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_call_mute_n(void)
{
	int ret;
	int mute=-10;
	char* api_name = "sound_manager_set_call_mute";
  	sound_type_e type=SOUND_TYPE_ALARM;
	if( (ret = sound_manager_set_call_mute(type, mute)) != SOUND_MANAGER_ERROR_NONE)
		dts_pass(api_name);
	if( (ret = sound_manager_get_call_mute(type, &mute)) != SOUND_MANAGER_ERROR_NONE)
		dts_pass(api_name);

	dts_message(api_name, "get mute value : %d", mute);
	if(mute!=-10)
		dts_pass(api_name);
	else
		dts_fail(api_name);
}

static void utc_media_sound_manager_get_balance_p(void)
{
	int ret;
	char* api_name = "sound_manager_get_balance";
	float balance=0.0;
	ret = sound_manager_get_balance(&balance);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_get_balance_n(void)
{
	int ret;
	char* api_name = "sound_manager_get_balance";
	ret = sound_manager_get_balance(NULL);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_get_muteall_p(void)
{
	int ret;
	bool onoff=true;
	char* api_name = "sound_manager_get_muteall";
	ret = sound_manager_get_muteall(&onoff);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_get_muteall_n(void)
{
	int ret;
	char* api_name = "sound_manager_get_muteall";
	ret = sound_manager_get_muteall(NULL);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_get_session_type_p(void)
{
	int ret;
	sound_session_type_e type;
	char* api_name = "sound_manager_get_session_type";
	ret = sound_manager_get_session_type(&type);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_get_session_type_n(void)
{
	int ret;
	char* api_name = "sound_manager_get_session_type";
	ret = sound_manager_get_session_type(NULL);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_multi_session_create_p(void)
{
	int ret;
	char* api_name = "sound_manager_multi_session_create";
	sound_multi_session_type_e type = SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION;
	sound_multi_session_h session;
	if( (ret = sound_manager_multi_session_create(type, &session)) == SOUND_MANAGER_ERROR_NONE)
	{
	    sound_manager_multi_session_destroy(session);
	    dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_multi_session_create_n(void)
{
	int ret;
	char* api_name = "sound_manager_multi_session_create";
	sound_multi_session_type_e type = SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION;
	sound_multi_session_h *session=NULL;
	ret = sound_manager_multi_session_create(type, session);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_multi_session_destroy_p(void)
{
	int ret;
	char* api_name = "sound_manager_multi_session_destroy";
	sound_multi_session_type_e type = SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION;
	sound_multi_session_h session;
	if( (ret = sound_manager_multi_session_create(type, &session)) == SOUND_MANAGER_ERROR_NONE)
	{
	    if( (ret = sound_manager_multi_session_destroy(session)) == SOUND_MANAGER_ERROR_NONE)
	    {
	       dts_pass(api_name);
	    }
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_multi_session_destroy_n(void)
{
	int ret;
	char* api_name = "sound_manager_multi_session_destroy";
	if( (ret = sound_manager_multi_session_destroy(NULL)) == SOUND_MANAGER_ERROR_NONE)
		dts_fail(api_name);
	else
		dts_pass(api_name);
}

static void utc_media_sound_manager_multi_session_get_mode_p(void)
{
	int ret;
	char* api_name = "sound_manager_multi_session_get_mode";
	sound_multi_session_type_e type = SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION;
	sound_multi_session_h session;
	sound_multi_session_mode_e mode;
	if( (ret = sound_manager_multi_session_create(type, &session)) == SOUND_MANAGER_ERROR_NONE)
	{
		if( (ret = sound_manager_multi_session_get_mode(session, &mode)) == SOUND_MANAGER_ERROR_NONE)
		{
			sound_manager_multi_session_destroy(session);
			dts_pass(api_name);
		}
		else
		{
			sound_manager_multi_session_destroy(session);
			dts_fail(api_name);
		}
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_multi_session_get_mode_n(void)
{
	int ret;
	char* api_name = "sound_manager_multi_session_get_mode";
	sound_multi_session_mode_e mode;
	if( (ret = sound_manager_multi_session_get_mode(NULL, &mode)) == SOUND_MANAGER_ERROR_NONE)
		dts_fail(api_name);
	else
		dts_pass(api_name);
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_multi_session_get_option_p(void)
{
	int ret;
	char* api_name = "sound_manager_multi_session_get_option";
	sound_multi_session_type_e type = SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION;
	sound_multi_session_h session;
	sound_multi_session_option_e option;
	if( (ret = sound_manager_multi_session_create(type, &session)) == SOUND_MANAGER_ERROR_NONE)
	{
		if( (ret = sound_manager_multi_session_get_option(session, &option)) == SOUND_MANAGER_ERROR_NONE)
		{
			sound_manager_multi_session_destroy(session);
			dts_pass(api_name);
		}
		else
		{
			sound_manager_multi_session_destroy(session);
			dts_fail(api_name);
		}
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_multi_session_get_option_n(void)
{
  	int ret;
	char* api_name = "sound_manager_multi_session_get_option";
	sound_multi_session_option_e option = SOUND_MULTI_SESSION_OPT_RESUME_OTHERS;
	if( (ret = sound_manager_multi_session_get_option(NULL, &option)) == SOUND_MANAGER_ERROR_NONE)
		dts_fail(api_name);
	else
		dts_pass(api_name);
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_multi_session_set_mode_p(void)
{
	int ret;
	char* api_name = "sound_manager_multi_session_set_mode";
	sound_multi_session_type_e type = SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION;
	sound_multi_session_h session;
	sound_multi_session_mode_e mode = SOUND_MULTI_SESSION_MODE_INIT;
	if( (ret = sound_manager_multi_session_create(type, &session)) == SOUND_MANAGER_ERROR_NONE)
	{
		if( (ret = sound_manager_multi_session_set_mode(session, mode)) == SOUND_MANAGER_ERROR_NONE)
		{
			sound_manager_multi_session_destroy(session);
			dts_pass(api_name);
		}
		else
		{
			sound_manager_multi_session_destroy(session);
			dts_fail(api_name);
		}
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_multi_session_set_mode_n(void)
{
    int ret;
	char* api_name = "sound_manager_multi_session_set_mode";
	sound_multi_session_mode_e mode = SOUND_MULTI_SESSION_MODE_INIT;
	if( (ret = sound_manager_multi_session_set_mode(NULL, mode)) == SOUND_MANAGER_ERROR_NONE)
		dts_fail(api_name);
	else
		dts_pass(api_name);
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_multi_session_set_option_p(void)
{
	int ret;
	char* api_name = "sound_manager_multi_session_set_option";
	sound_multi_session_type_e type = SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION;
	sound_multi_session_h session;
	sound_multi_session_option_e option = SOUND_MULTI_SESSION_OPT_RESUME_OTHERS;
	if( (ret = sound_manager_multi_session_create(type, &session)) == SOUND_MANAGER_ERROR_NONE)
	{
		if( (ret = sound_manager_multi_session_set_option(session, option)) == SOUND_MANAGER_ERROR_NONE)
		{
			sound_manager_multi_session_destroy(session);
			dts_pass(api_name);
		}
		else
		{
			sound_manager_multi_session_destroy(session);
			dts_fail(api_name);
		}
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_multi_session_set_option_n(void)
{
	int ret;
	char* api_name = "sound_manager_multi_session_set_option";
	sound_multi_session_option_e option = SOUND_MULTI_SESSION_OPT_RESUME_OTHERS;
	if( (ret = sound_manager_multi_session_set_option(NULL, option)) == SOUND_MANAGER_ERROR_NONE)
		dts_fail(api_name);
	else
		dts_pass(api_name);
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_set_balance_p(void)
{
	int ret ;
	char* api_name = "sound_manager_set_balance";
	float balance = 0.0;
	ret = sound_manager_set_balance(balance);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_balance_n(void)
{
	int ret ;
	char* api_name = "sound_manager_set_balance";
	float balance = -2.0;
	ret = sound_manager_set_balance(balance);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_muteall_p(void)
{
	int ret;
	char* api_name = "sound_manager_set_muteall";
	bool onoff=true;
	ret = sound_manager_set_muteall(onoff);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

/*
static void utc_media_sound_manager_set_muteall_n(void)
{
	int ret;
	bool onoff;
	char* api_name = "sound_manager_set_muteall";
	if( (ret = sound_manager_set_muteall(-1)) != SOUND_MANAGER_ERROR_NONE)
		dts_pass(api_name);

	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}
*/

static void utc_media_sound_manager_set_volume_key_type_p(void)
{
	int ret;
	volume_key_type_e type = VOLUME_KEY_TYPE_NONE;
	char* api_name = "sound_manager_set_volume_key_type";
	ret = sound_manager_set_volume_key_type(type);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_volume_key_type_n(void)
{
	int ret;
	volume_key_type_e type = VOLUME_KEY_TYPE_NONE;
	char* api_name = "sound_manager_set_volume_key_type";
	ret = sound_manager_set_volume_key_type(VOLUME_KEY_TYPE_NONE-1);
	dts_message(api_name, "Call log: %d", ret);
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

