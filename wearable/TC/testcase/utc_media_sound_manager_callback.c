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

static void utc_media_sound_manager_set_volume_changed_cb_p(void);
static void utc_media_sound_manager_set_volume_changed_cb_n(void);
static void utc_media_sound_manager_set_session_notify_cb_p(void);
static void utc_media_sound_manager_set_session_notify_cb_n(void);

static void utc_media_sound_manager_set_available_route_changed_cb_p(void);
static void utc_media_sound_manager_set_available_route_changed_cb_n(void);
static void utc_media_sound_manager_set_active_device_changed_cb_p(void);
static void utc_media_sound_manager_set_active_device_changed_cb_n(void);

static void utc_media_sound_manager_set_interrupted_cb_p(void);
static void utc_media_sound_manager_set_interrupted_cb_n(void);
static void utc_media_sound_manager_set_muteall_changed_cb_p(void);
static void utc_media_sound_manager_set_muteall_changed_cb_n(void);
static void utc_media_sound_manager_set_watch_cb_p(void);
static void utc_media_sound_manager_set_watch_cb_n(void);
/*
static void utc_media_sound_manager_unset_active_device_changed_cb_p(void);
static void utc_media_sound_manager_unset_active_device_changed_cb_n(void);
static void utc_media_sound_manager_unset_available_route_changed_cb_p(void);
static void utc_media_sound_manager_unset_available_route_changed_cb_n(void);
static void utc_media_sound_manager_unset_interrupted_cb_p(void);
static void utc_media_sound_manager_unset_interrupted_cb_n(void);
static void utc_media_sound_manager_unset_muteall_changed_cb_p(void);
static void utc_media_sound_manager_unset_muteall_changed_cb_n(void);
static void utc_media_sound_manager_unset_session_notify_cb_p(void);
static void utc_media_sound_manager_unset_session_notify_cb_n(void);
static void utc_media_sound_manager_unset_volume_changed_cb_p(void);
static void utc_media_sound_manager_unset_volume_changed_cb_n(void);
*/
static void utc_media_sound_manager_unset_watch_cb_p(void);
static void utc_media_sound_manager_unset_watch_cb_n(void);

