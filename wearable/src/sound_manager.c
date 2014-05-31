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


#define LOG_TAG "TIZEN_N_SOUND_MANAGER"

#include <sound_manager.h>
#include <sound_manager_private.h>

#include <mm_sound.h>
#include <mm_sound_private.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <dlog.h>
#include <mm_session.h>
#include <mm_session_private.h>

#define MAX_VOLUME_TYPE 7

typedef struct {
	void *user_data;
	sound_manager_volume_changed_cb user_cb;
}_changed_volume_info_s;

typedef struct {
	void *user_data;
	sound_manager_muteall_changed_cb user_cb;
}_changed_muteall_info_s;


typedef struct {
	int is_registered;
	void *user_data;
	sound_session_notify_cb user_cb;
	void *interrupted_user_data;
	sound_interrupted_cb interrupted_cb;
}_session_notify_info_s;

typedef struct {
	void *user_data[SOUND_SESSION_WATCH_TYPE_NUM];
	sound_session_watch_cb user_cb[SOUND_SESSION_WATCH_TYPE_NUM];
}_session_watch_info_s;

typedef struct {
	void *user_data;
	sound_available_route_changed_cb user_cb;
}_changed_available_route_info_s;

typedef struct {
	void *user_data;
	sound_active_device_changed_cb user_cb;
}_changed_active_device_info_s;

static _changed_muteall_info_s g_muteall_changed_cb_table;
static _session_notify_info_s g_session_notify_cb_table = {0, NULL, NULL, NULL, NULL};
static _session_watch_info_s g_session_watch_cb_table;
static sound_session_type_e g_cached_session = -1;

#define SOUND_SESSION_TYPE_DEFAULT SOUND_SESSION_TYPE_SHARE
#define SOUND_MULT_SESSION_TYPE_DEFAULT SOUND_SESSION_TYPE_SHARE

static void __muteall_changed_cb(void *user_data)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	bool new_muteall = false;
	ret = sound_manager_get_muteall(&new_muteall);
	if (ret == SOUND_MANAGER_ERROR_NONE) {
		if(g_muteall_changed_cb_table.user_cb)
			(g_muteall_changed_cb_table.user_cb)(new_muteall, g_muteall_changed_cb_table.user_data);
	} else {
		LOGE("sound_manager_get_muteall() error code(0x%08x)", ret);
	}
}

static void __session_notify_cb(session_msg_t msg, session_event_t event, void *user_data){
	if(g_session_notify_cb_table.user_cb){
		g_session_notify_cb_table.user_cb(msg, g_session_notify_cb_table.user_data);
	}
	if( g_session_notify_cb_table.interrupted_cb ){
		sound_interrupted_code_e e = SOUND_INTERRUPTED_COMPLETED;
		if( msg == MM_SESSION_MSG_RESUME )
			e = SOUND_INTERRUPTED_COMPLETED;
		else{
			switch(event){
				case MM_SESSION_EVENT_MEDIA :
					e = SOUND_INTERRUPTED_BY_MEDIA;
					break;
				case MM_SESSION_EVENT_RESUMABLE_MEDIA :
					e = SOUND_INTERRUPTED_BY_RESUMABLE_MEDIA;
					break;
				case MM_SESSION_EVENT_CALL :
					e = SOUND_INTERRUPTED_BY_CALL;
					break;
				case MM_SESSION_EVENT_ALARM :
					e = SOUND_INTERRUPTED_BY_ALARM;
					break;
				case MM_SESSION_EVENT_EARJACK_UNPLUG:
					e = SOUND_INTERRUPTED_BY_EARJACK_UNPLUG;
					break;
				case MM_SESSION_EVENT_RESOURCE_CONFLICT:
					e = SOUND_INTERRUPTED_BY_RESOURCE_CONFLICT;
					break;
				case MM_SESSION_EVENT_EMERGENCY:
					e = SOUND_INTERRUPTED_BY_EMERGENCY;
					break;
				case MM_SESSION_EVENT_NOTIFICATION :
					e = SOUND_INTERRUPTED_BY_NOTIFICATION;
					break;
				default :
					e = SOUND_INTERRUPTED_BY_MEDIA;
					break;
			}
		}
		g_session_notify_cb_table.interrupted_cb(e, g_session_notify_cb_table.interrupted_user_data);
	}
}

