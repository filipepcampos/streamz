#include "Admin.h"
#include "Stream.h"
#include "Streamer.h"
#include "Date.h"
#include <map>

Admin::Admin(const Platform * platform) : platform(platform) {
}

float Admin::averageViews() const {
    unsigned int totalStreams = 0, totalViews = 0;
    for (std::shared_ptr<Stream> stream : platform->active_streams) {
        totalStreams++;
        totalViews += stream->getViewers();
    }
    for (StreamData stream : platform->archive.streams) {
        totalStreams++;
        totalViews += stream.getViewers();
    }
    if (totalStreams == 0) return 0;
    return (float) totalViews / totalStreams;
}

unsigned int Admin::streamsCounter(const bool isPublic, const Date &lower, const Date &upper) const {
    unsigned int counter = 0;
    for (std::shared_ptr<Stream> stream : platform->active_streams)
        if (stream->getIsPublic() == isPublic && checkDateIntersection(stream->getStartDate(),Date(), lower, upper))
            counter++;
    for (StreamData stream : platform->archive.streams)
        if (stream.getIsPublic() == isPublic && checkDateIntersection(stream.getStartDate(),stream.getEndDate(), lower, upper))
            counter++;
    return counter;
}

std::string Admin::topLanguage() const {
    map<string, unsigned int> languages;
    for (std::shared_ptr<Stream> stream : platform->active_streams) {
        languages[stream->getLanguage()]++;
    }
    for (StreamData stream : platform->archive.streams) {
        languages[stream.getLanguage()]++;
    }

    unsigned maxCounter = 0;
    string maxLanguage = "There are no streams"; // In case no stream is processed
    map<string, unsigned int>::iterator it = languages.begin();
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
    for (std::shared_ptr<Stream> stream : platform->active_streams) {
        stream->getIsPublic() ? totalPublic++ : totalPrivate++;
    }
    for (StreamData stream : platform->archive.streams) {
        stream.getIsPublic() ? totalPublic++ : totalPrivate++;
    }
    if (totalPublic == totalPrivate) return "draw";
    return totalPublic > totalPrivate ? "public" : "private";
}

Streamer * Admin::topStreamer() const {
    unsigned int maxViews = 0;
    Streamer * maxStreamer;

    Streamer * streamer;
    unsigned int views = 0;
    for (User * user : platform->users) {
        try {
            streamer = dynamic_cast<Streamer*> (user);
            if (streamer == nullptr) throw std::bad_cast();
        }
        catch (std::bad_cast& bc) {
            continue;
        }
        vector<const StreamData *> history = platform->archive.getStreamsById(streamer->getStreamsHistory());


        for (const StreamData * stream : history)
            views += stream->getViewers();

        if (views > maxViews) {
            maxViews = views;
            maxStreamer = streamer;
        }
        views = 0;
    }
    return maxStreamer;
}
