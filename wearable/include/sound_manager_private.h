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

#ifndef __TIZEN_MEDIA_SOUND_MANAGER_PRIVATE_H__
#define __TIZEN_MEDIA_SOUND_MANAGER_PRIVATE_H__

#ifdef __cplusplus
extern "C"
{
#endif

struct sound_call_session_s
{
	int previous_session;
};

struct sound_multi_session_s
{
	int previous_session;
	sound_multi_session_type_e type;
	int type_option;
};

int __convert_sound_manager_error_code(const char *func, int code);

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_MEDIA_SOUND_MANAGER_PRIVATE_H__ */
