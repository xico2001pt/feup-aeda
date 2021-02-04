#include "Admin.h"
#include "Stream.h"
#include "Streamer.h"
#include "Date.h"
#include <map>

Admin::Admin(const Platform & platform) : platform(platform) {
}

float Admin::averageViews() const {
    unsigned int totalStreams = 0, totalViews = 0;
    for (const std::shared_ptr<Stream> &stream : platform.active_streams) {
        totalStreams++;
        totalViews += stream->getViewers();
    }
    for (const StreamData& stream : platform.archive.streams) {
        totalStreams++;
        totalViews += stream.getViewers();
    }
    if (totalStreams == 0) return 0;
    return (float) totalViews / totalStreams;
}

unsigned int Admin::streamsCounter(const bool isPublic, const Date &lower, const Date &upper) const {
    unsigned int counter = 0;
    for (const std::shared_ptr<Stream>& stream : platform.active_streams)
        if (stream->getIsPublic() == isPublic && checkDateIntersection(stream->getStartDate(),Date(), lower, upper))
            counter++;
    for (const StreamData& stream : platform.archive.streams)
        if (stream.getIsPublic() == isPublic && checkDateIntersection(stream.getStartDate(),stream.getEndDate(), lower, upper))
            counter++;
    return counter;
}

std::string Admin::topLanguage() const {
    std::map<std::string, unsigned int> languages;
    for (const std::shared_ptr<Stream>& stream : platform.active_streams) {
        languages[stream->getLanguage()]++;
    }
    for (const StreamData& stream : platform.archive.streams) {
        languages[stream.getLanguage()]++;
    }

    unsigned maxCounter = 0;
    std::string maxLanguage = "There are no streams"; // In case no stream is processed
    auto it = languages.begin();
    while (it != languages.end()) {
        if (it->second > maxCounter) {
            maxLanguage = it->first;
            maxCounter = it->second;
        }
        it++;
    }
    return maxLanguage;
}

std::string Admin::topTypeStream() const {
    unsigned int totalPublic = 0, totalPrivate = 0;
    for (const std::shared_ptr<Stream>& stream : platform.active_streams) {
        stream->getIsPublic() ? totalPublic++ : totalPrivate++;
    }
    for (const StreamData& stream : platform.archive.streams) {
        stream.getIsPublic() ? totalPublic++ : totalPrivate++;
    }
    if (totalPublic == totalPrivate) return "draw";
    return totalPublic > totalPrivate ? "public" : "private";
}

std::string Admin::topStreamer() const {
    std::map<std::string, unsigned int> streamers;
    for (const std::shared_ptr<Stream>& stream : platform.active_streams) {
        streamers[stream->getStreamer()]++;
    }
    for (const StreamData& stream : platform.archive.streams) {
        streamers[stream.getStreamer()]++;
    }

    unsigned maxCounter = 0;
    std::string maxStreamer = "There are no streamers"; // In case no streamer is processed
    auto it = streamers.begin();
    while (it != streamers.end()) {
        if (it->second > maxCounter) {
            maxStreamer = it->first;
            maxCounter = it->second;
        }
        it++;
    }
    return maxStreamer;
}
