#include "StreamerRecord.h"
#include "Streamer.h"


StreamerRecord::StreamerRecord(Streamer * st) : active(true), streamer(st), nickname(st->getNickname()) {
}

StreamerRecord::StreamerRecord(const std::string &nick) : active(false), streamer(nullptr), nickname(nick) {
}

StreamerRecord::StreamerRecord(const StreamerRecord &sr) {
    nickname.clear();
    active = sr.active;
    streamer = sr.streamer;
    nickname = sr.nickname;
}

StreamerRecord::~StreamerRecord() {
    streamer = nullptr;
    nickname.clear();
}

const Streamer * StreamerRecord::getStreamer() const {
    return streamer;
}

std::string StreamerRecord::getNickname() const {
    return nickname;
}

bool StreamerRecord::isActive() const {
    return active;
}
