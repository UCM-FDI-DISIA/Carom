#include "Frame.h"

Frame::Frame(Uint32 frameDuration, Texture* tex, float scale, Frame* nextFrame = nullptr, 
        std::function<void()> enterCallback = [] {}, std::function<void()> exitCallback = [] {})
: _milliseconds(frameDuration * (1000/60)),
_texture(tex),
_scale(scale),
_nextFrame(nextFrame),
_enterCallback(enterCallback),
_exitCallback(exitCallback) {

        assert(_milliseconds > 0 && _texture != nullptr);
    }

void
Frame::setNextframe(Frame* frame) {
        _nextFrame = frame;
}