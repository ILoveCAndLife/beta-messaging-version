#include <iostream>
#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

int main() {
    boost::asio::io_context io_context;

    std::string RMtext;
    std::string SMtext;
    std::string ChosenIP;
    std::string PlatformChoice;
    std::string MS;
    std::string DecryptionKey;

    std::cout << "Please enter the IP you would like to talk with.";
    std::cout << "Keep in mind that bad actors can bit flip since this uses XOR. never agree on transferring money.";
    std::cout << "NEVER share your keys either. just dont. your message can be decrypted.";
    std::cout << "Use at your own risk too.";
    std::cout << "Also just type ABC to go into recieving mode.";
    std::cout << "                  ";
    std::cout << "Keep in mind that I also encrypt your messages.";
    std::cout << "well, atleast if you type your key that you and your friend have to agree on!";
    std::cout << "by the way if you add any spaces std::cin will break. dont make it simple.";
    std::cin >> DecryptionKey;
    std::cin.ignore();
    std::cout << "                  ";
    std::cout << "choose the ip now.";
    std::cin >> ChosenIP;
    std::cin.ignore();

    if (ChosenIP == "ABC") {
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 80));
        std::cout << "WAITING FOR MESSAGE.";
        std::cout << "Keep in mind that this uses port 80 which is meant for HTTP traffic.";
        std::cout << "If this doesnt work, please check your firewall settings.";
        while (true) {
            boost::asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, "\n");
            SMtext.assign(boost::asio::buffers_begin(buffer.data()), boost::asio::buffers_end(buffer.data()));
            for (size_t i = 0; i < SMtext.size(); ++i) {
                SMtext[i] ^= DecryptionKey[i % DecryptionKey.size()];
            }

            buffer.consume(buffer.size());
            std::cout << SMtext << "\n";
            std::cout << "       ";
            std::cout << "listening finished.";
            return 0;
        }

    }
    std::cout << "Alright. The IP will recieve the message if they have this program open.";
    std::cout << "                  ";
    std::cout << "type your message.";
    std::cout << "       ";
    std::cout << "if the user doesnt recieve the message, tell them to temporarily disable their firewall.";
    std::cout << "       ";
    std::getline(std::cin, RMtext);
    tcp::endpoint peer_endpoint(boost::asio::ip::address::from_string(ChosenIP), 80);
    boost::asio::ip::tcp::socket socket(io_context);
    socket.connect(peer_endpoint);

    for (size_t i = 0; i < RMtext.size(); ++i) {
        RMtext[i] ^= DecryptionKey[i % DecryptionKey.size()];
    }
    boost::asio::write(socket, boost::asio::buffer(RMtext + "\n"));
    std::cout << "it has been sent.";
}





