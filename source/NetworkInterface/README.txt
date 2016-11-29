Below the message formats for encoding and decoding and who (client or server) should send what: 

In game:
General procedure : 
Server will send a string identifier of a request or notification
client may or may not reply.

requestMove()
Server sends : "Give Move"
Client Responds string as : <SUIT><char><opt char>
where the first char is either H, S, D, or C
and the next chars are a decodeable number corresponding to the 
correct enum value for Value

requestBid()
Server sends : "Give Bid"
client responds int parseable string representing the bid

requestSuit()
Server sends : "Give Suit"
client responds with single char representing suit either H, S, C or D

updateGameStatus()
Server sends : "Status update"
Server sends : serialized status of game
Client sends nothing but decodes game status and updates UI