/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. 
 */


#ifndef __TIZEN_MEDIA_SOUND_MANAGER_DOC_H__
#define __TIZEN_MEDIA_SOUND_MANAGER_DOC_H__


/**
 * @file sound_manager_doc.h
 * @brief This file contains high level documentation of the Sound Manager API.
 */

/**
 * @defgroup CAPI_MEDIA_SOUND_MANAGER_MODULE Sound Manager
 * @brief  The @ref CAPI_MEDIA_SOUND_MANAGER_MODULE  APIs provides functions to get and set sound parameters like volume and route policy.
 * @ingroup CAPI_MEDIA_FRAMEWORK
 *
 * @section CAPI_MEDIA_SOUND_MANAGER_MODULE_HEADER Required Header
 *   \#include <sound_manager.h>
 *
 * @section CAPI_MEDIA_SOUND_MANAGER_OVERVIEW Overview
 * The Sound Manager service provides APIs to manage audio output.
 *
 * The Sound Manager API allows you to:
 * - check/control output volume
 * - change audio route policy
 * - handle volume changed notification
 * - handle audio route policy change notificat
 *
 * Current volume level can be checked with sound_manager_get_volume().
 * To get maximum supported volume level, call sound_manager_get_max_volume().
 * The volume level can be adjusted with sound_manager_set_volume().
 *
 * The Sound Manager has predefined types of sounds, such as ringtone, call, alarm, etc.  The type of the currently playing sound may be
 * obtained by calling sound_manager_get_current_sound_type().
 *
 * @subsection CAPI_MEDIA_SOUND_MANAGER_DESCRIPTION_ROUTE_POLICY Route policy
 * The route policy is responsible for selection of sound sources and outputs that should be active. \n
 * Note: The bluetooth headset microphone is used only in the voice call mode.
 * <p>
 * <ul>
 *    <li> The default audio route policy is #SOUND_ROUTE_DEFAULT <p></li>
 *    <table>
 *        <tr>
 *           <td><b>Mode</b></td>
 *           <td><b>Bluetooth headset</b></td>
 *           <td><b>Wired headset</b></td>
 *           <td><b>Used device</b></td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>connected</td>
 *           <td>plugged</td>
 *           <td>Bluetooth headset</td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>connected</td>
 *           <td>unplugged</td>
 *           <td>Bluetooth headset</td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>disconnected</td>
 *           <td>plugged</td>
 *           <td>Wired headset</td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>disconnected</td>
 *           <td>unplugged</td>
 *           <td>Loudspeaker</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>connected</td>
 *           <td>plugged</td>
 *           <td>Wired headset microphone</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>connected</td>
 *           <td>unplugged</td>
 *           <td>Microphone</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>disconnected</td>
 *           <td>plugged</td>
 *           <td>Wired headset microphone</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>disconnected</td>
 *           <td>unplugged</td>
 *           <td>Built-in microphone</td>
 *        </tr>
 *    </table>
 *
 *    <li> The bluetooth headset will be ignored for the routing policy set to #SOUND_ROUTE_IGNORE_A2DP <p></li>
 *    <table>
 *        <tr>
 *           <td><b>Mode</b></td>
 *           <td><b>Bluetooth headset</b></td>
 *           <td><b>Wired headset</b></td>
 *           <td><b>Used device</b></td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>connected</td>
 *           <td>plugged</td>
 *           <td>Wired headset</td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>connected</td>
 *           <td>unplugged</td>
 *           <td>Loudspeaker</td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>disconnected</td>
 *           <td>plugged</td>
 *           <td>Wired headset</td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>disconnected</td>
 *           <td>unplugged</td>
 *           <td>Loudspeaker</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>connected</td>
 *           <td>plugged</td>
 *           <td>Wired headset microphone</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>connected</td>
 *           <td>unplugged</td>
 *           <td>Microphone</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>disconnected</td>
 *           <td>plugged</td>
 *           <td>Wired headset microphone</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>disconnected</td>
 *           <td>unplugged</td>
 *           <td>Built-in microphone</td>
 *        </tr>
 *    </table>
 *
 *    <li> Only the loudspeaker and microphone will be used for the routing policy set to #SOUND_ROUTE_HANDSET_ONLY <p></li>
 *    <table>
 *        <tr>
 *           <td><b>Mode</b></td>
 *           <td><b>Bluetooth headset</b></td>
 *           <td><b>Wired headset</b></td>
 *           <td><b>Used device</b></td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>connected</td>
 *           <td>plugged</td>
 *           <td>Loudspeaker</td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>connected</td>
 *           <td>unplugged</td>
 *           <td>Loudspeaker</td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>disconnected</td>
 *           <td>plugged</td>
 *           <td>Loudspeaker</td>
 *        </tr>
 *        <tr>
 *           <td>PLAYBACK</td>
 *           <td>disconnected</td>
 *           <td>unplugged</td>
 *           <td>Loudspeaker</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>connected</td>
 *           <td>plugged</td>
 *           <td>Microphone</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>connected</td>
 *           <td>unplugged</td>
 *           <td>Microphone</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>disconnected</td>
 *           <td>plugged</td>
 *           <td>Microphone</td>
 *        </tr>
 *        <tr>
 *           <td>CAPTURE</td>
 *           <td>disconnected</td>
 *           <td>unplugged</td>
 *           <td>Microphone</td>
 *        </tr>
 *    </table>
 * </ul>
 *
 * The sound_manager_set_route_policy() and  sound_manager_get_route_policy() functions set and check the route policy, which is limited to the pre-defined policies described.
 *
 * @subsection CAPI_MEDIA_SOUND_MANAGER_LIFE_CYCLE_ASYNCHRONOUS_OPERATIONS Asynchronous operations
 * The Sound Manager API provides only asynchronous operations. \n
 * Thus the result will be passed to the application via the callback mechanism.
 * An appropriate callback can be called in response to changes initiated from outside the application. \n
 * Possible callbacks are listed below:
 * <p>
 * <ul>
 *    <li> sound_manager_volume_changed_cb - invoked when volume level is changed.<p></li>
 *    <li> sound_manager_route_policy_changed_cb - invoked when route policy is changed.<p></li>
 * </ul>
 *
 * @subsection CAPI_MEDIA_SOUND_MANAGER_MODULE_LIFE_CYCLE_CALLBACK_OPERATIONS  Callback(Event) Operations
 * The callback mechanism is used to notify the application about significant sound manager events.
 * <div><table class="doxtable" >
 *     <tr>
 *        <th><b> REGISTER</b></th>
 *        <th><b> UNREGISTER</b></th> 
 *        <th><b> CALLBACK</b></th>
 *        <th><b> DESCRIPTION</b></th>
 *     </tr>
 *     <tr>
 *        <td> sound_manager_set_volume_changed_cb()</td>
 *        <td> sound_manager_unset_volume_changed_cb()</td> 
 *        <td> sound_manager_volume_changed_cb()</td>
 *        <td> This callback is called when volume value is changed.</td>
 *     </tr>
 *     <tr>
 *        <td> sound_manager_set_route_policy_changed_cb()</td>
 *        <td> sound_manager_unset_route_policy_changed_cb()</td> 
 *        <td> sound_manager_route_policy_changed_cb()</td>
 *        <td> This callback is called when the route policy is changed.</td>
 *     </tr> 
 * </table></div>
 *
*/

#endif /* __TIZEN_MEDIA_SOUND_MANAGER_DOC_H__ */