struct tet_testlist tet_testlist[] = {
	{ utc_media_sound_manager_set_volume_changed_cb_p , POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_volume_changed_cb_n , NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_session_notify_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_session_notify_cb_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_available_route_changed_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_available_route_changed_cb_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_active_device_changed_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_active_device_changed_cb_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_interrupted_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_interrupted_cb_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_muteall_changed_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_muteall_changed_cb_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_set_watch_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_set_watch_cb_n, NEGATIVE_TC_IDX },
	/*
	{ utc_media_sound_manager_unset_active_device_changed_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_unset_active_device_changed_cb_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_unset_available_route_changed_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_unset_available_route_changed_cb_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_unset_interrupted_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_unset_interrupted_cb_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_unset_muteall_changed_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_unset_muteall_changed_cb_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_unset_session_notify_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_unset_session_notify_cb_n, NEGATIVE_TC_IDX },
	{ utc_media_sound_manager_unset_volume_changed_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_unset_volume_changed_cb_n, NEGATIVE_TC_IDX },
	*/
	{ utc_media_sound_manager_unset_watch_cb_p, POSITIVE_TC_IDX },
	{ utc_media_sound_manager_unset_watch_cb_n, NEGATIVE_TC_IDX },
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

static void _sound_volume_changed_cb(sound_type_e type, unsigned int volume, void *user_data)
{
}

static void _sound_available_route_changed_cb (sound_route_e route, bool available, void *user_data)
{
}

static void _sound_active_device_changed_cb (sound_device_in_e in, sound_device_out_e out, void *user_data)
{
}

static void _sound_interrupted_cb (sound_interrupted_code_e code , void *user_data)
{
}

static void _sound_manager_muteall_changed_cb (bool muteall, void *user_data)
{
}

static void _sound_manager_volume_changed_cb(sound_type_e type, unsigned int volume, void *user_data)
{
}

static void _sound_session_watch_cb(sound_session_watch_type_e type, sound_session_watch_state_e state, void *user_data)
{
}

static void utc_media_sound_manager_set_volume_changed_cb_p(void)
{
	char* api_name = "sound_manager_set_volume_changed_cb";
	int ret;
	if ((ret = sound_manager_set_volume_changed_cb(_sound_volume_changed_cb, &ret)) == SOUND_MANAGER_ERROR_NONE)
	{
		sound_manager_unset_volume_changed_cb();
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}

static void utc_media_sound_manager_set_volume_changed_cb_n(void)
{
	char* api_name = "sound_manager_set_volume_changed_cb";
	int ret;
	if ((ret = sound_manager_set_volume_changed_cb(NULL, &ret)) != SOUND_MANAGER_ERROR_NONE)
	{
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}


void _session_notify_cb(sound_session_notify_e notify, void *user_data)
{
}


static void utc_media_sound_manager_set_session_notify_cb_p(void)
{
	char* api_name = "sound_manager_set_session_notify_cb";
	int ret;
	if ((ret = sound_manager_set_session_notify_cb(_session_notify_cb, NULL)) == SOUND_MANAGER_ERROR_NONE)
	{
		sound_manager_unset_session_notify_cb();
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);

}

static void utc_media_sound_manager_set_session_notify_cb_n(void)
{
	char* api_name = "sound_manager_set_session_notify_cb";
	int ret;
	if ((ret = sound_manager_set_session_notify_cb(NULL, NULL)) != SOUND_MANAGER_ERROR_NONE)
	{
		sound_manager_unset_session_notify_cb();
		dts_pass(api_name);
	}
	dts_message(api_name, "Call log: %d", ret);
	dts_fail(api_name);
}
/*
static void utc_media_sound_manager_unset_session_notify_cb_p(void)
{
	char* api_name = "sound_manager_unset_session_notify_cb";
	int ret = sound_manager_set_session_notify_cb(_session_notify_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		if( (ret = sound_manager_unset_session_notify_cb ()) != SOUND_MANAGER_ERROR_NONE )
			dts_pass(api_name);
		else
			dts_fail(api_name);
	}
	else
		dts_fail(api_name);
	dts_fail(api_name);
}

static void utc_media_sound_manager_unset_session_notify_cb_n(void)
{
	char* api_name = "sound_manager_unset_session_notify_cb";
	if( (ret = sound_manager_unset_session_notify_cb ()) != SOUND_MANAGER_ERROR_NONE )
		dts_fail(api_name);
	else
		dts_pass(api_name);
	dts_pass(api_name);
}
*/

static void utc_media_sound_manager_set_available_route_changed_cb_p(void)
{
	char* api_name = "sound_manager_set_available_route_changed_cb";
	int ret = sound_manager_set_available_route_changed_cb(_sound_available_route_changed_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		sound_manager_unset_available_route_changed_cb ();
	}
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_available_route_changed_cb_n(void)
{
	char* api_name = "sound_manager_set_available_route_changed_cb";
	int ret = sound_manager_set_available_route_changed_cb(NULL, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		sound_manager_unset_available_route_changed_cb ();
	}
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

/*
static void utc_media_sound_manager_unset_available_route_changed_cb_p(void)
{
	char* api_name = "sound_manager_unset_available_route_changed_cb";
        int ret = sound_manager_set_available_route_changed_cb(_sound_available_route_changed_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		if( (ret = sound_manager_unset_available_route_changed_cb ()) != SOUND_MANAGER_ERROR_NONE )
		    dts_pass(api_name);
		else
		    dts_fail(api_name);
	}
	else
	    dts_fail(api_name);
}

static void utc_media_sound_manager_unset_available_route_changed_cb_n(void)
{
	char* api_name = "sound_manager_unset_available_route_changed_cb";
  	if( (ret = sound_manager_unset_available_route_changed_cb ()) != SOUND_MANAGER_ERROR_NONE )
	    dts_fail(api_name);
	else
	    dts_pass(api_name);
}
*/

static void utc_media_sound_manager_set_active_device_changed_cb_p(void)
{
	char* api_name = "sound_manager_set_active_device_changed_cb";
	int ret = sound_manager_set_active_device_changed_cb(_sound_active_device_changed_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		sound_manager_unset_active_device_changed_cb ();
	}
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_active_device_changed_cb_n(void)
{
	char* api_name = "sound_manager_set_active_device_changed_cb";
	int ret = sound_manager_set_active_device_changed_cb(NULL, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		sound_manager_unset_active_device_changed_cb ();
	}
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

/*
static void utc_media_sound_manager_unset_active_device_changed_cb_p(void)
{
	char* api_name = "sound_manager_unset_active_device_changed_cb";
        int ret = sound_manager_set_active_device_changed_cb(_sound_active_device_changed_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		if( (ret = sound_manager_unset_active_device_changed_cb ()) != SOUND_MANAGER_ERROR_NONE )
		    dts_pass(api_name);
		else
		    dts_fail(api_name);
	}
	else
	    dts_fail(api_name);
}

static void utc_media_sound_manager_unset_active_device_changed_cb_n(void)
{
	char* api_name = "sound_manager_unset_active_device_changed_cb";
	if( (ret = sound_manager_unset_active_device_changed_cb ()) != SOUND_MANAGER_ERROR_NONE )
	    dts_fail(api_name);
	else
	    dts_pass(api_name);
}
*/

static void utc_media_sound_manager_set_interrupted_cb_p(void)
{
	char* api_name = "sound_manager_set_interrupted_cb";
	int ret = sound_manager_set_interrupted_cb(_sound_interrupted_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		sound_manager_unset_interrupted_cb ();
	}
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_interrupted_cb_n(void)
{
	char* api_name = "sound_manager_set_interrupted_cb";
	int ret = sound_manager_set_interrupted_cb(NULL, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		sound_manager_unset_interrupted_cb ();
	}
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

/*
static void utc_media_sound_manager_unset_interrupted_cb_p(void)
{
	char* api_name = "sound_manager_unset_interrupted_cb";
	int ret = sound_manager_set_interrupted_cb(_sound_interrupted_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		if( (ret = sound_manager_unset_interrupted_cb ()) != SOUND_MANAGER_ERROR_NONE )
		    dts_pass(api_name);
		else
		    dts_fail(api_name);
	}
	else
	    dts_fail(api_name);
}

static void utc_media_sound_manager_unset_interrupted_cb_n(void)
{
	char* api_name = "sound_manager_unset_interrupted_cb";
	if( (ret = sound_manager_unset_interrupted_cb ()) != SOUND_MANAGER_ERROR_NONE )
	    dts_fail(api_name);
	else
	    dts_pass(api_name);
}
*/

static void utc_media_sound_manager_set_muteall_changed_cb_p(void)
{
	char* api_name = "sound_manager_set_muteall_changed_cb";
	int ret = sound_manager_set_muteall_changed_cb(_sound_manager_muteall_changed_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		sound_manager_unset_muteall_changed_cb ();
	}
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_muteall_changed_cb_n(void)
{
	char* api_name = "sound_manager_set_muteall_changed_cb";
	int ret = sound_manager_set_muteall_changed_cb(NULL, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		sound_manager_unset_muteall_changed_cb ();
	}
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

/*
static void utc_media_sound_manager_unset_muteall_changed_cb_p(void)
{
	char* api_name = "sound_manager_unset_muteall_changed_cb";
        int ret = sound_manager_set_muteall_changed_cb(_sound_manager_muteall_changed_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		if( (ret = sound_manager_unset_muteall_changed_cb ()) != SOUND_MANAGER_ERROR_NONE )
		    dts_pass(api_name);
		else
		    dts_fail(api_name);
	}
	else
	    dts_fail(api_name);
}

static void utc_media_sound_manager_unset_muteall_changed_cb_n(void)
{
	char* api_name = "sound_manager_unset_muteall_changed_cb";
    	if( (ret = sound_manager_unset_muteall_changed_cb ()) != SOUND_MANAGER_ERROR_NONE )
	    dts_fail(api_name);
	else
	    dts_pass(api_name);
}

static void utc_media_sound_manager_unset_volume_changed_cb_p(void)
{
	char* api_name = "sound_manager_unset_volume_changed_cb";
        int ret = sound_manager_set_volume_changed_cb(_sound_manager_volume_changed_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		if( (ret = sound_manager_unset_volume_changed_cb ()) != SOUND_MANAGER_ERROR_NONE )
		    dts_pass(api_name);
		else
		    dts_fail(api_name);
	}
	else
	    dts_fail(api_name);
}

static void utc_media_sound_manager_unset_volume_changed_cb_n(void)
{
	char* api_name = "sound_manager_unset_volume_changed_cb";
    	if( (ret = sound_manager_unset_volume_changed_cb ()) != SOUND_MANAGER_ERROR_NONE )
	    dts_fail(api_name);
	else
	    dts_pass(api_name);
}
*/

static void utc_media_sound_manager_set_watch_cb_p(void)
{
	char* api_name = "sound_manager_set_watch_cb";
	sound_session_watch_type_e type = SOUND_SESSION_WATCH_TYPE_CALL;
	int ret = sound_manager_set_watch_cb(type, _sound_session_watch_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		sound_manager_unset_watch_cb (type);
	}
	dts_check_eq(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_set_watch_cb_n(void)
{
	char* api_name = "sound_manager_set_watch_cb";
	sound_session_watch_type_e type = SOUND_SESSION_WATCH_TYPE_CALL;
	int ret = sound_manager_set_watch_cb(type, NULL, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		sound_manager_unset_watch_cb (type);
	}
	dts_check_ne(api_name, ret, SOUND_MANAGER_ERROR_NONE);
}

static void utc_media_sound_manager_unset_watch_cb_p(void)
{
	char* api_name = "sound_manager_unset_watch_cb";
	sound_session_watch_type_e type = SOUND_SESSION_WATCH_TYPE_CALL;
	int ret = sound_manager_set_watch_cb(type, _sound_session_watch_cb, NULL);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		if( (ret = sound_manager_unset_watch_cb(type)) == SOUND_MANAGER_ERROR_NONE )
			dts_pass(api_name);
		else
		    dts_fail(api_name);
	}
	else
	    dts_fail(api_name);
}

static void utc_media_sound_manager_unset_watch_cb_n(void)
{
	int ret;
	char* api_name = "sound_manager_unset_watch_cb";
	sound_session_watch_type_e type = SOUND_SESSION_WATCH_TYPE_CALL;
	if( (ret = sound_manager_unset_watch_cb(type)) != SOUND_MANAGER_ERROR_NONE )
		dts_pass(api_name);
	else
		dts_fail(api_name);
}
