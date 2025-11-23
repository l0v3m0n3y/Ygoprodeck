# Ygoprodeck
api for ygoprodeck.com site about Yu-Gi-Oh
# main
```cpp
#include "Ygoprodeck.h"
#include <iostream>

int main() {
   Ygoprodeck api;

    auto version = api.database_version().then([](json::value result) {
        std::cout << result<< std::endl;
    });
    version.wait();
    
    return 0;
}
```

# Launch (your script)
```
g++ -std=c++11 -o main main.cpp -lcpprest -lssl -lcrypto -lpthread -lboost_system -lboost_chrono -lboost_thread
./main
```

