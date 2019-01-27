#include <iostream>
#include "messages.pb.cc"

using namespace std;
int main (int argc, char const *argv[]) {
    foo::Message *message = new foo::Message();
    message->ParseFromString("Hello World!");
    cout << "Hunter Protobuf Example: " << message << endl;
    return 0;

}