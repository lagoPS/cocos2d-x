/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef CC_AUDIO_APPLE_AUDIOENGINEINL_H
#define CC_AUDIO_APPLE_AUDIOENGINEINL_H

#include <cocos/audio/apple/ALAudioPlayer.h>
#include <cocos/audio/apple/AudioCache.h>
#include <cocos/audio/apple/AudioPlayer.h>
#include <cocos/audio/apple/SimpleAudioPlayer.h>
#include <cocos/base/CCRef.h>
#include <cocos/platform/CCPlatformConfig.h>

#include <chrono>
#include <list>
#include <unordered_map>

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC

NS_CC_BEGIN
class Scheduler;

namespace experimental
{
#    define MAX_AUDIOINSTANCES 24

    class AudioEngineImpl : public cocos2d::Ref
    {
    public:
        AudioEngineImpl();
        ~AudioEngineImpl();

        bool init();
        int play2d(const std::string& fileFullPath, bool loop, float volume, bool isMusic);
        void setVolume(int audioID, float volume);
        void setLoop(int audioID, bool loop);
        bool pause(int audioID);
        bool resume(int audioID);
        void stop(int audioID);
        void stopAll();
        std::chrono::milliseconds getDuration(int audioID);
        float getCurrentTime(int audioID);
        bool setCurrentTime(int audioID, float time);
        void setFinishCallback(int audioID, const std::function<void(int, const std::string&)>& callback);

        void uncache(const std::string& filePath);
        void uncacheAll();
        AudioCache& preload(const std::string& filePath, std::function<void(bool)> const& callback);
        void update(float dt);

    private:
        void _play2d(AudioPlayer* player, AudioCache& audioCache, bool loop, float volume);
        void _play2d(AudioCache& cache, int audioID, std::shared_ptr<std::atomic_bool> isCacheDestroyed);
        ALuint findValidSource();

        static ALvoid myAlSourceNotificationCallback(ALuint sid, ALuint notificationID, ALvoid* userData);

        ALuint _alSources[MAX_AUDIOINSTANCES];

        // source,used
        std::list<ALuint> _unusedSourcesPool;

        // filePath,bufferInfo
        std::unordered_map<std::string, AudioCache> _audioCaches;

        // audioID,AudioInfo
        std::unordered_map<int, AudioPlayer*> _audioPlayers;
        std::mutex _threadMutex;

        bool _lazyInitLoop;

        int _currentAudioID;
        Scheduler* _scheduler;
    };
} // namespace experimental
NS_CC_END
#endif
#endif // CC_AUDIO_APPLE_AUDIOENGINEINL_H
