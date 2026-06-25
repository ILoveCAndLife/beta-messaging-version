my first attempt at a cool email-ish messaging app. really bad, but atleast its open source lol
i used port 80 because it is usually open to inbound traffic
still conflicted with firewalls i cant lie though
i used XOR encryption even though it is viable to bit flipping because it just works extremely well for P2P messaging
it is still cryptographically sensitive (woah that was a long word)
if youre recieving the packages you MIGHT need to alter your firewall

REQUIREMENTS:

boost asio downloaded
g++ downloaded

to compile, you can also do 
```bash
g++ betamessagingversion.cpp -o messaging_app -lboost_system -pthread