static void __session_watch_cb(session_watch_event_t event, session_watch_state_t state, void *user_param){
	int index = 0;

	index = (int)event;
	if (index < 0) {
		LOGE("[%s] invalid event type(%d)", (int)event);
		return;
	}

	if( g_session_watch_cb_table.user_cb[index] ) {
		sound_session_watch_type_e watch_type;
		sound_session_watch_state_e watch_state;
		switch(event) {
			case MM_SESSION_WATCH_EVENT_CALL :
				watch_type = SOUND_SESSION_WATCH_TYPE_CALL;
				break;
			case MM_SESSION_WATCH_EVENT_VIDEO_CALL :
				watch_type = SOUND_SESSION_WATCH_TYPE_VIDEO_CALL;
				break;
			case MM_SESSION_WATCH_EVENT_ALARM :
				watch_type = SOUND_SESSION_WATCH_TYPE_ALARM;
				break;
			case MM_SESSION_WATCH_EVENT_MMCAMCORDER_EXCLUSIVE :
				watch_type = SOUND_SESSION_WATCH_TYPE_AV_RECORD;
				break;
			default :
				LOGE("[%s] invalid watch_event(%d)",__func__, event);
				return;
		}
		switch(state) {
			case MM_SESSION_WATCH_STATE_STOP :
				watch_state = SOUND_SESSION_WATCH_STATE_STOP;
				break;
			case MM_SESSION_WATCH_STATE_PLAYING :
				watch_state = SOUND_SESSION_WATCH_STATE_START;
				break;
			default :
				LOGE("[%s] invalid watch_state(%d)",__func__, state);
				return;
		}
		g_session_watch_cb_table.user_cb[index](watch_type, watch_state, g_session_watch_cb_table.user_data[index]);
	}
}

