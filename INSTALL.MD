####In Development Dragon Ball Online Server using Taiwan Game Client 1.69

- Prerequisites
  - Very few things are needed for compiing the emulator:
    - An up to date windows x64 !
      - 2015 redistribuable c++
    - Visual studio 15 - Community or highter
  
    - Lib directory:
      - packages\boost.1.63.0.0\compiled\
        - *.boostFile.lib
        - https://sourceforge.net/projects/boost/files/boost-binaries/1.63.0/boost_1_63_0-msvc-14.0-64.exe/download
        - your compiled folder should look like:
          - https://puu.sh/w8KjB/6c532dcd8e.png
        
    - PACKAGE:
      - Boost 1.63 nugget package
      - libxml2.2 nugget package
      - libxml2 redist nugget package
      - libxml2-vc140-static-64 nugget package
        
    - LAZY:
      - extract on root directory:
      - https://mega.nz/#!Ux9zWKaR!PvX7xkzdFpGCSHITBwtxJyZyKEidvxC0dLkPEnIWB_g
        - https://puu.sh/w8Kxz/3fef68c584.png
        
    - COMPILING
      - set the projet to RELEASE & x64 !
      
      
- DATABASE:
  - WAMP OR XAMP OR Any mysql server
    - Install dragonball.sql
    - Done
  
  - NETWORK CONFIG FILE:
    - (AuthServer - CharServer - GameServer) *.xml
    - Server IP (your public ip address)
    - Port (server port)
    - Mysql:
      - Host: your local address : your mysql port
      - Database: your dragon ball database name
      - User: your mysql username (see phpmyadmin if you don't create any)
      - Password: your mysql password (as below)
