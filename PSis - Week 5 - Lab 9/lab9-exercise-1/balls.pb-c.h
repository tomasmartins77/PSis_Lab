/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: balls.proto */

#ifndef PROTOBUF_C_balls_2eproto__INCLUDED
#define PROTOBUF_C_balls_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _BallDrawDisplayMsg BallDrawDisplayMsg;
typedef struct _PayperviewReq PayperviewReq;
typedef struct _PayperviewResp PayperviewResp;
typedef struct _ClientConnectionReq ClientConnectionReq;
typedef struct _MovementReq MovementReq;


/* --- enums --- */


/* --- messages --- */

struct  _BallDrawDisplayMsg
{
  ProtobufCMessage base;
  ProtobufCBinaryData ch;
  uint32_t x;
  uint32_t y;
};
#define BALL_DRAW_DISPLAY_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ball_draw_display_msg__descriptor) \
    , {0,NULL}, 0, 0 }


/*
 * TODO 1 - define a message (payperview_req) with the client name 
 *         and the credit card number (also a string)
 */
struct  _PayperviewReq
{
  ProtobufCMessage base;
  char *client_name;
  char *credit_card_number;
};
#define PAYPERVIEW_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&payperview_req__descriptor) \
    , NULL, NULL }


/*
 * TODO 1 - define a message (payperview_resp) with the 
 *         secret to the remote-display-client
 */
struct  _PayperviewResp
{
  ProtobufCMessage base;
  int32_t secret;
};
#define PAYPERVIEW_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&payperview_resp__descriptor) \
    , 0 }


/*
 * TODO 6 - define the client_connection_req message
 *          that will serialize initial client message
 */
struct  _ClientConnectionReq
{
  ProtobufCMessage base;
  uint32_t client_id;
};
#define CLIENT_CONNECTION_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&client_connection_req__descriptor) \
    , 0 }


/*
 * TODO 9 - define the movement_req message 
 *          that will serialize the movements of balls
 */
struct  _MovementReq
{
  ProtobufCMessage base;
  uint32_t client_id;
  uint32_t direction;
};
#define MOVEMENT_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&movement_req__descriptor) \
    , 0, 0 }


/* BallDrawDisplayMsg methods */
void   ball_draw_display_msg__init
                     (BallDrawDisplayMsg         *message);
size_t ball_draw_display_msg__get_packed_size
                     (const BallDrawDisplayMsg   *message);
size_t ball_draw_display_msg__pack
                     (const BallDrawDisplayMsg   *message,
                      uint8_t             *out);
size_t ball_draw_display_msg__pack_to_buffer
                     (const BallDrawDisplayMsg   *message,
                      ProtobufCBuffer     *buffer);
BallDrawDisplayMsg *
       ball_draw_display_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ball_draw_display_msg__free_unpacked
                     (BallDrawDisplayMsg *message,
                      ProtobufCAllocator *allocator);
/* PayperviewReq methods */
void   payperview_req__init
                     (PayperviewReq         *message);
size_t payperview_req__get_packed_size
                     (const PayperviewReq   *message);
size_t payperview_req__pack
                     (const PayperviewReq   *message,
                      uint8_t             *out);
size_t payperview_req__pack_to_buffer
                     (const PayperviewReq   *message,
                      ProtobufCBuffer     *buffer);
PayperviewReq *
       payperview_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   payperview_req__free_unpacked
                     (PayperviewReq *message,
                      ProtobufCAllocator *allocator);
/* PayperviewResp methods */
void   payperview_resp__init
                     (PayperviewResp         *message);
size_t payperview_resp__get_packed_size
                     (const PayperviewResp   *message);
size_t payperview_resp__pack
                     (const PayperviewResp   *message,
                      uint8_t             *out);
size_t payperview_resp__pack_to_buffer
                     (const PayperviewResp   *message,
                      ProtobufCBuffer     *buffer);
PayperviewResp *
       payperview_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   payperview_resp__free_unpacked
                     (PayperviewResp *message,
                      ProtobufCAllocator *allocator);
/* ClientConnectionReq methods */
void   client_connection_req__init
                     (ClientConnectionReq         *message);
size_t client_connection_req__get_packed_size
                     (const ClientConnectionReq   *message);
size_t client_connection_req__pack
                     (const ClientConnectionReq   *message,
                      uint8_t             *out);
size_t client_connection_req__pack_to_buffer
                     (const ClientConnectionReq   *message,
                      ProtobufCBuffer     *buffer);
ClientConnectionReq *
       client_connection_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   client_connection_req__free_unpacked
                     (ClientConnectionReq *message,
                      ProtobufCAllocator *allocator);
/* MovementReq methods */
void   movement_req__init
                     (MovementReq         *message);
size_t movement_req__get_packed_size
                     (const MovementReq   *message);
size_t movement_req__pack
                     (const MovementReq   *message,
                      uint8_t             *out);
size_t movement_req__pack_to_buffer
                     (const MovementReq   *message,
                      ProtobufCBuffer     *buffer);
MovementReq *
       movement_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   movement_req__free_unpacked
                     (MovementReq *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*BallDrawDisplayMsg_Closure)
                 (const BallDrawDisplayMsg *message,
                  void *closure_data);
typedef void (*PayperviewReq_Closure)
                 (const PayperviewReq *message,
                  void *closure_data);
typedef void (*PayperviewResp_Closure)
                 (const PayperviewResp *message,
                  void *closure_data);
typedef void (*ClientConnectionReq_Closure)
                 (const ClientConnectionReq *message,
                  void *closure_data);
typedef void (*MovementReq_Closure)
                 (const MovementReq *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor ball_draw_display_msg__descriptor;
extern const ProtobufCMessageDescriptor payperview_req__descriptor;
extern const ProtobufCMessageDescriptor payperview_resp__descriptor;
extern const ProtobufCMessageDescriptor client_connection_req__descriptor;
extern const ProtobufCMessageDescriptor movement_req__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_balls_2eproto__INCLUDED */