int sound_manager_get_max_volume(sound_type_e type, int *max)
{
	int volume;
	if(max == NULL)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	if(type > MAX_VOLUME_TYPE || type < 0)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	int ret = mm_sound_volume_get_step(type, &volume);

	if(ret == 0)
		*max = volume -1;	// actual volume step can be max step - 1

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_set_volume(sound_type_e type, int volume)
{
	if(type > MAX_VOLUME_TYPE || type < 0)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	if(volume < 0)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	int ret = mm_sound_volume_set_value(type, volume);
	LOGI("returns : type=%d, volume=%d, ret=0x%x", type, volume, ret);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_get_volume(sound_type_e type, int *volume)
{
	unsigned int uvolume;
	if(type > MAX_VOLUME_TYPE || type < 0)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	if(volume == NULL)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	int ret = mm_sound_volume_get_value(type, &uvolume);

	if(ret == 0)
		*volume = uvolume;

#if 0 /* FIXME: To many logs for enabing this... */
	LOGI("returns : type=%d, volume=%d, ret=0x%x", type, *volume, ret);
#endif

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_get_current_sound_type(sound_type_e *type)
{
	if(type == NULL)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	int ret;
	ret = mm_sound_volume_get_current_playing_type((volume_type_t *)type);

	LOGI("returns : type=%d, ret=0x%x", *type, ret);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_set_balance(float balance)
{
	if(balance < -1.0 || balance > 1.0)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	int ret = mm_sound_volume_set_balance(balance);

	LOGI("returns : balance=%f, ret=0x%x", balance, ret);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_get_balance(float *balance)
{
	float ubalance;
	if(balance == NULL)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	int ret = mm_sound_volume_get_balance(&ubalance);

	if (ret == 0)
		*balance = ubalance;

	LOGI("returns : balance=%f, ret=0x%x", *balance, ret);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_set_muteall(bool onoff)
{
	int muteall;
	if(true == onoff)
		muteall = 1;
	else
		muteall = 0;

	int ret = mm_sound_set_muteall(muteall);
	LOGI("returns : onoff=%d, ret=0x%x", onoff, ret);

	return __convert_sound_manager_error_code(__func__, ret);
}


int sound_manager_set_call_mute(sound_type_e type, int mute)
{
	int ret;

	ret  = mm_sound_set_call_mute(type, mute);
	LOGI("returns : type=%d, mute=%d, ret=0x%x", type, mute, ret);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_get_call_mute(sound_type_e type, int *mute)
{
	int ret;

	ret  = mm_sound_get_call_mute(type, mute);
	LOGI("returns : type=%d, mute=%d, ret=0x%x", type, *mute, ret);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_get_muteall(bool *onoff)
{
	int umuteall;
	if(onoff == NULL)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	int ret = mm_sound_get_muteall(&umuteall);

	if (ret == 0){
		if(0 == umuteall)
			*onoff = false;
		else
			*onoff = true;
	}
	LOGI("returns : onoff=%d, ret=0x%x", *onoff, ret);
	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_set_muteall_changed_cb(sound_manager_muteall_changed_cb callback, void* user_data)
{
	if(callback == NULL)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	g_muteall_changed_cb_table.user_cb = callback;
	g_muteall_changed_cb_table.user_data = user_data;
	mm_sound_muteall_add_callback(__muteall_changed_cb);
	return 0;
}

void sound_manager_unset_muteall_changed_cb(void)
{
	mm_sound_muteall_remove_callback(__muteall_changed_cb);
	g_muteall_changed_cb_table.user_cb = NULL;
	g_muteall_changed_cb_table.user_data = NULL;
}

int sound_manager_set_volume_changed_cb(sound_manager_volume_changed_cb callback, void* user_data)
{
	int ret;
	ret = mm_sound_add_volume_changed_callback((mm_sound_volume_changed_cb)callback, user_data);

	return __convert_sound_manager_error_code(__func__, ret);
}

void sound_manager_unset_volume_changed_cb(void)
{
	mm_sound_remove_volume_changed_callback();
}

int sound_manager_get_a2dp_status(bool *connected , char** bt_name){
	int ret = mm_sound_route_get_a2dp_status(connected , bt_name);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_set_session_type(sound_session_type_e type){
	int ret = 0;
	int session = 0;

	LOGI(">> enter : type=%d", type);

	if(type < 0 || type >  SOUND_SESSION_TYPE_NOTIFICATION)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	/* if call session is activated, can't set session */
	ret = mm_session_get_current_type(&session);
	if( ret == 0 && session >= MM_SESSION_TYPE_CALL ) {
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_OPERATION);
	}

	if(g_session_notify_cb_table.is_registered){
		ret = mm_session_finish();
		if (ret != MM_ERROR_NONE) {
			return __convert_sound_manager_error_code(__func__, ret);
		}
		g_session_notify_cb_table.is_registered = 0;
	}

	ret = mm_session_init_ex(type , __session_notify_cb, NULL);
	if(ret == 0){
		g_session_notify_cb_table.is_registered = 1;
	}
	LOGI("<< leave : type=%d, ret=0x%x", type, ret);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_get_session_type(sound_session_type_e *type){
	if( type == NULL )
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	int ret = 0;
	int session;
	ret = mm_session_get_current_type(&session);
	if( ret !=0 )
		session = SOUND_SESSION_TYPE_DEFAULT;
	if( session > SOUND_SESSION_TYPE_NOTIFICATION ){ // call session or voip session or voice recognition
		if( g_cached_session != -1 )
			session = g_cached_session;	 // saved session
		else //will be never reach here. just prevent code
			session = SOUND_SESSION_TYPE_DEFAULT;
	}

	*type = session;

	LOGI("returns : type=%d, ret=0x%x", *type, ret);

	return 0;
}

int sound_manager_set_session_notify_cb(sound_session_notify_cb callback , void *user_data){
	int ret =0 ;
	if(callback == NULL)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);


	if(g_session_notify_cb_table.is_registered ==0){
		ret = mm_session_init_ex(SOUND_SESSION_TYPE_DEFAULT /*default*/ , __session_notify_cb, NULL);
		if(ret != 0)
			return __convert_sound_manager_error_code(__func__, ret);
		g_session_notify_cb_table.is_registered = 1;
	}

	g_session_notify_cb_table.user_cb = callback;
	g_session_notify_cb_table.user_data  = user_data;
	return SOUND_MANAGER_ERROR_NONE;
}

void sound_manager_unset_session_notify_cb(void){
	g_session_notify_cb_table.user_cb = NULL;
	g_session_notify_cb_table.user_data  = NULL;
}

int sound_manager_set_interrupted_cb(sound_interrupted_cb callback, void *user_data){
	int ret =0 ;
	if(callback == NULL)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	if(g_session_notify_cb_table.is_registered ==0){
		ret = mm_session_init_ex(SOUND_SESSION_TYPE_DEFAULT /*default*/ , __session_notify_cb, NULL);
		if(ret != 0)
			return __convert_sound_manager_error_code(__func__, ret);
		g_session_notify_cb_table.is_registered = 1;
	}

	g_session_notify_cb_table.interrupted_cb= callback;
	g_session_notify_cb_table.interrupted_user_data = user_data;
	return SOUND_MANAGER_ERROR_NONE;
}

void sound_manager_unset_interrupted_cb(void){
	g_session_notify_cb_table.interrupted_cb= NULL;
	g_session_notify_cb_table.interrupted_user_data = NULL;
}

int sound_manager_set_watch_cb(sound_session_watch_type_e type, sound_session_watch_cb callback, void *user_data) {
	int ret = 0 ;
	int i = 0;

	if(callback == NULL) {
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	}

	if((int)type < 0 || (int)type >=  SOUND_SESSION_WATCH_TYPE_NUM) {
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	}

	if (g_session_watch_cb_table.user_cb[(int)type]) {
		/* just refresh callback pointer */
		g_session_watch_cb_table.user_cb[(int)type] = callback;
		g_session_watch_cb_table.user_data[(int)type] = user_data;
		LOGI("[%s] refresh watch callback(0x%x), user_data(0x%x)",__func__, callback, user_data);
		return SOUND_MANAGER_ERROR_NONE;
	}

	for (i = SOUND_SESSION_WATCH_STATE_STOP; i < SOUND_SESSION_WATCH_STATE_NUM; i++) {
		ret = mm_session_add_watch_callback(type, i, __session_watch_cb, NULL);
		if(ret != 0) {
			return __convert_sound_manager_error_code(__func__, ret);
		}
	}

	g_session_watch_cb_table.user_cb[(int)type] = callback;
	g_session_watch_cb_table.user_data[(int)type] = user_data;
	LOGI("[%s] register watch callback(0x%x), user_data(0x%x)",__func__, callback, user_data);

	return SOUND_MANAGER_ERROR_NONE;
}

int sound_manager_unset_watch_cb(sound_session_watch_type_e type) {
	int ret = 0;
	int i = 0;

	if((int)type < 0 || (int)type >=  SOUND_SESSION_WATCH_TYPE_NUM) {
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	}

	if (!g_session_watch_cb_table.user_cb[(int)type]) {
		LOGE("[%s] could not find the registered watch callback of the type(%d)",__func__, type);
		return SOUND_MANAGER_ERROR_INVALID_OPERATION;
	}

	for (i = SOUND_SESSION_WATCH_STATE_STOP; i < SOUND_SESSION_WATCH_STATE_NUM; i++) {
		ret = mm_session_remove_watch_callback(type, i);
		if(ret != 0) {
			return __convert_sound_manager_error_code(__func__, ret);
		}
	}

	LOGI("[%s] remove watch callback(0x%x), user_data(0x%x)",__func__, g_session_watch_cb_table.user_cb[(int)type], g_session_watch_cb_table.user_data[(int)type]);
	g_session_watch_cb_table.user_cb[(int)type] = NULL;
	g_session_watch_cb_table.user_data[(int)type] = NULL;

	return SOUND_MANAGER_ERROR_NONE;
}

int sound_manager_set_volume_key_type(volume_key_type_e type){
	if(type < VOLUME_KEY_TYPE_NONE || type > VOLUME_KEY_TYPE_SVOICE)
		return __convert_sound_manager_error_code(__func__, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	int ret;
	if(type == VOLUME_KEY_TYPE_NONE)
		ret = mm_sound_volume_primary_type_clear();
	else
		ret = mm_sound_volume_primary_type_set(type);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_foreach_available_route (sound_available_route_cb callback, void *user_data)
{
	int ret;
	ret = mm_sound_foreach_available_route_cb((mm_sound_available_route_cb)callback, user_data);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_set_active_route (sound_route_e route)
{
	int ret;
	ret = mm_sound_set_active_route(route);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_set_active_route_auto (void)
{
	int ret;
	ret = mm_sound_set_active_route_auto();

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_get_active_device (sound_device_in_e *in, sound_device_out_e *out)
{
	int ret;
	ret = mm_sound_get_active_device((mm_sound_device_in *)in, (mm_sound_device_out *)out);

	return __convert_sound_manager_error_code(__func__, ret);
}

bool sound_manager_is_route_available (sound_route_e route)
{
	bool is_available;
	mm_sound_is_route_available(route, &is_available);

	return is_available;
}

int sound_manager_set_available_route_changed_cb (sound_available_route_changed_cb callback, void *user_data)
{
	int ret;
	ret = mm_sound_add_available_route_changed_callback((mm_sound_available_route_changed_cb)callback, user_data);

	return __convert_sound_manager_error_code(__func__, ret);
}

void sound_manager_unset_available_route_changed_cb (void)
{
	mm_sound_remove_available_route_changed_callback();
}

int sound_manager_set_active_device_changed_cb (sound_active_device_changed_cb callback, void *user_data)
{
	int ret;
	ret = mm_sound_add_active_device_changed_callback("capi-client", (mm_sound_active_device_changed_cb)callback, user_data);

	return __convert_sound_manager_error_code(__func__, ret);
}

void sound_manager_unset_active_device_changed_cb (void)
{
	mm_sound_remove_active_device_changed_callback("capi-client");
}

int sound_manager_call_session_create(sound_call_session_type_e type, sound_call_session_h *session)
{
	int ret = SOUND_MANAGER_ERROR_NONE;
	sound_call_session_h handle = NULL;

	LOGI(">> enter : type=%d, session=%p", type, session);

	/* Check input parameters */
	if(type < SOUND_SESSION_TYPE_CALL || type > SOUND_SESSION_TYPE_VIDEOCALL || session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	/* Allocate handle */
	handle = malloc(sizeof(struct sound_call_session_s));
	if(!handle) {
		ret = SOUND_MANAGER_ERROR_OUT_OF_MEMORY;
		goto ERROR;
	}
	memset(handle, 0, sizeof(struct sound_call_session_s));

	/* Finish previous session if exists */
	if(g_session_notify_cb_table.is_registered){
		sound_manager_get_session_type((sound_session_type_e*)&handle->previous_session);
		g_cached_session = handle->previous_session;

		ret = mm_session_finish();
		if (ret != MM_ERROR_NONE) {
			goto ERROR;
		}
		g_session_notify_cb_table.is_registered = 0;

	}else{
		g_cached_session = SOUND_SESSION_TYPE_DEFAULT;
		handle->previous_session = SOUND_SESSION_TYPE_DEFAULT;
	}

	/* Initialize session */
	switch(type) {
	case SOUND_SESSION_TYPE_CALL:
		ret = mm_session_init_ex(MM_SESSION_TYPE_CALL, __session_notify_cb, NULL);
		break;
	case SOUND_SESSION_TYPE_VOIP:
		ret = mm_session_init_ex(MM_SESSION_TYPE_VOIP,__session_notify_cb, NULL);
		break;
	case SOUND_SESSION_TYPE_VIDEOCALL:
		ret = mm_session_init_ex(MM_SESSION_TYPE_VIDEOCALL,__session_notify_cb, NULL);
		break;
	}
	if(ret != MM_ERROR_NONE)
		goto ERROR;

	g_session_notify_cb_table.is_registered = 1;
	*session = handle;

	LOGI("<< leave : type=%d, session=%p, ret=0x%x", type, session, ret);

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	if(handle)
		free(handle);

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_call_session_set_mode(sound_call_session_h session, sound_call_session_mode_e mode)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	LOGI(">> enter : session=%p, mode=%d", session, mode);

	if(mode < SOUND_CALL_SESSION_MODE_VOICE || mode > SOUND_CALL_SESSION_MODE_VOICE_ANSWER_REC || session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	ret = mm_session_set_subsession ((mm_subsession_t)mode, MM_SUBSESSION_OPTION_NONE);

	if(ret != MM_ERROR_NONE)
		goto ERROR;

	LOGI("<< leave : session=%p, mode=%d, ret=0x%x", session, mode, ret);

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	return __convert_sound_manager_error_code(__func__, ret);
}

int  sound_manager_call_session_get_mode(sound_call_session_h session, sound_call_session_mode_e *mode)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	if(mode == NULL || session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	ret = mm_session_get_subsession ((mm_subsession_t *)mode);

	if(ret != MM_ERROR_NONE)
		goto ERROR;

	LOGI("returns : session=%p, mode=%d, ret=0x%x", session, *mode, ret);

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_call_session_destroy(sound_call_session_h session)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	LOGI(">> enter : session=%p", session);

	if(session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	if(g_session_notify_cb_table.is_registered){
		ret = mm_session_finish();
		if(ret != MM_ERROR_NONE)
			goto ERROR;
		g_session_notify_cb_table.is_registered = 0;
	}

	/* Restore previous session */
	ret = mm_session_init_ex(session->previous_session , __session_notify_cb, NULL);
	if(ret == 0){
		g_session_notify_cb_table.is_registered = 1;
	}

	if(session) {
		free(session);
		session = NULL;
	}

	LOGI("<< leave : session=%p, ret=0x%x", session, ret);

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_multi_session_create(sound_multi_session_type_e type, sound_multi_session_h *session)
{
	int ret = SOUND_MANAGER_ERROR_NONE;
	sound_multi_session_h handle = NULL;

	LOGI(">> enter : type=%d, session=%p", type, session);

	/* Check input parameters */
	if(type < SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION || type > SOUND_MULTI_SESSION_TYPE_RECORD_VIDEO || session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	/* Allocate handle */
	handle = malloc(sizeof(struct sound_multi_session_s));
	if(!handle) {
		ret = SOUND_MANAGER_ERROR_OUT_OF_MEMORY;
		goto ERROR;
	}
	memset(handle, 0, sizeof(struct sound_multi_session_s));

	/* Finish previous session if exists */
	if(g_session_notify_cb_table.is_registered){
		sound_manager_get_session_type((sound_session_type_e*)&handle->previous_session);
		g_cached_session = handle->previous_session;

		ret = mm_session_finish();
		if (ret != MM_ERROR_NONE) {
			goto ERROR;
		}
		g_session_notify_cb_table.is_registered = 0;

	}else{
		g_cached_session = SOUND_MULT_SESSION_TYPE_DEFAULT;
		handle->previous_session = SOUND_MULT_SESSION_TYPE_DEFAULT;
	}

	/* Initialize session */
	switch(type) {
	case SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION:
		ret = mm_session_init_ex(MM_SESSION_TYPE_VOICE_RECOGNITION, __session_notify_cb, NULL);
		break;
	case SOUND_MULTI_SESSION_TYPE_RECORD_AUDIO:
		ret = mm_session_init_ex(MM_SESSION_TYPE_RECORD_AUDIO, __session_notify_cb, NULL);
		break;
	case SOUND_MULTI_SESSION_TYPE_RECORD_VIDEO:
		ret = mm_session_init_ex(MM_SESSION_TYPE_RECORD_VIDEO, __session_notify_cb, NULL);
		break;
	}
	if(ret != MM_ERROR_NONE)
		goto ERROR;

	g_session_notify_cb_table.is_registered = 1;

	handle->type = type;
	*session = handle;

	LOGI("<< leave : type=%d, session=%p", type, session);

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	if(handle) {
		free(handle);
	}

	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_multi_session_mode_is_available(sound_multi_session_h session, sound_multi_session_mode_e mode, bool *available)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	if(available == NULL || session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	switch(mode) {
	case SOUND_MULTI_SESSION_MODE_INIT:
		*available = true;
		break;
	case SOUND_MULTI_SESSION_MODE_VR_NORMAL:
	case SOUND_MULTI_SESSION_MODE_VR_DRIVE:
		if (session->type == SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION) {
			*available = true;
		} else {
			*available = false;
		}
		break;
	case SOUND_MULTI_SESSION_MODE_RECORD_STEREO:
		if (session->type == SOUND_MULTI_SESSION_TYPE_RECORD_AUDIO ||
			session->type == SOUND_MULTI_SESSION_TYPE_RECORD_VIDEO) {
			*available = true;
		} else {
			*available = false;
		}
		break;
	case SOUND_MULTI_SESSION_MODE_RECORD_STEREO_FOR_INTERVIEW:
	case SOUND_MULTI_SESSION_MODE_RECORD_STEREO_FOR_CONVERSATION:
		if (session->type == SOUND_MULTI_SESSION_TYPE_RECORD_AUDIO) {
				*available = true;
		} else {
				*available = false;
		}
		break;
	default:
		break;
	}

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_multi_session_set_mode(sound_multi_session_h session, sound_multi_session_mode_e mode)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	LOGI(">> enter : session=%p, mode=%d", session, mode);

	if(session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	switch(mode) {
	case SOUND_MULTI_SESSION_MODE_INIT:
		ret = mm_session_set_subsession((mm_subsession_t)mode, (mm_subsession_option_t)session->type_option);
		if(ret != MM_ERROR_NONE) {
			goto ERROR;
		}
		break;
	case SOUND_MULTI_SESSION_MODE_VR_NORMAL:
	case SOUND_MULTI_SESSION_MODE_VR_DRIVE:
		if (session->type == SOUND_MULTI_SESSION_TYPE_VOICE_RECOGNITION) {
			ret = mm_session_set_subsession((mm_subsession_t)mode, (mm_subsession_option_t)session->type_option);
			if(ret != MM_ERROR_NONE) {
				goto ERROR;
			}
		} else {
			ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
			goto ERROR;
		}
		break;
	case SOUND_MULTI_SESSION_MODE_RECORD_MONO:
	case SOUND_MULTI_SESSION_MODE_RECORD_STEREO:
		if (session->type == SOUND_MULTI_SESSION_TYPE_RECORD_AUDIO ||
			session->type == SOUND_MULTI_SESSION_TYPE_RECORD_VIDEO) {
			ret = mm_session_set_subsession((mm_subsession_t)mode, (mm_subsession_option_t)session->type_option);
			if(ret != MM_ERROR_NONE) {
				goto ERROR;
			}
		} else {
			ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
			goto ERROR;
		}
		break;
	case SOUND_MULTI_SESSION_MODE_RECORD_STEREO_FOR_INTERVIEW:
	case SOUND_MULTI_SESSION_MODE_RECORD_STEREO_FOR_CONVERSATION:
		if (session->type == SOUND_MULTI_SESSION_TYPE_RECORD_AUDIO) {
			ret = mm_session_set_subsession((mm_subsession_t)mode, (mm_subsession_option_t)session->type_option);
			if(ret != MM_ERROR_NONE) {
				goto ERROR;
			}
		} else {
			ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
			goto ERROR;
		}
		break;
	default:
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	LOGI("<< leave : session=%p, mode=%d", session, mode);

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_multi_session_get_mode(sound_multi_session_h session, sound_multi_session_mode_e *mode)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	if(mode == NULL || session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	ret = mm_session_get_subsession((mm_subsession_t *)mode);

	if(ret != MM_ERROR_NONE) {
		goto ERROR;
	}
	LOGI("return : session=%p, mode=%d", session, *mode);

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_multi_session_set_option(sound_multi_session_h session, sound_multi_session_option_e type)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	LOGI("return : session=%p, type=%d", session, type);

	if(type < SOUND_MULTI_SESSION_OPT_RESUME_OTHERS || type > SOUND_MULTI_SESSION_OPT_RESET_OTHERS_RESUME_INFO || session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}
	if (type == SOUND_MULTI_SESSION_OPT_RESET_OTHERS_RESUME_INFO) {
		ret = mm_session_reset_resumption_info();
	} else {
		ret = mm_session_set_subevent((mm_session_sub_t)type);
	}
	if(ret != MM_ERROR_NONE) {
		goto ERROR;
	}

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_multi_session_get_option(sound_multi_session_h session, sound_multi_session_option_e *option)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	if(option == NULL || session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	ret = mm_session_get_subevent((mm_session_sub_t *)option);

	if(ret != MM_ERROR_NONE) {
		goto ERROR;
	}

	LOGI("return : session=%p, type=%d", session, *option);

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	return __convert_sound_manager_error_code(__func__, ret);
}

int sound_manager_multi_session_destroy(sound_multi_session_h session)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	LOGI(">> enter : session=%p", session);

	if(session == NULL) {
		ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
		goto ERROR;
	}

	if(g_session_notify_cb_table.is_registered){
		ret = mm_session_finish();
		if(ret != MM_ERROR_NONE) {
			goto ERROR;
		}
		g_session_notify_cb_table.is_registered = 0;
	}

	/* Restore previous session */
	if (session->previous_session) {
		ret = mm_session_init_ex(session->previous_session , __session_notify_cb, NULL);
		if(ret == 0){
			g_session_notify_cb_table.is_registered = 1;
		}
	}

	if(session) {
		free(session);
		session = NULL;
	}

	LOGI("<< leave : session=%p", session);

	return SOUND_MANAGER_ERROR_NONE;

ERROR:
	return __convert_sound_manager_error_code(__func__, ret);
}

__attribute__ ((destructor))
void __sound_manager_finalize(void)
{
	int ret = SOUND_MANAGER_ERROR_NONE;

	if(g_session_notify_cb_table.is_registered){
		LOGI("<ENTER>");
		ret = mm_session_finish();
		if (ret != MM_ERROR_NONE) {
			LOGE("[%s] failed to mm_session_finish(), ret(0x%x)", __func__, ret);
		}
		g_session_notify_cb_table.is_registered = 0;
		LOGI("<LEAVE>");
	}
}

__attribute__ ((constructor))
void __sound_manager_initialize(void)
{

}
