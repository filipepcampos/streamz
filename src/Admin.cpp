#include "Admin.h"

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
    return 0;
}

std::string Admin::topLanguage() const {
    return "Portuguese";
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
        vector<unsigned int> history = streamer->getStreamsHistory();
        for (StreamData stream : platform->archive.streams) {
            if (history.size() == 0) break;
            for (int i = 0; i < history.size(); i++) {
                if (history.at(i) == stream.getId()) {
                    views += stream.getViewers();
                    history.erase(history.begin() + i);
                    break;
                }
            }
        }
        if (views > maxViews) {
            maxViews = views;
            maxStreamer = streamer;
        }
        views = 0;
    }
    return maxStreamer;
}
