/*
   Copyright (c) 2010, The Mineserver Project
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
 * Neither the name of the The Mineserver Project nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _PACKETS_H
#define _PACKETS_H

#define PACKET_NEED_MORE_DATA -3
#define PACKET_VARIABLE_LEN   -1
#define PACKET_DOES_NOT_EXIST -2

class PacketHandler;

//Packet names
enum
{
  //Client to server
  PACKET_KEEP_ALIVE                = 0x00,
  PACKET_LOGIN_REQUEST             = 0x01,
  PACKET_HANDSHAKE                 = 0x02,
  PACKET_CHAT_MESSAGE              = 0x03,
  PACKET_PLAYER_INVENTORY          = 0x05,
  PACKET_PLAYER                    = 0x0a,
  PACKET_PLAYER_POSITION           = 0x0b,
  PACKET_PLAYER_LOOK               = 0x0c,
  PACKET_PLAYER_POSITION_AND_LOOK  = 0x0d,
  PACKET_PLAYER_DIGGING            = 0x0e,
  PACKET_PLAYER_BLOCK_PLACEMENT    = 0x0f,
  PACKET_HOLDING_CHANGE            = 0x10,
  PACKET_ARM_ANIMATION             = 0x12,
  PACKET_DISCONNECT                = 0xff,
  //Server to client
  PACKET_LOGIN_RESPONSE            = 0x01,
  PACKET_TIME_UPDATE               = 0x04,
  PACKET_SPAWN_POSITION            = 0x06,
  PACKET_ADD_TO_INVENTORY          = 0x11,
  PACKET_NAMED_ENTITY_SPAWN        = 0x14,
  PACKET_PICKUP_SPAWN              = 0x15,
  PACKET_COLLECT_ITEM              = 0x16,
  PACKET_ADD_OBJECT                = 0x17,
  PACKET_MOB_SPAWN                 = 0x18,
  PACKET_DESTROY_ENTITY            = 0x1d,
  PACKET_ENTITY                    = 0x1e,
  PACKET_ENTITY_RELATIVE_MOVE      = 0x1f,
  PACKET_ENTITY_LOOK               = 0x20,
  PACKET_ENTITY_LOOK_RELATIVE_MOVE = 0x21,
  PACKET_ENTITY_TELEPORT           = 0x22,
  PACKET_PRE_CHUNK                 = 0x32,
  PACKET_MAP_CHUNK                 = 0x33,
  PACKET_MULTI_BLOCK_CHANGE        = 0x34,
  PACKET_BLOCK_CHANGE              = 0x35,
  PACKET_COMPLEX_ENTITIES          = 0x3b,
  PACKET_KICK                      = 0xff,


  //v4 Packets
  PACKET_USE_ENTITY      = 0x07,
  PACKET_ENTITY_VELOCITY = 0x1c,
  PACKET_ATTACH_ENTITY   = 0x27,
};


struct Packets
{
  int len;
  void (PacketHandler::*function)(uint8 *, User *);

  int (PacketHandler::*varLenFunction)(User *);

  Packets()
  {
    len = PACKET_DOES_NOT_EXIST;
  }
  Packets(int newlen)
  {
    len = newlen;
  }
  Packets(int newlen, void (PacketHandler::*newfunction)(uint8*, User *))
  {
    len      = newlen;
    function = newfunction;
  }

  Packets(int newlen, int (PacketHandler::*newfunction)(User *))
  {
    len            = newlen;
    varLenFunction = newfunction;
  }
};

struct packet_login_request
{
  int version;
  std::string Username;
  std::string Password;
  sint64 map_seed;
  uint8 dimension;
};

struct packet_player_position
{
  double x;
  double y;
  double stance;
  double z;
  char onground;
};

struct packet_player_look
{
  float yaw;
  float pitch;
  char onground;
};

struct packet_player_position_and_look
{
  double x;
  double y;
  double stance;
  double z;
  float yaw;
  float pitch;
  char onground;
};

class PacketHandler
{

private:
  PacketHandler()
  {
  }
  ~PacketHandler()
  {
  }

public:

  void initPackets();



  static PacketHandler &get()
  {
    static PacketHandler instance;
    return instance;
  }
  //Information of all the packets
  //around 2kB of memory
  Packets packets[256];

  //The packet functions
  void keep_alive(uint8 *data, User *user);
  int  login_request(User *user);
  int  handshake(User *user);
  int  chat_message(User *user);
  int  player_inventory(User *user);
  void player(uint8 *data, User *user);
  void player_position(uint8 *data, User *user);
  void player_look(uint8 *data, User *user);
  void player_position_and_look(uint8 *data, User *user);
  void player_digging(uint8 *data, User *user);
  void player_block_placement(uint8 *data, User *user);
  void holding_change(uint8 *data, User *user);
  void arm_animation(uint8 *data, User *user);
  void pickup_spawn(uint8 *data, User *user);
  int  disconnect(User *user);
  int  complex_entities(User *user);

  void use_entity(uint8 *data, User *user);


};




#endif
