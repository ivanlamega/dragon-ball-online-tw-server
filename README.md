####In Development Dragon Ball Online Server using Taiwan Game Client 1.69

Server Developpement:

- Auth Server:
  - 99% done
  - TODO:
    - check for multi server not working ???

- Char Server:
  - 90% done
  - TODO:
    - Some packet are not handled:
      - UC_CONNECT_WAIT_CANCEL_REQ
      - UC_CASHITEM_HLSHOP_REFRESH_REQ ??
      - UC_CASHITEM_BUY_REQ ?
    - Log onto the game server and ask it the current waiting queue.
    
- GameServer
  - 5 % done
  - Can logging
    - NPC / MOB AROUND SPAWN
      - ISSUS: We don't know how to not spawn quest mob etc
    - INVENTORY
      - SELL
      - BUY
    - TELEPORT
      - ISSUS: don't find yet the cost
    - STATS
      - Calculate for level
      - Level up
      - Calculate when moving equipped item
