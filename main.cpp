#include <iostream>
#include "Platform.h"
#include "PrivateStream.h"
#include "Viewer.h"
#include "Stream.h"

int main(int argc, char* argv[]) {
    Platform platform;
    // Test 1
    /*
    for(int i = 0; i < 10; ++i){
        platform.registerViewer("viewer" + std::to_string(i), "Name" + std::to_string(i), Date("01/01/1984 00:00:00"));
        platform.registerStreamer("streamer" + std::to_string(i), "Streamer Name" + std::to_string(i), Date("01/01/1984 00:00:00"));
        platform.startPublicStream("title" + std::to_string(i), "streamer" + std::to_string(i), "PT", 15);
    }
    for(int i = 0; i < 10; i+=2){
        Viewer * ptr = dynamic_cast<Viewer *>(platform.getUser("viewer" + std::to_string(i)));
        std::weak_ptr<Stream> stream = platform.joinStreamById(i+1,*ptr);
        stream.lock()->giveLike();
    }

    platform.sort(id, descending);
    platform.showStreams();
    platform.topActiveStreams();
    platform.showStreams();
    platform.topArchivedStreams();

    for(int i = 0; i < 5; ++i){
        platform.endStream(i+1);
    }

    platform.topActiveStreams();
    platform.showStreams();
    platform.topArchivedStreams();*/
    
    // Test 2
    /*
    std::vector<std::string> allowed;
    allowed.reserve(10);
    for(int i = 0; i < 10; ++i){
        allowed.push_back("viewer" + std::to_string(i));
    }
    
    for(int i = 0; i < 10; ++i){
        platform.registerViewer("viewer" + std::to_string(i), "Name" + std::to_string(i), Date("01/01/1984 00:00:00"));
        platform.registerStreamer("streamer" + std::to_string(i), "Streamer Name" + std::to_string(i), Date("01/01/1984 00:00:00"));
        platform.startPrivateStream("title" + std::to_string(i), "streamer" + std::to_string(i), "PT", 15, 12, allowed);
    }
    for(int i = 0; i < 10; i+=2){
        Viewer * ptr = dynamic_cast<Viewer *>(platform.getUser("viewer" + std::to_string(i)));
        weak_ptr<PrivateStream> stream = weak_ptr<PrivateStream>(dynamic_pointer_cast<PrivateStream>(platform.joinStreamById(i+1,*ptr).lock()));
        stream.lock()->addComment(*ptr, "Very much good, comment made by me, viewer creatively named viewer" + std::to_string(i));
        stream.lock()->addComment(*ptr, "Second comment");
    }
    for(int i = 0; i < 5; ++i){
        platform.endStream(i);
    }*/
    std::cout << "StreamZ" << std::endl;
    return 0;
}