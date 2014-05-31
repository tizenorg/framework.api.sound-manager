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

#include <mm_sound.h>
#include <dlog.h>

int __convert_sound_manager_error_code(const char *func, int code) {
	int ret = SOUND_MANAGER_ERROR_NONE;
	char *errorstr = NULL;

	switch(code)
	{
		case SOUND_MANAGER_ERROR_INVALID_PARAMETER:
			ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
			errorstr = "INVALID_PARAMETER";
			break;
		case SOUND_MANAGER_ERROR_INVALID_OPERATION:
		case MM_ERROR_INVALID_HANDLE:
			ret = SOUND_MANAGER_ERROR_INVALID_OPERATION;
			errorstr = "INVALID_OPERATION";
			break;
		case MM_ERROR_NONE:
			ret = SOUND_MANAGER_ERROR_NONE;
			errorstr = "ERROR_NONE";
			break;
		case MM_ERROR_INVALID_ARGUMENT:
		case MM_ERROR_SOUND_INVALID_POINTER:
			ret = SOUND_MANAGER_ERROR_INVALID_PARAMETER;
			errorstr = "INVALID_PARAMETER";
			break;
		case MM_ERROR_SOUND_INTERNAL:
			ret = SOUND_MANAGER_ERROR_INTERNAL;
			errorstr = "INTERNAL";
			break;
		case MM_ERROR_POLICY_DUPLICATED:
		case MM_ERROR_POLICY_INTERNAL:
		case MM_ERROR_POLICY_BLOCKED:
			ret = SOUND_MANAGER_ERROR_POLICY;
			errorstr = "POLICY";
			break;
		case MM_ERROR_POLICY_BLOCKED_BY_CALL:
			ret = SOUND_MANAGER_ERROR_POLICY_BLOCKED_BY_CALL;
			errorstr = "POLICY_BLOCKED_BY_CALL";
			break;
		case MM_ERROR_POLICY_BLOCKED_BY_ALARM:
			ret = SOUND_MANAGER_ERROR_POLICY_BLOCKED_BY_ALARM;
			errorstr = "POLICY_BLOCKED_BY_ALARM";
			break;
		case MM_ERROR_SOUND_VOLUME_NO_INSTANCE:
			ret = SOUND_MANAGER_ERROR_NO_PLAYING_SOUND;
			errorstr = "NO_PLAYING_SOUND";
			break;
		case MM_ERROR_SOUND_VOLUME_CAPTURE_ONLY:
			ret = SOUND_MANAGER_ERROR_CAPTURE_ONLY;
			errorstr = "CAPTURE_ONLY";
			break;
		case MM_ERROR_SOUND_VOLUME_BLOCKED_BY_SAFETY:
			ret = SOUND_MANAGER_ERROR_NO_OPERATION;
			errorstr = "NO_OPERATION";
			break;
	}
	LOGE("[%s] %s(0x%08x) : core frameworks error code(0x%08x)",func, errorstr, ret, code);
	return ret;
}
